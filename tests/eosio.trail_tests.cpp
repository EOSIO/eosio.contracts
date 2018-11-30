#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <Runtime/Runtime.h>

#include <fc/variant_object.hpp>
#include "contracts.hpp"
#include "test_symbol.hpp"
#include "eosio.trail_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

BOOST_AUTO_TEST_SUITE(eosio_trail_tests)

BOOST_FIXTURE_TEST_CASE( reg_voters, eosio_trail_tester ) try {
	for (int i = 0; i < test_voters.size(); i++) {
		regvoter(test_voters[i].value, symbol(4, "VOTE"));
		symbol test_symbol = symbol(4, "VOTE");
		symbol_code test_code = test_symbol.to_symbol_code();
		produce_blocks();

		auto voter_info = get_voter(test_voters[i], test_code);
		
		REQUIRE_MATCHING_OBJECT(voter_info, mvo()
			("owner", test_voters[i].to_string())
			("tokens", "0.0000 VOTE")
		);

		auto trail_env = get_trail_env();
		BOOST_REQUIRE_EQUAL(trail_env["totals"][1], 1);

		unregvoter(test_voters[i].value, test_symbol);
		produce_blocks();

		voter_info = get_voter(test_voters[i], test_code);
		BOOST_REQUIRE_EQUAL(true, voter_info.is_null());

		trail_env = get_trail_env();
		BOOST_REQUIRE_EQUAL(trail_env["totals"][1], 0);
	}
} FC_LOG_AND_RETHROW()

//TODO: check for voter already exists assertion msg
BOOST_FIXTURE_TEST_CASE( vote_levies, eosio_trail_tester ) try {
	create_accounts({N(levytest1), N(levytest2)});
	produce_blocks( 2 );

	uint32_t initial_transfer_time = now();
	symbol test_symbol = symbol(4, "VOTE");
	symbol_code test_code = test_symbol.to_symbol_code();

	auto levy_info = get_vote_counter_bal(N(eosio), test_code);
	BOOST_REQUIRE_EQUAL(true, levy_info.is_null());

	//transfer 1
	transfer(N(eosio), N(levytest1), asset::from_string("1000.0000 TLOS"), "Monopoly Money");
	
	//from levy 1
	levy_info = get_vote_counter_bal(N(eosio), test_code);
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "eosio")
			("decayable_cb", "0.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", initial_transfer_time)
		);

	//to levy 1
	levy_info = get_vote_counter_bal(N(levytest1), test_code);
	// std::cout << "decayable_cb: " << levy_info["decayable_cb"].as_string() << std::endl;
	// std::cout << "persistent_cb: " << levy_info["persistent_cb"].as_string() << std::endl;
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "levytest1")
			("decayable_cb", "1000.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", initial_transfer_time)
		);

	//transfer 2
	transfer(N(levytest1), N(levytest2), asset::from_string("200.0000 TLOS"), "Monopoly Money");

	//from 2 
	levy_info = get_vote_counter_bal(N(levytest1), test_code);
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "levytest1")
			("decayable_cb", "800.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", initial_transfer_time)
		);

	//to 2
	levy_info = get_vote_counter_bal(N(levytest2), test_code);
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "levytest2")
			("decayable_cb", "200.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", initial_transfer_time)
		);

	produce_blocks( 2 );
	//tranfer 3
	transfer(N(levytest2), N(levytest1), asset::from_string("100.0000 TLOS"), "Monopoly Money");

	//from 3 
	levy_info = get_vote_counter_bal(N(levytest2), test_code);
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "levytest2")
			("decayable_cb", "100.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", initial_transfer_time)
		);

	//to 2
	levy_info = get_vote_counter_bal(N(levytest1), test_code);
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "levytest1")
			("decayable_cb", "900.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", initial_transfer_time)
		);

	create_accounts({N(levytest3)});
	//transfer 3
	transfer(N(levytest1), N(levytest3), asset::from_string("100.0000 TLOS"), "Monopoly Money");
	levy_info = get_vote_counter_bal(N(levytest1), test_code);
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "levytest1")
			("decayable_cb", "800.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", initial_transfer_time)
		);

	levy_info = get_vote_counter_bal(N(levytest3), test_code);
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "levytest3")
			("decayable_cb", "100.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", now())
		);
} FC_LOG_AND_RETHROW()

//TODO: check minimum lock period assertion msg
//TODO: check maximum lock period assertion msg
//TODO: check for positive VOTE quantity assertion msg
//TODO: check for non-registered voter assertion msg
BOOST_FIXTURE_TEST_CASE( mirror_cast, eosio_trail_tester ) try {
	fc::variant voter_info = mvo();
	symbol test_symbol = symbol(4, "VOTE");
	symbol_code test_code = test_symbol.to_symbol_code();
	uint32_t future = 0;
	for (int i = 0; i < test_voters.size(); i++) {
		regvoter(test_voters[i].value, test_symbol);
		// std::cout << "regvoter for: " << test_voters[i].to_string() << std::endl;

		mirrorcast(test_voters[i].value, test_symbol);
		voter_info = get_voter(test_voters[i], test_code);
		REQUIRE_MATCHING_OBJECT(voter_info, mvo()
			("owner", test_voters[i].to_string())
			("tokens", "200.0000 VOTE")
		);
		produce_blocks( 2 );
	}
	//Transfer to a new account
	create_accounts({N(votedecay)});
	transfer(N(eosio), N(votedecay), asset::from_string("1000.0000 TLOS"), "Vote decay test");
	auto levy_info = get_vote_counter_bal(N(votedecay), test_code);
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "votedecay")
			("decayable_cb", "1000.0000 VOTE")
			("persistent_cb", "0.0000 VOTE")
			("last_decay", now())
		);
	// std::cout << "counter balance object exists after initial transfer" << std::endl;

	produce_blocks();
	produce_block(fc::seconds(172798/2));
	produce_blocks();

	// regvoter and mirrorstake new account
	// std::cout << "regvoter for votedecay" << std::endl;
	regvoter(N(votedecay), test_symbol);
	// std::cout << "mirrorcast for voter" << std::endl;
	mirrorcast(N(votedecay), test_symbol);

	//1200 blocks = 5.0000 VOTE or 240 blocks / 1.0000 VOTE
	string levy_amount_after_decay = "280.0000 VOTE";

	levy_info = get_vote_counter_bal(N(votedecay), test_code);
	// std::cout << "now(): " << now() << std::endl;
	// std::cout << "counter_balance.last_decay: " << levy_info["last_decay"].as_uint64() << std::endl;
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("owner", "votedecay")
			("decayable_cb", levy_amount_after_decay)
			("persistent_cb", "0.0000 VOTE")
			("last_decay", now() - 86400) //600 is the NUMBER OF BLOCKS PRODUCED in seconds AFTER TRANFER
		);
} FC_LOG_AND_RETHROW()

