#include <eosio.system/eosio.system.hpp>
#include <eosiolib/dispatcher.hpp>
#include <eosiolib/crypto.h>

#include "producer_pay.cpp"
#include "delegate_bandwidth.cpp"
#include "voting.cpp"
#include "exchange_state.cpp"


namespace eosiosystem {

   system_contract::system_contract( account_name s )
   :native(s),
    _voters(_self,_self),
    _producers(_self,_self),
    _producers2(_self,_self),
    _global(_self,_self),
    _global2(_self,_self),
    _global3(_self,_self),
    _rammarket(_self,_self),
    _rextable(_self,_self),
    _rexbalance(_self,_self)
   {
      //print( "construct system\n" );
      _gstate  = _global.exists() ? _global.get() : get_default_parameters();
      _gstate2 = _global2.exists() ? _global2.get() : eosio_global_state2{};
      _gstate3 = _global3.exists() ? _global3.get() : eosio_global_state3{};

      auto itr = _rammarket.find(S(4,RAMCORE));

      if( itr == _rammarket.end() ) {
         auto system_token_supply   = eosio::token(N(eosio.token)).get_supply(eosio::symbol_type(system_token_symbol).name()).amount;
         if( system_token_supply > 0 ) {
            itr = _rammarket.emplace( _self, [&]( auto& m ) {
               m.supply.amount = 100000000000000ll;
               m.supply.symbol = S(4,RAMCORE);
               m.base.balance.amount = int64_t(_gstate.free_ram());
               m.base.balance.symbol = S(0,RAM);
               m.quote.balance.amount = system_token_supply / 1000;
               m.quote.balance.symbol = CORE_SYMBOL;
            });
         }
      } else {
         //print( "ram market already created" );
      }
   }

   eosio_global_state system_contract::get_default_parameters() {
      eosio_global_state dp;
      get_blockchain_parameters(dp);
      return dp;
   }

   time_point system_contract::current_time_point() {
      const static time_point ct{ microseconds{ static_cast<int64_t>( current_time() ) } };
      return ct;
   }

   block_timestamp system_contract::current_block_time() {
      const static block_timestamp cbt{ current_time_point() };
      return cbt;
   }

   system_contract::~system_contract() {
      _global.set( _gstate, _self );
      _global2.set( _gstate2, _self );
      _global3.set( _gstate3, _self );
   }

   void system_contract::setram( uint64_t max_ram_size ) {
      require_auth( _self );

      eosio_assert( _gstate.max_ram_size < max_ram_size, "ram may only be increased" ); /// decreasing ram might result market maker issues
      eosio_assert( max_ram_size < 1024ll*1024*1024*1024*1024, "ram size is unrealistic" );
      eosio_assert( max_ram_size > _gstate.total_ram_bytes_reserved, "attempt to set max below reserved" );

      auto delta = int64_t(max_ram_size) - int64_t(_gstate.max_ram_size);
      auto itr = _rammarket.find(S(4,RAMCORE));

      /**
       *  Increase the amount of ram for sale based upon the change in max ram size.
       */
      _rammarket.modify( itr, 0, [&]( auto& m ) {
         m.base.balance.amount += delta;
      });

      _gstate.max_ram_size = max_ram_size;
   }

   void system_contract::update_ram_supply() {
      auto cbt = current_block_time();

      if( cbt <= _gstate2.last_ram_increase ) return;

      auto itr = _rammarket.find(S(4,RAMCORE));
      auto new_ram = (cbt.slot - _gstate2.last_ram_increase.slot)*_gstate2.new_ram_per_block;
      _gstate.max_ram_size += new_ram;

      /**
       *  Increase the amount of ram for sale based upon the change in max ram size.
       */
      _rammarket.modify( itr, 0, [&]( auto& m ) {
         m.base.balance.amount += new_ram;
      });
      _gstate2.last_ram_increase = cbt;
   }

   /**
    *  Sets the rate of increase of RAM in bytes per block. It is capped by the uint16_t to
    *  a maximum rate of 3 TB per year.
    *
    *  If update_ram_supply hasn't been called for the most recent block, then new ram will
    *  be allocated at the old rate up to the present block before switching the rate.
    */
   void system_contract::setramrate( uint16_t bytes_per_block ) {
      require_auth( _self );

      update_ram_supply();
      _gstate2.new_ram_per_block = bytes_per_block;
   }

   void system_contract::setparams( const eosio::blockchain_parameters& params ) {
      require_auth( N(eosio) );
      (eosio::blockchain_parameters&)(_gstate) = params;
      eosio_assert( 3 <= _gstate.max_authority_depth, "max_authority_depth should be at least 3" );
      set_blockchain_parameters( params );
   }

   void system_contract::setpriv( account_name account, uint8_t ispriv ) {
      require_auth( _self );
      set_privileged( account, ispriv );
   }

   void system_contract::rmvproducer( account_name producer ) {
      require_auth( _self );
      auto prod = _producers.find( producer );
      eosio_assert( prod != _producers.end(), "producer not found" );
      _producers.modify( prod, 0, [&](auto& p) {
            p.deactivate();
         });
   }

