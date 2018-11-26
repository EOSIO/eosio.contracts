#pragma once
#include <eosiolib/crypto.h>
#include <eosiolib/eosio.hpp>
#include <eosiolib/privileged.hpp>
#include <eosiolib/action.hpp>
#include <eosio.system/native.hpp>

namespace eosio {

   class [[eosio::contract("eosio.bios")]] bios : public contract {
      public:
         using contract::contract;
         /**
          *  Called after a new account is created. This code enforces resource-limits rules
          *  for new accounts as well as new account naming conventions.
          *
          *  1. accounts cannot contain '.' symbols which forces all acccounts to be 12
          *  characters long without '.' until a future account auction process is implemented
          *  which prevents name squatting.
          *
          *  2. new accounts must stake a minimal number of tokens (as set in system parameters)
          *     therefore, this method will execute an inline buyram from receiver for newacnt in
          *     an amount equal to the current new account creation fee.
          */
         [[eosio::action]]
         void newaccount( name             creator,
                          name             name,
                          ignore<eosiosystem::authority> owner,
                          ignore<eosiosystem::authority> active){}


         [[eosio::action]]
         void updateauth(  ignore<name>  account,
                           ignore<name>  permission,
                           ignore<name>  parent,
                           ignore<eosiosystem::authority> auth ) {}

         [[eosio::action]]
         void deleteauth( ignore<name>  account,
                          ignore<name>  permission ) {}

         [[eosio::action]]
         void linkauth(  ignore<name>    account,
                         ignore<name>    code,
                         ignore<name>    type,
                         ignore<name>    requirement  ) {}

         [[eosio::action]]
         void unlinkauth( ignore<name>  account,
                          ignore<name>  code,
                          ignore<name>  type ) {}

         [[eosio::action]]
         void canceldelay( ignore<permission_level> canceling_auth, ignore<capi_checksum256> trx_id ) {}

         [[eosio::action]]
         void onerror( ignore<uint128_t> sender_id, ignore<std::vector<char>> sent_trx ) {}

         [[eosio::action]]
         void setcode( name account, uint8_t vmtype, uint8_t vmversion, const std::vector<char>& code ) {}

         [[eosio::action]]
         void setpriv( name account, uint8_t is_priv ) {
            require_auth( _self );
            set_privileged( account.value, is_priv );
         }

         [[eosio::action]]
         void setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
            require_auth( _self );
            set_resource_limits( account.value, ram_bytes, net_weight, cpu_weight );
         }

         [[eosio::action]]
         void setglimits( uint64_t ram, uint64_t net, uint64_t cpu ) {
            (void)ram; (void)net; (void)cpu;
            require_auth( _self );
         }

         [[eosio::action]]
         void setprods( std::vector<eosio::producer_key> schedule ) {
            (void)schedule; // schedule argument just forces the deserialization of the action data into vector<producer_key> (necessary check)
            require_auth( _self );

            constexpr size_t max_stack_buffer_size = 512;
            size_t size = action_data_size();
            char* buffer = (char*)( max_stack_buffer_size < size ? malloc(size) : alloca(size) );
            read_action_data( buffer, size );
            set_proposed_producers(buffer, size);
         }

         [[eosio::action]]
         void setparams( const eosio::blockchain_parameters& params ) {
            require_auth( _self );
            set_blockchain_parameters( params );
         }

         [[eosio::action]]
         void reqauth( name from ) {
            require_auth( from );
         }

         [[eosio::action]]
         void setabi( name account, const std::vector<char>& abi ) {
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

         struct [[eosio::table]] abi_hash {
            name              owner;
            capi_checksum256  hash;
            uint64_t primary_key()const { return owner.value; }

            EOSLIB_SERIALIZE( abi_hash, (owner)(hash) )
         };

         typedef eosio::multi_index< "abihash"_n, abi_hash > abi_hash_table;
   };

} /// namespace eosio
