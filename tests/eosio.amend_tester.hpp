#include "eosio.trail_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

class eosio_amend_tester : public eosio_trail_tester
{
  public:
	abi_serializer abi_ser;
	abi_serializer token_abi_ser;
	vector<mvo> documents = {
		mvo()("document_id", 0)("document_title", std::string("Document 0"))("clauses", std::vector<std::string>({std::string("clause 0.1"), std::string("clause 0.2"), std::string("clause 0.3")}))("last_amend", 0),
		mvo()("document_id", 1)("document_title", std::string("Document 1"))("clauses", std::vector<std::string>({std::string("clause 1.1"), std::string("clause 1.2"), std::string("clause 1.3")}))("last_amend", 0),
		mvo()("document_id", 2)("document_title", std::string("Document 2"))("clauses", std::vector<std::string>({std::string("clause 2.1"), std::string("clause 2.2"), std::string("clause 2.3")}))("last_amend", 0)};

	eosio_amend_tester()
	{
		std::cout << "init amend tester" << std::endl;
		create_accounts({N(eosio.amend)});
		produce_blocks();
		{
			const auto &accnt = control->db().get<account_object, by_name>(N(eosio.token));
			abi_def abi;
			BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
			token_abi_ser.set_abi(abi, abi_serializer_max_time);
		}

		deploy_contract();
		produce_blocks(1);
	}

	void deploy_contract()
	{
		set_code(N(eosio.amend), contracts::amend_wasm());
		set_abi(N(eosio.amend), contracts::amend_abi().data());
		{
			const auto &accnt = control->db().get<account_object, by_name>(N(eosio.amend));
			abi_def abi;
			BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
			abi_ser.set_abi(abi, abi_serializer_max_time);
		}
	}

	void insert_default_docs()
	{
		for (int i = 0; i < documents.size(); i++)
		{
			insertdoc(documents[i]["document_title"].as<std::string>(), documents[i]["clauses"].as<std::vector<std::string>>());
		}
		produce_blocks(1);

		REQUIRE_MATCHING_OBJECT(get_document(0), documents[0]);
		REQUIRE_MATCHING_OBJECT(get_document(1), documents[1]);
		REQUIRE_MATCHING_OBJECT(get_document(2), documents[2]);
	}

	transaction_trace_ptr getdeposit(account_name owner)
	{
		signed_transaction trx;
		trx.actions.emplace_back(get_action(N(eosio.amend), N(getdeposit), vector<permission_level>{{owner, config::active_name}},
											mvo()("owner", owner)));
		set_transaction_headers(trx);
		trx.sign(get_private_key(owner, "active"), control->get_chain_id());
		return push_transaction(trx);
	}

	transaction_trace_ptr insertdoc(string title, vector<string> clauses)
	{
		signed_transaction trx;
		trx.actions.emplace_back(get_action(N(eosio.amend), N(insertdoc), vector<permission_level>{{N(eosio.amend), config::active_name}},
											mvo()("title", title)("clauses", clauses)));
		set_transaction_headers(trx);
		trx.sign(get_private_key(N(eosio.amend), "active"), control->get_chain_id());
		return push_transaction(trx);
	}

	transaction_trace_ptr makeproposal(string sub_title, uint64_t doc_id, uint8_t new_clause_num, string new_ipfs_url, account_name proposer)
	{
		signed_transaction trx;
		trx.actions.emplace_back(get_action(N(eosio.amend), N(makeproposal), vector<permission_level>{{proposer, config::active_name}},
											mvo()("sub_title", sub_title)("doc_id", doc_id)("new_clause_num", new_clause_num)("new_ipfs_url", new_ipfs_url)("proposer", proposer)));
		set_transaction_headers(trx);
		trx.sign(get_private_key(proposer, "active"), control->get_chain_id());
		return push_transaction(trx);
	}

