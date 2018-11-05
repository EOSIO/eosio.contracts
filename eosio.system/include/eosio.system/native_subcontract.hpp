/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/aggregated_tables.hpp>
#include <eosiolib/ignore.hpp>

namespace eosiosystem {

   SYSTEM_CONTRACT native_subcontract : public eosio::contract_with_modules<contract_modules> {
   public:
      using eosio::contract_with_modules::contract_with_modules;

      using eosio::name;
      using eosio::permission_level;
      using eosio::public_key;
      using eosio::ignore;

      struct permission_level_weight {
         permission_level  permission;
         uint16_t          weight;

         // explicit serialization macro is not necessary, used here only to improve compilation time
         EOSLIB_SERIALIZE( permission_level_weight, (permission)(weight) )
      };

      struct key_weight {
         eosio::public_key  key;
         uint16_t           weight;

         // explicit serialization macro is not necessary, used here only to improve compilation time
         EOSLIB_SERIALIZE( key_weight, (key)(weight) )
      };

      struct wait_weight {
         uint32_t           wait_sec;
         uint16_t           weight;

         // explicit serialization macro is not necessary, used here only to improve compilation time
         EOSLIB_SERIALIZE( wait_weight, (wait_sec)(weight) )
      };

      struct authority {
         uint32_t                              threshold = 0;
         std::vector<key_weight>               keys;
         std::vector<permission_level_weight>  accounts;
         std::vector<wait_weight>              waits;

         // explicit serialization macro is not necessary, used here only to improve compilation time
         EOSLIB_SERIALIZE( authority, (threshold)(keys)(accounts)(waits) )
      };

      struct block_header {
         uint32_t                                  timestamp;
         name                                      producer;
         uint16_t                                  confirmed = 0;
         capi_checksum256                          previous;
         capi_checksum256                          transaction_mroot;
         capi_checksum256                          action_mroot;
         uint32_t                                  schedule_version = 0;
         std::optional<eosio::producer_schedule>   new_producers;

         // explicit serialization macro is not necessary, used here only to improve compilation time
         EOSLIB_SERIALIZE(block_header, (timestamp)(producer)(confirmed)(previous)(transaction_mroot)(action_mroot)
                                        (schedule_version)(new_producers))
      };

      /**
       *  Called after a new account is created. This code enforces resource-limits rules
       *  for new accounts as well as new account naming conventions.
       *
       *  1. accounts cannot contain '.' symbols which forces all acccounts to be 12
       *  characters long without '.' until a future account auction process is implemented
       *  which prevents name squatting.
       *
       *  2. new accounts must stake a minimal number of tokens (as set in system parameters)
       *     therefore, this method will execute an inline buyram from receiver for newacnt in
       *     an amount equal to the current new account creation fee.
       */
      ACTION newaccount( name               creator,
                         name               newact,
                         ignore<authority>  owner,
                         ignore<authority>  active );


      ACTION updateauth( ignore<name>      account,
                         ignore<name>      permission,
                         ignore<name>      parent,
                         ignore<authority> auth ) {}

      ACTION deleteauth( ignore<name>  account,
                         ignore<name>  permission ) {}

      ACTION linkauth( ignore<name>    account,
                       ignore<name>    code,
                       ignore<name>    type,
                       ignore<name>    requirement ) {}

      ACTION unlinkauth( ignore<name>  account,
                         ignore<name>  code,
                         ignore<name>  type ) {}

      ACTION canceldelay( ignore<permission_level> canceling_auth,
                          ignore<capi_checksum256> trx_id ) {}

      ACTION onerror( ignore<uint128_t> sender_id,
                      ignore<std::vector<char>> sent_trx ) {}

      ACTION setabi( name account,
                     const std::vector<char>& abi );

      ACTION setcode( ignore<name> account,
                      ignore<uint8_t> vmtype,
                      ignore<uint8_t> vmversion,
                      ignore<std::vector<char>> code ) {}

   };

} /// namespace eosiosystem
