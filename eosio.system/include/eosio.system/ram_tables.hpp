/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/common.hpp>

namespace eosiosystem {

   SYSTEM_CONTRACT ram_tables {
   public:
      using eosio::asset;
      using eosio::symbol;

      using real_type = double;

      /**
       *  Uses Bancor math to create a 50/50 relay between two asset types. The state of the
       *  bancor exchange is entirely contained within this struct. There are no external
       *  side effects associated with using this API.
       */
      TABLE exchange_state {
         static constexpr eosio::name table_name{"rammarket"};

         asset    supply;

         struct connector {
            asset balance;
            double weight = .5;

            EOSLIB_SERIALIZE( connector, (balance)(weight) )
         };

         connector base;
         connector quote;

         uint64_t primary_key()const { return supply.symbol.raw(); }

         asset convert_to_exchange( connector& c, asset in );
         asset convert_from_exchange( connector& c, asset in );
         asset convert( asset from, const symbol& to );

         EOSLIB_SERIALIZE( exchange_state, (supply)(base)(quote) )
      };

      using rammarket = eosio::multi_index< exchange_state::table_name, exchange_state >;


      using tables = eosio::module::tables<rammarket>;
   };

} /// namespace eosiosystem
