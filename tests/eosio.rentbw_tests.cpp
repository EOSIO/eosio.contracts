#include <Runtime/Runtime.h>
#include <boost/test/unit_test.hpp>
#include <cstdlib>
#include <eosio/chain/contract_table_objects.hpp>
#include <eosio/chain/exceptions.hpp>
#include <eosio/chain/global_property_object.hpp>
#include <eosio/chain/resource_limits.hpp>
#include <eosio/chain/wast_to_wasm.hpp>
#include <fc/log/logger.hpp>
#include <iostream>
#include <sstream>

#include "eosio.system_tester.hpp"

inline constexpr int64_t rentbw_frac  = 1'000'000'000'000'000ll; // 1.0 = 10^15
inline constexpr int64_t stake_weight = 100'000'000'0000ll; // 10^12

struct rentbw_config_resource {
   int64_t        current_weight_ratio = {};
   int64_t        target_weight_ratio  = {};
   int64_t        assumed_stake_weight = {};
   time_point_sec target_timestamp     = {};
   double         exponent             = {};
   uint32_t       decay_secs           = {};
   asset          target_price         = asset{};
};
FC_REFLECT(rentbw_config_resource,                                                             //
           (current_weight_ratio)(target_weight_ratio)(assumed_stake_weight)(target_timestamp) //
           (exponent)(decay_secs)(target_price))

struct rentbw_config {
   rentbw_config_resource net            = {};
   rentbw_config_resource cpu            = {};
   uint32_t               rent_days      = {};
   asset                  min_rent_price = asset{};
};
FC_REFLECT(rentbw_config, (net)(cpu)(rent_days)(min_rent_price))

struct rentbw_state_resource {
   uint8_t        version;
   int64_t        weight;
   int64_t        weight_ratio;
   int64_t        assumed_stake_weight;
   int64_t        initial_weight_ratio;
   int64_t        target_weight_ratio;
   time_point_sec initial_timestamp;
   time_point_sec target_timestamp;
   double         exponent;
   uint32_t       decay_secs;
   asset          target_price;
   int64_t        utilization;
   int64_t        adjusted_utilization;
   time_point_sec utilization_timestamp;
};
FC_REFLECT(rentbw_state_resource,                                                                           //
           (version)(weight)(weight_ratio)(assumed_stake_weight)(initial_weight_ratio)(target_weight_ratio) //
           (initial_timestamp)(target_timestamp)(exponent)(decay_secs)(target_price)(utilization)           //
           (adjusted_utilization)(utilization_timestamp))

struct rentbw_state {
   uint8_t               version;
   rentbw_state_resource net;
   rentbw_state_resource cpu;
   uint32_t              rent_days;
   asset                 min_rent_price;
};
FC_REFLECT(rentbw_state, (version)(net)(cpu)(rent_days)(min_rent_price))

using namespace eosio_system;

struct rentbw_tester : eosio_system_tester {

   rentbw_tester() { create_accounts_with_resources({ N(eosio.reserv) }); }

   void start_rex() {
      create_account_with_resources(N(rexholder111), config::system_account_name, core_sym::from_string("1.0000"),
                                    false);
      transfer(config::system_account_name, N(rexholder111), core_sym::from_string("1001.0000"));
      BOOST_REQUIRE_EQUAL("", stake(N(rexholder111), N(rexholder111), core_sym::from_string("500.0000"),
                                    core_sym::from_string("500.0000")));
      create_account_with_resources(N(proxyaccount), config::system_account_name, core_sym::from_string("1.0000"),
                                    false, core_sym::from_string("500.0000"), core_sym::from_string("500.0000"));
      BOOST_REQUIRE_EQUAL("",
                          push_action(N(proxyaccount), N(regproxy), mvo()("proxy", "proxyaccount")("isproxy", true)));
      BOOST_REQUIRE_EQUAL("", vote(N(rexholder111), {}, N(proxyaccount)));
      BOOST_REQUIRE_EQUAL("", push_action(N(rexholder111), N(deposit),
                                          mvo()("owner", "rexholder111")("amount", asset::from_string("1.0000 TST"))));
      BOOST_REQUIRE_EQUAL("", push_action(N(rexholder111), N(buyrex),
                                          mvo()("from", "rexholder111")("amount", asset::from_string("1.0000 TST"))));
   }

