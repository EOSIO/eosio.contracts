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
#include <fstream>
#include <time.h>

#include "eosio.system_tester.hpp"
#include "csvwriter.hpp"
#include "csv.h"

#define PICOJSON_USE_INT64

#include "picojson.hpp"

inline constexpr int64_t rentbw_frac = 1'000'000'000'000'000ll; // 1.0 = 10^15
inline constexpr int64_t stake_weight = 100'000'000'0000ll;     // 10^12

inline constexpr int64_t endstate_weight_ratio = 1'000'000'000'000'0ll; // 0.1 = 10^13

inline constexpr float asset_to_float_const = 10000.0;

inline float to_human_readable(uint64_t asset) { return asset / asset_to_float_const; }

struct rentbw_config_resource
{
   fc::optional<int64_t> current_weight_ratio = {};
   fc::optional<int64_t> target_weight_ratio = {};
   fc::optional<int64_t> assumed_stake_weight = {};
   fc::optional<time_point_sec> target_timestamp = {};
   fc::optional<double> exponent = {};
   fc::optional<uint32_t> decay_secs = {};
   fc::optional<asset> min_price = {};
   fc::optional<asset> max_price = {};
};
FC_REFLECT(rentbw_config_resource,                                                             //
           (current_weight_ratio)(target_weight_ratio)(assumed_stake_weight)(target_timestamp) //
           (exponent)(decay_secs)(min_price)(max_price))

struct rentbw_config
{
   rentbw_config_resource net = {};
   rentbw_config_resource cpu = {};
   fc::optional<uint32_t> rent_days = {};
   fc::optional<asset> min_rent_fee = {};
};
FC_REFLECT(rentbw_config, (net)(cpu)(rent_days)(min_rent_fee))

struct rentbw_state_resource
{
   uint8_t version;
   int64_t weight;
   int64_t weight_ratio;
   int64_t assumed_stake_weight;
   int64_t initial_weight_ratio;
   int64_t target_weight_ratio;
   time_point_sec initial_timestamp;
   time_point_sec target_timestamp;
   double exponent;
   uint32_t decay_secs;
   asset min_price;
   asset max_price;
   int64_t utilization;
   int64_t adjusted_utilization;
   time_point_sec utilization_timestamp;
   int64_t fee;
};
FC_REFLECT(rentbw_state_resource,                                                                           //
           (version)(weight)(weight_ratio)(assumed_stake_weight)(initial_weight_ratio)(target_weight_ratio) //
           (initial_timestamp)(target_timestamp)(exponent)(decay_secs)(min_price)(max_price)(utilization)   //
           (adjusted_utilization)(utilization_timestamp)(fee))

struct rentbw_state
{
   uint8_t version;
   rentbw_state_resource net;
   rentbw_state_resource cpu;
   uint32_t rent_days;
   asset min_rent_fee;
};
FC_REFLECT(rentbw_state, (version)(net)(cpu)(rent_days)(min_rent_fee))

using namespace eosio_system;

struct rentbw_tester : eosio_system_tester
{
   std::optional<CSVWriter> csv = std::nullopt;
 
   rentbw_tester()
   {
      create_accounts_with_resources({N(eosio.reserv)});
   }

   int64_t calc_rentbw_fee(const rentbw_state_resource& state, int64_t utilization_increase) {
      if( utilization_increase <= 0 ) return 0;

      // Let p(u) = price as a function of the utilization fraction u which is defined for u in [0.0, 1.0].
      // Let f(u) = integral of the price function p(x) from x = 0.0 to x = u, again defined for u in [0.0, 1.0].

      // In particular we choose f(u) = min_price * u + ((max_price - min_price) / exponent) * (u ^ exponent).
      // And so p(u) = min_price + (max_price - min_price) * (u ^ (exponent - 1.0)).

      // Returns f(double(end_utilization)/state.weight) - f(double(start_utilization)/state.weight) which is equivalent to
      // the integral of p(x) from x = double(start_utilization)/state.weight to x = double(end_utilization)/state.weight.
      // @pre 0 <= start_utilization <= end_utilization <= state.weight
      auto price_integral_delta = [&state](int64_t start_utilization, int64_t end_utilization) -> double {
         double coefficient = (state.max_price.get_amount() - state.min_price.get_amount()) / state.exponent;
         double start_u     = double(start_utilization) / state.weight;
         double end_u       = double(end_utilization) / state.weight;
         return state.min_price.get_amount() * end_u - state.min_price.get_amount() * start_u +
                  coefficient * std::pow(end_u, state.exponent) - coefficient * std::pow(start_u, state.exponent);
      };

      // Returns p(double(utilization)/state.weight).
      // @pre 0 <= utilization <= state.weight
      auto price_function = [&state](int64_t utilization) -> double {
         double price = state.min_price.get_amount();
         // state.exponent >= 1.0, therefore the exponent passed into std::pow is >= 0.0.
         // Since the exponent passed into std::pow could be 0.0 and simultaneously so could double(utilization)/state.weight,
         // the safest thing to do is handle that as a special case explicitly rather than relying on std::pow to return 1.0
         // instead of triggering a domain error.
         double new_exponent = state.exponent - 1.0;
         if (new_exponent <= 0.0) {
            return state.max_price.get_amount();
         } else {
            price += (state.max_price.get_amount() - state.min_price.get_amount()) * std::pow(double(utilization) / state.weight, new_exponent);
         }

         return price;
      };

      double  fee = 0.0;
      int64_t start_utilization = state.utilization;
      int64_t end_utilization   = start_utilization + utilization_increase;

      if (start_utilization < state.adjusted_utilization) {
         fee += price_function(state.adjusted_utilization) *
                  std::min(utilization_increase, state.adjusted_utilization - start_utilization) / state.weight;
         start_utilization = state.adjusted_utilization;
      }

      if (start_utilization < end_utilization) {
         fee += price_integral_delta(start_utilization, end_utilization);
      }

      return std::ceil(fee);
   }

