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

inline constexpr int64_t powerup_frac  = 1'000'000'000'000'000ll; // 1.0 = 10^15
inline constexpr int64_t stake_weight = 100'000'000'0000ll; // 10^12

struct powerup_config_resource {
   fc::optional<int64_t>        current_weight_ratio = {};
   fc::optional<int64_t>        target_weight_ratio  = {};
   fc::optional<int64_t>        assumed_stake_weight = {};
   fc::optional<time_point_sec> target_timestamp     = {};
   fc::optional<double>         exponent             = {};
   fc::optional<uint32_t>       decay_secs           = {};
   fc::optional<asset>          min_price            = {};
   fc::optional<asset>          max_price            = {};
};
FC_REFLECT(powerup_config_resource,                                                             //
           (current_weight_ratio)(target_weight_ratio)(assumed_stake_weight)(target_timestamp) //
           (exponent)(decay_secs)(min_price)(max_price))

struct powerup_config {
   powerup_config_resource net          = {};
   powerup_config_resource cpu          = {};
   fc::optional<uint32_t> powerup_days    = {};
   fc::optional<asset>    min_powerup_fee = {};
};
FC_REFLECT(powerup_config, (net)(cpu)(powerup_days)(min_powerup_fee))

struct powerup_state_resource {
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
   asset          min_price;
   asset          max_price;
   int64_t        utilization;
   int64_t        adjusted_utilization;
   time_point_sec utilization_timestamp;
};
FC_REFLECT(powerup_state_resource,                                                                           //
           (version)(weight)(weight_ratio)(assumed_stake_weight)(initial_weight_ratio)(target_weight_ratio) //
           (initial_timestamp)(target_timestamp)(exponent)(decay_secs)(min_price)(max_price)(utilization)   //
           (adjusted_utilization)(utilization_timestamp))

struct powerup_state {
   uint8_t               version;
   powerup_state_resource net;
   powerup_state_resource cpu;
   uint32_t              powerup_days;
   asset                 min_powerup_fee;
};
FC_REFLECT(powerup_state, (version)(net)(cpu)(powerup_days)(min_powerup_fee))

using namespace eosio_system;

struct powerup_tester : eosio_system_tester {

   powerup_tester() { create_accounts_with_resources({ N(eosio.reserv) }); }

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
   powerup_config make_config(F f) {
      powerup_config config;

      config.net.current_weight_ratio = powerup_frac;
      config.net.target_weight_ratio  = powerup_frac / 100;
      config.net.assumed_stake_weight = stake_weight;
      config.net.target_timestamp     = control->head_block_time() + fc::days(100);
      config.net.exponent             = 2;
      config.net.decay_secs           = fc::days(1).to_seconds();
      config.net.min_price            = asset::from_string("0.0000 TST");
      config.net.max_price            = asset::from_string("1000000.0000 TST");

      config.cpu.current_weight_ratio = powerup_frac;
      config.cpu.target_weight_ratio  = powerup_frac / 100;
      config.cpu.assumed_stake_weight = stake_weight;
      config.cpu.target_timestamp     = control->head_block_time() + fc::days(100);
      config.cpu.exponent             = 2;
      config.cpu.decay_secs           = fc::days(1).to_seconds();
      config.cpu.min_price            = asset::from_string("0.0000 TST");
      config.cpu.max_price            = asset::from_string("1000000.0000 TST");

      config.powerup_days    = 30;
      config.min_powerup_fee = asset::from_string("1.0000 TST");

      f(config);
      return config;
   }

   powerup_config make_config() {
      return make_config([](auto&) {});
   }

   template <typename F>
   powerup_config make_default_config(F f) {
      powerup_config config;
      f(config);
      return config;
   }

