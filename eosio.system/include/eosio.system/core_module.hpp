/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/aggregated_tables.hpp>

namespace eosiosystem {

   class core_module : public eosio::module::module_base<contract_modules, core_tables>
   {
   public:
      using module_base_type::module_base_type;
      //explicit core_module( contract_modules& mm ) : module_base_type(mm) {}

      friend class ram_module; // So it can access the global and global2 tables directly for RAM-related data

      static time_point      current_time_point();
      static block_timestamp current_block_time();

      // Helper methods needed for modules and sub-contracts within this contract:

      eosio::symbol core_symbol()const;

   };

} /// namespace eosiosystem
