/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio.system/native.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/privileged.hpp>
#include <eosiolib/singleton.hpp>
#include <eosio.system/exchange_state.hpp>

#include <string>

namespace eosiosystem {

   using eosio::asset;
   using eosio::indexed_by;
   using eosio::const_mem_fun;
   using eosio::block_timestamp;
   using eosio::time_point;
   using eosio::microseconds;

   struct name_bid {
     account_name            newname;
     account_name            high_bidder;
     int64_t                 high_bid = 0; ///< negative high_bid == closed auction waiting to be claimed
     time_point              last_bid_time;

     auto     primary_key()const { return newname;                          }
     uint64_t by_high_bid()const { return static_cast<uint64_t>(-high_bid); }
   };

   struct bid_refund {
      account_name bidder;
      asset        amount;

     auto primary_key() const { return bidder; }
   };

   typedef eosio::multi_index< N(namebids), name_bid,
                               indexed_by<N(highbid), const_mem_fun<name_bid, uint64_t, &name_bid::by_high_bid>  >
                               >  name_bid_table;

   typedef eosio::multi_index< N(bidrefunds), bid_refund> bid_refund_table;

   struct eosio_global_state : eosio::blockchain_parameters {
      uint64_t free_ram()const { return max_ram_size - total_ram_bytes_reserved; }

      uint64_t             max_ram_size = 64ll*1024 * 1024 * 1024;
      uint64_t             total_ram_bytes_reserved = 0;
      int64_t              total_ram_stake = 0;

      block_timestamp      last_producer_schedule_update;
      time_point           last_pervote_bucket_fill;
      int64_t              pervote_bucket = 0;
      int64_t              perblock_bucket = 0;
      uint32_t             total_unpaid_blocks = 0; /// all blocks which have been produced but not paid
      int64_t              total_activated_stake = 0;
      time_point           thresh_activated_stake_time;
      uint16_t             last_producer_schedule_size = 0;
      double               total_producer_vote_weight = 0; /// the sum of all producer votes
      block_timestamp      last_name_close;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE_DERIVED( eosio_global_state, eosio::blockchain_parameters,
                                (max_ram_size)(total_ram_bytes_reserved)(total_ram_stake)
                                (last_producer_schedule_update)(last_pervote_bucket_fill)
                                (pervote_bucket)(perblock_bucket)(total_unpaid_blocks)(total_activated_stake)(thresh_activated_stake_time)
                                (last_producer_schedule_size)(total_producer_vote_weight)(last_name_close) )
   };

   /**
    * Defines new global state parameters added after version 1.0
    */
   struct eosio_global_state2 {
      eosio_global_state2(){}

      uint16_t          new_ram_per_block = 0;
      block_timestamp   last_ram_increase;
      block_timestamp   last_block_num; /* deprecated */
      double            total_producer_votepay_share = 0;
      uint8_t           revision = 0; ///< used to track version updates in the future.

      EOSLIB_SERIALIZE( eosio_global_state2, (new_ram_per_block)(last_ram_increase)(last_block_num)
                        (total_producer_votepay_share)(revision) )
   };

   struct eosio_global_state3 {
      eosio_global_state3() { }
      time_point        last_vpay_state_update;
      double            total_vpay_share_change_rate = 0;

      EOSLIB_SERIALIZE( eosio_global_state3, (last_vpay_state_update)(total_vpay_share_change_rate) )
   };

   struct producer_info {
      account_name          owner;
      double                total_votes = 0;
      eosio::public_key     producer_key; /// a packed public key object
      bool                  is_active = true;
      std::string           url;
      uint32_t              unpaid_blocks = 0;
      time_point            last_claim_time;
      uint16_t              location = 0;

      uint64_t primary_key()const { return owner;                                   }
      double   by_votes()const    { return is_active ? -total_votes : total_votes;  }
      bool     active()const      { return is_active;                               }
      void     deactivate()       { producer_key = public_key(); is_active = false; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( producer_info, (owner)(total_votes)(producer_key)(is_active)(url)
                        (unpaid_blocks)(last_claim_time)(location) )
   };