//TODO: case for reg and unreg ballot
//TODO: shouldn't be able to cycle a ballet that hasn't expired or when the action sender isn't the publisher of the ballot
BOOST_FIXTURE_TEST_CASE( reg_proposal_ballot, eosio_trail_tester ) try {
	account_name publisher = N(voteraaaaaaa);
	uint64_t current_ballot_id = 0;
	uint64_t current_proposal_id = 0;
	string info_url = "879e0c2c-f436-11e8-8eb2-f2801f1b9fd1";
	uint8_t ballot_type = 0;
	uint32_t ballot_length = 1200;
	uint32_t begin_time = now() + 20;
	uint32_t end_time   = now() + ballot_length;
	symbol test_symbol = symbol(4, "VOTE");
	symbol_code test_code = test_symbol.to_symbol_code();


	regvoter(publisher, test_symbol);
	regballot(publisher, ballot_type, test_symbol, begin_time, end_time, info_url);

	auto ballot_info = get_ballot(current_ballot_id);
	REQUIRE_MATCHING_OBJECT(ballot_info, mvo()
		("ballot_id", current_ballot_id)
		("table_id", ballot_type)
		("reference_id", current_proposal_id)
	);

	auto proposal_info = get_proposal(current_proposal_id);
	REQUIRE_MATCHING_OBJECT(proposal_info, mvo()
		("prop_id", current_proposal_id)
		("publisher", publisher.to_string())
		("info_url", info_url)
		("no_count", "0.0000 VOTE")
		("yes_count", "0.0000 VOTE")
		("abstain_count", "0.0000 VOTE")
		("unique_voters", uint32_t(0))
		("begin_time", begin_time)
		("end_time", end_time)
		("cycle_count", 0)
		("status", uint8_t(0))
	);
	produce_blocks( 2 );

	//Malicious unreg: should fail
	account_name non_publisher = N(voteraaaaaab);
	BOOST_REQUIRE_EXCEPTION(unregballot(non_publisher, current_ballot_id),
		eosio_assert_message_exception, eosio_assert_message_is( "cannot delete another account's proposal" ) 
   	);
	
	unregballot(publisher, current_ballot_id);

	ballot_info = get_ballot(current_ballot_id);
	BOOST_REQUIRE_EQUAL(true, ballot_info.is_null());

	proposal_info = get_proposal(current_proposal_id);
	BOOST_REQUIRE_EQUAL(true, proposal_info.is_null());

	begin_time = now() + 20;
	end_time   = now() + ballot_length;

	regballot(publisher, ballot_type, test_symbol, begin_time, end_time, info_url);

	ballot_info = get_ballot(current_ballot_id);
	REQUIRE_MATCHING_OBJECT(ballot_info, mvo()
		("ballot_id", current_ballot_id)
		("table_id", ballot_type)
		("reference_id", current_proposal_id)
	);

	proposal_info = get_proposal(current_proposal_id);
	REQUIRE_MATCHING_OBJECT(proposal_info, mvo()
		("prop_id", current_proposal_id)
		("publisher", publisher.to_string())
		("info_url", info_url)
		("no_count", "0.0000 VOTE")
		("yes_count", "0.0000 VOTE")
		("abstain_count", "0.0000 VOTE")
		("unique_voters", uint32_t(0))
		("begin_time", begin_time)
		("end_time", end_time)
		("cycle_count", 0)
		("status", uint8_t(0))
	);

	produce_blocks( 2401 );
	
	BOOST_REQUIRE_EXCEPTION(closeballot(non_publisher, current_ballot_id, 1),
		eosio_assert_message_exception, eosio_assert_message_is( "cannot close another account's proposal" ) 
   	);

	closeballot(publisher, current_ballot_id, 1);

	proposal_info = get_proposal(current_proposal_id);
	REQUIRE_MATCHING_OBJECT(proposal_info, mvo()
		("prop_id", current_proposal_id)
		("publisher", publisher.to_string())
		("info_url", info_url)
		("no_count", "0.0000 VOTE")
		("yes_count", "0.0000 VOTE")
		("abstain_count", "0.0000 VOTE")
		("unique_voters", uint32_t(0))
		("begin_time", begin_time)
		("end_time", end_time)
		("cycle_count", 0)
		("status", uint8_t(1))
	);

	//TODO: check unregballot again
	//TODO: this assertion msg may change if we check a proposal to see if it's closed.
	BOOST_REQUIRE_EXCEPTION(unregballot(publisher, current_ballot_id),
		eosio_assert_message_exception, eosio_assert_message_is( "cannot delete proposal once voting has begun" ) 
   	);

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( proposal_voting_weight_calcs, eosio_trail_tester ) try {
	account_name publisher = N(voteraaaaaaa);
	uint64_t current_ballot_id = 0;
	uint64_t current_proposal_id = 0;
	string info_url = "8e18fa58-f436-11e8-8eb2-f2801f1b9fd1";
	uint8_t ballot_type = 0;
	uint32_t ballot_length = 1200 + test_voters.size() * 2;
	uint32_t begin_time = now() + 20;
	uint32_t end_time   = now() + ballot_length;
	symbol test_symbol = symbol(4, "VOTE");
	symbol_code test_code = test_symbol.to_symbol_code();

	regballot(publisher, 0, test_symbol, begin_time, end_time, info_url);
	mvo settings = mvo()
		("is_destructible", 0)
		("is_proxyable", 0)
		("is_burnable", 1) //NOTE: We think this is find fine, considering the functionality of the previous unregvoter implementation
		("is_seizable", 0)
		("is_max_mutable", 1)
		("is_transferable", 0)
		("is_recastable", 1) 
		("is_initialized", 1)
		("counterbal_decay_rate", 300)
		("lock_after_initialize", 1);
	initsettings(N(eosio.trail), test_symbol, settings);
	produce_blocks(1);

	auto ballot_info = get_ballot(current_ballot_id);
	REQUIRE_MATCHING_OBJECT(ballot_info, mvo()
		("ballot_id", current_ballot_id)
		("table_id", ballot_type)
		("reference_id", current_proposal_id)
	);

	auto proposal_info = get_proposal(current_proposal_id);
	REQUIRE_MATCHING_OBJECT(proposal_info, mvo()
		("prop_id", current_proposal_id)
		("publisher", publisher.to_string())
		("info_url", info_url)
		("no_count", "0.0000 VOTE")
		("yes_count", "0.0000 VOTE")
		("abstain_count", "0.0000 VOTE")
		("unique_voters", uint32_t(0))
		("begin_time", begin_time)
		("end_time", end_time)
		("cycle_count", 0)
		("status", uint8_t(0))
	);
	
	vector<asset> vote_count = {asset(0, test_symbol), asset(0, test_symbol), asset(0, test_symbol)};
	uint32_t unique_voters = 0;

	fc::variant voter_info = mvo();
	fc::variant vote_receipt_info = mvo();
	asset currency_balance = asset::from_string("0.0000 TLOS");
	asset voter_total = asset::from_string("0.0000 VOTE");
	for (int i = 0; i < test_voters.size(); i++) {
		regvoter(test_voters[i].value, test_symbol);
		voter_info = get_voter(test_voters[i], test_code);
		REQUIRE_MATCHING_OBJECT(voter_info, mvo()
			("owner", test_voters[i].to_string())
			("tokens", "0.0000 VOTE")
		);
		
		//TODO: mirror stake and check
		mirrorcast(test_voters[i].value, test_symbol);
		voter_info = get_voter(test_voters[i], test_code);
		voter_total = asset::from_string(voter_info["tokens"].as_string());
		currency_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), test_voters[i].value);
		BOOST_REQUIRE_EQUAL(currency_balance.get_amount(), voter_total.get_amount());
		produce_blocks(1);
	}

	auto doVote = [&](vector<name> voters, int start, int end, uint64_t ballot_id, uint16_t pD, uint16_t D, vector<asset> &totals, uint32_t *unique_voters){
		for (int i = start; i < end; i++) {
			castvote(test_voters[i].value, ballot_id, D);
			produce_blocks(1);

			auto voter_info = get_voter(test_voters[i], test_code);
			auto voter_total = asset::from_string(voter_info["tokens"].as_string());
			if(i >= *unique_voters){
				++(*unique_voters);
			}else{
				totals[pD] = totals[pD] - voter_total;
			}
			
			totals[D] = totals[D] + voter_total;
		}
	};

	uint16_t prev_direction = -1, direction = 0;
	doVote(test_voters, 0, 5, current_ballot_id, prev_direction, direction, vote_count, &unique_voters);
	proposal_info = get_proposal(current_proposal_id);	
	BOOST_REQUIRE_EQUAL(asset(10000000, test_symbol), proposal_info["no_count"].as<asset>());
	BOOST_REQUIRE_EQUAL(proposal_info["no_count"].as<asset>(), vote_count[0]);
	BOOST_REQUIRE_EQUAL(proposal_info["yes_count"].as<asset>(), vote_count[1]);
	BOOST_REQUIRE_EQUAL(proposal_info["abstain_count"].as<asset>(), vote_count[2]);

	prev_direction = direction; direction = 1;
	doVote(test_voters, 3, 7, current_ballot_id, prev_direction, direction, vote_count, &unique_voters);
	proposal_info = get_proposal(current_proposal_id);	
	BOOST_REQUIRE_EQUAL(asset(6000000, test_symbol), vote_count[0]);
	BOOST_REQUIRE_EQUAL(asset(8000000, test_symbol), vote_count[1]);
	BOOST_REQUIRE_EQUAL(proposal_info["no_count"].as<asset>(), vote_count[0]);
	BOOST_REQUIRE_EQUAL(proposal_info["yes_count"].as<asset>(), vote_count[1]);
	BOOST_REQUIRE_EQUAL(proposal_info["abstain_count"].as<asset>(), vote_count[2]);
	
	prev_direction = 1; direction = 2;
	doVote(test_voters, 6, 9, current_ballot_id, prev_direction, direction, vote_count, &unique_voters);
	proposal_info = get_proposal(current_proposal_id);	
	BOOST_REQUIRE_EQUAL(asset(6000000, test_symbol), vote_count[0]);
	BOOST_REQUIRE_EQUAL(asset(6000000, test_symbol), vote_count[1]);
	BOOST_REQUIRE_EQUAL(asset(6000000, test_symbol), vote_count[2]);
	BOOST_REQUIRE_EQUAL(proposal_info["no_count"].as<asset>(), vote_count[0]);
	BOOST_REQUIRE_EQUAL(proposal_info["yes_count"].as<asset>(), vote_count[1]);
	BOOST_REQUIRE_EQUAL(proposal_info["abstain_count"].as<asset>(), vote_count[2]);
	
} FC_LOG_AND_RETHROW()

