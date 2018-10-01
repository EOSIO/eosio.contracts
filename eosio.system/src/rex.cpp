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
   void system_contract::rentcpu( account_name from, account_name receiver, asset payment, bool auto_renew ) {

      require_auth( from );

      runrex(2);

      INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {from,N(active)},
                                                    { from, N(eosio.rex), payment, string("rent CPU") } );

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

      rex_cpu_loan_table cpu_loans(_self,_self);
      
      cpu_loans.emplace( from, [&]( auto& c ) {
         c.from         = from;
         c.receiver     = receiver;
         c.loan_payment = payment;
         c.total_staked = asset( rented_tokens, CORE_SYMBOL );
         c.expiration   = eosio::time_point( eosio::microseconds(current_time() + eosio::days(30).count()) );
         c.loan_num     = itr->loan_num;
         
         c.auto_renew   = auto_renew;
         c.balance      = asset( 0, CORE_SYMBOL );
      });

      update_resource_limits( receiver, rented_tokens, 0 );
   }
   
   void system_contract::rentnet( account_name from, account_name receiver, asset payment, bool auto_renew ) {

      require_auth( from );

      runrex(2);

      INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {from,N(active)},
                                                    { from, N(eosio.rex), payment, string("rent NET") } );

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

      rex_net_loan_table net_loans(_self,_self);

      net_loans.emplace( from, [&]( auto& c ) {
         c.from         = from;
         c.receiver     = receiver;
         c.loan_payment = payment;
         c.total_staked = asset( rented_tokens, CORE_SYMBOL );
         c.expiration   = eosio::time_point( eosio::microseconds(current_time() + eosio::days(30).count()) );
         c.loan_num     = itr->loan_num;
         
         c.auto_renew   = auto_renew;
         c.balance      = asset( 0, CORE_SYMBOL );
      });

      update_resource_limits( receiver, 0, rented_tokens );
   }


   void system_contract::fundrexloan( account_name from, uint64_t loan_num, asset payment, bool cpu ) {

      require_auth( from );

      INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {from,N(active)},
                                                    { from, N(eosio.rex), payment, string("fund ") + (cpu ? "CPU loan" : "NET loan") } );
      // TODO: refactor and remove code duplication
      if( cpu ) {
         rex_cpu_loan_table cpu_loans( _self, _self );
         auto itr = cpu_loans.find( loan_num );
         eosio_assert( itr != cpu_loans.end(), "loan not found" );
         eosio_assert( itr->from, "actor has to be loan creator" );
         eosio_assert( itr->auto_renew, "loan must be set as auto-renew" );
         eosio_assert( itr->expiration > current_time_point(), "loan has already expired" );
         cpu_loans.modify( itr, 0, [&]( auto& loan ) {
            loan.balance.amount += payment.amount;
         });
      } else {
         rex_net_loan_table net_loans( _self, _self );
         auto itr = net_loans.find( loan_num );
         eosio_assert( itr != net_loans.end(), "loan not found" );
         eosio_assert( itr->from, "actor has to be loan creator" );
         eosio_assert( itr->auto_renew, "loan must be set as auto-renew" );
         eosio_assert( itr->expiration > current_time_point(), "loan has already expired" );
         net_loans.modify( itr, 0, [&]( auto& loan ) {
            loan.balance.amount += payment.amount;
         });
      }
   }

   void system_contract::claimrefund( account_name owner ) {
      
      require_auth( owner );
      
      loan_refund_table loan_refunds( _self, _self );      
      auto itr = loan_refunds.find( owner );
      eosio_assert( itr != loan_refunds.end(), "no refund to be claimed" );
      if( itr->balance.amount > 0 )
         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), { N(eosio.rex), N(active) },
                                                       { N(eosio.rex), owner, itr->balance, "claim REX loan refund" } );
      loan_refunds.erase( itr );
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

      // TODO: refactor and remove code duplication
      {
         rex_cpu_loan_table cpu_loans( _self, _self );
         auto cpu_idx = cpu_loans.get_index<N(byexpr)>();
         bool delete_loan = false;
         for( uint16_t i = 0; i < max; ++i ) {
            auto itr = cpu_idx.begin();                                                                                                                                                                                                                                        
            if( itr == cpu_idx.end() ) break;
            if( itr->expiration.elapsed.count() > current_time() ) break;
            
            // update rex totals to account for closing the loan
            unrent( itr->total_staked.amount );
            
            int64_t delta_stake = 0;
            if( itr->auto_renew && itr->loan_payment <= itr->balance ) {
               
               int64_t rented_tokens = 0;
               _rextable.modify( rexi, 0, [&]( auto& rt ) {
                  rented_tokens = bancor_convert( rt.total_rent.amount,
                                                  rt.total_unlent.amount,
                                                  itr->loan_payment.amount );
                  rt.total_lent.amount    += rented_tokens;
                  rt.total_unlent.amount  += itr->loan_payment.amount;
                  rt.total_lendable.amount = rt.total_unlent.amount + rt.total_lent.amount;
               });
               
               cpu_idx.modify ( itr, 0, [&]( auto& loan ) {
                  delta_stake              = rented_tokens - loan.total_staked.amount;
                  loan.total_staked.amount = rented_tokens;
                  loan.expiration         += eosio::days(30);
                  loan.balance.amount     -= loan.loan_payment.amount;
               });
      
            } else {
               delete_loan = true;
               delta_stake = -( itr->total_staked.amount );
               // refund "from" account if the closed loan balance is positive
               if( itr->auto_renew && itr->balance.amount > 0 ) {
                  loan_refund_table loan_refunds( _self, _self );
                  auto ref_itr = loan_refunds.find( itr->from );
                  if( ref_itr == loan_refunds.end() ) {
                     loan_refunds.emplace( itr->from, [&]( auto& ref ) {
                        ref.owner   = itr->from;
                        ref.balance = itr->balance;
                     });
                  } else {
                     loan_refunds.modify( ref_itr, itr->from, [&]( auto& ref ) {
                        ref.balance.amount += itr->balance.amount;
                     });
                  }
               }
            }
            
            if( delta_stake != 0 )
               update_resource_limits( itr->receiver, delta_stake, 0 );

            if( delete_loan )
               cpu_idx.erase( itr );
         }
      }

      // TODO: refactor and remove code duplication
      {
         rex_net_loan_table net_loans( _self, _self );
         auto net_idx = net_loans.get_index<N(byexpr)>();
         bool delete_loan = false;
         for( uint16_t i = 0; i < max; ++i ) {
            auto itr = net_idx.begin();
            if( itr == net_idx.end() ) break;
            if( itr->expiration.elapsed.count() > current_time() ) break;

            // update rex totals to account for closing the loan
            unrent( itr->total_staked.amount );

            int64_t delta_stake = 0;
            if( itr->auto_renew && itr->loan_payment <= itr->balance ) {

               int64_t rented_tokens = 0;
               _rextable.modify( rexi, 0, [&]( auto& rt ) {
                  rented_tokens = bancor_convert( rt.total_rent.amount,
                                                  rt.total_unlent.amount,
                                                  itr->loan_payment.amount );
                  rt.total_lent.amount    += rented_tokens;
                  rt.total_unlent.amount  += itr->loan_payment.amount;
                  rt.total_lendable.amount = rt.total_unlent.amount + rt.total_lent.amount;
               });

               net_idx.modify ( itr, 0, [&]( auto& loan ) {
                  delta_stake              = rented_tokens - loan.total_staked.amount;
                  loan.total_staked.amount = rented_tokens;
                  loan.expiration         += eosio::days(30);
                  loan.balance            -= itr->loan_payment;
               });

            } else {
               delete_loan = true;
               delta_stake = -( itr->total_staked.amount );
               // refund "from" account if the closed loan balance is positive
               if( itr->auto_renew && itr->balance.amount > 0 ) {
                  loan_refund_table loan_refunds( _self, _self );
                  auto ref_itr = loan_refunds.find( itr->from );
                  if( ref_itr == loan_refunds.end() ) {
                     loan_refunds.emplace( itr->from, [&]( auto& ref ) { 
                        ref.owner   = itr->from;
                        ref.balance = itr->balance;
                     });
                  } else {
                     loan_refunds.modify( ref_itr, itr->from, [&]( auto& ref ) {
                        ref.balance.amount += itr->balance.amount;
                     });
                  }
               }
            }

            if( delta_stake != 0 )
               update_resource_limits( itr->receiver, 0, delta_stake );

            if( delete_loan )
               net_idx.erase( itr );
         }
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