   action_result configbw(const powerup_config& config) {
      // Verbose solution needed to work around bug in abi_serializer that fails if optional values aren't explicitly
      // specified with a null value.

      auto optional_to_variant = []( const auto& v ) -> fc::variant {
         return (!v ? fc::variant() : fc::variant(*v));
      };

      auto resource_conf_vo = [&optional_to_variant](const powerup_config_resource& c ) {
         return   mvo("current_weight_ratio", optional_to_variant(c.current_weight_ratio))
                     ("target_weight_ratio",  optional_to_variant(c.target_weight_ratio))
                     ("assumed_stake_weight", optional_to_variant(c.assumed_stake_weight))
                     ("target_timestamp",     optional_to_variant(c.target_timestamp))
                     ("exponent",             optional_to_variant(c.exponent))
                     ("decay_secs",           optional_to_variant(c.decay_secs))
                     ("min_price",            optional_to_variant(c.min_price))
                     ("max_price",            optional_to_variant(c.max_price))
         ;
      };

      auto conf = mvo("net",          resource_conf_vo(config.net))
                     ("cpu",          resource_conf_vo(config.cpu))
                     ("powerup_days",    optional_to_variant(config.powerup_days))
                     ("min_powerup_fee", optional_to_variant(config.min_powerup_fee))
      ;

      //idump((fc::json::to_pretty_string(conf)));
      return push_action(config::system_account_name, N(cfgpowerup), mvo()("args", std::move(conf)));

      // If abi_serializer worked correctly, the following is all that would be needed:
      //return push_action(config::system_account_name, N(cfgpowerup), mvo()("args", config));
   }

   action_result powerupexec(name user, uint16_t max) {
      return push_action(user, N(powerupexec), mvo()("user", user)("max", max));
   }

   action_result powerup(const name& payer, const name& receiver, uint32_t days, int64_t net_frac, int64_t cpu_frac,
                        const asset& max_payment) {
      return push_action(payer, N(powerup),
                         mvo()("payer", payer)("receiver", receiver)("days", days)("net_frac", net_frac)(
                               "cpu_frac", cpu_frac)("max_payment", max_payment));
   }

