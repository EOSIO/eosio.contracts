#pragma once

#include <eosio/eosio.hpp>
#include <eosio/ignore.hpp>
#include <eosio/transaction.hpp>

namespace eosio {

   class [[eosio::contract("eosio.wrap")]] wrap : public contract {
      public:
         using contract::contract;

         [[eosio::action]]
         void exec( ignore<name> executer, ignore<transaction> trx );

   };

} /// namespace eosio
