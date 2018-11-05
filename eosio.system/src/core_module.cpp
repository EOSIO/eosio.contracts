/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/core_module.hpp>
#include <eosio.system/ram_module.hpp>

#include <eosiolib/system.h>

namespace eosiosystem {

   eosio::symbol core_module::core_symbol()const {
      const static auto sym = ram_module::get_core_symbol( get_module<ram_module>().get_table<rammarket>() );
      return sym;
   }

   eosio::time_point core_module::current_time_point() {
      const static eosio::time_point ct{ eosio::microseconds{ static_cast<int64_t>( current_time() ) } };
      return ct;
   }

   eosio::block_timestamp core_module::current_block_time() {
      const static eosio::block_timestamp cbt{ current_time_point() };
      return cbt;
   }

} /// namespace eosiosystem
