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
		create_accounts({N(tf)});
		create_accounts(board_members);
		produce_blocks();

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

		voter_map(0, test_voters.size(), [&](auto& voter) {
			issuetoken(N(tf), voter.value, asset(1, tfvt_sym), false);
			produce_blocks();
			auto voter_info = get_voter(voter.value, tfvt_code);
			BOOST_REQUIRE_EQUAL(false, voter_info.is_null());
		});

		mvo token_settings = mvo()("is_destructible", 0)("is_proxyable", 0)("is_burnable", 0)("is_seizable", 0)("is_max_mutable", 1)("is_transferable", 0)("is_recastable", 1)("is_initialized", 1)("counterbal_decay_rate", 500)("lock_after_initialize", 1);

		auto token_registry = get_registry(tfvt_sym);

		REQUIRE_MATCHING_OBJECT(token_registry["settings"], token_settings);

		token_registry = get_registry(board_sym);
		token_settings["is_recastable"] = 0;
		// is_seizable = 0 => TFVT
		// is_seizable = 1 => TFBOARD
		token_settings["is_seizable"] = 1;
		token_settings["is_burnable"] = 1;
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

	void prepare_election(int candidate_count, uint32_t start_delay = 100, uint8_t max_board_seats = 12, name publisher = name("tf") ){
		auto holder = test_voters[0];
		std::string info_link = "some_info_is_here/believe_it/i_m_not_joking";

		uint8_t open_seats = max_board_seats;
		uint64_t open_election_id = 0;
		uint32_t holder_quorum_divisor = 3;
		uint32_t board_quorum_divisor = 4;
		uint32_t issue_duration = start_delay * 10;
		uint32_t leaderboard_duration = start_delay * 10;
		uint32_t election_frequency = (start_delay + leaderboard_duration) * 3;
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
		makeelection(holder, info_link);
		produce_blocks();

		for(auto &bm : board_members){
			if(candidate_count-- == 0) break;

			nominate(bm, holder);
			addcand(bm, info_link);
			produce_blocks();
		}
	}

	void cast_votes(int voters_start, int voters_end, int candidate_start, int candidate_end){
		auto config = get_config();
		uint64_t bid = config["open_election_id"].as<uint64_t>();

		for(int i = voters_start ; i < voters_end ; i++){
			for(uint16_t j = candidate_start ; j < candidate_end ; j++){
				castvote(test_voters[i], bid, j);
			}
			produce_blocks();
		}
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
		trx.actions.emplace_back( get_action(N(tf), N(setconfig), vector<permission_level>{{N(tf), config::active_name}},
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

	transaction_trace_ptr makeissue(account_name holder, account_name issue_name, string info_url, transaction trans) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(makeissue), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
			("info_url", info_url)
			("issue_name", issue_name)
			("transaction", trans)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr closeissue(account_name holder, account_name proposer) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(closeissue), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
			("proposer", proposer)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr makeelection(account_name holder, string info_url) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(makeelection), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
			("info_url", info_url)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr endelection(account_name holder) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(endelection), vector<permission_level>{{holder, config::active_name}},
			mvo()
			("holder", holder)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(holder, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr addcand(account_name nominee, std::string info_link) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(addcand), vector<permission_level>{{nominee, config::active_name}},
			mvo()
			("nominee", nominee)
			("info_link", info_link)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(nominee, "active"), control->get_chain_id());
		return push_transaction( trx );
	}

	transaction_trace_ptr removecand(account_name candidate) {
		signed_transaction trx;
		trx.actions.emplace_back( get_action(N(tf), N(removecand), vector<permission_level>{{candidate, config::active_name}},
			mvo()
			("candidate", candidate)
		));
		set_transaction_headers(trx);
		trx.sign(get_private_key(candidate, "active"), control->get_chain_id());
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
		vector<char> data = get_row_by_account(N(tf), N(tf), N(boardmembers), member);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("board_member", data, abi_serializer_max_time);
	}

	fc::variant get_config() {
		vector<char> data = get_row_by_account(N(tf), N(tf), N(configs), N(configs));
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("config", data, abi_serializer_max_time);
	}

	fc::variant get_issue(account_name proposer) {
		vector<char> data = get_row_by_account(N(tf), N(tf), N(issues), proposer);
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