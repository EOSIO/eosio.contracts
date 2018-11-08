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
//#include <eosiolib/types.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;

#pragma region Structs

struct [[eosio::table]] registry {
    asset native;
    name publisher;

    uint64_t primary_key() const { return native.symbol.raw(); }
    uint64_t by_publisher() const { return publisher.value; }
    EOSLIB_SERIALIZE(registry, (native)(publisher))
};

struct [[eosio::table]] balance {
    name owner;
    asset tokens;

    uint64_t primary_key() const { return owner.value; }
    EOSLIB_SERIALIZE(balance, (owner)(tokens))
};

// struct trail_transfer_args {
//     name sender;
//     name recipient;
//     asset tokens;
// };

#pragma endregion Structs

#pragma region Tables

typedef multi_index<name("balances"), balance> balances_table;

typedef multi_index<name("registries"), registry,
    indexed_by<name("bypub"), const_mem_fun<registry, uint64_t, &registry::by_publisher>>> registries_table;

#pragma endregion Tables

#pragma region Helper_Functions

bool is_trail_token(symbol sym) {
    registries_table registries(name("eosio.trail"), name("eosio.trail").value);
    auto r = registries.find(sym.raw());

    if (r != registries.end()) {
        return true;
    }

    return false;
}

bool is_registry(name publisher) {
    registries_table registries(name("eosio.trail"), name("eosio.trail").value);
    auto by_pub = registries.get_index<name("bypub")>();
    auto itr = by_pub.lower_bound(publisher.value);

    if (itr != by_pub.end()) {
        return true;
    }

    return false;
}

registries_table::const_iterator find_registry(symbol sym) {
    registries_table registries(name("eosio.trail"), name("eosio.trail").value);
    auto itr = registries.find(sym.raw());

    if (itr != registries.end()) {
        return itr;
    }

    return registries.end();
}

registry get_registry(symbol sym) {
    registries_table registries(name("eosio.trail"), name("eosio.trail").value);
    return registries.get(sym.raw());
}

// symbol get_sym(name publisher) {
//     registries_table registries(name("eosio.trail"), name("eosio.trail").value);
//     auto by_pub = registries.get_index<name("bypub")>();
//     auto itr = by_pub.lower_bound(publisher.value);

//     return itr->native.symbol.raw();
// }

asset get_token_balance(symbol sym, name voter) {
    auto reg = get_registry(sym).publisher;

    balances_table balances(reg, voter.value);
    auto b = balances.get(voter.value);

    return b.tokens;
}

#pragma endregion Helper_Functions
