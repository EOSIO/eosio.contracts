#include <boost/test/unit_test.hpp>
#include <eosio/chain/contract_table_objects.hpp>
#include <eosio/chain/global_property_object.hpp>
#include <eosio/chain/resource_limits.hpp>
#include <eosio/chain/wast_to_wasm.hpp>
#include <cstdlib>
#include <iostream>
#include <fc/log/logger.hpp>
#include <eosio/chain/exceptions.hpp>
#include <Runtime/Runtime.h>

#include "eosio.system_tester.hpp"
struct _abi_hash {
   name owner;
   fc::sha256 hash;
};
FC_REFLECT( _abi_hash, (owner)(hash) );

using namespace eosio_system;

BOOST_AUTO_TEST_SUITE(eosio_system_tests)

BOOST_FIXTURE_TEST_CASE( buysell, eosio_system_tester ) try {

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "alice1111111" );
   auto init_bytes =  total["ram_bytes"].as_uint64();

   const asset initial_ram_balance = get_balance(N(eosio.ram));
   const asset initial_ramfee_balance = get_balance(N(eosio.ramfee));
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("200.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("800.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( initial_ram_balance + core_sym::from_string("199.0000"), get_balance(N(eosio.ram)) );
   BOOST_REQUIRE_EQUAL( initial_ramfee_balance + core_sym::from_string("1.0000"), get_balance(N(eosio.ramfee)) );

   total = get_total_stake( "alice1111111" );
   auto bytes = total["ram_bytes"].as_uint64();
   auto bought_bytes = bytes - init_bytes;
   wdump((init_bytes)(bought_bytes)(bytes) );

   BOOST_REQUIRE_EQUAL( true, 0 < bought_bytes );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", bought_bytes ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("998.0049"), get_balance( "alice1111111" ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( true, total["ram_bytes"].as_uint64() == init_bytes );

   transfer( "eosio", "alice1111111", core_sym::from_string("100000000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100000998.0049"), get_balance( "alice1111111" ) );
   // alice buys ram for 10000000.0000, 0.5% = 50000.0000 go to ramfee
   // after fee 9950000.0000 go to bought bytes
   // when selling back bought bytes, pay 0.5% fee and get back 99.5% of 9950000.0000 = 9900250.0000
   // expected account after that is 90000998.0049 + 9900250.0000 = 99901248.0049 with a difference
   // of order 0.0001 due to rounding errors
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("90000998.0049"), get_balance( "alice1111111" ) );

   total = get_total_stake( "alice1111111" );
   bytes = total["ram_bytes"].as_uint64();
   bought_bytes = bytes - init_bytes;
   wdump((init_bytes)(bought_bytes)(bytes) );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", bought_bytes ) );
   total = get_total_stake( "alice1111111" );

   bytes = total["ram_bytes"].as_uint64();
   bought_bytes = bytes - init_bytes;
   wdump((init_bytes)(bought_bytes)(bytes) );

   BOOST_REQUIRE_EQUAL( true, total["ram_bytes"].as_uint64() == init_bytes );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("99901248.0048"), get_balance( "alice1111111" ) );

   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("30.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("99900688.0048"), get_balance( "alice1111111" ) );

   auto newtotal = get_total_stake( "alice1111111" );

   auto newbytes = newtotal["ram_bytes"].as_uint64();
   bought_bytes = newbytes - bytes;
   wdump((newbytes)(bytes)(bought_bytes) );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", bought_bytes ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("99901242.4187"), get_balance( "alice1111111" ) );

   newtotal = get_total_stake( "alice1111111" );
   auto startbytes = newtotal["ram_bytes"].as_uint64();

   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("10000000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("300000.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("49301242.4187"), get_balance( "alice1111111" ) );

   auto finaltotal = get_total_stake( "alice1111111" );
   auto endbytes = finaltotal["ram_bytes"].as_uint64();

   bought_bytes = endbytes - startbytes;
   wdump((startbytes)(endbytes)(bought_bytes) );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", bought_bytes ) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("99396507.4158"), get_balance( "alice1111111" ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_unstake, eosio_system_tester ) try {
   cross_15_percent_threshold();

   produce_blocks( 10 );
   produce_block( fc::hours(3*24) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());

   const auto init_eosio_stake_balance = get_balance( N(eosio.stake) );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( init_eosio_stake_balance + core_sym::from_string("300.0000"), get_balance( N(eosio.stake) ) );
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   produce_block( fc::hours(3*24-1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( init_eosio_stake_balance + core_sym::from_string("300.0000"), get_balance( N(eosio.stake) ) );
   //after 3 days funds should be released
   produce_block( fc::hours(1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( init_eosio_stake_balance, get_balance( N(eosio.stake) ) );

   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   total = get_total_stake("bob111111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());

   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000").get_amount(), total["net_weight"].as<asset>().get_amount() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000").get_amount(), total["cpu_weight"].as<asset>().get_amount() );

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000")), get_voter_info( "alice1111111" ) );

   auto bytes = total["ram_bytes"].as_uint64();
   BOOST_REQUIRE_EQUAL( true, 0 < bytes );

   //unstake from bob111111111
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   total = get_total_stake("bob111111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["cpu_weight"].as<asset>());
   produce_block( fc::hours(3*24-1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //after 3 days funds should be released
   produce_block( fc::hours(1) );
   produce_blocks(1);

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("0.0000") ), get_voter_info( "alice1111111" ) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance( "alice1111111" ) );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_unstake_with_transfer, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "eosio", core_sym::from_string("1000.0000"), config::system_account_name );
   issue( "eosio.stake", core_sym::from_string("1000.0000"), config::system_account_name );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   //eosio stakes for alice with transfer flag

   transfer( "eosio", "bob111111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "bob111111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   //check that alice has both bandwidth and voting power
   auto total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000")), get_voter_info( "alice1111111" ) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   //alice stakes for herself
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   //now alice's stake should be equal to transfered from eosio + own stake
   total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("410.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("600.0000")), get_voter_info( "alice1111111" ) );

   //alice can unstake everything (including what was transfered)
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("400.0000"), core_sym::from_string("200.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   produce_block( fc::hours(3*24-1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //after 3 days funds should be released

   produce_block( fc::hours(1) );
   produce_blocks(1);

   BOOST_REQUIRE_EQUAL( core_sym::from_string("1300.0000"), get_balance( "alice1111111" ) );

   //stake should be equal to what was staked in constructor, voting power should be 0
   total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("0.0000")), get_voter_info( "alice1111111" ) );

   // Now alice stakes to bob with transfer flag
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "alice1111111", "bob111111111", core_sym::from_string("100.0000"), core_sym::from_string("100.0000") ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_to_self_with_transfer, eosio_system_tester ) try {
   cross_15_percent_threshold();

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("cannot use transfer flag if delegating to self"),
                        stake_with_transfer( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") )
   );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_while_pending_refund, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "eosio", core_sym::from_string("1000.0000"), config::system_account_name );
   issue( "eosio.stake", core_sym::from_string("1000.0000"), config::system_account_name );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   //eosio stakes for alice with transfer flag

   transfer( "eosio", "bob111111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "bob111111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   //check that alice has both bandwidth and voting power
   auto total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000")), get_voter_info( "alice1111111" ) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );

   //alice stakes for herself
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   //now alice's stake should be equal to transfered from eosio + own stake
   total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("410.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("600.0000")), get_voter_info( "alice1111111" ) );

   //alice can unstake everything (including what was transfered)
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("400.0000"), core_sym::from_string("200.0000") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   produce_block( fc::hours(3*24-1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //after 3 days funds should be released

   produce_block( fc::hours(1) );
   produce_blocks(1);

   BOOST_REQUIRE_EQUAL( core_sym::from_string("1300.0000"), get_balance( "alice1111111" ) );

   //stake should be equal to what was staked in constructor, voting power should be 0
   total = get_total_stake("alice1111111");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("0.0000")), get_voter_info( "alice1111111" ) );

   // Now alice stakes to bob with transfer flag
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "alice1111111", "bob111111111", core_sym::from_string("100.0000"), core_sym::from_string("100.0000") ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( fail_without_auth, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("2000.0000"), core_sym::from_string("1000.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("10.0000"), core_sym::from_string("10.0000") ) );

   BOOST_REQUIRE_EQUAL( error("missing authority of alice1111111"),
                        push_action( N(alice1111111), N(delegatebw), mvo()
                                    ("from",     "alice1111111")
                                    ("receiver", "bob111111111")
                                    ("stake_net_quantity", core_sym::from_string("10.0000"))
                                    ("stake_cpu_quantity", core_sym::from_string("10.0000"))
                                    ("transfer", 0 )
                                    ,false
                        )
   );

   BOOST_REQUIRE_EQUAL( error("missing authority of alice1111111"),
                        push_action(N(alice1111111), N(undelegatebw), mvo()
                                    ("from",     "alice1111111")
                                    ("receiver", "bob111111111")
                                    ("unstake_net_quantity", core_sym::from_string("200.0000"))
                                    ("unstake_cpu_quantity", core_sym::from_string("100.0000"))
                                    ("transfer", 0 )
                                    ,false
                        )
   );
   //REQUIRE_MATCHING_OBJECT( , get_voter_info( "alice1111111" ) );
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( stake_negative, eosio_system_tester ) try {
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must stake a positive amount"),
                        stake( "alice1111111", core_sym::from_string("-0.0001"), core_sym::from_string("0.0000") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must stake a positive amount"),
                        stake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("-0.0001") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must stake a positive amount"),
                        stake( "alice1111111", core_sym::from_string("00.0000"), core_sym::from_string("00.0000") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must stake a positive amount"),
                        stake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("00.0000") )

   );

   BOOST_REQUIRE_EQUAL( true, get_voter_info( "alice1111111" ).is_null() );
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( unstake_negative, eosio_system_tester ) try {
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("200.0001"), core_sym::from_string("100.0001") ) );

   auto total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0001"), total["net_weight"].as<asset>());
   auto vinfo = get_voter_info("alice1111111" );
   wdump((vinfo));
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0002") ), get_voter_info( "alice1111111" ) );


   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must unstake a positive amount"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("-1.0000"), core_sym::from_string("0.0000") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must unstake a positive amount"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("0.0000"), core_sym::from_string("-1.0000") )
   );

   //unstake all zeros
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("must unstake a positive amount"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("0.0000"), core_sym::from_string("0.0000") )

   );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( unstake_more_than_at_stake, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());

   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   //trying to unstake more net bandwith than at stake

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked net bandwidth"),
                        unstake( "alice1111111", core_sym::from_string("200.0001"), core_sym::from_string("0.0000") )
   );

   //trying to unstake more cpu bandwith than at stake
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked cpu bandwidth"),
                        unstake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("100.0001") )

   );

   //check that nothing has changed
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( delegate_to_another_user, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   BOOST_REQUIRE_EQUAL( success(), stake ( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //all voting power goes to alice1111111
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000") ), get_voter_info( "alice1111111" ) );
   //but not to bob111111111
   BOOST_REQUIRE_EQUAL( true, get_voter_info( "bob111111111" ).is_null() );

   //bob111111111 should not be able to unstake what was staked by alice1111111
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked cpu bandwidth"),
                        unstake( "bob111111111", core_sym::from_string("0.0000"), core_sym::from_string("10.0000") )

   );
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked net bandwidth"),
                        unstake( "bob111111111", core_sym::from_string("10.0000"),  core_sym::from_string("0.0000") )
   );

   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", "bob111111111", core_sym::from_string("20.0000"), core_sym::from_string("10.0000") ) );
   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("230.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("120.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("970.0000"), get_balance( "carol1111111" ) );
   REQUIRE_MATCHING_OBJECT( voter( "carol1111111", core_sym::from_string("30.0000") ), get_voter_info( "carol1111111" ) );

   //alice1111111 should not be able to unstake money staked by carol1111111

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked net bandwidth"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("2001.0000"), core_sym::from_string("1.0000") )
   );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg("insufficient staked cpu bandwidth"),
                        unstake( "alice1111111", "bob111111111", core_sym::from_string("1.0000"), core_sym::from_string("101.0000") )

   );

   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("230.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("120.0000"), total["cpu_weight"].as<asset>());
   //balance should not change after unsuccessfull attempts to unstake
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );
   //voting power too
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000") ), get_voter_info( "alice1111111" ) );
   REQUIRE_MATCHING_OBJECT( voter( "carol1111111", core_sym::from_string("30.0000") ), get_voter_info( "carol1111111" ) );
   BOOST_REQUIRE_EQUAL( true, get_voter_info( "bob111111111" ).is_null() );
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( stake_unstake_separate, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance( "alice1111111" ) );

   //everything at once
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("10.0000"), core_sym::from_string("20.0000") ) );
   auto total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("20.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("30.0000"), total["cpu_weight"].as<asset>());

   //cpu
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("100.0000"), core_sym::from_string("0.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("120.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("30.0000"), total["cpu_weight"].as<asset>());

   //net
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("200.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("120.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("230.0000"), total["cpu_weight"].as<asset>());

   //unstake cpu
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("100.0000"), core_sym::from_string("0.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("20.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("230.0000"), total["cpu_weight"].as<asset>());

   //unstake net
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("0.0000"), core_sym::from_string("200.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("20.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("30.0000"), total["cpu_weight"].as<asset>());
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( adding_stake_partial_unstake, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000") ), get_voter_info( "alice1111111" ) );

   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("100.0000"), core_sym::from_string("50.0000") ) );

   auto total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("310.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("160.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("450.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("550.0000"), get_balance( "alice1111111" ) );

   //unstake a share
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "bob111111111", core_sym::from_string("150.0000"), core_sym::from_string("75.0000") ) );

   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("160.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("85.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("225.0000") ), get_voter_info( "alice1111111" ) );

   //unstake more
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "bob111111111", core_sym::from_string("50.0000"), core_sym::from_string("25.0000") ) );
   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("150.0000") ), get_voter_info( "alice1111111" ) );

   //combined amount should be available only in 3 days
   produce_block( fc::days(2) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("550.0000"), get_balance( "alice1111111" ) );
   produce_block( fc::days(1) );
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("850.0000"), get_balance( "alice1111111" ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_from_refund, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());

   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );

   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["cpu_weight"].as<asset>());

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("400.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("600.0000"), get_balance( "alice1111111" ) );

   //unstake a share
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("100.0000"), core_sym::from_string("50.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("250.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("600.0000"), get_balance( "alice1111111" ) );
   auto refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "50.0000"), refund["cpu_amount"].as<asset>() );
   //XXX auto request_time = refund["request_time"].as_int64();

   //alice delegates to bob, should pull from liquid balance not refund
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("60.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("350.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( "alice1111111" ) );
   refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "50.0000"), refund["cpu_amount"].as<asset>() );

   //stake less than pending refund, entire amount should be taken from refund
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("50.0000"), core_sym::from_string("25.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("160.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("85.0000"), total["cpu_weight"].as<asset>());
   refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("50.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("25.0000"), refund["cpu_amount"].as<asset>() );
   //request time should stay the same
   //BOOST_REQUIRE_EQUAL( request_time, refund["request_time"].as_int64() );
   //balance should stay the same
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( "alice1111111" ) );

   //stake exactly pending refund amount
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("50.0000"), core_sym::from_string("25.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   //pending refund should be removed
   refund = get_refund_request( "alice1111111" );
   BOOST_TEST_REQUIRE( refund.is_null() );
   //balance should stay the same
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( "alice1111111" ) );

   //create pending refund again
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("10.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( "alice1111111" ) );
   refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("200.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["cpu_amount"].as<asset>() );

   //stake more than pending refund
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("300.0000"), core_sym::from_string("200.0000") ) );
   total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("310.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["cpu_weight"].as<asset>());
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("700.0000") ), get_voter_info( "alice1111111" ) );
   refund = get_refund_request( "alice1111111" );
   BOOST_TEST_REQUIRE( refund.is_null() );
   //200 core tokens should be taken from alice's account
   BOOST_REQUIRE_EQUAL( core_sym::from_string("300.0000"), get_balance( "alice1111111" ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( stake_to_another_user_not_from_refund, eosio_system_tester ) try {
   cross_15_percent_threshold();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   auto total = get_total_stake( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   REQUIRE_MATCHING_OBJECT( voter( "alice1111111", core_sym::from_string("300.0000") ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance( "alice1111111" ) );

   //unstake
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   auto refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("200.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["cpu_amount"].as<asset>() );
   //auto orig_request_time = refund["request_time"].as_int64();

   //stake to another user
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "bob111111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   total = get_total_stake( "bob111111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("210.0000"), total["net_weight"].as<asset>());
   BOOST_REQUIRE_EQUAL( core_sym::from_string("110.0000"), total["cpu_weight"].as<asset>());
   //stake should be taken from alices' balance, and refund request should stay the same
   BOOST_REQUIRE_EQUAL( core_sym::from_string("400.0000"), get_balance( "alice1111111" ) );
   refund = get_refund_request( "alice1111111" );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("200.0000"), refund["net_amount"].as<asset>() );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("100.0000"), refund["cpu_amount"].as<asset>() );
   //BOOST_REQUIRE_EQUAL( orig_request_time, refund["request_time"].as_int64() );

} FC_LOG_AND_RETHROW()

// Tests for voting
BOOST_FIXTURE_TEST_CASE( producer_register_unregister, eosio_system_tester ) try {
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );

   //fc::variant params = producer_parameters_example(1);
   auto key =  fc::crypto::public_key( std::string("EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV") );
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", key )
                                               ("url", "http://block.one")
                                               ("location", 1)
                        )
   );

   auto info = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( "alice1111111", info["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( 0, info["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( "http://block.one", info["url"].as_string() );

   //change parameters one by one to check for things like #3783
   //fc::variant params2 = producer_parameters_example(2);
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", key )
                                               ("url", "http://block.two")
                                               ("location", 1)
                        )
   );
   info = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( "alice1111111", info["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( key, fc::crypto::public_key(info["producer_key"].as_string()) );
   BOOST_REQUIRE_EQUAL( "http://block.two", info["url"].as_string() );
   BOOST_REQUIRE_EQUAL( 1, info["location"].as_int64() );

   auto key2 =  fc::crypto::public_key( std::string("EOS5jnmSKrzdBHE9n8hw58y7yxFWBC8SNiG7m8S1crJH3KvAnf9o6") );
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", key2 )
                                               ("url", "http://block.two")
                                               ("location", 2)
                        )
   );
   info = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( "alice1111111", info["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( key2, fc::crypto::public_key(info["producer_key"].as_string()) );
   BOOST_REQUIRE_EQUAL( "http://block.two", info["url"].as_string() );
   BOOST_REQUIRE_EQUAL( 2, info["location"].as_int64() );

   //unregister producer
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(unregprod), mvo()
                                               ("producer",  "alice1111111")
                        )
   );
   info = get_producer_info( "alice1111111" );
   //key should be empty
   BOOST_REQUIRE_EQUAL( fc::crypto::public_key(), fc::crypto::public_key(info["producer_key"].as_string()) );
   //everything else should stay the same
   BOOST_REQUIRE_EQUAL( "alice1111111", info["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( 0, info["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( "http://block.two", info["url"].as_string() );

   //unregister bob111111111 who is not a producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "producer not found" ),
                        push_action( N(bob111111111), N(unregprod), mvo()
                                     ("producer",  "bob111111111")
                        )
   );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( vote_for_producer, eosio_system_tester, * boost::unit_test::tolerance(1e+5) ) try {
   cross_15_percent_threshold();

   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   fc::variant params = producer_parameters_example(1);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url", "http://block.one")
                                               ("location", 0 )
                        )
   );
   auto prod = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( "alice1111111", prod["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( 0, prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( "http://block.one", prod["url"].as_string() );

   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   issue( "carol1111111", core_sym::from_string("3000.0000"),  config::system_account_name );

   //bob111111111 makes stake
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("11.0000"), core_sym::from_string("0.1111") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1988.8889"), get_balance( "bob111111111" ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("11.1111") ), get_voter_info( "bob111111111" ) );

   //bob111111111 votes for alice1111111
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(alice1111111) } ) );

   //check that producer parameters stay the same after voting
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("11.1111")) == prod["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( "alice1111111", prod["owner"].as_string() );
   BOOST_REQUIRE_EQUAL( "http://block.one", prod["url"].as_string() );

   //carol1111111 makes stake
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("22.0000"), core_sym::from_string("0.2222") ) );
   REQUIRE_MATCHING_OBJECT( voter( "carol1111111", core_sym::from_string("22.2222") ), get_voter_info( "carol1111111" ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("2977.7778"), get_balance( "carol1111111" ) );
   //carol1111111 votes for alice1111111
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), { N(alice1111111) } ) );

   //new stake votes be added to alice1111111's total_votes
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("33.3333")) == prod["total_votes"].as_double() );

   //bob111111111 increases his stake
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("33.0000"), core_sym::from_string("0.3333") ) );
   //alice1111111 stake with transfer to bob111111111
   BOOST_REQUIRE_EQUAL( success(), stake_with_transfer( "alice1111111", "bob111111111", core_sym::from_string("22.0000"), core_sym::from_string("0.2222") ) );
   //should increase alice1111111's total_votes
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("88.8888")) == prod["total_votes"].as_double() );

   //carol1111111 unstakes part of the stake
   BOOST_REQUIRE_EQUAL( success(), unstake( "carol1111111", core_sym::from_string("2.0000"), core_sym::from_string("0.0002")/*"2.0000 EOS", "0.0002 EOS"*/ ) );

   //should decrease alice1111111's total_votes
   prod = get_producer_info( "alice1111111" );
   wdump((prod));
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("86.8886")) == prod["total_votes"].as_double() );

   //bob111111111 revokes his vote
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), vector<account_name>() ) );

   //should decrease alice1111111's total_votes
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("20.2220")) == prod["total_votes"].as_double() );
   //but eos should still be at stake
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1955.5556"), get_balance( "bob111111111" ) );

   //carol1111111 unstakes rest of eos
   BOOST_REQUIRE_EQUAL( success(), unstake( "carol1111111", core_sym::from_string("20.0000"), core_sym::from_string("0.2220") ) );
   //should decrease alice1111111's total_votes to zero
   prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( 0.0 == prod["total_votes"].as_double() );

   //carol1111111 should receive funds in 3 days
   produce_block( fc::days(3) );
   produce_block();
   BOOST_REQUIRE_EQUAL( core_sym::from_string("3000.0000"), get_balance( "carol1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( unregistered_producer_voting, eosio_system_tester, * boost::unit_test::tolerance(1e+5) ) try {
   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("13.0000"), core_sym::from_string("0.5791") ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("13.5791") ), get_voter_info( "bob111111111" ) );

   //bob111111111 should not be able to vote for alice1111111 who is not a producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "producer is not registered" ),
                        vote( N(bob111111111), { N(alice1111111) } ) );

   //alice1111111 registers as a producer
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   fc::variant params = producer_parameters_example(1);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url", "")
                                               ("location", 0)
                        )
   );
   //and then unregisters
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(unregprod), mvo()
                                               ("producer",  "alice1111111")
                        )
   );
   //key should be empty
   auto prod = get_producer_info( "alice1111111" );
   BOOST_REQUIRE_EQUAL( fc::crypto::public_key(), fc::crypto::public_key(prod["producer_key"].as_string()) );

   //bob111111111 should not be able to vote for alice1111111 who is an unregistered producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "producer is not currently registered" ),
                        vote( N(bob111111111), { N(alice1111111) } ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( more_than_30_producer_voting, eosio_system_tester ) try {
   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("13.0000"), core_sym::from_string("0.5791") ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("13.5791") ), get_voter_info( "bob111111111" ) );

   //bob111111111 should not be able to vote for alice1111111 who is not a producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "attempt to vote for too many producers" ),
                        vote( N(bob111111111), vector<account_name>(31, N(alice1111111)) ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( vote_same_producer_30_times, eosio_system_tester ) try {
   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("100.0000") ), get_voter_info( "bob111111111" ) );

   //alice1111111 becomes a producer
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   fc::variant params = producer_parameters_example(1);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key(N(alice1111111), "active") )
                                               ("url", "")
                                               ("location", 0)
                        )
   );

   //bob111111111 should not be able to vote for alice1111111 who is not a producer
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "producer votes must be unique and sorted" ),
                        vote( N(bob111111111), vector<account_name>(30, N(alice1111111)) ) );

   auto prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( 0 == prod["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( producer_keep_votes, eosio_system_tester, * boost::unit_test::tolerance(1e+5) ) try {
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   fc::variant params = producer_parameters_example(1);
   vector<char> key = fc::raw::pack( get_public_key( N(alice1111111), "active" ) );
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url", "")
                                               ("location", 0)
                        )
   );

   //bob111111111 makes stake
   issue( "bob111111111", core_sym::from_string("2000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("13.0000"), core_sym::from_string("0.5791") ) );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("13.5791") ), get_voter_info( "bob111111111" ) );

   //bob111111111 votes for alice1111111
   BOOST_REQUIRE_EQUAL( success(), vote(N(bob111111111), { N(alice1111111) } ) );

   auto prod = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("13.5791")) == prod["total_votes"].as_double() );

   //unregister producer
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(unregprod), mvo()
                                               ("producer",  "alice1111111")
                        )
   );
   prod = get_producer_info( "alice1111111" );
   //key should be empty
   BOOST_REQUIRE_EQUAL( fc::crypto::public_key(), fc::crypto::public_key(prod["producer_key"].as_string()) );
   //check parameters just in case
   //REQUIRE_MATCHING_OBJECT( params, prod["prefs"]);
   //votes should stay the same
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("13.5791")), prod["total_votes"].as_double() );

   //regtister the same producer again
   params = producer_parameters_example(2);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url", "")
                                               ("location", 0)
                        )
   );
   prod = get_producer_info( "alice1111111" );
   //votes should stay the same
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("13.5791")), prod["total_votes"].as_double() );

   //change parameters
   params = producer_parameters_example(3);
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url","")
                                               ("location", 0)
                        )
   );
   prod = get_producer_info( "alice1111111" );
   //votes should stay the same
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("13.5791")), prod["total_votes"].as_double() );
   //check parameters just in case
   //REQUIRE_MATCHING_OBJECT( params, prod["prefs"]);

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( vote_for_two_producers, eosio_system_tester, * boost::unit_test::tolerance(1e+5) ) try {
   //alice1111111 becomes a producer
   fc::variant params = producer_parameters_example(1);
   auto key = get_public_key( N(alice1111111), "active" );
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproducer), mvo()
                                               ("producer",  "alice1111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url","")
                                               ("location", 0)
                        )
   );
   //bob111111111 becomes a producer
   params = producer_parameters_example(2);
   key = get_public_key( N(bob111111111), "active" );
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproducer), mvo()
                                               ("producer",  "bob111111111")
                                               ("producer_key", get_public_key( N(alice1111111), "active") )
                                               ("url","")
                                               ("location", 0)
                        )
   );

   //carol1111111 votes for alice1111111 and bob111111111
   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("15.0005"), core_sym::from_string("5.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), { N(alice1111111), N(bob111111111) } ) );

   auto alice_info = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("20.0005")) == alice_info["total_votes"].as_double() );
   auto bob_info = get_producer_info( "bob111111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("20.0005")) == bob_info["total_votes"].as_double() );

   //carol1111111 votes for alice1111111 (but revokes vote for bob111111111)
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), { N(alice1111111) } ) );

   alice_info = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("20.0005")) == alice_info["total_votes"].as_double() );
   bob_info = get_producer_info( "bob111111111" );
   BOOST_TEST_REQUIRE( 0 == bob_info["total_votes"].as_double() );

   //alice1111111 votes for herself and bob111111111
   issue( "alice1111111", core_sym::from_string("2.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("1.0000"), core_sym::from_string("1.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), vote(N(alice1111111), { N(alice1111111), N(bob111111111) } ) );

   alice_info = get_producer_info( "alice1111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("22.0005")) == alice_info["total_votes"].as_double() );

   bob_info = get_producer_info( "bob111111111" );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("2.0000")) == bob_info["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( proxy_register_unregister_keeps_stake, eosio_system_tester ) try {
   //register proxy by first action for this user ever
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproxy), mvo()
                                               ("proxy",  "alice1111111")
                                               ("isproxy", true )
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //unregister proxy
   BOOST_REQUIRE_EQUAL( success(), push_action(N(alice1111111), N(regproxy), mvo()
                                               ("proxy",  "alice1111111")
                                               ("isproxy", false)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //stake and then register as a proxy
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("200.0002"), core_sym::from_string("100.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproxy), mvo()
                                               ("proxy",  "bob111111111")
                                               ("isproxy", true)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "bob111111111" )( "staked", 3000003 ), get_voter_info( "bob111111111" ) );
   //unrgister and check that stake is still in place
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproxy), mvo()
                                               ("proxy",  "bob111111111")
                                               ("isproxy", false)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "bob111111111", core_sym::from_string("300.0003") ), get_voter_info( "bob111111111" ) );

   //register as a proxy and then stake
   BOOST_REQUIRE_EQUAL( success(), push_action( N(carol1111111), N(regproxy), mvo()
                                               ("proxy",  "carol1111111")
                                               ("isproxy", true)
                        )
   );
   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("246.0002"), core_sym::from_string("531.0001") ) );
   //check that both proxy flag and stake a correct
   REQUIRE_MATCHING_OBJECT( proxy( "carol1111111" )( "staked", 7770003 ), get_voter_info( "carol1111111" ) );

   //unregister
   BOOST_REQUIRE_EQUAL( success(), push_action( N(carol1111111), N(regproxy), mvo()
                                                ("proxy",  "carol1111111")
                                                ("isproxy", false)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "carol1111111", core_sym::from_string("777.0003") ), get_voter_info( "carol1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( proxy_stake_unstake_keeps_proxy_flag, eosio_system_tester ) try {
   cross_15_percent_threshold();

   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                               ("proxy",  "alice1111111")
                                               ("isproxy", true)
                        )
   );
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //stake
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("100.0000"), core_sym::from_string("50.0000") ) );
   //check that account is still a proxy
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "staked", 1500000 ), get_voter_info( "alice1111111" ) );

   //stake more
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("30.0000"), core_sym::from_string("20.0000") ) );
   //check that account is still a proxy
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )("staked", 2000000 ), get_voter_info( "alice1111111" ) );

   //unstake more
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("65.0000"), core_sym::from_string("35.0000") ) );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )("staked", 1000000 ), get_voter_info( "alice1111111" ) );

   //unstake the rest
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("65.0000"), core_sym::from_string("35.0000") ) );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "staked", 0 ), get_voter_info( "alice1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( proxy_actions_affect_producers, eosio_system_tester, * boost::unit_test::tolerance(1e+5) ) try {
   cross_15_percent_threshold();

   create_accounts_with_resources( {  N(defproducer1), N(defproducer2), N(defproducer3) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer1", 1) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer2", 2) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer3", 3) );

   //register as a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );

   //accumulate proxied votes
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote(N(bob111111111), vector<account_name>(), N(alice1111111) ) );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "proxied_vote_weight", stake2votes(core_sym::from_string("150.0003")) ), get_voter_info( "alice1111111" ) );

   //vote for producers
   BOOST_REQUIRE_EQUAL( success(), vote(N(alice1111111), { N(defproducer1), N(defproducer2) } ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003")) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( 0 == get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //vote for another producers
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice1111111), { N(defproducer1), N(defproducer3) } ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003")) == get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //unregister proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", false)
                        )
   );
   //REQUIRE_MATCHING_OBJECT( voter( "alice1111111" )( "proxied_vote_weight", stake2votes(core_sym::from_string("150.0003")) ), get_voter_info( "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //register proxy again
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003")) == get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //stake increase by proxy itself affects producers
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("30.0001"), core_sym::from_string("20.0001") ) );
   BOOST_REQUIRE_EQUAL( stake2votes(core_sym::from_string("200.0005")), get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( stake2votes(core_sym::from_string("200.0005")), get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //stake decrease by proxy itself affects producers
   BOOST_REQUIRE_EQUAL( success(), unstake( "alice1111111", core_sym::from_string("10.0001"), core_sym::from_string("10.0001") ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("180.0003")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("180.0003")) == get_producer_info( "defproducer3" )["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(producer_pay, eosio_system_tester, * boost::unit_test::tolerance(1e-10)) try {

   const double continuous_rate = 4.879 / 100.;
   const double usecs_per_year  = 52 * 7 * 24 * 3600 * 1000000ll;
   const double secs_per_year   = 52 * 7 * 24 * 3600;


   const asset large_asset = core_sym::from_string("80.0000");
   create_account_with_resources( N(defproducera), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
   create_account_with_resources( N(defproducerb), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
   create_account_with_resources( N(defproducerc), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );

   create_account_with_resources( N(producvotera), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
   create_account_with_resources( N(producvoterb), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );

   BOOST_REQUIRE_EQUAL(success(), regproducer(N(defproducera)));
   produce_block(fc::hours(24));
   auto prod = get_producer_info( N(defproducera) );
   BOOST_REQUIRE_EQUAL("defproducera", prod["owner"].as_string());
   BOOST_REQUIRE_EQUAL(0, prod["total_votes"].as_double());

   transfer( config::system_account_name, "producvotera", core_sym::from_string("400000000.0000"), config::system_account_name);
   BOOST_REQUIRE_EQUAL(success(), stake("producvotera", core_sym::from_string("100000000.0000"), core_sym::from_string("100000000.0000")));
   BOOST_REQUIRE_EQUAL(success(), vote( N(producvotera), { N(defproducera) }));
   // defproducera is the only active producer
   // produce enough blocks so new schedule kicks in and defproducera produces some blocks
   {
      produce_blocks(50);

      const auto     initial_global_state      = get_global_state();
      const uint64_t initial_claim_time        = microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] );
      const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
      const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
      const int64_t  initial_savings           = get_balance(N(eosio.saving)).get_amount();
      const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();

      prod = get_producer_info("defproducera");
      const uint32_t unpaid_blocks = prod["unpaid_blocks"].as<uint32_t>();
      BOOST_REQUIRE(1 < unpaid_blocks);

      BOOST_REQUIRE_EQUAL(initial_tot_unpaid_blocks, unpaid_blocks);

      const asset initial_supply  = get_token_supply();
      const asset initial_balance = get_balance(N(defproducera));

      BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));

      const auto     global_state      = get_global_state();
      const uint64_t claim_time        = microseconds_since_epoch_of_iso_string( global_state["last_pervote_bucket_fill"] );
      const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
      const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
      const int64_t  savings           = get_balance(N(eosio.saving)).get_amount();
      const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();

      prod = get_producer_info("defproducera");
      BOOST_REQUIRE_EQUAL(1, prod["unpaid_blocks"].as<uint32_t>());
      BOOST_REQUIRE_EQUAL(1, tot_unpaid_blocks);
      const asset supply  = get_token_supply();
      const asset balance = get_balance(N(defproducera));

      BOOST_REQUIRE_EQUAL(claim_time, microseconds_since_epoch_of_iso_string( prod["last_claim_time"] ));

      auto usecs_between_fills = claim_time - initial_claim_time;
      int32_t secs_between_fills = usecs_between_fills/1000000;

      BOOST_REQUIRE_EQUAL(0, initial_savings);
      BOOST_REQUIRE_EQUAL(0, initial_perblock_bucket);
      BOOST_REQUIRE_EQUAL(0, initial_pervote_bucket);

      BOOST_REQUIRE_EQUAL(int64_t( ( initial_supply.get_amount() * double(secs_between_fills) * continuous_rate ) / secs_per_year ),
                          supply.get_amount() - initial_supply.get_amount());
      BOOST_REQUIRE_EQUAL(int64_t( ( initial_supply.get_amount() * double(secs_between_fills) * (4.   * continuous_rate/ 5.) / secs_per_year ) ),
                          savings - initial_savings);
      BOOST_REQUIRE_EQUAL(int64_t( ( initial_supply.get_amount() * double(secs_between_fills) * (0.25 * continuous_rate/ 5.) / secs_per_year ) ),
                          balance.get_amount() - initial_balance.get_amount());

      int64_t from_perblock_bucket = int64_t( initial_supply.get_amount() * double(secs_between_fills) * (0.25 * continuous_rate/ 5.) / secs_per_year ) ;
      int64_t from_pervote_bucket  = int64_t( initial_supply.get_amount() * double(secs_between_fills) * (0.75 * continuous_rate/ 5.) / secs_per_year ) ;


      if (from_pervote_bucket >= 100 * 10000) {
         BOOST_REQUIRE_EQUAL(from_perblock_bucket + from_pervote_bucket, balance.get_amount() - initial_balance.get_amount());
         BOOST_REQUIRE_EQUAL(0, pervote_bucket);
      } else {
         BOOST_REQUIRE_EQUAL(from_perblock_bucket, balance.get_amount() - initial_balance.get_amount());
         BOOST_REQUIRE_EQUAL(from_pervote_bucket, pervote_bucket);
      }
   }

   {
      BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
                          push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));
   }

   // defproducera waits for 23 hours and 55 minutes, can't claim rewards yet
   {
      produce_block(fc::seconds(23 * 3600 + 55 * 60));
      BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
                          push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));
   }

   // wait 5 more minutes, defproducera can now claim rewards again
   {
      produce_block(fc::seconds(5 * 60));

      const auto     initial_global_state      = get_global_state();
      const uint64_t initial_claim_time        = microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] );
      const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
      const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
      const int64_t  initial_savings           = get_balance(N(eosio.saving)).get_amount();
      const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();
      const double   initial_tot_vote_weight   = initial_global_state["total_producer_vote_weight"].as<double>();

      prod = get_producer_info("defproducera");
      const uint32_t unpaid_blocks = prod["unpaid_blocks"].as<uint32_t>();
      BOOST_REQUIRE(1 < unpaid_blocks);
      BOOST_REQUIRE_EQUAL(initial_tot_unpaid_blocks, unpaid_blocks);
      BOOST_REQUIRE(0 < prod["total_votes"].as<double>());
      BOOST_TEST(initial_tot_vote_weight, prod["total_votes"].as<double>());
      BOOST_REQUIRE(0 < microseconds_since_epoch_of_iso_string( prod["last_claim_time"] ));

      BOOST_REQUIRE_EQUAL(initial_tot_unpaid_blocks, unpaid_blocks);

      const asset initial_supply  = get_token_supply();
      const asset initial_balance = get_balance(N(defproducera));

      BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));

      const auto global_state          = get_global_state();
      const uint64_t claim_time        = microseconds_since_epoch_of_iso_string( global_state["last_pervote_bucket_fill"] );
      const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
      const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
      const int64_t  savings           = get_balance(N(eosio.saving)).get_amount();
      const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();

      prod = get_producer_info("defproducera");
      BOOST_REQUIRE_EQUAL(1, prod["unpaid_blocks"].as<uint32_t>());
      BOOST_REQUIRE_EQUAL(1, tot_unpaid_blocks);
      const asset supply  = get_token_supply();
      const asset balance = get_balance(N(defproducera));

      BOOST_REQUIRE_EQUAL(claim_time, microseconds_since_epoch_of_iso_string( prod["last_claim_time"] ));
      auto usecs_between_fills = claim_time - initial_claim_time;

      BOOST_REQUIRE_EQUAL(int64_t( ( double(initial_supply.get_amount()) * double(usecs_between_fills) * continuous_rate / usecs_per_year ) ),
                          supply.get_amount() - initial_supply.get_amount());
      BOOST_REQUIRE_EQUAL( (supply.get_amount() - initial_supply.get_amount()) - (supply.get_amount() - initial_supply.get_amount()) / 5,
                          savings - initial_savings);

      int64_t to_producer        = int64_t( (double(initial_supply.get_amount()) * double(usecs_between_fills) * continuous_rate) / usecs_per_year ) / 5;
      int64_t to_perblock_bucket = to_producer / 4;
      int64_t to_pervote_bucket  = to_producer - to_perblock_bucket;

      if (to_pervote_bucket + initial_pervote_bucket >= 100 * 10000) {
         BOOST_REQUIRE_EQUAL(to_perblock_bucket + to_pervote_bucket + initial_pervote_bucket, balance.get_amount() - initial_balance.get_amount());
         BOOST_REQUIRE_EQUAL(0, pervote_bucket);
      } else {
         BOOST_REQUIRE_EQUAL(to_perblock_bucket, balance.get_amount() - initial_balance.get_amount());
         BOOST_REQUIRE_EQUAL(to_pervote_bucket + initial_pervote_bucket, pervote_bucket);
      }
   }

   // defproducerb tries to claim rewards but he's not on the list
   {
      BOOST_REQUIRE_EQUAL(wasm_assert_msg("unable to find key"),
                          push_action(N(defproducerb), N(claimrewards), mvo()("owner", "defproducerb")));
   }

   // test stability over a year
   {
      regproducer(N(defproducerb));
      regproducer(N(defproducerc));
      produce_block(fc::hours(24));
      const asset   initial_supply  = get_token_supply();
      const int64_t initial_savings = get_balance(N(eosio.saving)).get_amount();
      for (uint32_t i = 0; i < 7 * 52; ++i) {
         produce_block(fc::seconds(8 * 3600));
         BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducerc), N(claimrewards), mvo()("owner", "defproducerc")));
         produce_block(fc::seconds(8 * 3600));
         BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducerb), N(claimrewards), mvo()("owner", "defproducerb")));
         produce_block(fc::seconds(8 * 3600));
         BOOST_REQUIRE_EQUAL(success(), push_action(N(defproducera), N(claimrewards), mvo()("owner", "defproducera")));
      }
      const asset   supply  = get_token_supply();
      const int64_t savings = get_balance(N(eosio.saving)).get_amount();
      // Amount issued per year is very close to the 5% inflation target. Small difference (500 tokens out of 50'000'000 issued)
      // is due to compounding every 8 hours in this test as opposed to theoretical continuous compounding
      BOOST_REQUIRE(500 * 10000 > int64_t(double(initial_supply.get_amount()) * double(0.05)) - (supply.get_amount() - initial_supply.get_amount()));
      BOOST_REQUIRE(500 * 10000 > int64_t(double(initial_supply.get_amount()) * double(0.04)) - (savings - initial_savings));
   }
} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(multiple_producer_pay, eosio_system_tester, * boost::unit_test::tolerance(1e-10)) try {

   auto within_one = [](int64_t a, int64_t b) -> bool { return std::abs( a - b ) <= 1; };

   const int64_t secs_per_year  = 52 * 7 * 24 * 3600;
   const double  usecs_per_year = secs_per_year * 1000000;
   const double  cont_rate      = 4.879/100.;

   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   const std::vector<account_name> voters = { N(producvotera), N(producvoterb), N(producvoterc), N(producvoterd) };
   for (const auto& v: voters) {
      create_account_with_resources( v, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
      transfer( config::system_account_name, v, core_sym::from_string("100000000.0000"), config::system_account_name );
      BOOST_REQUIRE_EQUAL(success(), stake(v, core_sym::from_string("30000000.0000"), core_sym::from_string("30000000.0000")) );
   }

   // create accounts {defproducera, defproducerb, ..., defproducerz, abcproducera, ..., defproducern} and register as producers
   std::vector<account_name> producer_names;
   {
      producer_names.reserve('z' - 'a' + 1);
      {
         const std::string root("defproducer");
         for ( char c = 'a'; c <= 'z'; ++c ) {
            producer_names.emplace_back(root + std::string(1, c));
         }
      }
      {
         const std::string root("abcproducer");
         for ( char c = 'a'; c <= 'n'; ++c ) {
            producer_names.emplace_back(root + std::string(1, c));
         }
      }
      setup_producer_accounts(producer_names);
      for (const auto& p: producer_names) {
         BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
         produce_blocks(1);
         ilog( "------ get pro----------" );
         wdump((p));
         BOOST_TEST(0 == get_producer_info(p)["total_votes"].as<double>());
      }
   }

   produce_block( fc::hours(24) );

   // producvotera votes for defproducera ... defproducerj
   // producvoterb votes for defproducera ... defproduceru
   // producvoterc votes for defproducera ... defproducerz
   // producvoterd votes for abcproducera ... abcproducern
   {
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvotera), vector<account_name>(producer_names.begin(), producer_names.begin()+10)));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.begin()+21)));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterc), vector<account_name>(producer_names.begin(), producer_names.begin()+26)));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterd), vector<account_name>(producer_names.begin()+26, producer_names.end())));
   }

   {
      auto proda = get_producer_info( N(defproducera) );
      auto prodj = get_producer_info( N(defproducerj) );
      auto prodk = get_producer_info( N(defproducerk) );
      auto produ = get_producer_info( N(defproduceru) );
      auto prodv = get_producer_info( N(defproducerv) );
      auto prodz = get_producer_info( N(defproducerz) );

      BOOST_REQUIRE (0 == proda["unpaid_blocks"].as<uint32_t>() && 0 == prodz["unpaid_blocks"].as<uint32_t>());

      // check vote ratios
      BOOST_REQUIRE ( 0 < proda["total_votes"].as<double>() && 0 < prodz["total_votes"].as<double>() );
      BOOST_TEST( proda["total_votes"].as<double>() == prodj["total_votes"].as<double>() );
      BOOST_TEST( prodk["total_votes"].as<double>() == produ["total_votes"].as<double>() );
      BOOST_TEST( prodv["total_votes"].as<double>() == prodz["total_votes"].as<double>() );
      BOOST_TEST( 2 * proda["total_votes"].as<double>() == 3 * produ["total_votes"].as<double>() );
      BOOST_TEST( proda["total_votes"].as<double>() ==  3 * prodz["total_votes"].as<double>() );
   }

   // give a chance for everyone to produce blocks
   {
      produce_blocks(23 * 12 + 20);
      bool all_21_produced = true;
      for (uint32_t i = 0; i < 21; ++i) {
         if (0 == get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            all_21_produced = false;
         }
      }
      bool rest_didnt_produce = true;
      for (uint32_t i = 21; i < producer_names.size(); ++i) {
         if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            rest_didnt_produce = false;
         }
      }
      BOOST_REQUIRE(all_21_produced && rest_didnt_produce);
   }

   std::vector<double> vote_shares(producer_names.size());
   {
      double total_votes = 0;
      for (uint32_t i = 0; i < producer_names.size(); ++i) {
         vote_shares[i] = get_producer_info(producer_names[i])["total_votes"].as<double>();
         total_votes += vote_shares[i];
      }
      BOOST_TEST(total_votes == get_global_state()["total_producer_vote_weight"].as<double>());
      std::for_each(vote_shares.begin(), vote_shares.end(), [total_votes](double& x) { x /= total_votes; });

      BOOST_TEST(double(1) == std::accumulate(vote_shares.begin(), vote_shares.end(), double(0)));
      BOOST_TEST(double(3./71.) == vote_shares.front());
      BOOST_TEST(double(1./71.) == vote_shares.back());
   }

   {
      const uint32_t prod_index = 2;
      const auto prod_name = producer_names[prod_index];

      const auto     initial_global_state      = get_global_state();
      const uint64_t initial_claim_time        = microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] );
      const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
      const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
      const int64_t  initial_savings           = get_balance(N(eosio.saving)).get_amount();
      const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();
      const asset    initial_supply            = get_token_supply();
      const asset    initial_bpay_balance      = get_balance(N(eosio.bpay));
      const asset    initial_vpay_balance      = get_balance(N(eosio.vpay));
      const asset    initial_balance           = get_balance(prod_name);
      const uint32_t initial_unpaid_blocks     = get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>();

      BOOST_REQUIRE_EQUAL(success(), push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));

      const auto     global_state      = get_global_state();
      const uint64_t claim_time        = microseconds_since_epoch_of_iso_string( global_state["last_pervote_bucket_fill"] );
      const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
      const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
      const int64_t  savings           = get_balance(N(eosio.saving)).get_amount();
      const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();
      const asset    supply            = get_token_supply();
      const asset    bpay_balance      = get_balance(N(eosio.bpay));
      const asset    vpay_balance      = get_balance(N(eosio.vpay));
      const asset    balance           = get_balance(prod_name);
      const uint32_t unpaid_blocks     = get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>();

      const uint64_t usecs_between_fills = claim_time - initial_claim_time;
      const int32_t secs_between_fills = static_cast<int32_t>(usecs_between_fills / 1000000);

      const double expected_supply_growth = initial_supply.get_amount() * double(usecs_between_fills) * cont_rate / usecs_per_year;
      BOOST_REQUIRE_EQUAL( int64_t(expected_supply_growth), supply.get_amount() - initial_supply.get_amount() );

      BOOST_REQUIRE_EQUAL( int64_t(expected_supply_growth) - int64_t(expected_supply_growth)/5, savings - initial_savings );

      const int64_t expected_perblock_bucket = int64_t( double(initial_supply.get_amount()) * double(usecs_between_fills) * (0.25 * cont_rate/ 5.) / usecs_per_year );
      const int64_t expected_pervote_bucket  = int64_t( double(initial_supply.get_amount()) * double(usecs_between_fills) * (0.75 * cont_rate/ 5.) / usecs_per_year );

      const int64_t from_perblock_bucket = initial_unpaid_blocks * expected_perblock_bucket / initial_tot_unpaid_blocks ;
      const int64_t from_pervote_bucket  = int64_t( vote_shares[prod_index] * expected_pervote_bucket);

      BOOST_REQUIRE( 1 >= abs(int32_t(initial_tot_unpaid_blocks - tot_unpaid_blocks) - int32_t(initial_unpaid_blocks - unpaid_blocks)) );

      if (from_pervote_bucket >= 100 * 10000) {
         BOOST_REQUIRE( within_one( from_perblock_bucket + from_pervote_bucket, balance.get_amount() - initial_balance.get_amount() ) );
         BOOST_REQUIRE( within_one( expected_pervote_bucket - from_pervote_bucket, pervote_bucket ) );
      } else {
         BOOST_REQUIRE( within_one( from_perblock_bucket, balance.get_amount() - initial_balance.get_amount() ) );
         BOOST_REQUIRE( within_one( expected_pervote_bucket, pervote_bucket ) );
         BOOST_REQUIRE( within_one( expected_pervote_bucket, vpay_balance.get_amount() ) );
         BOOST_REQUIRE( within_one( perblock_bucket, bpay_balance.get_amount() ) );
      }

      produce_blocks(5);

      BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
                          push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
   }

   {
      const uint32_t prod_index = 23;
      const auto prod_name = producer_names[prod_index];
      BOOST_REQUIRE_EQUAL(success(),
                          push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
      BOOST_REQUIRE_EQUAL(0, get_balance(prod_name).get_amount());
      BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
                          push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
   }

   // Wait for 23 hours. By now, pervote_bucket has grown enough
   // that a producer's share is more than 100 tokens.
   produce_block(fc::seconds(23 * 3600));

   {
      const uint32_t prod_index = 15;
      const auto prod_name = producer_names[prod_index];

      const auto     initial_global_state      = get_global_state();
      const uint64_t initial_claim_time        = microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] );
      const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
      const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
      const int64_t  initial_savings           = get_balance(N(eosio.saving)).get_amount();
      const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();
      const asset    initial_supply            = get_token_supply();
      const asset    initial_bpay_balance      = get_balance(N(eosio.bpay));
      const asset    initial_vpay_balance      = get_balance(N(eosio.vpay));
      const asset    initial_balance           = get_balance(prod_name);
      const uint32_t initial_unpaid_blocks     = get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>();

      BOOST_REQUIRE_EQUAL(success(), push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));

      const auto     global_state      = get_global_state();
      const uint64_t claim_time        = microseconds_since_epoch_of_iso_string( global_state["last_pervote_bucket_fill"] );
      const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
      const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
      const int64_t  savings           = get_balance(N(eosio.saving)).get_amount();
      const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();
      const asset    supply            = get_token_supply();
      const asset    bpay_balance      = get_balance(N(eosio.bpay));
      const asset    vpay_balance      = get_balance(N(eosio.vpay));
      const asset    balance           = get_balance(prod_name);
      const uint32_t unpaid_blocks     = get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>();

      const uint64_t usecs_between_fills = claim_time - initial_claim_time;

      const double expected_supply_growth = initial_supply.get_amount() * double(usecs_between_fills) * cont_rate / usecs_per_year;
      BOOST_REQUIRE_EQUAL( int64_t(expected_supply_growth), supply.get_amount() - initial_supply.get_amount() );
      BOOST_REQUIRE_EQUAL( int64_t(expected_supply_growth) - int64_t(expected_supply_growth)/5, savings - initial_savings );

      const int64_t expected_perblock_bucket = int64_t( double(initial_supply.get_amount()) * double(usecs_between_fills) * (0.25 * cont_rate/ 5.) / usecs_per_year )
                                               + initial_perblock_bucket;
      const int64_t expected_pervote_bucket  = int64_t( double(initial_supply.get_amount()) * double(usecs_between_fills) * (0.75 * cont_rate/ 5.) / usecs_per_year )
                                               + initial_pervote_bucket;
      const int64_t from_perblock_bucket = initial_unpaid_blocks * expected_perblock_bucket / initial_tot_unpaid_blocks ;
      const int64_t from_pervote_bucket  = int64_t( vote_shares[prod_index] * expected_pervote_bucket);

      BOOST_REQUIRE( 1 >= abs(int32_t(initial_tot_unpaid_blocks - tot_unpaid_blocks) - int32_t(initial_unpaid_blocks - unpaid_blocks)) );
      if (from_pervote_bucket >= 100 * 10000) {
         BOOST_REQUIRE( within_one( from_perblock_bucket + from_pervote_bucket, balance.get_amount() - initial_balance.get_amount() ) );
         BOOST_REQUIRE( within_one( expected_pervote_bucket - from_pervote_bucket, pervote_bucket ) );
         BOOST_REQUIRE( within_one( expected_pervote_bucket - from_pervote_bucket, vpay_balance.get_amount() ) );
         BOOST_REQUIRE( within_one( expected_perblock_bucket - from_perblock_bucket, perblock_bucket ) );
         BOOST_REQUIRE( within_one( expected_perblock_bucket - from_perblock_bucket, bpay_balance.get_amount() ) );
      } else {
         BOOST_REQUIRE( within_one( from_perblock_bucket, balance.get_amount() - initial_balance.get_amount() ) );
         BOOST_REQUIRE( within_one( expected_pervote_bucket, pervote_bucket ) );
      }

      produce_blocks(5);

      BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
                          push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
   }

   {
      const uint32_t prod_index = 24;
      const auto prod_name = producer_names[prod_index];
      BOOST_REQUIRE_EQUAL(success(),
                          push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
      BOOST_REQUIRE(100 * 10000 <= get_balance(prod_name).get_amount());
      BOOST_REQUIRE_EQUAL(wasm_assert_msg("already claimed rewards within past day"),
                          push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)));
   }

   {
      const uint32_t rmv_index = 5;
      account_name prod_name = producer_names[rmv_index];

      auto info = get_producer_info(prod_name);
      BOOST_REQUIRE( info["is_active"].as<bool>() );
      BOOST_REQUIRE( fc::crypto::public_key() != fc::crypto::public_key(info["producer_key"].as_string()) );

      BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
                           push_action(prod_name, N(rmvproducer), mvo()("producer", prod_name)));
      BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
                           push_action(producer_names[rmv_index + 2], N(rmvproducer), mvo()("producer", prod_name) ) );
      BOOST_REQUIRE_EQUAL( success(),
                           push_action(config::system_account_name, N(rmvproducer), mvo()("producer", prod_name) ) );
      {
         bool rest_didnt_produce = true;
         for (uint32_t i = 21; i < producer_names.size(); ++i) {
            if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
               rest_didnt_produce = false;
            }
         }
         BOOST_REQUIRE(rest_didnt_produce);
      }

      produce_blocks(3 * 21 * 12);
      info = get_producer_info(prod_name);
      const uint32_t init_unpaid_blocks = info["unpaid_blocks"].as<uint32_t>();
      BOOST_REQUIRE( !info["is_active"].as<bool>() );
      BOOST_REQUIRE( fc::crypto::public_key() == fc::crypto::public_key(info["producer_key"].as_string()) );
      BOOST_REQUIRE_EQUAL( wasm_assert_msg("producer does not have an active key"),
                           push_action(prod_name, N(claimrewards), mvo()("owner", prod_name) ) );
      produce_blocks(3 * 21 * 12);
      BOOST_REQUIRE_EQUAL( init_unpaid_blocks, get_producer_info(prod_name)["unpaid_blocks"].as<uint32_t>() );
      {
         bool prod_was_replaced = false;
         for (uint32_t i = 21; i < producer_names.size(); ++i) {
            if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
               prod_was_replaced = true;
            }
         }
         BOOST_REQUIRE(prod_was_replaced);
      }
   }

   {
      BOOST_REQUIRE_EQUAL( wasm_assert_msg("producer not found"),
                           push_action( config::system_account_name, N(rmvproducer), mvo()("producer", "nonexistingp") ) );
   }

   produce_block(fc::hours(24));

   // switch to new producer pay metric
   {
      BOOST_REQUIRE_EQUAL( 0, get_global_state2()["revision"].as<uint8_t>() );
      BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
                           push_action(producer_names[1], N(updtrevision), mvo()("revision", 1) ) );
      BOOST_REQUIRE_EQUAL( success(),
                           push_action(config::system_account_name, N(updtrevision), mvo()("revision", 1) ) );
      BOOST_REQUIRE_EQUAL( 1, get_global_state2()["revision"].as<uint8_t>() );

      const uint32_t prod_index = 2;
      const auto prod_name = producer_names[prod_index];

      const auto     initial_prod_info         = get_producer_info(prod_name);
      const auto     initial_prod_info2        = get_producer_info2(prod_name);
      const auto     initial_global_state      = get_global_state();
      const double   initial_tot_votepay_share = get_global_state2()["total_producer_votepay_share"].as_double();
      const double   initial_tot_vpay_rate     = get_global_state3()["total_vpay_share_change_rate"].as_double();
      const uint64_t initial_vpay_state_update = microseconds_since_epoch_of_iso_string( get_global_state3()["last_vpay_state_update"] );
      const uint64_t initial_bucket_fill_time  = microseconds_since_epoch_of_iso_string( initial_global_state["last_pervote_bucket_fill"] );
      const int64_t  initial_pervote_bucket    = initial_global_state["pervote_bucket"].as<int64_t>();
      const int64_t  initial_perblock_bucket   = initial_global_state["perblock_bucket"].as<int64_t>();
      const uint32_t initial_tot_unpaid_blocks = initial_global_state["total_unpaid_blocks"].as<uint32_t>();
      const asset    initial_supply            = get_token_supply();
      const asset    initial_balance           = get_balance(prod_name);
      const uint32_t initial_unpaid_blocks     = initial_prod_info["unpaid_blocks"].as<uint32_t>();
      const uint64_t initial_claim_time        = microseconds_since_epoch_of_iso_string( initial_prod_info["last_claim_time"] );
      const uint64_t initial_prod_update_time  = microseconds_since_epoch_of_iso_string( initial_prod_info2["last_votepay_share_update"] );

      BOOST_TEST_REQUIRE( 0 == get_producer_info2(prod_name)["votepay_share"].as_double() );
      BOOST_REQUIRE_EQUAL( success(), push_action(prod_name, N(claimrewards), mvo()("owner", prod_name) ) );

      const auto     prod_info         = get_producer_info(prod_name);
      const auto     prod_info2        = get_producer_info2(prod_name);
      const auto     global_state      = get_global_state();
      const uint64_t vpay_state_update = microseconds_since_epoch_of_iso_string( get_global_state3()["last_vpay_state_update"] );
      const uint64_t bucket_fill_time  = microseconds_since_epoch_of_iso_string( global_state["last_pervote_bucket_fill"] );
      const int64_t  pervote_bucket    = global_state["pervote_bucket"].as<int64_t>();
      const int64_t  perblock_bucket   = global_state["perblock_bucket"].as<int64_t>();
      const uint32_t tot_unpaid_blocks = global_state["total_unpaid_blocks"].as<uint32_t>();
      const asset    supply            = get_token_supply();
      const asset    balance           = get_balance(prod_name);
      const uint32_t unpaid_blocks     = prod_info["unpaid_blocks"].as<uint32_t>();
      const uint64_t claim_time        = microseconds_since_epoch_of_iso_string( prod_info["last_claim_time"] );
      const uint64_t prod_update_time  = microseconds_since_epoch_of_iso_string( prod_info2["last_votepay_share_update"] );

      const uint64_t usecs_between_fills         = bucket_fill_time - initial_bucket_fill_time;
      const double   secs_between_global_updates = (vpay_state_update - initial_vpay_state_update) / 1E6;
      const double   secs_between_prod_updates   = (prod_update_time - initial_prod_update_time) / 1E6;
      const double   votepay_share               = initial_prod_info2["votepay_share"].as_double() + secs_between_prod_updates * prod_info["total_votes"].as_double();
      const double   tot_votepay_share           = initial_tot_votepay_share + initial_tot_vpay_rate * secs_between_global_updates;

      const int64_t expected_perblock_bucket = int64_t( double(initial_supply.get_amount()) * double(usecs_between_fills) * (0.25 * cont_rate/ 5.) / usecs_per_year )
         + initial_perblock_bucket;
      const int64_t expected_pervote_bucket  = int64_t( double(initial_supply.get_amount()) * double(usecs_between_fills) * (0.75 * cont_rate/ 5.) / usecs_per_year )
         + initial_pervote_bucket;
      const int64_t from_perblock_bucket = initial_unpaid_blocks * expected_perblock_bucket / initial_tot_unpaid_blocks;
      const int64_t from_pervote_bucket  = int64_t( ( votepay_share * expected_pervote_bucket ) / tot_votepay_share );

      const double expected_supply_growth = initial_supply.get_amount() * double(usecs_between_fills) * cont_rate / usecs_per_year;
      BOOST_REQUIRE_EQUAL( int64_t(expected_supply_growth), supply.get_amount() - initial_supply.get_amount() );
      BOOST_REQUIRE_EQUAL( claim_time, vpay_state_update );
      BOOST_REQUIRE( 100 * 10000 < from_pervote_bucket );
      BOOST_CHECK_EQUAL( expected_pervote_bucket - from_pervote_bucket, pervote_bucket );
      BOOST_CHECK_EQUAL( from_perblock_bucket + from_pervote_bucket, balance.get_amount() - initial_balance.get_amount() );
      BOOST_TEST_REQUIRE( 0 == get_producer_info2(prod_name)["votepay_share"].as_double() );

      produce_block(fc::hours(2));

      BOOST_REQUIRE_EQUAL( wasm_assert_msg("already claimed rewards within past day"),
                           push_action(prod_name, N(claimrewards), mvo()("owner", prod_name) ) );
   }

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(multiple_producer_votepay_share, eosio_system_tester, * boost::unit_test::tolerance(1e-10)) try {

   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   const std::vector<account_name> voters = { N(producvotera), N(producvoterb), N(producvoterc), N(producvoterd) };
   for (const auto& v: voters) {
      create_account_with_resources( v, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
      transfer( config::system_account_name, v, core_sym::from_string("100000000.0000"), config::system_account_name );
      BOOST_REQUIRE_EQUAL(success(), stake(v, core_sym::from_string("30000000.0000"), core_sym::from_string("30000000.0000")) );
   }

   // create accounts {defproducera, defproducerb, ..., defproducerz, abcproducera, ..., defproducern} and register as producers
   std::vector<account_name> producer_names;
   {
      producer_names.reserve('z' - 'a' + 1);
      {
         const std::string root("defproducer");
         for ( char c = 'a'; c <= 'z'; ++c ) {
            producer_names.emplace_back(root + std::string(1, c));
         }
      }
      {
         const std::string root("abcproducer");
         for ( char c = 'a'; c <= 'n'; ++c ) {
            producer_names.emplace_back(root + std::string(1, c));
         }
      }
      setup_producer_accounts(producer_names);
      for (const auto& p: producer_names) {
         BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
         produce_blocks(1);
         ilog( "------ get pro----------" );
         wdump((p));
         BOOST_TEST_REQUIRE(0 == get_producer_info(p)["total_votes"].as_double());
         BOOST_TEST_REQUIRE(0 == get_producer_info2(p)["votepay_share"].as_double());
         BOOST_REQUIRE(0 < microseconds_since_epoch_of_iso_string( get_producer_info2(p)["last_votepay_share_update"] ));
      }
   }

   produce_block( fc::hours(24) );

   // producvotera votes for defproducera ... defproducerj
   // producvoterb votes for defproducera ... defproduceru
   // producvoterc votes for defproducera ... defproducerz
   // producvoterd votes for abcproducera ... abcproducern
   {
      BOOST_TEST_REQUIRE( 0 == get_global_state3()["total_vpay_share_change_rate"].as_double() );
      BOOST_REQUIRE_EQUAL( success(), vote(N(producvotera), vector<account_name>(producer_names.begin(), producer_names.begin()+10)) );
      produce_block( fc::hours(10) );
      BOOST_TEST_REQUIRE( 0 == get_global_state2()["total_producer_votepay_share"].as_double() );
      const auto& init_info  = get_producer_info(producer_names[0]);
      const auto& init_info2 = get_producer_info2(producer_names[0]);
      uint64_t init_update = microseconds_since_epoch_of_iso_string( init_info2["last_votepay_share_update"] );
      double   init_votes  = init_info["total_votes"].as_double();
      BOOST_REQUIRE_EQUAL( success(), vote(N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.begin()+21)) );
      const auto& info  = get_producer_info(producer_names[0]);
      const auto& info2 = get_producer_info2(producer_names[0]);
      BOOST_TEST_REQUIRE( ((microseconds_since_epoch_of_iso_string( info2["last_votepay_share_update"] ) - init_update)/double(1E6)) * init_votes == info2["votepay_share"].as_double() );
      BOOST_TEST_REQUIRE( info2["votepay_share"].as_double() * 10 == get_global_state2()["total_producer_votepay_share"].as_double() );

      BOOST_TEST_REQUIRE( 0 == get_producer_info2(producer_names[11])["votepay_share"].as_double() );
      produce_block( fc::hours(13) );
      BOOST_REQUIRE_EQUAL( success(), vote(N(producvoterc), vector<account_name>(producer_names.begin(), producer_names.begin()+26)) );
      BOOST_REQUIRE( 0 < get_producer_info2(producer_names[11])["votepay_share"].as_double() );
      produce_block( fc::hours(1) );
      BOOST_REQUIRE_EQUAL( success(), vote(N(producvoterd), vector<account_name>(producer_names.begin()+26, producer_names.end())) );
      BOOST_TEST_REQUIRE( 0 == get_producer_info2(producer_names[26])["votepay_share"].as_double() );
   }

   {
      auto proda = get_producer_info( N(defproducera) );
      auto prodj = get_producer_info( N(defproducerj) );
      auto prodk = get_producer_info( N(defproducerk) );
      auto produ = get_producer_info( N(defproduceru) );
      auto prodv = get_producer_info( N(defproducerv) );
      auto prodz = get_producer_info( N(defproducerz) );

      BOOST_REQUIRE (0 == proda["unpaid_blocks"].as<uint32_t>() && 0 == prodz["unpaid_blocks"].as<uint32_t>());

      // check vote ratios
      BOOST_REQUIRE ( 0 < proda["total_votes"].as_double() && 0 < prodz["total_votes"].as_double() );
      BOOST_TEST_REQUIRE( proda["total_votes"].as_double() == prodj["total_votes"].as_double() );
      BOOST_TEST_REQUIRE( prodk["total_votes"].as_double() == produ["total_votes"].as_double() );
      BOOST_TEST_REQUIRE( prodv["total_votes"].as_double() == prodz["total_votes"].as_double() );
      BOOST_TEST_REQUIRE( 2 * proda["total_votes"].as_double() == 3 * produ["total_votes"].as_double() );
      BOOST_TEST_REQUIRE( proda["total_votes"].as_double() ==  3 * prodz["total_votes"].as_double() );
   }

   std::vector<double> vote_shares(producer_names.size());
   {
      double total_votes = 0;
      for (uint32_t i = 0; i < producer_names.size(); ++i) {
         vote_shares[i] = get_producer_info(producer_names[i])["total_votes"].as_double();
         total_votes += vote_shares[i];
      }
      BOOST_TEST_REQUIRE( total_votes == get_global_state()["total_producer_vote_weight"].as_double() );
      BOOST_TEST_REQUIRE( total_votes == get_global_state3()["total_vpay_share_change_rate"].as_double() );
      BOOST_REQUIRE_EQUAL( microseconds_since_epoch_of_iso_string( get_producer_info2(producer_names.back())["last_votepay_share_update"] ),
                           microseconds_since_epoch_of_iso_string( get_global_state3()["last_vpay_state_update"] ) );

      std::for_each( vote_shares.begin(), vote_shares.end(), [total_votes](double& x) { x /= total_votes; } );
      BOOST_TEST_REQUIRE( double(1) == std::accumulate(vote_shares.begin(), vote_shares.end(), double(0)) );
      BOOST_TEST_REQUIRE( double(3./71.) == vote_shares.front() );
      BOOST_TEST_REQUIRE( double(1./71.) == vote_shares.back() );
   }

   std::vector<double> votepay_shares(producer_names.size());
   {
      const auto& gs3 = get_global_state3();
      double total_votepay_shares          = 0;
      double expected_total_votepay_shares = 0;
      for (uint32_t i = 0; i < producer_names.size() ; ++i) {
         const auto& info  = get_producer_info(producer_names[i]);
         const auto& info2 = get_producer_info2(producer_names[i]);
         votepay_shares[i] = info2["votepay_share"].as_double();
         total_votepay_shares          += votepay_shares[i];
         expected_total_votepay_shares += votepay_shares[i];
         expected_total_votepay_shares += info["total_votes"].as_double()
                                           * double( ( microseconds_since_epoch_of_iso_string( gs3["last_vpay_state_update"] )
                                                        - microseconds_since_epoch_of_iso_string( info2["last_votepay_share_update"] )
                                                     ) / 1E6 );
      }
      BOOST_TEST( expected_total_votepay_shares > total_votepay_shares );
      BOOST_TEST_REQUIRE( expected_total_votepay_shares == get_global_state2()["total_producer_votepay_share"].as_double() );
   }

   {
      const uint32_t prod_index = 15;
      const account_name prod_name = producer_names[prod_index];
      const auto& init_info        = get_producer_info(prod_name);
      const auto& init_info2       = get_producer_info2(prod_name);
      BOOST_REQUIRE( 0 < init_info2["votepay_share"].as_double() );
      BOOST_REQUIRE( 0 < microseconds_since_epoch_of_iso_string( init_info2["last_votepay_share_update"] ) );

      BOOST_REQUIRE_EQUAL( success(), push_action(prod_name, N(claimrewards), mvo()("owner", prod_name)) );

      BOOST_TEST_REQUIRE( 0 == get_producer_info2(prod_name)["votepay_share"].as_double() );
      BOOST_REQUIRE_EQUAL( get_producer_info(prod_name)["last_claim_time"].as_string(),
                           get_producer_info2(prod_name)["last_votepay_share_update"].as_string() );
      BOOST_REQUIRE_EQUAL( get_producer_info(prod_name)["last_claim_time"].as_string(),
                           get_global_state3()["last_vpay_state_update"].as_string() );
      const auto& gs3 = get_global_state3();
      double expected_total_votepay_shares = 0;
      for (uint32_t i = 0; i < producer_names.size(); ++i) {
         const auto& info  = get_producer_info(producer_names[i]);
         const auto& info2 = get_producer_info2(producer_names[i]);
         expected_total_votepay_shares += info2["votepay_share"].as_double();
         expected_total_votepay_shares += info["total_votes"].as_double()
                                           * double( ( microseconds_since_epoch_of_iso_string( gs3["last_vpay_state_update"] )
                                                        - microseconds_since_epoch_of_iso_string( info2["last_votepay_share_update"] )
                                                     ) / 1E6 );
      }
      BOOST_TEST_REQUIRE( expected_total_votepay_shares == get_global_state2()["total_producer_votepay_share"].as_double() );
   }

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(votepay_share_invariant, eosio_system_tester, * boost::unit_test::tolerance(1e-10)) try {

   cross_15_percent_threshold();

   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   const std::vector<account_name> accounts = { N(aliceaccount), N(bobbyaccount), N(carolaccount), N(emilyaccount) };
   for (const auto& a: accounts) {
      create_account_with_resources( a, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
      transfer( config::system_account_name, a, core_sym::from_string("1000.0000"), config::system_account_name );
   }
   const auto vota  = accounts[0];
   const auto votb  = accounts[1];
   const auto proda = accounts[2];
   const auto prodb = accounts[3];

   BOOST_REQUIRE_EQUAL( success(), stake( vota, core_sym::from_string("100.0000"), core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), stake( votb, core_sym::from_string("100.0000"), core_sym::from_string("100.0000") ) );

   BOOST_REQUIRE_EQUAL( success(), regproducer( proda ) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( prodb ) );

   BOOST_REQUIRE_EQUAL( success(), vote( vota, { proda } ) );
   BOOST_REQUIRE_EQUAL( success(), vote( votb, { prodb } ) );

   produce_block( fc::hours(25) );

   BOOST_REQUIRE_EQUAL( success(), vote( vota, { proda } ) );
   BOOST_REQUIRE_EQUAL( success(), vote( votb, { prodb } ) );

   produce_block( fc::hours(1) );

   BOOST_REQUIRE_EQUAL( success(), push_action(proda, N(claimrewards), mvo()("owner", proda)) );
   BOOST_TEST_REQUIRE( 0 == get_producer_info2(proda)["votepay_share"].as_double() );

   produce_block( fc::hours(24) );

   BOOST_REQUIRE_EQUAL( success(), vote( vota, { proda } ) );

   produce_block( fc::hours(24) );

   BOOST_REQUIRE_EQUAL( success(), push_action(prodb, N(claimrewards), mvo()("owner", prodb)) );
   BOOST_TEST_REQUIRE( 0 == get_producer_info2(prodb)["votepay_share"].as_double() );

   produce_block( fc::hours(10) );

   BOOST_REQUIRE_EQUAL( success(), vote( votb, { prodb } ) );

   produce_block( fc::hours(16) );

   BOOST_REQUIRE_EQUAL( success(), vote( votb, { prodb } ) );
   produce_block( fc::hours(2) );
   BOOST_REQUIRE_EQUAL( success(), vote( vota, { proda } ) );

   const auto& info  = get_producer_info(prodb);
   const auto& info2 = get_producer_info2(prodb);
   const auto& gs2   = get_global_state2();
   const auto& gs3   = get_global_state3();

   double expected_total_vpay_share = info2["votepay_share"].as_double()
                                       + info["total_votes"].as_double()
                                          * ( microseconds_since_epoch_of_iso_string( gs3["last_vpay_state_update"] )
                                               - microseconds_since_epoch_of_iso_string( info2["last_votepay_share_update"] ) ) / 1E6;

   BOOST_TEST_REQUIRE( expected_total_vpay_share == gs2["total_producer_votepay_share"].as_double() );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(votepay_share_proxy, eosio_system_tester, * boost::unit_test::tolerance(1e-5)) try {

   cross_15_percent_threshold();

   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   const std::vector<account_name> accounts = { N(aliceaccount), N(bobbyaccount), N(carolaccount), N(emilyaccount) };
   for (const auto& a: accounts) {
      create_account_with_resources( a, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
      transfer( config::system_account_name, a, core_sym::from_string("1000.0000"), config::system_account_name );
   }
   const auto alice = accounts[0];
   const auto bob   = accounts[1];
   const auto carol = accounts[2];
   const auto emily = accounts[3];

   // alice becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( alice, N(regproxy), mvo()("proxy", alice)("isproxy", true) ) );
   REQUIRE_MATCHING_OBJECT( proxy( alice ), get_voter_info( alice ) );

   // carol and emily become producers
   BOOST_REQUIRE_EQUAL( success(), regproducer( carol, 1) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( emily, 1) );

   // bob chooses alice as proxy
   BOOST_REQUIRE_EQUAL( success(), stake( bob, core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), stake( alice, core_sym::from_string("150.0000"), core_sym::from_string("150.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( bob, { }, alice ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003")) == get_voter_info(alice)["proxied_vote_weight"].as_double() );

   // alice (proxy) votes for carol
   BOOST_REQUIRE_EQUAL( success(), vote( alice, { carol } ) );
   double total_votes = get_producer_info(carol)["total_votes"].as_double();
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("450.0003")) == total_votes );
   BOOST_TEST_REQUIRE( 0 == get_producer_info2(carol)["votepay_share"].as_double() );
   uint64_t last_update_time = microseconds_since_epoch_of_iso_string( get_producer_info2(carol)["last_votepay_share_update"] );

   produce_block( fc::hours(15) );

   // alice (proxy) votes again for carol
   BOOST_REQUIRE_EQUAL( success(), vote( alice, { carol } ) );
   auto cur_info2 = get_producer_info2(carol);
   double expected_votepay_share = double( (microseconds_since_epoch_of_iso_string( cur_info2["last_votepay_share_update"] ) - last_update_time) / 1E6 ) * total_votes;
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("450.0003")) == get_producer_info(carol)["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( expected_votepay_share == cur_info2["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( expected_votepay_share == get_global_state2()["total_producer_votepay_share"].as_double() );
   last_update_time = microseconds_since_epoch_of_iso_string( cur_info2["last_votepay_share_update"] );
   total_votes      = get_producer_info(carol)["total_votes"].as_double();

   produce_block( fc::hours(40) );

   // bob unstakes
   BOOST_REQUIRE_EQUAL( success(), unstake( bob, core_sym::from_string("10.0002"), core_sym::from_string("10.0001") ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("430.0000")), get_producer_info(carol)["total_votes"].as_double() );

   cur_info2 = get_producer_info2(carol);
   expected_votepay_share += double( (microseconds_since_epoch_of_iso_string( cur_info2["last_votepay_share_update"] ) - last_update_time) / 1E6 ) * total_votes;
   BOOST_TEST_REQUIRE( expected_votepay_share == cur_info2["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( expected_votepay_share == get_global_state2()["total_producer_votepay_share"].as_double() );
   last_update_time = microseconds_since_epoch_of_iso_string( cur_info2["last_votepay_share_update"] );
   total_votes      = get_producer_info(carol)["total_votes"].as_double();

   // carol claims rewards
   BOOST_REQUIRE_EQUAL( success(), push_action(carol, N(claimrewards), mvo()("owner", carol)) );

   produce_block( fc::hours(20) );

   // bob votes for carol
   BOOST_REQUIRE_EQUAL( success(), vote( bob, { carol } ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("430.0000")), get_producer_info(carol)["total_votes"].as_double() );
   cur_info2 = get_producer_info2(carol);
   expected_votepay_share = double( (microseconds_since_epoch_of_iso_string( cur_info2["last_votepay_share_update"] ) - last_update_time) / 1E6 ) * total_votes;
   BOOST_TEST_REQUIRE( expected_votepay_share == cur_info2["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( expected_votepay_share == get_global_state2()["total_producer_votepay_share"].as_double() );

   produce_block( fc::hours(54) );

   // bob votes for carol again
   // carol hasn't claimed rewards in over 3 days
   total_votes = get_producer_info(carol)["total_votes"].as_double();
   BOOST_REQUIRE_EQUAL( success(), vote( bob, { carol } ) );
   BOOST_REQUIRE_EQUAL( get_producer_info2(carol)["last_votepay_share_update"].as_string(),
                        get_global_state3()["last_vpay_state_update"].as_string() );
   BOOST_TEST_REQUIRE( 0 == get_producer_info2(carol)["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( 0 == get_global_state2()["total_producer_votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( 0 == get_global_state3()["total_vpay_share_change_rate"].as_double() );

   produce_block( fc::hours(20) );

   // bob votes for carol again
   // carol still hasn't claimed rewards
   BOOST_REQUIRE_EQUAL( success(), vote( bob, { carol } ) );
   BOOST_REQUIRE_EQUAL(get_producer_info2(carol)["last_votepay_share_update"].as_string(),
                       get_global_state3()["last_vpay_state_update"].as_string() );
   BOOST_TEST_REQUIRE( 0 == get_producer_info2(carol)["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( 0 == get_global_state2()["total_producer_votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( 0 == get_global_state3()["total_vpay_share_change_rate"].as_double() );

   produce_block( fc::hours(24) );

   // carol finally claims rewards
   BOOST_REQUIRE_EQUAL( success(), push_action( carol, N(claimrewards), mvo()("owner", carol) ) );
   BOOST_TEST_REQUIRE( 0           == get_producer_info2(carol)["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( 0           == get_global_state2()["total_producer_votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( total_votes == get_global_state3()["total_vpay_share_change_rate"].as_double() );

   produce_block( fc::hours(5) );

   // alice votes for carol and emily
   // emily hasn't claimed rewards in over 3 days
   last_update_time = microseconds_since_epoch_of_iso_string( get_producer_info2(carol)["last_votepay_share_update"] );
   BOOST_REQUIRE_EQUAL( success(), vote( alice, { carol, emily } ) );
   cur_info2 = get_producer_info2(carol);
   auto cur_info2_emily = get_producer_info2(emily);

   expected_votepay_share = double( (microseconds_since_epoch_of_iso_string( cur_info2["last_votepay_share_update"] ) - last_update_time) / 1E6 ) * total_votes;
   BOOST_TEST_REQUIRE( expected_votepay_share == cur_info2["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( 0                      == cur_info2_emily["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( expected_votepay_share == get_global_state2()["total_producer_votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( get_producer_info(carol)["total_votes"].as_double() ==
                       get_global_state3()["total_vpay_share_change_rate"].as_double() );
   BOOST_REQUIRE_EQUAL( cur_info2["last_votepay_share_update"].as_string(),
                        get_global_state3()["last_vpay_state_update"].as_string() );
   BOOST_REQUIRE_EQUAL( cur_info2_emily["last_votepay_share_update"].as_string(),
                        get_global_state3()["last_vpay_state_update"].as_string() );

   produce_block( fc::hours(10) );

   // bob chooses alice as proxy
   // emily still hasn't claimed rewards
   last_update_time = microseconds_since_epoch_of_iso_string( get_producer_info2(carol)["last_votepay_share_update"] );
   BOOST_REQUIRE_EQUAL( success(), vote( bob, { }, alice ) );
   cur_info2 = get_producer_info2(carol);
   cur_info2_emily = get_producer_info2(emily);

   expected_votepay_share += double( (microseconds_since_epoch_of_iso_string( cur_info2["last_votepay_share_update"] ) - last_update_time) / 1E6 ) * total_votes;
   BOOST_TEST_REQUIRE( expected_votepay_share == cur_info2["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( 0                      == cur_info2_emily["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( expected_votepay_share == get_global_state2()["total_producer_votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( get_producer_info(carol)["total_votes"].as_double() ==
                       get_global_state3()["total_vpay_share_change_rate"].as_double() );
   BOOST_REQUIRE_EQUAL( cur_info2["last_votepay_share_update"].as_string(),
                        get_global_state3()["last_vpay_state_update"].as_string() );
   BOOST_REQUIRE_EQUAL( cur_info2_emily["last_votepay_share_update"].as_string(),
                        get_global_state3()["last_vpay_state_update"].as_string() );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(votepay_share_update_order, eosio_system_tester, * boost::unit_test::tolerance(1e-10)) try {

   cross_15_percent_threshold();

   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   const std::vector<account_name> accounts = { N(aliceaccount), N(bobbyaccount), N(carolaccount), N(emilyaccount) };
   for (const auto& a: accounts) {
      create_account_with_resources( a, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
      transfer( config::system_account_name, a, core_sym::from_string("1000.0000"), config::system_account_name );
   }
   const auto alice = accounts[0];
   const auto bob   = accounts[1];
   const auto carol = accounts[2];
   const auto emily = accounts[3];

   BOOST_REQUIRE_EQUAL( success(), regproducer( carol ) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( emily ) );

   produce_block( fc::hours(24) );

   BOOST_REQUIRE_EQUAL( success(), stake( alice, core_sym::from_string("100.0000"), core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( success(), stake( bob,   core_sym::from_string("100.0000"), core_sym::from_string("100.0000") ) );

   BOOST_REQUIRE_EQUAL( success(), vote( alice, { carol, emily } ) );


   BOOST_REQUIRE_EQUAL( success(), push_action( carol, N(claimrewards), mvo()("owner", carol) ) );
   produce_block( fc::hours(1) );
   BOOST_REQUIRE_EQUAL( success(), push_action( emily, N(claimrewards), mvo()("owner", emily) ) );

   produce_block( fc::hours(3 * 24 + 1) );

   {
      signed_transaction trx;
      set_transaction_headers(trx);

      trx.actions.emplace_back( get_action( config::system_account_name, N(claimrewards), { {carol, config::active_name} },
                                            mvo()("owner", carol) ) );

      std::vector<account_name> prods = { carol, emily };
      trx.actions.emplace_back( get_action( config::system_account_name, N(voteproducer), { {alice, config::active_name} },
                                            mvo()("voter", alice)("proxy", name(0))("producers", prods) ) );

      trx.actions.emplace_back( get_action( config::system_account_name, N(claimrewards), { {emily, config::active_name} },
                                            mvo()("owner", emily) ) );

      trx.sign( get_private_key( carol, "active" ), control->get_chain_id() );
      trx.sign( get_private_key( alice, "active" ), control->get_chain_id() );
      trx.sign( get_private_key( emily, "active" ), control->get_chain_id() );

      push_transaction( trx );
   }

   const auto& carol_info  = get_producer_info(carol);
   const auto& carol_info2 = get_producer_info2(carol);
   const auto& emily_info  = get_producer_info(emily);
   const auto& emily_info2 = get_producer_info2(emily);
   const auto& gs3         = get_global_state3();
   BOOST_REQUIRE_EQUAL( carol_info2["last_votepay_share_update"].as_string(), gs3["last_vpay_state_update"].as_string() );
   BOOST_REQUIRE_EQUAL( emily_info2["last_votepay_share_update"].as_string(), gs3["last_vpay_state_update"].as_string() );
   BOOST_TEST_REQUIRE( 0  == carol_info2["votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( 0  == emily_info2["votepay_share"].as_double() );
   BOOST_REQUIRE( 0 < carol_info["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( carol_info["total_votes"].as_double() == emily_info["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( gs3["total_vpay_share_change_rate"].as_double() == 2 * carol_info["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(votepay_transition, eosio_system_tester, * boost::unit_test::tolerance(1e-10)) try {

   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   const std::vector<account_name> voters = { N(producvotera), N(producvoterb), N(producvoterc), N(producvoterd) };
   for (const auto& v: voters) {
      create_account_with_resources( v, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
      transfer( config::system_account_name, v, core_sym::from_string("100000000.0000"), config::system_account_name );
      BOOST_REQUIRE_EQUAL(success(), stake(v, core_sym::from_string("30000000.0000"), core_sym::from_string("30000000.0000")) );
   }

   // create accounts {defproducera, defproducerb, ..., defproducerz} and register as producers
   std::vector<account_name> producer_names;
   {
      producer_names.reserve('z' - 'a' + 1);
      {
         const std::string root("defproducer");
         for ( char c = 'a'; c <= 'd'; ++c ) {
            producer_names.emplace_back(root + std::string(1, c));
         }
      }
      setup_producer_accounts(producer_names);
      for (const auto& p: producer_names) {
         BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
         BOOST_TEST_REQUIRE(0 == get_producer_info(p)["total_votes"].as_double());
         BOOST_TEST_REQUIRE(0 == get_producer_info2(p)["votepay_share"].as_double());
         BOOST_REQUIRE(0 < microseconds_since_epoch_of_iso_string( get_producer_info2(p)["last_votepay_share_update"] ));
      }
   }

   BOOST_REQUIRE_EQUAL( success(), vote(N(producvotera), vector<account_name>(producer_names.begin(), producer_names.end())) );
   auto* tbl = control->db().find<eosio::chain::table_id_object, eosio::chain::by_code_scope_table>(
                  boost::make_tuple( config::system_account_name,
                                     config::system_account_name,
                                     N(producers2) ) );
   BOOST_REQUIRE( tbl );
   BOOST_REQUIRE( 0 < microseconds_since_epoch_of_iso_string( get_producer_info2("defproducera")["last_votepay_share_update"] ) );

   // const_cast hack for now
   const_cast<chainbase::database&>(control->db()).remove( *tbl );
   tbl = control->db().find<eosio::chain::table_id_object, eosio::chain::by_code_scope_table>(
                  boost::make_tuple( config::system_account_name,
                                     config::system_account_name,
                                     N(producers2) ) );
   BOOST_REQUIRE( !tbl );

   BOOST_REQUIRE_EQUAL( success(), vote(N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.end())) );
   tbl = control->db().find<eosio::chain::table_id_object, eosio::chain::by_code_scope_table>(
            boost::make_tuple( config::system_account_name,
                               config::system_account_name,
                               N(producers2) ) );
   BOOST_REQUIRE( !tbl );
   BOOST_REQUIRE_EQUAL( success(), regproducer(N(defproducera)) );
   BOOST_REQUIRE( microseconds_since_epoch_of_iso_string( get_producer_info(N(defproducera))["last_claim_time"] ) < microseconds_since_epoch_of_iso_string( get_producer_info2(N(defproducera))["last_votepay_share_update"] ) );

   create_account_with_resources( N(defproducer1), config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu );
   BOOST_REQUIRE_EQUAL( success(), regproducer(N(defproducer1)) );
   BOOST_REQUIRE( 0 < microseconds_since_epoch_of_iso_string( get_producer_info(N(defproducer1))["last_claim_time"] ) );
   BOOST_REQUIRE_EQUAL( get_producer_info(N(defproducer1))["last_claim_time"].as_string(),
                        get_producer_info2(N(defproducer1))["last_votepay_share_update"].as_string() );

} FC_LOG_AND_RETHROW()


BOOST_AUTO_TEST_CASE(votepay_transition2, * boost::unit_test::tolerance(1e-10)) try {
   eosio_system_tester t(eosio_system_tester::setup_level::minimal);

   std::string old_contract_core_symbol_name = "SYS"; // Set to core symbol used in contracts::util::system_wasm_old()
   symbol old_contract_core_symbol{::eosio::chain::string_to_symbol_c( 4, old_contract_core_symbol_name.c_str() )};

   auto old_core_from_string = [&]( const std::string& s ) {
      return eosio::chain::asset::from_string(s + " " + old_contract_core_symbol_name);
   };

   t.create_core_token( old_contract_core_symbol );
   t.set_code( config::system_account_name, contracts::util::system_wasm_old() );
   t.set_abi(  config::system_account_name, contracts::util::system_abi_old().data() );
   {
      const auto& accnt = t.control->db().get<account_object,by_name>( config::system_account_name );
      abi_def abi;
      BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
      t.abi_ser.set_abi(abi, eosio_system_tester::abi_serializer_max_time);
   }
   const asset net = old_core_from_string("80.0000");
   const asset cpu = old_core_from_string("80.0000");
   const std::vector<account_name> voters = { N(producvotera), N(producvoterb), N(producvoterc), N(producvoterd) };
   for (const auto& v: voters) {
      t.create_account_with_resources( v, config::system_account_name, old_core_from_string("1.0000"), false, net, cpu );
      t.transfer( config::system_account_name, v, old_core_from_string("100000000.0000"), config::system_account_name );
      BOOST_REQUIRE_EQUAL(t.success(), t.stake(v, old_core_from_string("30000000.0000"), old_core_from_string("30000000.0000")) );
   }

   // create accounts {defproducera, defproducerb, ..., defproducerz} and register as producers
   std::vector<account_name> producer_names;
   {
      producer_names.reserve('z' - 'a' + 1);
      {
         const std::string root("defproducer");
         for ( char c = 'a'; c <= 'd'; ++c ) {
            producer_names.emplace_back(root + std::string(1, c));
         }
      }
     t.setup_producer_accounts( producer_names, old_core_from_string("1.0000"),
                     old_core_from_string("80.0000"), old_core_from_string("80.0000") );
      for (const auto& p: producer_names) {
         BOOST_REQUIRE_EQUAL( t.success(), t.regproducer(p) );
         BOOST_TEST_REQUIRE(0 == t.get_producer_info(p)["total_votes"].as_double());
      }
   }

   BOOST_REQUIRE_EQUAL( t.success(), t.vote(N(producvotera), vector<account_name>(producer_names.begin(), producer_names.end())) );
   t.produce_block( fc::hours(20) );
   BOOST_REQUIRE_EQUAL( t.success(), t.vote(N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.end())) );
   t.produce_block( fc::hours(30) );
   BOOST_REQUIRE_EQUAL( t.success(), t.vote(N(producvoterc), vector<account_name>(producer_names.begin(), producer_names.end())) );
   BOOST_REQUIRE_EQUAL( t.success(), t.push_action(producer_names[0], N(claimrewards), mvo()("owner", producer_names[0])) );
   BOOST_REQUIRE_EQUAL( t.success(), t.push_action(producer_names[1], N(claimrewards), mvo()("owner", producer_names[1])) );
   auto* tbl = t.control->db().find<eosio::chain::table_id_object, eosio::chain::by_code_scope_table>(
                                    boost::make_tuple( config::system_account_name,
                                                       config::system_account_name,
                                                       N(producers2) ) );
   BOOST_REQUIRE( !tbl );

   t.produce_block( fc::hours(2*24) );

   t.deploy_contract( false );

   t.produce_blocks(2);
   t.produce_block( fc::hours(24 + 1) );

   BOOST_REQUIRE_EQUAL( t.success(), t.push_action(producer_names[0], N(claimrewards), mvo()("owner", producer_names[0])) );
   BOOST_TEST_REQUIRE( 0 == t.get_global_state2()["total_producer_votepay_share"].as_double() );
   BOOST_TEST_REQUIRE( t.get_producer_info(producer_names[0])["total_votes"].as_double() == t.get_global_state3()["total_vpay_share_change_rate"].as_double() );

   t.produce_block( fc::hours(5) );

   BOOST_REQUIRE_EQUAL( t.success(), t.regproducer(producer_names[1]) );
   BOOST_TEST_REQUIRE( t.get_producer_info(producer_names[0])["total_votes"].as_double() + t.get_producer_info(producer_names[1])["total_votes"].as_double() ==
                       t.get_global_state3()["total_vpay_share_change_rate"].as_double() );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(producers_upgrade_system_contract, eosio_system_tester) try {
   //install multisig contract
   abi_serializer msig_abi_ser = initialize_multisig();
   auto producer_names = active_and_vote_producers();

   //helper function
   auto push_action_msig = [&]( const account_name& signer, const action_name &name, const variant_object &data, bool auth = true ) -> action_result {
         string action_type_name = msig_abi_ser.get_action_type(name);

         action act;
         act.account = N(eosio.msig);
         act.name = name;
         act.data = msig_abi_ser.variant_to_binary( action_type_name, data, abi_serializer_max_time );

         return base_tester::push_action( std::move(act), auth ? uint64_t(signer) : signer == N(bob111111111) ? N(alice1111111) : N(bob111111111) );
   };
   // test begins
   vector<permission_level> prod_perms;
   for ( auto& x : producer_names ) {
      prod_perms.push_back( { name(x), config::active_name } );
   }

   transaction trx;
   {
      //prepare system contract with different hash (contract differs in one byte)
      auto code = contracts::system_wasm();
      string msg = "producer votes must be unique and sorted";
      auto it = std::search( code.begin(), code.end(), msg.begin(), msg.end() );
      BOOST_REQUIRE( it != code.end() );
      msg[0] = 'P';
      std::copy( msg.begin(), msg.end(), it );

      variant pretty_trx = fc::mutable_variant_object()
         ("expiration", "2020-01-01T00:30")
         ("ref_block_num", 2)
         ("ref_block_prefix", 3)
         ("net_usage_words", 0)
         ("max_cpu_usage_ms", 0)
         ("delay_sec", 0)
         ("actions", fc::variants({
               fc::mutable_variant_object()
                  ("account", name(config::system_account_name))
                  ("name", "setcode")
                  ("authorization", vector<permission_level>{ { config::system_account_name, config::active_name } })
                  ("data", fc::mutable_variant_object() ("account", name(config::system_account_name))
                   ("vmtype", 0)
                   ("vmversion", "0")
                   ("code", bytes( code.begin(), code.end() ))
                  )
                  })
         );
      abi_serializer::from_variant(pretty_trx, trx, get_resolver(), abi_serializer_max_time);
   }

   BOOST_REQUIRE_EQUAL(success(), push_action_msig( N(alice1111111), N(propose), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "upgrade1")
                                                    ("trx",           trx)
                                                    ("requested", prod_perms)
                       )
   );

   // get 15 approvals
   for ( size_t i = 0; i < 14; ++i ) {
      BOOST_REQUIRE_EQUAL(success(), push_action_msig( name(producer_names[i]), N(approve), mvo()
                                                       ("proposer",      "alice1111111")
                                                       ("proposal_name", "upgrade1")
                                                       ("level",         permission_level{ name(producer_names[i]), config::active_name })
                          )
      );
   }

   //should fail
   BOOST_REQUIRE_EQUAL(wasm_assert_msg("transaction authorization failed"),
                       push_action_msig( N(alice1111111), N(exec), mvo()
                                         ("proposer",      "alice1111111")
                                         ("proposal_name", "upgrade1")
                                         ("executer",      "alice1111111")
                       )
   );

   // one more approval
   BOOST_REQUIRE_EQUAL(success(), push_action_msig( name(producer_names[14]), N(approve), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "upgrade1")
                                                    ("level",         permission_level{ name(producer_names[14]), config::active_name })
                          )
   );

   transaction_trace_ptr trace;
   control->applied_transaction.connect([&]( const transaction_trace_ptr& t) { if (t->scheduled) { trace = t; } } );
   BOOST_REQUIRE_EQUAL(success(), push_action_msig( N(alice1111111), N(exec), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "upgrade1")
                                                    ("executer",      "alice1111111")
                       )
   );

   BOOST_REQUIRE( bool(trace) );
   BOOST_REQUIRE_EQUAL( 1, trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, trace->receipt->status );

   produce_blocks( 250 );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(producer_onblock_check, eosio_system_tester) try {

   const asset large_asset = core_sym::from_string("80.0000");
   create_account_with_resources( N(producvotera), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
   create_account_with_resources( N(producvoterb), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );
   create_account_with_resources( N(producvoterc), config::system_account_name, core_sym::from_string("1.0000"), false, large_asset, large_asset );

   // create accounts {defproducera, defproducerb, ..., defproducerz} and register as producers
   std::vector<account_name> producer_names;
   producer_names.reserve('z' - 'a' + 1);
   const std::string root("defproducer");
   for ( char c = 'a'; c <= 'z'; ++c ) {
      producer_names.emplace_back(root + std::string(1, c));
   }
   setup_producer_accounts(producer_names);

   for (auto a:producer_names)
      regproducer(a);

   produce_block(fc::hours(24));

   BOOST_REQUIRE_EQUAL(0, get_producer_info( producer_names.front() )["total_votes"].as<double>());
   BOOST_REQUIRE_EQUAL(0, get_producer_info( producer_names.back() )["total_votes"].as<double>());


   transfer(config::system_account_name, "producvotera", core_sym::from_string("200000000.0000"), config::system_account_name);
   BOOST_REQUIRE_EQUAL(success(), stake("producvotera", core_sym::from_string("70000000.0000"), core_sym::from_string("70000000.0000") ));
   BOOST_REQUIRE_EQUAL(success(), vote( N(producvotera), vector<account_name>(producer_names.begin(), producer_names.begin()+10)));
   BOOST_CHECK_EQUAL( wasm_assert_msg( "cannot undelegate bandwidth until the chain is activated (at least 15% of all tokens participate in voting)" ),
                      unstake( "producvotera", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );

   // give a chance for everyone to produce blocks
   {
      produce_blocks(21 * 12);
      bool all_21_produced = true;
      for (uint32_t i = 0; i < 21; ++i) {
         if (0 == get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            all_21_produced= false;
         }
      }
      bool rest_didnt_produce = true;
      for (uint32_t i = 21; i < producer_names.size(); ++i) {
         if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            rest_didnt_produce = false;
         }
      }
      BOOST_REQUIRE_EQUAL(false, all_21_produced);
      BOOST_REQUIRE_EQUAL(true, rest_didnt_produce);
   }

   {
      const char* claimrewards_activation_error_message = "cannot claim rewards until the chain is activated (at least 15% of all tokens participate in voting)";
      BOOST_CHECK_EQUAL(0, get_global_state()["total_unpaid_blocks"].as<uint32_t>());
      BOOST_REQUIRE_EQUAL(wasm_assert_msg( claimrewards_activation_error_message ),
                          push_action(producer_names.front(), N(claimrewards), mvo()("owner", producer_names.front())));
      BOOST_REQUIRE_EQUAL(0, get_balance(producer_names.front()).get_amount());
      BOOST_REQUIRE_EQUAL(wasm_assert_msg( claimrewards_activation_error_message ),
                          push_action(producer_names.back(), N(claimrewards), mvo()("owner", producer_names.back())));
      BOOST_REQUIRE_EQUAL(0, get_balance(producer_names.back()).get_amount());
   }

   // stake across 15% boundary
   transfer(config::system_account_name, "producvoterb", core_sym::from_string("100000000.0000"), config::system_account_name);
   BOOST_REQUIRE_EQUAL(success(), stake("producvoterb", core_sym::from_string("4000000.0000"), core_sym::from_string("4000000.0000")));
   transfer(config::system_account_name, "producvoterc", core_sym::from_string("100000000.0000"), config::system_account_name);
   BOOST_REQUIRE_EQUAL(success(), stake("producvoterc", core_sym::from_string("2000000.0000"), core_sym::from_string("2000000.0000")));

   BOOST_REQUIRE_EQUAL(success(), vote( N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.begin()+21)));
   BOOST_REQUIRE_EQUAL(success(), vote( N(producvoterc), vector<account_name>(producer_names.begin(), producer_names.end())));

   // give a chance for everyone to produce blocks
   {
      produce_blocks(21 * 12);
      bool all_21_produced = true;
      for (uint32_t i = 0; i < 21; ++i) {
         if (0 == get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            all_21_produced= false;
         }
      }
      bool rest_didnt_produce = true;
      for (uint32_t i = 21; i < producer_names.size(); ++i) {
         if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            rest_didnt_produce = false;
         }
      }
      BOOST_REQUIRE_EQUAL(true, all_21_produced);
      BOOST_REQUIRE_EQUAL(true, rest_didnt_produce);
      BOOST_REQUIRE_EQUAL(success(),
                          push_action(producer_names.front(), N(claimrewards), mvo()("owner", producer_names.front())));
      BOOST_REQUIRE(0 < get_balance(producer_names.front()).get_amount());
   }

   BOOST_CHECK_EQUAL( success(), unstake( "producvotera", core_sym::from_string("50.0000"), core_sym::from_string("50.0000") ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( voters_actions_affect_proxy_and_producers, eosio_system_tester, * boost::unit_test::tolerance(1e+6) ) try {
   cross_15_percent_threshold();

   create_accounts_with_resources( { N(donald111111), N(defproducer1), N(defproducer2), N(defproducer3) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer1", 1) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer2", 2) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer3", 3) );

   //alice1111111 becomes a producer
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //alice1111111 makes stake and votes
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("30.0001"), core_sym::from_string("20.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice1111111), { N(defproducer1), N(defproducer2) } ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("50.0002")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("50.0002")) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   BOOST_REQUIRE_EQUAL( success(), push_action( N(donald111111), N(regproxy), mvo()
                                                ("proxy",  "donald111111")
                                                ("isproxy", true)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "donald111111" ), get_voter_info( "donald111111" ) );

   //bob111111111 chooses alice1111111 as a proxy
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), vector<account_name>(), "alice1111111" ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("150.0003")) == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("200.0005")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("200.0005")) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //carol1111111 chooses alice1111111 as a proxy
   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("30.0001"), core_sym::from_string("20.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), vector<account_name>(), "alice1111111" ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("200.0005")) == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("250.0007")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("250.0007")) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //proxied voter carol1111111 increases stake
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("50.0000"), core_sym::from_string("70.0000") ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("320.0005")) == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("370.0007")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("370.0007")) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //proxied voter bob111111111 decreases stake
   BOOST_REQUIRE_EQUAL( success(), unstake( "bob111111111", core_sym::from_string("50.0001"), core_sym::from_string("50.0001") ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("220.0003")) == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("270.0005")) == get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("270.0005")) == get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //proxied voter carol1111111 chooses another proxy
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), vector<account_name>(), "donald111111" ) );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("50.0001")), get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("170.0002")), get_voter_info( "donald111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("100.0003")), get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("100.0003")), get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_REQUIRE_EQUAL( 0, get_producer_info( "defproducer3" )["total_votes"].as_double() );

   //bob111111111 switches to direct voting and votes for one of the same producers, but not for another one
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer2) } ) );
   BOOST_TEST_REQUIRE( 0.0 == get_voter_info( "alice1111111" )["proxied_vote_weight"].as_double() );
   BOOST_TEST_REQUIRE(  stake2votes(core_sym::from_string("50.0002")), get_producer_info( "defproducer1" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( stake2votes(core_sym::from_string("100.0003")), get_producer_info( "defproducer2" )["total_votes"].as_double() );
   BOOST_TEST_REQUIRE( 0.0 == get_producer_info( "defproducer3" )["total_votes"].as_double() );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( vote_both_proxy_and_producers, eosio_system_tester ) try {
   //alice1111111 becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy", true)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" ), get_voter_info( "alice1111111" ) );

   //carol1111111 becomes a producer
   BOOST_REQUIRE_EQUAL( success(), regproducer( "carol1111111", 1) );

   //bob111111111 chooses alice1111111 as a proxy

   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( wasm_assert_msg("cannot vote for producers and proxy at same time"),
                        vote( N(bob111111111), { N(carol1111111) }, "alice1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( select_invalid_proxy, eosio_system_tester ) try {
   //accumulate proxied votes
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );

   //selecting account not registered as a proxy
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "invalid proxy specified" ),
                        vote( N(bob111111111), vector<account_name>(), "alice1111111" ) );

   //selecting not existing account as a proxy
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "invalid proxy specified" ),
                        vote( N(bob111111111), vector<account_name>(), "notexist" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( double_register_unregister_proxy_keeps_votes, eosio_system_tester ) try {
   //alice1111111 becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy",  1)
                        )
   );
   issue( "alice1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", core_sym::from_string("5.0000"), core_sym::from_string("5.0000") ) );
   edump((get_voter_info("alice1111111")));
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "staked", 100000 ), get_voter_info( "alice1111111" ) );

   //bob111111111 stakes and selects alice1111111 as a proxy
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), vector<account_name>(), "alice1111111" ) );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "proxied_vote_weight", stake2votes( core_sym::from_string("150.0003") ))( "staked", 100000 ), get_voter_info( "alice1111111" ) );

   //double regestering should fail without affecting total votes and stake
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "action has no effect" ),
                        push_action( N(alice1111111), N(regproxy), mvo()
                                     ("proxy",  "alice1111111")
                                     ("isproxy",  1)
                        )
   );
   REQUIRE_MATCHING_OBJECT( proxy( "alice1111111" )( "proxied_vote_weight", stake2votes(core_sym::from_string("150.0003")) )( "staked", 100000 ), get_voter_info( "alice1111111" ) );

   //uregister
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy",  0)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111" )( "proxied_vote_weight", stake2votes(core_sym::from_string("150.0003")) )( "staked", 100000 ), get_voter_info( "alice1111111" ) );

   //double unregistering should not affect proxied_votes and stake
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "action has no effect" ),
                        push_action( N(alice1111111), N(regproxy), mvo()
                                     ("proxy",  "alice1111111")
                                     ("isproxy",  0)
                        )
   );
   REQUIRE_MATCHING_OBJECT( voter( "alice1111111" )( "proxied_vote_weight", stake2votes(core_sym::from_string("150.0003")))( "staked", 100000 ), get_voter_info( "alice1111111" ) );

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( proxy_cannot_use_another_proxy, eosio_system_tester ) try {
   //alice1111111 becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(alice1111111), N(regproxy), mvo()
                                                ("proxy",  "alice1111111")
                                                ("isproxy",  1)
                        )
   );

   //bob111111111 becomes a proxy
   BOOST_REQUIRE_EQUAL( success(), push_action( N(bob111111111), N(regproxy), mvo()
                                                ("proxy",  "bob111111111")
                                                ("isproxy",  1)
                        )
   );

   //proxy should not be able to use a proxy
   issue( "bob111111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "account registered as a proxy is not allowed to use a proxy" ),
                        vote( N(bob111111111), vector<account_name>(), "alice1111111" ) );

   //voter that uses a proxy should not be allowed to become a proxy
   issue( "carol1111111", core_sym::from_string("1000.0000"),  config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), stake( "carol1111111", core_sym::from_string("100.0002"), core_sym::from_string("50.0001") ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(carol1111111), vector<account_name>(), "alice1111111" ) );
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "account that uses a proxy is not allowed to become a proxy" ),
                        push_action( N(carol1111111), N(regproxy), mvo()
                                     ("proxy",  "carol1111111")
                                     ("isproxy",  1)
                        )
   );

   //proxy should not be able to use itself as a proxy
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "cannot proxy to self" ),
                        vote( N(bob111111111), vector<account_name>(), "bob111111111" ) );

} FC_LOG_AND_RETHROW()