   void setOutputFile(const std::string &filename)
   {
      csv.emplace(filename);

      csv->newRow()
         << "last_block_time"
         << "before_state.net.assumed_stake_weight"
         << "before_state.net.weight_ratio"
         << "before_state.net.weight"
         << "before_reserve.net"
         << "after_reserve.net"
         << "before_reserve.cpu"
         << "after_reserve.cpu"
         << "liquid_balance"
         << "net.frac"
         << "net.delta"
         << "net.fee"
         << "cpu.frac"
         << "cpu.delta"
         << "cpu.fee"
         << "fee"
         << "net.weight"
         << "net.weight_ratio"
         << "net.assumed_stake_weight"
         << "net.initial_weight_ratio"
         << "net.target_weight_ratio"
         << "net.initial_timestamp"
         << "net.target_timestamp"
         << "net.exponent"
         << "net.decay_secs"
         << "net.min_price"
         << "net.max_price"
         << "net.utilization"
         << "net.adjusted_utilization"
         << "net.utilization_timestamp"
         << "cpu.weight"
         << "cpu.weight_ratio"
         << "cpu.assumed_stake_weight"
         << "cpu.initial_weight_ratio"
         << "cpu.target_weight_ratio"
         << "cpu.initial_timestamp"
         << "cpu.target_timestamp"
         << "cpu.exponent"
         << "cpu.decay_secs"
         << "cpu.min_price"
         << "cpu.max_price"
         << "cpu.utilization"
         << "cpu.adjusted_utilization"
         << "cpu.utilization_timestamp"
         << "function";
   }

