/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/aggregated_tables.hpp>
#include <eosio.system/core_module.hpp>

namespace eosiosystem {

   SYSTEM_CONTRACT core_subcontract : public eosio::contract_with_modules<contract_modules, core_module> {
   public:
      using eosio::contract_with_modules::contract_with_modules;

      ACTION init( unsigned_int version, symbol core );

      ACTION setparams( const eosio::blockchain_parameters& params );

      ACTION updtrevision( uint8_t revision );

      ACTION setpriv( name account, uint8_t is_priv );

      ACTION setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight );
   };

} /// namespace eosiosystem
