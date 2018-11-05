/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/ram_module.hpp>

namespace eosiosystem {

   uint64_t ram_module::get_free_ram()const {
      const auto& g1 = get_module<core_module>().get_table<global1_singleton>().get();
      return (g1.max_ram_size - g1.total_ram_bytes_reserved);
   }

   bool ram_module::initialize_ram_market( eosio::asset system_token_supply ) {
      if( system_token.supply.amount <= 0 ) {
         eosio_assert( false, "system token supply must be greater than 0" );
      }

      auto& rm = get_table<rammarket>();

      auto itr = rm.find( ramcore_symbol.raw() );
      if( itr != rm.end() )
         return false;

      rm.emplace( get_self(), [&]( auto& m ) {
         m.supply.amount = 100000000000000ll;
         m.supply.symbol = ramcore_symbol;
         m.base.balance.amount = int64_t( get_free_ram() );
         m.base.balance.symbol = ram_symbol;
         m.quote.balance.amount = system_token_supply.amount / 1000;
         m.quote.balance.symbol = system_token_supply.symbol;
      });

      return true;
   }

   void ram_module::update_ram_supply() {
      auto cbt = current_block_time();

      auto cm = get_module<core_module>();

      auto& g2s = cm.get_table<global2_singleton>();
      const auto& g2 = g2s.get();

      if( cbt <= g2.last_ram_increase ) return;

      auto new_ram = (cbt.slot - g2.last_ram_increase.slot) * g2.new_ram_per_block;
      cm.get_table<global_singleton>().modify( [&]( auto& g1 ) {
         g1.max_ram_size += new_ram;
      });

      // Increase the amount of ram for sale based upon the change in max ram size.
      auto& rmt = get_table<rammarket>();
      auto itr = rmt.find( ram_module::ramcore_symbol.raw() );
      rmt.modify( itr, same_payer, [&]( auto& r ) {
         r.base.balance.amount += new_ram;
      });

      cm.get_table<global2_singleton>().modify( [&]( auto& g2 ) {
         g2.last_ram_increase = cbt;
      })
   }

} /// namespace eosiosystem
