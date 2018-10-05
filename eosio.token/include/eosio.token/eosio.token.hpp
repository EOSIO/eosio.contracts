/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class token : public contract {
      public:
         token( name self ):contract(self){}

         void create( name   issuer,
                      asset  maximum_supply);

         void issue( name to, asset quantity, string memo );

         void retire( asset quantity, string memo );

         void transfer( name    from,
                        name    to,
                        asset   quantity,
                        string  memo );

         void open( name owner, const symbol& symbol, name payer );

         void close( name owner, const symbol& symbol );

         inline asset get_supply( symbol_code sym_code )const;

         inline asset get_balance( name owner, symbol_code sym_code )const;

      private:
         struct account {
            asset    balance;

            uint64_t primary_key()const { return balance.symbol.code().raw(); }
         };

         struct currency_stats {
            asset    supply;
            asset    max_supply;
            name     issuer;

            uint64_t primary_key()const { return supply.symbol.code().raw(); }
         };

         typedef eosio::multi_index< "accounts"_n, account > accounts;
         typedef eosio::multi_index< "stat"_n, currency_stats > stats;

         void sub_balance( name owner, asset value );
         void add_balance( name owner, asset value, name ram_payer );

      public:
         struct transfer_args {
            name     from;
            name     to;
            asset    quantity;
            string   memo;
         };
   };

   asset token::get_supply( symbol_code sym_code )const
   {
      stats statstable( _self, sym_code.raw() );
      const auto& st = statstable.get( sym_code.raw() );
      return st.supply;
   }

   asset token::get_balance( name owner, symbol_code sym_code )const
   {
      accounts accountstable( _self, owner.value );
      const auto& ac = accountstable.get( sym_code.raw() );
      return ac.balance;
   }

} /// namespace eosio
