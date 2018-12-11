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

#include <cmath>  
#include <string>

namespace eosiosystem {

   using eosio::name;
   using eosio::asset;
   using eosio::symbol;
   using eosio::symbol_code;
   using eosio::indexed_by;
   using eosio::const_mem_fun;
   using eosio::block_timestamp;
   using eosio::time_point;
   using eosio::microseconds;
   using eosio::datastream;

   const uint32_t block_num_network_activation = 1000000; 

   struct[[ eosio::table, eosio::contract("eosio.system") ]] payment_info {
     name bp;
     asset pay;

     uint64_t primary_key() const { return bp.value; }
     EOSLIB_SERIALIZE(payment_info, (bp)(pay))
   };

   typedef eosio::multi_index< "payments"_n, payment_info > payments_table;

   struct [[eosio::table("schedulemetr"), eosio::contract("eosio.system")]] schedule_metrics_state {
     name                     last_onblock_caller;
     int32_t                          block_counter_correction;  
     std::vector<producer_metric>     producers_metric;

     uint64_t primary_key()const { return last_onblock_caller.value; }
     // explicit serialization macro is not necessary, used here only to improve compilation time
     EOSLIB_SERIALIZE(schedule_metrics_state, (last_onblock_caller)(block_counter_correction)(producers_metric))
   };

   typedef eosio::singleton< "schedulemetr"_n, schedule_metrics_state > schedule_metrics_singleton;
   
   struct [[eosio::table("rotations"), eosio::contract("eosio.system")]] rotation_state {
      // bool                            is_rotation_active = true;
      name                    bp_currently_out;
      name                    sbp_currently_in;
      uint32_t                bp_out_index;
      uint32_t                sbp_in_index;
      block_timestamp         next_rotation_time;
      block_timestamp         last_rotation_time;

      //NOTE: This might not be the best place for this information

      // bool                            is_kick_active = true;
      // account_name                    last_onblock_caller;
      // block_timestamp                 last_time_block_produced;
      
      EOSLIB_SERIALIZE( rotation_state, /*(is_rotation_active)*/(bp_currently_out)(sbp_currently_in)(bp_out_index)(sbp_in_index)(next_rotation_time)
                        (last_rotation_time)/*(is_kick_active)(last_onblock_caller)(last_time_block_produced)*/ )
   };

   typedef eosio::singleton< "rotations"_n, rotation_state> rotation_singleton;

   struct [[eosio::table, eosio::contract("eosio.system")]] name_bid {
     name            newname;
     name            high_bidder;
     int64_t         high_bid = 0; ///< negative high_bid == closed auction waiting to be claimed
     time_point      last_bid_time;

     uint64_t primary_key()const { return newname.value;                    }
     uint64_t by_high_bid()const { return static_cast<uint64_t>(-high_bid); }
   };

   struct [[eosio::table, eosio::contract("eosio.system")]] bid_refund {
      name         bidder;
      asset        amount;

      uint64_t primary_key()const { return bidder.value; }
   };

   typedef eosio::multi_index< "namebids"_n, name_bid,
                               indexed_by<"highbid"_n, const_mem_fun<name_bid, uint64_t, &name_bid::by_high_bid>  >
                             > name_bid_table;

   typedef eosio::multi_index< "bidrefunds"_n, bid_refund > bid_refund_table;

   struct [[eosio::table("global"), eosio::contract("eosio.system")]] eosio_global_state : eosio::blockchain_parameters {
      uint64_t free_ram()const { return max_ram_size - total_ram_bytes_reserved; }

      uint64_t             max_ram_size = 12ll*1024 * 1024 * 1024;
      uint64_t             total_ram_bytes_reserved = 0;
      int64_t              total_ram_stake = 0;