   struct producer_info2 {
      account_name    owner;
      double          votepay_share = 0;
      time_point      last_votepay_share_update;

      uint64_t primary_key()const { return owner; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( producer_info2, (owner)(votepay_share)(last_votepay_share_update) )
   };

   struct voter_info {
      account_name                owner = 0; /// the voter
      account_name                proxy = 0; /// the proxy set by the voter, if any
      std::vector<account_name>   producers; /// the producers approved by this voter if no proxy set
      int64_t                     staked = 0;

      /**
       *  Every time a vote is cast we must first "undo" the last vote weight, before casting the
       *  new vote weight.  Vote weight is calculated as:
       *
       *  stated.amount * 2 ^ ( weeks_since_launch/weeks_per_year)
       */
      double                      last_vote_weight = 0; /// the vote weight cast the last time the vote was updated

      /**
       * Total vote weight delegated to this voter.
       */
      double                      proxied_vote_weight= 0; /// the total vote weight delegated to this voter as a proxy
      bool                        is_proxy = 0; /// whether the voter is a proxy for others


      uint32_t                    reserved1 = 0;
      time                        reserved2 = 0;
      eosio::asset                reserved3;

      uint64_t primary_key()const { return owner; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( voter_info, (owner)(proxy)(producers)(staked)(last_vote_weight)(proxied_vote_weight)(is_proxy)(reserved1)(reserved2)(reserved3) )
   };

   typedef eosio::multi_index< N(voters), voter_info>  voters_table;


   typedef eosio::multi_index< N(producers), producer_info,
                               indexed_by<N(prototalvote), const_mem_fun<producer_info, double, &producer_info::by_votes>  >
                               >  producers_table;
   typedef eosio::multi_index< N(producers2), producer_info2 > producers_table2;

   typedef eosio::singleton<N(global), eosio_global_state> global_state_singleton;
   typedef eosio::singleton<N(global2), eosio_global_state2> global_state2_singleton;
   typedef eosio::singleton<N(global3), eosio_global_state3> global_state3_singleton;

   static constexpr uint32_t     seconds_per_day = 24 * 3600;
   static constexpr uint64_t     system_token_symbol = CORE_SYMBOL;

   struct rex_pool {
      asset      total_lent; /// total EOS in open rex_loans
      asset      total_unlent; /// total EOS available to be lent (connector)
      asset      total_rent; /// fees received in exchange for lent  (connector)
      asset      total_lendable; /// total EOS that have been lent (total_unlent + total_lent)
      asset      total_rex; /// total number of REX shares allocated to contributors to total_lendable
      asset      namebid_proceeds; /// EOS to be transferred from namebids to REX pool
      uint64_t   loan_num = 0; /// increments with each new loan
      uint64_t primary_key()const { return 0; }
   };

   typedef eosio::multi_index< N(rexpool), rex_pool > rex_pool_table;

   struct rex_balance {
      account_name owner;
      asset        vote_stake; /// the amount of CORE_SYMBOL currently included in owner's vote
      asset        rex_balance; /// the amount of REX owned by owner

      uint64_t primary_key()const { return owner; }
   };

   typedef eosio::multi_index< N(rexbal), rex_balance > rex_balance_table;

   struct rex_loan {
      account_name        from;
      account_name        receiver;
      asset               loan_payment;
      asset               total_staked;
      uint64_t            loan_num;
      eosio::time_point   expiration;
      
      bool                auto_renew = false;
      asset               balance;

      uint64_t primary_key()const { return loan_num;                   }
      uint64_t by_expr()const     { return expiration.elapsed.count(); }
      uint64_t by_owner()const    { return from;                       }
   };

   typedef eosio::multi_index< N(cpuloan), rex_loan,
                               indexed_by<N(byexpr),  const_mem_fun<rex_loan, uint64_t, &rex_loan::by_expr>>,
                               indexed_by<N(byowner), const_mem_fun<rex_loan, uint64_t, &rex_loan::by_owner>>
                             > rex_cpu_loan_table;

