#pragma once
#include <eosiolib/domain.hpp>
#include <eosiolib/contract.hpp>

namespace eosiosystem {

class [[eosio::contract("cyber.domain")]] domain_native: public eosio::contract {
public:
    using eosio::contract::contract;

    /**
     *  Called after a new domain is created. This code enforces new domain naming conventions.
     */
    [[eosio::action]] void newdomain(eosio::name creator, const eosio::domain_name& name);
};

}