      block_timestamp      last_producer_schedule_update;
      block_timestamp      last_proposed_schedule_update;
      time_point           last_pervote_bucket_fill;
      int64_t              pervote_bucket = 0;
      int64_t              perblock_bucket = 0;
      uint32_t             total_unpaid_blocks = 0; /// all blocks which have been produced but not paid
      int64_t              total_activated_stake = 0;
      time_point           thresh_activated_stake_time;
      uint16_t             last_producer_schedule_size = 0;
      double               total_producer_vote_weight = 0; /// the sum of all producer votes
      block_timestamp      last_name_close;
      uint32_t             block_num = 12;
      uint32_t             last_claimrewards = 0;
      uint32_t             next_payment = 0;
      uint16_t             new_ram_per_block = 0;
      block_timestamp      last_ram_increase;
      block_timestamp      last_block_num; /* deprecated */
      double               total_producer_votepay_share = 0;
      uint8_t              revision = 0; ///< used to track version updates in the future.

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE_DERIVED( eosio_global_state, eosio::blockchain_parameters,
                                (max_ram_size)(total_ram_bytes_reserved)(total_ram_stake)
                                (last_producer_schedule_update)(last_proposed_schedule_update)(last_pervote_bucket_fill)
                                (pervote_bucket)(perblock_bucket)(total_unpaid_blocks)(total_activated_stake)(thresh_activated_stake_time)
                                (last_producer_schedule_size)(total_producer_vote_weight)(last_name_close)(block_num)(last_claimrewards)(next_payment)
                                (new_ram_per_block)(last_ram_increase)(last_block_num)(total_producer_votepay_share)(revision) )
   };

  enum class kick_type {
     REACHED_TRESHOLD = 1,
    //  PREVENT_LIB_STOP_MOVING = 2,
     BPS_VOTING = 2
   };

   struct [[eosio::table, eosio::contract("eosio.system")]] producer_info {
      name                  owner;
      double                total_votes = 0;
      eosio::public_key     producer_key; /// a packed public key object
      bool                  is_active = true;
      std::string           unreg_reason;
      std::string           url;
      uint32_t              unpaid_blocks = 0;
      uint32_t              lifetime_produced_blocks = 0;
      uint32_t              missed_blocks_per_rotation = 0;
      uint32_t              lifetime_missed_blocks = 0;
      time_point            last_claim_time;
      uint16_t              location = 0;
      
      uint32_t              kick_reason_id = 0;
      std::string           kick_reason;
      uint32_t              times_kicked = 0;
      uint32_t              kick_penalty_hours = 0; 
      block_timestamp       last_time_kicked;

      uint64_t primary_key()const { return owner.value;                             }
      double   by_votes()const    { return is_active ? -total_votes : total_votes;  }
      bool     active()const      { return is_active;                               }
      void     deactivate()       { producer_key = public_key(); is_active = false; }

      void kick(kick_type kt, uint32_t penalty = 0) {
        times_kicked++;
        last_time_kicked = block_timestamp(eosio::time_point(eosio::microseconds(int64_t(current_time()))));
        
        if(penalty == 0) kick_penalty_hours  = uint32_t(std::pow(2, times_kicked));
        
        switch(kt) {
          case kick_type::REACHED_TRESHOLD:
            kick_reason_id = uint32_t(kick_type::REACHED_TRESHOLD);
            kick_reason = "Producer account was deactivated because it reached the maximum missed blocks in this rotation timeframe.";
          break;
          // case kick_type::PREVENT_LIB_STOP_MOVING:
          //   kick_reason_id = uint32_t(kick_type::PREVENT_LIB_STOP_MOVING);
          //   kick_reason = "Producer account was deactivated to prevent the LIB from halting.";
          // break;
          case kick_type::BPS_VOTING:
            kick_reason_id = uint32_t(kick_type::BPS_VOTING);
            kick_reason = "Producer account was deactivated by vote.";
            kick_penalty_hours = penalty;
          break;
        }
        lifetime_missed_blocks += missed_blocks_per_rotation;
        missed_blocks_per_rotation = 0;
        // print("\nblock producer: ", name{owner}, " was kicked.");
        deactivate();
      } 
      

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( producer_info, (owner)(total_votes)(producer_key)(is_active)(unreg_reason)(url)
                        (unpaid_blocks)(lifetime_produced_blocks)(missed_blocks_per_rotation)(lifetime_missed_blocks)(last_claim_time)
                        (location)(kick_reason_id)(kick_reason)(times_kicked)(kick_penalty_hours)(last_time_kicked) )
   };

