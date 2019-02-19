#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>

namespace cyber {
using eosio::name;
using eosio::contract;

class [[contract("cyber.govern")]] govern : public contract {
    struct [[eosio::table("state")]] state_info {
        uint16_t last_producers_num = 0;
    };
    using state_singleton = eosio::singleton<"governstate"_n, state_info>;
public:
    using contract::contract;
    [[eosio::action]] void update(name producer);
};

} /// cyber
