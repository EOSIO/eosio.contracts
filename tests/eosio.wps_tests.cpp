#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <Runtime/Runtime.h>
#include <iomanip>

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

BOOST_FIXTURE_TEST_CASE( deposit_system, eosio_wps_tester) try {
	asset local_sum = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), N(eosio.saving));
	for(uint16_t i = 0; i < test_voters.size(); i++) {
		auto deposit_info = get_deposit(test_voters[i].value);
		BOOST_REQUIRE_EQUAL(true, deposit_info.is_null());
		asset sum = asset::from_string("20.0000 TLOS");
		auto voter_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), test_voters[i].value);
		
		BOOST_REQUIRE_EQUAL(voter_balance, asset::from_string("200.0000 TLOS"));
		std::cout << "transfer " << "1" << " account " << i << std::endl;
		transfer(test_voters[i].value, N(eosio.saving), sum, "WPS deposit");
		produce_blocks( 2 );
		auto contract_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), N(eosio.saving));
		BOOST_REQUIRE_EQUAL(contract_balance, local_sum + sum);
		local_sum += sum;

		deposit_info = get_deposit(test_voters[i].value);
		REQUIRE_MATCHING_OBJECT(deposit_info, mvo()
			("owner", test_voters[i].to_string())
			("escrow", sum.to_string())
		);
		std::cout << "transfer " << " 2 " << " account " << i << std::endl;
		transfer(test_voters[i].value, N(eosio.saving), sum, "WPS depost");
		produce_blocks( 2 );
		contract_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), N(eosio.saving));
		BOOST_REQUIRE_EQUAL(contract_balance, (local_sum + sum));
		local_sum += sum;

		deposit_info = get_deposit(test_voters[i].value);
		REQUIRE_MATCHING_OBJECT(deposit_info, mvo()
			("owner", test_voters[i].to_string())
			("escrow", (sum + sum).to_string())
		);

		asset pre_refund = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), test_voters[i].value);
		asset escrow = asset::from_string(get_deposit(test_voters[i].value)["escrow"].as_string());
		getdeposit(test_voters[i].value);
            local_sum -= escrow;
		asset post_refund = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), test_voters[i].value);

		BOOST_REQUIRE_EQUAL((pre_refund + escrow), post_refund);
	}
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( ballot_id_and_fee, eosio_wps_tester ) try {
   register_voters(test_voters, 0, 1, symbol(4, "VOTE"));

   auto proposer = test_voters[0];
   transfer(N(eosio), proposer.value, asset::from_string("2000.0000 TLOS"), "Blood Money");
   transfer(N(eosio), eosio::chain::name("eosio.saving"), asset::from_string("0.0001 TLOS"), "Init WPS");

   auto title = std::string("my proposal test title");
   auto cycles = 1;
   auto ipfs_location = std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B9");
   auto receiver = test_voters[0];

   int num_proposals = 10;
   auto env = get_wps_env();
   uint16_t fee_percentage = env["fee_percentage"].as<uint16_t>();
   uint64_t fee_min = env["fee_min"].as<uint64_t>();
   uint64_t base_amount = fee_min * 100 / fee_percentage + (10000 * (num_proposals / 2));
   
   asset expected_total = core_sym::from_string("0.0001");
   signed_transaction trx;
   for( int i = 0; i < num_proposals; i++){
      uint64_t amount = base_amount - i * 10000;
      uint64_t fee = amount * fee_percentage / 100;
      fee = fee < fee_min ? fee_min : fee;
      
      std::stringstream ssa;
      std::stringstream ssf;
      ssa << std::fixed << std::setprecision(4) << (double(amount)/10000);
      ssf << std::fixed << std::setprecision(4) << (double(fee)/10000);
      asset _amount = core_sym::from_string(ssa.str());
      asset _fee = core_sym::from_string(ssf.str());
      expected_total += _fee;

      trx.actions.emplace_back( get_action(N(eosio.token), N(transfer), vector<permission_level>{{proposer.value, config::active_name}},
         mvo()
            ("from", proposer)
            ("to", eosio::chain::name("eosio.saving"))
            ("quantity", _fee)
            ("memo", std::string("proposal fee ")+i)
         )
      );
      
      trx.actions.emplace_back( get_action(N(eosio.saving), N(submit), vector<permission_level>{{proposer.value, config::active_name}},
         mvo()
            ("proposer",      proposer)
            ("title",         title + i)
            ("cycles",        cycles + i)
            ("ipfs_location", ipfs_location + i)
            ("amount",        _amount)
            ("receiver",      proposer)
         )
      );
   }
   set_transaction_headers(trx);
   trx.sign(get_private_key(proposer, "active"), control->get_chain_id());
   push_transaction( trx );
   produce_blocks(1);

   asset saving_balance = get_balance(N(eosio.saving));

   BOOST_REQUIRE_EQUAL(saving_balance, expected_total);

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
   }
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( set_env, eosio_wps_tester ) try {
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
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( create_proposal_and_cancel, eosio_wps_tester ) try {
   int total_voters = test_voters.size();
   name proposer = test_voters[total_voters - 1];
   
   wps_set_env(2500000, 3, 864000000, 500000, 5, 50, 4, 20);
   produce_blocks(1);

   transfer(N(eosio), proposer.value, core_sym::from_string("300.0000"), "Blood Money");
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( proposer ) );
   
   transfer(proposer, eosio::chain::name("eosio.saving"), core_sym::from_string("30.0000"), "proposal 1 fee");
   
	BOOST_REQUIRE_EXCEPTION( 
      submit_worker_proposal(
         proposer.value,
         std::string("test proposal 1"),
         (uint16_t)3,
         std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"),
         core_sym::from_string("1000.0000"),
         proposer.value
      ), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Deposit amount is less than fee, please transfer more TLOS" )
   );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("470.0000"), get_balance( proposer ) );

   transfer(proposer, eosio::chain::name("eosio.saving"), core_sym::from_string("20.0000"), "proposal 1 fee");
   submit_worker_proposal(
      proposer.value,
      std::string("test proposal 1"),
      (uint16_t)3,
      std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"),
      core_sym::from_string("1000.0000"),
      test_voters[0].value
   );
   produce_blocks();

   // check if 50TLOS (3% < 50) fee was used
   BOOST_REQUIRE_EQUAL( core_sym::from_string("450.0000"), get_balance( proposer ) );
   auto submission = get_wps_submission(0);
   REQUIRE_MATCHING_OBJECT(
      submission, 
      mvo()
         ("id", uint64_t(0))
		   ("ballot_id", uint64_t(0))
		   ("proposer", proposer)
		   ("receiver", test_voters[0])
		   ("title", std::string("test proposal 1"))
         ("ipfs_location", std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"))
         ("cycles", uint16_t(3 + 1))
         ("amount", uint64_t(10000000))
         ("fee", uint64_t(500000))
   );
   
	BOOST_REQUIRE_EXCEPTION( 
      submit_worker_proposal(
         proposer.value,
         std::string("test proposal 2"),
         (uint16_t)3,
         std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"),
         core_sym::from_string("2000.0000"),
         proposer.value
      ),
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Deposit not found, please transfer your TLOS fee" )
   );

   transfer(proposer, eosio::chain::name("eosio.saving"), core_sym::from_string("60.0000"), "proposal 2 fee");
   submit_worker_proposal(
      proposer.value,
      std::string("test proposal 2"),
      (uint16_t)3,
      std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"),
      core_sym::from_string("2000.0000"),
      proposer.value
   );
   // check if 60TLOS (3% > 50) fee was used
   BOOST_REQUIRE_EQUAL( core_sym::from_string("390.0000"), get_balance( proposer ) );

   auto deposit_info = get_deposit(proposer.value);
   BOOST_REQUIRE(deposit_info.is_null());

   cancelsub(proposer, 0);
   cancelsub(proposer, 1);
   produce_blocks();
   
   BOOST_REQUIRE_EXCEPTION( openvoting(proposer.value, 0), eosio_assert_message_exception, 
      eosio_assert_message_is( "Submission not found" ));

   BOOST_REQUIRE_EQUAL( core_sym::from_string("390.0000"), get_balance( proposer ) );
   
   BOOST_REQUIRE(get_proposal(0).is_null());
   BOOST_REQUIRE(get_proposal(1).is_null());
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( multiple_cycles_complete_flow, eosio_wps_tester ) try {
   uint32_t wp_cycle_duration = 2500000; // 2.5 mil seconds = 5 mil blocks

   int total_voters = test_voters.size();
	symbol vote_symbol = symbol(4, "VOTE");
   register_voters(test_voters, 0, total_voters - 1, vote_symbol);
   
   auto registry_info = get_registry(symbol(4, "VOTE"));
		BOOST_REQUIRE_EQUAL(registry_info["total_voters"], total_voters - 1);

   name proposer = test_voters[total_voters - 1];
   transfer(N(eosio), proposer.value, asset::from_string("1800.0000 TLOS"), "Blood Money");
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("2000.0000"), get_balance( proposer ) );

   wps_set_env(2500000, 3, 864000000, 500000, 5, 50, 4, 20);
   produce_blocks(1);
   auto env = get_wps_env();
   
   double threshold_pass_voters = env["threshold_pass_voters"].as<double>();
   double threshold_fee_voters = env["threshold_fee_voters"].as<double>();
   unsigned int quorum_voters_size_pass = (total_voters * threshold_pass_voters) / 100;
   unsigned int quorum_voters_size_fail = quorum_voters_size_pass - 1;
   unsigned int fee_voters = (total_voters * threshold_fee_voters) / 100;
   
   double threshold_pass_votes = env["threshold_pass_votes"].as<double>();
   double threshold_fee_votes = env["threshold_fee_votes"].as<double>();

   // std::cout<<"---- "<<quorum_voters_size_pass<<" = "<<quorum_voters_size_fail<<" = "<<fee_voters<<" = "<<threshold_pass_votes<<" = "<<threshold_fee_votes<<" ----"<<std::endl;
   
   transfer(proposer, eosio::chain::name("eosio.saving"), core_sym::from_string("50.0000"), "proposal 1 fee");
   submit_worker_proposal(
      proposer.value,
      std::string("test proposal 1"),
      (uint16_t)3,
      std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"),
      core_sym::from_string("1000.0000"),
      test_voters[0]
   );
   // check if 50TLOS (3% < 50) fee was used
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1950.0000"), get_balance( proposer ) );
   
   transfer(proposer, eosio::chain::name("eosio.saving"), core_sym::from_string("60.0000"), "proposal 2 fee");
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

   produce_block(fc::days(1));

   BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 0, 1), eosio_assert_message_exception, 
      eosio_assert_message_is( "ballot voting window not open" ));

	openvoting(proposer.value, 0);
	openvoting(proposer.value, 1);
   produce_blocks(1);
   
   BOOST_REQUIRE_EXCEPTION( openvoting(proposer.value, 0), eosio_assert_message_exception, 
      eosio_assert_message_is( "proposal is no longer in building stage" ));

   // validate vote integrity
	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 0, 3), eosio_assert_message_exception, 
      eosio_assert_message_is( "Invalid Vote. [0 = NO, 1 = YES, 2 = ABSTAIN]" ));

	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 3, 1), eosio_assert_message_exception, 
      eosio_assert_message_is( "ballot with given ballot_id doesn't exist" ));

   // voters are now added when they are not found 
	// BOOST_REQUIRE_EXCEPTION( castvote(proposer.value, 0, 1), eosio_assert_message_exception, 
   //    eosio_assert_message_is( "voter is not registered" ));

   // mirrorcast on the other hand will throw an exception 
	BOOST_REQUIRE_EXCEPTION( mirrorcast(proposer.value, symbol(4, "TLOS")), eosio_assert_message_exception, 
      eosio_assert_message_is( "voter is not registered" ));

   auto quorum = vector<account_name>(test_voters.begin(), test_voters.begin() + quorum_voters_size_pass); 

   
   auto calculateTippingPoint = [&](int quorum_size, int threshold, bool fee = false) {
      if( fee )
         return std::ceil( double(quorum_size * threshold) / 100);

      return std::floor( double(quorum_size * threshold) / 100) + 1;
   };
 
   int vote_tipping_point = calculateTippingPoint(quorum_voters_size_fail, threshold_pass_votes);
   int fee_tipping_point = calculateTippingPoint(quorum_voters_size_fail, threshold_fee_votes, true);

   // std::cout<<"conditions: [ "<<vote_tipping_point<<" ] / [ i < "<<fee_tipping_point<<" - 1 ] "<<std::endl;

   // voting window (#0) started
   // not enough voters in first cycle
   for(int i = 0; i < quorum_voters_size_fail; i++) {
      mirrorcast(quorum[i].value, symbol(4, "TLOS"));

      // fail vote from lack of voters, but get fee
      uint16_t vote_direction_0 = 1;
      // fail vote from lack of voters and the fee from no votes
      uint16_t vote_direction_1 = ( i < fee_tipping_point - 1 ) ? uint16_t(1) : uint16_t(0);
      
      // std::cout<<i<<" => "<<vote_direction_0<<" "<<vote_direction_1<<std::endl;

      castvote(quorum[i].value, 0, vote_direction_0);
      castvote(quorum[i].value, 1, vote_direction_1);
      produce_blocks(1);
   }

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Cycle is still open" ), claim_proposal_funds(0, proposer.value));
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1890.0000"), get_balance( proposer ) );

   produce_block(fc::seconds(2500000)); // end the cycle
   produce_blocks(1);

   // CLAIM: get fee back
   claim_proposal_funds(0, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("200.0000"), get_balance( test_voters[0] ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   // CLAIM: nothing to claim
   claim_proposal_funds(1, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   produce_blocks(1);

//    // voting windows starts in 1 day
// 	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 0, 1), eosio_assert_message_exception, 
//       eosio_assert_message_is( "ballot voting window not open" ));

//    // 1 day later voting window opens
//    produce_block(fc::days(1));

   vote_tipping_point = calculateTippingPoint(quorum_voters_size_pass, threshold_pass_votes);
   fee_tipping_point = calculateTippingPoint(quorum_voters_size_pass, threshold_fee_votes, true);

   // std::cout<<"conditions: [ i < "<<vote_tipping_point<<" - 1 ] / [ i < "<<fee_tipping_point<<" - 1 ] "<<std::endl;

   // voting window (#1) started
   for(int i = 0; i < quorum_voters_size_pass; i++){
      mirrorcast(quorum[i].value, symbol(4, "TLOS"));

      // fail vote, fee already claimed but would pass
      uint16_t vote_direction_0 = ( i < vote_tipping_point - 1 ) ? uint16_t(1) : uint16_t(0);
      // fail vote and fee from no votes
      uint16_t vote_direction_1 = ( i < fee_tipping_point - 1 ) ? uint16_t(1) : uint16_t(0);

      // std::cout<<i<<" => "<<vote_direction_0<<" "<<vote_direction_1<<std::endl;

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

   // // CLAIM: nothing to claim
   claim_proposal_funds(0, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("200.0000"), get_balance( test_voters[0] ) );

   produce_blocks(2);

//    // voting windows starts in 1 day
// 	BOOST_REQUIRE_EXCEPTION( castvote(test_voters[0].value, 0, 1), eosio_assert_message_exception, 
//       eosio_assert_message_is( "ballot voting window not open" ));

//    // 1 day later voting window opens
//    produce_block(fc::days(1));

   vote_tipping_point = calculateTippingPoint(quorum_voters_size_pass, threshold_pass_votes);
   fee_tipping_point = calculateTippingPoint(quorum_voters_size_pass, threshold_fee_votes, true);

//    std::cout<<"conditions: [ i < "<<vote_tipping_point<<" ] / [ i < "<<fee_tipping_point<<" ] "<<std::endl;

   // voting window (#2) started
   for(int i = 0; i < quorum_voters_size_pass; i++){
      mirrorcast(quorum[i].value, symbol(4, "TLOS"));
      
      // pass vote, fee already claimed
      uint16_t vote_direction_0 = ( i < vote_tipping_point ) ? uint16_t(1) : uint16_t(0);
      // pass vote and fee
      uint16_t vote_direction_1 = ( i < vote_tipping_point ) ? uint16_t(1) : uint16_t(0);
      
      // std::cout<<i<<" => "<<vote_direction_0<<" "<<vote_direction_1<<std::endl;

      castvote(quorum[i].value, 0, vote_direction_0);
      castvote(quorum[i].value, 1, vote_direction_1);
      produce_blocks(1);
   }
   
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Cycle is still open" ), claim_proposal_funds(0, proposer.value));
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1940.0000"), get_balance( proposer ) );

   produce_block(fc::seconds(2500000)); // end the cycle

   // // last cycle check = prep 0 + cycle 1, cycle 2 [ended] / cycle 3 waiting for claim [3rd cycle is not counted until claim]
   BOOST_REQUIRE_EQUAL(1 + 2, get_proposal(0)["cycle_count"].as_uint64());
   BOOST_REQUIRE_EQUAL(1 + 2, get_proposal(1)["cycle_count"].as_uint64());

   // CLAIM: funds - 2060 should be added => close ballot
   claim_proposal_funds(1, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("4000.0000"), get_balance( proposer ) );
   
   // CLAIM: funds - 1000 should be added => close ballot 
   claim_proposal_funds(0, proposer.value);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("1200.0000"), get_balance( test_voters[0] ) );
   BOOST_REQUIRE_EQUAL( core_sym::from_string("4000.0000"), get_balance( proposer ) );

   BOOST_REQUIRE_EQUAL( core_sym::from_string("0.0000"), get_balance( eosio::chain::name("eosio.saving") ) );

   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Proposal is closed" ), claim_proposal_funds(0, proposer.value));
   BOOST_REQUIRE_EQUAL( wasm_assert_msg( "Proposal is closed" ), claim_proposal_funds(1, proposer.value));

   BOOST_REQUIRE_EXCEPTION( openvoting(proposer.value, 0), eosio_assert_message_exception, 
      eosio_assert_message_is( "proposal is no longer in building stage" ));

   // CHECK IF BOTH PROPOSALS ENDED 
   BOOST_REQUIRE_EQUAL(get_proposal(0)["status"].as<uint8_t>(), uint8_t(1));
   BOOST_REQUIRE_EQUAL(get_proposal(1)["status"].as<uint8_t>(), uint8_t(1));

} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()