   struct [[eosio::table, eosio::contract("eosio.system")]] voter_info {
      name                owner;     /// the voter
      name                proxy;     /// the proxy set by the voter, if any
      std::vector<name>   producers; /// the producers approved by this voter if no proxy set
      int64_t             staked = 0;
      int64_t             last_stake = 0;

      /**
       *  Every time a vote is cast we must first "undo" the last vote weight, before casting the
       *  new vote weight.  Vote weight is calculated as:
       *
       *  stated.amount * 2 ^ ( weeks_since_launch/weeks_per_year)
       */
      double              last_vote_weight = 0; /// the vote weight cast the last time the vote was updated

      /**
       * Total vote weight delegated to this voter.
       */
      double              proxied_vote_weight= 0; /// the total vote weight delegated to this voter as a proxy
      bool                is_proxy = 0; /// whether the voter is a proxy for others


      uint32_t            reserved1 = 0;
      uint32_t            reserved2 = 0;
      eosio::asset        reserved3;
      uint64_t primary_key()const { return owner.value; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( voter_info, (owner)(proxy)(producers)(staked)(last_stake)(last_vote_weight)(proxied_vote_weight)(is_proxy)(reserved1)(reserved2)(reserved3) )
   };

   typedef eosio::multi_index< "voters"_n, voter_info >  voters_table;


   typedef eosio::multi_index< "producers"_n, producer_info,
                               indexed_by<"prototalvote"_n, const_mem_fun<producer_info, double, &producer_info::by_votes>  >
                             > producers_table;
   
   typedef eosio::singleton< "global"_n, eosio_global_state >   global_state_singleton;

   //   static constexpr uint32_t     max_inflation_rate = 5;  // 5% annual inflation
   static constexpr uint32_t     seconds_per_day = 24 * 3600;

   class [[eosio::contract("eosio.system")]] system_contract : public native {
      private:
         voters_table                _voters;
         producers_table             _producers;
         global_state_singleton      _global;
         eosio_global_state          _gstate;
         rammarket                   _rammarket;

         schedule_metrics_singleton  _schedule_metrics;
         schedule_metrics_state      _gschedule_metrics;
         rotation_singleton          _rotation;
         rotation_state              _grotation;
         payments_table              _payments;

      public:
         static constexpr eosio::name active_permission{"active"_n};
         static constexpr eosio::name token_account{"eosio.token"_n};
         static constexpr eosio::name ram_account{"eosio.ram"_n};
         static constexpr eosio::name ramfee_account{"eosio.ramfee"_n};
         static constexpr eosio::name stake_account{"eosio.stake"_n};
         static constexpr eosio::name bpay_account{"eosio.bpay"_n};
         static constexpr eosio::name vpay_account{"eosio.vpay"_n};
         static constexpr eosio::name names_account{"eosio.names"_n};
         static constexpr eosio::name saving_account{"eosio.saving"_n};
         static constexpr symbol ramcore_symbol = symbol(symbol_code("RAMCORE"), 4);
         static constexpr symbol ram_symbol     = symbol(symbol_code("RAM"), 0);

         system_contract( name s, name code, datastream<const char*> ds );
         ~system_contract();

         static symbol get_core_symbol( name system_account = "eosio"_n ) {
            rammarket rm(system_account, system_account.value);
            const static auto sym = get_core_symbol( rm );
            return sym;
         }

         // Actions:
         [[eosio::action]]
         void init( unsigned_int version, symbol core );
         [[eosio::action]]
         void onblock( ignore<block_header> header );

         [[eosio::action]]
         void setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight );
         // functions defined in delegate_bandwidth.cpp

