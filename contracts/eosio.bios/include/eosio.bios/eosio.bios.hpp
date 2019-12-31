#pragma once

#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio/eosio.hpp>
#include <eosio/fixed_bytes.hpp>
#include <eosio/privileged.hpp>
#include <eosio/producer_schedule.hpp>

namespace eosiobios {

   using eosio::action_wrapper;
   using eosio::check;
   using eosio::checksum256;
   using eosio::ignore;
   using eosio::name;
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

   /**
    * The `eosio.bios` is the first sample of system contract provided by `block.one` through the EOSIO platform. It is a minimalist system contract because it only supplies the actions that are absolutely critical to bootstrap a chain and nothing more. This allows for a chain agnostic approach to bootstrapping a chain.
    * 
    * Just like in the `eosio.system` sample contract implementation, there are a few actions which are not implemented at the contract level (`newaccount`, `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, `canceldelay`, `onerror`, `setabi`, `setcode`), they are just declared in the contract so they will show in the contract's ABI and users will be able to push those actions to the chain via the account holding the `eosio.system` contract, but the implementation is at the EOSIO core level. They are referred to as EOSIO native actions.
    */
   class [[eosio::contract("eosio.bios")]] bios : public eosio::contract {
      public:
         using contract::contract;
         /**
          * \details New account action, it is called after a new account is created. This code enforces resource-limits rules
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
         [[eosio::action]] void newaccount(  name             creator,
                                             name             name,
                                             ignore<authority> owner,
                                             ignore<authority> active){}
         /**
          * \details Updates permission for an account.
          *
          * \param account The account for which the permission is updated,
          * \param permission The permission name which is updated,
          * \param parent The parent of the permission which is updated,
          * \param auth The json describing the permission authorization.
          */
         [[eosio::action]] void updateauth(  ignore<name>  account,
                                             ignore<name>  permission,
                                             ignore<name>  parent,
                                             ignore<authority> auth ) {}

         /**
          * \details Deletes the authorization for an account's permission.
          *
          * \param account The account for which the permission authorization is deleted,
          * \param permission The permission name been deleted.
          */
         [[eosio::action]] void deleteauth(  ignore<name>  account,
                                             ignore<name>  permission ) {}

         /**
          * \details Assigns a specific action from a contract to a permission you have created. Five system
          * actions can not be linked `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, and `canceldelay`.
          * This is useful because when doing authorization checks, the EOSIO based blockchain starts with the
          * action needed to be authorized (and the contract belonging to), and looks up which permission
          * is needed to pass authorization validation. If a link is set, that permission is used for authoraization
          * validation otherwise then active is the default, with the exception of `eosio.any`.
          * `eosio.any` is an implicit permission which exists on every account; you can link actions to `eosio.any`
          * and that will make it so linked actions are accessible to any permissions defined for the account.
          *
          * \param account The permission's owner to be linked and the payer of the RAM needed to store this link,
          * \param code The owner of the action to be linked,
          * \param type The action to be linked,
          * \param requirement The permission to be linked.
          */
         [[eosio::action]] void linkauth( ignore<name>    account,
                                          ignore<name>    code,
                                          ignore<name>    type,
                                          ignore<name>    requirement  ) {}

         /**
          * \details It's doing the reverse of linkauth action, by unlinking the given action.
          *
          * \param account The owner of the permission to be unlinked and the receiver of the freed RAM,
          * \param code The owner of the action to be unlinked,
          * \param type The action to be unlinked.
          */
         [[eosio::action]] void unlinkauth(  ignore<name>  account,
                                             ignore<name>  code,
                                             ignore<name>  type ) {}

         /**
          * \details Cancels a deferred transaction.
          *
          * \param canceling_auth The permission that authorizes this action,
          * \param trx_id The deferred transaction id to be cancelled.
          */
         [[eosio::action]] void canceldelay( ignore<permission_level> canceling_auth, ignore<checksum256> trx_id ) {}

         /**
          * \details Sets the contract code for an account.
          *
          * \param account The account for which to set the contract code.
          * \param vmtype Reserved, set it to zero.
          * \param vmversion Reserved, set it to zero.
          * \param code The code content to be set, in the form of a blob binary..
          */
         [[eosio::action]] void setcode( name account, uint8_t vmtype, uint8_t vmversion, const std::vector<char>& code ) {}

         /**
          * \details Set the abi for contract identified by `account` name. Creates an entry in the abi_hash_table
          * index, with `account` name as key, if it is not already present and sets its value with the abi hash.
          * Otherwise it is updating the current abi hash value for the existing `account` key.
          *
          * \param account The name of the account to set the abi for
          * \param abi     The abi hash represented as a vector of characters
          */
         [[eosio::action]] void setabi( name account, const std::vector<char>& abi );

         /**
          * \details Notification of this action is delivered to the sender of a deferred transaction
          * when an objective error occurs while executing the deferred transaction.
          * This action is not meant to be called directly.
          *
          * \param sender_id The id for the deferred transaction chosen by the sender,
          * \param sent_trx The deferred transaction that failed.
          */
         [[eosio::action]] void onerror( ignore<uint128_t> sender_id, ignore<std::vector<char>> sent_trx );

         /**
          * \details Allows to set privilege status for an account (turn it on/off).
          * \param account The account to set the privileged status for.
          * \param is_priv 0 for false, > 0 for true.
          */
         [[eosio::action]] void setpriv( name account, uint8_t is_priv );

         /**
          * \details Set the resource limits of an account
          *
          * \param account The name of the account whose resource limit to be set
          * \param ram_bytes The ram limit in absolute bytes
          * \param net_weight The fractionally proportionate net limit of available resources based on (weight / total_weight_of_all_accounts)
          * \param cpu_weight The fractionally proportionate cpu limit of available resources based on (weight / total_weight_of_all_accounts)
          */
         [[eosio::action]] void setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight );

         /**
          * \details Set a new list of active producers, by proposing a schedule change, once the block that
          * contains the proposal becomes irreversible, the schedule is promoted to "pending"
          * automatically. Once the block that promotes the schedule is irreversible, the schedule will
          * become "active".
          *
          * \param schedule The new list of active producers to set
          */
         [[eosio::action]] void setprods( const std::vector<eosio::producer_authority>& schedule );

         /**
          * \details Set the blockchain parameters. By tuning these parameters, various degrees of customization can be achieved.
          *
          * \param params The new blockchain parameters to set
          */
         [[eosio::action]] void setparams( const eosio::blockchain_parameters& params );

         /**
          * \details Checks if the account name `from` passed in as param has authorization to access
          * current action, that is, if it is listed in the action’s allowed permissions vector.
          *
          * \param from The account name to authorize
          */
         [[eosio::action]] void reqauth( name from );

         /**
          * \details Activates a protocol feature
          *
          * \param feature_digest The hash of the protocol feature to activate.
          */
         [[eosio::action]]void activate( const eosio::checksum256& feature_digest );

         /**
          * \details Asserts that a protocol feature has been activated
          *
          * \param feature_digest The hash of the protocol feature to check for activation.
          */
         [[eosio::action]] void reqactivated( const eosio::checksum256& feature_digest );

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
