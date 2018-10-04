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

         void create( account_name issuer,
                      asset        maximum_supply);

         void issue( account_name to, asset quantity, string memo );

         void retire( asset quantity, string memo );

         void transfer( account_name from,
                        account_name to,
                        asset        quantity,
                        string       memo );

         void open( account_name owner, const symbol& symbol, account_name payer );

         void close( account_name owner, const symbol& symbol );

         inline asset get_supply( const symbol& sym )const;

         inline asset get_balance( account_name owner, symbol sym )const;

      private:
         struct account {
            asset    balance;

            uint64_t primary_key()const { return balance.symbol.raw(); }
         };

         struct currency_stats {
            asset          supply;
            asset          max_supply;
            account_name   issuer;

            uint64_t primary_key()const { return supply.symbol.raw(); }
         };

         typedef eosio::multi_index< "accounts"_n, account > accounts;
         typedef eosio::multi_index< "stat"_n, currency_stats > stats;

         void sub_balance( account_name owner, asset value );
         void add_balance( account_name owner, asset value, account_name ram_payer );

      public:
         struct transfer_args {
            account_name  from;
            account_name  to;
            asset         quantity;
            string        memo;
         };
   };

   asset token::get_supply( const symbol& sym )const
   {
      stats statstable( _self, sym.raw() );
      const auto& st = statstable.get( sym.raw() );
      return st.supply;
   }

   asset token::get_balance( account_name owner, symbol sym )const
   {
      accounts accountstable( _self, owner );
      const auto& ac = accountstable.get( sym.raw() );
      eosio::print(sym);
      eosio::print(sym.raw());
      return ac.balance;
   }

} /// namespace eosio
