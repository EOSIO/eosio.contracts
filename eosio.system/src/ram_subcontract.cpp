/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/ram_subcontract.hpp>
#include <eosio.system/core_module.hpp>

namespace eosiosystem {

   void ram_subcontract::setram( uint64_t max_ram_size ) {
      require_auth( _self );

      _module.update_ram_supply();

      auto cm = _mm.get_module<core_module>();
      auto& g1s = cm.get_table<global_singleton>();
      const auto& g1 = g1s.get();

      eosio_assert( g1.max_ram_size < max_ram_size,  "ram may only be increased" ); /// decreasing ram might result in market maker issues
      eosio_assert( max_ram_size < 1024ll*1024*1024*1024*1024, "ram size is unrealistic" );
      eosio_assert( max_ram_size > g1.total_ram_bytes_reserved, "attempt to set max below reserved" );

      auto delta = int64_t(max_ram_size) - int64_t(g1.max_ram_size);

      // Increase the amount of ram for sale based upon the change in max ram size.
      auto& rmt = get_table<rammarket>();
      auto itr = rmt.find( ram_module::ramcore_symbol.raw() );
      rmt.modify( itr, same_payer, [&]( auto& r ) {
         r.base.balance.amount += delta;
      });

      g1s.modify( [&]( auto& g1 ) {
         g1.max_ram_size = max_ram_size;
      });
   }

   void ram_subcontract::setramrate( uint16_t bytes_per_block ) {
      require_auth( _self );

      _module.update_ram_supply();

      auto cm = _mm.get_module<core_module>();
      cm.get_table<global2_singleton>().modify( [&]( auto& g2 ) {
         g2.new_ram_per_block = bytes_per_block;
      });
   }

   void ram_subcontract::buyram( name payer, name receiver, asset quant ) {
      
   }

   void ram_subcontract::buyrambytes( name payer, name receiver, uint32_t bytes ) {

   }

   void ram_subcontract::sellram( name account, int64_t bytes ) {

   }

} /// namespace eosiosystem