   powerup_state get_state() {
      vector<char> data = get_row_by_account(config::system_account_name, {}, N(powup.state), N(powup.state));
      return fc::raw::unpack<powerup_state>(data);
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

   void check_powerup(const name& payer, const name& receiver, uint32_t days, int64_t net_frac, int64_t cpu_frac,
                     const asset& expected_fee, int64_t expected_net, int64_t expected_cpu) {
      auto before_payer    = get_account_info(payer);
      auto before_receiver = get_account_info(receiver);
      auto before_reserve  = get_account_info(N(eosio.reserv));
      auto before_state    = get_state();
      BOOST_REQUIRE_EQUAL("", powerup(payer, receiver, days, net_frac, cpu_frac, expected_fee));
      auto after_payer    = get_account_info(payer);
      auto after_receiver = get_account_info(receiver);
      auto after_reserve  = get_account_info(N(eosio.reserv));
      auto after_state    = get_state();

      if (false) {
         ilog("before_state.net.assumed_stake_weight:    ${x}", ("x", before_state.net.assumed_stake_weight));
         ilog("before_state.net.weight_ratio:            ${x}",
              ("x", before_state.net.weight_ratio / double(powerup_frac)));
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

BOOST_AUTO_TEST_SUITE(eosio_system_powerup_tests)

BOOST_FIXTURE_TEST_CASE(config_tests, powerup_tester) try {
   BOOST_REQUIRE_EQUAL("missing authority of eosio",
                       push_action(N(alice1111111), N(cfgpowerup), mvo()("args", make_config())));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("powerup hasn't been initialized"), powerupexec(N(alice1111111), 10));

   BOOST_REQUIRE_EQUAL(wasm_assert_msg("powerup_days must be > 0"),
                       configbw(make_config([&](auto& c) { c.powerup_days = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_powerup_fee doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.min_powerup_fee = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_powerup_fee does not have a default value"),
                       configbw(make_config([&](auto& c) { c.min_powerup_fee = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_powerup_fee must be positive"),
                       configbw(make_config([&](auto& c) { c.min_powerup_fee = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_powerup_fee must be positive"),
                       configbw(make_config([&](auto& c) { c.min_powerup_fee = asset::from_string("-1.0000 TST"); })));

   // net assertions
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("current_weight_ratio is too large"),
                       configbw(make_config([](auto& c) { c.net.current_weight_ratio = powerup_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight/target_weight_ratio is too large"),
                       configbw(make_config([](auto& c) {
                          c.net.assumed_stake_weight = 100000;
                          c.net.target_weight_ratio  = 10;
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("weight can't grow over time"),
                       configbw(make_config([](auto& c) { c.net.target_weight_ratio = powerup_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight does not have a default value"),
                       configbw(make_config([](auto& c) { c.net.assumed_stake_weight = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight must be at least 1; a much larger value is recommended"),
                       configbw(make_config([](auto& c) { c.net.assumed_stake_weight = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp does not have a default value"),
                       configbw(make_config([&](auto& c) { c.net.target_timestamp = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"),
                       configbw(make_config([&](auto& c) { c.net.target_timestamp = control->head_block_time(); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"), configbw(make_config([&](auto& c) {
                          c.net.target_timestamp = control->head_block_time() - fc::seconds(1);
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("exponent must be >= 1"),
                       configbw(make_config([&](auto& c) { c.net.exponent = .999; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("decay_secs must be >= 1"),
                       configbw(make_config([&](auto& c) { c.net.decay_secs = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price does not have a default value"),
                       configbw(make_config([&](auto& c) { c.net.max_price = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.net.max_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price must be positive"),
                       configbw(make_config([&](auto& c) { c.net.max_price = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price must be positive"),
                       configbw(make_config([&](auto& c) { c.net.max_price = asset::from_string("-1.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.net.min_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price must be non-negative"),
                       configbw(make_config([&](auto& c) { c.net.min_price = asset::from_string("-1.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price cannot exceed max_price"),
                       configbw(make_config([&](auto& c) {
                          c.net.min_price = asset::from_string("3.0000 TST");
                          c.net.max_price = asset::from_string("2.0000 TST");
                       })));

   // cpu assertions
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("current_weight_ratio is too large"),
                       configbw(make_config([](auto& c) { c.cpu.current_weight_ratio = powerup_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight/target_weight_ratio is too large"),
                       configbw(make_config([](auto& c) {
                          c.cpu.assumed_stake_weight = 100000;
                          c.cpu.target_weight_ratio  = 10;
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("weight can't grow over time"),
                       configbw(make_config([](auto& c) { c.cpu.target_weight_ratio = powerup_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight does not have a default value"),
                       configbw(make_config([](auto& c) { c.cpu.assumed_stake_weight = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight must be at least 1; a much larger value is recommended"),
                       configbw(make_config([](auto& c) { c.cpu.assumed_stake_weight = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp does not have a default value"),
                       configbw(make_config([&](auto& c) { c.cpu.target_timestamp = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"),
                       configbw(make_config([&](auto& c) { c.cpu.target_timestamp = control->head_block_time(); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"), configbw(make_config([&](auto& c) {
                          c.cpu.target_timestamp = control->head_block_time() - fc::seconds(1);
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("exponent must be >= 1"),
                       configbw(make_config([&](auto& c) { c.cpu.exponent = .999; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("decay_secs must be >= 1"),
                       configbw(make_config([&](auto& c) { c.cpu.decay_secs = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price does not have a default value"),
                       configbw(make_config([&](auto& c) { c.cpu.max_price = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.cpu.max_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price must be positive"),
                       configbw(make_config([&](auto& c) { c.cpu.max_price = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price must be positive"),
                       configbw(make_config([&](auto& c) { c.cpu.max_price = asset::from_string("-1.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.cpu.min_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price must be non-negative"),
                       configbw(make_config([&](auto& c) { c.cpu.min_price = asset::from_string("-1.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price cannot exceed max_price"),
                       configbw(make_config([&](auto& c) {
                          c.cpu.min_price = asset::from_string("3.0000 TST");
                          c.cpu.max_price = asset::from_string("2.0000 TST");
                       })));
} // config_tests
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(weight_tests, powerup_tester) try {
   produce_block();

   auto net_start  = (powerup_frac * 11) / 100;
   auto net_target = (powerup_frac * 1) / 100;
   auto cpu_start  = (powerup_frac * 11) / 1000;
   auto cpu_target = (powerup_frac * 1) / 1000;

   BOOST_REQUIRE_EQUAL("", configbw(make_config([&](powerup_config& config) {
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
            int64_t(state.net.assumed_stake_weight * eosio::chain::int128_t(powerup_frac) /
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
         BOOST_REQUIRE_EQUAL("", powerupexec(config::system_account_name, 10));
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
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](powerup_config& config) {
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
         BOOST_REQUIRE_EQUAL("", powerupexec(config::system_account_name, 10));
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
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](powerup_config& config) {
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
         BOOST_REQUIRE_EQUAL("", powerupexec(config::system_account_name, 10));
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
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](powerup_config& config) {
                             config.net.target_timestamp = control->head_block_time() + fc::milliseconds(1000);
                             config.cpu.target_timestamp = control->head_block_time() + fc::milliseconds(1000);
                          })));
      produce_blocks(2);
   }

   // Verify targets hold as time advances
   for (int i = 0; i <= 10; ++i) {
      BOOST_REQUIRE_EQUAL("", powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net_target, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu_target, 1));
      check_weight();
      produce_block(fc::days(1));
   }
} // weight_tests
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_CASE(rent_tests) try {
   {
      powerup_tester t;
      t.produce_block();

      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("powerup hasn't been initialized"), //
                          t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac / 4, powerup_frac / 8,
                                   asset::from_string("1.000 TST")));

      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_config([&](auto& config) {
         config.net.current_weight_ratio = powerup_frac;
         config.net.target_weight_ratio  = powerup_frac;
         config.net.assumed_stake_weight = stake_weight;
         config.net.exponent             = 1;
         config.net.min_price            = asset::from_string("1000000.0000 TST");
         config.net.max_price            = asset::from_string("1000000.0000 TST");

         config.cpu.current_weight_ratio = powerup_frac;
         config.cpu.target_weight_ratio  = powerup_frac;
         config.cpu.assumed_stake_weight = stake_weight;
         config.cpu.exponent             = 1;
         config.cpu.min_price            = asset::from_string("1000000.0000 TST");
         config.cpu.max_price            = asset::from_string("1000000.0000 TST");

         config.powerup_days    = 30;
         config.min_powerup_fee = asset::from_string("1.0000 TST");
      })));

      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("max_payment doesn't match core symbol"), //
            t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac, powerup_frac, asset::from_string("1.000 TST")));
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("market doesn't have resources available"), //
            t.powerup(N(bob111111111), N(alice1111111), 30, 0, powerup_frac, asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("market doesn't have resources available"), //
            t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac, 0, asset::from_string("1.0000 TST")));

      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_default_config([&](auto& config) {
         // weight = stake_weight
         config.net.current_weight_ratio = powerup_frac/2;
         config.net.target_weight_ratio  = powerup_frac/2;

         // weight = stake_weight
         config.cpu.current_weight_ratio = powerup_frac/2;
         config.cpu.target_weight_ratio  = powerup_frac/2;
      })));

      auto net_weight = stake_weight;
      auto cpu_weight = stake_weight;

      t.start_rex();
      t.create_account_with_resources(N(aaaaaaaaaaaa), config::system_account_name, core_sym::from_string("1.0000"),
                                      false, core_sym::from_string("500.0000"), core_sym::from_string("500.0000"));

      // 10%, 20%
      // (.1) * 1000000.0000 = 100000.0000
      // (.2) * 1000000.0000 = 200000.0000
      //               total = 300000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("300000.0000"));
      t.check_powerup(N(aaaaaaaaaaaa), N(aaaaaaaaaaaa), 30, powerup_frac * .1, powerup_frac * .2,
                     asset::from_string("300000.0000 TST"), net_weight * .1, cpu_weight * .2);

      // Start decay
      t.produce_block(fc::days(30) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, .1 * net_weight, 0));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, .2 * cpu_weight, 0));

      // 2 days of decay from (10%, 20%) to (1.35%, 2.71%)
      t.produce_block(fc::days(2) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, int64_t(.1 * net_weight * exp(-2)),
                         int64_t(.1 * net_weight * exp(-2)) / 1000));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, int64_t(.2 * cpu_weight * exp(-2)),
                         int64_t(.2 * cpu_weight * exp(-2)) / 1000));

      // 2%, 2%
      // (0.0135 + 0.02 - 0.0135) * 1000000.0000 = 20000.0000
      // (.02) * 1000000.0000                    = 20000.0000
      //                                   total = 40000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("40000.0001"));
      t.check_powerup(N(aaaaaaaaaaaa), N(aaaaaaaaaaaa), 30, powerup_frac * .02, powerup_frac * .02,
                     asset::from_string("40000.0001 TST"), net_weight * .02, cpu_weight * .02);
   }

   auto init = [](auto& t, bool rex) {
      t.produce_block();
      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_config([&](auto& config) {
         // weight = stake_weight * 3
         config.net.current_weight_ratio = powerup_frac / 4;
         config.net.target_weight_ratio  = powerup_frac / 4;
         config.net.assumed_stake_weight = stake_weight;
         config.net.exponent             = 2;
         config.net.max_price            = asset::from_string("2000000.0000 TST");

         // weight = stake_weight * 4 / 2
         config.cpu.current_weight_ratio = powerup_frac / 5;
         config.cpu.target_weight_ratio  = powerup_frac / 5;
         config.cpu.assumed_stake_weight = stake_weight / 2;
         config.cpu.exponent             = 3;
         config.cpu.max_price            = asset::from_string("6000000.0000 TST");

         config.powerup_days    = 30;
         config.min_powerup_fee = asset::from_string("1.0000 TST");
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
      powerup_tester t;
      init(t, false);
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("days doesn't match configuration"), //
            t.powerup(N(bob111111111), N(alice1111111), 20, powerup_frac, powerup_frac, asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                   //
            t.wasm_assert_msg("net_frac can't be negative"), //
            t.powerup(N(bob111111111), N(alice1111111), 30, -powerup_frac, powerup_frac,
                     asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                   //
            t.wasm_assert_msg("cpu_frac can't be negative"), //
            t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac, -powerup_frac,
                     asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                    //
            t.wasm_assert_msg("net can't be more than 100%"), //
            t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac + 1, powerup_frac,
                     asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                    //
            t.wasm_assert_msg("cpu can't be more than 100%"), //
            t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac, powerup_frac + 1,
                     asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("max_payment is less than calculated fee: 3000000.0000 TST"), //
            t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac, powerup_frac, asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("can't channel fees to rex"), //
                          t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac, powerup_frac,
                                   asset::from_string("3000000.0000 TST")));
   }

   // net:100%, cpu:100%
   {
      powerup_tester t;
      init(t, true);
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("3000000.0000"));
      BOOST_REQUIRE_EQUAL(
            t.wasm_assert_msg("calculated fee is below minimum; try renting more"),
            t.powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, 10, 10, asset::from_string("3000000.0000 TST")));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac, powerup_frac,
                     asset::from_string("3000000.0000 TST"), net_weight, cpu_weight);

      BOOST_REQUIRE_EQUAL( //
            t.wasm_assert_msg("weight can't shrink below utilization"),
            t.configbw(t.make_default_config([&](auto& config) {
               config.net.current_weight_ratio = powerup_frac / 4 + 1;
               config.net.target_weight_ratio  = powerup_frac / 4 + 1;
               config.cpu.current_weight_ratio = powerup_frac / 5;
               config.cpu.target_weight_ratio  = powerup_frac / 5;
            })));
      BOOST_REQUIRE_EQUAL( //
            t.wasm_assert_msg("weight can't shrink below utilization"),
            t.configbw(t.make_default_config([&](auto& config) {
               config.net.current_weight_ratio = powerup_frac / 4;
               config.net.target_weight_ratio  = powerup_frac / 4;
               config.cpu.current_weight_ratio = powerup_frac / 5 + 1;
               config.cpu.target_weight_ratio  = powerup_frac / 5 + 1;
            })));
      BOOST_REQUIRE_EQUAL( //
            "",            //
            t.configbw(t.make_default_config([&](auto& config) {
               config.net.current_weight_ratio = powerup_frac / 4;
               config.net.target_weight_ratio  = powerup_frac / 4;
               config.cpu.current_weight_ratio = powerup_frac / 5;
               config.cpu.target_weight_ratio  = powerup_frac / 5;
            })));
   }

   // net:30%, cpu:40%, then net:5%, cpu:10%
   {
      powerup_tester t;
      init(t, true);
      // (.3 ^ 2) * 2000000.0000 / 2 =  90000.0000
      // (.4 ^ 3) * 6000000.0000 / 3 = 128000.0000
      //                       total = 218000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("218000.0001"));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac * .3, powerup_frac * .4,
                     asset::from_string("218000.0001 TST"), net_weight * .3, cpu_weight * .4);

      // (.35 ^ 2) * 2000000.0000 / 2 -  90000.0000 =  32500.0000
      // (.5  ^ 3) * 6000000.0000 / 3 - 128000.0000 = 122000.0000
      //                                      total = 154500.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("154500.0000"));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac * .05, powerup_frac * .10,
                     asset::from_string("154500.0000 TST"), net_weight * .05, cpu_weight * .10);
   }

   // net:50%, cpu:50% (but with non-zero min_price and also an exponent of 2 to simplify the math)
   {
      powerup_tester t;
      init(t, true);
      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_default_config([&](auto& config) {
         config.cpu.exponent             = 2;
         config.net.min_price            = asset::from_string("1200000.0000 TST");
         config.net.max_price            = asset::from_string("2000000.0000 TST");

         config.cpu.exponent             = 2;
         config.cpu.min_price            = asset::from_string("4000000.0000 TST");
         config.cpu.max_price            = asset::from_string("6000000.0000 TST");
      })));

      // At 0% utilization for both NET and CPU, the cost (in TST) for renting an infinitesimal amount of resources (dr) is
      //    1200000.0000 * dr for NET and 4000000.0000 * dr for CPU.
      // At 50% utilization for both NET and CPU, the cost (in TST for renting an infinitesimal amount of resources (dr) is
      //    1600000.0000 * dr for NET and 5000000.0000 * dr for CPU.

      // The fee for renting 50% of NET (starting from 0% utilization) is expected to be somewhere between
      //    1200000.0000 * 0.5 (= 600000.0000) and 1600000.0000 * 0.5 (= 800000.0000).
      //    In fact, the cost ends up being 700000.0000.

      // The fee for renting 50% of CPU (starting from 0% utilization) is expected to be somewhere between
      //    4000000.0000 * 0.5 (= 2000000.0000) and 5000000.0000 * 0.5 (= 2500000.0000).
      //    In fact, the cost ends up being 2250000.0000.


      // 1200000.0000 * .5 +  (800000.0000 / 2) * (.5 ^ 2) =  700000.0000
      // 4000000.0000 * .5 + (2000000.0000 / 2) * (.5 ^ 2) = 2250000.0000
      //                                             total = 2950000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("2950000.0000"));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac * .5, powerup_frac * .5,
                     asset::from_string("2950000.0000 TST"), net_weight * .5, cpu_weight * .5);
   }

   {
      // net:100%, cpu:100%
      powerup_tester t;
      init(t, true);
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("3000000.0000"));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac, powerup_frac,
                     asset::from_string("3000000.0000 TST"), net_weight, cpu_weight);

      // No more available for 30 days
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac / 1000, powerup_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::days(29));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac / 1000, powerup_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::days(1) - fc::milliseconds(1500));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac / 1000, powerup_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::milliseconds(500));

      // immediate renewal: adjusted_utilization doesn't have time to fall
      //
      // (1.0 ^ 1) * 2000000.0000 = 2000000.0000
      // (1.0 ^ 2) * 6000000.0000 = 6000000.0000
      //                    total = 8000000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("8000000.0000"));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac, powerup_frac,
                     asset::from_string("8000000.0000 TST"), 0, 0);

      // No more available for 30 days
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac / 1000, powerup_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::days(29));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac / 1000, powerup_frac / 1000,
                                   asset::from_string("1.0000 TST")));
      t.produce_block(fc::days(1) - fc::milliseconds(1000));
      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("market doesn't have enough resources available"), //
                          t.powerup(N(bob111111111), N(alice1111111), 30, powerup_frac / 1000, powerup_frac / 1000,
                                   asset::from_string("1.0000 TST")));

      // Start decay
      t.produce_block(fc::milliseconds(1000));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, net_weight, net_weight / 1000));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, cpu_weight, cpu_weight / 1000));

      // 1 day of decay
      t.produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, int64_t(net_weight * exp(-1)),
                         int64_t(net_weight * exp(-1)) / 1000));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, int64_t(cpu_weight * exp(-1)),
                         int64_t(cpu_weight * exp(-1)) / 1000));

      // 1 day of decay
      t.produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, int64_t(net_weight * exp(-2)),
                         int64_t(net_weight * exp(-2)) / 1000));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, int64_t(cpu_weight * exp(-2)),
                         int64_t(cpu_weight * exp(-2)) / 1000));

      // 100% after 2 days of decay
      //
      // [ ((e^-2) ^ 1)*(e^-2 - 0.0) + ((1.0) ^ 2)/2 - ((e^-2) ^ 2)/2 ] * 2000000.0000 = 1018315.6389
      // [ ((e^-2) ^ 2)*(e^-2 - 0.0) + ((1.0) ^ 3)/3 - ((e^-2) ^ 3)/3 ] * 6000000.0000 = 2009915.0087
      //                                                                         total = 3028230.6476
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("3028229.8795"));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac, powerup_frac,
                     asset::from_string("3028229.8795 TST"), net_weight, cpu_weight);
   }

   {
      powerup_tester t;
      init(t, true);

      // 10%, 20%
      // (.1 ^ 2) * 2000000.0000 / 2 = 10000.0000
      // (.2 ^ 3) * 6000000.0000 / 3 = 16000.0000
      //                       total = 26000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("26000.0002"));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac * .1, powerup_frac * .2,
                     asset::from_string("26000.0002 TST"), net_weight * .1, cpu_weight * .2);

      t.produce_block(fc::days(15) - fc::milliseconds(500));

      // 20%, 20%
      // (.3 ^ 2) * 2000000.0000 / 2 - 10000.0000 =  80000.0000
      // (.4 ^ 3) * 6000000.0000 / 3 - 16000.0000 = 112000.0000
      //                                    total = 192000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("192000.0001"));
      t.check_powerup(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, powerup_frac * .2, powerup_frac * .2,
                     asset::from_string("192000.0001 TST"), net_weight * .2, cpu_weight * .2);

      // Start decay
      t.produce_block(fc::days(15) - fc::milliseconds(1000));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, .3 * net_weight, 0));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, .4 * cpu_weight, 0));

      // 1 day of decay from (30%, 40%) to (20%, 20%)
      t.produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(
            near(t.get_state().net.adjusted_utilization, int64_t(.1 * net_weight * exp(-1) + .2 * net_weight), 0));
      BOOST_REQUIRE(
            near(t.get_state().cpu.adjusted_utilization, int64_t(.2 * cpu_weight * exp(-1) + .2 * cpu_weight), 0));

      // 2 days of decay from (30%, 40%) to (20%, 20%)
      t.produce_block(fc::days(1) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.powerupexec(config::system_account_name, 10));
      BOOST_REQUIRE(
            near(t.get_state().net.adjusted_utilization, int64_t(.1 * net_weight * exp(-2) + .2 * net_weight), 0));
      BOOST_REQUIRE(
            near(t.get_state().cpu.adjusted_utilization, int64_t(.2 * cpu_weight * exp(-2) + .2 * cpu_weight), 0));
   }

} // rent_tests
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
