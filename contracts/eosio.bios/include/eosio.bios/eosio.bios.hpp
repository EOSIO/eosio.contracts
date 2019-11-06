#pragma once

#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/fixed_bytes.hpp>
#include <eosio/privileged.hpp>
#include <eosio/producer_schedule.hpp>

// This header is needed until `is_feature_activiated` and `preactivate_feature` are added to `eosio.cdt`
#include <eosio/../../capi/eosio/crypto.h>

namespace eosio {
   namespace internal_use_do_not_use {
      extern "C" {
         __attribute__((eosio_wasm_import))
         bool is_feature_activated( const ::capi_checksum256* feature_digest );

         __attribute__((eosio_wasm_import))
         void preactivate_feature( const ::capi_checksum256* feature_digest );
      }
   }
}

namespace eosio {
   bool is_feature_activated( const eosio::checksum256& feature_digest ) {
      auto feature_digest_data = feature_digest.extract_as_byte_array();
      return internal_use_do_not_use::is_feature_activated(
         reinterpret_cast<const ::capi_checksum256*>( feature_digest_data.data() )
      );
   }

   void preactivate_feature( const eosio::checksum256& feature_digest ) {
      auto feature_digest_data = feature_digest.extract_as_byte_array();
      internal_use_do_not_use::preactivate_feature(
         reinterpret_cast<const ::capi_checksum256*>( feature_digest_data.data() )
      );
   }
}

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

   using eosio::ignore;
   using eosio::permission_level;
   using eosio::public_key;

   struct permission_level_weight {
      permission_level  permission;
      uint16_t          weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( permission_level_weight, (permission)(weight) )
   };

   struct key_weight {
      eosio::public_key  key;
      uint16_t           weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( key_weight, (key)(weight) )
   };

   struct wait_weight {
      uint32_t           wait_sec;
      uint16_t           weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( wait_weight, (wait_sec)(weight) )
   };

   struct authority {
      uint32_t                              threshold = 0;
      std::vector<key_weight>               keys;
      std::vector<permission_level_weight>  accounts;
      std::vector<wait_weight>              waits;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( authority, (threshold)(keys)(accounts)(waits) )
   };

   struct block_header {
      uint32_t                                  timestamp;
      name                                      producer;
      uint16_t                                  confirmed = 0;
      checksum256                               previous;
      checksum256                               transaction_mroot;
      checksum256                               action_mroot;
      uint32_t                                  schedule_version = 0;
      std::optional<eosio::producer_schedule>   new_producers;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE(block_header, (timestamp)(producer)(confirmed)(previous)(transaction_mroot)(action_mroot)
                                     (schedule_version)(new_producers))
   };

   class [[eosio::contract("eosio.bios")]] bios : public contract {
      public:
         using contract::contract;
         /**
          * New account action
          *
          * @details Called after a new account is created. This code enforces resource-limits rules
          * for new accounts as well as new account naming conventions.
          *
          * 1. accounts cannot contain '.' symbols which forces all acccounts to be 12
          * characters long without '.' until a future account auction process is implemented
          * which prevents name squatting.
          *
          * 2. new accounts must stake a minimal number of tokens (as set in system parameters)
          * therefore, this method will execute an inline buyram from receiver for newacnt in
          * an amount equal to the current new account creation fee.
          */
         [[eosio::action]]
         void newaccount( name             creator,
                          name             name,
                          ignore<authority> owner,
                          ignore<authority> active){}
         /**
          * Update authorization action.
          *
          * @details Updates pemission for an account.
          *
          * @param account - the account for which the permission is updated,
          * @param pemission - the permission name which is updated,
          * @param parem - the parent of the permission which is updated,
          * @param aut - the json describing the permission authorization.
          */
         [[eosio::action]]
         void updateauth(  ignore<name>  account,
                           ignore<name>  permission,
                           ignore<name>  parent,
                           ignore<authority> auth ) {}

         /**
          * Delete authorization action.
          *
          * @details Deletes the authorization for an account's permision.
          *
          * @param account - the account for which the permission authorization is deleted,
          * @param permission - the permission name been deleted.
          */
         [[eosio::action]]
         void deleteauth( ignore<name>  account,
                          ignore<name>  permission ) {}

         /**
          * Link authorization action.
          *
          * @details Assigns a specific action from a contract to a permission you have created. Five system
          * actions can not be linked `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, and `canceldelay`.
          * This is useful because when doing authorization checks, the EOSIO based blockchain starts with the
          * action needed to be authorized (and the contract belonging to), and looks up which permission
          * is needed to pass authorization validation. If a link is set, that permission is used for authoraization
          * validation otherwise then active is the default, with the exception of `eosio.any`.
          * `eosio.any` is an implicit permission which exists on every account; you can link actions to `eosio.any`
          * and that will make it so linked actions are accessible to any permissions defined for the account.
          *
          * @param account - the permission's owner to be linked and the payer of the RAM needed to store this link,
          * @param code - the owner of the action to be linked,
          * @param type - the action to be linked,
          * @param requirement - the permission to be linked.
          */
         [[eosio::action]]
         void linkauth(  ignore<name>    account,
                         ignore<name>    code,
                         ignore<name>    type,
                         ignore<name>    requirement  ) {}

         /**
          * Unlink authorization action.
          *
          * @details It's doing the reverse of linkauth action, by unlinking the given action.
          *
          * @param account - the owner of the permission to be unlinked and the receiver of the freed RAM,
          * @param code - the owner of the action to be unlinked,
          * @param type - the action to be unlinked.
          */
         [[eosio::action]]
         void unlinkauth( ignore<name>  account,
                          ignore<name>  code,
                          ignore<name>  type ) {}

         /**
          * Cancel delay action.
          *
          * @details Cancels a deferred transaction.
          *
          * @param canceling_auth - the permission that authorizes this action,
          * @param trx_id - the deferred transaction id to be cancelled.
          */
         [[eosio::action]]
         void canceldelay( ignore<permission_level> canceling_auth, ignore<checksum256> trx_id ) {}

         /**
          * Set code action.
          *
          * @details Sets the contract code for an account.
          *
          * @param account - the account for which to set the contract code.
          * @param vmtype - reserved, set it to zero.
          * @param vmversion - reserved, set it to zero.
          * @param code - the code content to be set, in the form of a blob binary..
          */
         [[eosio::action]]
         void setcode( name account, uint8_t vmtype, uint8_t vmversion, const std::vector<char>& code ) {}

         /** @}*/

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
         void setabi( name account, const std::vector<char>& abi );

         /**
          * On error action.
          *
          * @details Notification of this action is delivered to the sender of a deferred transaction
          * when an objective error occurs while executing the deferred transaction.
          * This action is not meant to be called directly.
          *
          * @param sender_id - the id for the deferred transaction chosen by the sender,
          * @param sent_trx - the deferred transaction that failed.
          */
         [[eosio::action]]
         void onerror( ignore<uint128_t> sender_id, ignore<std::vector<char>> sent_trx );

         /**
          * Set privilege status for an account.
          *
          * @details Allows to set privilege status for an account (turn it on/off).
          * @param account - the account to set the privileged status for.
          * @param is_priv - 0 for false, > 0 for true.
          */
         [[eosio::action]]
         void setpriv( name account, uint8_t is_priv );

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
         void setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight );

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
         void setprods( std::vector<eosio::producer_key> schedule );

         /**
          * Set the blockchain parameters
          *
          * @details Set the blockchain parameters. By tuning these parameters, various degrees of customization can be achieved.
          *
          * @param params - New blockchain parameters to set
          */
         [[eosio::action]]
         void setparams( const eosio::blockchain_parameters& params );

         /**
          * Check if an account has authorization to access current action.
          *
          * @details Checks if the account name `from` passed in as param has authorization to access
          * current action, that is, if it is listed in the action’s allowed permissions vector.
          *
          * @param from - the account name to authorize
          */
         [[eosio::action]]
         void reqauth( name from );

         /**
          * Activates a protocol feature.
          *
          * @details Activates a protocol feature
          *
          * @param feature_digest - hash of the protocol feature to activate.
          */
         [[eosio::action]]
         void activate( const eosio::checksum256& feature_digest );

         /**
          * Asserts that a protocol feature has been activated.
          *
          * @details Asserts that a protocol feature has been activated
          *
          * @param feature_digest - hash of the protocol feature to check for activation.
          */
         [[eosio::action]]
         void reqactivated( const eosio::checksum256& feature_digest );

         struct [[eosio::table]] abi_hash {
            name              owner;
            checksum256       hash;
            uint64_t primary_key()const { return owner.value; }

            EOSLIB_SERIALIZE( abi_hash, (owner)(hash) )
         };

         typedef eosio::multi_index< "abihash"_n, abi_hash > abi_hash_table;

         using newaccount_action = action_wrapper<"newaccount"_n, &bios::newaccount>;
         using updateauth_action = action_wrapper<"updateauth"_n, &bios::updateauth>;
         using deleteauth_action = action_wrapper<"deleteauth"_n, &bios::deleteauth>;
         using linkauth_action = action_wrapper<"linkauth"_n, &bios::linkauth>;
         using unlinkauth_action = action_wrapper<"unlinkauth"_n, &bios::unlinkauth>;
         using canceldelay_action = action_wrapper<"canceldelay"_n, &bios::canceldelay>;
         using setcode_action = action_wrapper<"setcode"_n, &bios::setcode>;
         using setabi_action = action_wrapper<"setabi"_n, &bios::setabi>;
         using setpriv_action = action_wrapper<"setpriv"_n, &bios::setpriv>;
         using setalimits_action = action_wrapper<"setalimits"_n, &bios::setalimits>;
         using setprods_action = action_wrapper<"setprods"_n, &bios::setprods>;
         using setparams_action = action_wrapper<"setparams"_n, &bios::setparams>;
         using reqauth_action = action_wrapper<"reqauth"_n, &bios::reqauth>;
         using activate_action = action_wrapper<"activate"_n, &bios::activate>;
         using reqactivated_action = action_wrapper<"reqactivated"_n, &bios::reqactivated>;
   };
}
