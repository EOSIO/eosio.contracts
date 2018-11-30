#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/name.hpp>
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

class eosio_trail_tester : public tester
{
  public:
	abi_serializer abi_ser;
	abi_serializer token_ser;

	vector<name> test_voters;

	eosio_trail_tester()
	{
		produce_blocks( 2 );
		create_accounts({N(eosio.token), N(eosio.ram), N(eosio.ramfee), N(eosio.stake),
						 N(eosio.bpay), N(eosio.vpay), N(eosio.saving), N(eosio.names), N(eosio.trail)});
		produce_blocks( 2 );

		set_code(N(eosio.token), contracts::token_wasm());
		set_abi(N(eosio.token), contracts::token_abi().data());
		{
			const auto &accnt = control->db().get<account_object, by_name>(N(eosio.token));
			abi_def abi;
			BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
			token_ser.set_abi(abi, abi_serializer_max_time);
		}
		create(N(eosio), asset::from_string("10000000000.0000 TLOS"));
		issue(N(eosio), N(eosio), asset::from_string("1000000000.0000 TLOS"), "Initial amount!");
		produce_blocks( 2 );

		vector<name> voters;
		string temp_name = "";
		name curr = name("");
		asset balance = asset::from_string("0.0000 TLOS");
		for (int i = 0; i < NUM_VOTERS; i++) {
			produce_blocks(1);
			temp_name = "voter" + toBase31(i);
			curr = eosio::chain::name(temp_name);
			voters.emplace_back(curr);
			create_accounts({curr.value});
			produce_blocks(1);
			transfer(N(eosio), curr.value, asset::from_string("200.0000 TLOS"), "Monopoly Money");
			balance = get_currency_balance(N(eosio.token), symbol(4, "TLOS"), curr.value);
			BOOST_REQUIRE_EQUAL(asset::from_string("200.0000 TLOS").get_amount(), balance.get_amount());
			produce_blocks( 2 );
		}
		test_voters = voters;
		produce_blocks( 2 );

		deploy_contract();
		produce_blocks( 2 );
		asset max_supply = asset::from_string("10000000000.0000 VOTE");
		string info_url = "Qmdsafkjhasdlfjh";
		regtoken(max_supply, N(eosio.trail), info_url);
		mvo settings = mvo()
			("is_destructible", 0)
			("is_proxyable", 0)
			("is_burnable", 1) //NOTE: We think this is find fine, considering the functionality of the previous unregvoter implementation
			("is_seizable", 0)
			("is_max_mutable", 1)
			("is_transferable", 0)
			("is_recastable", 0) //TODO: should change once eosio.trial recasting logic is setup for leaderboard voting
			("is_initialized", 1)
			("counterbal_decay_rate", 300)
			("lock_after_initialize", 1);
		initsettings(N(eosio.trail), symbol(4, "VOTE"), settings);
		auto token_registry = get_registry(symbol(4, "VOTE"));
		BOOST_REQUIRE_EQUAL(settings["is_burnable"], token_registry["settings"].as<mvo>()["is_burnable"]);
		std::cout << "=======================END SETUP==============================" << std::endl;
	}

	#pragma region Setup_Actions
	void deploy_contract() {
      set_code( N(eosio.trail), contracts::trail_wasm() );
      set_abi( N(eosio.trail), contracts::trail_abi().data() );
      {
         const auto& accnt = control->db().get<account_object,by_name>( N(eosio.trail) );
         abi_def abi;
         BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
         abi_ser.set_abi(abi, abi_serializer_max_time);
      }
   }

   uint32_t now() {
	   return (control->pending_block_time().time_since_epoch().count() / 1000000);
   }

   string base31 = "abcdefghijklmnopqrstuvwxyz12345";
   string toBase31(uint32_t in) {
	   vector<uint32_t> out = { 0, 0, 0, 0, 0, 0, 0 };
	   uint32_t remainder = in;
	   uint32_t divisor = 0;
	   uint32_t quotient = 0;
	   for (int i = 0; i < out.size(); i++) {
		   divisor = pow(31, out.size() - 1 - i);
		   quotient = remainder / divisor;
		   remainder = remainder - (quotient * divisor);
		   out[i] = quotient;
	   }
	   string output = "aaaaaaa";
	   for (int i = 0; i < out.size(); i++) {
		   output[i] = base31[out[i]];
	   }

	   return output;
   }

	action_result create(account_name issuer,
						 asset maximum_supply)
	{
		return push_action(N(eosio.token), N(create), mvo()("issuer", issuer)("maximum_supply", maximum_supply));
	}

	action_result issue(account_name issuer, account_name to, asset quantity, string memo)
	{
		return push_action(issuer, N(issue), mvo()("to", to)("quantity", quantity)("memo", memo));
	}

