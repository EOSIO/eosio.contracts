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

inline constexpr int64_t rentbw_frac  = 1000000000000000ll; // 1.0 = 10^15
inline constexpr int64_t stake_weight = 1000000000000ll;    // 10^12

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

using namespace eosio_system;

struct rentbw_tester : eosio_system_tester {

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

   action_result configbw(const rentbw_config& config) {
      return push_action(N(eosio), N(configrentbw), mvo()("args", config));
   }
};

BOOST_AUTO_TEST_SUITE(eosio_system_rentbw_tests)

BOOST_FIXTURE_TEST_CASE(config_tests, rentbw_tester) try {
   BOOST_REQUIRE_EQUAL("missing authority of eosio",
                       push_action(N(alice1111111), N(configrentbw), mvo()("args", make_config())));

   BOOST_REQUIRE_EQUAL(wasm_assert_msg("rent_days must be > 0"),
                       configbw(make_config([&](auto& c) { c.rent_days = 0; })));
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
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("decay_secs must be >= 1"),
                       configbw(make_config([&](auto& c) { c.net.decay_secs = 0; })));
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
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("decay_secs must be >= 1"),
                       configbw(make_config([&](auto& c) { c.cpu.decay_secs = 0; })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price doesn't match core symbol"), configbw(make_config([&](auto& c) {
                          c.cpu.target_price = asset::from_string("1000000.000 TST");
                       })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price must be positive"),
                       configbw(make_config([&](auto& c) { c.cpu.target_price = asset::from_string("0.0000 TST"); })));
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("target_price must be positive"),
                       configbw(make_config([&](auto& c) { c.cpu.target_price = asset::from_string("-1.0000 TST"); })));
}

FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
