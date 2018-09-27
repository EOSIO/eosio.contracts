/**
 *  @copyright defined in eos/LICENSE.txt 
 */

#include <eosio.system/eosio.system.hpp>

namespace eosiosystem {

   /**
    * Transfers SYS tokens from user balance and credits converts them to REX stake.
    */
   void system_contract::lendrex( account_name from, asset amount ) {
      require_auth( from );

      INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {from,N(active)},
                                                    { from, N(eosio.rex), amount, "buy REX" } );

      asset rex_received( 0, S(4,REX) );

      auto itr = _rextable.begin();
      if( itr == _rextable.end() ) {
         _rextable.emplace( _self, [&]( auto& rp ){
            rex_received.amount = amount.amount * 10000;

            rp.total_lendable        = amount;
            rp.total_lent            = asset( 0, CORE_SYMBOL );
            rp.total_rent            = asset( 1000000, CORE_SYMBOL ); /// base amount prevents renting profitably until at least a minimum number of CORE_SYMBOL are made available
            rp.total_rex             = rex_received;
            rp.total_unlent.amount   = rp.total_lendable.amount - rp.total_lent.amount;
         });
      } else {
         const auto S0 = itr->total_lendable.amount;
         const auto S1 = S0 + amount.amount;
         const auto R0 = itr->total_rex.amount;
         const auto R1 = (uint128_t(S1) * R0) / S0;

         rex_received.amount = R1 - R0;

         _rextable.modify( itr, 0, [&]( auto& rp ) {
            rp.total_lendable.amount = S1;
            rp.total_rex.amount      = R1;
            rp.total_unlent.amount   = rp.total_lendable.amount - rp.total_lent.amount;
            eosio_assert( rp.total_unlent.amount >= 0, "programmer error, this should never go negative" );
         });
      }

      auto bitr = _rexbalance.find( from );
      if( bitr == _rexbalance.end() ) {
         _rexbalance.emplace( from, [&]( auto& rb ) {
            rb.owner       = from;
            rb.vote_stake  = amount;
            rb.rex_balance = rex_received;
         });
      } else {
         _rexbalance.modify( bitr, 0, [&]( auto& rb ) {
            rb.vote_stake.amount  += amount.amount;
            rb.rex_balance.amount += rex_received.amount;
         });
      }

      update_voting_power( from, amount );

