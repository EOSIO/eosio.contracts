#include <eosio.system/eosio.system.hpp>

#include <eosio.token/eosio.token.hpp>

namespace eosiosystem {

   const int64_t  min_pervote_daily_pay = 100'0000;
   const int64_t  min_activated_stake   = 150'000'000'0000;
   const double   continuous_rate       = 0.04879;          // 5% annual rate
   const double   perblock_rate         = 0.0025;           // 0.25%
   const double   standby_rate          = 0.0075;           // 0.75%
   const uint32_t blocks_per_year       = 52*7*24*2*3600;   // half seconds per year
   const uint32_t seconds_per_year      = 52*7*24*3600;
   const uint32_t blocks_per_day        = 2 * 24 * 3600;
   const uint32_t blocks_per_hour       = 2 * 3600;
   const uint64_t useconds_per_day      = 24 * 3600 * uint64_t(1000000);
   const uint64_t useconds_per_year     = seconds_per_year*1000000ll;


   void system_contract::onblock( block_timestamp timestamp, account_name producer ) {
      using namespace eosio;

      require_auth(N(eosio));

      // _gstate2.last_block_num is not used anywhere in the system contract code anymore.
      // Although this field is deprecated, we will continue updating it for now until the last_block_num field
      // is eventually completely removed, at which point this line can be removed.
      _gstate2.last_block_num = timestamp;

      /** until activated stake crosses this threshold no new rewards are paid */
      if( _gstate.total_activated_stake < min_activated_stake )
         return;

      if( _gstate.last_pervote_bucket_fill == 0 )  /// start the presses
         _gstate.last_pervote_bucket_fill = current_time();


      /**
       * At startup the initial producer may not be one that is registered / elected
       * and therefore there may be no producer object for them.
       */
      auto prod = _producers.find(producer);
      if ( prod != _producers.end() ) {
         _gstate.total_unpaid_blocks++;
         _producers.modify( prod, 0, [&](auto& p ) {
               p.unpaid_blocks++;
         });
      }

      /// only update block producers once every minute, block_timestamp is in half seconds
      if( timestamp.slot - _gstate.last_producer_schedule_update.slot > 120 ) {
         update_elected_producers( timestamp );

         if( (timestamp.slot - _gstate.last_name_close.slot) > blocks_per_day ) {
            name_bid_table bids(_self,_self);
            auto idx = bids.get_index<N(highbid)>();
            auto highest = idx.lower_bound( std::numeric_limits<uint64_t>::max()/2 );
            if( highest != idx.end() &&
                highest->high_bid > 0 &&
                highest->last_bid_time < (current_time() - useconds_per_day) &&
                _gstate.thresh_activated_stake_time > 0 &&
                (current_time() - _gstate.thresh_activated_stake_time) > 14 * useconds_per_day ) {
                   _gstate.last_name_close = timestamp;
                   idx.modify( highest, 0, [&]( auto& b ){
                         b.high_bid = -b.high_bid;
               });
            }
         }
      }
   }