   template <typename F>
   rentbw_config make_config(F f) {
      rentbw_config config;

      config.net.current_weight_ratio = rentbw_frac;
      config.net.target_weight_ratio  = rentbw_frac / 100;
      config.net.assumed_stake_weight = stake_weight;
      config.net.target_timestamp     = control->head_block_time() + fc::days(100);
      config.net.exponent             = 2;
      config.net.decay_secs           = fc::days(1).to_seconds();
      config.net.target_price         = asset::from_string("1000000.0000 TST");

      config.cpu.current_weight_ratio = rentbw_frac;
      config.cpu.target_weight_ratio  = rentbw_frac / 100;
      config.cpu.assumed_stake_weight = stake_weight;
      config.cpu.target_timestamp     = control->head_block_time() + fc::days(100);
      config.cpu.exponent             = 2;
      config.cpu.decay_secs           = fc::days(1).to_seconds();
      config.cpu.target_price         = asset::from_string("1000000.0000 TST");

      config.rent_days      = 30;
      config.min_rent_price = asset::from_string("1.0000 TST");

      f(config);
      return config;
   }

   rentbw_config make_config() {
      return make_config([](auto&) {});
   }

   template <typename F>
   rentbw_config make_default_config(F f) {
      rentbw_config config;
      f(config);
      return config;
   }

   action_result configbw(const rentbw_config& config) {
      return push_action(config::system_account_name, N(configrentbw), mvo()("args", config));
   }

   action_result rentbwexec(name user, uint16_t max) {
      return push_action(user, N(rentbwexec), mvo()("user", user)("max", max));
   }

   action_result rentbw(const name& payer, const name& receiver, uint32_t days, int64_t net_frac, int64_t cpu_frac,
                        const asset& max_payment) {
      return push_action(payer, N(rentbw),
                         mvo()("payer", payer)("receiver", receiver)("days", days)("net_frac", net_frac)(
                               "cpu_frac", cpu_frac)("max_payment", max_payment));
   }

   rentbw_state get_state() {
      vector<char> data = get_row_by_account(config::system_account_name, {}, N(rent.state), N(rent.state));
      return fc::raw::unpack<rentbw_state>(data);
   }

   struct account_info {
      int64_t ram = 0;
      int64_t net = 0;
      int64_t cpu = 0;
      asset   liquid;
   };

   account_info get_account_info(account_name acc) {
      account_info info;
      control->get_resource_limits_manager().get_account_limits(acc, info.ram, info.net, info.cpu);
      info.liquid = get_balance(acc);
      return info;
   };