	transaction_trace_ptr addclause(uint64_t sub_id, uint8_t new_clause_num, string new_ipfs_url, account_name proposer)
	{
		signed_transaction trx;
		trx.actions.emplace_back(get_action(N(eosio.amend), N(addclause), vector<permission_level>{{proposer, config::active_name}},
											mvo()("sub_id", sub_id)("new_clause_num", new_clause_num)("new_ipfs_url", new_ipfs_url)));
		set_transaction_headers(trx);
		trx.sign(get_private_key(proposer, "active"), control->get_chain_id());
		return push_transaction(trx);
	}

	transaction_trace_ptr openvoting(uint64_t sub_id, account_name proposer)
	{
		signed_transaction trx;
		trx.actions.emplace_back(get_action(N(eosio.amend), N(openvoting), vector<permission_level>{{proposer, config::active_name}},
											mvo()("sub_id", sub_id)));
		set_transaction_headers(trx);
		trx.sign(get_private_key(proposer, "active"), control->get_chain_id());
		return push_transaction(trx);
	}

	transaction_trace_ptr cancelsub(uint64_t sub_id, account_name proposer)
	{
		signed_transaction trx;
		trx.actions.emplace_back(get_action(N(eosio.amend), N(cancelsub), vector<permission_level>{{proposer, config::active_name}},
											mvo()("sub_id", sub_id)));
		set_transaction_headers(trx);
		trx.sign(get_private_key(proposer, "active"), control->get_chain_id());
		return push_transaction(trx);
	}

	transaction_trace_ptr closeprop(uint64_t sub_id, account_name proposer)
	{
		signed_transaction trx;
		trx.actions.emplace_back(get_action(N(eosio.amend), N(closeprop), vector<permission_level>{{proposer, config::active_name}},
											mvo()("sub_id", sub_id)));
		set_transaction_headers(trx);
		trx.sign(get_private_key(proposer, "active"), control->get_chain_id());
		return push_transaction(trx);
	}

	transaction_trace_ptr set_env(
		uint32_t expiration_length,
		uint64_t fee,
		uint32_t start_delay,
		double threshold_pass_voters,
		double threshold_pass_votes,
		double threshold_fee_voters,
		double threshold_fee_votes)
	{
		signed_transaction trx;
		trx.actions.emplace_back(get_action(N(eosio.amend), N(setenv), vector<permission_level>{{N(eosio.amend), config::active_name}},
											mvo()("new_environment",
												  mvo()("publisher", eosio::chain::name("eosio.amend"))("expiration_length", uint32_t(expiration_length))("fee", uint64_t(fee))("start_delay", uint32_t(start_delay))("threshold_pass_voters", double(threshold_pass_voters))("threshold_pass_votes", double(threshold_pass_votes))("threshold_fee_voters", double(threshold_fee_voters))("threshold_fee_votes", double(threshold_fee_votes)))));
		set_transaction_headers(trx);
		trx.sign(get_private_key(N(eosio.amend), "active"), control->get_chain_id());
		return push_transaction(trx);
	}

	fc::variant get_deposit(account_name owner)
	{
		vector<char> data = get_row_by_account(N(eosio.amend), N(eosio.amend), N(deposits), owner);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("deposit", data, abi_serializer_max_time);
	}

	fc::variant get_document(uint64_t doc_id)
	{
		vector<char> data = get_row_by_account(N(eosio.amend), N(eosio.amend), N(documents), doc_id);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("document", data, abi_serializer_max_time);
	}

	fc::variant get_submission(uint64_t sub_id)
	{
		vector<char> data = get_row_by_account(N(eosio.amend), N(eosio.amend), N(submissions), sub_id);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("submission", data, abi_serializer_max_time);
	}

	fc::variant get_env()
	{
		vector<char> data = get_row_by_account(N(eosio.amend), N(eosio.amend), N(configs), N(configs));
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("config", data, abi_serializer_max_time);
	}
};