   using namespace eosio;
   void system_contract::claimrewards( const account_name& owner ) {
      require_auth( owner );

      const auto& prod = _producers.get( owner );
      eosio_assert( prod.active(), "producer does not have an active key" );

      eosio_assert( _gstate.total_activated_stake >= min_activated_stake,
                    "cannot claim rewards until the chain is activated (at least 15% of all tokens participate in voting)" );

      const auto ct = current_time();

      eosio_assert( ct - prod.last_claim_time > useconds_per_day, "already claimed rewards within past day" );

      const asset token_supply   = token( N(eosio.token)).get_supply(symbol_type(system_token_symbol).name() );
      const auto usecs_since_last_fill = ct - _gstate.last_pervote_bucket_fill;

      if( usecs_since_last_fill > 0 && _gstate.last_pervote_bucket_fill > 0 ) {
         auto new_tokens = static_cast<int64_t>( (continuous_rate * double(token_supply.amount) * double(usecs_since_last_fill)) / double(useconds_per_year) );

         auto to_producers     = new_tokens / 5;
         auto to_savings       = new_tokens - to_producers;
         auto to_per_block_pay = to_producers / 4;
         auto to_per_vote_pay  = to_producers - to_per_block_pay;

         INLINE_ACTION_SENDER(eosio::token, issue)( N(eosio.token), {{N(eosio),N(active)}},
                                                    { N(eosio), asset(new_tokens), std::string("issue tokens for producer pay and savings") } );

         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {N(eosio),N(active)},
                                                       { N(eosio), N(eosio.saving), asset(to_savings), "unallocated inflation" } );

         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {N(eosio),N(active)},
                                                       { N(eosio), N(eosio.bpay), asset(to_per_block_pay), "fund per-block bucket" } );

         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {N(eosio),N(active)},
                                                       { N(eosio), N(eosio.vpay), asset(to_per_vote_pay), "fund per-vote bucket" } );

         _gstate.pervote_bucket          += to_per_vote_pay;
         _gstate.perblock_bucket         += to_per_block_pay;
         _gstate.last_pervote_bucket_fill = ct;
      }

      auto prod2 = _producers2.find( owner );
      if ( prod2 == _producers2.end() ) {
         prod2 = _producers2.emplace( owner, [&]( producer_info2& info  ) {
            info.owner                     = owner;
            info.last_votepay_share_update = ct;
         });
      }

      int64_t producer_per_block_pay = 0;
      if( _gstate.total_unpaid_blocks > 0 ) {
         producer_per_block_pay = (_gstate.perblock_bucket * prod.unpaid_blocks) / _gstate.total_unpaid_blocks;
      }

      /// New metric to be used in pervote pay calculation. Instead of vote weight ratio, we combine vote weight and
      /// time duration the vote weight has been held into one metric.
      const uint64_t last_claim_plus_3days = prod.last_claim_time + 3 * useconds_per_day;
      double delta_votepay_share       = 0;
      double delta_total_votepay_share = 0;
      double votepay_share             = 0;
      double total_votepay_share       = 0;
      
      if( ct < last_claim_plus_3days || ( ct >= last_claim_plus_3days && last_claim_plus_3days > prod2->last_votepay_share_update ) ) {
         delta_votepay_share       = prod.total_votes * double( (ct - prod2->last_votepay_share_update) / 1E6 );
         delta_total_votepay_share = _gstate3.total_vpay_share_change_rate * double( (ct - _gstate3.last_vpay_state_update) / 1E6) ;
         votepay_share             = prod2->votepay_share + delta_votepay_share;
         total_votepay_share       = _gstate2.total_producer_votepay_share + delta_total_votepay_share;
      }

      int64_t producer_per_vote_pay = 0;
      if( _gstate2.revision > 0 ) {
         if( total_votepay_share > 0 && ct < last_claim_plus_3days ) {
            producer_per_vote_pay = int64_t((votepay_share * _gstate.pervote_bucket) / total_votepay_share);
            if( producer_per_vote_pay > _gstate.pervote_bucket )
               producer_per_vote_pay = _gstate.pervote_bucket;
         }
      } else {
         if( _gstate.total_producer_vote_weight > 0 ) {
            producer_per_vote_pay = int64_t((_gstate.pervote_bucket * prod.total_votes) / _gstate.total_producer_vote_weight);
         }
      }

      if( producer_per_vote_pay < min_pervote_daily_pay ) {
         producer_per_vote_pay = 0;
      }
      
      _gstate.pervote_bucket      -= producer_per_vote_pay;
      _gstate.perblock_bucket     -= producer_per_block_pay;
      _gstate.total_unpaid_blocks -= prod.unpaid_blocks;

      if( ct >= last_claim_plus_3days && last_claim_plus_3days <= prod2->last_votepay_share_update ) { 
         _gstate3.total_vpay_share_change_rate += prod.total_votes;
      }

      _producers.modify( prod, 0, [&](auto& p) {
         p.last_claim_time = ct;
         p.unpaid_blocks   = 0;
      });

      _producers2.modify( prod2, 0, [&](auto& p) {
         _gstate2.total_producer_votepay_share += ( delta_total_votepay_share - p.votepay_share - delta_votepay_share );
         _gstate3.last_vpay_state_update        = ct;
         p.votepay_share                        = 0;
         p.last_votepay_share_update            = ct;
      });

      if( producer_per_block_pay > 0 ) {
         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {N(eosio.bpay),N(active)},
                                                       { N(eosio.bpay), owner, asset(producer_per_block_pay), std::string("producer block pay") } );
      }
      if( producer_per_vote_pay > 0 ) {
         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {N(eosio.vpay),N(active)},
                                                       { N(eosio.vpay), owner, asset(producer_per_vote_pay), std::string("producer vote pay") } );
      }
   }

} //namespace eosiosystem
