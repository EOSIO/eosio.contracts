#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <Runtime/Runtime.h>
#include <iomanip>

#include <fc/variant_object.hpp>
#include "contracts.hpp"
#include "test_symbol.hpp"
#include "eosio.amend_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

BOOST_AUTO_TEST_SUITE(eosio_amend_tests)

BOOST_FIXTURE_TEST_CASE( deposit_system, eosio_amend_tester) try {
	asset local_sum = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), N(eosio.amend));
	for(uint16_t i = 0; i < test_voters.size(); i++) {
		auto deposit_info = get_deposit(test_voters[i].value);
		BOOST_REQUIRE_EQUAL(true, deposit_info.is_null());
		asset sum = asset::from_string("20.0000 TLOS");
		auto voter_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), test_voters[i].value);
		
		BOOST_REQUIRE_EQUAL(voter_balance, asset::from_string("200.0000 TLOS"));
		std::cout << "transfer " << "1" << " account " << i << std::endl;
		transfer(test_voters[i].value, N(eosio.amend), sum, "WPS deposit");
		produce_blocks( 2 );
		auto contract_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), N(eosio.amend));
		BOOST_REQUIRE_EQUAL(contract_balance, local_sum + sum);
		local_sum += sum;

		deposit_info = get_deposit(test_voters[i].value);
		BOOST_REQUIRE_EQUAL(false, deposit_info.is_null());
		REQUIRE_MATCHING_OBJECT(deposit_info, mvo()
			("owner", test_voters[i].to_string())
			("escrow", sum.to_string())
		);
		std::cout << "transfer " << " 2 " << " account " << i << std::endl;
		transfer(test_voters[i].value, N(eosio.amend), sum, "WPS depost");
		produce_blocks( 2 );
		contract_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), N(eosio.amend));
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

