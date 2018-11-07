/**
 * This file includes all definitions necessary to interact with Trail's voting system. Developers who want to
 * utilize the system simply must include this file in their implementation to interact with the information
 * stored by Trail.
 * 
 * @author Craig Branscom
 */

#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/types.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;

#pragma region Structs

///@abi table votereceipts i64
struct vote_receipt {
    uint64_t ballot_id;
    uint16_t direction;
    asset weight;
    uint32_t expiration;

    uint64_t primary_key() const { return ballot_id; }
    EOSLIB_SERIALIZE(vote_receipt, (ballot_id)(direction)(weight)(expiration))
};

/// @abi table votelevies i64
struct vote_levy {
    account_name voter;
    asset levy_amount;
    uint32_t last_decay;

    uint64_t primary_key() const { return voter; }
    EOSLIB_SERIALIZE(vote_levy, (voter)(levy_amount)(last_decay))
};

/// @abi table voters i64
struct voter_id {
    account_name voter;
    asset votes;
    uint32_t release_time;

    uint64_t primary_key() const { return voter; }
    EOSLIB_SERIALIZE(voter_id, (voter)(votes)(release_time))
};

/// @abi table ballots
struct ballot {
    uint64_t ballot_id;
    account_name publisher;
    string info_url;
    
    asset no_count;
    asset yes_count;
    asset abstain_count;
    uint32_t unique_voters;

    uint32_t begin_time;
    uint32_t end_time;
    uint8_t status; // 0 = OPEN, 1 = PASS, 2 = FAIL

    uint64_t primary_key() const { return ballot_id; }
    EOSLIB_SERIALIZE(ballot, (ballot_id)(publisher)(info_url)
        (no_count)(yes_count)(abstain_count)(unique_voters)
        (begin_time)(end_time)(status))
};

/// @abi table environment i64
struct env {
    account_name publisher;
    
    uint64_t total_tokens;
    uint64_t total_voters;
    uint64_t total_ballots;

    asset vote_supply;

    uint32_t time_now;

    uint64_t primary_key() const { return publisher; }
    EOSLIB_SERIALIZE(env, (publisher)
        (total_tokens)(total_voters)(total_ballots)
        (vote_supply)
        (time_now))
};

#pragma endregion Structs

#pragma region Tables

typedef multi_index<N(voters), voter_id> voters_table;

typedef multi_index<N(ballots), ballot> ballots_table;

typedef multi_index<N(votereceipts), vote_receipt> votereceipts_table;

typedef multi_index<N(votelevies), vote_levy> votelevies_table;

typedef singleton<N(environment), env> environment_singleton;

#pragma endregion Tables

#pragma region Helper_Functions

bool is_voter(account_name voter) {
    voters_table voters(N(eosio.trail), N(eosio.trail));
    auto v = voters.find(voter);

    if (v != voters.end()) {
        return true;
    }

    return false;
}

bool is_ballot(uint64_t ballot_id) {
    ballots_table ballots(N(eosio.trail), N(eosio.trail));
    auto b = ballots.find(ballot_id);

    if (b != ballots.end()) {
        return true;
    }

    return false;
}

bool is_ballot_publisher(account_name publisher, uint64_t ballot_id) {
    ballots_table ballots(N(eosio.trail), N(eosio.trail));
    auto b = ballots.find(ballot_id);

    if (b != ballots.end()) {
        auto bal = *b;

        if (bal.publisher == publisher) {
            return true;
        }
    }

    return false;
}

symbol_name get_ballot_sym(uint64_t ballot_id) {
    ballots_table ballots(N(eosio.trail), N(eosio.trail));
    auto b = ballots.get(ballot_id);

    return b.no_count.symbol.name();
}

#pragma endregion Helper_Functions