   void check_rentbw(const name& payer, const name& receiver, uint32_t days, int64_t net_frac, int64_t cpu_frac,
                     const asset& expected_fee, int64_t expected_net, int64_t expected_cpu) {
      auto before_payer    = get_account_info(payer);
      auto before_receiver = get_account_info(receiver);
      auto before_reserve  = get_account_info(N(eosio.reserv));
      auto before_state    = get_state();
      BOOST_REQUIRE_EQUAL("", rentbw(payer, receiver, days, net_frac, cpu_frac, expected_fee));
      auto after_payer    = get_account_info(payer);
      auto after_receiver = get_account_info(receiver);
      auto after_reserve  = get_account_info(N(eosio.reserv));
      auto after_state    = get_state();

      if (false) {
         ilog("before_state.net.assumed_stake_weight:    ${x}", ("x", before_state.net.assumed_stake_weight));
         ilog("before_state.net.weight_ratio:            ${x}",
              ("x", before_state.net.weight_ratio / double(rentbw_frac)));
         ilog("before_state.net.assumed_stake_weight:    ${x}", ("x", before_state.net.assumed_stake_weight));
         ilog("before_state.net.weight:                  ${x}", ("x", before_state.net.weight));

         ilog("before_receiver.net:                      ${x}", ("x", before_receiver.net));
         ilog("after_receiver.net:                       ${x}", ("x", after_receiver.net));
         ilog("after_receiver.net - before_receiver.net: ${x}", ("x", after_receiver.net - before_receiver.net));
         ilog("expected_net:                             ${x}", ("x", expected_net));
         ilog("before_payer.liquid - after_payer.liquid: ${x}", ("x", before_payer.liquid - after_payer.liquid));
         ilog("expected_fee:                             ${x}", ("x", expected_fee));

         ilog("before_reserve.net:                       ${x}", ("x", before_reserve.net));
         ilog("after_reserve.net:                        ${x}", ("x", after_reserve.net));
         ilog("before_reserve.cpu:                       ${x}", ("x", before_reserve.cpu));
         ilog("after_reserve.cpu:                        ${x}", ("x", after_reserve.cpu));
      }

      if (payer != receiver) {
         BOOST_REQUIRE_EQUAL(before_payer.ram, after_payer.ram);
         BOOST_REQUIRE_EQUAL(before_payer.net, after_payer.net);
         BOOST_REQUIRE_EQUAL(before_payer.cpu, after_payer.cpu);
         BOOST_REQUIRE_EQUAL(before_receiver.liquid, after_receiver.liquid);
      }
      BOOST_REQUIRE_EQUAL(before_receiver.ram, after_receiver.ram);
      BOOST_REQUIRE_EQUAL(after_receiver.net - before_receiver.net, expected_net);
      BOOST_REQUIRE_EQUAL(after_receiver.cpu - before_receiver.cpu, expected_cpu);
      BOOST_REQUIRE_EQUAL(before_payer.liquid - after_payer.liquid, expected_fee);

      BOOST_REQUIRE_EQUAL(before_reserve.net - after_reserve.net, expected_net);
      BOOST_REQUIRE_EQUAL(before_reserve.cpu - after_reserve.cpu, expected_cpu);
      BOOST_REQUIRE_EQUAL(after_state.net.utilization - before_state.net.utilization, expected_net);
      BOOST_REQUIRE_EQUAL(after_state.cpu.utilization - before_state.cpu.utilization, expected_cpu);
   }
};

template <typename A, typename B, typename D>
bool near(A a, B b, D delta) {
   if (abs(a - b) <= delta)
      return true;
   elog("near: ${a} ${b}", ("a", a)("b", b));
   return false;
}

BOOST_AUTO_TEST_SUITE(eosio_system_rentbw_tests)