fc::mutable_variant_object config_to_variant( const eosio::chain::chain_config& config ) {
   return mutable_variant_object()
      ( "max_block_net_usage", config.max_block_net_usage )
      ( "target_block_net_usage_pct", config.target_block_net_usage_pct )
      ( "max_transaction_net_usage", config.max_transaction_net_usage )
      ( "base_per_transaction_net_usage", config.base_per_transaction_net_usage )
      ( "context_free_discount_net_usage_num", config.context_free_discount_net_usage_num )
      ( "context_free_discount_net_usage_den", config.context_free_discount_net_usage_den )
      ( "max_block_cpu_usage", config.max_block_cpu_usage )
      ( "target_block_cpu_usage_pct", config.target_block_cpu_usage_pct )
      ( "max_transaction_cpu_usage", config.max_transaction_cpu_usage )
      ( "min_transaction_cpu_usage", config.min_transaction_cpu_usage )
      ( "max_transaction_lifetime", config.max_transaction_lifetime )
      ( "deferred_trx_expiration_window", config.deferred_trx_expiration_window )
      ( "max_transaction_delay", config.max_transaction_delay )
      ( "max_inline_action_size", config.max_inline_action_size )
      ( "max_inline_action_depth", config.max_inline_action_depth )
      ( "max_authority_depth", config.max_authority_depth );
}

