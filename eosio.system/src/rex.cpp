/**
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/eosio.system.hpp>

namespace eosiosystem {

   void system_contract::deposit( const name& owner, const asset& amount )
   {   
      require_auth( owner );

      eosio_assert( amount.symbol == core_symbol(), "must deposit core token" );
      eosio_assert( 0 < amount.amount, "must deposit a positive amount" );

      INLINE_ACTION_SENDER(eosio::token, transfer)( token_account, { owner, active_permission },
                                                    { owner, rex_account, amount, "deposit to REX fund" } );
      auto itr = _rexfunds.find( owner.value );
      if ( itr == _rexfunds.end()  ) {
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

   void system_contract::withdraw( const name& owner, const asset& amount )
   {
      require_auth( owner );

      eosio_assert( amount.symbol == core_symbol(), "must withdraw core token" );
      eosio_assert( 0 < amount.amount, "must withdraw a positive amount" );
      update_rex_account( owner, asset( 0, core_symbol() ), asset( 0, core_symbol() ) );
      transfer_from_fund( owner, amount );

      INLINE_ACTION_SENDER(eosio::token, transfer)( token_account, { rex_account, active_permission },
                                                    { rex_account, owner, amount, "withdraw from REX fund" } );
   }

   /**
    * Transfers SYS tokens from user balance and credits converts them to REX stake.
    */
   void system_contract::buyrex( const name& from, const asset& amount )
   {   
      require_auth( from );

      eosio_assert( amount.symbol == core_symbol(), "asset must be core token" );
      eosio_assert( amount.amount > 0, "must use positive amount" );
      
      transfer_from_fund( from, amount );
      const asset rex_received    = add_to_rex_pool( amount );
      const asset delta_rex_stake = add_to_rex_balance( from, amount, rex_received );
      runrex(2);
      update_rex_account( from, asset( 0, core_symbol() ), delta_rex_stake );
   }

   void system_contract::unstaketorex( const name& owner, const name& receiver, const asset& from_net, const asset& from_cpu )
   {
      require_auth( owner );

      eosio_assert( from_cpu.symbol == core_symbol() && from_net.symbol == core_symbol(), "asset must be core token" );
      eosio_assert( 0 <= from_cpu.amount, "must unstake a positive amount to buy rex" );
      eosio_assert( 0 <= from_net.amount, "must unstake a positive amount to buy rex" );
      eosio_assert( 0 < from_cpu.amount || 0 < from_net.amount, "must unstake a positive amount to buy rex" );
      
      {
         auto vitr = _voters.find( owner.value );
         eosio_assert( vitr != _voters.end() && ( vitr->proxy || vitr->producers.size() >= 21 ),
                       "must vote for proxy or at least 21 producers before buying REX" );
      }

      {
         del_bandwidth_table dbw_table( _self, owner.value );
         auto del_itr = dbw_table.require_find( receiver.value, "delegated bandwidth record does not exist" );
         eosio_assert( from_cpu.amount <= del_itr->cpu_weight.amount, "amount exceeds tokens staked for cpu");
         eosio_assert( from_net.amount <= del_itr->net_weight.amount, "amount exceeds tokens staked for net");
         dbw_table.modify( del_itr, same_payer, [&]( delegated_bandwidth& dbw ) {
            dbw.cpu_weight.amount -= from_cpu.amount;
            dbw.net_weight.amount -= from_net.amount;
         });
         if ( del_itr->cpu_weight.amount == 0 && del_itr->net_weight.amount == 0 ) {
            dbw_table.erase( del_itr );
         }
      }

      update_resource_limits( name(0), receiver, -from_cpu.amount, -from_net.amount );

      const asset payment = from_cpu + from_net;
      INLINE_ACTION_SENDER(eosio::token, transfer)( token_account, { stake_account, active_permission },
                                                    { stake_account, rex_account, payment, "buy REX with staked tokens" } );

      const asset rex_received = add_to_rex_pool( payment );
      add_to_rex_balance( owner, payment, rex_received );
      runrex(2);
      update_rex_account( owner, asset( 0, core_symbol() ), asset( 0, core_symbol() ), true );
   }

   void system_contract::sellrex( const name& from, const asset& rex )
   {
      runrex(2);

      require_auth( from );

      eosio_assert( rex_system_initialized(), "rex system not initialized yet" );

      auto bitr = _rexbalance.require_find( from.value, "user must first buyrex" );
      eosio_assert( rex.symbol == bitr->rex_balance.symbol , "asset symbol must be (4, REX)" );
      process_rex_maturities( bitr );
      eosio_assert( rex.amount <= bitr->matured_rex, "insufficient funds" );

      auto current_order = close_rex_order( bitr, rex );
      update_rex_account( from, current_order.proceeds, current_order.stake_change );
      if ( !current_order.success ) {
         /**
          * REX order couldn't be filled and is added to queue.
          * If account already has an open order, requested rex is added to existing order.
          */
         auto oitr = _rexorders.find( from.value );
         if ( oitr == _rexorders.end() ) {
            _rexorders.emplace( from, [&]( auto& order ) {
               order.owner         = from;
               order.rex_requested = rex;
               order.is_open       = true;
               order.proceeds      = asset( 0, core_symbol() );
               order.stake_change  = asset( 0, core_symbol() );
               order.order_time    = current_time_point();
            });
         } else {
            _rexorders.modify( oitr, same_payer, [&]( auto& order ) {
               order.rex_requested.amount += rex.amount;
               eosio_assert( order.rex_requested.amount <= bitr->matured_rex,
                             "insufficient funds for current and scheduled orders");
            });
         }
      }
   }

   void system_contract::cnclrexorder( const name& owner )
   {
      require_auth( owner );

      auto itr = _rexorders.require_find( owner.value, "no sellrex order is scheduled" );
      eosio_assert( itr->is_open, "sellrex order has been closed and cannot be canceled" );
      _rexorders.erase( itr );
   }

   /**
    * Uses payment to rent as many SYS tokens as possible and stake them for either cpu or net for the benefit of receiver,
    * after 30 days the rented SYS delegation of CPU or NET will expire.
    */
   void system_contract::rentcpu( const name& from, const name& receiver, const asset& loan_payment, const asset& loan_fund )
   {
      require_auth( from );

      rex_cpu_loan_table cpu_loans( _self, _self.value );
      int64_t rented_tokens = rent_rex( cpu_loans, from, receiver, loan_payment, loan_fund );
      update_resource_limits( from, receiver, rented_tokens, 0 );
   }
   
   void system_contract::rentnet( const name& from, const name& receiver, const asset& loan_payment, const asset& loan_fund )
   {
      require_auth( from );

      rex_net_loan_table net_loans( _self, _self.value );
      int64_t rented_tokens = rent_rex( net_loans, from, receiver, loan_payment, loan_fund );
      update_resource_limits( from, receiver, 0, rented_tokens );
   }

   void system_contract::fundcpuloan( const name& from, uint64_t loan_num, const asset& payment )
   {
      require_auth( from );

      rex_cpu_loan_table cpu_loans( _self, _self.value );
      fund_rex_loan( cpu_loans, from, loan_num, payment  );
   }

   void system_contract::fundnetloan( const name& from, uint64_t loan_num, const asset& payment )
   {
      require_auth( from );

      rex_net_loan_table net_loans( _self, _self.value );
      fund_rex_loan( net_loans, from, loan_num, payment );
   }

   void system_contract::defcpuloan( const name& from, uint64_t loan_num, const asset& amount )
   {     
      require_auth( from );
      
      rex_cpu_loan_table cpu_loans( _self, _self.value );
      defund_rex_loan( cpu_loans, from, loan_num, amount );
   }

   void system_contract::defnetloan( const name& from, uint64_t loan_num, const asset& amount )
   {
      require_auth( from );

      rex_net_loan_table net_loans( _self, _self.value );
      defund_rex_loan( net_loans, from, loan_num, amount );
   }

   void system_contract::updaterex( const name& owner )
   {   
      require_auth( owner );

      runrex(2);

      auto itr = _rexbalance.require_find( owner.value, "account has no REX balance" );
      const asset init_stake = itr->vote_stake;

      auto rexp_itr = _rexpool.begin();
      const int64_t total_rex      = rexp_itr->total_rex.amount;
      const int64_t total_lendable = rexp_itr->total_lendable.amount;
      const int64_t rex_balance    = itr->rex_balance.amount;
      
      asset current_stake( 0, core_symbol() );
      if ( total_rex > 0 ) {
         current_stake.amount = ( uint128_t(rex_balance) * total_lendable ) / total_rex;
      }
      _rexbalance.modify( itr, same_payer, [&]( auto& rb ) {
         rb.vote_stake = current_stake;
      });

      update_rex_account( owner, asset( 0, core_symbol() ), current_stake - init_stake );
      process_rex_maturities( itr );
   }

   void system_contract::rexexec( const name& user, uint16_t max )
   {
      require_auth( user );
      
      runrex( max );
   }

   void system_contract::consolidate( const name& owner )
   {
      require_auth( owner );
      
      runrex(2);
      
      auto bitr = _rexbalance.require_find( owner.value, "account has no REX balance" );
      asset rex_in_sell_order = update_rex_account( owner, asset( 0, core_symbol() ), asset( 0, core_symbol() ) );
      consolidate_rex_balance( bitr, rex_in_sell_order );
   }

   void system_contract::closerex( const name& owner )
   {
      require_auth( owner );
      
      if ( rex_system_initialized() )
         runrex(2);
      
      update_rex_account( owner, asset( 0, core_symbol() ), asset( 0, core_symbol() ) );
      
      /// check for any outstanding cpu loans
      {
         rex_cpu_loan_table cpu_loans( _self, _self.value );
         auto cpu_idx = cpu_loans.get_index<"byowner"_n>();
         eosio_assert( cpu_idx.find( owner.value ) == cpu_idx.end(), "account has outstanding CPU loan" );
      }
      
      /// check for any outstanding net loans
      {
         rex_net_loan_table net_loans( _self, _self.value );
         auto net_idx = net_loans.get_index<"byowner"_n>();
         eosio_assert( net_idx.find( owner.value ) == net_idx.end(), "account has outstanding NET loan" );
      }

      /// check for remaining rex balance
      {
         auto rex_itr = _rexbalance.find( owner.value );
         if ( rex_itr != _rexbalance.end() ) {
            eosio_assert( rex_itr->rex_balance.amount == 0, "account has remaining REX, must sell first");
            _rexbalance.erase( rex_itr );
         }
      }

      /// check for remaining rex fund balance
      {
         auto fund_itr =_rexfunds.find( owner.value );
         if ( fund_itr != _rexfunds.end() ) {
            eosio_assert( fund_itr->balance.amount == 0, "account has remaining funds, must withdraw first");
            _rexfunds.erase( fund_itr );
         }
      }
   }

   /**
    * Given two connector balances (conin, and conout), and an incoming amount of
    * in, this function will modify conin and conout and return the delta out.
    *
    * @param in - same units as conin
    * @param conin - the input connector balance
    * @param conout - the output connector balance
    */
   int64_t bancor_convert( int64_t& conin, int64_t& conout, int64_t in )
   {
      const double F0 = double(conin);
      const double T0 = double(conout);
      const double I  = double(in);

      auto out = int64_t((I*T0) / (I+F0));

      if ( out < 0 ) out = 0;

      conin  += in;
      conout -= out;

      return out;
   }

   void system_contract::update_resource_limits( const name& from, const name& receiver, int64_t delta_cpu, int64_t delta_net )
   {
      if ( delta_cpu == 0 && delta_net == 0 ) { // nothing to update
         return;
      }

      {
         user_resources_table totals_tbl( _self, receiver.value );
         auto tot_itr = totals_tbl.find( receiver.value );
         if ( tot_itr == totals_tbl.end() ) {
            eosio_assert( 0 <= delta_cpu && 0 <= delta_net, "logic error, should not occur");
            eosio_assert( 0 < delta_cpu || 0 < delta_net, "");
            tot_itr = totals_tbl.emplace( from, [&]( auto& tot ) {
               tot.owner = receiver;
               tot.cpu_weight = asset( delta_cpu, core_symbol() );
               tot.net_weight = asset( delta_net, core_symbol() );
            });
         } else {
            totals_tbl.modify( tot_itr, same_payer, [&]( auto& tot ) {
               tot.cpu_weight.amount += delta_cpu;
               tot.net_weight.amount += delta_net;
            });
         }
         eosio_assert( 0 <= tot_itr->net_weight.amount, "insufficient staked total net bandwidth" );
         eosio_assert( 0 <= tot_itr->cpu_weight.amount, "insufficient staked total cpu bandwidth" );
         
         if ( tot_itr->net_weight.amount == 0 && tot_itr->cpu_weight.amount == 0 && tot_itr->ram_bytes == 0 ) {
            totals_tbl.erase( tot_itr );
         }
      }

      int64_t ram_bytes, net, cpu;
      get_resource_limits( receiver.value, &ram_bytes, &net, &cpu );
      set_resource_limits( receiver.value, ram_bytes, net + delta_net, cpu + delta_cpu );
   }

   /**
    * Perform maintenance operations on expired rex
    */
   void system_contract::runrex( uint16_t max )
   {
      eosio_assert( rex_system_initialized(), "rex system not initialized yet" );

      auto rexi = _rexpool.begin();

      auto process_expired_loan = [&]( auto& idx, const auto& itr ) -> std::pair<bool, int64_t> {
         _rexpool.modify( rexi, same_payer, [&]( auto& rt ) {
            bancor_convert( rt.total_unlent.amount, rt.total_rent.amount, itr->total_staked.amount );
            rt.total_lent.amount    -= itr->total_staked.amount;
            rt.total_lendable.amount = rt.total_unlent.amount + rt.total_lent.amount;
         });

         bool    delete_loan = false;
         int64_t delta_stake = 0;
         if( itr->payment <= itr->balance && rex_loans_available() ) {
            int64_t rented_tokens = 0;
            _rexpool.modify( rexi, same_payer, [&]( auto& rt ) {
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
            if ( itr->balance.amount > 0 ) {
               transfer_to_fund( itr->from, itr->balance );
            }
         }
         
         return std::make_pair( delete_loan, delta_stake );
      };

      /// transfer from eosio.names to eosio.rex
      if( rexi->namebid_proceeds.amount > 0 ) {
         channel_to_rex( names_account, rexi->namebid_proceeds );
         _rexpool.modify( rexi, same_payer, [&]( auto& rt ) {
            rt.namebid_proceeds.amount = 0;
         });
      }

      /// process cpu loans
      {
         rex_cpu_loan_table cpu_loans( _self, _self.value );
         auto cpu_idx = cpu_loans.get_index<"byexpr"_n>();
         for( uint16_t i = 0; i < max; ++i ) {
            auto itr = cpu_idx.begin();                                                                                                                                                                                                                                        
            if ( itr == cpu_idx.end() || itr->expiration > current_time_point() ) break;
      
            auto result = process_expired_loan( cpu_idx, itr );
            if ( result.second != 0 )
               update_resource_limits( itr->from, itr->receiver, result.second, 0 );

            if ( result.first )
               cpu_idx.erase( itr );
         }
      }

      /// process net loans
      {
         rex_net_loan_table net_loans( _self, _self.value );
         auto net_idx = net_loans.get_index<"byexpr"_n>();
         for ( uint16_t i = 0; i < max; ++i ) {
            auto itr = net_idx.begin();
            if( itr == net_idx.end() || itr->expiration > current_time_point() ) break;

            auto result = process_expired_loan( net_idx, itr );
            if ( result.second != 0 )
               update_resource_limits( itr->from, itr->receiver, 0, result.second );

            if ( result.first )
               net_idx.erase( itr );
         }
      }

      /// process sellrex orders
      {
         auto idx = _rexorders.get_index<"bytime"_n>();
         auto oitr = idx.begin();
         for ( uint16_t i = 0; i < max; ++i ) {
            if( oitr == idx.end() || !oitr->is_open ) break;
            auto bitr   = _rexbalance.find( oitr->owner.value ); // bitr != _rexbalance.end()
            auto result = close_rex_order( bitr, oitr->rex_requested );
            auto next   = oitr;
            ++next;
            if ( result.success ) {
               idx.modify( oitr, same_payer, [&]( auto& order ) {
                  order.proceeds.amount     = result.proceeds.amount;
                  order.stake_change.amount = result.stake_change.amount;
                  order.close();
               });
            }
            oitr = next;
         }
      }

   }

   template <typename T>
   int64_t system_contract::rent_rex( T& table, const name& from, const name& receiver, const asset& payment, const asset& fund )
   {
      runrex(2);

      eosio_assert( rex_loans_available(), "rex loans are not currently available" );
      eosio_assert( payment.symbol == core_symbol() && fund.symbol == core_symbol(), "must use core token" );
      
      update_rex_account( from, asset( 0, core_symbol() ), asset( 0, core_symbol() ) );
      transfer_from_fund( from, payment + fund );

      auto itr = _rexpool.begin();
      eosio_assert( itr != _rexpool.end(), "rex system not initialized yet" );

      int64_t rented_tokens = 0;
      _rexpool.modify( itr, same_payer, [&]( auto& rt ) {
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

   /**
    * close_rex_order processes an incoming of already scheduled sellrex order. If REX pool has enough core
    * tokens (not frozen in loans), order can be filled. In this case, REX pool totals, user rex_balance
    * and user vote_stake are updated. However, user voting power is not updated inside this function. The
    * function returns success flag, order proceeds, and vote stake change. These are used later to finish
    * order processing, which includes transfering proceeds and updating user vote weight.
    */
   rex_order_outcome system_contract::close_rex_order( const rex_balance_table::const_iterator& bitr, const asset& rex )
   {
      auto rexitr = _rexpool.begin();
      const auto S0 = rexitr->total_lendable.amount;
      const auto R0 = rexitr->total_rex.amount;
      const auto R1 = R0 - rex.amount;
      const auto S1 = (uint128_t(R1) * S0) / R0;
      asset proceeds( S0 - S1, core_symbol() );
      asset stake_change( 0, core_symbol() );      
      bool success = false;
      
      if ( proceeds.amount <= rexitr->total_unlent.amount ) {
         const int64_t init_vote_stake_amount = bitr->vote_stake.amount;
         const int64_t current_stake_value = ( uint128_t(bitr->rex_balance.amount) * S0 ) / R0;
         _rexpool.modify( rexitr, same_payer, [&]( auto& rt ) {
            rt.total_rex.amount      = R1;
            rt.total_lendable.amount = S1;
            rt.total_unlent.amount   = rt.total_lendable.amount - rt.total_lent.amount;
         });
         _rexbalance.modify( bitr, same_payer, [&]( auto& rb ) {
            rb.vote_stake.amount   = current_stake_value - proceeds.amount;
            rb.rex_balance.amount -= rex.amount;
            rb.matured_rex        -= rex.amount;
         });
         stake_change.amount = bitr->vote_stake.amount - init_vote_stake_amount;
         success = true;
      } else {
         proceeds.amount = 0;
      }

      return { success, proceeds, stake_change };
   }

   template <typename T>
   void system_contract::fund_rex_loan( T& table, const name& from, uint64_t loan_num, const asset& payment  )
   {
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
   void system_contract::defund_rex_loan( T& table, const name& from, uint64_t loan_num, const asset& amount  )
   {
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

   void system_contract::transfer_from_fund( const name& owner, const asset& amount )
   {
      eosio_assert( 0 < amount.amount, "must transfer positive amount from REX fund" );
      auto itr = _rexfunds.require_find( owner.value, "must deposit to REX fund first" );
      eosio_assert( amount <= itr->balance, "insufficient funds");
      _rexfunds.modify( itr, same_payer, [&]( auto& fund ) {
         fund.balance.amount -= amount.amount;
      });
   }

   void system_contract::transfer_to_fund( const name& owner, const asset& amount )
   {
      eosio_assert( 0 < amount.amount, "must transfer positive amount to REX fund" );
      auto itr = _rexfunds.find( owner.value );
      if ( itr == _rexfunds.end() ) {
         _rexfunds.emplace( owner, [&]( auto& fund ) {
            fund.owner   = owner;
            fund.balance = amount;
         }); 
      } else {
         _rexfunds.modify( itr, same_payer, [&]( auto& fund ) {
            fund.balance.amount += amount.amount;
         });
      }
   }

   /**
    * update_rex_account checks if user has a scheduled sellrex order that has been closed, completes its processing,
    * and deletes it.
    * Processing entails transfering proceeds to user REX fund and updating user vote weight.
    * Additional proceeds and stake change can be passed as arguments.
    * This function is called only by actions pushed by owner, unlike close_rex_order.
    */
   asset system_contract::update_rex_account( const name& owner, const asset& proceeds, const asset& delta_stake, bool force_vote_update )
   {
      asset to_fund( proceeds );
      asset to_stake( delta_stake );
      asset rex_in_sell_order( 0, core_symbol() );
      auto itr = _rexorders.find( owner.value );
      if ( itr != _rexorders.end() && !itr->is_open ) {
         to_fund.amount  += itr->proceeds.amount;
         to_stake.amount += itr->stake_change.amount;
         _rexorders.erase( itr );
      } else if ( itr != _rexorders.end() ) { // itr->is_open is true
         rex_in_sell_order.amount = itr->rex_requested.amount;
      }

      if ( to_fund.amount > 0 )
         transfer_to_fund( owner, to_fund );
      if ( force_vote_update || to_stake.amount != 0 )
         update_voting_power( owner, to_stake );

      return rex_in_sell_order;
   }

   void system_contract::channel_to_rex( const name& from, const asset& amount )
   {
      if ( rex_available() ) {
         _rexpool.modify( _rexpool.begin(), same_payer, [&]( auto& rp ) {
            rp.total_unlent.amount   += amount.amount;
            rp.total_lendable.amount += amount.amount;
         });

         INLINE_ACTION_SENDER(eosio::token, transfer)( token_account, { from, active_permission },
            { from, rex_account, amount, std::string("transfer from ") + name{from}.to_string() + " to eosio.rex"} );
      }
   }

   void system_contract::channel_namebid_to_rex( const int64_t highest_bid )
   {
      if ( rex_available() ) {
         _rexpool.modify( _rexpool.begin(), same_payer, [&]( auto& rp ) {
            rp.namebid_proceeds.amount += highest_bid;
         });
      }
   }

   time_point_sec system_contract::get_rex_maturity()
   {
      const uint32_t num_of_maturity_buckets = 4;
      static const uint32_t now = current_time_point_sec().utc_seconds;
      static const uint32_t r = (current_time_point_sec().utc_seconds + 1) % seconds_per_day;
      static const time_point_sec rms{ now - r + (num_of_maturity_buckets + 1) * seconds_per_day };
      return rms;
   }

   void system_contract::process_rex_maturities( const rex_balance_table::const_iterator& bitr )
   {
      time_point_sec now = current_time_point_sec();
      _rexbalance.modify( bitr, same_payer, [&]( auto& rb ) {
         while ( !rb.rex_maturities.empty() && rb.rex_maturities.front().first <= now ) {
            rb.matured_rex += rb.rex_maturities.front().second;
            rb.rex_maturities.pop_front();
         }
      });
   }

   void system_contract::consolidate_rex_balance( const rex_balance_table::const_iterator& bitr,
                                                  const asset& rex_in_sell_order ) 
   {
      _rexbalance.modify( bitr, same_payer, [&]( auto& rb ) {
         int64_t total  = rb.matured_rex - rex_in_sell_order.amount;
         rb.matured_rex = rex_in_sell_order.amount;
         while ( !rb.rex_maturities.empty() ) {
            total += rb.rex_maturities.front().second;
            rb.rex_maturities.pop_front();
         }
         rb.rex_maturities.emplace_back( get_rex_maturity(), total );
      });
   }

   asset system_contract::add_to_rex_pool( const asset& payment )
   {
      const int64_t rex_ratio       = 10000;
      const int64_t init_total_rent = 100'000'0000; /// base amount prevents renting profitably until at least a minimum number of core_symbol() are made available
      asset rex_received( 0, rex_symbol );
      auto itr = _rexpool.begin();
      if ( !rex_system_initialized() ) {
         /// initialize REX pool
         _rexpool.emplace( _self, [&]( auto& rp ) {
            rex_received.amount = payment.amount * rex_ratio;

            rp.total_lendable   = payment;
            rp.total_lent       = asset( 0, core_symbol() );
            rp.total_unlent     = rp.total_lendable - rp.total_lent;
            rp.total_rent       = asset( init_total_rent, core_symbol() );
            rp.total_rex        = rex_received;
            rp.namebid_proceeds = asset( 0, core_symbol() );
         });
      } else if ( !rex_available() ) { /// should be a rare corner case, REX pool initialized but empty
         _rexpool.modify( itr, same_payer, [&]( auto& rp ) {
            rex_received.amount = payment.amount * rex_ratio;

            rp.total_lendable.amount = payment.amount;
            rp.total_lent.amount     = 0;
            rp.total_unlent.amount   = rp.total_lendable.amount - rp.total_lent.amount;
            rp.total_rent.amount     = init_total_rent;
            rp.total_rex.amount      = rex_received.amount;
         });
      } else {
         const auto S0 = itr->total_lendable.amount;
         const auto S1 = S0 + payment.amount;
         const auto R0 = itr->total_rex.amount;
         const auto R1 = (uint128_t(S1) * R0) / S0;

         rex_received.amount = R1 - R0;

         _rexpool.modify( itr, same_payer, [&]( auto& rp ) {
            rp.total_lendable.amount = S1;
            rp.total_rex.amount      = R1;
            rp.total_unlent.amount   = rp.total_lendable.amount - rp.total_lent.amount;
            eosio_assert( rp.total_unlent.amount >= 0, "programmer error, this should never go negative" );
         });
      }
      
      return rex_received;
   }

   asset system_contract::add_to_rex_balance( const name& owner, const asset& payment, const asset& rex_received )
   {
      auto bitr = _rexbalance.find( owner.value );
      asset init_rex_stake( 0, core_symbol() );
      asset current_rex_stake( 0, core_symbol() );
      if ( bitr == _rexbalance.end() ) {
         bitr = _rexbalance.emplace( owner, [&]( auto& rb ) {
            rb.owner       = owner;
            rb.vote_stake  = payment;
            rb.rex_balance = rex_received;
         });
         current_rex_stake.amount = payment.amount;
      } else {
         init_rex_stake.amount = bitr->vote_stake.amount;
         _rexbalance.modify( bitr, same_payer, [&]( auto& rb ) {
            rb.rex_balance.amount += rex_received.amount;
            rb.vote_stake.amount   = ( uint128_t(rb.rex_balance.amount) * _rexpool.begin()->total_lendable.amount ) 
                                     / _rexpool.begin()->total_rex.amount;
         });
         current_rex_stake.amount = bitr->vote_stake.amount;
      }

      process_rex_maturities( bitr );
      const time_point_sec maturity = get_rex_maturity();
      _rexbalance.modify( bitr, same_payer, [&]( auto& rb ) {
         if ( !rb.rex_maturities.empty() && rb.rex_maturities.back().first == maturity ) {
            rb.rex_maturities.back().second += rex_received.amount;
         } else {
            rb.rex_maturities.emplace_back( maturity, rex_received.amount );
         }
      });

      return current_rex_stake - init_rex_stake;
   }

}; /// namespace eosiosystem
