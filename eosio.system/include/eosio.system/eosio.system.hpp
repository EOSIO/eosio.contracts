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
#include <type_traits>
#include <optional>

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

   /**
    * @defgroup eosiosystem eosio.system
    * @ingroup eosiocontracts
    * eosio.system contract defines the structures and actions needed for blockchain's core functionality.
    * @{
    */

   template<typename E, typename F>
   static inline auto has_field( F flags, E field )
   -> std::enable_if_t< std::is_integral_v<F> && std::is_unsigned_v<F> &&
                        std::is_enum_v<E> && std::is_same_v< F, std::underlying_type_t<E> >, bool>
   {
      return ( (flags & static_cast<F>(field)) != 0 );
   }

   template<typename E, typename F>
   static inline auto set_field( F flags, E field, bool value = true )
   -> std::enable_if_t< std::is_integral_v<F> && std::is_unsigned_v<F> &&
                        std::is_enum_v<E> && std::is_same_v< F, std::underlying_type_t<E> >, F >
   {
      if( value )
         return ( flags | static_cast<F>(field) );
      else
         return ( flags & ~static_cast<F>(field) );
   }

   /**
    * A name bid.
    * 
    * @details A name bid consists of:
    * - a `newname` name that the bid is for
    * - a `higher_bidder` account name that is the one with the highest bid so far
    * - the `high_bid` which is amount of highest bid
    * - and `last_bid_time` which is the time of the highest bid
    */
   struct [[eosio::table, eosio::contract("eosio.system")]] name_bid {
     name            newname;
     name            high_bidder;
     int64_t         high_bid = 0; ///< negative high_bid == closed auction waiting to be claimed
     time_point      last_bid_time;

     uint64_t primary_key()const { return newname.value;                    }
     uint64_t by_high_bid()const { return static_cast<uint64_t>(-high_bid); }
   };

   /**
    * A bid refund.
    * 
    * @details A bid refund is defined by:
    * - the `bidder` account name owning the refund
    * - the `amount` to be refunded
    */
   struct [[eosio::table, eosio::contract("eosio.system")]] bid_refund {
      name         bidder;
      asset        amount;

      uint64_t primary_key()const { return bidder.value; }
   };

   /**
    * Name bid table
    * 
    * @details The name bid table is storing all the `name_bid`s instances.
    */
   typedef eosio::multi_index< "namebids"_n, name_bid,
                               indexed_by<"highbid"_n, const_mem_fun<name_bid, uint64_t, &name_bid::by_high_bid>  >
                             > name_bid_table;

   /**
    * Bid refund table.
    * 
    * @details The bid refund table is storing all the `bid_refund`s instances.
    */
   typedef eosio::multi_index< "bidrefunds"_n, bid_refund > bid_refund_table;

   /**
    * Defines new global state parameters.
    */
   struct [[eosio::table("global"), eosio::contract("eosio.system")]] eosio_global_state : eosio::blockchain_parameters {
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
   struct [[eosio::table("global2"), eosio::contract("eosio.system")]] eosio_global_state2 {
      eosio_global_state2(){}

      uint16_t          new_ram_per_block = 0;
      block_timestamp   last_ram_increase;
      block_timestamp   last_block_num; /* deprecated */
      double            total_producer_votepay_share = 0;
      uint8_t           revision = 0; ///< used to track version updates in the future.

      EOSLIB_SERIALIZE( eosio_global_state2, (new_ram_per_block)(last_ram_increase)(last_block_num)
                        (total_producer_votepay_share)(revision) )
   };

   /**
    * Defines new global state parameters added after version 1.3.0
    */
   struct [[eosio::table("global3"), eosio::contract("eosio.system")]] eosio_global_state3 {
      eosio_global_state3() { }
      time_point        last_vpay_state_update;
      double            total_vpay_share_change_rate = 0;

      EOSLIB_SERIALIZE( eosio_global_state3, (last_vpay_state_update)(total_vpay_share_change_rate) )
   };

   /**
    * Defines `producer_info` structure to be stored in `producer_info` table, added after version 1.0
    */
   struct [[eosio::table, eosio::contract("eosio.system")]] producer_info {
      name                  owner;
      double                total_votes = 0;
      eosio::public_key     producer_key; /// a packed public key object
      bool                  is_active = true;
      std::string           url;
      uint32_t              unpaid_blocks = 0;
      time_point            last_claim_time;
      uint16_t              location = 0;

      uint64_t primary_key()const { return owner.value;                             }
      double   by_votes()const    { return is_active ? -total_votes : total_votes;  }
      bool     active()const      { return is_active;                               }
      void     deactivate()       { producer_key = public_key(); is_active = false; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( producer_info, (owner)(total_votes)(producer_key)(is_active)(url)
                        (unpaid_blocks)(last_claim_time)(location) )
   };

   /**
    * Defines new producer info structure to be stored in new producer info table, added after version 1.3.0
    */
   struct [[eosio::table, eosio::contract("eosio.system")]] producer_info2 {
      name            owner;
      double          votepay_share = 0;
      time_point      last_votepay_share_update;

      uint64_t primary_key()const { return owner.value; }

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( producer_info2, (owner)(votepay_share)(last_votepay_share_update) )
   };

   /**
    * Voter info.
    * 
    * @details Voter info stores information about the voter:
    * - `owner` the voter
    * - `proxy` the proxy set by the voter, if any
    * - `producers` the producers approved by this voter if no proxy set
    * - `staked` the amount staked
    */
   struct [[eosio::table, eosio::contract("eosio.system")]] voter_info {
      name                owner;     /// the voter
      name                proxy;     /// the proxy set by the voter, if any
      std::vector<name>   producers; /// the producers approved by this voter if no proxy set
      int64_t             staked = 0;

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


      uint32_t            flags1 = 0;
      uint32_t            reserved2 = 0;
      eosio::asset        reserved3;

      uint64_t primary_key()const { return owner.value; }

      enum class flags1_fields : uint32_t {
         ram_managed = 1,
         net_managed = 2,
         cpu_managed = 4
      };

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( voter_info, (owner)(proxy)(producers)(staked)(last_vote_weight)(proxied_vote_weight)(is_proxy)(flags1)(reserved2)(reserved3) )
   };

   /**
    * Voters table
    * 
    * @details The voters table stores all the `voter_info`s instances, all voters information.
    */
   typedef eosio::multi_index< "voters"_n, voter_info >  voters_table;


   /**
    * Defines producer info table added in version 1.0
    */
   typedef eosio::multi_index< "producers"_n, producer_info,
                               indexed_by<"prototalvote"_n, const_mem_fun<producer_info, double, &producer_info::by_votes>  >
                             > producers_table;
   /**
    * Defines new producer info table added in version 1.3.0
    */
   typedef eosio::multi_index< "producers2"_n, producer_info2 > producers_table2;

   /**
    * Global state singleton added in version 1.0
    */
   typedef eosio::singleton< "global"_n, eosio_global_state >   global_state_singleton;
   /**
    * Global state singleton added in version 1.1.0
    */
   typedef eosio::singleton< "global2"_n, eosio_global_state2 > global_state2_singleton;
   /**
    * Global state singleton added in version 1.3
    */
   typedef eosio::singleton< "global3"_n, eosio_global_state3 > global_state3_singleton;

   //   static constexpr uint32_t     max_inflation_rate = 5;  // 5% annual inflation
   static constexpr uint32_t     seconds_per_day = 24 * 3600;

   /**
    * The EOSIO system contract.
    * 
    * @details The EOSIO system contract governs ram market, voters, producers, global state.
    */
   class [[eosio::contract("eosio.system")]] system_contract : public native {
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

         /**
          * System contract constructor.
          * 
          * @details Constructs a system contract based on self account, code account and data.
          * 
          * @params s    - The current code account that is executing the action,
          * @params code - The original code account that executed the action,
          * @params ds   - The contract data represented as an `eosio::datastream`.
          */
         system_contract( name s, name code, datastream<const char*> ds );
         ~system_contract();

         /**
          * Returns the core symbol by system account name
          * 
          * @params system_account - the system account to get the core symbol for.
          */
         static symbol get_core_symbol( name system_account = "eosio"_n ) {
            rammarket rm(system_account, system_account.value);
            const static auto sym = get_core_symbol( rm );
            return sym;
         }

         // Actions:
         /**
          * Init action.
          * 
          * @details Init action initializes the system contract for a version and a symbol. 
          * Only succeeds when:
          * - version is 0 and 
          * - symbol is found and
          * - system token supply is greater than 0, 
          * - and system contract wasn’t already been initialized.
          * 
          * @param version - the version, has to be 0,
          * @param core - the system symbol.
          */
         [[eosio::action]]
         void init( unsigned_int version, symbol core );

         /**
          * On block action.
          * 
          * @details This special action is triggered when a block is applied by the given producer 
          * and cannot be generated from any other source. It is used to pay producers and calculate 
          * missed blocks of other producers. Producer pay is deposited into the producer's stake 
          * balance and can be withdrawn over time. If blocknum is the start of a new round this may 
          * update the active producer config from the producer votes.
          * 
          * @param header - the block header produced.
          */
         [[eosio::action]]
         void onblock( ignore<block_header> header );

         /**
          * Set account limits action.
          * 
          * @details Set the resource limits of an account
          * 
          * @param account - name of the account whose resource limit to be set,
          * @param ram_bytes - ram limit in absolute bytes,
          * @param net_weight - fractionally proportionate net limit of available resources based on (weight / total_weight_of_all_accounts),
          * @param cpu_weight - fractionally proportionate cpu limit of available resources based on (weight / total_weight_of_all_accounts).
          */
         [[eosio::action]]
         void setalimits( name account, int64_t ram_bytes, int64_t net_weight, int64_t cpu_weight );

         [[eosio::action]]
         void setacctram( name account, std::optional<int64_t> ram_bytes );

         [[eosio::action]]
         void setacctnet( name account, std::optional<int64_t> net_weight );

         [[eosio::action]]
         void setacctcpu( name account, std::optional<int64_t> cpu_weight );

         // functions defined in delegate_bandwidth.cpp

         /**
          * Delegate bandwidth and/or cpu action.
          * 
          * @details Stakes SYS from the balance of `from` for the benfit of `receiver`.
          * 
          * @param from - the account to delegate bandwidth from,
          * @param receiver - the account to delegate bandwith to,
          * @param stake_net_quantity - the amount of bandwidth to delegate,
          * @param stake_cpu_quantity - the amount of cpu to delegate,
          * @param transfer - if true, then `receiver` can unstake to their account, 
          *                   else `from` can unstake at any time.
          */
         [[eosio::action]]
         void delegatebw( name from, name receiver,
                          asset stake_net_quantity, asset stake_cpu_quantity, bool transfer );

         /**
          * Undelegate bandwitdh action.
          * 
          * @details Decreases the total tokens delegated by `from` to `receiver` and/or
          * frees the memory associated with the delegation if there is nothing
          * left to delegate.
          * This will cause an immediate reduction in net/cpu bandwidth of the
          * receiver.
          * A transaction is scheduled to send the tokens back to `from` after
          * the staking period has passed. If existing transaction is scheduled, it
          * will be canceled and a new transaction issued that has the combined
          * undelegated amount.
          * The `from` account loses voting power as a result of this call and
          * all producer tallies are updated.
          * 
          * @param from - the account to undelegate bandwidth from,
          * @param receiver - the account to undelegate bandwith to,
          * @param unstake_net_quantity - the amount of bandwidth to undelegate,
          * @param unstake_cpu_quantity - the amount of cpu to undelegate,
          */
         [[eosio::action]]
         void undelegatebw( name from, name receiver,
                            asset unstake_net_quantity, asset unstake_cpu_quantity );

         /**
          * Buy ram action.
          * 
          * @details Increases receiver's ram quota based upon current price and quantity of
          * tokens provided. An inline transfer from receiver to system contract of
          * tokens will be executed.
          * 
          * @param payer - the ram buyer,
          * @param receiver - the ram receiver,
          * @param quant - the quntity of tokens to by ram with.
          */
         [[eosio::action]]
         void buyram( name payer, name receiver, asset quant );

         /**
          * Buy an specific amount of ram bytes action.
          * 
          * @details Increases receiver's ram in quantity of bytes provided. 
          * An inline transfer from receiver to system contract of tokens will be executed.
          * 
          * @param payer - the ram buyer,
          * @param receiver - the ram receiver,
          * @param bytes - the quntity of ram to buy specified in bytes.
          */
         [[eosio::action]]
         void buyrambytes( name payer, name receiver, uint32_t bytes );

         /**
          * Sell ram action.
          *  
          * @details Reduces quota my bytes and then performs an inline transfer of tokens
          * to receiver based upon the average purchase price of the original quota.
          * 
          * @param account - the ram seller account,
          * @param bytes - the amount of ram to sell in bytes.
          */
         [[eosio::action]]
         void sellram( name account, int64_t bytes );

         /**
          * Refund action.
          * 
          * @details This action is called after the delegation-period to claim all pending
          * unstaked tokens belonging to owner.
          * 
          * @param owner - the owner of the tokens claimed.
          */
         [[eosio::action]]
         void refund( name owner );

         // functions defined in voting.cpp

         /**
          * Register producer action.
          * 
          * @details Register producer action, this action will create a `producer_config` and a
          * `producer_info` object for `producer` scope in producers tables.
          * 
          * @param producer - the account of the block producer to be registered,
          * @param producer_key - the public key of the block producer, this is the key used by block producer to sign blocks,
          * @param url - the url of the block producer, normally the url of the block producer presentation website,
          * @param location - is the country code as defined in the ISO 3166, https://en.wikipedia.org/wiki/List_of_ISO_3166_country_codes
          * 
          * @pre Producer is not already registered
          * @pre Producer to register is an account
          * @pre Authority of producer to register
          */
         [[eosio::action]]
         void regproducer( const name producer, const public_key& producer_key, const std::string& url, uint16_t location );

         /**
          * Unregister producer action.
          * 
          * @details Deactivate the block producer with account name `producer`.
          * @param producer - the block producer account to unregister.
          */
         [[eosio::action]]
         void unregprod( const name producer );

         /**
          * Set ram action.
          * 
          * @details Set the ram supply.
          * @param max_ram_size - the amount of ram supply to set.
          */
         [[eosio::action]]
         void setram( uint64_t max_ram_size );

         /**
          * Set ram rate action.
          * 
          * @details Set the ram increase rate.
          * @param bytes_per_block - the amount of bytes per block increase to set.
          */
         [[eosio::action]]
         void setramrate( uint16_t bytes_per_block );

         /**
          * Vote producer action.
          * 
          * @details Votes for a set of producers. This action updates the list of `producers` voted for, 
          * for `voter` account. If voting for a `proxy`, the producer votes will not change until the 
          * proxy updates their own vote.
          * 
          * @params voter - the account to change the voted producers for,
          * @params proxy - the proxy to change the voted producers for,
          * @params producers - the list of producers to vote for.
          * 
          * @pre Producers must be sorted from lowest to highest and must be registered and active
          * @pre If proxy is set then no producers can be voted for
          * @pre If proxy is set then proxy account must exist and be registered as a proxy
          * @pre Every listed producer or proxy must have been previously registered
          * @pre Voter must authorize this action
          * @pre Voter must have previously staked some EOS for voting
          * @pre Voter->staked must be up to date
          *
          * @post Every producer previously voted for will have vote reduced by previous vote weight
          * @post Every producer newly voted for will have vote increased by new vote amount
          * @post Prior proxy will proxied_vote_weight decremented by previous vote weight
          * @post New proxy will proxied_vote_weight incremented by new vote weight
          */
         [[eosio::action]]
         void voteproducer( const name voter, const name proxy, const std::vector<name>& producers );

         /**
          * Register proxy action.
          * 
          * @details Set `proxy` account as proxy.
          * An account marked as a proxy can vote with the weight of other accounts which
          * have selected it as a proxy. Other accounts must refresh their voteproducer to
          * update the proxy's weight.
          *
          * @param rpoxy - the account to set as proxy,
          * @param isproxy - true if proxy wishes to vote on behalf of others, false otherwise.
          * 
          * @pre Proxy must have something staked (existing row in voters table)
          * @pre New state must be different than current state
          */
         [[eosio::action]]
         void regproxy( const name proxy, bool isproxy );

         /**
          * Set the blockchain parameters
          * 
          * @details Set the blockchain parameters. By tunning these parameters a degree of 
          * customization can be achieved.
          * @param params - New blockchain parameters to set.
          */
         [[eosio::action]]
         void setparams( const eosio::blockchain_parameters& params );

         // functions defined in producer_pay.cpp
         /**
          * Claim rewards action.
          * 
          * @details Claim block producing and vote rewards.
          * @param owner - the block producer account to claim rewards for.
          */
         [[eosio::action]]
         void claimrewards( const name owner );

         /**
          * Set privilege status for an account.
          * 
          * @details Allows to set privilege status for an account (turn it on/off).
          * @param account - the account to set the privileged status for.
          * @param is_priv - 0 for false, > 0 for true.
          */
         [[eosio::action]]
         void setpriv( name account, uint8_t is_priv );

         /**
          * Remove producer action.
          * 
          * @details Deactivates a producer by name, if not found asserts.
          * @param producer - the producer account to deactivate.
          */
         [[eosio::action]]
         void rmvproducer( name producer );

         /**
          * Update revision action.
          * 
          * @details Updates the current revision. 
          * @param revision - it has to be incremented by 1 compared with current revision.
          * 
          * @pre Current revision can not be higher than 254, and has to be smaller
          * than or equal 1 (“set upper bound to greatest revision supported in the code”).
          */
         [[eosio::action]]
         void updtrevision( uint8_t revision );

         /**
          * Bid name action.
          * 
          * @details Allows an account `bidder` to place a bid for a name `newname`. 
          * @param bidder - the account placing the bid,
          * @param newname - the name the bid is placed for,
          * @param bid - the amount of system tokens payed for the bid.
          * 
          * @pre Bids can be placed only on top-level suffix,
          * @pre Non empty name,
          * @pre Names longer than 12 chars are not allowed,
          * @pre Names equal with 12 chars can be created without placing a bid,
          * @pre Bid has to be bigger than zero,
          * @pre Bid's symbol must be system token,
          * @pre Bidder account has to be different than current highest bidder,
          * @pre Bid must increase current bid by 10%,
          * @pre Auction must still be opened.
          */
         [[eosio::action]]
         void bidname( name bidder, name newname, asset bid );

         /**
          * Bid refund action.
          * 
          * @details Allows the account `bidder` to get back the amount it bid so far on a `newname` name.
          * 
          * @param bidder - the account that gets refunded,
          * @param newname - the name for which the bid was placed and now it gets refunded for.
          */
         [[eosio::action]]
         void bidrefund( name bidder, name newname );

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

         //defined in voting.hpp
         void update_elected_producers( block_timestamp timestamp );
         void update_votes( const name voter, const name proxy, const std::vector<name>& producers, bool voting );

         // defined in voting.cpp
         void propagate_weight_change( const voter_info& voter );

         double update_producer_votepay_share( const producers_table2::const_iterator& prod_itr,
                                               time_point ct,
                                               double shares_rate, bool reset_to_zero = false );
         double update_total_votepay_share( time_point ct,
                                            double additional_shares_delta = 0.0, double shares_rate_delta = 0.0 );
   };
   /** @}*/ // end of @defgroup eosiosystem eosio.system
} /// eosiosystem
