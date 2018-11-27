#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <Runtime/Runtime.h>

#include <fc/variant_object.hpp>
#include "contracts.hpp"
#include "test_symbol.hpp"
#include "eosio.wps_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

BOOST_AUTO_TEST_SUITE(eosio_wps_tests)

BOOST_FIXTURE_TEST_CASE( ballot_id_distribution, eosio_wps_tester ) try {
   register_voters(test_voters, 0, 1);

   auto proposer = test_voters[0];
   transfer(N(eosio), proposer.value, asset::from_string("2000.0000 TLOS"), "Blood Money");
   auto title = std::string("my proposal test title");
   auto cycles = 1;
   auto ipfs_location = std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B9");
   auto amnt = std::string("1");
   auto receiver = test_voters[0];

   int num_proposals = 10;

   signed_transaction trx;
   for( int i = 0; i < num_proposals; i++){
      std::string _amount = amnt + std::to_string(i);
      trx.actions.emplace_back( get_action(N(eosio.saving), N(submit), vector<permission_level>{{proposer.value, config::active_name}},
         mvo()
            ("proposer",      proposer)
            ("title",         title + i)
            ("cycles",        cycles + i)
            ("ipfs_location", ipfs_location + i)
            ("amount",        core_sym::from_string(_amount))
            ("receiver",      proposer)
         )
      );
   }
   set_transaction_headers(trx);
   trx.sign(get_private_key(proposer, "active"), control->get_chain_id());
   push_transaction( trx );
   produce_blocks(1);

   for( int i = 0; i < num_proposals; i++){
      auto proposal = get_proposal(i);
      auto submission = get_wps_submission(i);
      auto ballot = get_ballot(i);
      // since only wps here, there should be same ids for props and subs
      BOOST_REQUIRE_EQUAL(proposal["prop_id"], submission["id"]);
      BOOST_REQUIRE_EQUAL(proposal["info_url"], submission["ipfs_location"]);
      
      // prop id and ballot ref id should be same
      BOOST_REQUIRE_EQUAL(proposal["prop_id"], ballot["reference_id"]);

      // submission should have correct ballot_id
      BOOST_REQUIRE_EQUAL(submission["ballot_id"], ballot["ballot_id"]);

      // wdump((proposal));
      // wdump((submission));
      // wdump((ballot));
      // ilog("----------");
   }
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( multiple_cycles_complete_flow, eosio_wps_tester ) try {
   uint32_t wp_cycle_duration = 2500000; // 2.5 mil seconds = 5 mil blocks

   int total_voters = test_voters.size();

   register_voters(test_voters, 0, total_voters - 1);
   auto trail_env = get_trail_env();
   wdump((trail_env));
   BOOST_REQUIRE_EQUAL(trail_env["totals"][1], total_voters - 1);

   name proposer = test_voters[total_voters - 1];
   transfer(N(eosio), proposer.value, asset::from_string("1800.0000 TLOS"), "Blood Money");
   base_tester::set_authority( 
      proposer.value, 
      name(config::active_name).to_string(), 
      authority(
            1,
            {key_weight{get_public_key( proposer.value, "active" ), 1}},
            {permission_level_weight{{N(eosio.saving), config::eosio_code_name}, 1}}
         ),
      name(config::owner_name).to_string()
   );
   produce_blocks(1);

   BOOST_REQUIRE_EQUAL( core_sym::from_string("2000.0000"), get_balance( proposer ) );

   wps_set_env(1111111, 1, 111111, 11111, 1, 11, 1, 11);
   produce_blocks(1);

   auto env = get_wps_env();
   REQUIRE_MATCHING_OBJECT(
      env, 
      mvo()
         ("publisher", eosio::chain::name("eosio.saving"))
         ("cycle_duration", 1111111)
         ("fee_percentage", 1)
         ("start_delay", 111111)
         ("fee_min", 11111)
         ("threshold_pass_voters", 1)
         ("threshold_pass_votes", 11)
         ("threshold_fee_voters", 1)
         ("threshold_fee_votes", 11)
   );

   wps_set_env(2500000, 3, 86400, 500000, 5, 50, 4, 20);
   produce_blocks(1);
   env = get_wps_env();
   // wdump((env));
   
   double threshold_pass_voters = env["threshold_pass_voters"].as<double>();
   double threshold_fee_voters = env["threshold_fee_voters"].as<double>();
   unsigned int quorum_voters_size_pass = (total_voters * threshold_pass_voters) / 100;
   unsigned int quorum_voters_size_fail = quorum_voters_size_pass - 1;
   unsigned int fee_voters = (total_voters * threshold_fee_voters) / 100;
   
   double threshold_pass_votes = env["threshold_pass_votes"].as<double>();
   double threshold_fee_votes = env["threshold_fee_votes"].as<double>();

   submit_worker_proposal(
      proposer.value,
      std::string("test proposal 1"),
      (uint16_t)3,
      std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"),
      core_sym::from_string("1000.0000"),
      proposer.value
   );
   // check if 50TLOS (3% < 50) fee was used
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1950.0000"), get_balance( proposer ) );
   
   submit_worker_proposal(
      proposer.value,
      std::string("test proposal 2"),
      (uint16_t)3,
      std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"),
      core_sym::from_string("2000.0000"),
      proposer.value
   );
   // check if 60TLOS (3% > 50) fee was used
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1890.0000"), get_balance( proposer ) );

   // make sure saving has enough to cover the 2 proposals
   transfer(N(eosio), N(eosio.saving), asset::from_string("3000.0000 TLOS"), "Blood Money");
   produce_blocks(1);

   // voting windows starts in 1 day
	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 0, 1), eosio_assert_message_exception, 
      eosio_assert_message_is( "ballot voting window not open" ));

   // 1 day later voting window opens
   produce_block(fc::days(1));

   // validate vote integrity
	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 0, 3), eosio_assert_message_exception, 
      eosio_assert_message_is( "Invalid Vote. [0 = NO, 1 = YES, 2 = ABSTAIN]" ));

	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 3, 1), eosio_assert_message_exception, 
      eosio_assert_message_is( "ballot with given ballot_id doesn't exist" ));

   // voters are now added when they are not found 
	// BOOST_REQUIRE_EXCEPTION( castvote(proposer.value, 0, 1), eosio_assert_message_exception, 
   //    eosio_assert_message_is( "voter is not registered" ));

   // mirrorcast on the other hand will throw an exception 
	BOOST_REQUIRE_EXCEPTION( mirrorcast(proposer.value, symbol(4, "VOTE")), eosio_assert_message_exception, 
      eosio_assert_message_is( "voter is not registered" ));

   auto quorum = vector<account_name>(test_voters.begin(), test_voters.begin() + quorum_voters_size_pass); 

   int vote_tipping_point = ((quorum_voters_size_pass * 100) / threshold_pass_votes) + 1;
   int fee_tipping_point = ((quorum_voters_size_pass * 100) / threshold_fee_votes) + 1;

   // voting window (#0) started
   // not enough voters in first cycle
   for(int i = 0; i < quorum_voters_size_fail; i++){
      mirrorcast(quorum[i].value, symbol(4, "VOTE"));

      // fail vote from lack of voters, but get fee
      uint16_t vote_direction_0 = 1;
      // fail vote from lack of voters and the fee from no votes
      uint16_t vote_direction_1 = (quorum_voters_size_fail - i < fee_tipping_point) ? uint16_t(0) : uint16_t(1);

      castvote(quorum[i].value, 0, vote_direction_0);
      castvote(quorum[i].value, 1, vote_direction_1);
      produce_blocks(1);
   }

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Cycle is still open" ), claim_proposal_funds(0, proposer.value));
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1890.0000"), get_balance( proposer ) );

   produce_block(fc::seconds(2500000)); // end the cycle
   produce_blocks(1);

   wdump((get_proposal(0)));
   wdump((get_proposal(1)));
   wdump((now()));

   // CLAIM: get fee back
   claim_proposal_funds(0, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   // CLAIM: nothing to claim
   claim_proposal_funds(1, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   produce_blocks(1);

   // voting windows starts in 1 day
	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 0, 1), eosio_assert_message_exception, 
      eosio_assert_message_is( "ballot voting window not open" ));

   // 1 day later voting window opens
   produce_block(fc::days(1));

   // voting window (#1) started
   for(int i = 0; i < quorum_voters_size_pass; i++){
      mirrorcast(quorum[i].value, symbol(4, "VOTE"));

      // fail vote, fee already claimed but would pass
      uint16_t vote_direction_0 = ( i < vote_tipping_point || (quorum_voters_size_pass - i < fee_tipping_point) ) ? uint16_t(0) : uint16_t(1);
      // fail vote and fee from no votes
      uint16_t vote_direction_1 = ( i < vote_tipping_point || (quorum_voters_size_pass - i >= fee_tipping_point) ) ? uint16_t(0) : uint16_t(1);

      castvote(quorum[i].value, 0, vote_direction_0);
      castvote(quorum[i].value, 1, vote_direction_1);
      produce_blocks(1);
   }
   
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Cycle is still open" ), claim_proposal_funds(0, proposer.value));
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   produce_block(fc::seconds(2500000)); // end the cycle

   // // CLAIM: nothing to claim
   claim_proposal_funds(1, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   // // CLAIM: fee from proposal 0 should be added to account
   claim_proposal_funds(0, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   produce_blocks(1);

   // voting windows starts in 1 day
	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 0, 1), eosio_assert_message_exception, 
      eosio_assert_message_is( "ballot voting window not open" ));

   // 1 day later voting window opens
   produce_block(fc::days(1));

   // voting window (#2) started
   for(int i = 0; i < quorum_voters_size_pass; i++){
      mirrorcast(quorum[i].value, symbol(4, "VOTE"));
      
      // pass vote, fee already claimed
      uint16_t vote_direction_0 = ( i <= vote_tipping_point ) ? uint16_t(1) : uint16_t(0);
      // pass vote and fee
      uint16_t vote_direction_1 = ( i <= vote_tipping_point ) ? uint16_t(1) : uint16_t(0);

      castvote(quorum[i].value, 0, vote_direction_0);
      castvote(quorum[i].value, 1, vote_direction_1);
      produce_blocks(1);
   }
   
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Cycle is still open" ), claim_proposal_funds(0, proposer.value));
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   produce_block(fc::seconds(2500000)); // end the cycle

   // CLAIM: funds - 2060 should be added
   claim_proposal_funds(1, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("4000.0000"), get_balance( proposer ) );
   
   // CLAIM: funds - 1000 should be added
   claim_proposal_funds(0, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("5000.0000"), get_balance( proposer ) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( eosio::chain::name("eosio.saving") ) );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Proposal is closed" ), claim_proposal_funds(0, proposer.value));
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Proposal is closed" ), claim_proposal_funds(1, proposer.value));

   // // CHECK IF BOTH PROPOSALS ENDED
   // BOOST_REQUIRE_EQUAL(0, get_wp_info(0)["status"].as_uint64());
   // BOOST_REQUIRE_EQUAL(3, get_wp_info(0)["current_cycle"].as_uint64());

   // BOOST_REQUIRE_EQUAL(0, get_wp_info(1)["status"].as_uint64());
   // BOOST_REQUIRE_EQUAL(3, get_wp_info(1)["current_cycle"].as_uint64());

   // // CLAIM AFTER PROPOSALS ENDED
   // BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Proposal is closed" ), claim_proposal_funds(0, N(proposer1111)));

   // // TODO: check list + close ballot
} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()