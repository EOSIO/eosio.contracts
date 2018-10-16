/**
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/eosio.system.hpp>

namespace eosiosystem {

   void system_contract::deposit( name owner, asset amount ) {
      
      require_auth( owner );

      eosio_assert( amount.symbol == core_symbol(), "must deposit core token" );

      INLINE_ACTION_SENDER(eosio::token, transfer)( token_account, { owner, active_permission },
                                                    { owner, rex_account, amount, "deposit into REX fund" } );
      auto itr = _rexfunds.find( owner.value );
      if( itr == _rexfunds.end()  ) {
         _rexfunds.emplace( owner, [&]( auto& fund ) {
            fund.owner   = owner;
            fund.balance = amount;
         });
      } else {
         _rexfunds.modify( itr, same_payer, [&]( auto& fund ) {
            fund.balance.amount += amount.amount;
         });
      }
      
      update_rex_account( owner, asset( 0, core_symbol() ), asset( 0, core_symbol() ) );
   }

   void system_contract::withdraw( name owner, asset amount ) {

      require_auth( owner );

      eosio_assert( amount.symbol == core_symbol(), "must withdraw core token" );

      update_rex_account( owner, asset( 0, core_symbol() ), asset( 0, core_symbol() ) );

      auto itr = _rexfunds.require_find( owner.value, "account has no REX funds" );
      eosio_assert( amount <= itr->balance, "insufficient funds");
      _rexfunds.modify( itr, same_payer, [&]( auto& fund ) {
         fund.balance.amount -= amount.amount;
      });      

      INLINE_ACTION_SENDER(eosio::token, transfer)( token_account, { rex_account, active_permission },
                                                    { rex_account, owner, amount, "withdraw from REX fund" } );
   }

   /**
    * Transfers SYS tokens from user balance and credits converts them to REX stake.
    */
   void system_contract::buyrex( name from, asset amount ) {
      
      require_auth( from );

      eosio_assert( amount.symbol == core_symbol(), "asset must be system token" );

      const int64_t rex_ratio = 10000;
      const int64_t init_rent = 1000000;
      {
         auto vitr = _voters.find( from.value );
         eosio_assert( vitr != _voters.end() && ( vitr->proxy || vitr->producers.size() >= 21 ), 
                       "must vote for proxy or at least 21 producers before buying REX" );
      }

      transfer_from_fund( from, amount );

      asset rex_received( 0, rex_symbol );

      auto itr = _rextable.begin();
      if( itr == _rextable.end() ) {
         _rextable.emplace( _self, [&]( auto& rp ){
            rex_received.amount = amount.amount * rex_ratio;

            rp.total_lendable   = amount;
            rp.total_lent       = asset( 0, core_symbol() );
            rp.total_rent       = asset( init_rent, core_symbol() ); /// base amount prevents renting profitably until at least a minimum number of core_symbol() are made available
            rp.total_rex        = rex_received;
            rp.total_unlent     = rp.total_lendable - rp.total_lent;
            rp.namebid_proceeds = asset( 0, core_symbol() );
         });
      } else if( itr->total_lendable.amount == 0 ) { /// should be a rare corner case
         _rextable.modify( itr, same_payer, [&]( auto& rp ) {
            rex_received.amount = amount.amount * rex_ratio;
            
            rp.total_lendable.amount = amount.amount;
            rp.total_lent.amount     = 0;
            rp.total_rex.amount      = rex_received.amount;
            rp.total_unlent.amount   = amount.amount;
            rp.total_rent.amount     = std::min( init_rent, rp.total_rent.amount );
         });
      } else {
         const auto S0 = itr->total_lendable.amount;
         const auto S1 = S0 + amount.amount;
         const auto R0 = itr->total_rex.amount;
         const auto R1 = (uint128_t(S1) * R0) / S0;

         rex_received.amount = R1 - R0;

         _rextable.modify( itr, same_payer, [&]( auto& rp ) {
            rp.total_lendable.amount = S1;
            rp.total_rex.amount      = R1;
            rp.total_unlent.amount   = rp.total_lendable.amount - rp.total_lent.amount;
            eosio_assert( rp.total_unlent.amount >= 0, "programmer error, this should never go negative" );
         });
      }

      auto bitr = _rexbalance.find( from.value );
      if( bitr == _rexbalance.end() ) {
         _rexbalance.emplace( from, [&]( auto& rb ) {
            rb.owner       = from;
            rb.vote_stake  = amount;
            rb.rex_balance = rex_received;
         });
      } else {
         _rexbalance.modify( bitr, same_payer, [&]( auto& rb ) {
            rb.vote_stake.amount  += amount.amount;
            rb.rex_balance.amount += rex_received.amount;
         });
      }

      runrex(2);

      update_rex_account( from, asset( 0, core_symbol() ), amount );
   }

   /**
    * Converts REX stake back into SYS tokens at current exchange rate
    */
   void system_contract::sellrex( name from, asset rex ) {

      runrex(2);

      require_auth( from );

      auto itr = _rextable.begin();
      eosio_assert( itr != _rextable.end(), "rex system not initialized yet" );

      auto bitr = _rexbalance.require_find( from.value, "user must first buyrex" );
      eosio_assert( bitr->rex_balance.symbol == rex.symbol, "asset symbol must be (4, REX)" );
      eosio_assert( bitr->rex_balance >= rex, "insufficient funds" );

      auto current_order = close_rex_order( bitr, rex );
      update_rex_account( from, current_order.proceeds, -current_order.unstake_quant );
      if( !current_order.success ) {
         /**
          * REX order couldn't be filled and is added to queue.
          * If account already has an open order, requested rex is added to existing order.
          */
         auto oitr = _rexorders.find( from.value );
         if( oitr == _rexorders.end() ) {
            _rexorders.emplace( from, [&]( auto& ordr ) {
               ordr.owner         = from;
               ordr.rex_requested = rex;
               ordr.is_open       = true;
               ordr.proceeds      = asset( 0, core_symbol() );
               ordr.unstake_quant = asset( 0, core_symbol() );
               ordr.order_time    = current_time_point();
            });
         } else {
            _rexorders.modify( oitr, same_payer, [&]( auto& ordr ) {
               ordr.rex_requested.amount += rex.amount;
               eosio_assert( bitr->rex_balance >= ordr.rex_requested, "insufficient funds for current and scheduled orders");
            });
         }
      }
   }

   void system_contract::cnclrexorder( name owner ) {

      require_auth( owner );

      auto itr = _rexorders.require_find( owner.value, "no sellrex order is scheduled" );
      eosio_assert( itr->is_open, "sellrex order has been closed and cannot be canceled" );
      _rexorders.erase( itr );
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

   void system_contract::update_resource_limits( name receiver, int64_t delta_cpu, int64_t delta_net ) {
      user_resources_table   totals_tbl( _self, receiver.value );
      auto tot_itr = totals_tbl.find( receiver.value );
      eosio_assert( tot_itr !=  totals_tbl.end(), "expected to find resource table" );
      totals_tbl.modify( tot_itr, same_payer, [&]( auto& tot ) {
         tot.cpu_weight.amount += delta_cpu;
         tot.net_weight.amount += delta_net;
      });
      eosio_assert( 0 <= tot_itr->net_weight.amount, "insufficient staked total net bandwidth" );
      eosio_assert( 0 <= tot_itr->cpu_weight.amount, "insufficient staked total cpu bandwidth" );

      int64_t ram_bytes, net, cpu;
      get_resource_limits( receiver.value, &ram_bytes, &net, &cpu );
      set_resource_limits( receiver.value, ram_bytes, tot_itr->net_weight.amount, tot_itr->cpu_weight.amount );
   }

   /**
    * Uses payment to rent as many SYS tokens as possible and stake them for either cpu or net for the benefit of receiver,
    * after 30 days the rented SYS delegation of CPU or NET will expire.
    */
   void system_contract::rentcpu( name from, name receiver, asset loan_payment, asset loan_fund ) {

      require_auth( from );

      rex_cpu_loan_table cpu_loans( _self, _self.value );
      int64_t rented_tokens = rent_rex( cpu_loans, from, receiver, loan_payment, loan_fund );
      update_resource_limits( receiver, rented_tokens, 0 );
   }
   
   void system_contract::rentnet( name from, name receiver, asset loan_payment, asset loan_fund ) {

      require_auth( from );

      rex_net_loan_table net_loans( _self, _self.value );
      int64_t rented_tokens = rent_rex( net_loans, from, receiver, loan_payment, loan_fund );
      update_resource_limits( receiver, 0, rented_tokens );
   }

   void system_contract::fundcpuloan( name from, uint64_t loan_num, asset payment ) {

      require_auth( from );

      rex_cpu_loan_table cpu_loans( _self, _self.value );
      fund_rex_loan( cpu_loans, from, loan_num, payment  );
   }

   void system_contract::fundnetloan( name from, uint64_t loan_num, asset payment ) {

      require_auth( from );

      rex_net_loan_table net_loans( _self, _self.value );
      fund_rex_loan( net_loans, from, loan_num, payment );
   }

   void system_contract::defcpuloan( name from, uint64_t loan_num, asset amount ) {
      
      require_auth( from );
      
      rex_cpu_loan_table cpu_loans( _self, _self.value );
      defund_rex_loan( cpu_loans, from, loan_num, amount );
   }

   void system_contract::defnetloan( name from, uint64_t loan_num, asset amount ) {

      require_auth( from );

      rex_net_loan_table net_loans( _self, _self.value );
      defund_rex_loan( net_loans, from, loan_num, amount );
   }

   void system_contract::updaterex( name owner ) {
      
      require_auth( owner );
      
      auto itr = _rexbalance.require_find( owner.value, "account has no REX balance" );
      const asset init_stake = itr->vote_stake;

      runrex(2);

      auto rexp_itr = _rextable.begin();
      const asset& total_rex      = rexp_itr->total_rex;
      const asset& total_lendable = rexp_itr->total_lendable;

      asset current_stake( 0, core_symbol() );
      current_stake.amount = ( uint128_t(itr->rex_balance.amount) * total_lendable.amount ) / total_rex.amount;
      _rexbalance.modify( itr, same_payer, [&]( auto& rb ) {
         rb.vote_stake = current_stake;
      });

      asset delta_stake = current_stake - init_stake;
      update_rex_account( owner, asset( 0, core_symbol() ), delta_stake );
   }

   void system_contract::rexexec( name user, uint16_t max ) {

      require_auth( user );
      
      runrex( max );
   }

   /**
    * Perform maitenance operations on expired rex
    */
   void system_contract::runrex( uint16_t max ) {
      auto rexi = _rextable.begin();
      eosio_assert( rexi != _rextable.end(), "rex system not initialized yet" );

      auto process_expired_loan = [&]( auto& idx, const auto& itr ) -> std::pair<bool, int64_t> {
         _rextable.modify( rexi, same_payer, [&]( auto& rt ) {
            bancor_convert( rt.total_unlent.amount, rt.total_rent.amount, itr->total_staked.amount );
            rt.total_lent.amount    -= itr->total_staked.amount;
            rt.total_lendable.amount = rt.total_unlent.amount + rt.total_lent.amount;
         });

         bool    delete_loan = false;
         int64_t delta_stake = 0;
         if( itr->payment <= itr->balance && rex_loans_available() ) {
            int64_t rented_tokens = 0;
            _rextable.modify( rexi, same_payer, [&]( auto& rt ) {
               rented_tokens = bancor_convert( rt.total_rent.amount,
                                               rt.total_unlent.amount,
                                               itr->payment.amount );
               rt.total_lent.amount    += rented_tokens;
               rt.total_unlent.amount  += itr->payment.amount;
               rt.total_lendable.amount = rt.total_unlent.amount + rt.total_lent.amount;
            });
            idx.modify ( itr, same_payer, [&]( auto& loan ) {
               delta_stake              = rented_tokens - loan.total_staked.amount;
               loan.total_staked.amount = rented_tokens;
               loan.expiration         += eosio::days(30);
               loan.balance.amount     -= loan.payment.amount;
            });
         } else {
            delete_loan = true;
            delta_stake = -( itr->total_staked.amount );
            /// refund "from" account if the closed loan balance is positive
            if( itr->balance.amount > 0 ) {
               transfer_to_fund( itr->from, itr->balance );
            }
         }
         
         return std::make_pair( delete_loan, delta_stake );
      };

      /// transfer from eosio.names to eosio.rex
      if( rexi->namebid_proceeds.amount > 0 ) {
         deposit_rex( names_account, rexi->namebid_proceeds );
         _rextable.modify( rexi, same_payer, [&]( auto& rt ) {
            rt.namebid_proceeds.amount = 0;
         });
      }

      /// process cpu loans
      {
         rex_cpu_loan_table cpu_loans( _self, _self.value );
         auto cpu_idx = cpu_loans.get_index<"byexpr"_n>();
         for( uint16_t i = 0; i < max; ++i ) {
            auto itr = cpu_idx.begin();                                                                                                                                                                                                                                        
            if( itr == cpu_idx.end() || itr->expiration > current_time_point() ) break;
      
            auto result = process_expired_loan( cpu_idx, itr );
            if( result.second != 0 )
               update_resource_limits( itr->receiver, result.second, 0 );

            if( result.first )
               cpu_idx.erase( itr );
         }
      }

      /// process net loans
      {
         rex_net_loan_table net_loans( _self, _self.value );
         auto net_idx = net_loans.get_index<"byexpr"_n>();
         for( uint16_t i = 0; i < max; ++i ) {
            auto itr = net_idx.begin();
            if( itr == net_idx.end() || itr->expiration > current_time_point() ) break;

            auto result = process_expired_loan( net_idx, itr );
            if( result.second != 0 )
               update_resource_limits( itr->receiver, 0, result.second );

            if( result.first )
               net_idx.erase( itr );
         }
      }

      /// process sellrex orders
      {
         auto idx = _rexorders.get_index<"bytime"_n>();
         auto oitr = idx.begin();
         for( uint16_t i = 0; i < max; ++i ) {
            if( oitr == idx.end() || !oitr->is_open ) break;
            auto bitr   = _rexbalance.find( oitr->owner.value ); // bitr != _rexbalance.end()
            auto result = close_rex_order( bitr, oitr->rex_requested );
            auto next   = oitr;
            ++next;
            if( result.success ) {
               idx.modify( oitr, same_payer, [&]( auto& rt ) {
                  rt.proceeds.amount      = result.proceeds.amount;
                  rt.unstake_quant.amount = result.unstake_quant.amount;
                  rt.close();
               });
            }
            oitr = next;
         }
      }

   }

   template <typename T>
   int64_t system_contract::rent_rex( T& table, name from, name receiver, const asset& payment, const asset& fund ) {

      runrex(2);

      eosio_assert(  rex_loans_available(), "rex loans are not currently available" );
      eosio_assert( payment.symbol == core_symbol() && fund.symbol == core_symbol(), "must use core token" );
      
      update_rex_account( from, asset( 0, core_symbol() ), asset( 0, core_symbol() ) );
      transfer_from_fund( from, payment + fund );

      auto itr = _rextable.begin();
      eosio_assert( itr != _rextable.end(), "rex system not initialized yet" );

      int64_t rented_tokens = 0;
      _rextable.modify( itr, same_payer, [&]( auto& rt ) {
         rented_tokens = bancor_convert( rt.total_rent.amount, rt.total_unlent.amount, payment.amount );
         rt.total_lent.amount    += rented_tokens;
         rt.total_unlent.amount  += payment.amount;
         rt.total_lendable.amount = rt.total_unlent.amount + rt.total_lent.amount;
         rt.loan_num++;
      });

      table.emplace( from, [&]( auto& c ) {
         c.from         = from;
         c.receiver     = receiver;
         c.payment      = payment;
         c.balance      = fund;
         c.total_staked = asset( rented_tokens, core_symbol() );
         c.expiration   = current_time_point() + eosio::days(30);
         c.loan_num     = itr->loan_num;
      });

      return rented_tokens;
   }

   rex_order_output system_contract::close_rex_order( const rex_balance_table::const_iterator& bitr, const asset& rex ) {
      auto rexitr = _rextable.begin();
      const auto S0 = rexitr->total_lendable.amount;
      const auto R0 = rexitr->total_rex.amount;
      const auto R1 = R0 - rex.amount;
      const auto S1 = (uint128_t(R1) * S0) / R0;
      asset proceeds( S0 - S1, core_symbol() );
      asset unstake_quant( ( uint128_t(rex.amount) * bitr->vote_stake.amount ) / bitr->rex_balance.amount,
                           core_symbol() );
      bool success = false;
      if( proceeds.amount <= rexitr->total_unlent.amount ) {
         _rextable.modify( rexitr, same_payer, [&]( auto& rt ) {
            rt.total_rex.amount      = R1;
            rt.total_lendable.amount = S1;
            rt.total_unlent.amount   = rt.total_lendable.amount - rt.total_lent.amount;
         });
         _rexbalance.modify( bitr, same_payer, [&]( auto& rb ) {
            rb.vote_stake.amount  -= unstake_quant.amount;
            rb.rex_balance.amount -= rex.amount;
         });
         success = true;
      } else {
         proceeds.amount      = 0;
         unstake_quant.amount = 0;
      }
      return { success, proceeds, unstake_quant };
   }

   void system_contract::deposit_rex( const name& from, const asset& amount ) {
      auto itr = _rextable.begin();
      if( itr != _rextable.end() ) {
         _rextable.modify( itr, same_payer, [&]( auto& rp ) {
            rp.total_unlent.amount   += amount.amount;
            rp.total_lendable.amount += amount.amount;
         });
         
         INLINE_ACTION_SENDER(eosio::token, transfer)( token_account, { from, active_permission },
            { from, rex_account, amount, std::string("transfer from ") + name{from}.to_string() + " REX"} );
      }
   }

   template <typename T>
   void system_contract::fund_rex_loan( T& table, name from, uint64_t loan_num, const asset& payment  ) {
      eosio_assert( payment.symbol == core_symbol(), "must use core token" );
      transfer_from_fund( from, payment );
      auto itr = table.require_find( loan_num, "loan not found" );
      eosio_assert( itr->from == from, "actor has to be loan creator" );
      eosio_assert( itr->expiration > current_time_point(), "loan has already expired" );
      table.modify( itr, same_payer, [&]( auto& loan ) {
         loan.balance.amount += payment.amount;
      });
   }

   template <typename T>
   void system_contract::defund_rex_loan( T& table, name from, uint64_t loan_num, const asset& amount  ) {
      eosio_assert( amount.symbol == core_symbol(), "must use core token" );
      auto itr = table.require_find( loan_num, "loan not found" );
      eosio_assert( itr->from == from, "actor has to be loan creator" );
      eosio_assert( itr->expiration > current_time_point(), "loan has already expired" );
      eosio_assert( itr->balance >= amount, "insufficent loan balance" );
      table.modify( itr, same_payer, [&]( auto& loan ) {
         loan.balance.amount -= amount.amount;
      });
      transfer_to_fund( from, amount );
   }

   void system_contract::transfer_from_fund( name owner, const asset& amount ) {
      auto itr = _rexfunds.require_find( owner.value, "must deposit to REX fund first" );
      eosio_assert( amount <= itr->balance, "insufficient funds");
      _rexfunds.modify( itr, same_payer, [&]( auto& fund ) {
         fund.balance.amount -= amount.amount;
      });
   }

   void system_contract::transfer_to_fund( name owner, const asset& amount ) {
      auto itr = _rexfunds.require_find( owner.value, "programmer error" );
      _rexfunds.modify( itr, same_payer, [&]( auto& fund ) {
         fund.balance.amount += amount.amount;
      });
   }

   void system_contract::update_rex_account( name owner, asset proceeds, asset delta_stake ) {
      auto itr = _rexorders.find( owner.value );
      if( itr != _rexorders.end() && !itr->is_open ) {
         proceeds.amount    += itr->proceeds.amount;
         delta_stake.amount -= itr->unstake_quant.amount;
         _rexorders.erase( itr );
      }
      if( proceeds.amount > 0 )
         transfer_to_fund( owner, proceeds );
      if( delta_stake.amount != 0 )
         update_voting_power( owner, delta_stake );
   }

}; /// namespace eosiosystem
