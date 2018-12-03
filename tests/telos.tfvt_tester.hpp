#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/name.hpp>
#include <eosio.trail_tester.hpp>
#include <iostream>

#include <eosio/chain/wast_to_wasm.hpp>
#include <Runtime/Runtime.h>
#include <math.h>

#include <fc/variant_object.hpp>

#include <contracts.hpp>
#include "test_symbol.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

#define NUM_VOTERS 128

using mvo = fc::mutable_variant_object;

class telos_tfvt_tester : eosio_trail_tester {
  public:
	abi_serializer abi_ser;
	abi_serializer token_ser;

	telos_tfvt_tester() {

	}

#pragma region trx
	transaction_trace_ptr setconfig(account_name member, mvo config) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(setconfig), vector<permission_level>{{member, config::active_name}},
			config
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(member, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr nominate(account_name nominee, account_name nominator) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(nominate), vector<permission_level>{{nominator, config::active_name}},
			("nominee", nominee)
			("nominator", nominator)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(nominator, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr makeissue(account_name holder, uint32_t begin_time, uint32_t end_time, string info_url) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(makeissue), vector<permission_level>{{holder, config::active_name}},
			("holder", holder)
			("begin_time", begin_time)
			("end_time", end_time)
			("info_url", info_url)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr closeissue(account_name holder, uint64_t ballot_id) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(closeissue), vector<permission_level>{{holder, config::active_name}},
			("holder", holder)
			("ballot_id", ballot_id)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr makelboard(account_name holder, uint32_t begin_time, uint32_t end_time, string info_url) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(makelboard), vector<permission_level>{{holder, config::active_name}},
			("holder", holder)
			("begin_time", begin_time)
			("end_time", end_time)
			("info_url", info_url)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr closelboard(account_name holder, uint64_t ballot_id) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(makelboard), vector<permission_level>{{holder, config::active_name}},
			("holder", holder)
			("ballot_id", ballot_id)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}
#pragma endregion trx_funcs

#pragma region get_funcs
	fc::variant get_voter(account_name voter, symbol_code scope) {
		vector<char> data = get_row_by_account(N(eosio.trail), scope.value, N(balances), voter);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("balance", data, abi_serializer_max_time);
	}
#pragma endregion get_funcs
	
};