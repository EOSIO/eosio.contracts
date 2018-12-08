#include "eosio.trail_tester.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

class eosio_arb_tester : public eosio_trail_tester
{
  public:
    abi_serializer abi_ser;

    eosio_arb_tester()
    {
        deploy_contract();
        produce_blocks(1);
    }

    void deploy_contract()
    {
        create_accounts({N(eosio.arb)});

        set_code(N(eosio.arb), contracts::eosio_arb_wasm());
        set_abi(N(eosio.arb), contracts::eosio_arb_abi().data());
        {
            const auto &accnt = control->db().get<account_object, by_name>(N(eosio.arb));
            abi_def abi;
            BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
            abi_ser.set_abi(abi, abi_serializer_max_time);
        }
    }

    // #pragma regions getters
    
    fc::variant get_config()
    {
        vector<char> data = get_row_by_account(N(eosio.arb), N(eosio.arb), N(configs), N(configs));
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("config", data, abi_serializer_max_time);
    }

    fc::variant get_candidate(uint64_t candidate_id)
    {
        vector<char> data = get_row_by_account(N(eosio.arb), N(eosio.arb), N(pendingcands), candidate_id);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("pending_candidate", data, abi_serializer_max_time);
    }
    
    fc::variant get_arbitrator(uint64_t arbitrator_id)
    {
        vector<char> data = get_row_by_account(N(eosio.arb), N(eosio.arb), N(arbitrators), arbitrator_id);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("arbitrator", data, abi_serializer_max_time);
    }
    
    // todo : make this work by getting case first then claim
    fc::variant get_claim(uint64_t case_id, uint64_t claim_index)
    {
        return mvo();
    }
    
    fc::variant get_casefile(uint64_t casefile_id)
    {
        vector<char> data = get_row_by_account(N(eosio.arb), N(eosio.arb), N(casefiles), casefile_id);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("casefile", data, abi_serializer_max_time);
    }
    
    fc::variant get_dismissed_casefile(uint64_t casefile_id)
    {
        vector<char> data = get_row_by_account(N(eosio.arb), N(eosio.arb), N(dismisscases), casefile_id);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("casefile", data, abi_serializer_max_time);
    }
    
    fc::variant get_evidence(uint64_t evidence_id)
    {
        vector<char> data = get_row_by_account(N(eosio.arb), N(eosio.arb), N(evidence), evidence_id);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("evidence", data, abi_serializer_max_time);
    }
    
    fc::variant get_dismissed_evidence(uint64_t evidence_id)
    {
        vector<char> data = get_row_by_account(N(eosio.arb), N(eosio.arb), N(dismissedev), evidence_id);
        return data.empty() ? fc::variant() : abi_ser.binary_to_variant("evidence", data, abi_serializer_max_time);
    }

    // #pragma endregion getters

    // #pragma region actions

