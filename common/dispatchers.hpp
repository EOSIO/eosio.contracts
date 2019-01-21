#pragma once

#include "config.hpp"
#include <eosiolib/dispatcher.hpp>


#define DISPATCH_WITH_TRANSFER(TYPE, TOKEN, TRANSFER, MEMBERS) \
extern "C" { \
   void apply(uint64_t receiver, uint64_t code, uint64_t action) { \
        if (code == receiver) { \
            switch (action) { \
                EOSIO_DISPATCH_HELPER(TYPE, MEMBERS) \
            } \
            /* does not allow destructor of thiscontract to run: eosio_exit(0); */ \
        } else if (code == TOKEN.value && action == "transfer"_n.value) { \
            eosio::execute_action(eosio::name(receiver), eosio::name(code), &TYPE::TRANSFER); \
        } \
   } \
} \
