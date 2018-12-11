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

BOOST_FIXTURE_TEST_CASE( check_config_setter, eosio_arb_tester ) try {
   auto one_day = 86400;
   uint32_t 
      start_election = 300, 
      election_duration = 300, 
      arbitrator_term_length = one_day * 10;
   vector<int64_t> 
      fees = {int64_t(1), int64_t(2), int64_t(3), int64_t(4)};
   uint16_t 
      max_elected_arbs = 20;

   produce_blocks(1);
   // setup config
   setconfig ( max_elected_arbs, start_election, election_duration, arbitrator_term_length, fees);
   produce_blocks(1);

   auto config = get_config();
   REQUIRE_MATCHING_OBJECT(
      config, 
      mvo()
         ("publisher", eosio::chain::name("eosio.arb"))
         ("max_elected_arbs", max_elected_arbs)
         ("election_duration", election_duration)
         ("start_election", start_election)
         ("fee_structure", vector<int64_t>({int64_t(1), int64_t(2), int64_t(3), int64_t(4)}))
         ("arbitrator_term_length", uint32_t(one_day * 10))
         ("last_time_edited", now())
         ("ballot_id", 0)
         ("auto_start_election", false)
   );

   init_election();
   produce_blocks(1);
   produce_block(fc::seconds(start_election + election_duration));
   produce_blocks(1);
   regcand(test_voters[0], "12345678901234567890123456789012345678901234567890123");
   endelection(test_voters[0]);
   produce_blocks(1);

   max_elected_arbs--;
   start_election++;
   election_duration++;
   arbitrator_term_length++;
   setconfig ( max_elected_arbs, start_election, election_duration, arbitrator_term_length, fees);
   produce_blocks(1);

   config = get_config();
   REQUIRE_MATCHING_OBJECT(
      config, 
      mvo()
         ("publisher", eosio::chain::name("eosio.arb"))
         ("max_elected_arbs", max_elected_arbs)
         ("election_duration", election_duration)
         ("start_election", start_election)
         ("fee_structure", vector<int64_t>({int64_t(1), int64_t(2), int64_t(3), int64_t(4)}))
         ("arbitrator_term_length", uint32_t(one_day * 10 + 1))
         ("last_time_edited", now())
         ("ballot_id", 1)
         ("auto_start_election", true)
   );
   produce_blocks(1);
   
   // cannot init another election while one is in progress
   BOOST_REQUIRE_EXCEPTION( 
      init_election(),
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Election is on auto start mode." )
   );

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( init_election_integrity, eosio_arb_tester ) try {
   auto one_day = 86400;
   uint32_t 
      start_election = 300, 
      election_duration = 300, 
      arbitrator_term_length = one_day * 10;
   vector<int64_t> 
      fees = {int64_t(1), int64_t(2), int64_t(3), int64_t(4)};
   uint16_t 
      max_elected_arbs = 20;

   // setup config
   setconfig ( max_elected_arbs, start_election, election_duration, arbitrator_term_length, fees);
   produce_blocks(1);
   
   init_election();
   uint32_t expected_begin_time = uint32_t(now() + start_election);
   uint32_t expected_end_time = expected_begin_time + election_duration;
   produce_blocks(1);

   auto config = get_config();
   auto cbid = config["ballot_id"].as_uint64();   

   auto ballot = get_ballot(cbid);
   auto bid = ballot["reference_id"].as_uint64();

   auto leaderboard = get_leaderboard(bid);
   auto lid = leaderboard["board_id"].as_uint64();

   BOOST_REQUIRE_EQUAL(expected_begin_time, leaderboard["begin_time"].as<uint32_t>());
   BOOST_REQUIRE_EQUAL(expected_end_time, leaderboard["end_time"].as<uint32_t>());

   // exceptions : "ballot doesn't exist" and "leaderboard doesn't exist" mean the following checks should fail
      // if they didn't yet got the error, check the code - can't check here
   // verify correct assignments of available primary keys
   BOOST_REQUIRE_EQUAL(bid, lid);
   BOOST_REQUIRE_EQUAL(cbid, lid);

   // cannot init another election while one is in progress
   BOOST_REQUIRE_EXCEPTION( 
      init_election(),
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Election is on auto start mode." )
   );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( register_unregister_endelection, eosio_arb_tester ) try {
   auto one_day = 86400;
   uint32_t start_election = 300, election_duration = 300, arbitrator_term_length = one_day * 10;
   vector<int64_t> fees = {int64_t(1), int64_t(2), int64_t(3), int64_t(4)};
   uint16_t max_elected_arbs = 20;

   // setup config
   setconfig ( max_elected_arbs, start_election, election_duration, arbitrator_term_length, fees);
   produce_blocks(1);
   
   // choose 1 candidate
   name voter = test_voters[0];
   name candidate = test_voters[1];
   name dropout = test_voters[2];
   name noncandidate = test_voters[3];

   std::string credentials = std::string("/ipfs/53CharacterLongHashToSatisfyIPFSHashCondition1/");

   // candidates cannot register without an election
   regcand(candidate, credentials);
   BOOST_REQUIRE_EXCEPTION( 
      candaddlead(candidate, credentials), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "ballot doesn't exist" )
   );

   auto config = get_config();
   BOOST_REQUIRE_EQUAL(false, config["auto_start_election"]);

   // start an election
   init_election();
   produce_blocks(1);

   BOOST_REQUIRE_EXCEPTION( 
      candrmvlead(candidate), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "candidate not found in leaderboard list" )
   );

   config = get_config();
   BOOST_REQUIRE_EQUAL(true, config["auto_start_election"]);
   
   BOOST_REQUIRE_EXCEPTION( 
      candaddlead( dropout, credentials ), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate isn't an applicant. Use regcand action to register candidate" )
   );

   // register 
   candaddlead( candidate, credentials );
   regcand( dropout, credentials );
   candaddlead( dropout, credentials );
   produce_blocks(1);

   // check integrity
   auto c = get_candidate(dropout.value);
   BOOST_REQUIRE_EQUAL( c["cand_name"].as<name>(), dropout );
   BOOST_REQUIRE_EQUAL( c["credential_link"],  credentials );
   
   c = get_candidate(candidate.value);
   BOOST_REQUIRE_EQUAL( c["cand_name"].as<name>(), candidate );
   BOOST_REQUIRE_EQUAL( c["credential_link"],  credentials );

   // dropout unregisters
   candrmvlead( dropout );
   unregcand( dropout );
   // candidate unregisters
   candrmvlead( candidate );
   unregcand( candidate );
   produce_blocks(1);

   // check dropout is not a candidate anymore
   c = get_candidate(dropout.value);
   BOOST_REQUIRE_EQUAL(true, c.is_null());
   c = get_candidate(candidate.value);
   BOOST_REQUIRE_EQUAL(true, c.is_null());
   
   // candidate registers back
   regcand( candidate, credentials );
   candaddlead( candidate, credentials );
   c = get_candidate(candidate.value);
   BOOST_REQUIRE_EQUAL( c["cand_name"].as<name>(), candidate );
   BOOST_REQUIRE_EQUAL( c["credential_link"],  credentials );
   produce_blocks(1);

   // candidates cannot register multiple times
   BOOST_REQUIRE_EXCEPTION( 
      regcand(candidate, credentials), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate is already an applicant" )
   );

   // dropout cannot unregister multiple times
   BOOST_REQUIRE_EXCEPTION( 
      unregcand(dropout), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate isn't an applicant" )
   );

   BOOST_REQUIRE_EXCEPTION( 
      candrmvlead(dropout), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate isn't an applicant." )
   );
   
   // start the election period
   produce_block(fc::seconds(start_election));
   produce_blocks(1);
   
   // candidates cannot unregister during election
   BOOST_REQUIRE_EXCEPTION( 
      unregcand(candidate), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Cannot unregister while election is in progress" )
   );
   BOOST_REQUIRE_EXCEPTION( 
      candrmvlead(candidate), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "cannot remove candidates once voting has begun" )
   );
   
   // new candidates can register while an election is ongoing
   regcand(dropout, credentials);

   // but they cannot unregister during election even if they are not part of it
   BOOST_REQUIRE_EXCEPTION( 
      unregcand(dropout), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Cannot unregister while election is in progress" )
   );

   config = get_config();
   auto cbid = config["ballot_id"].as_uint64();   

   // vote for candidate
   symbol vote_symbol = symbol(4, "VOTE");
   register_voters(test_voters, 0, 1, vote_symbol);
   mirrorcast(voter.value, symbol(4, "TLOS"));
   castvote(voter.value, config["ballot_id"].as_uint64(), 0);
   produce_blocks(1);

   auto ballot = get_ballot(cbid);
   auto bid = ballot["reference_id"].as_uint64();

   auto leaderboard = get_leaderboard(bid);
   auto lid = leaderboard["board_id"].as_uint64();

   // election cannot end while in progress
   uint32_t remaining_seconds = uint32_t( leaderboard["end_time"].as<uint32_t>() - now() );
   BOOST_REQUIRE_EXCEPTION( 
      endelection(candidate), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "election isn't ended. Please check again in " + std::to_string( remaining_seconds ) + " seconds" )
   );

   // election period is over
   produce_block(fc::seconds(election_duration));
   produce_blocks(1);

   // non-candidates cannot end the election
   BOOST_REQUIRE_EXCEPTION( 
      endelection(voter), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate isn't an applicant." )
   );
   produce_blocks(1);

   config = get_config();
   cbid = config["ballot_id"].as_uint64();   

   uint32_t expected_term_length = now() + arbitrator_term_length;

   // candidates that have NOT participated in the election CAN end it
   endelection(candidate); 
   produce_blocks(1);

   // the single candidate passes
   // so, candidate should be an arbitrator
   // and candidate is removed from the pending_candidates_table
   c = get_candidate(candidate.value);
   BOOST_REQUIRE_EQUAL(true, c.is_null());

   auto arb = get_arbitrator(candidate.value);
   uint16_t UNAVAILABLE_STATUS = 1;
   BOOST_REQUIRE_EQUAL(false, arb.is_null());
   BOOST_REQUIRE_EQUAL(arb["arb"].as<name>(), candidate);
   BOOST_REQUIRE_EQUAL(arb["arb_status"].as<uint16_t>(), UNAVAILABLE_STATUS);
   BOOST_REQUIRE_EQUAL(arb["credential_link"].as<std::string>(), credentials);
   BOOST_REQUIRE_EQUAL(arb["term_length"].as<uint32_t>(), expected_term_length);
   // candidate is not in the candidates table anymore
   BOOST_REQUIRE_EQUAL(true, get_candidate(candidate.value).is_null());
   
   config = get_config();
   auto next_cbid = config["ballot_id"].as_uint64();   

   BOOST_REQUIRE_EQUAL(true, config["auto_start_election"]);

   // election will start automatically because dropout reged mid-election
   BOOST_REQUIRE_NE(cbid, next_cbid);

   config = get_config();
   cbid = config["ballot_id"].as_uint64();   

   ballot = get_ballot(cbid);
   bid = ballot["reference_id"].as_uint64();

   leaderboard = get_leaderboard(bid);
   lid = leaderboard["board_id"].as_uint64();

   // dropout is part of the new election
   BOOST_REQUIRE_EQUAL((get_leaderboard(lid)["candidates"].as<vector<mvo>>()[0])["member"].as<name>(), dropout);

   // start the election period
   produce_block(fc::seconds(start_election));
   produce_blocks(1);
   
   // election period is over
   produce_block(fc::seconds(election_duration));
   produce_blocks(1);

   // arbitrators cannot end elections
   BOOST_REQUIRE_EXCEPTION( 
      endelection(candidate), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate isn't an applicant." )
   );
   produce_blocks(1);

   produce_block(fc::seconds(arbitrator_term_length - start_election - election_duration - 10));
   produce_blocks(1);

   endelection(dropout); 
   expected_term_length = now() + arbitrator_term_length;
   produce_blocks(1);

   config = get_config();
   cbid = next_cbid;
   next_cbid = config["ballot_id"].as_uint64();   

   BOOST_REQUIRE_EQUAL(true, config["auto_start_election"]);

   // election will start automatically because dropout had no votes
   BOOST_REQUIRE_NE(cbid, next_cbid);
   produce_blocks(1);

   // arbitrators with a valid seat cannot register for election
   BOOST_REQUIRE_EXCEPTION( 
      regcand(candidate, credentials), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate is already an Arbitrator and the seat isn't expired" )
   );

   // let the term expire
   produce_block(fc::seconds(10));
   produce_blocks(1);

   // arbitrators with expired terms can join the election
   regcand(candidate, credentials);
   candaddlead(candidate, credentials);
   produce_blocks(1);

   arb = get_arbitrator(candidate);
   uint16_t SEAT_EXPIRED_STATUS = 3;
   BOOST_REQUIRE_EQUAL(false, arb.is_null());
   BOOST_REQUIRE_EQUAL(arb["arb_status"], SEAT_EXPIRED_STATUS);
   
   config = get_config();
   cbid = config["ballot_id"].as_uint64();   

   ballot = get_ballot(cbid);
   bid = ballot["reference_id"].as_uint64();

   leaderboard = get_leaderboard(bid);
   lid = leaderboard["board_id"].as_uint64();

   // dropout and the expired arbitrator are part of the new election
   BOOST_REQUIRE_EQUAL(get_leaderboard(lid)["candidates"].size(), 2);
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( full_election, eosio_arb_tester ) try {
   auto one_day = 86400;
   uint32_t 
      start_election = 300, 
      election_duration = 300, 
      arbitrator_term_length = one_day * 10;
   vector<int64_t> 
      fees = {int64_t(1), int64_t(2), int64_t(3), int64_t(4)};
   uint16_t 
      max_elected_arbs = 2;

   // setup config
   setconfig ( max_elected_arbs, start_election, election_duration, arbitrator_term_length, fees);
   produce_blocks(1);

   // initialize election
   init_election();
   produce_blocks(1);

   // prepare voters
   symbol vote_symbol = symbol(4, "VOTE");
   register_voters(test_voters, 5, 30, vote_symbol);

   // choose 3 candidates
   name candidate1 = test_voters[0];
   name candidate2 = test_voters[1];
   name candidate3 = test_voters[2];
   name noncandidate = test_voters[3];

   std::string credentials = std::string("/ipfs/53CharacterLongHashToSatisfyIPFSHashCondition1/");

   // register and verifiy integrity of candidate info
   for(int i = 0; i <= 2; i++){
      // register 
      regcand( test_voters[i], credentials);
      candaddlead( test_voters[i], credentials);
      produce_blocks(1);
   }

   // ensure candidates that unreg + reg after initelection will be votable
   // note for the continuation of the test :
   // unreg + rereg will put the candidate at the end of the leaderboard queue 
   candrmvlead(candidate3);
   unregcand(candidate3);
   produce_blocks(1);
   regcand(candidate3, credentials);
   candaddlead(candidate3, credentials);
   produce_blocks(1);

   // start the election period
   produce_block(fc::seconds(start_election));
   produce_blocks(1);

   // prepare for vote weight checking 
   asset weight = asset::from_string("200.0000 VOTE"), zero_asset = asset::from_string("0.0000 VOTE");
   vector<asset> expected_weights = {zero_asset, zero_asset, zero_asset};
   auto config = get_config();
   auto cbid = config["ballot_id"].as_uint64();   

   auto ballot = get_ballot(cbid);
   auto bid = ballot["reference_id"].as_uint64();

   //cast 6 votes
   for(int i = 5; i < 11; i++) {
      mirrorcast(test_voters[i].value, symbol(4, "TLOS"));
  
      // everyone votes candidate1 => the direction is actually candidate index for leaderboard voting
      uint16_t vote_for_candidate = 0;      
      castvote(test_voters[i].value, config["ballot_id"].as_uint64(), vote_for_candidate);
      expected_weights[vote_for_candidate] += weight;

      // todo : recast vote test ??

      // other vote :
      // every 3rd voter votes for candidate3 and others vote for candidate2
      vote_for_candidate = ( i % 3 == 0 ) ? uint16_t(2) : uint16_t(1);
      castvote(test_voters[i].value, config["ballot_id"].as_uint64(), vote_for_candidate);
      expected_weights[vote_for_candidate] += weight;

      produce_blocks(1);
   }

   // verify votes
   BOOST_REQUIRE_EQUAL(expected_weights[0], asset::from_string("1200.0000 VOTE"));
   BOOST_REQUIRE_EQUAL(expected_weights[1], asset::from_string("800.0000 VOTE"));
   BOOST_REQUIRE_EQUAL(expected_weights[2], asset::from_string("400.0000 VOTE"));

   auto leaderboard = get_leaderboard(bid);
   auto lid = leaderboard["board_id"].as_uint64();

   for(int i = 0 ; i < 3 ; i++){
      REQUIRE_MATCHING_OBJECT(
         leaderboard["candidates"][i], 
         mvo()
            ("member", test_voters[i])
            ("info_link", credentials)
            ("votes", expected_weights[i])
            ("status", uint8_t(0))
      );
   }
   
   // election period is over
   produce_block(fc::seconds(election_duration));
   produce_blocks(1);

   config = get_config();
   cbid = config["ballot_id"].as_uint64();   

   // end the election
   endelection(candidate1);
   uint32_t expected_term_length = now() + arbitrator_term_length;
   produce_blocks(1);

   // candidate1 should be arbitrator and not a candidate anymore
   auto arb = get_arbitrator(candidate1.value);
   uint16_t UNAVAILABLE_STATUS = 1;
   BOOST_REQUIRE_EQUAL(false, arb.is_null());
   BOOST_REQUIRE_EQUAL(arb["arb"].as<name>(), candidate1);
   BOOST_REQUIRE_EQUAL(arb["arb_status"].as<uint16_t>(), UNAVAILABLE_STATUS);
   BOOST_REQUIRE_EQUAL(arb["credential_link"].as<std::string>(), credentials);
   BOOST_REQUIRE_EQUAL(arb["term_length"].as<uint32_t>(), expected_term_length);
   auto c = get_candidate(candidate1.value);
   BOOST_REQUIRE_EQUAL(c.is_null(), true);
   
   // candidate2 should be arbitrator and not a candidate anymore
   arb = get_arbitrator(candidate2.value);
   BOOST_REQUIRE_EQUAL(false, arb.is_null());
   BOOST_REQUIRE_EQUAL(arb["arb"].as<name>(), candidate2);
   BOOST_REQUIRE_EQUAL(arb["arb_status"].as<uint16_t>(), UNAVAILABLE_STATUS);
   BOOST_REQUIRE_EQUAL(arb["credential_link"].as<std::string>(), credentials);
   BOOST_REQUIRE_EQUAL(arb["term_length"].as<uint32_t>(), expected_term_length);
   c = get_candidate(candidate2.value);
   BOOST_REQUIRE_EQUAL(c.is_null(), true);

   // candidate3 should NOT be an arbitrator, only 2 seats were available
   arb = get_arbitrator(candidate3.value);
   BOOST_REQUIRE_EQUAL(true, arb.is_null());
   // candidate3 will be removed as a candidate because there are no more seats available , and no new election will start
   c = get_candidate(candidate3.value);
   BOOST_REQUIRE_EQUAL(c.is_null(), true);

   auto previous_cbid = cbid;
   
   config = get_config();
   cbid = config["ballot_id"].as_uint64();   

   ballot = get_ballot(cbid);
   bid = ballot["reference_id"].as_uint64();

   leaderboard = get_leaderboard(bid);
   lid = leaderboard["board_id"].as_uint64();

   // there is no new election in progress since no seats are left
   BOOST_REQUIRE_EQUAL(cbid, previous_cbid);
   BOOST_REQUIRE_EQUAL(false, config["auto_start_election"]);

   produce_blocks(1);

   BOOST_REQUIRE_EXCEPTION( 
      candaddlead(noncandidate, credentials),
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Candidate isn't an applicant. Use regcand action to register candidate" )
   );

   regcand(noncandidate, credentials);
   produce_blocks(1);

   BOOST_REQUIRE_EXCEPTION( 
      candaddlead(noncandidate, credentials),
      eosio_assert_message_exception, 
      eosio_assert_message_is( "A new election hasn't started. Use initelection action to start a new election." )
   );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( tiebreaker, eosio_arb_tester ) try {
   auto one_day = 86400;
   uint32_t 
      start_election = 300, 
      election_duration = 300, 
      arbitrator_term_length = one_day * 10;
   vector<int64_t> 
      fees = {int64_t(1), int64_t(2), int64_t(3), int64_t(4)};
   uint16_t 
      max_elected_arbs = 2;

   // setup config
   setconfig ( max_elected_arbs, start_election, election_duration, arbitrator_term_length, fees);
   produce_blocks(1);

   // initialize election
   init_election();
   produce_blocks(1);

   // prepare voters
   symbol vote_symbol = symbol(4, "VOTE");
   register_voters(test_voters, 5, 30, vote_symbol);

   // choose 3 candidates
   name candidate1 = test_voters[0];
   name candidate2 = test_voters[1];
   name candidate3 = test_voters[2];

   std::string credentials = std::string("/ipfs/53CharacterLongHashToSatisfyIPFSHashCondition1/");

   // register and verifiy integrity of candidate info
   for(int i = 0; i <= 2; i++){
      // register 
      regcand( test_voters[i], credentials);
      candaddlead( test_voters[i], credentials);
      produce_blocks(1);
   }

   // ensure candidates that unreg + reg after initelection will be votable
   // note for the continuation of the test :
   // unreg + rereg will put the candidate at the end of the leaderboard queue 
   candrmvlead(candidate3);
   unregcand(candidate3);
   produce_blocks(1);
   regcand(candidate3, credentials);
   candaddlead(candidate3, credentials);
   produce_blocks(1);

   // start the election period
   produce_block(fc::seconds(start_election));
   produce_blocks(1);

   // prepare for vote weight checking 
   asset weight = asset::from_string("200.0000 VOTE"), zero_asset = asset::from_string("0.0000 VOTE");
   vector<asset> expected_weights = {zero_asset, zero_asset, zero_asset};

   auto config = get_config();
   auto cbid = config["ballot_id"].as_uint64();   

   auto ballot = get_ballot(cbid);
   auto bid = ballot["reference_id"].as_uint64();

   //cast 6 votes
   for(int i = 5; i < 11; i++) {
      mirrorcast(test_voters[i].value, symbol(4, "TLOS"));
  
      // everyone votes candidate1 => the direction is actually candidate index for leaderboard voting
      uint16_t vote_for_candidate = 0;      
      castvote(test_voters[i].value, config["ballot_id"].as_uint64(), vote_for_candidate);
      expected_weights[vote_for_candidate] += weight;

      // other vote : 1 for candidate2 and 1 for candidate3 to get a tie
      vote_for_candidate = ( i % 2 == 0 ) ? uint16_t(2) : uint16_t(1);
      castvote(test_voters[i].value, config["ballot_id"].as_uint64(), vote_for_candidate);
      expected_weights[vote_for_candidate] += weight;

      produce_blocks(1);
   }

   // verify votes
   BOOST_REQUIRE_EQUAL(expected_weights[0], asset::from_string("1200.0000 VOTE"));
   BOOST_REQUIRE_EQUAL(expected_weights[1], asset::from_string("600.0000 VOTE"));
   BOOST_REQUIRE_EQUAL(expected_weights[2], asset::from_string("600.0000 VOTE"));

   auto leaderboard = get_leaderboard(bid);
   auto lid = leaderboard["board_id"].as_uint64();

   for(int i = 0 ; i < 3 ; i++){
      REQUIRE_MATCHING_OBJECT(
         leaderboard["candidates"][i], 
         mvo()
            ("member", test_voters[i])
            ("info_link", credentials)
            ("votes", expected_weights[i])
            ("status", uint8_t(0))
      );
   }
   
   // election period is over
   produce_block(fc::seconds(election_duration));
   produce_blocks(1);

   // end the election
   uint32_t expected_term_length = now() + arbitrator_term_length;
   endelection(candidate1);
   produce_blocks(1);

   // candidate1 should be arbitrator and not a candidate anymore
   auto arb = get_arbitrator(candidate1.value);
   uint16_t UNAVAILABLE_STATUS = 1;
   BOOST_REQUIRE_EQUAL(false, arb.is_null());
   BOOST_REQUIRE_EQUAL(arb["arb"].as<name>(), candidate1);
   BOOST_REQUIRE_EQUAL(arb["arb_status"].as<uint16_t>(), UNAVAILABLE_STATUS);
   BOOST_REQUIRE_EQUAL(arb["credential_link"].as<std::string>(), credentials);
   BOOST_REQUIRE_EQUAL(arb["term_length"].as<uint32_t>(), expected_term_length);
   auto c = get_candidate(candidate1.value);
   BOOST_REQUIRE_EQUAL(c.is_null(), true);
   
   // candidate2 and candidate3 should still be candidates in new election for a tie breaker
   arb = get_arbitrator(candidate2.value);
   BOOST_REQUIRE_EQUAL(true, arb.is_null());
   c = get_candidate(candidate2.value);
   BOOST_REQUIRE_EQUAL(c.is_null(), false);
   BOOST_REQUIRE_EQUAL( c["cand_name"].as<name>(), candidate2 );
   
   arb = get_arbitrator(candidate3.value);
   BOOST_REQUIRE_EQUAL(true, arb.is_null());
   c = get_candidate(candidate3.value);
   BOOST_REQUIRE_EQUAL(c.is_null(), false);
   BOOST_REQUIRE_EQUAL( c["cand_name"].as<name>(), candidate3 );

   config = get_config();
   // a new leaderboard for the re-election / tiebreaker
   BOOST_REQUIRE_NE(config["ballot_id"].as_uint64(), cbid);
   cbid = config["ballot_id"].as_uint64();   

   ballot = get_ballot(cbid);
   bid = ballot["reference_id"].as_uint64();

   leaderboard = get_leaderboard(bid);
   lid = leaderboard["board_id"].as_uint64();
 
   for(int i = 0 ; i < 2 ; i++){
      REQUIRE_MATCHING_OBJECT(
         leaderboard["candidates"][i], 
         mvo()
            ("member", test_voters[i+1])
            ("info_link", credentials)
            ("votes", zero_asset)
            ("status", uint8_t(0))
      );
   }

   BOOST_REQUIRE_EQUAL(true, config["auto_start_election"]);

} FC_LOG_AND_RETHROW()


BOOST_AUTO_TEST_SUITE_END()