//TODO: full flow test
BOOST_FIXTURE_TEST_CASE( full_proposal_flow, eosio_trail_tester ) try {
	//TODO: regballot type 0 and check
	account_name publisher = N(voteraaaaaaa);
	uint64_t current_ballot_id = 0;
	uint64_t current_proposal_id = 0;
	string info_url = "950e7c8e-f436-11e8-8eb2-f2801f1b9fd1";
	uint8_t ballot_type = 0;
	uint32_t ballot_length = 1200 + test_voters.size() * 2;
	uint32_t begin_time = now() + 20;
	uint32_t end_time   = now() + ballot_length;
	symbol test_symbol = symbol(4, "VOTE");
	symbol_code test_code = test_symbol.to_symbol_code();

	regballot(publisher, ballot_type, test_symbol, begin_time, end_time, info_url);
	
	auto ballot_info = get_ballot(current_ballot_id);
	REQUIRE_MATCHING_OBJECT(ballot_info, mvo()
		("ballot_id", current_ballot_id)
		("table_id", ballot_type)
		("reference_id", current_proposal_id)
	);

	auto proposal_info = get_proposal(current_proposal_id);
	REQUIRE_MATCHING_OBJECT(proposal_info, mvo()
		("prop_id", current_proposal_id)
		("publisher", publisher.to_string())
		("info_url", info_url)
		("no_count", "0.0000 VOTE")
		("yes_count", "0.0000 VOTE")
		("abstain_count", "0.0000 VOTE")
		("unique_voters", uint32_t(0))
		("begin_time", begin_time)
		("end_time", end_time)
		("cycle_count", 0)
		("status", uint8_t(0))
	);
	
	asset no_count = asset(0, test_symbol);
	asset yes_count = asset(0, test_symbol);
	asset abstain_count = asset(0, test_symbol);
	uint32_t unique_voters = 0;
	produce_blocks( 41 );

	fc::variant voter_info = mvo();
	fc::variant vote_receipt_info = mvo();
	asset currency_balance = asset::from_string("0.0000 TLOS");
	asset voter_total = asset::from_string("0.0000 VOTE");
	for (int i = 0; i < test_voters.size(); i++) {
		regvoter(test_voters[i].value, test_symbol);
		voter_info = get_voter(test_voters[i], test_code);
		REQUIRE_MATCHING_OBJECT(voter_info, mvo()
			("owner", test_voters[i].to_string())
			("tokens", "0.0000 VOTE")
		);
		
		//TODO: mirror stake and check
		mirrorcast(test_voters[i].value, test_symbol);
		voter_info = get_voter(test_voters[i], test_code);
		currency_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), test_voters[i].value);
		voter_total = asset::from_string(voter_info["tokens"].as_string());
		BOOST_REQUIRE_EQUAL(currency_balance.get_amount(), voter_total.get_amount());

		uint16_t direction = std::rand() % 3;
		// std::cout << "random direction for vote: " << direction << std::endl;
		castvote(test_voters[i].value, current_ballot_id, direction);
		switch(direction) {
			case 0:
				no_count = no_count + voter_total;
				break;
			case 1:
				yes_count = yes_count + voter_total;
				break;
			case 2:
				abstain_count = abstain_count + voter_total;
				break;
		}
		unique_voters++;
		produce_blocks();

		vote_receipt_info = get_vote_receipt(test_voters[i].value, current_ballot_id);
 		std::cout << "direction: " << vote_receipt_info["directions"].get_array()[0] << std::endl;
		REQUIRE_MATCHING_OBJECT(vote_receipt_info, mvo()
			("ballot_id", current_ballot_id)
			("directions", vector<uint16_t> {direction})
			("weight", voter_total.to_string())
			("expiration", end_time)
		);

		deloldvotes(test_voters[i].value, 1);
		vote_receipt_info = get_vote_receipt(test_voters[i].value, current_ballot_id);
		BOOST_REQUIRE_EQUAL(false, vote_receipt_info.is_null());
	}
	// std::cout << "local_no_count: " << no_count.to_string() << std::endl;
	// std::cout << "local_yes_count: " << yes_count.to_string() << std::endl;
	// std::cout << "local_abstain_count: " << abstain_count.to_string() << std::endl;
	proposal_info = get_proposal(current_proposal_id);
	REQUIRE_MATCHING_OBJECT(proposal_info, mvo()
		("prop_id", current_proposal_id)
		("publisher", publisher.to_string())
		("info_url", info_url)
		("no_count", no_count.to_string())
		("yes_count", yes_count.to_string())
		("abstain_count", abstain_count.to_string())
		("unique_voters", unique_voters)
		("begin_time", begin_time)
		("end_time", end_time)
		("cycle_count", 0)
		("status", uint8_t(0))
	);
	
	//produce blocks until expiration period
	// do {
	// 	produce_blocks( 100 );
	// } while(now() < end_time);

	produce_blocks();
	produce_block(fc::seconds(end_time - now()));
	produce_blocks();
	
	// nextcycle
	begin_time = now() + 20;
	end_time   = now() + ballot_length;
	nextcycle(publisher, current_ballot_id, begin_time, end_time);
	no_count = asset(0, test_symbol);
	yes_count = asset(0, test_symbol);
	abstain_count = asset(0, test_symbol);
	unique_voters = 0;
	produce_blocks( 41 );
	for (int i = 0; i < test_voters.size(); i++) {
		//TODO: castvote and check
		deloldvotes(test_voters[i].value, 1);
		vote_receipt_info = get_vote_receipt(test_voters[i].value, current_ballot_id);
		BOOST_REQUIRE_EQUAL(true, vote_receipt_info.is_null());

		uint16_t direction = std::rand() % 3;
		std::cout << "random direction for vote: " << direction << std::endl;
		castvote(test_voters[i].value, current_ballot_id, direction);
		voter_info = get_voter(test_voters[i], test_code);
		voter_total = asset::from_string(voter_info["tokens"].as_string());
		switch(direction) {
			case 0:
				no_count = no_count + voter_total;
				break;
			case 1:
				yes_count = yes_count + voter_total;
				break;
			case 2:
				abstain_count = abstain_count + voter_total;
				break;
		}
		produce_blocks();
		vote_receipt_info = get_vote_receipt(test_voters[i].value, current_ballot_id);
		REQUIRE_MATCHING_OBJECT(vote_receipt_info, mvo()
			("ballot_id", current_ballot_id)
			("directions", vector<uint16_t> { direction })
			("weight", voter_total.to_string())
			("expiration", end_time)
		);
		unique_voters++;
	}
	
	do {
		produce_blocks( 100 );
	} while(now() < end_time);

	//closeballot and check
	closeballot(publisher, current_ballot_id, 1);
	proposal_info = get_proposal(current_proposal_id);
	REQUIRE_MATCHING_OBJECT(proposal_info, mvo()
		("prop_id", current_proposal_id)
		("publisher", publisher.to_string())
		("info_url", info_url)
		("no_count", no_count.to_string())
		("yes_count", yes_count.to_string())
		("abstain_count", abstain_count.to_string())
		("unique_voters", unique_voters)
		("begin_time", begin_time)
		("end_time", end_time)
		("cycle_count", 1)
		("status", 1)
	);
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( full_leaderboard_flow, eosio_trail_tester ) try {
	//TODO: regballot type 0 and check
	account_name publisher = N(voteraaaaaaa);
	uint64_t current_ballot_id = 0;
	uint64_t current_leaderboard_id = 0;
	string info_url = "9bd47bae-f436-11e8-8eb2-f2801f1b9fd1";
	uint8_t ballot_type = 2;
	uint32_t ballot_length = 1200 + test_voters.size() * 2;
	uint32_t begin_time = now() + 20;
	uint32_t end_time   = now() + ballot_length;
	symbol test_symbol = symbol(4, "VOTE");
	symbol_code test_code = test_symbol.to_symbol_code();

	regballot(publisher, ballot_type, test_symbol, begin_time, end_time, info_url);
	
	auto ballot_info = get_ballot(current_ballot_id);
	REQUIRE_MATCHING_OBJECT(ballot_info, mvo()
		("ballot_id", current_ballot_id)
		("table_id", ballot_type)
		("reference_id", current_leaderboard_id)
	);

	//TODO: check for greater than zero assertion, before called setseats

	setseats(publisher, current_ballot_id, 3);
	string candidate1_info = "Qm1";
	addcandidate(publisher, current_ballot_id, N(voteraaaaaab), candidate1_info);

	string candidate2_info = "Qm2";
	addcandidate(publisher, current_ballot_id, N(voteraaaaaac), candidate2_info);

	string candidate3_info = "Qm3";
	addcandidate(publisher, current_ballot_id, N(voteraaaaaad), candidate3_info);
	
	vector<mvo> candidates;
	candidates.emplace_back(mvo()
		("member", "voteraaaaaab")
		("info_link", candidate1_info)
		("votes", "0.0000 VOTE")
		("status", uint8_t(0))
	);

	candidates.emplace_back(mvo()
		("member", "voteraaaaaac")
		("info_link", candidate2_info)
		("votes", "0.0000 VOTE")
		("status", uint8_t(0))
	);

	candidates.emplace_back(mvo()
		("member", "voteraaaaaad")
		("info_link", candidate3_info)
		("votes", "0.0000 VOTE")
		("status", uint8_t(0))
	);

	auto leaderboard_info = get_leaderboard(current_leaderboard_id);
	BOOST_REQUIRE_EQUAL(false, leaderboard_info.is_null());
	BOOST_REQUIRE_EQUAL(true, leaderboard_info["candidates"].get_array().size() == 3);
	BOOST_REQUIRE_EQUAL(true, leaderboard_info["available_seats"].as_uint64() == uint64_t(3));

	uint32_t unique_voters = 0;
	produce_blocks( 41 );

	fc::variant voter_info = mvo();
	fc::variant vote_receipt_info = mvo();
	asset currency_balance = asset::from_string("0.0000 TLOS");
	asset voter_total = asset::from_string("0.0000 VOTE");
	vector<asset> candidate_votes { 
		asset::from_string("0.0000 VOTE"), 
		asset::from_string("0.0000 VOTE"), 
		asset::from_string("0.0000 VOTE")
	};
	for (int i = 0; i < test_voters.size(); i++) {
		regvoter(test_voters[i].value, test_symbol);
		voter_info = get_voter(test_voters[i], test_code);
		REQUIRE_MATCHING_OBJECT(voter_info, mvo()
			("owner", test_voters[i].to_string())
			("tokens", "0.0000 VOTE")
		);
		
		mirrorcast(test_voters[i].value, test_symbol);
		voter_info = get_voter(test_voters[i], test_code);
		currency_balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), test_voters[i].value);
		voter_total = asset::from_string(voter_info["tokens"].as_string());
		std::cout << voter_total.to_string() << std::endl;
		BOOST_REQUIRE_EQUAL(currency_balance.get_amount(), voter_total.get_amount());

		int16_t direction = std::rand() % 3;
		std::cout << "random direction for vote: " << direction << std::endl;
		vector<uint16_t> vote_directions;
		for(int16_t j = direction; j >= 0; --j) {
			std::cout << "vote #" << j << std::endl;
			dump_trace(castvote(test_voters[i].value, current_ballot_id, j));
			vote_directions.emplace_back(uint16_t(j));
			candidate_votes[j] += voter_total;
		}

		unique_voters++;
		produce_blocks( 2 );

		vote_receipt_info = get_vote_receipt(test_voters[i].value, current_ballot_id);
		BOOST_REQUIRE_EQUAL(false, vote_receipt_info.is_null());
		BOOST_REQUIRE_EQUAL(false, vote_receipt_info["directions"].is_null());
		std::cout << "directions.size(): " << vote_receipt_info["directions"].get_array().size() << std::endl;
		BOOST_REQUIRE_EQUAL(true, vote_receipt_info["directions"].get_array().size() > 0);
		REQUIRE_MATCHING_OBJECT(vote_receipt_info, mvo()
			("ballot_id", current_ballot_id)
			("directions", vote_directions)
			("weight", voter_total.to_string())
			("expiration", end_time)
		);

		deloldvotes(test_voters[i].value, 1);
		vote_receipt_info = get_vote_receipt(test_voters[i].value, current_ballot_id);
		BOOST_REQUIRE_EQUAL(false, vote_receipt_info.is_null());
	}

	for (uint8_t i = 0; i < candidates.size(); i++) {
		candidates[i]["votes"] = candidate_votes[i].to_string();
	}

	leaderboard_info = get_leaderboard(current_leaderboard_id);
	BOOST_REQUIRE_EQUAL(false, leaderboard_info.is_null());
	auto candidates_from_board = leaderboard_info["candidates"].get_array();
	BOOST_REQUIRE_EQUAL(true, candidates_from_board.size() == 3);
	BOOST_REQUIRE_EQUAL(true, leaderboard_info["available_seats"].as_uint64() == uint64_t(3));

	for(int i = 0; i < candidates_from_board.size(); i++) {
		REQUIRE_MATCHING_OBJECT(candidates[i], candidates_from_board[i]);
	}
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( custom_token_voting, eosio_trail_tester ) try {
	//TODO: regtoken for TFVT
	account_name publisher = N(voteraaaaaaa);
	string info_url = "6da746f8-f436-11e8-8eb2-f2801f1b9fd1";
	symbol test_symbol = symbol(0, "TFVT");
	symbol_code test_code = test_symbol.to_symbol_code();
	asset total_supply = asset(test_voters.size() * 5, test_symbol);
	asset per_voter = asset(total_supply.get_amount() / test_voters.size(), test_symbol);
	BOOST_REQUIRE_EQUAL(true, per_voter.get_amount() == 5);
	regtoken(total_supply, publisher, info_url);
	mvo token_settings = mvo()
		("is_destructible", 0)
		("is_proxyable", 0)
		("is_burnable", 0)
		("is_seizable", 0)
		("is_max_mutable", 1)
		("is_transferable", 0)
		("is_recastable", 0) //TODO: should change once eosio.trial recasting logic is setup for leaderboard voting
		("is_initialized", 1)
		("counterbal_decay_rate", 300)
		("lock_after_initialize", 1);

	fc::variant registration = fc::variant(mvo()
		("max_supply", total_supply)
		("supply", "0 TFVT")
		("publisher", publisher.to_string())
		("info_url", info_url)
		("settings", token_settings)
	);

	initsettings(publisher, test_symbol, token_settings);
	auto token_registry = get_registry(test_symbol);

	// REQUIRE_MATCHING_OBJECT(token_registry, registration);

	//TODO: initsettings with appropraite TFVT settings
	
	
	//TODO: issuetoken to recipients (airdrops AND airgrabs)
			//issue to a subset of voters 
			//some airdrop and some airgrab
	vector<account_name> airgrabs;
	uint16_t airgrab_count = 0;
	for(uint32_t i = 0; i < test_voters.size(); i++) {
		int16_t direction = std::rand() % 2;
		// std::cout << "random direction: " << direction << std::endl;
		if(direction == uint16_t(0)) {
			// std::cout << "airgrab" << std::endl;
			issuetoken(publisher, test_voters[i].value, per_voter, true);
			auto airgrab_info = get_airgrab(publisher, test_voters[i].value);
			REQUIRE_MATCHING_OBJECT(airgrab_info, mvo()
				("recipient", test_voters[i].to_string())
				("tokens", per_voter.to_string())
			);
			airgrabs.emplace_back(test_voters[i].value);
			airgrab_count++;
		} else {
			// std::cout << "airdrop" << std::endl;
			auto voter_info = get_voter(test_voters[i].value, test_code);
			BOOST_REQUIRE_EQUAL(true, voter_info.is_null());
			issuetoken(publisher, test_voters[i].value, per_voter, false);
			voter_info = get_voter(test_voters[i].value, test_code);
			BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
			REQUIRE_MATCHING_OBJECT(voter_info, mvo()
				("owner", test_voters[i].to_string())
				("tokens", per_voter.to_string())
			);
		}
		produce_blocks();
	}

	//TODO: claimairgrab for airgrab recipients
			//those that receive airgrabs will claim
	// std::cout << "airgrab.size(): " << airgrabs.size() << std::endl;
	// std::cout << "airgrab_count: " << airgrab_count << std::endl;
	for(uint32_t i = 0; i < airgrabs.size(); i++) {
		std::cout << "airgrab for " << i << std::endl;
		auto voter_info = get_voter(airgrabs[i], test_code);
		BOOST_REQUIRE_EQUAL(true, voter_info.is_null());
		claimairgrab(airgrabs[i], publisher, test_symbol);
		produce_blocks();
		voter_info = get_voter(airgrabs[i], test_code);
		BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
			REQUIRE_MATCHING_OBJECT(voter_info, mvo()
				("owner", airgrabs[i].to_string())
				("tokens", per_voter.to_string())
			);
	}
	
	//TODO: regballot with leaderboard type
	//TODO: check ballot and leaderboard
	uint64_t current_ballot_id = 0;
	uint64_t current_leaderboard_id = 0;
	uint8_t ballot_type = 2;
	uint32_t ballot_length = 1200 + test_voters.size() * 2;
	uint32_t begin_time = now() + 20;
	uint32_t end_time   = now() + ballot_length;
	regballot(publisher, ballot_type, test_symbol, begin_time, end_time, info_url);
	auto ballot_info = get_ballot(current_ballot_id);
	REQUIRE_MATCHING_OBJECT(ballot_info, mvo()
		("ballot_id", current_ballot_id)
		("table_id", ballot_type)
		("reference_id", current_leaderboard_id)
	);

	setseats(publisher, current_ballot_id, 3);
	string candidate1_info = "Qm1";
	addcandidate(publisher, current_ballot_id, N(voteraaaaaab), candidate1_info);

	string candidate2_info = "Qm2";
	addcandidate(publisher, current_ballot_id, N(voteraaaaaac), candidate2_info);

	string candidate3_info = "Qm3";
	addcandidate(publisher, current_ballot_id, N(voteraaaaaad), candidate3_info);
	
	vector<mvo> candidates;
	candidates.emplace_back(mvo()
		("member", "voteraaaaaab")
		("info_link", candidate1_info)
		("votes", "0 TFVT")
		("status", uint8_t(0))
	);

	candidates.emplace_back(mvo()
		("member", "voteraaaaaac")
		("info_link", candidate2_info)
		("votes", "0 TFVT")
		("status", uint8_t(0))
	);

	candidates.emplace_back(mvo()
		("member", "voteraaaaaad")
		("info_link", candidate3_info)
		("votes", "0 TFVT")
		("status", uint8_t(0))
	);
	produce_blocks(41);

	//TODO: castvote for each voter with tokens
	vector<asset> candidate_votes { 
		asset::from_string("0 TFVT"), 
		asset::from_string("0 TFVT"), 
		asset::from_string("0 TFVT")
	};
	for(uint32_t i = 0; i < test_voters.size(); i++) {
		vector<uint16_t> votes;
		auto voter_info = get_voter(test_voters[i].value, test_code);
		BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
		int16_t direction = std::rand() % 3;
		dump_trace(castvote(test_voters[i].value, current_ballot_id, direction));
		votes.emplace_back(direction);
		candidate_votes[direction] += per_voter;
		produce_blocks();
		//TODO: check vote receipts
		auto voter_receipt_info = get_vote_receipt(test_voters[i].value, current_ballot_id);
		REQUIRE_MATCHING_OBJECT(voter_receipt_info, mvo()
			("ballot_id", current_ballot_id)
			("directions", votes)
			("weight", per_voter)
			("expiration", end_time)
		);
	}
	//TODO: wait for end_time on leaderboard
	// std::cout << "now(): " << now() << std::endl;
	// std::cout << "end_time: " << end_time << std::endl;
	// std::cout << "end_time - now(): " << (end_time - now())  << std::endl;
	// std::cout << "end_time - now(): " << ((end_time - now()) * 2 + 100)  << std::endl;
	produce_blocks((end_time - now()) * 2 + 100);
	
	closeballot(publisher, current_ballot_id, 1);

	for (uint8_t i = 0; i < candidates.size(); i++) {
		candidates[i]["votes"] = candidate_votes[i].to_string();
	}

	auto leaderboard_info = get_leaderboard(current_leaderboard_id);
	BOOST_REQUIRE_EQUAL(false, leaderboard_info.is_null());
	auto candidates_from_board = leaderboard_info["candidates"].get_array();
	BOOST_REQUIRE_EQUAL(true, candidates_from_board.size() == 3);
	BOOST_REQUIRE_EQUAL(true, leaderboard_info["available_seats"].as_uint64() == uint64_t(3));

	for(int i = 0; i < candidates_from_board.size(); i++) {
		REQUIRE_MATCHING_OBJECT(candidates[i], candidates_from_board[i]);
	}
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( token_functions, eosio_trail_tester ) try {
	//TODO: regtoken
	account_name publisher = N(voteraaaaaaa);
	string info_url = "64c05ec6-f436-11e8-8eb2-f2801f1b9fd1";
	symbol test_symbol = symbol(2, "CRAIG");
	asset total_supply = asset(test_voters.size() * 500, test_symbol);
	asset per_voter = asset(total_supply.get_amount() / test_voters.size(), test_symbol);
	BOOST_REQUIRE_EQUAL(true, per_voter.get_amount() == 500);
	
	regtoken(total_supply, publisher, info_url);
	auto registry_info = get_registry(test_symbol);
	BOOST_REQUIRE_EQUAL(false, registry_info.is_null());

	regvoter(N(voteraaaaaaa), test_symbol);
	auto voter_info = get_voter(N(voteraaaaaaa), test_symbol.to_symbol_code());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaaa")
		("tokens", "0.00 CRAIG")
	);

	produce_blocks(2);

	//TODO: initsettings
	mvo token_settings = mvo()
		("is_destructible", 1)
		("is_proxyable", 0)
		("is_burnable", 1)
		("is_seizable", 1)
		("is_max_mutable", 1)
		("is_transferable", 1)
		("is_recastable", 0) //TODO: should change once eosio.trial recasting logic is setup for leaderboard voting
		("is_initialized", 1)
		("counterbal_decay_rate", 500)
		("lock_after_initialize", 0); //for easy testing

	initsettings(publisher, test_symbol, token_settings);
	registry_info = get_registry(test_symbol);
	REQUIRE_MATCHING_OBJECT(registry_info["settings"].as<mvo>(), token_settings);

	produce_blocks(2);

	//TODO: test registry destructibility
	unregtoken(test_symbol, publisher);
	registry_info = get_registry(test_symbol);
	BOOST_REQUIRE_EQUAL(true, registry_info.is_null());

	produce_blocks(2);

	//check is null

	//make registry again, initsettings again with is_destructible off
	regtoken(total_supply, publisher, info_url);
	registry_info = get_registry(test_symbol);
	BOOST_REQUIRE_EQUAL(false, registry_info.is_null());

	initsettings(publisher, test_symbol, token_settings);
	registry_info = get_registry(test_symbol);
	REQUIRE_MATCHING_OBJECT(registry_info["settings"].as<mvo>(), token_settings);

	produce_blocks(2);

	regvoter(N(voteraaaaaab), test_symbol);
	voter_info = get_voter(N(voteraaaaaab), test_symbol.to_symbol_code());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaab")
		("tokens", "0.00 CRAIG")
	);
	
	//TODO: test issuance airgrab/drop

	issuetoken(publisher, N(voteraaaaaab), per_voter, true);
	auto airgrab_info = get_airgrab(publisher, N(voteraaaaaab));
	REQUIRE_MATCHING_OBJECT(airgrab_info, mvo()
		("recipient", "voteraaaaaab")
		("tokens", per_voter.to_string())
	);
	claimairgrab(N(voteraaaaaab), publisher, test_symbol);
	airgrab_info = get_airgrab(publisher, N(voteraaaaaab));
	BOOST_REQUIRE_EQUAL(true, airgrab_info.is_null());
	voter_info = get_voter(N(voteraaaaaab), per_voter.get_symbol().to_symbol_code());
	BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaab")
		("tokens", per_voter.to_string())
	);

	issuetoken(publisher, N(voteraaaaaac), per_voter, false);
	voter_info = get_voter(N(voteraaaaaac), per_voter.get_symbol().to_symbol_code());
	BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaac")
		("tokens", per_voter.to_string())
	);

	issuetoken(publisher, N(voteraaaaaad), per_voter, true);
	airgrab_info = get_airgrab(publisher, N(voteraaaaaad));
	REQUIRE_MATCHING_OBJECT(airgrab_info, mvo()
		("recipient", "voteraaaaaad")
		("tokens", per_voter.to_string())
	);

	produce_blocks(2);

	//TODO: test token burning (unregvoter, burntoken)

	burntoken(N(voteraaaaaab), asset(100, test_symbol));
	voter_info = get_voter(N(voteraaaaaab), test_symbol.to_symbol_code());
	BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaab")
		("tokens", per_voter - asset(100, test_symbol))
	);

	unregvoter(N(voteraaaaaac), test_symbol);
	voter_info = get_voter(N(voteraaaaaac), test_symbol.to_symbol_code());
	BOOST_REQUIRE_EQUAL(true, voter_info.is_null());

	//TODO: test seizingtoken
	voter_info = get_voter(N(voteraaaaaaa), test_symbol.to_symbol_code());
	BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaaa")
		("tokens", "0.00 CRAIG")
	);
	seizetoken(publisher, N(voteraaaaaab), asset(100, test_symbol));
	voter_info = get_voter(N(voteraaaaaaa), test_symbol.to_symbol_code());
	BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaaa")
		("tokens", "1.00 CRAIG")
	);

	voter_info = get_voter(N(voteraaaaaab), test_symbol.to_symbol_code());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaab")
		("tokens", "3.00 CRAIG")
	);

	//TODO: test seize airgrab

	seizeairgrab(publisher, N(voteraaaaaad), asset(100, test_symbol));
	airgrab_info = get_airgrab(publisher, N(voteraaaaaad));
	REQUIRE_MATCHING_OBJECT(airgrab_info, mvo()
		("recipient", "voteraaaaaad")
		("tokens", (per_voter - asset(100, test_symbol)).to_string())
	);

	voter_info = get_voter(N(voteraaaaaaa), test_symbol.to_symbol_code());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaaa")
		("tokens", "2.00 CRAIG")
	);

	seizeairgrab(publisher, N(voteraaaaaad), asset(400, test_symbol));
	airgrab_info = get_airgrab(publisher, N(voteraaaaaad));
	BOOST_REQUIRE_EQUAL(true, airgrab_info.is_null());

	voter_info = get_voter(N(voteraaaaaaa), test_symbol.to_symbol_code());
	REQUIRE_MATCHING_OBJECT(voter_info, mvo()
		("owner", "voteraaaaaaa")
		("tokens", "6.00 CRAIG")
	);

	produce_blocks(2);

	//TODO: test raising/lowering max



	//TODO: test transfers and counterbalances



	//TODO: test recasting?
	//TODO: test proxyable once implemented

} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()