BOOST_FIXTURE_TEST_CASE( ballot_id_and_fee, eosio_amend_tester ) try {
   register_voters(test_voters, 0, 1, symbol(4, "VOTE"));
   
   insert_default_docs();

   auto proposer = test_voters[0];
   transfer(N(eosio), proposer.value, asset::from_string("2000.0000 TLOS"), "Blood Money");
   transfer(N(eosio), eosio::chain::name("eosio.amend"), asset::from_string("0.0001 TLOS"), "Init Amend env");

   auto title = std::string("my ratify test title");
   auto cycles = 1;
   auto ipfs_location = std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B9");
   auto receiver = test_voters[0];

   int num_proposals = 10;
   auto env = get_env();
   uint64_t fee = env["fee"].as<uint64_t>();
   
   asset expected_total = core_sym::from_string("0.0001");
   signed_transaction trx;
   for( int i = 0; i < num_proposals; i++){
      std::stringstream ssf;
      ssf << std::fixed << std::setprecision(4) << (double(fee)/10000);
      asset _fee = core_sym::from_string(ssf.str());
      expected_total += _fee;

      transfer(proposer, eosio::chain::name("eosio.amend"), _fee, std::string("fee for ratify "+std::to_string(i)));

      uint64_t doc_num = i % documents.size();
      uint8_t clause_num = i % documents[doc_num]["clauses"].size(); 
	   makeproposal(std::string(title+std::to_string(i)), uint64_t(doc_num), uint8_t(clause_num), ipfs_location, proposer);
   }
   produce_blocks(1);
	
	BOOST_REQUIRE_EXCEPTION( 
      makeproposal(std::string(title+std::to_string(num_proposals)), uint64_t(documents.size()), uint8_t(0), ipfs_location, proposer), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Document Not Found" )
   );

	BOOST_REQUIRE_EXCEPTION( 
      makeproposal(std::string(title+std::to_string(num_proposals)), uint64_t(0), uint8_t(documents[0]["clauses"].size()), ipfs_location, proposer),
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Deposit not found, please transfer your TLOS fee" )
   );
   
   asset saving_balance = get_balance(N(eosio.amend));

   BOOST_REQUIRE_EQUAL(saving_balance, expected_total);

   for( int i = 0; i < num_proposals; i++){
      auto proposal = get_proposal(i);
      auto submission = get_submission(i);
      auto ballot = get_ballot(i);

      // since only wps here, there should be same ids for props and subs
      BOOST_REQUIRE_EQUAL(proposal["prop_id"], submission["proposal_id"]);
      BOOST_REQUIRE_EQUAL(proposal["info_url"], submission["new_ipfs_urls"].as<vector<std::string>>()[0]);
      
      // prop id and ballot ref id should be same
      BOOST_REQUIRE_EQUAL(proposal["prop_id"], ballot["reference_id"]);

      // submission should have correct ballot_id
      BOOST_REQUIRE_EQUAL(submission["ballot_id"], ballot["ballot_id"]);
   }
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( set_environment, eosio_amend_tester ) try {
   set_env(111111, 2222, 33333, 1.1, 11.1, 1.2, 11.2);
   produce_blocks(1);

   // transfer(N(eosio), N(eosio.saving), core_sym::from_string("1.0000"), "memo");
   // getdeposit(N(eosio));

   auto env = get_env();
   REQUIRE_MATCHING_OBJECT(
      env, 
      mvo()
         ("publisher", eosio::chain::name("eosio.amend"))
         ("expiration_length", 111111)
         ("fee", 2222)
         ("start_delay", 33333)
         ("threshold_pass_voters", 1.1)
         ("threshold_pass_votes", 11.1)
         ("threshold_fee_voters", 1.2)
         ("threshold_fee_votes", 11.2)
   );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( create_proposal_and_cancel, eosio_amend_tester ) try {
   int total_voters = test_voters.size();
   name proposer = test_voters[total_voters - 1];
   transfer(N(eosio), proposer.value, core_sym::from_string("300.0000"), "Blood Money");
   produce_blocks(1);
   BOOST_REQUIRE_EQUAL( core_sym::from_string("500.0000"), get_balance( proposer ) );

   set_env(uint32_t(2500000), uint64_t(1000000), uint32_t(864000000), double(5), double(66.67), double(4), double(25));
   produce_blocks(1);

   insert_default_docs();

	BOOST_REQUIRE_EXCEPTION( 
      makeproposal(
         std::string("test ratify 1"), 
         uint64_t(0), 
         uint8_t(0), 
         std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"), 
         proposer
      ), 
      eosio_assert_message_exception, eosio_assert_message_is( "Deposit not found, please transfer your TLOS fee" )
   );

   transfer(proposer, eosio::chain::name("eosio.amend"), core_sym::from_string("50.0000"), "ratify 1 fee");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("450.0000"), get_balance( proposer ) );
   produce_blocks(1);

	BOOST_REQUIRE_EXCEPTION( 
      makeproposal(
         std::string("test ratify 1"), 
         uint64_t(0), 
         uint8_t(0), 
         std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"), 
         proposer
      ), 
      eosio_assert_message_exception, 
      eosio_assert_message_is( "Deposit amount is less than fee, please transfer more TLOS" )
   );

   transfer(proposer, eosio::chain::name("eosio.amend"), core_sym::from_string("50.0000"), "ratify 1 fee");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("400.0000"), get_balance( proposer ) );
   produce_blocks(1);

   makeproposal(
      std::string("test ratify 1"), 
      uint64_t(0), 
      uint8_t(0), 
      std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"), 
      proposer
   );
   produce_blocks(1);

   transfer(proposer, eosio::chain::name("eosio.amend"), core_sym::from_string("100.0000"), "amend 2 fee");
   BOOST_REQUIRE_EQUAL( core_sym::from_string("300.0000"), get_balance( proposer ) );

   makeproposal(
      std::string("test amend 2"), 
      uint64_t(0), 
      uint8_t(0), 
      std::string("32662273CFF99078EC3BFA5E7BBB1C369B1D3884DEDF2AF7D8748DEE080E4B99"), 
      proposer
   );
   produce_blocks(1);

   auto deposit_info = get_deposit(proposer.value);
   BOOST_REQUIRE(deposit_info.is_null());

   cancelsub(0, proposer);
   cancelsub(1, proposer);

   BOOST_REQUIRE_EQUAL( core_sym::from_string("300.0000"), get_balance( proposer ) );
   
   BOOST_REQUIRE(get_proposal(0).is_null());
   BOOST_REQUIRE(get_proposal(1).is_null());
} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()