/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/aggregated_tables.hpp>
#include <eosio.system/name_auction_module.hpp>

namespace eosiosystem {

   SYSTEM_CONTRACT name_auction_subcontract : public eosio::contract_with_modules<contract_modules, name_auction_module> {
   public:
      using eosio::contract_with_modules::contract_with_modules;

      using eosio::name;

      ACTION bidname( name bidder, name newname, asset bid );

      ACTION bidrefund( name bidder, name newname );

   };

} /// namespace eosiosystem
