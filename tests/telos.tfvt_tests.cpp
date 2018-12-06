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

BOOST_FIXTURE_TEST_CASE(board_election, telos_tfvt_tester)
try
{
	//TIE BREAKER LOGIC
}
FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(board_issue, telos_tfvt_tester)
try
{
	setboard(board_members);
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
	makeissue(N(alice), N(test1), start_time, end_time, "08276642d5084cd8bc0cc10c62f782f5", trx);

	auto issue_info = get_issue(current_ballot_id);
	BOOST_REQUIRE_EQUAL(false, issue_info.is_null());
	BOOST_REQUIRE_EQUAL(issue_info["transaction"]["expiration"], pretty_trx["expiration"]);


	produce_blocks();
	produce_block(fc::seconds(issue_duration));
	produce_blocks();

	issue_info = get_issue(current_ballot_id);
	BOOST_REQUIRE_EQUAL(issue_info["transaction"]["expiration"], pretty_trx["expiration"]);
	closeissue(N(alice), current_ballot_id);
}
FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