	transaction_trace_ptr transfer(account_name from, account_name to, asset amount, string memo) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.token), N(transfer), vector<permission_level>{{from, config::active_name}},
			mvo()
			("from", from)
			("to", to)
			("quantity", amount)
			("memo", memo)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(from, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	action_result push_action(const account_name &signer, const action_name &name, const variant_object &data)
	{
		string action_type_name = token_ser.get_action_type(name);

		action act;
		act.account = N(eosio.token);
		act.name = name;
		act.data = token_ser.variant_to_binary(action_type_name, data, abi_serializer_max_time);

		return base_tester::push_action(std::move(act), uint64_t(signer));
	}

	action_result trail_push_action(const account_name &signer, const action_name &name, const variant_object &data)
	{
		string action_type_name = abi_ser.get_action_type(name);

		action act;
		act.account = N(eosio.trail);
		act.name = name;
		act.data = abi_ser.variant_to_binary(action_type_name, data, abi_serializer_max_time);

		return base_tester::push_action(std::move(act), uint64_t(signer));
	}

	#pragma endregion Setup_Actions

	#pragma region Get_Functions

	fc::variant get_account(account_name acc, const string &symbolname)
	{
		auto symb = eosio::chain::symbol::from_string(symbolname);
		auto symbol_code = symb.to_symbol_code().value;
		vector<char> data = get_row_by_account(N(eosio.token), acc, N(accounts), symbol_code);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("account", data, abi_serializer_max_time);
	}
	
	fc::variant get_trail_env() {
		vector<char> data = get_row_by_account( N(eosio.trail), N(eosio.trail), N(environment), N(environment) );
		if (data.empty()) std::cout << "\nData is empty\n" << std::endl;
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant( "env", data, abi_serializer_max_time );
	}

	fc::variant get_voter(account_name voter, symbol_code scope) {
		vector<char> data = get_row_by_account(N(eosio.trail), scope.value, N(balances), voter);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("balance", data, abi_serializer_max_time);
	}

	fc::variant get_vote_receipt(account_name voter, uint64_t ballot_id) {
		vector<char> data = get_row_by_account(N(eosio.trail), voter, N(votereceipts), ballot_id);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("vote_receipt", data, abi_serializer_max_time);
	}

	fc::variant get_leaderboard(uint64_t board_id) {
		vector<char> data = get_row_by_account(N(eosio.trail), N(eosio.trail), N(leaderboards), board_id);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("leaderboard", data, abi_serializer_max_time);
	}

	fc::variant get_ballot(uint64_t ballot_id) {
		vector<char> data = get_row_by_account(N(eosio.trail), N(eosio.trail), N(ballots), ballot_id);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("ballot", data, abi_serializer_max_time);
	}

	fc::variant get_proposal(uint64_t proposal_id) {
		vector<char> data = get_row_by_account(N(eosio.trail), N(eosio.trail), N(proposals), proposal_id);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("proposal", data, abi_serializer_max_time);
	}

	fc::variant get_vote_counter_bal(account_name acc, symbol_code scope)
	{
		vector<char> data = get_row_by_account(N(eosio.trail), scope.value, N(counterbals), acc);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("counter_balance", data, abi_serializer_max_time);
	}

	fc::variant get_registry(symbol sym)
	{
		vector<char> data = get_row_by_account(N(eosio.trail), N(eosio.trail), N(registries), sym.to_symbol_code());
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("registry", data, abi_serializer_max_time);
	}

	fc::variant get_airgrab(account_name publisher, account_name recipient)
	{
		vector<char> data = get_row_by_account(N(eosio.trail), publisher, N(airgrabs), recipient);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("airgrab", data, abi_serializer_max_time);
	}

	#pragma endregion Get_Functions

	#pragma region Voting_Actions

	transaction_trace_ptr regvoter(account_name voter, symbol token_symbol) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(regvoter), vector<permission_level>{{voter, config::active_name}},
			mvo()
			("voter", voter)
			("token_symbol", token_symbol)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(voter, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr unregvoter(account_name voter, symbol token_symbol) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(unregvoter), vector<permission_level>{{voter, config::active_name}},
			mvo()
			("voter", voter)
			("token_symbol", token_symbol)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(voter, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr mirrorcast(account_name voter, symbol sym) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(mirrorcast), vector<permission_level>{{voter, config::active_name}},
			mvo()
			("voter", voter)
			("token_symbol", sym)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(voter, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr castvote(account_name voter, uint32_t ballot_id, uint16_t direction) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(castvote), vector<permission_level>{{voter, config::active_name}},
			mvo()
			("voter", voter)
			("ballot_id", ballot_id)
			("direction", direction)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(voter, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr deloldvotes(account_name voter, uint16_t num_to_delete) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(deloldvotes), vector<permission_level>{{voter, config::active_name}},
			mvo()
			("voter", voter)
			("num_to_delete", num_to_delete)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(voter, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	#pragma endregion Voting_Actions

	#pragma region Token_Action

	transaction_trace_ptr issuetoken(account_name publisher, account_name recipient, asset tokens, bool airgrab) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(issuetoken), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("recipient", recipient)
			("tokens", tokens)
			("airgrab", airgrab)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr claimairgrab(account_name claimant, account_name publisher, symbol token_symbol) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(claimairgrab), vector<permission_level>{{claimant, config::active_name}},
			mvo()
			("claimant", claimant)
			("publisher", publisher)
			("token_symbol", token_symbol)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(claimant, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr initsettings(account_name publisher, symbol token_symbol, mvo new_settings) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(initsettings), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("token_symbol", token_symbol)
			("new_settings", new_settings)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr burntoken(account_name balance_owner, asset amount) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(burntoken), vector<permission_level>{{balance_owner, config::active_name}},
			mvo()
			("balance_owner", balance_owner)
			("amount", amount)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(balance_owner, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr seizetoken(account_name publisher, account_name owner, asset tokens) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(seizetoken), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("owner", owner)
			("tokens", tokens)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr seizeairgrab(account_name publisher, account_name recipient, asset amount) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(seizeairgrab), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("recipient", recipient)
			("amount", amount)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr raisemax(account_name publisher, asset amount) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(raisemax), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("amount", amount)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr lowermax(account_name publisher, asset amount) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(lowermax), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("amount", amount)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr transfer(account_name sender, account_name recipient, asset amount) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(transfer), vector<permission_level>{{sender, config::active_name}},
			mvo()
			("sender", sender)
			("recipient", recipient)
			("amount", amount)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(sender, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr regtoken(asset max_supply, name publisher, string info_url) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(regtoken), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("max_supply", max_supply)
			("publisher", publisher)
			("info_url", info_url)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr unregtoken(symbol token_symbol, account_name publisher) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(unregtoken), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("token_symbol", token_symbol)
			("publisher", publisher)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	#pragma endregion Token_Actions

	#pragma region Publisher_Actions

	transaction_trace_ptr regballot(account_name publisher, uint8_t ballot_type, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(regballot), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("ballot_type", ballot_type)
			("voting_symbol", voting_symbol)
			("begin_time", begin_time)
			("end_time", end_time)
			("info_url", info_url)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr unregballot(account_name publisher, uint64_t ballot_id) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(unregballot), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("ballot_id", ballot_id)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr nextcycle(account_name publisher, uint64_t ballot_id, uint32_t new_begin_time, uint32_t new_end_time) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(nextcycle), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("ballot_id", ballot_id)
			("new_begin_time", new_begin_time)
			("new_end_time", new_end_time)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr closeballot(account_name publisher, uint64_t ballot_id, uint8_t pass) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(closeballot), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("ballot_id", ballot_id)
			("pass", pass)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr setseats(account_name publisher, uint64_t ballot_id, uint8_t num_seats) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(setseats), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("ballot_id", ballot_id)
			("num_seats", num_seats)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr addcandidate(account_name publisher, uint64_t ballot_id, account_name new_candidate, string info_link) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(eosio.trail), N(addcandidate), vector<permission_level>{{publisher, config::active_name}},
			mvo()
			("publisher", publisher)
			("ballot_id", ballot_id)
			("new_candidate", new_candidate)
			("info_link", info_link)
			)
		);
		set_transaction_headers(trx);
		trx.sign(get_private_key(publisher, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	#pragma endregion Publisher_Actions

	#pragma region Common_Helpers

	void register_voters(vector<name> test_voters, int start, int end, symbol smb){
		for (int i = start; i < end; i++) {
			regvoter(test_voters[i].value, smb);
			produce_blocks(1);

			auto voter_info = get_voter(test_voters[i], smb.to_symbol_code());
			REQUIRE_MATCHING_OBJECT(voter_info, mvo()
				("owner", test_voters[i].to_string())
				("tokens", std::string(std::string("0.0000 ") + smb.name()))
			);
		}
	}

	template<typename Lambda>
	void voter_map(int start, int end, Lambda&& func) {
		BOOST_REQUIRE_EQUAL(true, start <= end);
		BOOST_REQUIRE_EQUAL(true, end <= test_voters.size());
		for (int i = start; i < end; i++) {
			func(test_voters[i]);
		}
	}
      
	asset get_balance( const account_name& act, symbol balance_symbol = symbol{CORE_SYM}, const account_name& contract = N(eosio.token) ) {
		return get_currency_balance(contract, balance_symbol, act);
	}

	#pragma endregion Common_Helpers

	void dump_trace(transaction_trace_ptr trace_ptr) {
		std::cout << std::endl << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
		for(auto trace : trace_ptr->action_traces) {
			std::cout << "action_name trace: " << trace.act.name.to_string() << std::endl;
			//TODO: split by new line character, loop and indent output
			std::cout << trace.console << std::endl << std::endl;
		}
		std::cout << std::endl << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl << std::endl;
	}
};