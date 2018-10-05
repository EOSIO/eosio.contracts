#pragma once
#include <eosiolib/crypto.h>
#include <eosiolib/eosio.hpp>
#include <eosiolib/privileged.hpp>

namespace eosio {

   struct abi_hash {
      name              owner;
      capi_checksum256  hash;
      uint64_t primary_key()const { return owner.value; }

      EOSLIB_SERIALIZE( abi_hash, (owner)(hash) )
   };

   typedef eosio::multi_index< "abihash"_n, abi_hash > abi_hash_table;

   class bios : public contract {
      public:
         bios( name self ):contract(self){}

         void setpriv( name account, uint8_t ispriv ) {
            require_auth( _self );
            set_privileged( account.value, ispriv );
         }

         void setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
            require_auth( _self );
            set_resource_limits( account.value, ram_bytes, net_weight, cpu_weight );
         }

         void setglimits( uint64_t ram, uint64_t net, uint64_t cpu ) {
            (void)ram; (void)net; (void)cpu;
            require_auth( _self );
         }

         void setprods( std::vector<eosio::producer_key> schedule ) {
            (void)schedule; // schedule argument just forces the deserialization of the action data into vector<producer_key> (necessary check)
            require_auth( _self );

            constexpr size_t max_stack_buffer_size = 512;
            size_t size = action_data_size();
            char* buffer = (char*)( max_stack_buffer_size < size ? malloc(size) : alloca(size) );
            read_action_data( buffer, size );
            set_proposed_producers(buffer, size);
         }

         void setparams( const eosio::blockchain_parameters& params ) {
            require_auth( _self );
            set_blockchain_parameters( params );
         }

         void reqauth( name from ) {
            require_auth( from );
         }

         void setabi( name acnt, const std::vector<char>& abi ) {
            abi_hash_table table(_self, _self.value);
            auto itr = table.find( acnt.value );
            if( itr == table.end() ) {
               table.emplace( acnt, [&]( auto& row ) {
                  row.owner = acnt;
                  sha256( const_cast<char*>(abi.data()), abi.size(), &row.hash );
               });
            } else {
               table.modify( itr, same_payer, [&]( auto& row ) {
                  sha256( const_cast<char*>(abi.data()), abi.size(), &row.hash );
               });
            }
         }

      private:
   };

} /// namespace eosio
