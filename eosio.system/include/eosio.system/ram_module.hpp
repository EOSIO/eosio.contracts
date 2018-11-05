/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/aggregated_tables.hpp>

namespace eosiosystem {

   class ram_module : public eosio::module::module_base<contract_modules, ram_tables>
   {
   public:
      using module_base_type::module_base_type;

      static constexpr symbol ramcore_symbol = symbol(symbol_code("RAMCORE"), 4);
      static constexpr symbol ram_symbol     = symbol(symbol_code("RAM"), 0);

   protected:
      static symbol get_core_symbol( const rammarket& rm ) {
         auto itr = rm.find( ramcore_symbol.raw() );
         eosio_assert( itr != rm.end(), "system contract must first be initialized" );
         return itr->quote.balance.symbol;
      }

      friend class core_module; // So it can access the rammarket table directly for core_symbol()

   public:
      /** Extracts core symbol for rammarket table */
      static symbol get_core_symbol( eosio::name specified_system_account = system_account ) {
         rammarket rm( specified_system_account, specified_system_account.value );
         const static auto sym = get_core_symbol( rm );
         return sym;
      }

      // Helper methods needed for modules and sub-contracts within this contract:

      uint64_t get_free_ram()const;

      /** @return false iff RAM market was already initialized */
      bool initialize_ram_market( eosio::asset system_token_supply );

      void update_ram_supply();

   };

} /// namespace eosiosystem
