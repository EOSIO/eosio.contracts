#pragma once
#include <eosiolib/action.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/eosio.hpp>
#include <eosiolib/privileged.hpp>
#include <eosiolib/producer_schedule.hpp>

/** 
 * EOSIO Contracts
 * 
 * @details The design of the EOSIO blockchain calls for a number of smart contracts that are run at a 
 * privileged permission level in order to support functions such as block producer registration and 
 * voting, token staking for CPU and network bandwidth, RAM purchasing, multi-sig, etc. These smart 
 * contracts are referred to as the system, token, msig and wrap (formerly known as sudo) contracts.
 * 
 * This repository contains examples of these privileged contracts that are useful when deploying, 
 * managing, and/or using an EOSIO blockchain. They are provided for reference purposes:
 * - eosio.bios
 * - eosio.system
 * - eosio.msig
 * - eosio.wrap
 * 
 * The following unprivileged contract(s) are also part of the system.
 * - eosio.token
 */

namespace eosio {

   using eosio::permission_level;
   using eosio::public_key;
   using eosio::ignore;

   /**
    * A weighted permission. 
    * 
    * @details Defines a weighted permission, that is a permission which has a weight associated. 
    * A permission is defined by an account name plus a permission name.
    */
   struct permission_level_weight {
      permission_level  permission;
      uint16_t          weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( permission_level_weight, (permission)(weight) )
   };

   /**
    * Weighted key.
    * 
    * @details A weigted key is defined by a public key and an associated weight.
    */
   struct key_weight {
      eosio::public_key  key;
      uint16_t           weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( key_weight, (key)(weight) )
   };

   /**
    * Wait weight.
    * 
    * @details A wait weight is defined by a number of seconds to wait for and a weight.
    */
   struct wait_weight {
      uint32_t           wait_sec;
      uint16_t           weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( wait_weight, (wait_sec)(weight) )
   };

   /**
    * Blockchain authority.
    * 
    * @details An authority is defined by:
    * - a vector of key_weights (a key_weight is a public key plus a wieght),
    * - a vector of permission_level_weights, (a permission_level is an account name plus a permission name)
    * - a vector of wait_weights (a wait_weight is defined by a number of seconds to wait and a weight)
    * - a threshold value
    */
   struct authority {
      uint32_t                              threshold = 0;
      std::vector<key_weight>               keys;
      std::vector<permission_level_weight>  accounts;
      std::vector<wait_weight>              waits;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( authority, (threshold)(keys)(accounts)(waits) )
   };

   /**
    * Blockchain block header.
    * 
    * @details A block header is defined by:
    * - a timestamp,
    * - the producer that created it,
    * - a confirme flag default as zero,
    * - a link to previous block,
    * - a link to the transaction merkel root,
    * - a link to action root,
    * - a schedule version,
    * - and a producers' schedule.
    */
   struct block_header {
      uint32_t                                  timestamp;
      name                                      producer;
      uint16_t                                  confirmed = 0;
      capi_checksum256                          previous;
      capi_checksum256                          transaction_mroot;
      capi_checksum256                          action_mroot;
      uint32_t                                  schedule_version = 0;
      std::optional<eosio::producer_schedule>   new_producers;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE(block_header, (timestamp)(producer)(confirmed)(previous)(transaction_mroot)(action_mroot)
                                     (schedule_version)(new_producers))
   };

   /**
    * @defgroup eosiobios eosio.bios
    * @ingroup eosiocontracts
    * 
    * eosio.bios contract defines the actions that govern authentication, 
    * authorization, permissions, blockchain properties and producers schedule.
    * 
    * @{
    */
   class [[eosio::contract("eosio.bios")]] bios : public contract {
      public:
         using contract::contract;
         /**
          * @{
          * These actions map one-on-one with the ones defined in 
          * [Native Action Handlers](@ref native_action_handlers) section.
          */
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
                          ignore<authority> owner,
                          ignore<authority> active){}
         /**
          * Update authorization action.
          */
         [[eosio::action]]
         void updateauth(  ignore<name>  account,
                           ignore<name>  permission,
                           ignore<name>  parent,
                           ignore<authority> auth ) {}

         /**
          * Delete authorization action.
          */
         [[eosio::action]]
         void deleteauth( ignore<name>  account,
                          ignore<name>  permission ) {}

         /**
          * Link authorization action.
          */
         [[eosio::action]]
         void linkauth(  ignore<name>    account,
                         ignore<name>    code,
                         ignore<name>    type,
                         ignore<name>    requirement  ) {}

         /**
          * Unlink authorization action.
          */
         [[eosio::action]]
         void unlinkauth( ignore<name>  account,
                          ignore<name>  code,
                          ignore<name>  type ) {}

         /**
          * Cancel delay action.
          */
         [[eosio::action]]
         void canceldelay( ignore<permission_level> canceling_auth, ignore<capi_checksum256> trx_id ) {}

         /**
          * On error action.
          * 
          * @details Called every time an error occurs while a transaction was processed.
          */
         [[eosio::action]]
         void onerror( ignore<uint128_t> sender_id, ignore<std::vector<char>> sent_trx ) {}

