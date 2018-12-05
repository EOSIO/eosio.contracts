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

BOOST_FIXTURE_TEST_CASE( token_registration, telos_tfvt_tester) try {
	string initial_info_link = "3a1db1cf0b4344b59a1ddeb4bc317548";

	symbol tfvt_sym = symbol(0, "TFVT");
	symbol_code tfvt_code = tfvt_sym.to_symbol_code();

	symbol board_sym = symbol(0, "TFBOARD");
	symbol_code board_code = board_sym.to_symbol_code();

	inittfvt(initial_info_link);
	inittfboard(initial_info_link);

	mvo token_settings = mvo()
		("is_destructible", 0)
		("is_proxyable", 0)
		("is_burnable", 0)
		("is_seizable", 0)
		("is_max_mutable", 1)
		("is_transferable", 0)
		("is_recastable", 1)
		("is_initialized", 1)
		("counterbal_decay_rate", 500)
		("lock_after_initialize", 1);

	auto token_registry = get_registry(tfvt_sym);

	REQUIRE_MATCHING_OBJECT(token_registry["settings"], token_settings);

	token_registry = get_registry(board_sym);
	token_settings["is_recastable"] = 0;
	REQUIRE_MATCHING_OBJECT(token_registry["settings"], token_settings);
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( board_election, telos_tfvt_tester) try {
	//TIE BREAKER LOGIC
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( board_issue, telos_tfvt_tester) try {
	
} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