    transaction_trace_ptr setconfig(uint16_t max_elected_arbs, uint32_t election_duration, uint32_t start_election, uint32_t arbitrator_term_length, vector<int64_t> fees)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(
            N(eosio.arb), N(setconfig), 
            vector<permission_level>{{N(eosio), config::active_name}},
            mvo()
                ("max_elected_arbs", max_elected_arbs)
                ("election_duration", election_duration)
                ("start_election", start_election)
                ("arbitrator_term_length", arbitrator_term_length)
                ("fees", fees))
        );

        set_transaction_headers(trx);
        trx.sign(get_private_key(N(eosio), "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    // #pragma region actions_Arb_Elections

     transaction_trace_ptr init_election()
    {
        signed_transaction trx;
        trx.actions.emplace_back(
            get_action(
            N(eosio.arb), N(initelection), vector<permission_level>{{N(eosio), config::active_name}},mvo()));
        set_transaction_headers(trx);
        trx.sign(get_private_key(N(eosio), "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr candaddlead(name candidate, string creds_ipfs_url)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(candaddlead), vector<permission_level>{{candidate, config::active_name}},
                                            mvo()("candidate", candidate)("creds_ipfs_url", creds_ipfs_url)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(candidate, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr candrmvlead( name candidate )
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(candrmvlead), vector<permission_level>{{candidate, config::active_name}},
                                            mvo()("candidate", candidate)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(candidate, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr regcand(name candidate, string creds_ipfs_url)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(regcand), vector<permission_level>{{candidate, config::active_name}},
                                            mvo()("candidate", candidate)("creds_ipfs_url", creds_ipfs_url)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(candidate, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr unregcand( name candidate )
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(unregcand), vector<permission_level>{{candidate, config::active_name}},
                                            mvo()("candidate", candidate)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(candidate, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr endelection( name candidate)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(endelection), vector<permission_level>{{candidate, config::active_name}},
                                    mvo()("candidate", candidate)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(candidate, "active"), control->get_chain_id());
        return push_transaction(trx);
    }            

    // #pragma endregion actions_Arb_Elections
    // #pragma region actions_Case_Setup

    transaction_trace_ptr filecase(name claimant, uint16_t class_suggestion, string ev_ipfs_url)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(endelection), vector<permission_level>{{claimant, config::active_name}},
                                            mvo()("claimant", claimant)("class_suggestion", class_suggestion)("ev_ipfs_url", ev_ipfs_url)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(claimant, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr addclaim( uint64_t case_id, uint16_t class_suggestion, string ev_ipfs_url, name claimant)
    {
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(endelection), vector<permission_level>{{claimant, config::active_name}},
                                            mvo()("case_id", case_id)("class_suggestion", class_suggestion)("ev_ipfs_url", ev_ipfs_url)("claimant", claimant)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(claimant, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr removeclaim(uint64_t case_id, uint16_t claim_num, name claimant)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(endelection), vector<permission_level>{{claimant, config::active_name}},
                                            mvo()("case_id", case_id)("claim_num", claim_num)("claimant", claimant)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(claimant, "active"), control->get_chain_id());
        return push_transaction(trx);
    }
    
    transaction_trace_ptr shredcase( uint64_t case_id, name claimant)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(endelection), vector<permission_level>{{claimant, config::active_name}},
                                            mvo()("case_id", case_id)("claimant", claimant)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(claimant, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr readycase(uint64_t case_id, name claimant)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(readycase), vector<permission_level>{{claimant, config::active_name}},
                                            mvo()("case_id", case_id)("claimant", claimant)));
        set_transaction_headers(trx);
        trx.sign(get_private_key(claimant, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    // #pragma endregion actions_Case_Setup
    // #pragma region actions_Member_Only

    #pragma endregion actions_Member_Only
    #pragma region actions_Arb_Only

    transaction_trace_ptr dismisscase(uint64_t case_id, name arb, string ipfs_url)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(dismisscase), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("case_id", case_id)("arb", arb)("ipfs_url", ipfs_url) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr closecase(uint64_t case_id, name arb, string ipfs_url)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(closecase), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("case_id", case_id)("arb", arb)("ipfs_url", ipfs_url) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr dismissev(uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb, string ipfs_url)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(dismissev), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("case_id", case_id)("claim_index", claim_index)("ev_index", ev_index)("arb", arb)("ipfs_url", ipfs_url) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr acceptev(uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb, string ipfs_url)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(acceptev), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("case_id", case_id)("claim_index", claim_index)("ev_index", ev_index)("arb", arb)("ipfs_url", ipfs_url) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr arbstatus(uint16_t new_status, name arb)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(arbstatus), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("new_status", new_status)("arb", arb) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr casestatus(uint64_t case_id, uint16_t new_status, name arb)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(casestatus), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("case_id", case_id)("new_status", new_status)("arb", arb) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr changeclass(uint64_t case_id, uint16_t claim_index, uint16_t new_class, name arb)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(changeclass), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("case_id", case_id)("claim_index", claim_index)("new_class", new_class)("arb", arb) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    transaction_trace_ptr recuse(uint64_t case_id, string rationale, name arb)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(recuse), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("case_id", case_id)("rationale", rationale)("arb", arb) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    // #pragma endregion actions_Arb_Only
    // #pragma region actions_BP_Multisig_Actions

    // ! double check permissions on this ! 
    transaction_trace_ptr dismissarb(name arb)
    {   
        signed_transaction trx;
        trx.actions.emplace_back(get_action(N(eosio.arb), N(dismissarb), vector<permission_level>{{arb, config::active_name}},
                                            mvo()("arb", arb) ));
        set_transaction_headers(trx);
        trx.sign(get_private_key(arb, "active"), control->get_chain_id());
        return push_transaction(trx);
    }

    // #pragma endregion actions_BP_Multisig_Actions

    // #pragma endregion actions

    // #pragma region Enums

    enum case_state {
        CASE_SETUP,         // 0
        AWAITING_ARBS,      // 1
        CASE_INVESTIGATION, // 2
        DISMISSED,          // 3
        HEARING,            // 4
        DELIBERATION,       // 5
        DECISION,           // 6 NOTE: No more joinders allowed
        ENFORCEMENT,        // 7
        COMPLETE            // 8
    };

    enum claim_class {
        UNDECIDED,           // 0
        LOST_KEY_RECOVERY,   // 1
        TRX_REVERSAL,        // 2
        EMERGENCY_INTER,     // 3
        CONTESTED_OWNER,     // 4
        UNEXECUTED_RELIEF,   // 5
        CONTRACT_BREACH,     // 6
        MISUSED_CR_IP,       // 7
        A_TORT,              // 8
        BP_PENALTY_REVERSAL, // 9
        WRONGFUL_ARB_ACT,    // 10
        ACT_EXEC_RELIEF,     // 11
        WP_PROJ_FAILURE,     // 12
        TBNOA_BREACH,        // 13
        MISC                 // 14
    };

    // CLARIFY: can arbs determine classes of cases they take? YES
    enum arb_status {
        AVAILABLE,   // 0
        UNAVAILABLE, // 1
        INACTIVE     // 2
    };

    enum election_status {
        OPEN,   // 0
        PASSED, // 1
        FAILED, // 2
        CLOSED  // 3 
    };

    // TODO: Evidence states

    // #pragma endregion Enums
};