   void start_rex()
   {
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
   rentbw_config make_config(F f)
   {
      rentbw_config config;

      config.net.current_weight_ratio = rentbw_frac;
      config.net.target_weight_ratio = rentbw_frac / 100;
      config.net.assumed_stake_weight = stake_weight;
      config.net.target_timestamp = control->head_block_time() + fc::days(100);
      config.net.exponent = 2;
      config.net.decay_secs = fc::days(1).to_seconds();
      config.net.min_price = asset::from_string("0.0000 TST");
      config.net.max_price = asset::from_string("1000000.0000 TST");

      config.cpu.current_weight_ratio = rentbw_frac;
      config.cpu.target_weight_ratio = rentbw_frac / 100;
      config.cpu.assumed_stake_weight = stake_weight;
      config.cpu.target_timestamp = control->head_block_time() + fc::days(100);
      config.cpu.exponent = 2;
      config.cpu.decay_secs = fc::days(1).to_seconds();
      config.cpu.min_price = asset::from_string("0.0000 TST");
      config.cpu.max_price = asset::from_string("1000000.0000 TST");

      config.rent_days = 30;
      config.min_rent_fee = asset::from_string("1.0000 TST");

      f(config);
      return config;
   }

   template <typename F>
   rentbw_config make_config_from_file(const string &fname, F g)
   {
      rentbw_config config;

      stringstream ss;
      ifstream f;
      unsigned int i;

      // Read Json file
      f.open(fname, ios::binary);
      if (!f.is_open())
      {
         ilog("Unable to find model configuration file, using default");
         return make_config(g);
      }
      ss << f.rdbuf();
      f.close();

      // Parse Json data
      picojson::value v;
      ss >> v;
      string err = picojson::get_last_error();
      if (!err.empty())
      {
         cerr << err << endl;
      }

      picojson::object &o = v.get<picojson::object>()["cpu"].get<picojson::object>();

      config.net.current_weight_ratio = v.get("net").get("current_weight_ratio").get<int64_t>();
      config.net.target_weight_ratio = v.get("net").get("target_weight_ratio").get<int64_t>();
      config.net.assumed_stake_weight = v.get("net").get("assumed_stake_weight").get<int64_t>();
      config.net.target_timestamp = fc::time_point::from_iso_string(v.get("net").get("target_timestamp").get<string>());

      config.net.exponent = v.get("net").get("exponent").get<int64_t>();
      config.net.decay_secs = v.get("net").get("decay_secs").get<int64_t>();
      config.net.min_price = asset::from_string(v.get("net").get("min_price").get<string>());
      config.net.max_price = asset::from_string(v.get("net").get("max_price").get<string>());
      config.cpu.current_weight_ratio = v.get("cpu").get("current_weight_ratio").get<int64_t>();
      config.cpu.target_weight_ratio = v.get("cpu").get("target_weight_ratio").get<int64_t>();

      config.cpu.assumed_stake_weight = v.get("cpu").get("assumed_stake_weight").get<int64_t>();
      config.cpu.target_timestamp = fc::time_point::from_iso_string(v.get("cpu").get("target_timestamp").get<string>());
      config.cpu.exponent = v.get("cpu").get("exponent").get<int64_t>();
      config.cpu.decay_secs = v.get("cpu").get("decay_secs").get<int64_t>();
      config.cpu.min_price = asset::from_string(v.get("cpu").get("min_price").get<string>());
      config.cpu.max_price = asset::from_string(v.get("cpu").get("max_price").get<string>());

      config.rent_days = v.get("rent_days").get<int64_t>();
      config.min_rent_fee = asset::from_string(v.get("min_rent_fee").get<string>());

      g(config);
      return config;
   }

   rentbw_config make_config()
   {
      return make_config([](auto &) {});
   }

   template <typename F>
   rentbw_config make_default_config(F f)
   {
      rentbw_config config;
      f(config);
      return config;
   }

   action_result configbw(const rentbw_config &config)
   {
      // Verbose solution needed to work around bug in abi_serializer that fails if optional values aren't explicitly
      // specified with a null value.

      auto optional_to_variant = [](const auto &v) -> fc::variant {
         return (!v ? fc::variant() : fc::variant(*v));
      };

      auto resource_conf_vo = [&optional_to_variant](const rentbw_config_resource &c) {
         return mvo("current_weight_ratio", optional_to_variant(c.current_weight_ratio))("target_weight_ratio", optional_to_variant(c.target_weight_ratio))("assumed_stake_weight", optional_to_variant(c.assumed_stake_weight))("target_timestamp", optional_to_variant(c.target_timestamp))("exponent", optional_to_variant(c.exponent))("decay_secs", optional_to_variant(c.decay_secs))("min_price", optional_to_variant(c.min_price))("max_price", optional_to_variant(c.max_price));
      };

      auto conf = mvo("net", resource_conf_vo(config.net))("cpu", resource_conf_vo(config.cpu))("rent_days", optional_to_variant(config.rent_days))("min_rent_fee", optional_to_variant(config.min_rent_fee));

      //idump((fc::json::to_pretty_string(conf)));
      return push_action(config::system_account_name, N(configrentbw), mvo()("args", std::move(conf)));

      // If abi_serializer worked correctly, the following is all that would be needed:
      //return push_action(config::system_account_name, N(configrentbw), mvo()("args", config));
   }

   action_result rentbwexec(name user, uint16_t max)
   {
      return push_action(user, N(rentbwexec), mvo()("user", user)("max", max));
   }

   action_result rentbw(const name &payer, const name &receiver, uint32_t days, int64_t net_frac, int64_t cpu_frac,
                        const asset &max_payment)
   {
      return push_action(payer, N(rentbw),
                         mvo()("payer", payer)("receiver", receiver)("days", days)("net_frac", net_frac)(
                             "cpu_frac", cpu_frac)("max_payment", max_payment));
   }

   rentbw_state get_state()
   {
      vector<char> data = get_row_by_account(config::system_account_name, {}, N(rent.state), N(rent.state));
      return fc::raw::unpack<rentbw_state>(data);
   }

   struct account_info
   {
      int64_t ram = 0;
      int64_t net = 0;
      int64_t cpu = 0;
      asset liquid;
   };

   account_info get_account_info(account_name acc)
   {
      account_info info;
      control->get_resource_limits_manager().get_account_limits(acc, info.ram, info.net, info.cpu);
      info.liquid = get_balance(acc);
      return info;
   };

   void check_rentbw(const name &payer, const name &receiver, uint32_t days, int64_t net_frac, int64_t cpu_frac,
                     const asset &expected_fee, int64_t expected_net, int64_t expected_cpu, uint16_t max = 0)
   {
      auto before_payer = get_account_info(payer);
      auto before_receiver = get_account_info(receiver);
      auto before_reserve = get_account_info(N(eosio.reserv));
      auto before_state = get_state();
      // fees
      auto net_util = __int128_t(net_frac) * before_state.net.weight / rentbw_frac;
      auto net_fee = calc_rentbw_fee(before_state.net, net_util);
      auto cpu_util = __int128_t(cpu_frac) * before_state.cpu.weight / rentbw_frac;
      auto cpu_fee = calc_rentbw_fee(before_state.cpu, cpu_util);
      try
      {
         action_result res;
         if (max > 0)
         {
            res = rentbwexec(config::system_account_name, max);
         }
         else
         {
            res = rentbw(payer, receiver, before_state.rent_days, net_frac, cpu_frac, expected_fee);
         }
         if ( !res.empty() )
         {
            elog("${func} failed with error ${err}. Skipping this input", ("func", max > 0 ? "rentbwexec" : "rentbw")("err", res));
            return;
         }
      }
      catch (const fc::exception &ex)
      {
         elog("${func} failed with exception: ${err}. Skipping this input", ("func", max > 0 ? "rentbwexec" : "rentbw")("err", ex.to_detail_string()));
         return;
      }
      auto after_payer = get_account_info(payer);
      auto after_receiver = get_account_info(receiver);
      auto after_reserve = get_account_info(N(eosio.reserv));
      auto after_state = get_state();

      if (csv)
      {
         ilog("before_state.net.assumed_stake_weight:    ${x}", ("x", before_state.net.assumed_stake_weight));
         ilog("before_state.net.weight_ratio:            ${x}",
              ("x", before_state.net.weight_ratio / double(rentbw_frac)));
         ilog("before_state.net.assumed_stake_weight:    ${x}", ("x", before_state.net.assumed_stake_weight));
         ilog("before_state.net.weight:                  ${x}", ("x", before_state.net.weight));

         ilog("before_receiver.net:                      ${x}", ("x", before_receiver.net));
         ilog("after_receiver.net:                       ${x}", ("x", after_receiver.net));
         ilog("net util:                                 ${x}", ("x", to_human_readable(net_util)));
         ilog("expected_net:                             ${x}", ("x", expected_net));
         ilog("fee:                                      ${x}", ("x", before_payer.liquid - after_payer.liquid));
         ilog("expected_fee:                             ${x}", ("x", expected_fee));

         ilog("before_reserve.net:                       ${x}", ("x", before_reserve.net));
         ilog("after_reserve.net:                        ${x}", ("x", after_reserve.net));
         ilog("before_reserve.cpu:                       ${x}", ("x", before_reserve.cpu));
         ilog("after_reserve.cpu:                        ${x}", ("x", after_reserve.cpu));
   
         csv->newRow()  << last_block_time()           
                        << before_state.net.assumed_stake_weight
                        << before_state.net.weight_ratio / double(rentbw_frac)
                        << before_state.net.weight
                        << to_human_readable(before_reserve.net)
                        << to_human_readable(after_reserve.net)
                        << to_human_readable(before_reserve.cpu)
                        << to_human_readable(after_reserve.cpu)
                        << before_payer.liquid
                        << net_frac
                        << to_human_readable(net_util)
                        << to_human_readable(net_fee)
                        << cpu_frac
                        << to_human_readable(cpu_util)
                        << to_human_readable(cpu_fee)
                        << to_human_readable((before_payer.liquid - after_payer.liquid).get_amount()) 
                        << after_state.net.weight
                        << after_state.net.weight_ratio
                        << after_state.net.assumed_stake_weight
                        << after_state.net.initial_weight_ratio
                        << after_state.net.target_weight_ratio
                        << after_state.net.initial_timestamp.sec_since_epoch()
                        << after_state.net.target_timestamp.sec_since_epoch()
                        << after_state.net.exponent
                        << after_state.net.decay_secs
                        << after_state.net.min_price.to_string()
                        << after_state.net.max_price.to_string()
                        << after_state.net.utilization
                        << after_state.net.adjusted_utilization
                        << after_state.net.utilization_timestamp.sec_since_epoch()
                        << after_state.cpu.weight
                        << after_state.cpu.weight_ratio
                        << after_state.cpu.assumed_stake_weight
                        << after_state.cpu.initial_weight_ratio
                        << after_state.cpu.target_weight_ratio
                        << after_state.cpu.initial_timestamp.sec_since_epoch()
                        << after_state.cpu.target_timestamp.sec_since_epoch()
                        << after_state.cpu.exponent
                        << after_state.cpu.decay_secs
                        << after_state.cpu.min_price.to_string()
                        << after_state.cpu.max_price.to_string()
                        << after_state.cpu.utilization
                        << after_state.cpu.adjusted_utilization
                        << after_state.cpu.utilization_timestamp.sec_since_epoch()
                        << (max > 0 ? "rentbwexec" : "rentbw");
      }

      if (payer != receiver)
      {
         BOOST_REQUIRE_EQUAL(before_payer.ram, after_payer.ram);
         BOOST_REQUIRE_EQUAL(before_payer.net, after_payer.net);
         BOOST_REQUIRE_EQUAL(before_payer.cpu, after_payer.cpu);
         BOOST_REQUIRE_EQUAL(before_receiver.liquid, after_receiver.liquid);
      }
   }

   void produce_blocks_date(const char *str)
   {
      auto time_diff = fc::time_point::from_iso_string(str).sec_since_epoch() - last_block_time();
      if (time_diff > 500)
      {
         produce_block(fc::seconds(time_diff) - fc::milliseconds(500));
      }     
   }
};

template <typename A, typename B, typename D>
bool near(A a, B b, D delta)
{
   if (abs(a - b) <= delta)
      return true;
   elog("near: ${a} ${b}", ("a", a)("b", b));
   return false;
}

BOOST_AUTO_TEST_SUITE(eosio_system_rentbw_tests)

BOOST_FIXTURE_TEST_CASE(config_tests, rentbw_tester)
try
{
   BOOST_REQUIRE_EQUAL("missing authority of eosio",
                       push_action(N(alice1111111), N(configrentbw), mvo()("args", make_config())));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("rentbw hasn't been initialized"), rentbwexec(N(alice1111111), 10));

