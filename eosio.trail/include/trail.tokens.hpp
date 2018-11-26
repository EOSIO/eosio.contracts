/**
 * This file includes all definitions necessary to interact with Trail's token registration system. Developers 
 * who want to utilize the system simply must include this file in their implementation to interact with the 
 * information stored by Trail.
 * 
 * @author Craig Branscom
 */

#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;

#pragma region Structs

//TODO: fold into a vector?
struct token_settings {
    bool is_burnable = false; //NOTE: can only burn from own balance
    bool is_max_raisable = false;
    bool is_max_lowerable = false;
    bool is_destructible = true;
    bool is_proxyable = false; //NOTE: adds proxy system //TODO: implement
    bool is_transferable = false; //NOTE: adds levy system and levy decay //TODO: implement
    bool is_seizable = false; //TODO: implement
    bool is_recastable = false; //TODO: implement
    bool is_initialized = false;
    bool is_mutable_after_initialized = true;

    uint32_t levy_decay_rate = 600; //seconds to decay by 1 whole token
};

//NOTE: registries MUST be scoped by name("eosio.trail").value
struct [[eosio::table, eosio::contract("eosio.trail")]] registry {
    asset max_supply;
    asset supply;
    name publisher;
    string info_url;
    token_settings settings;

    uint64_t primary_key() const { return max_supply.symbol.code().raw(); }
    EOSLIB_SERIALIZE(registry, (max_supply)(supply)(publisher)(info_url)(settings))
};

//NOTE: balances are scoped by symbol 
//TODO: scope by symbol.code().raw()
struct [[eosio::table, eosio::contract("eosio.trail")]] balance {
    name owner;
    asset tokens;

    uint64_t primary_key() const { return owner.value; }
    EOSLIB_SERIALIZE(balance, (owner)(tokens))
};

//NOTE: proxy balances are scoped by balance owner
//TODO: scope by symbol.code().raw(), key by name constituent, rename proxied_balance?
// struct [[eosio::table, eosio::contract("eosio.trail")]] proxy_balance {
//     asset proxied_tokens;
//     name proxy;

//     uint64_t primary_key() const { return proxied_tokens.symbol.code().raw(); }
//     EOSLIB_SERIALIZE(proxy_balance, (proxied_tokens)(proxy))
// };

//NOTE: airgrabs are scoped by publisher?
struct [[eosio::table, eosio::contract("eosio.trail")]] airgrab {
    name recipient;
    asset tokens;

    uint64_t primary_key() const { return recipient.value; }
    EOSLIB_SERIALIZE(airgrab, (recipient)(tokens))
};

#pragma endregion Structs


#pragma region Tables

typedef multi_index<name("balances"), balance> balances_table;

//typedef multi_index<name("proxybals"), proxy_balance> proxy_balances_table;

typedef multi_index<name("airgrabs"), airgrab> airgrabs_table;

typedef multi_index<name("registries"), registry> registries_table;

#pragma endregion Tables


#pragma region Helper_Functions

bool is_registered_token(symbol token_symbol) {
    registries_table registries(name("eosio.trail"), name("eosio.trail").value);
    auto itr = registries.find(token_symbol.raw());

    if (itr != registries.end()) {
        return true;
    }

    return false;
}

asset get_token_balance(name owner, symbol token_symbol) {
    balances_table balances(name("eosio.trail"), token_symbol.raw());
    auto itr = balances.find(owner.value);

    if (itr != balances.end()) {
        auto bal = *itr;
        return bal.tokens;
    }

    return asset(0, token_symbol);
}

#pragma endregion Helper_Functions