   void system_contract::updtrevision( uint8_t revision ) {
      require_auth( _self );
      eosio_assert( revision == _gstate2.revision + 1, "can only increment revision by one" );
      eosio_assert( _gstate2.revision < 255, "can not increment revision" );
      _gstate2.revision = revision;
   }

   void system_contract::bidname( account_name bidder, account_name newname, asset bid ) {
      require_auth( bidder );
      eosio_assert( eosio::name_suffix(newname) == newname, "you can only bid on top-level suffix" );

      eosio_assert( newname != 0, "the empty name is not a valid account name to bid on" );
      eosio_assert( (newname & 0xFull) == 0, "13 character names are not valid account names to bid on" );
      eosio_assert( (newname & 0x1F0ull) == 0, "accounts with 12 character names and no dots can be created without bidding required" );
      eosio_assert( !is_account( newname ), "account already exists" );
      eosio_assert( bid.symbol == asset().symbol, "asset must be system token" );
      eosio_assert( bid.amount > 0, "insufficient bid" );

      INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {bidder,N(active)},
                                                    { bidder, N(eosio.names), bid, std::string("bid name ")+(name{newname}).to_string()  } );

      name_bid_table bids(_self,_self);
      print( name{bidder}, " bid ", bid, " on ", name{newname}, "\n" );
      auto current = bids.find( newname );
      if( current == bids.end() ) {
         bids.emplace( bidder, [&]( auto& b ) {
            b.newname = newname;
            b.high_bidder = bidder;
            b.high_bid = bid.amount;
            b.last_bid_time = current_time_point();
         });
      } else {
         eosio_assert( current->high_bid > 0, "this auction has already closed" );
         eosio_assert( bid.amount - current->high_bid > (current->high_bid / 10), "must increase bid by 10%" );
         eosio_assert( current->high_bidder != bidder, "account is already highest bidder" );

         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {N(eosio.names),N(active)},
                                                       { N(eosio.names), current->high_bidder, asset(current->high_bid),
                                                       std::string("refund bid on name ")+(name{newname}).to_string()  } );

