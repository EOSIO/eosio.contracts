/**
 * Trail is an EOSIO-based voting service that allows users to create ballots that
 * are voted on by the network of registered voters. It also offers custom token
 * features that let any user to create their own token and configure token settings 
 * to match a wide variety of intended use cases. 
 * 
 * @author Craig Branscom
 */

#include "trail.voting.hpp"
#include "trail.system.hpp"
#include "trail.tokens.hpp"

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/dispatcher.hpp>
#include <string>

using namespace eosio;

class [[eosio::contract("eosio.trail")]] trail : public contract {
    
public:

    trail(name self, name code, datastream<const char*> ds);

    ~trail();

    environment_singleton environment;
    env env_struct;

    #pragma region Constants

    uint64_t const VOTE_ISSUE_RATIO = 1; //indicates a 1:1 TLOS/VOTE issuance

    uint32_t const MIN_LOCK_PERIOD = 86400; //86,400 seconds is ~1 day

    uint32_t const DECAY_RATE = 120; //number of seconds to decay by 1 VOTE

    //TODO: add constants for totals vector mappings?

    #pragma endregion Constants


    #pragma region Token_Registration
    
    [[eosio::action]] void regtoken(asset max_supply, name publisher, string info_url);

    //[[eosio::action]] void settokenurl(name publisher, string info_url);

    [[eosio::action]] void initsettings(name publisher, symbol token_symbol, token_settings new_settings);

    [[eosio::action]] void unregtoken(symbol token_symbol, name publisher);

    #pragma endregion Token_Registration


    #pragma region Token_Actions

    [[eosio::action]] void issuetoken(name publisher, name recipient, asset tokens, bool airgrab);

    [[eosio::action]] void claimairgrab(name claimant, name publisher, symbol token_symbol);

    [[eosio::action]] void burntoken(name balance_owner, asset amount);

    [[eosio::action]] void seizetoken(name publisher, name owner, asset tokens); //TODO: add string memo?

    [[eosio::action]] void seizeairgrab(name publisher, name recipient, asset amount); //TODO: add string memo?

    [[eosio::action]] void seizebygroup(name publisher, vector<name> group, asset amount);

    [[eosio::action]] void raisemax(name publisher, asset amount);

    [[eosio::action]] void lowermax(name publisher, asset amount);

    [[eosio::action]] void transfer(name sender, name recipient, asset amount); //TODO: rename to something other than transfer? may be confused with eosio.token transfer

    #pragma endregion Token_Actions


    #pragma region Voter_Registration

    [[eosio::action]] void regvoter(name voter, symbol token_symbol);

    [[eosio::action]] void unregvoter(name voter, symbol token_symbol);

    #pragma endregion Voter_Registration


    #pragma region Voting_Actions

    //NOTE: casts TLOS into VOTE tokens and subtracts counterbalance
    [[eosio::action]] void mirrorcast(name voter, symbol token_symbol);

    [[eosio::action]] void castvote(name voter, uint64_t ballot_id, uint16_t direction);

    [[eosio::action]] void deloldvotes(name voter, uint16_t num_to_delete);

    #pragma endregion Voting_Actions


    #pragma region Proxy_Registration

    //[[eosio::action]] void regproxy(name proxy, symbol voting_token);

    #pragma endregion Proxy_Registration


    #pragma region Proxy_Actions



    #pragma endregion Proxy_Actions


    #pragma region Ballot_Registration

    [[eosio::action]] void regballot(name publisher, uint8_t ballot_type, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url);

    [[eosio::action]] void unregballot(name publisher, uint64_t ballot_id);

    //TODO: archivebal() action to replace ballot publisher's RAM with Trail's RAM. Could require TLOS payment?

    #pragma endregion Ballot_Registration


    #pragma region Ballot_Actions

    [[eosio::action]] void addcandidate(name publisher, uint64_t ballot_id, name new_candidate, string info_link);

    [[eosio::action]] void setallcands(name publisher, uint64_t ballot_id, vector<candidate> new_candidates);

    [[eosio::action]] void setallstats(name publisher, uint64_t ballot_id, vector<uint8_t> new_cand_statuses);

    [[eosio::action]] void rmvcandidate(name publisher, uint64_t ballot_id, name candidate); //TODO: should candidates be allowed to remove themselves? or only publisher?

    [[eosio::action]] void setseats(name publisher, uint64_t ballot_id, uint8_t num_seats);

    [[eosio::action]] void nextcycle(name publisher, uint64_t ballot_id, uint32_t new_begin_time, uint32_t new_end_time); //only for ballots?

    [[eosio::action]] void closeballot(name publisher, uint64_t ballot_id, uint8_t pass);

    #pragma endregion Ballot_Actions


    #pragma region Helper_Functions

    uint64_t make_proposal(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url);

    bool delete_proposal(uint64_t prop_id, name publisher);

    bool vote_for_proposal(name voter, uint64_t ballot_id, uint64_t prop_id, uint16_t direction);

    bool close_proposal(uint64_t prop_id, uint8_t pass, name publisher);


    uint64_t make_election(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url);

    bool vote_for_election(name voter, uint64_t ballot_id, uint64_t elec_id, uint16_t direction);
    
    bool close_election(uint64_t elec_id, uint8_t pass, name publisher);

    bool delete_election(uint64_t elec_id, name publisher);


    uint64_t make_leaderboard(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url);
    
    bool delete_leaderboard(uint64_t board_id, name publisher);

    bool vote_for_leaderboard(name voter, uint64_t ballot_id, uint64_t board_id, uint16_t direction);

    bool close_leaderboard(uint64_t board_id, uint8_t pass, name publisher);


    asset get_vote_weight(name voter, symbol voting_token);

    bool has_direction(uint16_t direction, vector<uint16_t> direction_list);

    vector<candidate> set_candidate_statuses(vector<candidate> candidate_list, vector<uint8_t> new_status_list);

    #pragma endregion Helper_Functions


    #pragma region Reactions

    //Reactions are regular functions called only as a trigger from the dispatcher.

    void update_from_cb(name from, asset amount);

    void update_to_cb(name to, asset amount);

    asset get_decay_amount(name voter, symbol token_symbol, uint32_t decay_rate);

    #pragma endregion Reactions
};
