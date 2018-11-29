#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <Runtime/Runtime.h>
#include <iomanip>

#include <fc/variant_object.hpp>
#include "contracts.hpp"
#include "test_symbol.hpp"
#include "eosio.arb_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

BOOST_AUTO_TEST_SUITE(eosio_arb_tests)

/*
Helpers : 

test assets : 
   BOOST_REQUIRE_EQUAL( core_sym::from_string("470.0000"), get_balance( proposer ) );

test expected exception : 
   BOOST_REQUIRE_EXCEPTION( 
      transaction_trace_ptr_function(param), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "expected error msg" )
   );

test matching full object :  warning , if the objects don't match, the error will look ugly, look for the blue Log: line of text for what fails
   REQUIRE_MATCHING_OBJECT(variant_object, mvo()("param", value)("param2", value2));

*/


// BOOST_FIXTURE_TEST_CASE( deposit_system, eosio_arb_tester) try {
// 	asset local_sum = get_balance(N(eosio.arb));
// 	for(uint16_t i = 0; i < test_voters.size(); i++) {
// 		auto deposit_info = get_deposit(test_voters[i].value);
// 		BOOST_REQUIRE_EQUAL(true, deposit_info.is_null());
// 		asset sum = asset::from_string("20.0000 TLOS");
// 		auto voter_balance = get_balance(test_voters[i].value);
		
// 		BOOST_REQUIRE_EQUAL(voter_balance, asset::from_string("200.0000 TLOS"));
// 		std::cout << "transfer " << "1" << " account " << i << std::endl;
// 		transfer(test_voters[i].value, N(eosio.arb), sum, "arb deposit");
// 		produce_blocks( 2 );
// 		auto contract_balance = get_balance(N(eosio.arb));
// 		BOOST_REQUIRE_EQUAL(contract_balance, local_sum + sum);
// 		local_sum += sum;

// 		deposit_info = get_deposit(test_voters[i].value);
// 		REQUIRE_MATCHING_OBJECT(deposit_info, mvo()
// 			("owner", test_voters[i].to_string())
// 			("escrow", sum.to_string())
// 		);
// 		std::cout << "transfer " << " 2 " << " account " << i << std::endl;
// 		transfer(test_voters[i].value, N(eosio.arb), sum, "WPS depost");
// 		produce_blocks( 2 );
// 		contract_balance = get_balance(N(eosio.arb));
// 		BOOST_REQUIRE_EQUAL(contract_balance, (local_sum + sum));
// 		local_sum += sum;

// 		deposit_info = get_deposit(test_voters[i].value);
// 		REQUIRE_MATCHING_OBJECT(deposit_info, mvo()
// 			("owner", test_voters[i].to_string())
// 			("escrow", (sum + sum).to_string())
// 		);

// 		asset pre_refund = get_balance(test_voters[i].value);
// 		asset escrow = asset::from_string(get_deposit(test_voters[i].value)["escrow"].as_string());
// 		getdeposit(test_voters[i].value);
//             local_sum -= escrow;
// 		asset post_refund = get_balance(test_voters[i].value);

// 		BOOST_REQUIRE_EQUAL((pre_refund + escrow), post_refund);
// 	}
// } FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( set_env, eosio_arb_tester ) try {
   setconfig(1111, 2222222, vector<int64_t>({int64_t(1), int64_t(2), int64_t(3), int64_t(4)}));
   produce_blocks(1);

   auto env = get_config();
   REQUIRE_MATCHING_OBJECT(
      env, 
      mvo()
         ("publisher", eosio::chain::name("eosio.arb"))
         ("max_arbs", uint16_t(1111))
         ("default_time", uint32_t(2222222))
         ("fee_structure", vector<int64_t>({int64_t(1), int64_t(2), int64_t(3), int64_t(4)}))
   );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( apply_cancel_for_arb, eosio_arb_tester ) try {
   name candidate1 = test_voters[0];
   wdump((get_candidate(candidate1.value)));
   wdump((candidate1));

   applyforarb(candidate1, std::string("/ipfs/53CharacterLongHashToSatisfyIPFSHashCondition0/"));
   auto candidate = get_candidate(candidate1.value);
   BOOST_REQUIRE_EQUAL( candidate["cand_name"].as<name>(), candidate1 );
   BOOST_REQUIRE_EQUAL( candidate["credential_link"],  std::string("/ipfs/53CharacterLongHashToSatisfyIPFSHashCondition0/") );

   BOOST_REQUIRE_EXCEPTION( 
      applyforarb(candidate1, "/ipfs/53CharacterLongHashToSatisfyIPFSHashCondition1/"), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate is already an applicant" )
   );

   cancelarbapp(candidate1);
   
   applyforarb(candidate1, std::string("/ipfs/53CharacterLongHashToSatisfyIPFSHashCondition1/"));
   candidate = get_candidate(candidate1.value);
   BOOST_REQUIRE_EQUAL( candidate["cand_name"].as<name>(), candidate1 );
   BOOST_REQUIRE_EQUAL( candidate["credential_link"],  std::string("/ipfs/53CharacterLongHashToSatisfyIPFSHashCondition1/") );
} FC_LOG_AND_RETHROW()


BOOST_AUTO_TEST_SUITE_END()