BOOST_FIXTURE_TEST_CASE(config_tests, rentbw_tester) try {
   BOOST_REQUIRE_EQUAL("missing authority of eosio",
                       push_action(N(alice1111111), N(configrentbw), mvo()("args", make_config())));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("rentbw hasn't been initialized"), rentbwexec(N(alice1111111), 10));

   //BOOST_REQUIRE_EQUAL(wasm_assert_msg("rent_days must be > 0"),
   //                    configbw(make_config([&](auto& c) { c.rent_days = 0; }))); // needed only if rent_days does not have default
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_rent_price doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.min_rent_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_rent_price must be positive"),
                       configbw(make_config([&](auto& c) { c.min_rent_price = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_rent_price must be positive"),
                       configbw(make_config([&](auto& c) { c.min_rent_price = asset::from_string("-1.0000 TST"); })));

   // net assertions
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("current_weight_ratio is too large"),
                       configbw(make_config([](auto& c) { c.net.current_weight_ratio = rentbw_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight/target_weight_ratio is too large"),
                       configbw(make_config([](auto& c) {
                          c.net.assumed_stake_weight = 100000;
                          c.net.target_weight_ratio  = 10;
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("weight can't grow over time"),
                       configbw(make_config([](auto& c) { c.net.target_weight_ratio = rentbw_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight must be at least 1; a much larger value is recommended"),
                       configbw(make_config([](auto& c) { c.net.assumed_stake_weight = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"),
                       configbw(make_config([&](auto& c) { c.net.target_timestamp = control->head_block_time(); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"), configbw(make_config([&](auto& c) {
                          c.net.target_timestamp = control->head_block_time() - fc::seconds(1);
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("exponent must be >= 1"),
                       configbw(make_config([&](auto& c) { c.net.exponent = .999; })));
   //BOOST_REQUIRE_EQUAL(wasm_assert_msg("decay_secs must be >= 1"),
   //                    configbw(make_config([&](auto& c) { c.net.decay_secs = 0; }))); // needed only if decay_secs does not have default
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.net.target_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price must be positive"),
                       configbw(make_config([&](auto& c) { c.net.target_price = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price must be positive"),
                       configbw(make_config([&](auto& c) { c.net.target_price = asset::from_string("-1.0000 TST"); })));

   // cpu assertions
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("current_weight_ratio is too large"),
                       configbw(make_config([](auto& c) { c.cpu.current_weight_ratio = rentbw_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight/target_weight_ratio is too large"),
                       configbw(make_config([](auto& c) {
                          c.cpu.assumed_stake_weight = 100000;
                          c.cpu.target_weight_ratio  = 10;
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("weight can't grow over time"),
                       configbw(make_config([](auto& c) { c.cpu.target_weight_ratio = rentbw_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight must be at least 1; a much larger value is recommended"),
                       configbw(make_config([](auto& c) { c.cpu.assumed_stake_weight = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"),
                       configbw(make_config([&](auto& c) { c.cpu.target_timestamp = control->head_block_time(); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"), configbw(make_config([&](auto& c) {
                          c.cpu.target_timestamp = control->head_block_time() - fc::seconds(1);
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("exponent must be >= 1"),
                       configbw(make_config([&](auto& c) { c.cpu.exponent = .999; })));
   //BOOST_REQUIRE_EQUAL(wasm_assert_msg("decay_secs must be >= 1"),
   //                    configbw(make_config([&](auto& c) { c.cpu.decay_secs = 0; }))); // needed only if decay_secs does not have default
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.cpu.target_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price must be positive"),
                       configbw(make_config([&](auto& c) { c.cpu.target_price = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price must be positive"),
                       configbw(make_config([&](auto& c) { c.cpu.target_price = asset::from_string("-1.0000 TST"); })));
} // config_tests
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(weight_tests, rentbw_tester) try {
   produce_block();

   auto net_start  = (rentbw_frac * 11) / 100;
   auto net_target = (rentbw_frac * 1) / 100;
   auto cpu_start  = (rentbw_frac * 11) / 1000;
   auto cpu_target = (rentbw_frac * 1) / 1000;

   BOOST_REQUIRE_EQUAL("", configbw(make_config([&](rentbw_config& config) {
                          config.net.current_weight_ratio = net_start;
                          config.net.target_weight_ratio  = net_target;
                          config.net.assumed_stake_weight = stake_weight;
                          config.net.target_timestamp     = control->head_block_time() + fc::days(10);

                          config.cpu.current_weight_ratio = cpu_start;
                          config.cpu.target_weight_ratio  = cpu_target;
                          config.cpu.assumed_stake_weight = stake_weight;
                          config.cpu.target_timestamp     = control->head_block_time() + fc::days(20);
                       })));

   int64_t net;
   int64_t cpu;

   auto check_weight = [&] {
      auto state = get_state();
      BOOST_REQUIRE(near(           //
            state.net.weight_ratio, //
            int64_t(state.net.assumed_stake_weight * eosio::chain::int128_t(rentbw_frac) /
                    (state.net.weight + state.net.assumed_stake_weight)),
            10));
   };

   for (int i = 0; i <= 6; ++i) {
      if (i == 2) {
         // Leaves config as-is, but may introduce slight rounding
         produce_block(fc::days(1) - fc::milliseconds(500));
         BOOST_REQUIRE_EQUAL("", configbw({}));
      } else if (i) {
         produce_block(fc::days(1) - fc::milliseconds(500));
         BOOST_REQUIRE_EQUAL("", rentbwexec(config::system_account_name, 10));
      }
      net = net_start + i * (net_target - net_start) / 10;
      cpu = cpu_start + i * (cpu_target - cpu_start) / 20;
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu, 1));
      check_weight();
   }

   // Extend transition time
   {
      int i = 7;
      produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](rentbw_config& config) {
                             config.net.target_timestamp = control->head_block_time() + fc::days(30);
                             config.cpu.target_timestamp = control->head_block_time() + fc::days(40);
                          })));
      net_start = net = net_start + i * (net_target - net_start) / 10;
      cpu_start = cpu = cpu_start + i * (cpu_target - cpu_start) / 20;
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu, 1));
      check_weight();
   }

   for (int i = 0; i <= 5; ++i) {
      if (i) {
         produce_block(fc::days(1) - fc::milliseconds(500));
         BOOST_REQUIRE_EQUAL("", rentbwexec(config::system_account_name, 10));
      }
      net = net_start + i * (net_target - net_start) / 30;
      cpu = cpu_start + i * (cpu_target - cpu_start) / 40;
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu, 1));
      check_weight();
   }

   // Change target, keep existing transition time
   {
      int i = 6;
      produce_block(fc::days(1) - fc::milliseconds(500));
      auto new_net_target = net_target / 10;
      auto new_cpu_target = cpu_target / 20;
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](rentbw_config& config) {
                             config.net.target_weight_ratio = new_net_target;
                             config.cpu.target_weight_ratio = new_cpu_target;
                          })));
      net_start = net = net_start + i * (net_target - net_start) / 30;
      cpu_start = cpu = cpu_start + i * (cpu_target - cpu_start) / 40;
      net_target      = new_net_target;
      cpu_target      = new_cpu_target;
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu, 1));
      check_weight();
   }

   for (int i = 0; i <= 10; ++i) {
      if (i) {
         produce_block(fc::days(1) - fc::milliseconds(500));
         BOOST_REQUIRE_EQUAL("", rentbwexec(config::system_account_name, 10));
      }
      net = net_start + i * (net_target - net_start) / (30 - 6);
      cpu = cpu_start + i * (cpu_target - cpu_start) / (40 - 6);
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu, 1));
      check_weight();
   }

   // Move transition time to immediate future
   {
      produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](rentbw_config& config) {
                             config.net.target_timestamp = control->head_block_time() + fc::milliseconds(1000);
                             config.cpu.target_timestamp = control->head_block_time() + fc::milliseconds(1000);
                          })));
      produce_blocks(2);
   }

   // Verify targets hold as time advances
   for (int i = 0; i <= 10; ++i) {
      BOOST_REQUIRE_EQUAL("", rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net_target, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu_target, 1));
      check_weight();
      produce_block(fc::days(1));
   }
} // weight_tests
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_CASE(rent_tests) try {
   {
      rentbw_tester t;
      t.produce_block();

      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("rentbw hasn't been initialized"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac / 4, rentbw_frac / 8,
                                   asset::from_string("1.000 TST")));

      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_config([&](auto& config) {
         config.net.current_weight_ratio = rentbw_frac;
         config.net.target_weight_ratio  = rentbw_frac;
         config.net.assumed_stake_weight = stake_weight;
         config.net.exponent             = 1;
         config.net.target_price         = asset::from_string("1000000.0000 TST");

         config.cpu.current_weight_ratio = rentbw_frac;
         config.cpu.target_weight_ratio  = rentbw_frac;
         config.cpu.assumed_stake_weight = stake_weight;
         config.cpu.exponent             = 1;
         config.cpu.target_price         = asset::from_string("1000000.0000 TST");

         config.rent_days      = 30;
         config.min_rent_price = asset::from_string("1.0000 TST");
      })));

      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("max_payment doesn't match core symbol"), //
            t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac, rentbw_frac, asset::from_string("1.000 TST")));
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("market doesn't have resources available"), //
            t.rentbw(N(bob111111111), N(alice1111111), 30, 0, rentbw_frac, asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("market doesn't have resources available"), //
            t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac, 0, asset::from_string("1.0000 TST")));
   }

   auto init = [](auto& t, bool rex) {
      t.produce_block();
      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_config([&](auto& config) {
         // weight = stake_weight * 3
         config.net.current_weight_ratio = rentbw_frac / 4;
         config.net.target_weight_ratio  = rentbw_frac / 4;
         config.net.assumed_stake_weight = stake_weight;
         config.net.exponent             = 2;
         config.net.target_price         = asset::from_string("1000000.0000 TST");

         // weight = stake_weight * 4 / 2
         config.cpu.current_weight_ratio = rentbw_frac / 5;
         config.cpu.target_weight_ratio  = rentbw_frac / 5;
         config.cpu.assumed_stake_weight = stake_weight / 2;
         config.cpu.exponent             = 3;
         config.cpu.target_price         = asset::from_string("2000000.0000 TST");

         config.rent_days      = 30;
         config.min_rent_price = asset::from_string("1.0000 TST");
      })));

      if (rex)
         t.start_rex();

      t.create_account_with_resources(N(aaaaaaaaaaaa), config::system_account_name, core_sym::from_string("1.0000"),
                                      false, core_sym::from_string("500.0000"), core_sym::from_string("500.0000"));
      t.create_account_with_resources(N(bbbbbbbbbbbb), config::system_account_name, core_sym::from_string("1.0000"),
                                      false, core_sym::from_string("500.0000"), core_sym::from_string("500.0000"));
   };
   auto net_weight = stake_weight * 3;
   auto cpu_weight = stake_weight * 4 / 2;

   {
      rentbw_tester t;
      init(t, false);
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("days doesn't match configuration"), //
            t.rentbw(N(bob111111111), N(alice1111111), 20, rentbw_frac, rentbw_frac, asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                   //
            t.wasm_assert_msg("net_frac can't be negative"), //
            t.rentbw(N(bob111111111), N(alice1111111), 30, -rentbw_frac, rentbw_frac,
                     asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                   //
            t.wasm_assert_msg("cpu_frac can't be negative"), //
            t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac, -rentbw_frac,
                     asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                    //
            t.wasm_assert_msg("net can't be more than 100%"), //
            t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac + 1, rentbw_frac,
                     asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                    //
            t.wasm_assert_msg("cpu can't be more than 100%"), //
            t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac, rentbw_frac + 1,
                     asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("max_payment is less than calculated fee: 3000000.0000 TST"), //
            t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac, rentbw_frac, asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("can't channel fees to rex"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac, rentbw_frac,
                                   asset::from_string("3000000.0000 TST")));
   }

   // net:100%, cpu:100%
   {
      rentbw_tester t;
      init(t, true);
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("3000000.0000"));
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("calculated fee is below minimum; try renting more"),
            t.rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, 10, 10, asset::from_string("3000000.0000 TST")));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac, rentbw_frac,
                     asset::from_string("3000000.0000 TST"), net_weight, cpu_weight);

      BOOST_REQUIRE_EQUAL( //
            t.wasm_assert_msg("weight can't shrink below utilization"),
            t.configbw(t.make_default_config([&](auto& config) {
               config.net.current_weight_ratio = rentbw_frac / 4 + 1;
               config.net.target_weight_ratio  = rentbw_frac / 4 + 1;
               config.cpu.current_weight_ratio = rentbw_frac / 5;
               config.cpu.target_weight_ratio  = rentbw_frac / 5;
            })));
      BOOST_REQUIRE_EQUAL( //
            t.wasm_assert_msg("weight can't shrink below utilization"),
            t.configbw(t.make_default_config([&](auto& config) {
               config.net.current_weight_ratio = rentbw_frac / 4;
               config.net.target_weight_ratio  = rentbw_frac / 4;
               config.cpu.current_weight_ratio = rentbw_frac / 5 + 1;
               config.cpu.target_weight_ratio  = rentbw_frac / 5 + 1;
            })));
      BOOST_REQUIRE_EQUAL( //
            "",            //
            t.configbw(t.make_default_config([&](auto& config) {
               config.net.current_weight_ratio = rentbw_frac / 4;
               config.net.target_weight_ratio  = rentbw_frac / 4;
               config.cpu.current_weight_ratio = rentbw_frac / 5;
               config.cpu.target_weight_ratio  = rentbw_frac / 5;
            })));
   }

   // net:30%, cpu:40%, then net:5%, cpu:10%
   {
      rentbw_tester t;
      init(t, true);
      // (.3 ^ 2) * 1000000.0000 =  90000.0000
      // (.4 ^ 3) * 2000000.0000 = 128000.0000
      //                   total = 218000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("218000.0001"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .3, rentbw_frac * .4,
                     asset::from_string("218000.0001 TST"), net_weight * .3, cpu_weight * .4);

      // (.35 ^ 2) * 1000000.0000 -  90000.0000 =  32500.0000
      // (.5  ^ 3) * 2000000.0000 - 128000.0000 = 122000.0000
      //                                  total = 154500.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("154500.0000"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .05, rentbw_frac * .10,
                     asset::from_string("154500.0000 TST"), net_weight * .05, cpu_weight * .10);
   }

   {
      // net:100%, cpu:100%
      rentbw_tester t;
      init(t, true);
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("3000000.0000"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac, rentbw_frac,
                     asset::from_string("3000000.0000 TST"), net_weight, cpu_weight);

      // No more available for 30 days
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac / 1000, rentbw_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::days(29));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac / 1000, rentbw_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::days(1) - fc::milliseconds(1500));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac / 1000, rentbw_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::milliseconds(500));

      // immediate renewal: adjusted_utilization doesn't have time to fall
      //
      // (2.0 ^ 2) * 1000000.0000 - 1000000.0000 =  3000000.0000
      // (2.0 ^ 3) * 2000000.0000 - 2000000.0000 = 14000000.0000
      //                                   total = 17000000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("17000000.0000"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac, rentbw_frac,
                     asset::from_string("17000000.0000 TST"), 0, 0);

      // No more available for 30 days
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac / 1000, rentbw_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::days(29));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac / 1000, rentbw_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::days(1) - fc::milliseconds(1000));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac / 1000, rentbw_frac / 1000,
                                   asset::from_string("1.0000 TST")));

      // Start decay
      t.produce_block(fc::milliseconds(1000));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, net_weight, net_weight / 1000));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, cpu_weight, cpu_weight / 1000));

      // 1 day of decay
      t.produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, int64_t(net_weight * exp(-1)),
                         int64_t(net_weight * exp(-1)) / 1000));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, int64_t(cpu_weight * exp(-1)),
                         int64_t(cpu_weight * exp(-1)) / 1000));

      // 1 day of decay
      t.produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, int64_t(net_weight * exp(-2)),
                         int64_t(net_weight * exp(-2)) / 1000));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, int64_t(cpu_weight * exp(-2)),
                         int64_t(cpu_weight * exp(-2)) / 1000));

      // 100% after 2 days of decay
      //
      // [((e^-2 + 1.0) ^ 2) - ((e^-2) ^ 2) ] * 1000000.0000 = 1270670.5664
      // [((e^-2 + 1.0) ^ 3) - ((e^-2) ^ 3) ] * 2000000.0000 = 2921905.5327
      //                                               total = 4192576.0991
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("4192561.0246"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac, rentbw_frac,
                     asset::from_string("4192561.0246 TST"), net_weight, cpu_weight);
   }

   {
      rentbw_tester t;
      init(t, true);

      // 10%, 20%
      // (.1 ^ 2) * 1000000.0000 = 10000.0000
      // (.2 ^ 3) * 2000000.0000 = 16000.0000
      //                   total = 26000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("26000.0002"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .1, rentbw_frac * .2,
                     asset::from_string("26000.0002 TST"), net_weight * .1, cpu_weight * .2);

      t.produce_block(fc::days(15) - fc::milliseconds(500));

      // 20%, 20%
      // (.3 ^ 2) * 1000000.0000 - 10000.0000 =  80000.0000
      // (.4 ^ 3) * 2000000.0000 - 16000.0000 = 112000.0000
      //                                total = 192000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("192000.0001"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .2, rentbw_frac * .2,
                     asset::from_string("192000.0001 TST"), net_weight * .2, cpu_weight * .2);

      // Start decay
      t.produce_block(fc::days(15) - fc::milliseconds(1000));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, .3 * net_weight, 0));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, .4 * cpu_weight, 0));

      // 1 day of decay from (30%, 40%) to (20%, 20%)
      t.produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(
            near(t.get_state().net.adjusted_utilization, int64_t(.1 * net_weight * exp(-1) + .2 * net_weight), 0));
      BOOST_REQUIRE(
            near(t.get_state().cpu.adjusted_utilization, int64_t(.2 * cpu_weight * exp(-1) + .2 * cpu_weight), 0));

      // 2 days of decay from (30%, 40%) to (20%, 20%)
      t.produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(
            near(t.get_state().net.adjusted_utilization, int64_t(.1 * net_weight * exp(-2) + .2 * net_weight), 0));
      BOOST_REQUIRE(
            near(t.get_state().cpu.adjusted_utilization, int64_t(.2 * cpu_weight * exp(-2) + .2 * cpu_weight), 0));
   }

} // rent_tests
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
