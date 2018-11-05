/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/aggregated_tables.hpp>

namespace eosiosystem {

   class name_auction_module : public eosio::module::module_base<contract_modules, name_auction_tables>
   {
   public:
      using module_base_type::module_base_type;

      static constexpr eosio::name names_account{"eosio.names"};

      // Helper methods needed for modules and sub-contracts within this contract:

      void assert_and_remove_winning_bid( eosio::name new_account, eosio::name highest_bidder );

   };

} /// namespace eosiosystem
