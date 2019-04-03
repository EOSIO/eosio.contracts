#pragma once

#include <eosiolib/asset.hpp>

namespace eosiosystem {
   using eosio::asset;
   using eosio::symbol;

   /**
    *  Uses Bancor math to create a 50/50 relay between two asset types. The state of the
    *  bancor exchange is entirely contained within this struct. There are no external
    *  side effects associated with using this API.
    */
   struct [[eosio::table, eosio::contract("eosio.system")]] exchange_state {
      asset    supply;

      struct connector {
         asset balance;
         double weight = .5;

         EOSLIB_SERIALIZE( connector, (balance)(weight) )
      };

      connector base;
      connector quote;

      uint64_t primary_key()const { return supply.symbol.raw(); }

      asset convert_to_exchange( connector& c, const asset& in );
      asset convert_from_exchange( connector& c, const asset& in );
      asset convert( const asset& from, const symbol& to );
      asset direct_convert( const asset& from, const symbol& to );
      static asset get_direct_bancor_output( const asset& inp_reserve,
                                             const asset& out_reserve,
                                             const asset& inp );

      EOSLIB_SERIALIZE( exchange_state, (supply)(base)(quote) )
   };

   typedef eosio::multi_index< "rammarket"_n, exchange_state > rammarket;

} /// namespace eosiosystem
