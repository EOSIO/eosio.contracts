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
#include <trail.voting.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/types.h>

using namespace std;
using namespace eosio;

class[[eosio::contract("eosio.arbitration")]] arbitration
    : public eosio::contract {
public:
  using contract::contract;
#pragma region Enums

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
    INACTIVE,    // 2
    SEAT_EXPIRED // 3
  };

  enum election_status {
    OPEN,   // 0
    PASSED, // 1
    FAILED, // 2
    CLOSED  // 3 
  };

// TODO: Evidence states

#pragma endregion Enums
#pragma region Structs

  struct permission_level_weight {
    permission_level permission;
    uint16_t weight;

    EOSLIB_SERIALIZE(permission_level_weight, (permission)(weight))
  };

  struct key_weight {
    eosio::public_key key;
    uint16_t weight;

    EOSLIB_SERIALIZE(key_weight, (key)(weight))
  };

  struct wait_weight {
    uint32_t wait_sec;
    uint16_t weight;

    EOSLIB_SERIALIZE(wait_weight, (wait_sec)(weight))
  };

  struct authority {
    uint32_t threshold = 0;
    std::vector<key_weight> keys;
    std::vector<permission_level_weight> accounts;
    std::vector<wait_weight> waits;

    EOSLIB_SERIALIZE(authority, (threshold)(keys)(accounts)(waits))
  };

  struct[[eosio::table]] candidate {
    name cand_name;
    string credential_link;
    uint32_t applied_time;

    uint64_t primary_key() const { return cand_name.value; }
    EOSLIB_SERIALIZE(candidate, (cand_name)(credential_link)(applied_time))
  };

  // NOTE: diminishing subsequent response (default) times
  // NOTE: initial deposit saved
  // NOTE: class of claim where neither party can pay fees, TF pays instead
  struct[[eosio::table]] config {
    name publisher;
    uint16_t max_elected_arbs;
    uint32_t election_duration_days;
    uint32_t start_election_days;
    vector<int64_t> fee_structure; 
    uint32_t arb_seat_expiration_time_days;
    uint32_t last_time_edited;
    uint64_t ballot_id = 0;
    bool auto_start_election = false;     

    uint64_t primary_key() const { return publisher.value; }
    EOSLIB_SERIALIZE(config, (publisher)(max_elected_arbs)(election_duration_days)(start_election_days)(fee_structure)(arb_seat_expiration_time_days)(last_time_edited)(ballot_id)(auto_start_election))
  };

  struct[[eosio::table]] arbitrator {
    name arb;
    uint16_t arb_status;
    vector<uint64_t> open_case_ids;
    vector<uint64_t> closed_case_ids;
    string credential_link; //ipfs_url of credentials
    uint32_t elected_time;
    uint32_t seat_expiration_time_days;
    vector<string> languages; //NOTE: language codes for space

    uint64_t primary_key() const { return arb.value; }
    EOSLIB_SERIALIZE(arbitrator,
                     (arb)(arb_status)(open_case_ids)(closed_case_ids)(credential_link)(elected_time)(seat_expiration_time_days)(languages))
  };

  struct[[eosio::table]] claim {
    uint16_t class_suggestion;
    vector<string> submitted_pending_evidence; // submitted by claimant
    vector<uint64_t> accepted_ev_ids;          // accepted and emplaced by arb
    uint16_t class_decision;                   // initialized to UNDECIDED (0)

    EOSLIB_SERIALIZE(claim, (class_suggestion)(submitted_pending_evidence)(
                                accepted_ev_ids)(class_decision))
  };

  // TODO: evidence types?
  // NOTE: add metadata
  struct[[eosio::table]] evidence {
    uint64_t ev_id;
    string ipfs_url;

    uint64_t primary_key() const { return ev_id; }
    EOSLIB_SERIALIZE(evidence, (ev_id)(ipfs_url))
  };

  // NOTE: joinders saved in separate table
  struct[[eosio::table]] casefile {
    uint64_t case_id;
    name claimant; // TODO: add vector for claimant's party? same for respondant
                   // and their party?
    name respondant; // NOTE: can be set to 0
    vector<claim> claims;
    vector<name> arbitrators; // CLARIFY: do arbitrators get added when joining?
    uint16_t case_status;
    uint32_t last_edit;
    vector<string> findings_ipfs;
    // vector<asset> additional_fees; //NOTE: case by case?
    // TODO: add messages field

    uint64_t primary_key() const { return case_id; }
    uint64_t by_claimant() const { return claimant.value; }
    EOSLIB_SERIALIZE(casefile, (case_id)(claimant)(claims)(arbitrators)(
                                   case_status)(last_edit)(findings_ipfs))
  };

