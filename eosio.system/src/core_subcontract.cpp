/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/core_subcontract.hpp>

namespace eosiosystem {

   void core_subcontract::init( unsigned_int version, symbol core ) {
      require_auth( _self );
      eosio_assert( version.value == 0, "unsupported version for init action" );

      auto system_token_supply = eosio::token::get_supply(token_account, core.code() );
      eosio_assert( system_token_supply.symbol == core, "specified core symbol does not exist (precision mismatch)" );

      bool success = _mm.get_module<ram_module>().initialize_ram_market( system_token_supply );
      eosio_assert( success, "system contract has already been initialized" );
   }

   void core_subcontract::setparams( const eosio::blockchain_parameters& params ) {
      require_auth( _self );
      eosio_assert( 3 <= params.max_authority_depth, "max_authority_depth should be at least 3" );

      set_blockchain_parameters( params );
      _module.get_table<global1_singleton>().modify( [&]( auto& g1 ) {
         (eosio::blockchain_parameters&)(g1) = params;
      });
   }

   void core_subcontract::updtrevision( uint8_t revision ) {
      require_auth( _self );

      auto& g2s = _module.get_table<global2_singleton>();
      auto current_revision = g2s.get().revision;

      eosio_assert( current_revision < 255, "can not increment revision" ); // prevent wrap around
      eosio_assert( revision == current_revision + 1, "can only increment revision by one" );
      eosio_assert( revision <= 1, // set upper bound to greatest revision supported in the code
                    "specified revision is not yet supported by the code" );

      g2s.modify( [&]( auto& g2 ) {
         g2.revision = revision;
      })
   }

   void core_subcontract::setpriv( name account, uint8_t is_priv ) {
      require_auth( _self );

      set_privileged( account.value, is_priv );
   }

   void core_subcontract::setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
      require_auth( _self );

      auto& userres = _module.get_table<user_resources_table>( account.value );
      auto ritr = userres.find( account.value );
      eosio_assert( ritr == userres.end(), "only supports unlimited accounts" );
      set_resource_limits( account.value, ram_bytes, net_weight, cpu_weight );
   }

} /// namespace eosiosystem
