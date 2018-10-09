#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/ignore.hpp>
#include <eosiolib/transaction.hpp>

namespace eosio {

   class [[eosio::contract]] sudo : public contract {
      public:
         sudo( name self, name code, datastream<const char*> ds ):contract(self,code,ds){}

         [[eosio::action]]
         void exec(ignore<name> executer, ignore<transaction> trx);

   };

} /// namespace eosio
