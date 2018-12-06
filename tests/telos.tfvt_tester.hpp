#include "eosio.trail_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

#define NUM_VOTERS 128

using mvo = fc::mutable_variant_object;

class telos_tfvt_tester : public eosio_trail_tester {
  public:
	abi_serializer abi_ser;
	abi_serializer token_ser;
	abi_serializer msig_ser;

	vector<account_name> board_members {
		N(boardmem1a), 
		N(boardmem1b), 
		N(boardmem1c), 
		N(boardmem1d), 
		N(boardmem1e), 
		N(boardmem1f), 
		N(boardmem1g),
		N(boardmem1h),
		N(boardmem1i),
		N(boardmem1j),
		N(boardmem1k),
		N(boardmem1l)
	};
	telos_tfvt_tester() {
		create_accounts({
			N(tf),
			N(boardmem1a), 
			N(boardmem1b), 
			N(boardmem1c), 
			N(boardmem1d), 
			N(boardmem1e), 
			N(boardmem1f), 
			N(boardmem1g),
			N(boardmem1h),
			N(boardmem1i),
			N(boardmem1j),
			N(boardmem1k),
			N(boardmem1l)
		});
		deploy_contract();
		produce_blocks();
		deploy_msig();
		produce_blocks();
		transfer(N(eosio), N(tf), asset::from_string("10000.0000 TLOS"), "Monopoly Money");

		string initial_info_link = "3a1db1cf0b4344b59a1ddeb4bc317548";

		symbol tfvt_sym = symbol(0, "TFVT");
		symbol_code tfvt_code = tfvt_sym.to_symbol_code();

		symbol board_sym = symbol(0, "TFBOARD");
		symbol_code board_code = board_sym.to_symbol_code();

		inittfvt(initial_info_link);
		inittfboard(initial_info_link);

		mvo token_settings = mvo()("is_destructible", 0)("is_proxyable", 0)("is_burnable", 0)("is_seizable", 0)("is_max_mutable", 1)("is_transferable", 0)("is_recastable", 1)("is_initialized", 1)("counterbal_decay_rate", 500)("lock_after_initialize", 1);

		auto token_registry = get_registry(tfvt_sym);

		REQUIRE_MATCHING_OBJECT(token_registry["settings"], token_settings);

		token_registry = get_registry(board_sym);
		token_settings["is_recastable"] = 0;
		REQUIRE_MATCHING_OBJECT(token_registry["settings"], token_settings);
		std::cout << time_point_sec(now()).to_iso_string() << std::endl;
	}

	void deploy_contract()
    {
        set_code(N(tf), contracts::tfvt_wasm());
        set_abi(N(tf), contracts::tfvt_abi().data());
        {
            const auto &accnt = control->db().get<account_object, by_name>(N(tf));
            abi_def abi;
            BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
            abi_ser.set_abi(abi, abi_serializer_max_time);
        }
    }

	void deploy_msig() {
		create_accounts( { N(eosio.msig), N(alice), N(bob), N(carol) } );
		produce_block();

		auto trace = base_tester::push_action(config::system_account_name, N(setpriv),
												config::system_account_name,  mutable_variant_object()
												("account", "eosio.msig")
												("is_priv", 1)
		);

		set_code( N(eosio.msig), contracts::msig_wasm() );
		set_abi( N(eosio.msig), contracts::msig_abi().data() );

		produce_blocks();
		const auto& accnt = control->db().get<account_object,by_name>( N(eosio.msig) );
		abi_def abi;
		BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
		msig_ser.set_abi(abi, abi_serializer_max_time);
	}

	void set_contract_authority()
	{

	}

#pragma region trx
	transaction_trace_ptr inittfvt(string initial_info_link) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(inittfvt), vector<permission_level>{{N(tf), config::active_name}},
			mvo()
			("initial_info_link", initial_info_link)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(N(tf), "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr inittfboard(string initial_info_link) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(inittfboard), vector<permission_level>{{N(tf), config::active_name}},
			mvo()
			("initial_info_link", initial_info_link)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(N(tf), "active"), control->get_chain_id());
		return push_transaction( trx );
	}		

	transaction_trace_ptr setconfig(account_name member, mvo config) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(setconfig), vector<permission_level>{{member, config::active_name}},
			config
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(member, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr nominate(account_name nominee, account_name nominator) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(nominate), vector<permission_level>{{nominator, config::active_name}},
			mvo()
			("nominee", nominee)
			("nominator", nominator)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(nominator, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr makeissue(account_name holder, account_name issue_name, uint32_t begin_time, uint32_t end_time, string info_url, transaction trans) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(makeissue), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
			("begin_time", begin_time)
			("end_time", end_time)
			("info_url", info_url)
			("issue_name", issue_name)
			("transaction", trans)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr closeissue(account_name holder, uint64_t ballot_id) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(closeissue), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
			("ballot_id", ballot_id)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr makeelection(account_name holder, uint32_t begin_time, uint32_t end_time, string info_url) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(makeelection), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
			("begin_time", begin_time)
			("end_time", end_time)
			("info_url", info_url)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr endelection(account_name holder, uint64_t ballot_id) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(endelection), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
			("ballot_id", ballot_id)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr addallcands(account_name holder, uint64_t ballot_id, vector<mvo> new_cands) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(addallcands), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
			("ballot_id", ballot_id)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr setboard(vector<account_name> members) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(setboard), vector<permission_level>{{N(tf), config::active_name}},
			mvo()
			("members", members)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(N(tf), "active"), control->get_chain_id());
		return push_transaction( trx );
	}
#pragma endregion trx_funcs

#pragma region get_funcs
	fc::variant get_nominee(account_name nominee) {
		vector<char> data = get_row_by_account(N(tf), N(tf), N(nominees), nominee);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("board_nominee", data, abi_serializer_max_time);
	}

	fc::variant get_board_member(account_name member) {
		vector<char> data = get_row_by_account(N(tf), N(tf), N(nominees), member);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("board_member", data, abi_serializer_max_time);
	}

	fc::variant get_config(account_name publisher) {
		vector<char> data = get_row_by_account(N(tf), N(tf), N(configs), publisher);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("config", data, abi_serializer_max_time);
	}

	fc::variant get_issue(uint64_t issue_id) {
		vector<char> data = get_row_by_account(N(tf), N(tf), N(issues), issue_id);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("issue", data, abi_serializer_max_time);
	}
#pragma endregion get_funcs

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