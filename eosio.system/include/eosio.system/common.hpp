/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/lazy_singleton.hpp>

#define SYSTEM_CONTRACT class [[eosio::contract("eosio.system")]]

namespace eosiosystem {
   static constexpr eosio::name active_permission{"active"};
   static constexpr eosio::name system_account{"eosio"};
   static constexpr eosio::name token_account{"eosio.token"};
}

namespace eosio {
   using namespace eosio_ex;
}