   BOOST_REQUIRE_EQUAL(wasm_assert_msg("rent_days must be > 0"),
                       configbw(make_config([&](auto &c) { c.rent_days = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_rent_fee doesn't match core symbol"), configbw(make_config([&](auto &c) {
                          c.min_rent_fee = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_rent_fee does not have a default value"),
                       configbw(make_config([&](auto &c) { c.min_rent_fee = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_rent_fee must be positive"),
                       configbw(make_config([&](auto &c) { c.min_rent_fee = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_rent_fee must be positive"),
                       configbw(make_config([&](auto &c) { c.min_rent_fee = asset::from_string("-1.0000 TST"); })));

   // net assertions
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("current_weight_ratio is too large"),
                       configbw(make_config([](auto &c) { c.net.current_weight_ratio = rentbw_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight/target_weight_ratio is too large"),
                       configbw(make_config([](auto &c) {
                          c.net.assumed_stake_weight = 100000;
                          c.net.target_weight_ratio = 10;
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("weight can't grow over time"),
                       configbw(make_config([](auto &c) { c.net.target_weight_ratio = rentbw_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight does not have a default value"),
                       configbw(make_config([](auto &c) { c.net.assumed_stake_weight = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight must be at least 1; a much larger value is recommended"),
                       configbw(make_config([](auto &c) { c.net.assumed_stake_weight = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp does not have a default value"),
                       configbw(make_config([&](auto &c) { c.net.target_timestamp = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"),
                       configbw(make_config([&](auto &c) { c.net.target_timestamp = control->head_block_time(); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"), configbw(make_config([&](auto &c) {
                          c.net.target_timestamp = control->head_block_time() - fc::seconds(1);
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("exponent must be >= 1"),
                       configbw(make_config([&](auto &c) { c.net.exponent = .999; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("decay_secs must be >= 1"),
                       configbw(make_config([&](auto &c) { c.net.decay_secs = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price does not have a default value"),
                       configbw(make_config([&](auto &c) { c.net.max_price = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price doesn't match core symbol"), configbw(make_config([&](auto &c) {
                          c.net.max_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price must be positive"),
                       configbw(make_config([&](auto &c) { c.net.max_price = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price must be positive"),
                       configbw(make_config([&](auto &c) { c.net.max_price = asset::from_string("-1.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price doesn't match core symbol"), configbw(make_config([&](auto &c) {
                          c.net.min_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price must be non-negative"),
                       configbw(make_config([&](auto &c) { c.net.min_price = asset::from_string("-1.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price cannot exceed max_price"),
                       configbw(make_config([&](auto &c) {
                          c.net.min_price = asset::from_string("3.0000 TST");
                          c.net.max_price = asset::from_string("2.0000 TST");
                       })));

   // cpu assertions
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("current_weight_ratio is too large"),
                       configbw(make_config([](auto &c) { c.cpu.current_weight_ratio = rentbw_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight/target_weight_ratio is too large"),
                       configbw(make_config([](auto &c) {
                          c.cpu.assumed_stake_weight = 100000;
                          c.cpu.target_weight_ratio = 10;
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("weight can't grow over time"),
                       configbw(make_config([](auto &c) { c.cpu.target_weight_ratio = rentbw_frac + 1; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight does not have a default value"),
                       configbw(make_config([](auto &c) { c.cpu.assumed_stake_weight = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("assumed_stake_weight must be at least 1; a much larger value is recommended"),
                       configbw(make_config([](auto &c) { c.cpu.assumed_stake_weight = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp does not have a default value"),
                       configbw(make_config([&](auto &c) { c.cpu.target_timestamp = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"),
                       configbw(make_config([&](auto &c) { c.cpu.target_timestamp = control->head_block_time(); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_timestamp must be in the future"), configbw(make_config([&](auto &c) {
                          c.cpu.target_timestamp = control->head_block_time() - fc::seconds(1);
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("exponent must be >= 1"),
                       configbw(make_config([&](auto &c) { c.cpu.exponent = .999; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("decay_secs must be >= 1"),
                       configbw(make_config([&](auto &c) { c.cpu.decay_secs = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price does not have a default value"),
                       configbw(make_config([&](auto &c) { c.cpu.max_price = {}; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price doesn't match core symbol"), configbw(make_config([&](auto &c) {
                          c.cpu.max_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price must be positive"),
                       configbw(make_config([&](auto &c) { c.cpu.max_price = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("max_price must be positive"),
                       configbw(make_config([&](auto &c) { c.cpu.max_price = asset::from_string("-1.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price doesn't match core symbol"), configbw(make_config([&](auto &c) {
                          c.cpu.min_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price must be non-negative"),
                       configbw(make_config([&](auto &c) { c.cpu.min_price = asset::from_string("-1.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("min_price cannot exceed max_price"),
                       configbw(make_config([&](auto &c) {
                          c.cpu.min_price = asset::from_string("3.0000 TST");
                          c.cpu.max_price = asset::from_string("2.0000 TST");
                       })));
} // config_tests
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(weight_tests, rentbw_tester)
try
{
   produce_block();

   auto net_start = (rentbw_frac * 11) / 100;
   auto net_target = (rentbw_frac * 1) / 100;
   auto cpu_start = (rentbw_frac * 11) / 1000;
   auto cpu_target = (rentbw_frac * 1) / 1000;

   BOOST_REQUIRE_EQUAL("", configbw(make_config([&](rentbw_config &config) {
                          config.net.current_weight_ratio = net_start;
                          config.net.target_weight_ratio = net_target;
                          config.net.assumed_stake_weight = stake_weight;
                          config.net.target_timestamp = control->head_block_time() + fc::days(10);

                          config.cpu.current_weight_ratio = cpu_start;
                          config.cpu.target_weight_ratio = cpu_target;
                          config.cpu.assumed_stake_weight = stake_weight;
                          config.cpu.target_timestamp = control->head_block_time() + fc::days(20);
                       })));

   int64_t net;
   int64_t cpu;

   auto check_weight = [&] {
      auto state = get_state();
      BOOST_REQUIRE(near(         //
          state.net.weight_ratio, //
          int64_t(state.net.assumed_stake_weight * eosio::chain::int128_t(rentbw_frac) /
                  (state.net.weight + state.net.assumed_stake_weight)),
          10));
   };

   for (int i = 0; i <= 6; ++i)
   {
      if (i == 2)
      {
         // Leaves config as-is, but may introduce slight rounding
         produce_block(fc::days(1) - fc::milliseconds(500));
         BOOST_REQUIRE_EQUAL("", configbw({}));
      }
      else if (i)
      {
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
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](rentbw_config &config) {
                             config.net.target_timestamp = control->head_block_time() + fc::days(30);
                             config.cpu.target_timestamp = control->head_block_time() + fc::days(40);
                          })));
      net_start = net = net_start + i * (net_target - net_start) / 10;
      cpu_start = cpu = cpu_start + i * (cpu_target - cpu_start) / 20;
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu, 1));
      check_weight();
   }

   for (int i = 0; i <= 5; ++i)
   {
      if (i)
      {
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
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](rentbw_config &config) {
                             config.net.target_weight_ratio = new_net_target;
                             config.cpu.target_weight_ratio = new_cpu_target;
                          })));
      net_start = net = net_start + i * (net_target - net_start) / 30;
      cpu_start = cpu = cpu_start + i * (cpu_target - cpu_start) / 40;
      net_target = new_net_target;
      cpu_target = new_cpu_target;
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu, 1));
      check_weight();
   }

   for (int i = 0; i <= 10; ++i)
   {
      if (i)
      {
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
      BOOST_REQUIRE_EQUAL("", configbw(make_default_config([&](rentbw_config &config) {
                             config.net.target_timestamp = control->head_block_time() + fc::milliseconds(1000);
                             config.cpu.target_timestamp = control->head_block_time() + fc::milliseconds(1000);
                          })));
      produce_blocks(2);
   }

   // Verify targets hold as time advances
   for (int i = 0; i <= 10; ++i)
   {
      BOOST_REQUIRE_EQUAL("", rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(get_state().net.weight_ratio, net_target, 1));
      BOOST_REQUIRE(near(get_state().cpu.weight_ratio, cpu_target, 1));
      check_weight();
      produce_block(fc::days(1));
   }
} // weight_tests
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_CASE(rent_tests)
try
{
   {
      rentbw_tester t;
      t.produce_block();

      BOOST_REQUIRE_EQUAL(t.wasm_assert_msg("rentbw hasn't been initialized"), //
                          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac / 4, rentbw_frac / 8,
                                   asset::from_string("1.000 TST")));

      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_config([&](auto &config) {
         config.net.current_weight_ratio = rentbw_frac;
         config.net.target_weight_ratio = rentbw_frac;
         config.net.assumed_stake_weight = stake_weight;
         config.net.exponent = 1;
         config.net.min_price = asset::from_string("1000000.0000 TST");
         config.net.max_price = asset::from_string("1000000.0000 TST");

         config.cpu.current_weight_ratio = rentbw_frac;
         config.cpu.target_weight_ratio = rentbw_frac;
         config.cpu.assumed_stake_weight = stake_weight;
         config.cpu.exponent = 1;
         config.cpu.min_price = asset::from_string("1000000.0000 TST");
         config.cpu.max_price = asset::from_string("1000000.0000 TST");

         config.rent_days = 30;
         config.min_rent_fee = asset::from_string("1.0000 TST");
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

      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_default_config([&](auto &config) {
         // weight = stake_weight
         config.net.current_weight_ratio = rentbw_frac / 2;
         config.net.target_weight_ratio = rentbw_frac / 2;

         // weight = stake_weight
         config.cpu.current_weight_ratio = rentbw_frac / 2;
         config.cpu.target_weight_ratio = rentbw_frac / 2;
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
      t.check_rentbw(N(aaaaaaaaaaaa), N(aaaaaaaaaaaa), 30, rentbw_frac * .1, rentbw_frac * .2,
                     asset::from_string("300000.0000 TST"), net_weight * .1, cpu_weight * .2);

      // Start decay
      t.produce_block(fc::days(30) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, .1 * net_weight, 0));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, .2 * cpu_weight, 0));

      // 2 days of decay from (10%, 20%) to (1.35%, 2.71%)
      t.produce_block(fc::days(2) - fc::milliseconds(500));
      BOOST_REQUIRE_EQUAL("", t.rentbwexec(config::system_account_name, 10));
      BOOST_REQUIRE(near(t.get_state().net.adjusted_utilization, int64_t(.1 * net_weight * exp(-2)),
                         int64_t(.1 * net_weight * exp(-2)) / 1000));
      BOOST_REQUIRE(near(t.get_state().cpu.adjusted_utilization, int64_t(.2 * cpu_weight * exp(-2)),
                         int64_t(.2 * cpu_weight * exp(-2)) / 1000));

      // 2%, 2%
      // (0.0135 + 0.02 - 0.0135) * 1000000.0000 = 20000.0000
      // (.02) * 1000000.0000                    = 20000.0000
      //                                   total = 40000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("40000.0001"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(aaaaaaaaaaaa), 30, rentbw_frac * .02, rentbw_frac * .02,
                     asset::from_string("40000.0001 TST"), net_weight * .02, cpu_weight * .02);
   }

   auto init = [](auto &t, bool rex) {
      t.produce_block();
      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_config([&](auto &config) {
         // weight = stake_weight * 3
         config.net.current_weight_ratio = rentbw_frac / 4;
         config.net.target_weight_ratio = rentbw_frac / 4;
         config.net.assumed_stake_weight = stake_weight;
         config.net.exponent = 2;
         config.net.max_price = asset::from_string("2000000.0000 TST");

         // weight = stake_weight * 4 / 2
         config.cpu.current_weight_ratio = rentbw_frac / 5;
         config.cpu.target_weight_ratio = rentbw_frac / 5;
         config.cpu.assumed_stake_weight = stake_weight / 2;
         config.cpu.exponent = 3;
         config.cpu.max_price = asset::from_string("6000000.0000 TST");

         config.rent_days = 30;
         config.min_rent_fee = asset::from_string("1.0000 TST");
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
      BOOST_REQUIRE_EQUAL(                                 //
          t.wasm_assert_msg("net_frac can't be negative"), //
          t.rentbw(N(bob111111111), N(alice1111111), 30, -rentbw_frac, rentbw_frac,
                   asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                 //
          t.wasm_assert_msg("cpu_frac can't be negative"), //
          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac, -rentbw_frac,
                   asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                  //
          t.wasm_assert_msg("net can't be more than 100%"), //
          t.rentbw(N(bob111111111), N(alice1111111), 30, rentbw_frac + 1, rentbw_frac,
                   asset::from_string("1.0000 TST")));
      BOOST_REQUIRE_EQUAL(                                  //
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
          t.configbw(t.make_default_config([&](auto &config) {
             config.net.current_weight_ratio = rentbw_frac / 4 + 1;
             config.net.target_weight_ratio = rentbw_frac / 4 + 1;
             config.cpu.current_weight_ratio = rentbw_frac / 5;
             config.cpu.target_weight_ratio = rentbw_frac / 5;
          })));
      BOOST_REQUIRE_EQUAL( //
          t.wasm_assert_msg("weight can't shrink below utilization"),
          t.configbw(t.make_default_config([&](auto &config) {
             config.net.current_weight_ratio = rentbw_frac / 4;
             config.net.target_weight_ratio = rentbw_frac / 4;
             config.cpu.current_weight_ratio = rentbw_frac / 5 + 1;
             config.cpu.target_weight_ratio = rentbw_frac / 5 + 1;
          })));
      BOOST_REQUIRE_EQUAL( //
          "",              //
          t.configbw(t.make_default_config([&](auto &config) {
             config.net.current_weight_ratio = rentbw_frac / 4;
             config.net.target_weight_ratio = rentbw_frac / 4;
             config.cpu.current_weight_ratio = rentbw_frac / 5;
             config.cpu.target_weight_ratio = rentbw_frac / 5;
          })));
   }

   // net:30%, cpu:40%, then net:5%, cpu:10%
   {
      rentbw_tester t;
      init(t, true);
      // (.3 ^ 2) * 2000000.0000 / 2 =  90000.0000
      // (.4 ^ 3) * 6000000.0000 / 3 = 128000.0000
      //                       total = 218000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("218000.0001"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .3, rentbw_frac * .4,
                     asset::from_string("218000.0001 TST"), net_weight * .3, cpu_weight * .4);

      // (.35 ^ 2) * 2000000.0000 / 2 -  90000.0000 =  32500.0000
      // (.5  ^ 3) * 6000000.0000 / 3 - 128000.0000 = 122000.0000
      //                                      total = 154500.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("154500.0000"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .05, rentbw_frac * .10,
                     asset::from_string("154500.0000 TST"), net_weight * .05, cpu_weight * .10);
   }

   // net:50%, cpu:50% (but with non-zero min_price and also an exponent of 2 to simplify the math)
   {
      rentbw_tester t;
      init(t, true);
      BOOST_REQUIRE_EQUAL("", t.configbw(t.make_default_config([&](auto &config) {
         config.cpu.exponent = 2;
         config.net.min_price = asset::from_string("1200000.0000 TST");
         config.net.max_price = asset::from_string("2000000.0000 TST");

         config.cpu.exponent = 2;
         config.cpu.min_price = asset::from_string("4000000.0000 TST");
         config.cpu.max_price = asset::from_string("6000000.0000 TST");
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
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .5, rentbw_frac * .5,
                     asset::from_string("2950000.0000 TST"), net_weight * .5, cpu_weight * .5);
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
      // (1.0 ^ 1) * 2000000.0000 = 2000000.0000
      // (1.0 ^ 2) * 6000000.0000 = 6000000.0000
      //                    total = 8000000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("8000000.0000"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac, rentbw_frac,
                     asset::from_string("8000000.0000 TST"), 0, 0);

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
      // [ ((e^-2) ^ 1)*(e^-2 - 0.0) + ((1.0) ^ 2)/2 - ((e^-2) ^ 2)/2 ] * 2000000.0000 = 1018315.6389
      // [ ((e^-2) ^ 2)*(e^-2 - 0.0) + ((1.0) ^ 3)/3 - ((e^-2) ^ 3)/3 ] * 6000000.0000 = 2009915.0087
      //                                                                         total = 3028230.6476
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("3028229.8795"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac, rentbw_frac,
                     asset::from_string("3028229.8795 TST"), net_weight, cpu_weight);
   }

   {
      rentbw_tester t;
      init(t, true);

      // 10%, 20%
      // (.1 ^ 2) * 2000000.0000 / 2 = 10000.0000
      // (.2 ^ 3) * 6000000.0000 / 3 = 16000.0000
      //                       total = 26000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("26000.0002"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .1, rentbw_frac * .2,
                     asset::from_string("26000.0002 TST"), net_weight * .1, cpu_weight * .2);

      t.produce_block(fc::days(15) - fc::milliseconds(500));

      // 20%, 20%
      // (.3 ^ 2) * 2000000.0000 / 2 - 10000.0000 =  80000.0000
      // (.4 ^ 3) * 6000000.0000 / 3 - 16000.0000 = 112000.0000
      //                                    total = 192000.0000
      t.transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("192000.0001"));
      t.check_rentbw(N(aaaaaaaaaaaa), N(bbbbbbbbbbbb), 30, rentbw_frac * .2, rentbw_frac * .2,
                     asset::from_string("192000.0001 TST"), net_weight * .2, cpu_weight * .2);

      // Start decay
      t.produce_block(fc::days(15) - fc::milliseconds(1000));
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

namespace ut = boost::unit_test;

BOOST_AUTO_TEST_SUITE(eosio_system_rentbw_modeling_tests, *ut::disabled())

BOOST_FIXTURE_TEST_CASE(model_tests, rentbw_tester)
try
{
   auto argc = ut::framework::master_test_suite().argc;
   char **argv = ut::framework::master_test_suite().argv;
   if (argc < 4)
   {
      std::cout << "\nUsage: "s << argv[0] << " -t " << (ut::framework::get<ut::test_suite>(ut::framework::current_test_case().p_parent_id)).p_name
                << " -- <json config model file> <csv data file> <output file> [--verbose]\n"
                << std::endl;
      BOOST_FAIL("Files weren't provided");
   }

   produce_block();
   start_rex();

   io::CSVReader<9> in(argv[2]);
   in.read_header(io::ignore_extra_column, "datetime", "function", "payer", "receiver", "days", "net_frac", "cpu_frac", "max_payment", "queue_max");

   std::string datetime, function, payer, receiver;
   uint32_t days;
   int64_t net_frac, cpu_frac;
   std::string max_payment;
   uint16_t queue_max;

   setOutputFile(argv[3]);

   while (in.read_row(datetime, function, payer, receiver, days, net_frac, cpu_frac, max_payment, queue_max))
   {
      if (function == "rentbwexec" || function == "rentbw")
      {
         produce_blocks_date(datetime.c_str());

         account_name payer_name = string_to_name(payer);
         account_name receiver_name = string_to_name(receiver);

         check_rentbw(payer_name, receiver_name,
                      days, net_frac, cpu_frac, asset::from_string(max_payment + " TST"), 0, 0, function == "rentbwexec" ? queue_max : 0);
      }
      else if (function == "configrentbw")
      {
         produce_blocks_date(datetime.c_str());

         create_account_with_resources(N(aaaaaaaaaaaa), config::system_account_name, core_sym::from_string("1.0000"),
                                 false, core_sym::from_string("500.0000"), core_sym::from_string("500.0000"));
         issue_and_transfer(N(aaaaaaaaaaaa), core_sym::from_string("8500000000.0000"));
         // transfer(config::system_account_name, N(aaaaaaaaaaaa), core_sym::from_string("500000000.0000"));         
         
         action_result res = configbw(make_config_from_file(argv[1], [&](auto &config) {}));
         if ( !res.empty() )
         {
            ilog("Unexpected issue with configbw: ${err}", ("err", res));
         }
      }
      else {
         ilog("Unexpected input function '${func}', skipping. Please check your input csv file line ${line}",
              ("func", function)
              ("line", in.get_file_line())
              );
      }
   }
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