#pragma endregion Structs

  arbitration(name s, name code, datastream<const char *> ds);
  ~arbitration();

  [[eosio::action]] void init();

  [[eosio::action]] void setconfig(uint16_t max_elected_arbs, uint32_t election_duration_days, uint32_t start_election_days, uint32_t arb_seat_expiration_time_days, vector<int64_t> fees);

#pragma region Arb_Elections

  [[eosio::action]] void applyforarb( name candidate, string creds_ipfs_url);

  [[eosio::action]] void cancelarbapp( name candidate);

  [[eosio::action]] void endelection(name candidate); 
                                                      
#pragma endregion Arb_Elections

#pragma region Case_Setup

  [[eosio::action]] void filecase(name claimant, uint16_t class_suggestion, string ev_ipfs_url); // NOTE: filing a case doesn't require a respondent

  [[eosio::action]] void addclaim( uint64_t case_id, uint16_t class_suggestion, string ev_ipfs_url, name claimant); // NOTE: adds subsequent claims to a case

  [[eosio::action]] void removeclaim(uint64_t case_id, uint16_t claim_num, name claimant);  // NOTE: Claims can only be
                                                                                            // removed by a claimant
                                                                                            // during case setup.
                                                                                            // Enfore that have atleas
                                                                                            // one claim before
                                                                                            // awaiting arbs

  [[eosio::action]] void shredcase( uint64_t case_id, name claimant); // NOTE: member-level case removal,
                                                                     // called during CASE_SETUP

  [[eosio::action]] void readycase(uint64_t case_id, name claimant);

#pragma endregion Case_Setup

#pragma region Member_Only
  [[eosio::action]] void vetoarb(uint64_t case_id, name arb, name selector);

#pragma endregion Member_Only

#pragma region Arb_Only

  // TODO: Set case respondant action
  [[eosio::action]] void dismisscase(
      uint64_t case_id, name arb, string ipfs_url); // TODO: require rationale?

  [[eosio::action]] void closecase(uint64_t case_id, name arb,
                                   string ipfs_url); // TODO: require decision?

  [[eosio::action]] void dismissev(
      uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb,
      string ipfs_url); // NOTE: moves to dismissed_evidence table

  [[eosio::action]] void acceptev(
      uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb,
      string ipfs_url); // NOTE: moves to evidence_table and assigns ID

  [[eosio::action]] void arbstatus(uint16_t new_status, name arb);

  [[eosio::action]] void casestatus(uint64_t case_id, uint16_t new_status,
                                    name arb);

  [[eosio::action]] void changeclass(uint64_t case_id, uint16_t claim_index,
                                     uint16_t new_class, name arb);

  // [[eosio::action]]
  // void joincases(vector<uint64_t> case_ids, name arb); //CLARIFY: joined case
  // is rolled into Base case?

  // [[eosio::action]]
  // void addevidence(uint64_t case_id, vector<uint64_t> ipfs_urls, name arb);
  // //NOTE: member version is submitev()

  [[eosio::action]] void recuse(uint64_t case_id, string rationale, name arb);

#pragma endregion Arb_Only

#pragma region BP_Multisig_Actions

  [[eosio::action]] void dismissarb(name arb);

#pragma endregion BP_Multisig_Actions

protected:
#pragma region Tables

  typedef singleton<"configs"_n, config> config_singleton;
  config_singleton configs;
  config _config;

  typedef multi_index<"candidates"_n, candidate> candidates_table;
  typedef multi_index<"arbitrators"_n, arbitrator> arbitrators_table;

  typedef multi_index<"casefiles"_n, casefile> casefiles_table;
  typedef multi_index<"dismisscases"_n, casefile> dismissed_cases_table;

  typedef multi_index<"evidence"_n, evidence> evidence_table;
  typedef multi_index<"dismissedev"_n, evidence> dismissed_evidence_table;

#pragma endregion Tables

  void validate_ipfs_url(string ipfs_url);
  
  config get_default_config();
  
  void start_new_election();
  
  bool has_available_seats(arbitrators_table &arbitrators);

};
