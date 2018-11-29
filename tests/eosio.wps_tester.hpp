#include "eosio.trail_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

class eosio_wps_tester : public eosio_trail_tester
{
  public:
    abi_serializer abi_ser;

    eosio_wps_tester()
    {
        deploy_contract();
        produce_blocks(1);
    }

    void deploy_contract()
    {
        set_code(N(eosio.saving), contracts::eosio_saving_wasm());
        set_abi(N(eosio.saving), contracts::eosio_saving_abi().data());
        {
            const auto &accnt = control->db().get<account_object, by_name>(N(eosio.saving));
            abi_def abi;
            BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
            abi_ser.set_abi(abi, abi_serializer_max_time);
        }
    }

    transaction_trace_ptr wps_set_env(
        uint32_t cycle_duration,
        uint16_t fee_percentage,
        uint64_t start_delay,
        uint64_t fee_min,
        double threshold_pass_voters,
        double threshold_pass_votes,
        double threshold_fee_voters,
        double threshold_fee_votes)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.saving), N(setenv), vector<permission_level>{{N(eosio.saving), config::active_name}},
                                            mvo()("new_environment",
                                                  mvo()("publisher", eosio::chain::name("eosio.saving"))("cycle_duration", cycle_duration)("fee_percentage", fee_percentage)("start_delay", start_delay)("fee_min", fee_min)("threshold_pass_voters", threshold_pass_voters)("threshold_pass_votes", threshold_pass_votes)("threshold_fee_voters", threshold_fee_voters)("threshold_fee_votes", threshold_fee_votes))));
        set_transaction_headers(trx);
        trx.sign(get_private_key(N(eosio.saving), "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr getdeposit(account_name owner)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.saving), N(getdeposit), vector<permission_level>{{owner, config::active_name}},
                                            mvo()("owner", owner)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(owner, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr cancelsub(name owner, uint64_t sub_id)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.saving), N(cancelsub), vector<permission_level>{{owner, config::active_name}},
                                            mvo()("sub_id", sub_id)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(owner, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr submit_worker_proposal(account_name proposer, std::string title, uint16_t cycles, std::string ipfs_location, asset amount, account_name receiver)
    {
        return base_tester::push_action(N(eosio.saving), N(submit), proposer, mvo()("proposer", proposer)("title", title)("cycles", cycles)("ipfs_location", ipfs_location)("amount", amount)("receiver", receiver));
    }

    transaction_trace_ptr openvoting(account_name proposer, uint64_t sub_id)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.saving), N(openvoting), vector<permission_level>{{proposer, config::active_name}},
                                            mvo()("sub_id", sub_id)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(proposer, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    action_result claim_proposal_funds(uint64_t proposal_id, account_name proposer)
    {
        return push_wps_action(proposer, N(claim), mvo()("prop_id", proposal_id)("proposer", proposer));
    }

    fc::variant get_wps_info(const uint64_t id)
    {
        vector<char> data = get_row_by_account(N(eosio.saving), N(eosio.saving), N(proposals), id);
        return abi_ser.binary_to_variant("proposal", data, abi_serializer_max_time);
    }

    fc::variant get_wps_env()
    {
        vector<char> data = get_row_by_account(N(eosio.saving), N(eosio.saving), N(wpenv), N(wpenv));
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("wp_env", data, abi_serializer_max_time);
    }

    action_result push_wps_action(const account_name &signer, const action_name &name, const variant_object &data)
    {
        string action_type_name = abi_ser.get_action_type(name);

        action act;
        act.account = N(eosio.saving);
        act.name = name;
        act.data = abi_ser.variant_to_binary(action_type_name, data, abi_serializer_max_time);

        return base_tester::push_action(std::move(act), uint64_t(signer));
    }

    action_result push_trail_action(const account_name &signer, const action_name &name, const variant_object &data)
    {
        string action_type_name = abi_ser.get_action_type(name);

        action act;
        act.account = N(eosio.trail);
        act.name = name;
        act.data = abi_ser.variant_to_binary(action_type_name, data, abi_serializer_max_time);

        return base_tester::push_action(std::move(act), uint64_t(signer));
    }

    fc::variant get_wps_submission(uint64_t submission_id)
    {
        vector<char> data = get_row_by_account(N(eosio.saving), N(eosio.saving), N(submissions), submission_id);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("submission", data, abi_serializer_max_time);
    }

    fc::variant get_deposit(account_name owner)
    {
        vector<char> data = get_row_by_account(N(eosio.saving), N(eosio.saving), N(deposits), owner);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("deposit", data, abi_serializer_max_time);
    }
};