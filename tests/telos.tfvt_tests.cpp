#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <Runtime/Runtime.h>
#include <iomanip>

#include <fc/variant_object.hpp>
#include "contracts.hpp"
#include "test_symbol.hpp"
#include "telos.tfvt_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

BOOST_AUTO_TEST_SUITE(telos_tfvt_tests)

BOOST_FIXTURE_TEST_CASE(config_test, telos_tfvt_tester)
try
{
	name publisher = name("tf");
	uint8_t max_board_seats = 13; 
	uint8_t open_seats = 13;
	uint64_t open_election_id = 2;
	uint32_t holder_quorum_divisor = 3;
	uint32_t board_quorum_divisor = 4;
	uint32_t issue_duration = 5;
	uint32_t start_delay = 6;
	uint32_t leaderboard_duration = 7;
	uint32_t election_frequency = 8;
	uint32_t last_election = 0;
	
	auto expected_config = mvo()
		("publisher", publisher)
		("new_config", mvo()
			("publisher", publisher)
			("max_board_seats", max_board_seats)
			("open_seats", open_seats)
			("holder_quorum_divisor", holder_quorum_divisor)
			("board_quorum_divisor", board_quorum_divisor)
			("issue_duration", issue_duration)
			("start_delay", start_delay)
			("leaderboard_duration", leaderboard_duration)
			("election_frequency", election_frequency)
			("last_board_election_time", last_election)
			("open_election_id", open_election_id)
		);

	setconfig(publisher, expected_config);
	produce_blocks();

	auto config = get_config();
	BOOST_REQUIRE_EQUAL(config["max_board_seats"].as<uint8_t>(), max_board_seats);
	BOOST_REQUIRE_EQUAL(config["open_seats"].as<uint8_t>(), open_seats);
	BOOST_REQUIRE_EQUAL(config["holder_quorum_divisor"], holder_quorum_divisor);
	BOOST_REQUIRE_EQUAL(config["board_quorum_divisor"], board_quorum_divisor);
	BOOST_REQUIRE_EQUAL(config["issue_duration"], issue_duration);
	BOOST_REQUIRE_EQUAL(config["start_delay"], start_delay);
	BOOST_REQUIRE_EQUAL(config["leaderboard_duration"], leaderboard_duration);
	BOOST_REQUIRE_EQUAL(config["election_frequency"], election_frequency);

	BOOST_REQUIRE_EQUAL(config["open_election_id"].as<uint64_t>(), 0);

	auto token_registry = get_registry(symbol(0, "TFBOARD"));
	BOOST_REQUIRE_EQUAL(token_registry["max_supply"].as<asset>(), asset::from_string("14 TFBOARD"));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(nominate_candidate, telos_tfvt_tester)
try
{
	// get nominator, and nominee
	auto nominator = test_voters[0];
	auto nominee = test_voters[1];
	auto nontfvt = name("nontfvt");
	create_account({nontfvt.value});
	produce_blocks();
	
	BOOST_REQUIRE_EQUAL(true, get_nominee(nontfvt).is_null());
	BOOST_REQUIRE_EQUAL(true, get_nominee(nominator).is_null());
	BOOST_REQUIRE_EQUAL(true, get_nominee(nominee).is_null());

	BOOST_REQUIRE_EXCEPTION(
		nominate(nontfvt, nontfvt),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "caller must be a TFVT holder" ) 
   	);

	nominate(nontfvt, nominator);
	produce_blocks();

	REQUIRE_MATCHING_OBJECT(get_nominee(nontfvt), mvo()("nominee", nontfvt));
	BOOST_REQUIRE_EQUAL(true, get_nominee(nominator).is_null());
	BOOST_REQUIRE_EQUAL(true, get_nominee(nominee).is_null());

	BOOST_REQUIRE_EXCEPTION(
		nominate(nontfvt, nominator),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "nominee has already been nominated" ) 
   	);
	
	nominate(nominator, nominator);
	produce_blocks();

	REQUIRE_MATCHING_OBJECT(get_nominee(nominator), mvo()("nominee", nominator));
	BOOST_REQUIRE_EQUAL(true, get_nominee(nominee).is_null());

	nominate(nominee, nominator);
	produce_blocks();

	REQUIRE_MATCHING_OBJECT(get_nominee(nominee), mvo()("nominee", nominee));

	/////////////////////////////////////////////
	// ???? You can't remove a nomination ???? //
	// - maybe remove all nominees on endelection like arbitration ?
	/////////////////////////////////////////////
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(make_election, telos_tfvt_tester)
try
{
	// TODO ::: CHECK PROBLEM WITH last_board_election_time TIME SLOT = check verbose logs, 30000000000000 should be 3 , same in the test below 
	std::string info_link = "ipfs_link_to_election_info";
	auto holder = test_voters[0];
	auto nontfvt = name("nontfvt");
	name tf = name("tf");

	create_account({nontfvt.value});
	produce_blocks();

	BOOST_REQUIRE_EXCEPTION(
		makeelection(nontfvt, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "caller must be a TFVT or TFBOARD holder" ) 
   	);
	
	// term expired by deafult, no matter what we set here 
	uint32_t last_election = now();
	// and no open seats
	auto new_config = mvo()
		("publisher", tf)
		("new_config", mvo()
			("publisher", tf)
			("max_board_seats", 0)
			("open_seats", 0)
			("holder_quorum_divisor", 8)
			("board_quorum_divisor", 7)
			("issue_duration", 6)
			("start_delay", 5)
			("leaderboard_duration", 4)
			("election_frequency", 3)
			("last_board_election_time", last_election)
			("open_election_id", 0)
		);
	setconfig(tf, new_config);
	produce_blocks();

	// this would be allowed if max_board_seats > 0
	BOOST_REQUIRE_EXCEPTION(
		makeelection(holder, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "num seats must be greater than 0" ) 
   	);

	// term expired by deafult, no matter what we set here 
	// this passed with non-expired too, allowed setting last election in cfg to test it 
	last_election = now();
	// and open seats
	new_config = mvo()
		("publisher", tf)
		("new_config", mvo()
			("publisher", tf)
			("max_board_seats", 1)
			("open_seats", 1)
			("holder_quorum_divisor", 8)
			("board_quorum_divisor", 7)
			("issue_duration", 6)
			("start_delay", 100)
			("leaderboard_duration", 1000)
			("election_frequency", 10000)
			("last_board_election_time", last_election)
			("open_election_id", 0)
		);
	setconfig(tf, new_config);
	produce_blocks();

	nominate(nontfvt, holder);
	produce_blocks();

	makeelection(holder, info_link);
	produce_blocks();
	
	addcand(nontfvt, std::string("some_info_link"));
	produce_blocks();

	wdump((get_nominee(nontfvt)));

	produce_block(fc::seconds(100));
	produce_blocks();

	auto config = get_config();
	castvote(holder, config["open_election_id"].as<uint32_t>(), 0);
	produce_blocks();

	BOOST_REQUIRE_EXCEPTION(
		endelection(nontfvt),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "caller must be a TFVT or TFBOARD holder" ) 
	);

	produce_block(fc::seconds(998));
	// produce_blocks();

	BOOST_REQUIRE_EXCEPTION(
		endelection(holder),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "cannot close leaderboard while voting is still open" ) 
	);

	produce_blocks(2);

	endelection(holder);
	produce_blocks();

	BOOST_REQUIRE_EQUAL(get_nominee(nontfvt).is_null(), true);
	BOOST_REQUIRE_EQUAL(get_board_member(nontfvt)["member"].as<name>(), nontfvt);

	BOOST_REQUIRE_EXCEPTION(
		makeelection(holder, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "it isn't time for the next election" ) 
   	);
	
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(add_remove_candidate, telos_tfvt_tester)
try
{
	std::string info_link = "ipfs_link_to_credentials";
	auto nominator = test_voters[0];
	auto candidate1 = test_voters[1];
	auto nontfvt = name("nontfvt");
	name tf = name("tf");

	create_account({nontfvt.value});
	produce_blocks();

	uint32_t last_election = now();
	auto expected_config = mvo()
		("publisher", tf)
		("new_config", mvo()
			("publisher", tf)
			("max_board_seats", 2)
			("open_seats", 2)
			("holder_quorum_divisor", 8)
			("board_quorum_divisor", 7)
			("issue_duration", 6)
			("start_delay", 100)
			("leaderboard_duration", 1000)
			("election_frequency", 3)
			("last_board_election_time", last_election)
			("open_election_id", 0)
		);
	
	setconfig(tf, expected_config);

	BOOST_REQUIRE_EXCEPTION(
		addcand(candidate1, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "only nominees can be added to the election" ) 
   	);

	nominate(candidate1, nominator);
	produce_blocks();
	
	BOOST_REQUIRE_EXCEPTION(
		addcand(candidate1, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "ballot with given ballot_id doesn't exist" ) 
   	);

	makeelection(nominator, info_link);
	produce_blocks();
	
	addcand(candidate1, info_link);
	produce_blocks();

	BOOST_REQUIRE_EXCEPTION(
		addcand(candidate1, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "candidate already in leaderboard" ) 
   	);
	
	removecand(candidate1);
	addcand(candidate1, info_link);
	produce_blocks();

	BOOST_REQUIRE_EXCEPTION(
		removecand(nontfvt),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "candidate is not a nominee" ) 
   	);

	nominate(nontfvt, nominator);
	produce_blocks();

	BOOST_REQUIRE_EXCEPTION(
		removecand(nontfvt),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "candidate not found in leaderboard list" ) 
   	);

	produce_block(fc::seconds(100));
	produce_blocks();

	BOOST_REQUIRE_EXCEPTION(
		addcand(nontfvt, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "cannot add candidates once voting has begun" ) 
   	);

	BOOST_REQUIRE_EXCEPTION(
		removecand(candidate1),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "cannot remove candidates once voting has begun" ) 
   	);

	produce_block(fc::seconds(1000));
	produce_blocks();

	endelection(nominator);
	produce_blocks();

	BOOST_REQUIRE_EXCEPTION(
		removecand(candidate1),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "cannot remove candidates once voting has begun" ) 
   	);
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(weight_check, telos_tfvt_tester)
try
{
	auto holder = test_voters[0];
	std::string info_link = "some_info_is_here/believe_it/i_m_not_joking";
	prepare_election(3, 100, 2);

	removecand(board_members[2]);
	produce_blocks();
	addcand(board_members[2], info_link);
	produce_blocks();

	produce_block(fc::seconds(100));
	produce_blocks();

	// prepare for vote weight checking 
	asset weight = asset::from_string("1 TFVT"), zero_asset = asset::from_string("0 TFVT");
	vector<asset> expected_weights = {zero_asset, zero_asset, zero_asset};
	auto config = get_config();
	auto cbid = config["open_election_id"].as_uint64();   

	auto ballot = get_ballot(cbid);
	auto bid = ballot["reference_id"].as_uint64();

	//cast 6 votes
	for(int i = 0; i < 6; i++) {	
		// everyone votes candidate1 => the direction is actually candidate index for leaderboard voting
		uint16_t vote_for_candidate = 0;      
		castvote(test_voters[i].value, config["open_election_id"].as_uint64(), vote_for_candidate);
		expected_weights[vote_for_candidate] += weight;

		// todo : recast vote test ??

		// other vote :
		// every 3rd voter votes for candidate3 and others vote for candidate2
		vote_for_candidate = ( i % 3 == 0 ) ? uint16_t(2) : uint16_t(1);
		castvote(test_voters[i].value, config["open_election_id"].as_uint64(), vote_for_candidate);
		expected_weights[vote_for_candidate] += weight;

		produce_blocks(1);
	}

	// verify votes
	BOOST_REQUIRE_EQUAL(expected_weights[0], asset::from_string("6 TFVT"));
	BOOST_REQUIRE_EQUAL(expected_weights[1], asset::from_string("4 TFVT"));
	BOOST_REQUIRE_EQUAL(expected_weights[2], asset::from_string("2 TFVT"));

	auto leaderboard = get_leaderboard(bid);
	auto lid = leaderboard["board_id"].as_uint64();

	for(int i = 0 ; i < 3 ; i++){
		REQUIRE_MATCHING_OBJECT(
			leaderboard["candidates"][i], 
			mvo()
				("member", board_members[i])
				("info_link", info_link)
				("votes", expected_weights[i])
				("status", uint8_t(0))
		);
	}
	
	// election period is over
	produce_block(fc::seconds(1000));
	produce_blocks();

	config = get_config();
	cbid = config["open_election_id"].as_uint64();   

	// end the election
	dump_trace(endelection(holder));
	uint32_t expected_last_board_election_time = now();
	produce_blocks(1);

	name candidate1 = board_members[0];
	name candidate2 = board_members[1];
	name candidate3 = board_members[2];

	// candidate1 should be board member and not a nominee anymore
	auto bm = get_board_member(candidate1.value);
	uint16_t UNAVAILABLE_STATUS = 1;
	BOOST_REQUIRE_EQUAL(false, bm.is_null());
	BOOST_REQUIRE_EQUAL(bm["member"].as<name>(), candidate1);
	auto c = get_nominee(candidate1.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), true);

	auto voter_info = get_voter(candidate1.value, symbol(0, "TFBOARD").to_symbol_code());
	BOOST_REQUIRE_EQUAL(voter_info["tokens"].as<asset>(), asset::from_string("1 TFBOARD"));

	// candidate2 should be board member and not a nominee anymore
	bm = get_board_member(candidate2.value);
	BOOST_REQUIRE_EQUAL(false, bm.is_null());
	BOOST_REQUIRE_EQUAL(bm["member"].as<name>(), candidate2);
	c = get_nominee(candidate2.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), true);

	voter_info = get_voter(candidate2.value, symbol(0, "TFBOARD").to_symbol_code());
	BOOST_REQUIRE_EQUAL(voter_info["tokens"].as<asset>(), asset::from_string("1 TFBOARD"));
	
	// candidate2 should be board member and not a nominee anymore
	bm = get_board_member(candidate3.value);
	BOOST_REQUIRE_EQUAL(true, bm.is_null());
	c = get_nominee(candidate3.value);

	// todo :: this should be true , nominee is not removed atm
	BOOST_REQUIRE_EQUAL(c.is_null(), false);
	BOOST_REQUIRE_EQUAL(c["nominee"].as<name>(), candidate3);
	
	voter_info = get_voter(candidate3.value, symbol(0, "TFBOARD").to_symbol_code());
	BOOST_REQUIRE_EQUAL(voter_info.is_null(), true);

	// there is no new election in progress since no seats are left
	config = get_config();
	BOOST_REQUIRE_EQUAL(config["last_board_election_time"].as<uint32_t>(), expected_last_board_election_time);
	BOOST_REQUIRE_EQUAL(config["open_seats"].as<uint8_t>(), uint8_t(0));
	
	BOOST_REQUIRE_EXCEPTION(
		makeelection(holder, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "it isn't time for the next election" ) 
   	);

	produce_block(fc::seconds(3300));
	produce_blocks();

	prepare_election(2, 100, 3, candidate1);
	addcand(candidate3, info_link);
	produce_blocks();
	
	produce_block(fc::seconds(100));
	produce_blocks();
	cast_votes(0, 1, 1, 3);
	produce_block(fc::seconds(1000));
	produce_blocks();
	endelection(holder);	
	
	bm = get_board_member(candidate1.value);
	BOOST_REQUIRE_EQUAL(true, bm.is_null());
	c = get_nominee(candidate1.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), false);

	voter_info = get_voter(candidate1.value, symbol(0, "TFBOARD").to_symbol_code());
	BOOST_REQUIRE_EQUAL(voter_info["tokens"].as<asset>(), asset::from_string("0 TFBOARD"));

	bm = get_board_member(candidate2.value);
	BOOST_REQUIRE_EQUAL(false, bm.is_null());
	BOOST_REQUIRE_EQUAL(bm["member"].as<name>(), candidate2);
	c = get_nominee(candidate2.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), true);
	
	voter_info = get_voter(candidate2.value, symbol(0, "TFBOARD").to_symbol_code());
	BOOST_REQUIRE_EQUAL(voter_info["tokens"].as<asset>(), asset::from_string("1 TFBOARD"));

	bm = get_board_member(candidate3.value);
	BOOST_REQUIRE_EQUAL(false, bm.is_null());
	BOOST_REQUIRE_EQUAL(bm["member"].as<name>(), candidate3);
	c = get_nominee(candidate3.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), true);

	voter_info = get_voter(candidate3.value, symbol(0, "TFBOARD").to_symbol_code());
	BOOST_REQUIRE_EQUAL(voter_info["tokens"].as<asset>(), asset::from_string("1 TFBOARD"));
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(tiebreaker, telos_tfvt_tester)
try
{
	auto holder = test_voters[0];
	std::string info_link = "some_info_is_here/believe_it/i_m_not_joking";
	prepare_election(3, 100, 2);

	removecand(board_members[2]);
	produce_blocks();
	addcand(board_members[2], info_link);
	produce_blocks();

	produce_block(fc::seconds(100));
	produce_blocks();

	// prepare for vote weight checking 
	asset weight = asset::from_string("1 TFVT"), zero_asset = asset::from_string("0 TFVT");
	vector<asset> expected_weights = {zero_asset, zero_asset, zero_asset};
	auto config = get_config();
	auto cbid = config["open_election_id"].as_uint64();   

	auto ballot = get_ballot(cbid);
	auto bid = ballot["reference_id"].as_uint64();

	//cast 6 votes
	for(int i = 0; i < 6; i++) {	
		// everyone votes candidate1 => the direction is actually candidate index for leaderboard voting
		uint16_t vote_for_candidate = 0;      
		castvote(test_voters[i].value, config["open_election_id"].as_uint64(), vote_for_candidate);
		expected_weights[vote_for_candidate] += weight;

		// todo : recast vote test ??

		// other vote :
		// every 3rd voter votes for candidate3 and others vote for candidate2
		vote_for_candidate = ( i % 2 == 0 ) ? uint16_t(2) : uint16_t(1);
		castvote(test_voters[i].value, config["open_election_id"].as_uint64(), vote_for_candidate);
		expected_weights[vote_for_candidate] += weight;

		produce_blocks(1);
	}

	// verify votes
	BOOST_REQUIRE_EQUAL(expected_weights[0], asset::from_string("6 TFVT"));
	BOOST_REQUIRE_EQUAL(expected_weights[1], asset::from_string("3 TFVT"));
	BOOST_REQUIRE_EQUAL(expected_weights[2], asset::from_string("3 TFVT"));

	auto leaderboard = get_leaderboard(bid);
	auto lid = leaderboard["board_id"].as_uint64();

	for(int i = 0 ; i < 3 ; i++){
		REQUIRE_MATCHING_OBJECT(
			leaderboard["candidates"][i], 
			mvo()
				("member", board_members[i])
				("info_link", info_link)
				("votes", expected_weights[i])
				("status", uint8_t(0))
		);
	}
	
	// election period is over
	produce_block(fc::seconds(1000));
	produce_blocks();

	config = get_config();
	cbid = config["open_election_id"].as_uint64();   

	std::cout<<"PREVIOUS NOW > "<<now()<<std::endl;
	// end the election
	endelection(holder);
	uint32_t expected_last_board_election_time = now();
	produce_blocks(1);

	name candidate1 = board_members[0];
	name candidate2 = board_members[1];
	name candidate3 = board_members[2];

	// candidate1 should be board member and not a nominee anymore
	auto bm = get_board_member(candidate1.value);
	uint16_t UNAVAILABLE_STATUS = 1;
	BOOST_REQUIRE_EQUAL(false, bm.is_null());
	BOOST_REQUIRE_EQUAL(bm["member"].as<name>(), candidate1);
	auto c = get_nominee(candidate1.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), true);
	
	// candidate2 should be board member and not a nominee anymore
	bm = get_board_member(candidate2.value);
	BOOST_REQUIRE_EQUAL(true, bm.is_null());
	c = get_nominee(candidate2.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), false);
	BOOST_REQUIRE_EQUAL(c["nominee"].as<name>(), candidate2);

	// candidate3 should not be a bm
	bm = get_board_member(candidate3.value);
	BOOST_REQUIRE_EQUAL(true, bm.is_null());
	c = get_nominee(candidate3.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), false);
	BOOST_REQUIRE_EQUAL(c["nominee"].as<name>(), candidate3);
	
	// there is no new election in progress since no seats are left
	config = get_config();
	BOOST_REQUIRE_EQUAL(config["last_board_election_time"].as<uint32_t>(), expected_last_board_election_time);
	BOOST_REQUIRE_EQUAL(config["open_seats"].as<uint8_t>(), uint8_t(1));

	// allow to make election and add the leftover candidates to a new election
	makeelection(holder, info_link);
	addcand(candidate2, info_link);
	addcand(candidate3, info_link);
	produce_blocks();

	produce_block(fc::seconds(100));
	produce_blocks();

	config = get_config();
	//cast 6 votes
	for(int i = 0; i < 6; i++) {	
		uint16_t vote_for_candidate = ( i % 3 == 0 ) ? uint16_t(1) : uint16_t(0);
		castvote(test_voters[i].value, config["open_election_id"].as_uint64(), vote_for_candidate);
		produce_blocks(1);
	}

	produce_block(fc::seconds(1000));
	produce_blocks();

	std::cout<<"NOW > "<<now()<<std::endl;
	endelection(holder);
	produce_blocks();

	// candidate1 should be board member and not a nominee anymore
	bm = get_board_member(candidate2.value);
	BOOST_REQUIRE_EQUAL(false, bm.is_null());
	BOOST_REQUIRE_EQUAL(bm["member"].as<name>(), candidate2);
	c = get_nominee(candidate2.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), true);
	
	wdump((get_config()));

	// candidate1 should be board member and not a nominee anymore
	bm = get_board_member(candidate1.value);
	BOOST_REQUIRE_EQUAL(false, bm.is_null());
	BOOST_REQUIRE_EQUAL(bm["member"].as<name>(), candidate1);
	c = get_nominee(candidate1.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), true);
	
	// candidate2 should not be board member 
	bm = get_board_member(candidate3.value);
	BOOST_REQUIRE_EQUAL(true, bm.is_null());
	c = get_nominee(candidate3.value);
	BOOST_REQUIRE_EQUAL(c.is_null(), false);
	BOOST_REQUIRE_EQUAL(c["nominee"].as<name>(), candidate3);


	BOOST_REQUIRE_EXCEPTION(
		makeelection(holder, info_link),
		eosio_assert_message_exception, 
		eosio_assert_message_is( "it isn't time for the next election" ) 
   	);

	produce_block(fc::seconds(2200));
	
	makeelection(holder, info_link);
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(board_issue, telos_tfvt_tester)
try
{
	prepare_election(12);
	produce_block(fc::seconds(100));
	produce_blocks();
	cast_votes(0, 1, 0, 12);
	produce_block(fc::seconds(1000));
	produce_blocks();
	endelection(test_voters[0]);	

	produce_blocks(2);
	//TODO: verify permissions
	vector<permission_level> perm;

	for (auto m : board_members)
	{
		perm.emplace_back(permission_level{m, N(active)});
	}
	variant pretty_trx = fc::mutable_variant_object()
		("expiration", "2021-01-01T00:30:00")
		("ref_block_num", 2)
		("ref_block_prefix", 3)
		("max_net_usage_words", 0)
		("max_cpu_usage_ms", 0)
		("delay_sec", 0)
		("actions", 
			fc::variants({fc::mutable_variant_object()
				("account", name("eosio.token"))
				("name", "transfer")
				("authorization", perm)
				("data", fc::mutable_variant_object()
					("from", "tf")
					("to", "bob")
					("quantity", "10.0000 TLOS")
					("memo", "foo bar"))}));

	transaction trx;
	abi_serializer::from_variant(pretty_trx, trx, get_resolver(), abi_serializer_max_time);
	
	std::cout << "trx expiration: " << trx.expiration.to_iso_string() << std::endl;

	uint32_t issue_duration = 2500000;
	uint32_t start_time = now();
	uint32_t end_time = now() + issue_duration;
	uint64_t current_ballot_id = 0;
	std::cout << "makeissue" << std::endl;
	makeissue(test_voters[0].value, N(test1), "08276642d5084cd8bc0cc10c62f782f5", trx);

	auto issue_info = get_issue(test_voters[0].value);
	BOOST_REQUIRE_EQUAL(false, issue_info.is_null());
	BOOST_REQUIRE_EQUAL(issue_info["transaction"]["expiration"], pretty_trx["expiration"]);


	produce_blocks();
	produce_block(fc::seconds(issue_duration));
	produce_blocks();

	issue_info = get_issue(test_voters[0].value);
	BOOST_REQUIRE_EQUAL(issue_info["transaction"]["expiration"], pretty_trx["expiration"]);
	std::cout << "closeissue" << std::endl;
	dump_trace(closeissue(test_voters[0].value, test_voters[0].value));
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
