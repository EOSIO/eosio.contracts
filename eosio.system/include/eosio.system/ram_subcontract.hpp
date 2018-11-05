/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/aggregated_tables.hpp>
#include <eosio.system/ram_module.hpp>

namespace eosiosystem {

   SYSTEM_CONTRACT ram_subcontract : public eosio::contract_with_modules<contract_modules, ram_module> {
   public:
      using eosio::contract_with_modules::contract_with_modules;

      using eosio::name;

      ACTION setram( uint64_t max_ram_size );

      /**
       *  Sets the rate of increase of RAM in bytes per block. It is capped by the uint16_t to
       *  a maximum rate of 3 TB per year.
       */
      ACTION setramrate( uint16_t bytes_per_block );

      /**
       * Increases receiver's RAM quota based upon current price and quantity of tokens provided.
       * An inline transfer of quant tokens from receiver to system contract accounts will be executed.
       */
      ACTION buyram( name payer, name receiver, asset quant );
      ACTION buyrambytes( name payer, name receiver, uint32_t bytes );

      /**
       *  Reduces quota by bytes and then performs an inline transfer of tokens
       *  to receiver based upon the current price and amount of bytes sold.
       */
      ACTION sellram( name account, int64_t bytes );
   };

} /// namespace eosiosystem