   typedef eosio::multi_index< N(netloan), rex_loan,
                               indexed_by<N(byexpr),  const_mem_fun<rex_loan, uint64_t, &rex_loan::by_expr>>,
                               indexed_by<N(byowner), const_mem_fun<rex_loan, uint64_t, &rex_loan::by_owner>>
                             > rex_net_loan_table;

   struct loan_refund {
      account_name  owner;
      asset         balance;
         
      uint64_t primary_key()const { return owner; }
   };

   typedef eosio::multi_index< N(loanrefunds), loan_refund > loan_refund_table;

   struct rex_order {
      account_name        owner;
      asset               rex_requested;
      asset               proceeds;
      asset               unstake_quant;
      eosio::time_point   order_time;
      bool                is_open = true;
      
      void close()            { is_open = false; }
      auto primary_key()const { return owner;    }
      uint64_t by_time()const { return is_open ? order_time.elapsed.count() : -order_time.elapsed.count(); }
   };

   typedef eosio::multi_index< N(rexqueue), rex_order,
                               indexed_by<N(bytime), const_mem_fun<rex_order, uint64_t, &rex_order::by_time>>> rex_order_table;

   class system_contract : public native {
      private:
         voters_table            _voters;
         producers_table         _producers;
         producers_table2        _producers2;
         global_state_singleton  _global;
         global_state2_singleton _global2;
         global_state3_singleton _global3;
         eosio_global_state      _gstate;
         eosio_global_state2     _gstate2;
         eosio_global_state3     _gstate3;
         rammarket               _rammarket;
         rex_pool_table          _rextable;
         rex_balance_table       _rexbalance;

      public:
         system_contract( account_name s );
         ~system_contract();

         // Actions:
         void onblock( block_timestamp timestamp, account_name producer );
                      // const block_header& header ); /// only parse first 3 fields of block header

         void setalimits( account_name act, int64_t ram, int64_t net, int64_t cpu );
         // functions defined in delegate_bandwidth.cpp

         /**
          *  Stakes SYS from the balance of 'from' for the benfit of 'receiver'.
          *  If transfer == true, then 'receiver' can unstake to their account
          *  Else 'from' can unstake at any time.
          */
         void delegatebw( account_name from, account_name receiver,
                          asset stake_net_quantity, asset stake_cpu_quantity, bool transfer );


         /**
          * Transfers SYS tokens from user balance and credits converts them to REX stake.
          */
         void buyrex( account_name from, asset amount );

         /**
          * Converts REX stake back into SYS tokens at current exchange rate. If order cannot be 
          * processed, it gets queued until it can be there is enough REX to fill order.
          */
         void sellrex( account_name from, asset rex );
         
         /**
          * Cancels queued sellrex order.
          */
         void cnclrexorder( account_name owner );

         /**
          * Transfers processed sellrex order that had been queued proceeds to owner account. Fails if 
          * order hasn't been filled.
          */
         void claimrex( account_name owner );

         /**
          * Use payment to rent as many SYS tokens as possible and stake them for either cpu or net for the benefit of receiver,
          * after 30 days the rented SYS delegation of CPU or NET will expire unless auto_renew == true.
          * If auto_renew == true, loan creator can fund that specific loan. Upon expiration, if loan has enough funds, it 
          * gets renewed at current market price, otherwise, the loan is closed and remaining balance if refunded to loan 
          * creator. User claims the refund in a separate action.
          */
         void rentcpu( account_name from, account_name receiver, asset payment, bool auto_renew );
         void rentnet( account_name from, account_name receiver, asset payment, bool auto_renew );

         /**
          * Loan initiator funds a given CPU or NET loan. Loan must've been set as autorenew.
          */
         void fundcpuloan( account_name from, uint64_t loan_num, asset payment );
         void fundnetloan( account_name from, uint64_t loan_num, asset payment );

         /**
          * Transfers remaining balance of closed auto-renew loans to owner account.
          */
         void claimrefund( account_name owner );
         
