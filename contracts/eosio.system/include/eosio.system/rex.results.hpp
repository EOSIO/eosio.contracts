#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/name.hpp>
#include <eosiolib/asset.hpp>

using eosio::name;
using eosio::asset;

class [[eosio::contract("rex.results")]] rex_results {
   public:
      [[eosio::action]]
      void buyresult( const asset& rex_received );
      
      [[eosio::action]]
      void sellresult( const asset& proceeds );
   
      [[eosio::action]]
      void orderresult( const name& owner, const asset& proceeds );
   
      using buyresult_action   = eosio::action_wrapper<"buyresult"_n, &rex_results::buyresult>;
      using sellresult_action  = eosio::action_wrapper<"sellresult"_n, &rex_results::sellresult>;
      using orderresult_action = eosio::action_wrapper<"orderresult"_n, &rex_results::orderresult>;
};
