/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/name_auction_module.hpp>

namespace eosiosystem {

   void name_auction_module::assert_and_remove_winning_bid( eosio::name new_account, eosio::name highest_bidder ) {
      auto& nbt = get_table<name_bid_table>()
      auto winning_bid = nbt.find( new_account.value );
      eosio_assert( winning_bid != nbt.end(), "no active bid for name" );
      eosio_assert( winning_bid->high_bid < 0, "auction for name is not closed yet" );
      eosio_assert( winning_bid->high_bidder == highest_bidder, "only highest bidder can claim" );
      nbt.erase( winning_bid );
   }


} /// namespace eosiosystem
