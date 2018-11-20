/**
 * This file includes all definitions necessary to interact with the system contract. Developers who want to
 * utilize this system simply must include this file in their implementation to interact with the information
 * stored by Trail.
 * 
 * @author Craig Branscom
 */

#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
//#include <eosiolib/types.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;

#pragma region Structs

struct account {
    asset balance;

    uint64_t primary_key() const { return balance.symbol.raw(); }
};

struct currency_stats {
    asset supply;
    asset max_supply;
    name issuer;

    uint64_t primary_key() const { return supply.symbol.raw(); }
};

struct user_resources {
    name owner;
    asset net_weight;
    asset cpu_weight;
    int64_t ram_bytes = 0;

    uint64_t primary_key()const { return owner.value; }
    EOSLIB_SERIALIZE( user_resources, (owner)(net_weight)(cpu_weight)(ram_bytes) )
};

struct delegatebw_args {
    name from;
    name receiver;
    asset stake_net_quantity;
    asset stake_cpu_quantity;
    bool transfer;
};

struct undelegatebw_args {
    name from;
    name receiver;
    asset unstake_net_quantity;
    asset unstake_cpu_quantity;
};

struct transfer_args {
    name from;
    name to;
    asset quantity;
    string memo;
};

#pragma endregion Structs

#pragma region Tables

typedef eosio::multi_index<name("accounts"), account> accounts;

typedef eosio::multi_index<name("stat"), currency_stats> stats;

typedef eosio::multi_index<name("userres"), user_resources> user_resources_table;

#pragma endregion Tables

#pragma region Helper_Functions

bool is_eosio_token(symbol sym, name owner) {
    accounts accountstable(name("eosio.token"), owner.value);
    auto a = accountstable.find(sym.raw());

    if (a != accountstable.end()) {
        return true;
    }

    return false;
}

asset get_eosio_token_balance(symbol sym, name owner) {
    accounts accountstable(name("eosio.token"), owner.value);
    auto acct = accountstable.get(sym.raw());

    auto amount = acct.balance;

    return amount;
}

asset get_liquid_tlos(name owner) {
    accounts accountstable(name("eosio.token"), owner.value);
    auto a = accountstable.find(symbol_code("TLOS").raw());
	
    int64_t amount = 0;
	print("\nfinding account...");
    if (a != accountstable.end()) {
        auto acct = *a;
        amount = acct.balance.amount;
		print("\naccount found");
    }
    
    return asset(amount, symbol("TLOS", 4));
}

asset get_staked_tlos(name owner) {
    user_resources_table userres(name("eosio"), owner.value);
    auto r = userres.find(owner.value);

    int64_t amount = 0;

    if (r != userres.end()) {
        auto res = *r;
        amount = (res.cpu_weight.amount + res.net_weight.amount);
    }
    
    return asset(amount, symbol("TLOS", 4));
}

#pragma endregion Helper_Functions
