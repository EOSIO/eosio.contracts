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
	std::cout << "test_voters.size(): " << test_voters.size() << std::endl;
	for (int i = 0; i < test_voters.size(); i++) {
		std::cout << "regvoter for: " << test_voters[i].to_string() << std::endl;
		regvoter(test_voters[i].value);
		produce_blocks();
		auto voter_info = get_voter(test_voters[i]);
		
		REQUIRE_MATCHING_OBJECT(voter_info, mvo()
			("voter", test_voters[i].to_string())
			("votes", "0.0000 VOTE")
			("release_time", "0")
		);

		std::cout << "unregvoter for: " << test_voters[i].to_string() << std::endl;
		unregvoter(test_voters[i].value);
		produce_blocks();
		voter_info = get_voter(test_voters[i]);
		BOOST_REQUIRE_EQUAL(true, voter_info.is_null());
	}
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( vote_levies, eosio_trail_tester ) try {
	create_accounts({N(levytest1), N(levytest2)});
	produce_blocks( 2 );

	asset balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), N(eosio));
	std::cout << "eosio currency balance: " << balance.get_amount() << std::endl;
	//transfer 1
	transfer(N(eosio), N(levytest1), asset::from_string("1000.0000 TLOS"), "Monopoly Money");

	//from levy 1
	auto levy_info = get_vote_levy(N(eosio));

	//BOOST_REQUIRE_EQUAL(true, !levy_info.is_null());
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("voter", "eosio")
			("levy_amount", "0.0000 VOTE")
			("last_decay", now())
		);

	//to levy 1
	levy_info = get_vote_levy(N(levytest1));
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("voter", "levytest1")
			("levy_amount", "1000.0000 VOTE")
			("last_decay", now())
		);

	//transfer 2
	transfer(N(levytest1), N(levytest2), asset::from_string("200.0000 TLOS"), "Monopoly Money");

	//from 2 
	levy_info = get_vote_levy(N(levytest1));
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("voter", "levytest1")
			("levy_amount", "800.0000 VOTE")
			("last_decay", now())
		);

	//to 2
	levy_info = get_vote_levy(N(levytest2));
	REQUIRE_MATCHING_OBJECT(levy_info, mvo()
			("voter", "levytest2")
			("levy_amount", "200.0000 VOTE")
			("last_decay", now())
		);

} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE( mirror_stake, eosio_trail_tester ) try {
	std::cout << "test_voters.size(): " << test_voters.size() << std::endl;
	for (int i = 0; i < test_voters.size(); i++) {
		regvoter(test_voters[i].value);
		std::cout << "regvoter for: " << test_voters[i].to_string() << std::endl;

		asset balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), test_voters[i].value);
		std::cout << "test_voter " << test_voters[i].to_string() << ": " << balance.get_amount() << std::endl;
		mirrorstake(test_voters[i].value, 86401);
		auto voter_info = get_voter(test_voters[i]);
		auto future = now() + 86401;
		REQUIRE_MATCHING_OBJECT(voter_info, mvo()
			("voter", test_voters[i].to_string())
			("votes", "200.0000 VOTE")
			("release_time", future)
		);
		produce_blocks( 2 );

		//TODO: Transfer to a new account
		//TODO: mirrorstake new account, calculate decay, check
		//TODO: 240 block one full vote decay
	}
} FC_LOG_AND_RETHROW()

//TODO: case for reg and unreg ballot

//TODO: case for reg and unreg token

//TODO: full flow test

BOOST_AUTO_TEST_SUITE_END()