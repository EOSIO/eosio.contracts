/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/common.hpp>

namespace eosiosystem {

   SYSTEM_CONTRACT core_tables {
   public:
      using eosio::block_timestamp;
      using eosio::time_point;
      using eosio::name;
      using eosio::asset;

      TABLE eosio_global_state : public eosio::blockchain_parameters {
         static constexpr eosio::name table_name{"global"};

         uint64_t             max_ram_size = 64ll*1024 * 1024 * 1024;
         uint64_t             total_ram_bytes_reserved = 0;
         int64_t              total_ram_stake = 0;

         block_timestamp      last_producer_schedule_update;
         time_point           last_pervote_bucket_fill;
         int64_t              pervote_bucket = 0;
         int64_t              perblock_bucket = 0;
         uint32_t             total_unpaid_blocks = 0; /// all blocks which have been produced but not paid
         int64_t              total_activated_stake = 0;
         time_point           thresh_activated_stake_time;
         uint16_t             last_producer_schedule_size = 0;
         double               total_producer_vote_weight = 0; /// the sum of all producer votes
         block_timestamp      last_name_close;

         EOSLIB_SERIALIZE_DERIVED( eosio_global_state, eosio::blockchain_parameters,
                                   (max_ram_size)(total_ram_bytes_reserved)(total_ram_stake)
                                   (last_producer_schedule_update)(last_pervote_bucket_fill)
                                   (pervote_bucket)(perblock_bucket)(total_unpaid_blocks)
                                   (total_activated_stake)(thresh_activated_stake_time)
                                   (last_producer_schedule_size)(total_producer_vote_weight)(last_name_close) )
      };

      class global_singleton : public eosio::lazy_singleton< eosio_global_state, system_account >
      {
         eosio_global_state_lazy_singleton( eosio::name code, uint64_t scope )
         :lazy_singleton( name code, uint64_t scope )
         {
            if( _dirty ) {
               // singleton does not exist in persistent state, so *_cache was default initialized
               get_blockchain_parameters(*_cache);
               // keep _dirty as true
            }
         }
      }


      /**
       * Defines new global state parameters added after version 1.0
       */
      TABLE eosio_global_state2 {
         static constexpr eosio::name table_name{"global2"};

         uint16_t          new_ram_per_block = 0;
         block_timestamp   last_ram_increase;
         block_timestamp   last_block_num; /* deprecated */
         double            total_producer_votepay_share = 0;
         uint8_t           revision = 0; ///< used to track version updates in the future.

         EOSLIB_SERIALIZE( eosio_global_state2, (new_ram_per_block)(last_ram_increase)(last_block_num)
                                                (total_producer_votepay_share)(revision) )
      };

      using global2_singleton = eosio::lazy_singleton< eosio_global_state2, system_account >;


      TABLE eosio_global_state3 {
         static constexpr eosio::name table_name{"global3"};

         time_point        last_vpay_state_update;
         double            total_vpay_share_change_rate = 0;

         EOSLIB_SERIALIZE( eosio_global_state3, (last_vpay_state_update)(total_vpay_share_change_rate) )
      };

      using global3_singleton = eosio::lazy_singleton< eosio_global_state3, system_account >;


      TABLE abi_hash {
         static constexpr eosio::name table_name{"abihash"};

         name              owner;
         capi_checksum256  hash;

         uint64_t primary_key()const { return owner.value; }

         EOSLIB_SERIALIZE( abi_hash, (owner)(hash) )
      };

      using abi_hash_table = eosio::multi_index< abi_hash::table_name, abi_hash >;


      TABLE user_resources {
         static constexpr eosio::name table_name{"userres"};

         name          owner;
         asset         net_weight;
         asset         cpu_weight;
         int64_t       ram_bytes = 0;

         uint64_t primary_key()const { return owner.value; }

         EOSLIB_SERIALIZE( user_resources, (owner)(net_weight)(cpu_weight)(ram_bytes) )
      };

      using user_resources_table = eosio::multi_index< user_resources::table_name, user_resources >;


      using tables = eosio::module::tables<
                        global1_singleton,
                        global2_singleton,
                        global3_singleton,
                        abi_hash_table,
                        user_resources_table
                     >;
   };

} /// namespace eosiosystem
