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
    bool is_destructible = false;
    bool is_proxyable = false; //NOTE: allows proxy system //TODO: implement
    bool is_burnable = false; //NOTE: can only burn from own balance
    bool is_seizable = false;
    bool is_max_mutable = false;
    bool is_transferable = false; //NOTE: allows counerbalances and cb decay
    bool is_recastable = false;
    bool is_initialized = false;

    uint32_t counterbal_decay_rate = 300; //seconds to decay by 1 whole token
    bool lock_after_initialize = true;
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

//NOTE: balances are scoped by symbol.code().raw()
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

//NOTE: airgrabs are scoped by publisher.value
struct [[eosio::table, eosio::contract("eosio.trail")]] airgrab {
    name recipient;
    asset tokens;

    uint64_t primary_key() const { return recipient.value; }
    EOSLIB_SERIALIZE(airgrab, (recipient)(tokens))
};

//NOTE: counterbalances are scoped by symbol.code().raw()
struct [[eosio::table, eosio::contract("eosio.trail")]] counter_balance {
    name owner;
    asset decayable_cb;
    asset persistent_cb;
    uint32_t last_decay;

    uint64_t primary_key() const { return owner.value; }
    EOSLIB_SERIALIZE(counter_balance, (owner)(decayable_cb)(persistent_cb)(last_decay))
};

#pragma endregion Structs


#pragma region Tables

typedef multi_index<name("balances"), balance> balances_table;

typedef multi_index<name("counterbals"), counter_balance> counterbalances_table;

//typedef multi_index<name("proxybals"), proxy_balance> proxy_balances_table;

typedef multi_index<name("airgrabs"), airgrab> airgrabs_table;

typedef multi_index<name("registries"), registry> registries_table;

#pragma endregion Tables


#pragma region Helper_Functions



#pragma endregion Helper_Functions
