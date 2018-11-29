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

BOOST_AUTO_TEST_SUITE_END()