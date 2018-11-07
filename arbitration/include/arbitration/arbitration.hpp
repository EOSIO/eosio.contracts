/**
 * The arbitration contract is used as an interface for the Telos arbitration
 * system. Users register their
 * account through the Trail Service, where they will be issued a VoterID card
 * that tracks and stores vote
 * participation.
 *
 * @author Craig Branscom, Peter Bue, Ed Silva, Douglas Horn
 * @copyright defined in telos/LICENSE.txt
 */

#pragma once

// #include <../trail.service/trail.connections/trailconn.voting.hpp>

#include <eosiolib/action.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/types.h>

using namespace std;
using namespace eosio;

class[[eosio::contract("arbitration")]] arbitration : public eosio::contract {
public:
  using contract::contract;
   #pragma region Enums

        enum case_state {
            CASE_SETUP, //0
            AWAITING_ARBS, //1
            CASE_INVESTIGATION, //2
            DISMISSED, //3
            HEARING, //4
            DELIBERATION, //5
            DECISION, //6 NOTE: No more joinders allowed
            ENFORCEMENT, //7
            COMPLETE //8
        };

        enum claim_class {
            UNDECIDED, //0
            LOST_KEY_RECOVERY, //1
            TRX_REVERSAL, //2
            EMERGENCY_INTER, //3
            CONTESTED_OWNER, //4
            UNEXECUTED_RELIEF, //5
            CONTRACT_BREACH, //6
            MISUSED_CR_IP, //7
            A_TORT, //8
            BP_PENALTY_REVERSAL, //9
            WRONGFUL_ARB_ACT, //10
            ACT_EXEC_RELIEF, //11
            WP_PROJ_FAILURE, //12
            TBNOA_BREACH, //13
            MISC //14
        };

        //CLARIFY: can arbs determine classes of cases they take? YES
        enum arb_status {
            AVAILABLE, //0
            UNAVAILABLE, //1
            INACTIVE //2
        };

        enum election_status {
            OPEN, //0
            PASSED, //1
            FAILED //2
        };

        //TODO: Evidence states

        #pragma endregion Enums

    arbitration(name s, name code, datastream<const char*> ds);
    ~arbitration(); 

    [[eosio::action]]
    void setconfig(uint16_t max_arbs, uint32_t default_time, vector<int64_t> fees);

     #pragma region Arb_Elections

        [[eosio::action]]
        void applyforarb(name candidate, string creds_ipfs_url); //TODO: rename to arbapply(), newarbapp()

        [[eosio::action]]
        void cancelarbapp(name candidate); //TODO: rename to arbunapply(), rmvarbapply()

        [[eosio::action]]
        void voteforarb(name candidate, uint16_t direction, name voter);

        [[eosio::action]]
        void endelection(name candidate); //automate in constructor?

        #pragma endregion Arb_Elections

        #pragma region Case_Setup

        [[eosio::action]] 
        void filecase(name claimant, uint16_t class_suggestion, string ev_ipfs_url); //NOTE: filing a case doesn't require a respondent

        [[eosio::action]]
        void addclaim(uint64_t case_id, uint16_t class_suggestion, string ev_ipfs_url, name claimant); //NOTE: adds subsequent claims to a case

        [[eosio::action]]
        void removeclaim(uint64_t case_id, uint16_t claim_num, name claimant); //NOTE: Claims can only be removed by a claimant during case setup. Enfore that have atleas one claim before awaiting arbs

        [[eosio::action]]
        void shredcase(uint64_t case_id, name claimant); //NOTE: member-level case removal, called during CASE_SETUP

        [[eosio::action]]
		void readycase(uint64_t case_id, name claimant);

        #pragma endregion Case_Setup

        #pragma region Member_Only
        [[eosio::action]]
        void vetoarb(uint64_t case_id, name arb, name selector);

        #pragma endregion Member_Only

        #pragma region Arb_Only

		//TODO: Set case respondant action
        [[eosio::action]]
        void dismisscase(uint64_t case_id, name arb, string ipfs_url); //TODO: require rationale?

        [[eosio::action]]
        void closecase(uint64_t case_id, name closer, string ipfs_url); //TODO: require decision?

        [[eosio::action]]
        void dismissev(uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb, string ipfs_url); //NOTE: moves to dismissed_evidence table
        
        [[eosio::action]]
        void acceptev(uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb, string ipfs_url); //NOTE: moves to evidence_table and assigns ID

        [[eosio::action]]
        void arbstatus(uint16_t new_status, name arb);

        [[eosio::action]]
        void casestatus(uint64_t case_id, uint16_t new_status, name arb);

        [[eosio::action]]
        void changeclass(uint64_t case_id, uint16_t claim_index, uint16_t new_class, name arb);

        // [[eosio::action]]
        //void joincases(vector<uint64_t> case_ids, name arb); //CLARIFY: joined case is rolled into Base case?

        // [[eosio::action]]
        //void addevidence(uint64_t case_id, vector<uint64_t> ipfs_urls, name arb); //NOTE: member version is submitev()

        [[eosio::action]]
        void recuse(uint64_t case_id, string rationale, name arb);

        #pragma endregion Arb_Only

        #pragma region BP_Multisig_Actions

        [[eosio::action]]
        void dismissarb(name arb);

        #pragma endregion BP_Multisig_Actions
};