BOOST_FIXTURE_TEST_CASE( elect_producers /*_and_parameters*/, eosio_system_tester ) try {
   create_accounts_with_resources( {  N(defproducer1), N(defproducer2), N(defproducer3) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer1", 1) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer2", 2) );
   BOOST_REQUIRE_EQUAL( success(), regproducer( "defproducer3", 3) );

   //stake more than 15% of total EOS supply to activate chain
   transfer( "eosio", "alice1111111", core_sym::from_string("600000000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "alice1111111", "alice1111111", core_sym::from_string("300000000.0000"), core_sym::from_string("300000000.0000") ) );
   //vote for producers
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice1111111), { N(defproducer1) } ) );
   produce_blocks(250);
   auto producer_keys = control->head_block_state()->active_schedule.producers;
   BOOST_REQUIRE_EQUAL( 1, producer_keys.size() );
   BOOST_REQUIRE_EQUAL( name("defproducer1"), producer_keys[0].producer_name );

   //auto config = config_to_variant( control->get_global_properties().configuration );
   //auto prod1_config = testing::filter_fields( config, producer_parameters_example( 1 ) );
   //REQUIRE_EQUAL_OBJECTS(prod1_config, config);

   // elect 2 producers
   issue( "bob111111111", core_sym::from_string("80000.0000"),  config::system_account_name );
   ilog("stake");
   BOOST_REQUIRE_EQUAL( success(), stake( "bob111111111", core_sym::from_string("40000.0000"), core_sym::from_string("40000.0000") ) );
   ilog("start vote");
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer2) } ) );
   ilog(".");
   produce_blocks(250);
   producer_keys = control->head_block_state()->active_schedule.producers;
   BOOST_REQUIRE_EQUAL( 2, producer_keys.size() );
   BOOST_REQUIRE_EQUAL( name("defproducer1"), producer_keys[0].producer_name );
   BOOST_REQUIRE_EQUAL( name("defproducer2"), producer_keys[1].producer_name );
   //config = config_to_variant( control->get_global_properties().configuration );
   //auto prod2_config = testing::filter_fields( config, producer_parameters_example( 2 ) );
   //REQUIRE_EQUAL_OBJECTS(prod2_config, config);

   // elect 3 producers
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer2), N(defproducer3) } ) );
   produce_blocks(250);
   producer_keys = control->head_block_state()->active_schedule.producers;
   BOOST_REQUIRE_EQUAL( 3, producer_keys.size() );
   BOOST_REQUIRE_EQUAL( name("defproducer1"), producer_keys[0].producer_name );
   BOOST_REQUIRE_EQUAL( name("defproducer2"), producer_keys[1].producer_name );
   BOOST_REQUIRE_EQUAL( name("defproducer3"), producer_keys[2].producer_name );
   //config = config_to_variant( control->get_global_properties().configuration );
   //REQUIRE_EQUAL_OBJECTS(prod2_config, config);

   // try to go back to 2 producers and fail
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob111111111), { N(defproducer3) } ) );
   produce_blocks(250);
   producer_keys = control->head_block_state()->active_schedule.producers;
   BOOST_REQUIRE_EQUAL( 3, producer_keys.size() );

   // The test below is invalid now, producer schedule is not updated if there are
   // fewer producers in the new schedule
   /*
   BOOST_REQUIRE_EQUAL( 2, producer_keys.size() );
   BOOST_REQUIRE_EQUAL( name("defproducer1"), producer_keys[0].producer_name );
   BOOST_REQUIRE_EQUAL( name("defproducer3"), producer_keys[1].producer_name );
   //config = config_to_variant( control->get_global_properties().configuration );
   //auto prod3_config = testing::filter_fields( config, producer_parameters_example( 3 ) );
   //REQUIRE_EQUAL_OBJECTS(prod3_config, config);
   */

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( buyname, eosio_system_tester ) try {
   create_accounts_with_resources( { N(dan), N(sam) } );
   transfer( config::system_account_name, "dan", core_sym::from_string( "10000.0000" ) );
   transfer( config::system_account_name, "sam", core_sym::from_string( "10000.0000" ) );
   stake_with_transfer( config::system_account_name, "sam", core_sym::from_string( "80000000.0000" ), core_sym::from_string( "80000000.0000" ) );
   stake_with_transfer( config::system_account_name, "dan", core_sym::from_string( "80000000.0000" ), core_sym::from_string( "80000000.0000" ) );

   regproducer( config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), vote( N(sam), { config::system_account_name } ) );
   // wait 14 days after min required amount has been staked
   produce_block( fc::days(7) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(dan), { config::system_account_name } ) );
   produce_block( fc::days(7) );
   produce_block();

   BOOST_REQUIRE_EXCEPTION( create_accounts_with_resources( { N(fail) }, N(dan) ), // dan shouldn't be able to create fail
                            eosio_assert_message_exception, eosio_assert_message_is( "no active bid for name" ) );
   bidname( "dan", "nofail", core_sym::from_string( "1.0000" ) );
   BOOST_REQUIRE_EQUAL( "assertion failure with message: must increase bid by 10%", bidname( "sam", "nofail", core_sym::from_string( "1.0000" ) )); // didn't increase bid by 10%
   BOOST_REQUIRE_EQUAL( success(), bidname( "sam", "nofail", core_sym::from_string( "2.0000" ) )); // didn't increase bid by 10%
   produce_block( fc::days(1) );
   produce_block();

   BOOST_REQUIRE_EXCEPTION( create_accounts_with_resources( { N(nofail) }, N(dan) ), // dan shoudn't be able to do this, sam won
                            eosio_assert_message_exception, eosio_assert_message_is( "only highest bidder can claim" ) );
   //wlog( "verify sam can create nofail" );
   create_accounts_with_resources( { N(nofail) }, N(sam) ); // sam should be able to do this, he won the bid
   //wlog( "verify nofail can create test.nofail" );
   transfer( "eosio", "nofail", core_sym::from_string( "1000.0000" ) );
   create_accounts_with_resources( { N(test.nofail) }, N(nofail) ); // only nofail can create test.nofail
   //wlog( "verify dan cannot create test.fail" );
   BOOST_REQUIRE_EXCEPTION( create_accounts_with_resources( { N(test.fail) }, N(dan) ), // dan shouldn't be able to do this
                            eosio_assert_message_exception, eosio_assert_message_is( "only suffix may create this account" ) );

   create_accounts_with_resources( { N(goodgoodgood) }, N(dan) ); /// 12 char names should succeed
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( bid_invalid_names, eosio_system_tester ) try {
   create_accounts_with_resources( { N(dan) } );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "you can only bid on top-level suffix" ),
                        bidname( "dan", "abcdefg.12345", core_sym::from_string( "1.0000" ) ) );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "the empty name is not a valid account name to bid on" ),
                        bidname( "dan", "", core_sym::from_string( "1.0000" ) ) );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "13 character names are not valid account names to bid on" ),
                        bidname( "dan", "abcdefgh12345", core_sym::from_string( "1.0000" ) ) );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "accounts with 12 character names and no dots can be created without bidding required" ),
                        bidname( "dan", "abcdefg12345", core_sym::from_string( "1.0000" ) ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( multiple_namebids, eosio_system_tester ) try {

   const std::string not_closed_message("auction for name is not closed yet");

   std::vector<account_name> accounts = { N(alice), N(bob), N(carl), N(david), N(eve) };
   create_accounts_with_resources( accounts );
   for ( const auto& a: accounts ) {
      transfer( config::system_account_name, a, core_sym::from_string( "10000.0000" ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "10000.0000" ), get_balance(a) );
   }
   create_accounts_with_resources( { N(producer) } );
   BOOST_REQUIRE_EQUAL( success(), regproducer( N(producer) ) );

   produce_block();
   // stake but but not enough to go live
   stake_with_transfer( config::system_account_name, "bob",  core_sym::from_string( "35000000.0000" ), core_sym::from_string( "35000000.0000" ) );
   stake_with_transfer( config::system_account_name, "carl", core_sym::from_string( "35000000.0000" ), core_sym::from_string( "35000000.0000" ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(bob), { N(producer) } ) );
   BOOST_REQUIRE_EQUAL( success(), vote( N(carl), { N(producer) } ) );

   // start bids
   bidname( "bob",  "prefa", core_sym::from_string("1.0003") );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.9997" ), get_balance("bob") );
   bidname( "bob",  "prefb", core_sym::from_string("1.0000") );
   bidname( "bob",  "prefc", core_sym::from_string("1.0000") );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "9996.9997" ), get_balance("bob") );

   bidname( "carl", "prefd", core_sym::from_string("1.0000") );
   bidname( "carl", "prefe", core_sym::from_string("1.0000") );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.0000" ), get_balance("carl") );

   BOOST_REQUIRE_EQUAL( error("assertion failure with message: account is already highest bidder"),
                        bidname( "bob", "prefb", core_sym::from_string("1.1001") ) );
   BOOST_REQUIRE_EQUAL( error("assertion failure with message: must increase bid by 10%"),
                        bidname( "alice", "prefb", core_sym::from_string("1.0999") ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "9996.9997" ), get_balance("bob") );
   BOOST_REQUIRE_EQUAL( core_sym::from_string( "10000.0000" ), get_balance("alice") );

   // alice outbids bob on prefb
   {
      const asset initial_names_balance = get_balance(N(eosio.names));
      BOOST_REQUIRE_EQUAL( success(),
                           bidname( "alice", "prefb", core_sym::from_string("1.1001") ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9997.9997" ), get_balance("bob") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.8999" ), get_balance("alice") );
      BOOST_REQUIRE_EQUAL( initial_names_balance + core_sym::from_string("0.1001"), get_balance(N(eosio.names)) );
   }

   // david outbids carl on prefd
   {
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.0000" ), get_balance("carl") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "10000.0000" ), get_balance("david") );
      BOOST_REQUIRE_EQUAL( success(),
                           bidname( "david", "prefd", core_sym::from_string("1.9900") ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9999.0000" ), get_balance("carl") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string( "9998.0100" ), get_balance("david") );
   }

   // eve outbids carl on prefe
   {
      BOOST_REQUIRE_EQUAL( success(),
                           bidname( "eve", "prefe", core_sym::from_string("1.7200") ) );
   }

   produce_block( fc::days(14) );
   produce_block();

   // highest bid is from david for prefd but no bids can be closed yet
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefd), N(david) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );

   // stake enough to go above the 15% threshold
   stake_with_transfer( config::system_account_name, "alice", core_sym::from_string( "10000000.0000" ), core_sym::from_string( "10000000.0000" ) );
   BOOST_REQUIRE_EQUAL(0, get_producer_info("producer")["unpaid_blocks"].as<uint32_t>());
   BOOST_REQUIRE_EQUAL( success(), vote( N(alice), { N(producer) } ) );

   // need to wait for 14 days after going live
   produce_blocks(10);
   produce_block( fc::days(2) );
   produce_blocks( 10 );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefd), N(david) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   // it's been 14 days, auction for prefd has been closed
   produce_block( fc::days(12) );
   create_account_with_resources( N(prefd), N(david) );
   produce_blocks(2);
   produce_block( fc::hours(23) );
   // auctions for prefa, prefb, prefc, prefe haven't been closed
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefa), N(bob) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefb), N(alice) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefc), N(bob) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefe), N(eve) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   // attemp to create account with no bid
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefg), N(alice) ),
                            fc::exception, fc_assert_exception_message_is( "no active bid for name" ) );
   // changing highest bid pushes auction closing time by 24 hours
   BOOST_REQUIRE_EQUAL( success(),
                        bidname( "eve",  "prefb", core_sym::from_string("2.1880") ) );

   produce_block( fc::hours(22) );
   produce_blocks(2);

   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefb), N(eve) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   // but changing a bid that is not the highest does not push closing time
   BOOST_REQUIRE_EQUAL( success(),
                        bidname( "carl", "prefe", core_sym::from_string("2.0980") ) );
   produce_block( fc::hours(2) );
   produce_blocks(2);
   // bid for prefb has closed, only highest bidder can claim
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefb), N(alice) ),
                            eosio_assert_message_exception, eosio_assert_message_is( "only highest bidder can claim" ) );
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefb), N(carl) ),
                            eosio_assert_message_exception, eosio_assert_message_is( "only highest bidder can claim" ) );
   create_account_with_resources( N(prefb), N(eve) );

   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefe), N(carl) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );
   produce_block();
   produce_block( fc::hours(24) );
   // by now bid for prefe has closed
   create_account_with_resources( N(prefe), N(carl) );
   // prefe can now create *.prefe
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(xyz.prefe), N(carl) ),
                            fc::exception, fc_assert_exception_message_is("only suffix may create this account") );
   transfer( config::system_account_name, N(prefe), core_sym::from_string("10000.0000") );
   create_account_with_resources( N(xyz.prefe), N(prefe) );

   // other auctions haven't closed
   BOOST_REQUIRE_EXCEPTION( create_account_with_resources( N(prefa), N(bob) ),
                            fc::exception, fc_assert_exception_message_is( not_closed_message ) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( namebid_pending_winner, eosio_system_tester ) try {
   cross_15_percent_threshold();
   produce_block( fc::hours(14*24) );    //wait 14 day for name auction activation
   transfer( config::system_account_name, N(alice1111111), core_sym::from_string("10000.0000") );
   transfer( config::system_account_name, N(bob111111111), core_sym::from_string("10000.0000") );

   BOOST_REQUIRE_EQUAL( success(), bidname( "alice1111111", "prefa", core_sym::from_string( "50.0000" ) ));
   BOOST_REQUIRE_EQUAL( success(), bidname( "bob111111111", "prefb", core_sym::from_string( "30.0000" ) ));
   produce_block( fc::hours(100) ); //should close "perfa"
   produce_block( fc::hours(100) ); //should close "perfb"

   //despite "perfa" account hasn't been created, we should be able to create "perfb" account
   create_account_with_resources( N(prefb), N(bob111111111) );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( vote_producers_in_and_out, eosio_system_tester ) try {

   const asset net = core_sym::from_string("80.0000");
   const asset cpu = core_sym::from_string("80.0000");
   std::vector<account_name> voters = { N(producvotera), N(producvoterb), N(producvoterc), N(producvoterd) };
   for (const auto& v: voters) {
      create_account_with_resources(v, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu);
   }

   // create accounts {defproducera, defproducerb, ..., defproducerz} and register as producers
   std::vector<account_name> producer_names;
   {
      producer_names.reserve('z' - 'a' + 1);
      const std::string root("defproducer");
      for ( char c = 'a'; c <= 'z'; ++c ) {
         producer_names.emplace_back(root + std::string(1, c));
      }
      setup_producer_accounts(producer_names);
      for (const auto& p: producer_names) {
         BOOST_REQUIRE_EQUAL( success(), regproducer(p) );
         produce_blocks(1);
         ilog( "------ get pro----------" );
         wdump((p));
         BOOST_TEST(0 == get_producer_info(p)["total_votes"].as<double>());
      }
   }

   for (const auto& v: voters) {
      transfer( config::system_account_name, v, core_sym::from_string("200000000.0000"), config::system_account_name );
      BOOST_REQUIRE_EQUAL(success(), stake(v, core_sym::from_string("30000000.0000"), core_sym::from_string("30000000.0000")) );
   }

   {
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvotera), vector<account_name>(producer_names.begin(), producer_names.begin()+20)));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterb), vector<account_name>(producer_names.begin(), producer_names.begin()+21)));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterc), vector<account_name>(producer_names.begin(), producer_names.end())));
   }

   // give a chance for everyone to produce blocks
   {
      produce_blocks(23 * 12 + 20);
      bool all_21_produced = true;
      for (uint32_t i = 0; i < 21; ++i) {
         if (0 == get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            all_21_produced = false;
         }
      }
      bool rest_didnt_produce = true;
      for (uint32_t i = 21; i < producer_names.size(); ++i) {
         if (0 < get_producer_info(producer_names[i])["unpaid_blocks"].as<uint32_t>()) {
            rest_didnt_produce = false;
         }
      }
      BOOST_REQUIRE(all_21_produced && rest_didnt_produce);
   }

   {
      produce_block(fc::hours(7));
      const uint32_t voted_out_index = 20;
      const uint32_t new_prod_index  = 23;
      BOOST_REQUIRE_EQUAL(success(), stake("producvoterd", core_sym::from_string("40000000.0000"), core_sym::from_string("40000000.0000")));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterd), { producer_names[new_prod_index] }));
      BOOST_REQUIRE_EQUAL(0, get_producer_info(producer_names[new_prod_index])["unpaid_blocks"].as<uint32_t>());
      produce_blocks(4 * 12 * 21);
      BOOST_REQUIRE(0 < get_producer_info(producer_names[new_prod_index])["unpaid_blocks"].as<uint32_t>());
      const uint32_t initial_unpaid_blocks = get_producer_info(producer_names[voted_out_index])["unpaid_blocks"].as<uint32_t>();
      produce_blocks(2 * 12 * 21);
      BOOST_REQUIRE_EQUAL(initial_unpaid_blocks, get_producer_info(producer_names[voted_out_index])["unpaid_blocks"].as<uint32_t>());
      produce_block(fc::hours(24));
      BOOST_REQUIRE_EQUAL(success(), vote(N(producvoterd), { producer_names[voted_out_index] }));
      produce_blocks(2 * 12 * 21);
      BOOST_REQUIRE(fc::crypto::public_key() != fc::crypto::public_key(get_producer_info(producer_names[voted_out_index])["producer_key"].as_string()));
      BOOST_REQUIRE_EQUAL(success(), push_action(producer_names[voted_out_index], N(claimrewards), mvo()("owner", producer_names[voted_out_index])));
   }

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( setparams, eosio_system_tester ) try {
   //install multisig contract
   abi_serializer msig_abi_ser = initialize_multisig();
   auto producer_names = active_and_vote_producers();

   //helper function
   auto push_action_msig = [&]( const account_name& signer, const action_name &name, const variant_object &data, bool auth = true ) -> action_result {
         string action_type_name = msig_abi_ser.get_action_type(name);

         action act;
         act.account = N(eosio.msig);
         act.name = name;
         act.data = msig_abi_ser.variant_to_binary( action_type_name, data, abi_serializer_max_time );

         return base_tester::push_action( std::move(act), auth ? uint64_t(signer) : signer == N(bob111111111) ? N(alice1111111) : N(bob111111111) );
   };

   // test begins
   vector<permission_level> prod_perms;
   for ( auto& x : producer_names ) {
      prod_perms.push_back( { name(x), config::active_name } );
   }

   eosio::chain::chain_config params;
   params = control->get_global_properties().configuration;
   //change some values
   params.max_block_net_usage += 10;
   params.max_transaction_lifetime += 1;

   transaction trx;
   {
      variant pretty_trx = fc::mutable_variant_object()
         ("expiration", "2020-01-01T00:30")
         ("ref_block_num", 2)
         ("ref_block_prefix", 3)
         ("net_usage_words", 0)
         ("max_cpu_usage_ms", 0)
         ("delay_sec", 0)
         ("actions", fc::variants({
               fc::mutable_variant_object()
                  ("account", name(config::system_account_name))
                  ("name", "setparams")
                  ("authorization", vector<permission_level>{ { config::system_account_name, config::active_name } })
                  ("data", fc::mutable_variant_object()
                   ("params", params)
                  )
                  })
         );
      abi_serializer::from_variant(pretty_trx, trx, get_resolver(), abi_serializer_max_time);
   }

   BOOST_REQUIRE_EQUAL(success(), push_action_msig( N(alice1111111), N(propose), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "setparams1")
                                                    ("trx",           trx)
                                                    ("requested", prod_perms)
                       )
   );

   // get 16 approvals
   for ( size_t i = 0; i < 15; ++i ) {
      BOOST_REQUIRE_EQUAL(success(), push_action_msig( name(producer_names[i]), N(approve), mvo()
                                                       ("proposer",      "alice1111111")
                                                       ("proposal_name", "setparams1")
                                                       ("level",         permission_level{ name(producer_names[i]), config::active_name })
                          )
      );
   }

   transaction_trace_ptr trace;
   control->applied_transaction.connect([&]( const transaction_trace_ptr& t) { if (t->scheduled) { trace = t; } } );
   BOOST_REQUIRE_EQUAL(success(), push_action_msig( N(alice1111111), N(exec), mvo()
                                                    ("proposer",      "alice1111111")
                                                    ("proposal_name", "setparams1")
                                                    ("executer",      "alice1111111")
                       )
   );

   BOOST_REQUIRE( bool(trace) );
   BOOST_REQUIRE_EQUAL( 1, trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, trace->receipt->status );

   produce_blocks( 250 );

   // make sure that changed parameters were applied
   auto active_params = control->get_global_properties().configuration;
   BOOST_REQUIRE_EQUAL( params.max_block_net_usage, active_params.max_block_net_usage );
   BOOST_REQUIRE_EQUAL( params.max_transaction_lifetime, active_params.max_transaction_lifetime );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( setram_effect, eosio_system_tester ) try {

   const asset net = core_sym::from_string("8.0000");
   const asset cpu = core_sym::from_string("8.0000");
   std::vector<account_name> accounts = { N(aliceaccount), N(bobbyaccount) };
   for (const auto& a: accounts) {
      create_account_with_resources(a, config::system_account_name, core_sym::from_string("1.0000"), false, net, cpu);
   }

   {
      const auto name_a = accounts[0];
      transfer( config::system_account_name, name_a, core_sym::from_string("1000.0000") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance(name_a) );
      const uint64_t init_bytes_a = get_total_stake(name_a)["ram_bytes"].as_uint64();
      BOOST_REQUIRE_EQUAL( success(), buyram( name_a, name_a, core_sym::from_string("300.0000") ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance(name_a) );
      const uint64_t bought_bytes_a = get_total_stake(name_a)["ram_bytes"].as_uint64() - init_bytes_a;

      // after buying and selling balance should be 700 + 300 * 0.995 * 0.995 = 997.0075 (actually 997.0074 due to rounding fees up)
      BOOST_REQUIRE_EQUAL( success(), sellram(name_a, bought_bytes_a ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("997.0074"), get_balance(name_a) );
   }

   {
      const auto name_b = accounts[1];
      transfer( config::system_account_name, name_b, core_sym::from_string("1000.0000") );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("1000.0000"), get_balance(name_b) );
      const uint64_t init_bytes_b = get_total_stake(name_b)["ram_bytes"].as_uint64();
      // name_b buys ram at current price
      BOOST_REQUIRE_EQUAL( success(), buyram( name_b, name_b, core_sym::from_string("300.0000") ) );
      BOOST_REQUIRE_EQUAL( core_sym::from_string("700.0000"), get_balance(name_b) );
      const uint64_t bought_bytes_b = get_total_stake(name_b)["ram_bytes"].as_uint64() - init_bytes_b;

      // increase max_ram_size, ram bought by name_b loses part of its value
      BOOST_REQUIRE_EQUAL( wasm_assert_msg("ram may only be increased"),
                           push_action(config::system_account_name, N(setram), mvo()("max_ram_size", 64ll*1024 * 1024 * 1024)) );
      BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
                           push_action(name_b, N(setram), mvo()("max_ram_size", 80ll*1024 * 1024 * 1024)) );
      BOOST_REQUIRE_EQUAL( success(),
                           push_action(config::system_account_name, N(setram), mvo()("max_ram_size", 80ll*1024 * 1024 * 1024)) );

      BOOST_REQUIRE_EQUAL( success(), sellram(name_b, bought_bytes_b ) );
      BOOST_REQUIRE( core_sym::from_string("900.0000") < get_balance(name_b) );
      BOOST_REQUIRE( core_sym::from_string("950.0000") > get_balance(name_b) );
   }

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( ram_inflation, eosio_system_tester ) try {

   const uint64_t init_max_ram_size = 64ll*1024 * 1024 * 1024;

   BOOST_REQUIRE_EQUAL( init_max_ram_size, get_global_state()["max_ram_size"].as_uint64() );
   produce_blocks(20);
   BOOST_REQUIRE_EQUAL( init_max_ram_size, get_global_state()["max_ram_size"].as_uint64() );
   transfer( config::system_account_name, "alice1111111", core_sym::from_string("1000.0000"), config::system_account_name );
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   produce_blocks(3);
   BOOST_REQUIRE_EQUAL( init_max_ram_size, get_global_state()["max_ram_size"].as_uint64() );
   uint16_t rate = 1000;
   BOOST_REQUIRE_EQUAL( success(), push_action( config::system_account_name, N(setramrate), mvo()("bytes_per_block", rate) ) );
   BOOST_REQUIRE_EQUAL( rate, get_global_state2()["new_ram_per_block"].as<uint16_t>() );
   // last time update_ram_supply called is in buyram, num of blocks since then to
   // the block that includes the setramrate action is 1 + 3 = 4.
   // However, those 4 blocks were accumulating at a rate of 0, so the max_ram_size should not have changed.
   BOOST_REQUIRE_EQUAL( init_max_ram_size, get_global_state()["max_ram_size"].as_uint64() );
   // But with additional blocks, it should start accumulating at the new rate.
   uint64_t cur_ram_size = get_global_state()["max_ram_size"].as_uint64();
   produce_blocks(10);
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("100.0000") ) );
   BOOST_REQUIRE_EQUAL( cur_ram_size + 11 * rate, get_global_state()["max_ram_size"].as_uint64() );
   cur_ram_size = get_global_state()["max_ram_size"].as_uint64();
   produce_blocks(5);
   BOOST_REQUIRE_EQUAL( cur_ram_size, get_global_state()["max_ram_size"].as_uint64() );
   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", 100 ) );
   BOOST_REQUIRE_EQUAL( cur_ram_size + 6 * rate, get_global_state()["max_ram_size"].as_uint64() );
   cur_ram_size = get_global_state()["max_ram_size"].as_uint64();
   produce_blocks();
   BOOST_REQUIRE_EQUAL( success(), buyrambytes( "alice1111111", "alice1111111", 100 ) );
   BOOST_REQUIRE_EQUAL( cur_ram_size + 2 * rate, get_global_state()["max_ram_size"].as_uint64() );

   BOOST_REQUIRE_EQUAL( error("missing authority of eosio"),
                        push_action( "alice1111111", N(setramrate), mvo()("bytes_per_block", rate) ) );

   cur_ram_size = get_global_state()["max_ram_size"].as_uint64();
   produce_blocks(10);
   uint16_t old_rate = rate;
   rate = 5000;
   BOOST_REQUIRE_EQUAL( success(), push_action( config::system_account_name, N(setramrate), mvo()("bytes_per_block", rate) ) );
   BOOST_REQUIRE_EQUAL( cur_ram_size + 11 * old_rate, get_global_state()["max_ram_size"].as_uint64() );
   produce_blocks(5);
   BOOST_REQUIRE_EQUAL( success(), buyrambytes( "alice1111111", "alice1111111", 100 ) );
   BOOST_REQUIRE_EQUAL( cur_ram_size + 11 * old_rate + 6 * rate, get_global_state()["max_ram_size"].as_uint64() );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( eosioram_ramusage, eosio_system_tester ) try {
   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( "alice1111111" ) );
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );

   const asset initial_ram_balance = get_balance(N(eosio.ram));
   const asset initial_ramfee_balance = get_balance(N(eosio.ramfee));
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("1000.0000") ) );

   BOOST_REQUIRE_EQUAL( false, get_row_by_account( N(eosio.token), N(alice1111111), N(accounts), symbol{CORE_SYM}.to_symbol_code() ).empty() );

   //remove row
   base_tester::push_action( N(eosio.token), N(close), N(alice1111111), mvo()
                             ( "owner", "alice1111111" )
                             ( "symbol", symbol{CORE_SYM} )
   );
   BOOST_REQUIRE_EQUAL( true, get_row_by_account( N(eosio.token), N(alice1111111), N(accounts), symbol{CORE_SYM}.to_symbol_code() ).empty() );

   auto rlm = control->get_resource_limits_manager();
   auto eosioram_ram_usage = rlm.get_account_ram_usage(N(eosio.ram));
   auto alice_ram_usage = rlm.get_account_ram_usage(N(alice1111111));

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", 2048 ) );

   //make sure that ram was billed to alice, not to eosio.ram
   BOOST_REQUIRE_EQUAL( true, alice_ram_usage < rlm.get_account_ram_usage(N(alice1111111)) );
   BOOST_REQUIRE_EQUAL( eosioram_ram_usage, rlm.get_account_ram_usage(N(eosio.ram)) );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( ram_gift, eosio_system_tester ) try {
   active_and_vote_producers();

   auto rlm = control->get_resource_limits_manager();
   int64_t ram_bytes_orig, net_weight, cpu_weight;
   rlm.get_account_limits( N(alice1111111), ram_bytes_orig, net_weight, cpu_weight );

   /*
    * It seems impossible to write this test, because buyrambytes action doesn't give you exact amount of bytes requested
    *
   //check that it's possible to create account bying required_bytes(2724) + userres table(112) + userres row(160) - ram_gift_bytes(1400)
   create_account_with_resources( N(abcdefghklmn), N(alice1111111), 2724 + 112 + 160 - 1400 );

   //check that one byte less is not enough
   BOOST_REQUIRE_THROW( create_account_with_resources( N(abcdefghklmn), N(alice1111111), 2724 + 112 + 160 - 1400 - 1 ),
                        ram_usage_exceeded );
   */

   //check that stake/unstake keeps the gift
   transfer( "eosio", "alice1111111", core_sym::from_string("1000.0000"), "eosio" );
   BOOST_REQUIRE_EQUAL( success(), stake( "eosio", "alice1111111", core_sym::from_string("200.0000"), core_sym::from_string("100.0000") ) );
   int64_t ram_bytes_after_stake;
   rlm.get_account_limits( N(alice1111111), ram_bytes_after_stake, net_weight, cpu_weight );
   BOOST_REQUIRE_EQUAL( ram_bytes_orig, ram_bytes_after_stake );

   BOOST_REQUIRE_EQUAL( success(), unstake( "eosio", "alice1111111", core_sym::from_string("20.0000"), core_sym::from_string("10.0000") ) );
   int64_t ram_bytes_after_unstake;
   rlm.get_account_limits( N(alice1111111), ram_bytes_after_unstake, net_weight, cpu_weight );
   BOOST_REQUIRE_EQUAL( ram_bytes_orig, ram_bytes_after_unstake );

   uint64_t ram_gift = 1400;

   int64_t ram_bytes;
   BOOST_REQUIRE_EQUAL( success(), buyram( "alice1111111", "alice1111111", core_sym::from_string("1000.0000") ) );
   rlm.get_account_limits( N(alice1111111), ram_bytes, net_weight, cpu_weight );
   auto userres = get_total_stake( N(alice1111111) );
   BOOST_REQUIRE_EQUAL( userres["ram_bytes"].as_uint64() + ram_gift, ram_bytes );

   BOOST_REQUIRE_EQUAL( success(), sellram( "alice1111111", 1024 ) );
   rlm.get_account_limits( N(alice1111111), ram_bytes, net_weight, cpu_weight );
   userres = get_total_stake( N(alice1111111) );
   BOOST_REQUIRE_EQUAL( userres["ram_bytes"].as_uint64() + ram_gift, ram_bytes );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( setabi_bios, TESTER ) try {
   abi_serializer abi_ser(fc::json::from_string( (const char*)contracts::system_abi().data()).template as<abi_def>(), abi_serializer_max_time);
   set_code( config::system_account_name, contracts::bios_wasm() );
   set_abi( config::system_account_name, contracts::bios_abi().data() );
   create_account(N(eosio.token));
   set_abi( N(eosio.token), contracts::token_abi().data() );
   {
      auto res = get_row_by_account( config::system_account_name, config::system_account_name, N(abihash), N(eosio.token) );
      _abi_hash abi_hash;
      auto abi_hash_var = abi_ser.binary_to_variant( "abi_hash", res, abi_serializer_max_time );
      abi_serializer::from_variant( abi_hash_var, abi_hash, get_resolver(), abi_serializer_max_time);
      auto abi = fc::raw::pack(fc::json::from_string( (const char*)contracts::token_abi().data()).template as<abi_def>());
      auto result = fc::sha256::hash( (const char*)abi.data(), abi.size() );

      BOOST_REQUIRE( abi_hash.hash == result );
   }

   set_abi( N(eosio.token), contracts::system_abi().data() );
   {
      auto res = get_row_by_account( config::system_account_name, config::system_account_name, N(abihash), N(eosio.token) );
      _abi_hash abi_hash;
      auto abi_hash_var = abi_ser.binary_to_variant( "abi_hash", res, abi_serializer_max_time );
      abi_serializer::from_variant( abi_hash_var, abi_hash, get_resolver(), abi_serializer_max_time);
      auto abi = fc::raw::pack(fc::json::from_string( (const char*)contracts::system_abi().data()).template as<abi_def>());
      auto result = fc::sha256::hash( (const char*)abi.data(), abi.size() );

      BOOST_REQUIRE( abi_hash.hash == result );
   }
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( setabi, eosio_system_tester ) try {
   set_abi( N(eosio.token), contracts::token_abi().data() );
   {
      auto res = get_row_by_account( config::system_account_name, config::system_account_name, N(abihash), N(eosio.token) );
      _abi_hash abi_hash;
      auto abi_hash_var = abi_ser.binary_to_variant( "abi_hash", res, abi_serializer_max_time );
      abi_serializer::from_variant( abi_hash_var, abi_hash, get_resolver(), abi_serializer_max_time);
      auto abi = fc::raw::pack(fc::json::from_string( (const char*)contracts::token_abi().data()).template as<abi_def>());
      auto result = fc::sha256::hash( (const char*)abi.data(), abi.size() );

      BOOST_REQUIRE( abi_hash.hash == result );
   }

   set_abi( N(eosio.token), contracts::system_abi().data() );
   {
      auto res = get_row_by_account( config::system_account_name, config::system_account_name, N(abihash), N(eosio.token) );
      _abi_hash abi_hash;
      auto abi_hash_var = abi_ser.binary_to_variant( "abi_hash", res, abi_serializer_max_time );
      abi_serializer::from_variant( abi_hash_var, abi_hash, get_resolver(), abi_serializer_max_time);
      auto abi = fc::raw::pack(fc::json::from_string( (const char*)contracts::system_abi().data()).template as<abi_def>());
      auto result = fc::sha256::hash( (const char*)abi.data(), abi.size() );

      BOOST_REQUIRE( abi_hash.hash == result );
   }
} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
