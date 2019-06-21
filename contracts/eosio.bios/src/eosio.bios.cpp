#include <eosio.bios/eosio.bios.hpp>

namespace eosio {

void bios::setabi( name account, const std::vector<char>& abi ) {
   abi_hash_table table(_self, _self.value);
   auto itr = table.find( account.value );
   if( itr == table.end() ) {
      table.emplace( account, [&]( auto& row ) {
         row.owner = account;
         sha256( const_cast<char*>(abi.data()), abi.size(), &row.hash );
      });
   } else {
      table.modify( itr, same_payer, [&]( auto& row ) {
         sha256( const_cast<char*>(abi.data()), abi.size(), &row.hash );
      });
   }
}

void bios::setpriv( name account, uint8_t is_priv ) {
   require_auth( _self );
   set_privileged( account.value, is_priv );
}

void bios::setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
   require_auth( _self );
   set_resource_limits( account.value, ram_bytes, net_weight, cpu_weight );
}

void bios::setprods( std::vector<eosio::producer_key> schedule ) {
   (void)schedule; // schedule argument just forces the deserialization of the action data into vector<producer_key> (necessary check)
   require_auth( _self );

   constexpr size_t max_stack_buffer_size = 512;
   size_t size = action_data_size();
   char* buffer = (char*)( max_stack_buffer_size < size ? malloc(size) : alloca(size) );
   read_action_data( buffer, size );
   set_proposed_producers(buffer, size);
}

void bios::setparams( const eosio::blockchain_parameters& params ) {
   require_auth( _self );
   set_blockchain_parameters( params );
}

void bios::reqauth( name from ) {
   require_auth( from );
}

void bios::activate( const eosio::checksum256& feature_digest ) {
   require_auth( get_self() );
   preactivate_feature( feature_digest );
}

void bios::reqactivated( const eosio::checksum256& feature_digest ) {
   check( is_feature_activated( feature_digest ), "protocol feature is not activated" );
}

}
