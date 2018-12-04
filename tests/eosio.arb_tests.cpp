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

BOOST_FIXTURE_TEST_CASE( set_env, eosio_arb_tester ) try {
   auto one_day = 86400;
   
   setconfig (
   20, 
   300, 
   now() + 300, 
   now() + (one_day * 10), 
   vector<int64_t>({int64_t(1), int64_t(2), int64_t(3), int64_t(4)}
   ));

   produce_blocks(1);

   auto env = get_config();
   REQUIRE_MATCHING_OBJECT(
      env, 
      mvo()
         ("publisher", eosio::chain::name("eosio.arb"))
         ("max_elected_arbs", uint16_t(20))
         ("election_duration", uint32_t(300))
         ("start_election", uint32_t(now() + 300))
         ("arbitrator_term_length", uint32_t(now() + (one_day * 10)))
         ("fee_structure", vector<int64_t>({int64_t(1), int64_t(2), int64_t(3), int64_t(4)}))
         ("last_time_edited", now())
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