         /**
          *  Stakes SYS from the balance of 'from' for the benfit of 'receiver'.
          *  If transfer == true, then 'receiver' can unstake to their account
          *  Else 'from' can unstake at any time.
          */
         [[eosio::action]]
         void delegatebw( name from, name receiver,
                          asset stake_net_quantity, asset stake_cpu_quantity, bool transfer );


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
         [[eosio::action]]
         void undelegatebw( name from, name receiver,
                            asset unstake_net_quantity, asset unstake_cpu_quantity );

        
         /**
          * Increases receiver's ram quota based upon current price and quantity of
          * tokens provided. An inline transfer from receiver to system contract of
          * tokens will be executed.
          */
         [[eosio::action]]
         void buyram( name payer, name receiver, asset quant );
         [[eosio::action]]
         void buyrambytes( name payer, name receiver, uint32_t bytes );

         /**
          *  Reduces quota my bytes and then performs an inline transfer of tokens
          *  to receiver based upon the average purchase price of the original quota.
          */
         [[eosio::action]]
         void sellram( name account, int64_t bytes );

         /**
          *  This action is called after the delegation-period to claim all pending
          *  unstaked tokens belonging to owner
          */
         [[eosio::action]]
         void refund( name owner );

         // functions defined in voting.cpp

         [[eosio::action]]
         void regproducer( const name producer, const public_key& producer_key, const std::string& url, uint16_t location );

         [[eosio::action]]
         void unregprod( const name producer );

         [[eosio::action]]
         void unregreason( const name producer, std::string reason );

         [[eosio::action]]
         void setram( uint64_t max_ram_size );
         [[eosio::action]]
         void setramrate( uint16_t bytes_per_block );

         [[eosio::action]]
         void voteproducer( const name voter, const name proxy, const std::vector<name>& producers );

         [[eosio::action]]
         void regproxy( const name proxy, bool isproxy );

         [[eosio::action]]
         void setparams( const eosio::blockchain_parameters& params );

         // functions defined in producer_pay.cpp
         [[eosio::action]]
         void claimrewards( const name owner );

         [[eosio::action]]
         void setpriv( name account, uint8_t is_priv );

         [[eosio::action]]
         void rmvproducer( name producer );

         [[eosio::action]]
         void updtrevision( uint8_t revision );

         [[eosio::action]]
         void bidname( name bidder, name newname, asset bid );

         [[eosio::action]]
         void bidrefund( name bidder, name newname );

         [[eosio::action]]
         void votebpout(name bp, uint32_t penalty_hours);

      private:
         // Implementation details:

         static symbol get_core_symbol( const rammarket& rm ) {
            auto itr = rm.find(ramcore_symbol.raw());
            eosio_assert(itr != rm.end(), "system contract must first be initialized");
            return itr->quote.balance.symbol;
         }

         //defined in eosio.system.cpp
         static eosio_global_state get_default_parameters();
         static time_point current_time_point();
         static block_timestamp current_block_time();
         

         symbol core_symbol()const;

         void update_ram_supply();

         //defined in delegate_bandwidth.cpp
         void changebw( name from, name receiver,
                        asset stake_net_quantity, asset stake_cpu_quantity, bool transfer );

         // defined in producer_pay.cpp 
         void claimrewards_snapshot(); 

         // defined in voting.cpp
         void update_elected_producers( block_timestamp timestamp );
         void update_votes( const name voter, const name proxy, const std::vector<name>& producers, bool voting );
         void propagate_weight_change( const voter_info& voter );
         double inverse_vote_weight(double staked, double amountVotedProducers);
         void recalculate_votes();

         //defined in system_kick.cpp 
         bool crossed_missed_blocks_threshold(uint32_t amountBlocksMissed, uint32_t schedule_size);
         void reset_schedule_metrics(name producer);
         void update_producer_missed_blocks(name producer);
         bool is_new_schedule_activated(capi_name active_schedule[], uint32_t size);
         bool check_missed_blocks(block_timestamp timestamp, name producer);

         //define in system_rotation.cpp
         void set_bps_rotation(name bpOut, name sbpIn); 
         void update_rotation_time(block_timestamp block_time);
         void update_missed_blocks_per_rotation();
         void restart_missed_blocks_per_rotation(std::vector<eosio::producer_key> prods);
         bool is_in_range(int32_t index, int32_t low_bound, int32_t up_bound);
         std::vector<eosio::producer_key> check_rotation_state(std::vector<eosio::producer_key> producers, block_timestamp block_time);
   };

} /// eosiosystem
