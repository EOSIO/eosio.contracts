/**
 * 
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

    uint32_t const MAX_LOCK_PERIOD = 7776000; //7,776,000 seconds is ~3 months

    uint32_t const DECAY_RATE = 120; //number of seconds to decay by 1 VOTE

    #pragma endregion Constants


    #pragma region Token_Actions
    
    [[eosio::action]] void regtoken(asset native, name publisher);

    [[eosio::action]] void unregtoken(asset native, name publisher);

    #pragma endregion Token_Actions


    #pragma region Registration

    [[eosio::action]] void regvoter(name voter);

    [[eosio::action]] void unregvoter(name voter);

    [[eosio::action]] void regballot(name publisher, uint8_t ballot_type, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url);

    [[eosio::action]] void unregballot(name publisher, uint64_t ballot_id);

    //[[eosio::action]] void addcandidate(name publisher, uint64_t ballot_id, name new_candidate, string info_link);

    //[[eosio::action]] void setseats(name publisher, uint8_t num_seats);

    [[eosio::action]] void nextcycle(name publisher, uint64_t ballot_id, uint32_t new_begin_time, uint32_t new_end_time); //only for ballots?

    [[eosio::action]] void closeballot(name publisher, uint64_t ballot_id, uint8_t pass);

    #pragma endregion Registration


    #pragma region Voting_Actions

    [[eosio::action]] void mirrorstake(name voter, uint32_t lock_period);

    [[eosio::action]] void castvote(name voter, uint64_t ballot_id, uint16_t direction);

    [[eosio::action]] void deloldvotes(name voter, uint16_t num_to_delete);

    #pragma endregion Voting_Actions


    #pragma region Helper_Functions

    uint64_t make_proposal(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url);

    bool delete_proposal(uint64_t prop_id);

    bool vote_for_proposal(name voter, uint64_t ballot_id, uint64_t prop_id, uint16_t direction);

    bool close_proposal(uint64_t prop_id, uint8_t pass);


    uint64_t make_election(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url);

    //TODO: delete_election();

    //TODO: vote_for_election();

    bool delete_election(uint64_t elec_id);


    uint64_t make_leaderboard(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url);
    
    bool delete_leaderboard(uint64_t board_id);

    bool vote_for_leaderboard(name voter, uint64_t ballot_id, uint64_t board_id, uint16_t direction);

    bool close_leaderboard(uint64_t board_id, uint8_t pass);


    asset get_vote_weight(name voter, symbol voting_token);

    #pragma endregion Helper_Functions


    #pragma region Reactions

    //Reactions are regular functions called only as a trigger from the dispatcher.

    void update_from_levy(name from, asset amount);

    void update_to_levy(name to, asset amount);

    asset calc_decay(name voter, asset amount);

    #pragma endregion Reactions
};