      runrex(2);
   }

   /**
    * Converts REX stake back into SYS tokens at current exchange rate
    */
   void system_contract::unlendrex( account_name from, asset rex ) {
      runrex(2);

      require_auth( from );

      auto itr = _rextable.begin();
      eosio_assert( itr != _rextable.end(), "rex system not initialized yet" );

      auto bitr = _rexbalance.find( from );
      eosio_assert( bitr != _rexbalance.end(), "user must first lendrex" );
      eosio_assert( bitr->rex_balance.symbol == rex.symbol, "asset symbol must be (4, REX)" );
      eosio_assert( bitr->rex_balance >= rex, "insufficient funds" );

      auto result = close_rex_order( bitr, rex );
      if( std::get<0>(result) ) {
         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), { N(eosio.rex), N(active) },
                                                       { N(eosio.rex), from, asset( std::get<1>(result), CORE_SYMBOL ), "sell REX" } );
         update_voting_power( from, asset( -(std::get<2>(result)), CORE_SYMBOL ) );
      } else {
         rex_order_table rexorders( _self, _self );
         eosio_assert( rexorders.find( from ) == rexorders.end(), "an unlendrex request has already been scheduled");
         rexorders.emplace( from, [&]( auto& ordr ) {
            ordr.owner         = from;
            ordr.rex_requested = rex;
            ordr.unstake_quant = std::get<2>(result);
            ordr.order_time    = current_time_point();
         });
      }
   }

   void system_contract::cnclrexorder( account_name owner ) {
      require_auth( owner );
      rex_order_table rexorders( _self, _self );
      auto itr = rexorders.find( owner );
      eosio_assert( itr != rexorders.end(), "no unlendrex is scheduled" );
      eosio_assert( itr->is_open, "rex order has been closed and cannot be canceled" );
      rexorders.erase( itr );
   }

   void system_contract::claimrex( account_name owner ) {
      require_auth( owner );
      runrex(2);
      rex_order_table rexorders(_self, _self);
      auto itr = rexorders.find( owner );
      eosio_assert( itr != rexorders.end(), "no unlendrex is scheduled" );
      eosio_assert( !itr->is_open, "rex order has not been closed" );
      INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {N(eosio.rex),N(active)},
                                                    { N(eosio.rex), itr->owner, asset(itr->proceeds, CORE_SYMBOL), "claim REX proceeds" } );
      update_voting_power( owner, asset( -( itr->unstake_quant ), CORE_SYMBOL ) );
      rexorders.erase( itr );
   }

   /**
    * Given two connector balances (conin, and conout), and an incoming amount of
    * in, this function will modify conin and conout and return the delta out.
    *
    * @param in - same units as conin
    * @param conin - the input connector balance
    * @param conout - the output connector balance
    */
   int64_t bancor_convert( int64_t& conin, int64_t& conout, int64_t in ) {
      const double F0 = double(conin);
      const double T0 = double(conout);
      const double I  = double(in);

      auto out = int64_t((I*T0) / (I+F0));

      if( out < 0 ) out = 0;

      conin  += in;
      conout -= out;

      return out;
   }

   void system_contract::update_resource_limits( account_name receiver, int64_t delta_cpu, int64_t delta_net ) {
      user_resources_table   totals_tbl( _self, receiver );
      auto tot_itr = totals_tbl.find( receiver );
      eosio_assert( tot_itr !=  totals_tbl.end(), "expected to find resource table" );
      totals_tbl.modify( tot_itr, 0, [&]( auto& tot ) {
         tot.cpu_weight.amount    += delta_cpu;
         tot.net_weight.amount    += delta_net;
      });
      eosio_assert( asset(0) <= tot_itr->net_weight, "insufficient staked total net bandwidth" );
      eosio_assert( asset(0) <= tot_itr->cpu_weight, "insufficient staked total cpu bandwidth" );

      int64_t ram_bytes, net, cpu;
      get_resource_limits( receiver, &ram_bytes, &net, &cpu );
      set_resource_limits( receiver, ram_bytes, tot_itr->net_weight.amount, tot_itr->cpu_weight.amount );
   }

   /**
    * Uses payment to rent as many SYS tokens as possible and stake them for either cpu or net for the benefit of receiver,
    * after 30 days the rented SYS delegation of CPU or NET will expire.
    */
   void system_contract::rent( account_name from, account_name receiver, asset payment, bool cpu  ) {
      require_auth( from );

      runrex(2);

      INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {from,N(active)},
                                                    { from, N(eosio.rex), payment, string("rent ") + (cpu ? "CPU" : "NET") } );

      auto itr = _rextable.begin();
      eosio_assert( itr != _rextable.end(), "rex system not initialized yet" );

      int64_t rented_tokens = 0;
      _rextable.modify( itr, 0, [&]( auto& rt ) {
         rented_tokens = bancor_convert( rt.total_rent.amount, rt.total_unlent.amount, payment.amount );
         rt.total_lent.amount    += rented_tokens;
         rt.total_unlent.amount  += payment.amount;
         rt.total_lendable.amount = rt.total_unlent.amount + rt.total_lent.amount;
         rt.loan_num++;
      });

      if( cpu ) {
         rex_cpu_loan_table cpu_loans(_self,_self);

         cpu_loans.emplace( from, [&]( auto& c ) {
            c.receiver     = receiver;
            c.total_staked = asset( rented_tokens, CORE_SYMBOL );
            c.expiration   = eosio::time_point( eosio::microseconds(current_time() + eosio::days(30).count()) );
            c.loan_num     = itr->loan_num;
         });
         update_resource_limits( receiver, rented_tokens, 0 );
      } else {
         rex_net_loan_table net_loans(_self,_self);
         
         net_loans.emplace( from, [&]( auto& c ) {
            c.receiver     = receiver;
            c.total_staked = asset( rented_tokens, CORE_SYMBOL );
            c.expiration   = eosio::time_point( eosio::microseconds(current_time() + eosio::days(30).count()) );
            c.loan_num     = itr->loan_num;
         });
         update_resource_limits( receiver, 0, rented_tokens );
      }
   }

   /**
    * Perform maitenance operations on expired rex
    */
   void system_contract::runrex( uint16_t max ) {
      auto rexi = _rextable.begin();
      eosio_assert( rexi != _rextable.end(), "rex system not initialized yet" );

      auto unrent = [&]( int64_t rented_tokens )  {
         _rextable.modify( rexi, 0, [&]( auto& rt ) {
            auto fee = bancor_convert( rt.total_unlent.amount, rt.total_rent.amount, rented_tokens );
            rt.total_lent.amount    -= rented_tokens;
            rt.total_lendable.amount = rt.total_unlent.amount + rt.total_lent.amount;
         });
      };

      rex_cpu_loan_table cpu_loans( _self, _self );
      for( uint16_t i = 0; i < max; ++i ) {
         auto itr = cpu_loans.begin();
         if( itr == cpu_loans.end() ) break;
         if( itr->expiration.elapsed.count() > current_time() ) break;

         update_resource_limits( itr->receiver, -itr->total_staked.amount, 0 );
         unrent( itr->total_staked.amount );
         cpu_loans.erase( itr );
      }

      rex_net_loan_table net_loans( _self, _self );
      for( uint16_t i = 0; i < max; ++i ) {
         auto itr = net_loans.begin();
         if( itr == net_loans.end() ) break;
         if( itr->expiration.elapsed.count() > current_time() ) break;

         update_resource_limits( itr->receiver, 0, -itr->total_staked.amount );
         unrent( itr->total_staked.amount );
         net_loans.erase( itr );
      }

      rex_order_table rexorders( _self, _self );
      auto idx = rexorders.get_index<N(bytime)>();
      auto oitr = idx.begin();
      for( uint16_t i = 0; i < max; ++i ) {
         if( oitr == idx.end() || !oitr->is_open ) break;
         auto bitr = _rexbalance.find( oitr->owner );
         // TODO: change the logic below
         if( bitr == _rexbalance.end() ) {
            idx.erase( oitr++ );
            continue;
         }
         auto result = close_rex_order( bitr, oitr->rex_requested );
         auto next   = oitr;
         ++next;
         if( std::get<0>( result ) ) {
            idx.modify( oitr, 0, [&]( auto& rt ) {
               rt.proceeds = std::get<1>( result );
               rt.close();
            });
         }
         oitr = next;
      }

   }

   std::tuple<bool, int64_t, int64_t> system_contract::close_rex_order( const rex_balance_table::const_iterator& bitr, const asset& rex ) {
      auto rexitr = _rextable.begin();
      const auto S0 = rexitr->total_lendable.amount;
      const auto R0 = rexitr->total_rex.amount;
      const auto R1 = R0 - rex.amount;
      const auto S1 = (uint128_t(R1) * S0) / R0;
      const int64_t proceeds      = S0 - S1;  // asset( S0 - S1, CORE_SYMBOL );
      const int64_t unstake_quant = ( uint128_t(rex.amount) * bitr->vote_stake.amount ) / bitr->rex_balance.amount;
      bool success = false;
      if( proceeds <= rexitr->total_unlent.amount ) {
         _rextable.modify( rexitr, 0, [&]( auto& rt ) {
            rt.total_rex.amount      = R1;
            rt.total_lendable.amount = S1;
            rt.total_unlent.amount   = rt.total_lendable.amount - rt.total_lent.amount;
         });
         _rexbalance.modify( bitr, 0, [&]( auto& rb ) {
            rb.vote_stake.amount  -= unstake_quant;
            rb.rex_balance.amount -= rex.amount;
         });
         success = true;
      }
      return std::make_tuple( success, proceeds, unstake_quant );
   }

}; /// namespace eosiosystem
