/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/name_auction_subcontract.hpp>
#include <eosio.system/core_module.hpp>

namespace eosiosystem {

   void name_auction_subcontract::bidname( name bidder, name newname, asset bid ) {
      using name_auction_module::names_account;

      require_auth( bidder );
      eosio_assert( newname.suffix() == newname, "you can only bid on top-level suffix" );

      eosio_assert( (bool)newname, "the empty name is not a valid account name to bid on" );
      eosio_assert( (newname.value & 0xFull) == 0, "13 character names are not valid account names to bid on" );
      eosio_assert( (newname.value & 0x1F0ull) == 0, "accounts with 12 character names and no dots can be created without bidding required" );
      eosio_assert( !is_account( newname ), "account already exists" );

      auto cm = _mm.get_module<core_module>();

      eosio_assert( bid.symbol == cm.core_symbol(), "asset must be system token" );
      eosio_assert( bid.amount > 0, "insufficient bid" );

      INLINE_ACTION_SENDER(eosio::token, transfer)(
         token_account, { {bidder, active_permission} },
         { bidder, names_account, bid, std::string("bid name ")+ newname.to_string() }
      );

      auto& bids = get_table<name_bid_table>();
      //print( name{bidder}, " bid ", bid, " on ", name{newname}, "\n" );
      auto current = bids.find( newname.value );
      if( current == bids.end() ) {
         bids.emplace( bidder, [&]( auto& b ) {
            b.newname = newname;
            b.high_bidder = bidder;
            b.high_bid = bid.amount;
            b.last_bid_time = cm.current_time_point();
         });
      } else {
         eosio_assert( current->high_bid > 0, "this auction has already closed" );
         eosio_assert( bid.amount - current->high_bid > (current->high_bid / 10), "must increase bid by 10%" );
         eosio_assert( current->high_bidder != bidder, "account is already highest bidder" );

         auto& brt = get_table<bid_refund_table>( newname.value );

         auto it = brt.find( current->high_bidder.value );
         if ( it != brt.end() ) {
            brt.modify( it, same_payer, [&](auto& r) {
               r.amount += asset( current->high_bid, cm.core_symbol() );
            });
         } else {
            brt.emplace( bidder, [&](auto& r) {
               r.bidder = current->high_bidder;
               r.amount = asset( current->high_bid, cm.core_symbol() );
            });
         }

         transaction t;
         t.actions.emplace_back( permission_level{_self, active_permission},
                                 _self, "bidrefund"_n,
                                 std::make_tuple( current->high_bidder, newname )
         );
         t.delay_sec = 0;
         uint128_t deferred_id = (uint128_t(newname.value) << 64) | current->high_bidder.value;
         cancel_deferred( deferred_id );
         t.send( deferred_id, bidder );

         bids.modify( current, bidder, [&]( auto& b ) {
            b.high_bidder = bidder;
            b.high_bid = bid.amount;
            b.last_bid_time = cm.current_time_point();
         });
      }
   }

   void name_auction_subcontract::bidrefund( name bidder, name newname ) {
      using name_auction_module::names_account;

      auto& brt = _module.get_table<bid_refund_table>( newname.value );
      auto itr = brt.find( bidder.value );
      eosio_assert( itr != brt.end(), "refund not found" );

      INLINE_ACTION_SENDER(eosio::token, transfer)(
         token_account, { {names_account, active_permission}, {bidder, active_permission} },
         { names_account, bidder, asset(itr->amount), std::string("refund bid on name ")+(name{newname}).to_string() }
      );
      brt.erase( itr );
   }

} /// namespace eosiosystem