         /**
          * Set code action.
          */
         [[eosio::action]]
         void setcode( name account, uint8_t vmtype, uint8_t vmversion, const std::vector<char>& code ) {}
         
         /** @}*/

         /**
          * Set privilege status for an account.
          * 
          * @details Allows to set privilege status for an account (turn it on/off).
          * @param account - the account to set the privileged status for.
          * @param is_priv - 0 for false, > 0 for true.
          */
         [[eosio::action]]
         void setpriv( name account, uint8_t is_priv ) {
            require_auth( _self );
            set_privileged( account.value, is_priv );
         }

         /**
          * Set the resource limits of an account
          * 
          * @details Set the resource limits of an account
          * 
          * @param account - name of the account whose resource limit to be set
          * @param ram_bytes - ram limit in absolute bytes
          * @param net_weight - fractionally proportionate net limit of available resources based on (weight / total_weight_of_all_accounts)
          * @param cpu_weight - fractionally proportionate cpu limit of available resources based on (weight / total_weight_of_all_accounts)
          */
         [[eosio::action]]
         void setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight ) {
            require_auth( _self );
            set_resource_limits( account.value, ram_bytes, net_weight, cpu_weight );
         }

         /**
          * Set global resource limits.
          * 
          * @details Not implemented yet.
          * Set global resource' limits
          * 
          * @param ram  - ram limit
          * @param net - net limit
          * @param cpu - cpu limit
          */
         [[eosio::action]]
         void setglimits( uint64_t ram, uint64_t net, uint64_t cpu ) {
            (void)ram; (void)net; (void)cpu;
            require_auth( _self );
         }

         /**
          * Set a new list of active producers, that is, a new producers' schedule.
          * 
          * @details Set a new list of active producers, by proposing a schedule change, once the block that 
          * contains the proposal becomes irreversible, the schedule is promoted to "pending" 
          * automatically. Once the block that promotes the schedule is irreversible, the schedule will 
          * become "active".
          * 
          * @param schedule - New list of active producers to set
          */
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

         /**
          * Set the blockchain parameters
          * 
          * @details Set the blockchain parameters. By tunning these parameters a degree of customization can be achieved.
          * 
          * @param params - New blockchain parameters to set
          */
         [[eosio::action]]
         void setparams( const eosio::blockchain_parameters& params ) {
            require_auth( _self );
            set_blockchain_parameters( params );
         }

         /**
          * Check if an account has authorization to access current action.
          * 
          * @details Checks if the account name `from` passed in as param has authorization to access 
          * current action, that is, if it is listed in the action’s allowed permissions vector.
          * 
          * @param from - the account name to authorize
          */
         [[eosio::action]]
         void reqauth( name from ) {
            require_auth( from );
         }

         /**
          * Set abi for contract.
          * 
          * @details Set the abi for contract identified by `account` name. Creates an entry in the abi_hash_table 
          * index, with `account` name as key, if it is not already present and sets its value with the abi hash.
          * Otherwise it is updating the current abi hash value for the existing `account` key.
          * 
          * @param account - the name of the account to set the abi for
          * @param abi     - the abi hash represented as a vector of characters
          */
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

         /**
          * Abi hash structure
          * 
          * @details Abi has structure is defined by contract owner and the contract hash.
          */
         struct [[eosio::table]] abi_hash {
            name              owner;
            capi_checksum256  hash;
            uint64_t primary_key()const { return owner.value; }

            EOSLIB_SERIALIZE( abi_hash, (owner)(hash) )
         };

         /**
          * Multi index table that stores the contracts' abi index by their owners/accounts.
          */
         typedef eosio::multi_index< "abihash"_n, abi_hash > abi_hash_table;
         
         using newaccount_action = action_wrapper<"newaccount"_n, &bios::newaccount>;
         using updateauth_action = action_wrapper<"updateauth"_n, &bios::updateauth>;
         using deleteauth_action = action_wrapper<"deleteauth"_n, &bios::deleteauth>;
         using linkauth_action = action_wrapper<"linkauth"_n, &bios::linkauth>;
         using unlinkauth_action = action_wrapper<"unlinkauth"_n, &bios::unlinkauth>;
         using canceldelay_action = action_wrapper<"canceldelay"_n, &bios::canceldelay>;
         using setcode_action = action_wrapper<"setcode"_n, &bios::setcode>;
         using setpriv_action = action_wrapper<"setpriv"_n, &bios::setpriv>;
         using setalimits_action = action_wrapper<"setalimits"_n, &bios::setalimits>;
         using setglimits_action = action_wrapper<"setglimits"_n, &bios::setglimits>;
         using setprods_action = action_wrapper<"setprods"_n, &bios::setprods>;
         using setparams_action = action_wrapper<"setparams"_n, &bios::setparams>;
         using reqauth_action = action_wrapper<"reqauth"_n, &bios::reqauth>;
         using setabi_action = action_wrapper<"setabi"_n, &bios::setabi>;
   };
   /** @}*/ // end of @defgroup eosiobios eosio.bios
} /// namespace eosio