         /**
          * Updates REX vote stake of owner to its current value.
          */
         void updaterex( account_name owner );

         /**
          *  Decreases the total tokens delegated by from to receiver and/or
          *  frees the memory associated with the delegation if there is nothing
          *  left to delegate.
          *
          *  This will cause an immediate reduction in net/cpu bandwidth of the
          *  receiver.
          *
          *  A transaction is scheduled to send the tokens back to 'from' after
          *  the staking period has passed. If existing transaction is scheduled, it
          *  will be canceled and a new transaction issued that has the combined
          *  undelegated amount.
          *
          *  The 'from' account loses voting power as a result of this call and
          *  all producer tallies are updated.
          */
         void undelegatebw( account_name from, account_name receiver,
                            asset unstake_net_quantity, asset unstake_cpu_quantity );


         /**
          * Increases receiver's ram quota based upon current price and quantity of
          * tokens provided. An inline transfer from receiver to system contract of
          * tokens will be executed.
          */
         void buyram( account_name buyer, account_name receiver, asset tokens );
         void buyrambytes( account_name buyer, account_name receiver, uint32_t bytes );

         /**
          *  Reduces quota my bytes and then performs an inline transfer of tokens
          *  to receiver based upon the average purchase price of the original quota.
          */
         void sellram( account_name receiver, int64_t bytes );

         /**
          *  This action is called after the delegation-period to claim all pending
          *  unstaked tokens belonging to owner
          */
         void refund( account_name owner );

         // functions defined in voting.cpp

         void regproducer( const account_name producer, const public_key& producer_key, const std::string& url, uint16_t location );

         void unregprod( const account_name producer );

         void setram( uint64_t max_ram_size );
         void setramrate( uint16_t bytes_per_block );

         void voteproducer( const account_name voter, const account_name proxy, const std::vector<account_name>& producers );

         void regproxy( const account_name proxy, bool isproxy );

         void setparams( const eosio::blockchain_parameters& params );

         // functions defined in producer_pay.cpp
         void claimrewards( const account_name& owner );

         void setpriv( account_name account, uint8_t ispriv );

         void rmvproducer( account_name producer );

         void updtrevision( uint8_t revision );

         void bidname( account_name bidder, account_name newname, asset bid );

         void bidrefund( account_name bidder, account_name newname );

      private:
         // Implementation details:

         // defined in eosio.system.cpp
         static eosio_global_state get_default_parameters();
         static time_point current_time_point();
         static block_timestamp current_block_time();
         void update_ram_supply();
         // defined in rex.cpp
         void runrex( uint16_t max );
         std::tuple<bool, int64_t, int64_t> close_rex_order( const rex_balance_table::const_iterator& bitr, const asset& rex );
         void deposit_rex( const account_name& from, const asset& amount );
         template <typename T>
         int64_t rentrex( T& table, account_name from, account_name receiver, const asset& payment, bool auto_renew,
                          const std::string& memo );
         template <typename T>
         void fundrexloan( T& table, account_name from, uint64_t loan_num, const asset& payment, const std::string& memo );

         // defined in delegate_bandwidth.cpp
         void changebw( account_name from, account_name receiver,
                        asset stake_net_quantity, asset stake_cpu_quantity, bool transfer );
         void update_resource_limits( account_name receiver, int64_t delta_cpu, int64_t delta_net );
         void update_voting_power( const account_name& voter, const asset& total_update );

         // defined in voting.hpp
         void update_elected_producers( block_timestamp timestamp );
         void update_votes( const account_name voter, const account_name proxy, const std::vector<account_name>& producers, bool voting );
         void propagate_weight_change( const voter_info& voter );
         double update_producer_votepay_share( const producers_table2::const_iterator& prod_itr,
                                               time_point ct,
                                               double shares_rate, bool reset_to_zero = false );
         double update_total_votepay_share( time_point ct,
                                            double additional_shares_delta = 0.0, double shares_rate_delta = 0.0 );
   };

} /// eosiosystem
