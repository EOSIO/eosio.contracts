/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/common.hpp>

namespace eosiosystem {

   SYSTEM_CONTRACT name_auction_tables {
   public:
      using eosio::name;
      using eosio::time_point;
      using eosio::asset;

      TABLE name_bid {
         static constexpr eosio::name table_name{"namebids"};

         name            newname;
         name            high_bidder;
         int64_t         high_bid = 0; ///< negative high_bid == closed auction waiting to be claimed
         time_point      last_bid_time;

         uint64_t primary_key()const { return newname.value;                    }
         uint64_t by_high_bid()const { return static_cast<uint64_t>(-high_bid); }
      };

      using name_bid_table =  eosio::multi_index< name_bid::table_name, name_bid,
                                 indexed_by<"highbid"_n, const_mem_fun<name_bid, uint64_t, &name_bid::by_high_bid>  >
                              > name_bid_table;


      TABLE bid_refund {
         static constexpr eosio::name table_name{"bidrefunds"};

         name         bidder;
         asset        amount;

         uint64_t primary_key()const { return bidder.value; }
      };

      using bid_refund_table =  eosio::multi_index< bid_refund::table_name, bid_refund >;


      using tables = eosio::module::tables<
                        name_bid_table,
                        bid_refund_table
                     >;
   };

} /// namespace eosiosystem
