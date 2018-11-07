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
#include <eosiolib/types.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;

#pragma region Structs

/// @abi table registries i64
struct registration {
    asset native;
    account_name publisher;

    uint64_t primary_key() const { return native.symbol.name(); }
    uint64_t by_publisher() const { return publisher; }
    EOSLIB_SERIALIZE(registration, (native)(publisher))
};

/// @abi table balances i64
struct balance {
    account_name owner;
    asset tokens;

    uint64_t primary_key() const { return owner; }
    EOSLIB_SERIALIZE(balance, (owner)(tokens))
};

struct trail_transfer_args {
    account_name sender;
    account_name recipient;
    asset tokens;
};

#pragma endregion Structs

#pragma region Tables

typedef multi_index<N(balances), balance> balances_table;

typedef multi_index<N(registries), registration,
    indexed_by<N(bypub), const_mem_fun<registration, uint64_t, &registration::by_publisher>>> registries_table;

#pragma endregion Tables

#pragma region Helper_Functions

bool is_trail_token(symbol_name sym) {
    registries_table registries(N(eosio.trail), N(eosio.trail));
    auto r = registries.find(sym);

    if (r != registries.end()) {
        return true;
    }

    return false;
}

bool is_registry(account_name publisher) {
    registries_table registries(N(eosio.trail), N(eosio.trail));
    auto by_pub = registries.get_index<N(bypub)>();
    auto itr = by_pub.lower_bound(publisher);

    if (itr != by_pub.end()) {
        return true;
    }

    return false;
}

registries_table::const_iterator find_registry(symbol_name sym) {
    registries_table registries(N(eosio.trail), N(eosio.trail));
    auto itr = registries.find(sym);

    if (itr != registries.end()) {
        return itr;
    }

    return registries.end();
}

registration get_registry(symbol_name sym) {
    registries_table registries(N(eosio.trail), N(eosio.trail));
    return registries.get(sym);
}

symbol_name get_sym(account_name publisher) {
    registries_table registries(N(eosio.trail), N(eosio.trail));
    auto by_pub = registries.get_index<N(bypub)>();
    auto itr = by_pub.lower_bound(publisher);

    return itr->native.symbol.name();
}

asset get_token_balance(symbol_name sym, account_name voter) {
    auto reg = get_registry(sym).publisher;

    balances_table balances(reg, voter);
    auto b = balances.get(voter);

    return b.tokens;
}

#pragma endregion Helper_Functions
