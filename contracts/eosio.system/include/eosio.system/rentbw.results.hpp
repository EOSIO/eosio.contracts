#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/name.hpp>

using eosio::action_wrapper;
using eosio::asset;
using eosio::name;

/**
 * The actions `buyresult`, `sellresult`, `rentresult`, and `orderresult` of `rex.results` are all no-ops.
 * They are added as inline convenience actions to `rentnet`, `rentcpu`, `buyrex`, `unstaketorex`, and `sellrex`.
 * An inline convenience action does not have any effect, however,
 * its data includes the result of the parent action and appears in its trace.
 */
class [[eosio::contract("rentbw.results")]] rentbw_results : eosio::contract {
   public:

      using eosio::contract::contract;

      /**
       * Rentbwresult action.
       *
       * @param fee        - rental fee amount
       * @param rented_net - amount of rented NET tokens
       * @param rented_cpu - amount of rented CPU tokens
       */
      [[eosio::action]]
      void rentbwresult( const asset& fee, const asset& rented_net, const asset& rented_cpu );

      using rentbwresult_action  = action_wrapper<"rentbwresult"_n,  &rentbw_results::rentbwresult>;
};