         bids.modify( current, bidder, [&]( auto& b ) {
            b.high_bidder = bidder;
            b.high_bid = bid.amount;
            b.last_bid_time = current_time_point();
         });
      }
   }

   /**
    *  Called after a new account is created. This code enforces resource-limits rules
    *  for new accounts as well as new account naming conventions.
    *
    *  Account names containing '.' symbols must have a suffix equal to the name of the creator.
    *  This allows users who buy a premium name (shorter than 12 characters with no dots) to be the only ones
    *  who can create accounts with the creator's name as a suffix.
    *
    */
   void native::newaccount( account_name     creator,
                            account_name     newact
                            /*  no need to parse authorites
                            const authority& owner,
                            const authority& active*/ ) {

      if( creator != _self ) {
         auto tmp = newact >> 4;
         bool has_dot = false;

         for( uint32_t i = 0; i < 12; ++i ) {
           has_dot |= !(tmp & 0x1f);
           tmp >>= 5;
         }
         if( has_dot ) { // or is less than 12 characters
            auto suffix = eosio::name_suffix(newact);
            if( suffix == newact ) {
               name_bid_table bids(_self,_self);
               auto current = bids.find( newact );
               eosio_assert( current != bids.end(), "no active bid for name" );
               eosio_assert( current->high_bidder == creator, "only highest bidder can claim" );
               eosio_assert( current->high_bid < 0, "auction for name is not closed yet" );
               bids.erase( current );
            } else {
               eosio_assert( creator == suffix, "only suffix may create this account" );
            }
         }
      }

      user_resources_table  userres( _self, newact);

      userres.emplace( newact, [&]( auto& res ) {
        res.owner = newact;
      });

      set_resource_limits( newact, 0, 0, 0 );
   }

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
            rb.owner = from;
            rb.rex_balance = rex_received;
         });
      }
      else {
         _rexbalance.modify( bitr, 0, [&]( auto& rb ) {
            rb.rex_balance.amount  += rex_received.amount;
         });
      }
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
      if( result.first ) {
         INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), { N(eosio.rex), N(active) },
                                                       { N(eosio.rex), from, result.second, "sell REX" } );
      } else {
         rex_order_table rexorders(_self, _self);
         rexorders.emplace( from, [&]( auto& ordr ) {
            ordr.owner         = from;
            ordr.rex_requested = rex;
            ordr.order_time    = current_time_point();
         });
      }
   }

   void system_contract::cnclrexorder( account_name owner ) {
      require_auth( owner );
      rex_order_table rexorders(_self, _self);
      auto itr = rexorders.find( owner );
      eosio_assert( itr != rexorders.end(), "no unlendrex is scheduled" );
      rexorders.erase( itr );
   }

   void system_contract::claimrex( account_name owner ) {
      runrex(2);
      require_auth( owner );
      rex_order_table rexorders(_self, _self);
      auto itr = rexorders.find( owner );
      eosio_assert( itr != rexorders.end(), "no unlendrex is scheduled" );
      eosio_assert( !itr->is_open, "rex order hasn't been closed" );
      INLINE_ACTION_SENDER(eosio::token, transfer)( N(eosio.token), {N(eosio.rex),N(active)},
                                                    { N(eosio.rex), itr->owner, itr->proceeds, "sell REX" } );
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
         rented_tokens  = bancor_convert( rt.total_rent.amount, rt.total_unlent.amount, payment.amount );
         rt.total_lent.amount     += rented_tokens;
         rt.total_unlent.amount   += payment.amount;
         rt.total_lendable.amount += payment.amount;
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
            bancor_convert( rt.total_unlent.amount, rt.total_rent.amount, rented_tokens ); 
            rt.total_lent.amount = rt.total_lendable.amount - rt.total_unlent.amount;
         });
      };

      rex_cpu_loan_table cpu_loans(_self,_self);
      for( uint16_t i = 0; i < max; ++i ) {
         auto itr = cpu_loans.begin();
         if( itr == cpu_loans.end() ) break;
         if( itr->expiration.elapsed.count() > current_time() ) break;

         update_resource_limits( itr->receiver, -itr->total_staked.amount, 0 );
         unrent( itr->total_staked.amount );
         cpu_loans.erase( itr );
      }

      rex_net_loan_table net_loans(_self,_self);
      for( uint16_t i = 0; i < max; ++i ) {
         auto itr = net_loans.begin();
         if( itr == net_loans.end() ) break;
         if( itr->expiration.elapsed.count() > current_time() ) break;

         update_resource_limits( itr->receiver, 0, -itr->total_staked.amount );
         unrent( itr->total_staked.amount );
         net_loans.erase( itr );
      }

      rex_order_table rexorders(_self, _self);
      auto idx = rexorders.get_index<N(bytime)>();
      auto oitr = idx.begin();
      for( uint16_t i = 0; i < max; ++i ) {
         if( oitr == idx.end() || !oitr->is_open ) break;
         auto bitr = _rexbalance.find( oitr->owner );
         if( bitr == _rexbalance.end() ) {
            idx.erase( oitr++ );
            continue;
         }
         auto result = close_rex_order( bitr, oitr->rex_requested );
         auto next   = oitr;
         if( result.first ) {
            idx.modify( oitr, 0, [&]( auto& rt ) {
               rt.proceeds.amount = result.second.amount;
               rt.close();
            });
         }
         oitr = ++next;
      }

   }

   std::pair<bool, asset> system_contract::close_rex_order( const rex_balance_table::const_iterator& bitr, const asset& rex) {
      auto rexitr = _rextable.begin();
      const auto S0  = rexitr->total_lendable.amount;
      const auto R0  = rexitr->total_rex.amount;
      const auto R1  = R0 - rex.amount;
      const auto S1  = (uint128_t(R1) * S0) / R0;
      asset proceeds(S0-S1, CORE_SYMBOL);
      bool success = false;
      if( proceeds <= rexitr->total_unlent ) {
         _rextable.modify( rexitr, 0, [&]( auto& rt ) {
            rt.total_rex.amount      = R1;
            rt.total_lendable.amount = S1;
            rt.total_unlent.amount   = rt.total_lendable.amount - rt.total_lent.amount;
         });
         _rexbalance.modify( bitr, 0, [&]( auto& rb ) {
            rb.rex_balance.amount -= rex.amount;
         });
         success = true;
      }
      return std::make_pair(success, proceeds);
   }

   void native::setabi( account_name acnt, const bytes& abi ) {
      eosio::multi_index< N(abihash), abi_hash>  table(_self,_self);
      auto itr = table.find( acnt );
      if( itr == table.end() ) {
         table.emplace( acnt, [&]( auto& row ) {
            row.owner= acnt;
            sha256( const_cast<char*>(abi.data()), abi.size(), &row.hash );
         });
      } else {
         table.modify( itr, 0, [&]( auto& row ) {
            sha256( const_cast<char*>(abi.data()), abi.size(), &row.hash );
         });
      }
   }

} /// eosio.system


EOSIO_ABI( eosiosystem::system_contract,
     // native.hpp (newaccount definition is actually in eosio.system.cpp)
     (newaccount)(updateauth)(deleteauth)(linkauth)(unlinkauth)(canceldelay)(onerror)(setabi)
     // eosio.system.cpp
     (setram)(setramrate)(setparams)(setpriv)(rmvproducer)(updtrevision)(bidname)
     (lendrex)(unlendrex)(cnclrexorder)(claimrex)(rent)
     // delegate_bandwidth.cpp
     (buyrambytes)(buyram)(sellram)(delegatebw)(undelegatebw)(refund)
     // voting.cpp
     (regproducer)(unregprod)(voteproducer)(regproxy)
     // producer_pay.cpp
     (onblock)(claimrewards)
)
