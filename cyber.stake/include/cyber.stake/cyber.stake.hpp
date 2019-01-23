/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>
#include "config.hpp"
#include <string>


namespace cyber {

using eosio::name;
using eosio::asset;
using eosio::symbol;
using eosio::symbol_code;
using eosio::time_point_sec;
using std::string;

class [[eosio::contract("eosio.stake")]] stake : public eosio::contract {
struct structures {
    struct [[eosio::table]] agent {
        name account;
        uint8_t proxy_level;
        
        time_point_sec last_proxied_update;
        int64_t balance = 0;// aka unproxied funds
        int64_t proxied = 0;// proxed funds
        int64_t shares_sum = 0;
        int64_t own_share = 0;
        int16_t fee = 0; //TODO: rules for changing fees
        int64_t min_own_staked = 0; //TODO: rules for changing this
        
        uint64_t primary_key()const { return account.value; }
        int64_t get_total_funds()const { return balance + proxied; };
     };
     
    struct [[eosio::table]] grant {
        uint64_t id; 
        name grantor_name;
        name agent_name;
        int16_t pct = 0;
        int64_t share = 0;
        uint64_t primary_key()const { return id; }
        uint64_t by_grantor()const { return grantor_name.value; }
    };
    
    //TODO: use parameter.hpp for this
    struct [[eosio::table]] param {
        symbol token_symbol;
        std::map<symbol_code, uint8_t> purpose_ids;
        std::vector<uint8_t> max_proxies;
        int64_t frame_length;
        int64_t payout_step_lenght; //TODO: these parameters should
        uint16_t payout_steps_num;  //--/--  depend on the purposes      
        uint64_t primary_key()const { return token_symbol.code().raw(); }
        symbol get_purpose_symbol(symbol_code token_code, symbol_code purpose_code) const;
    };

    struct [[eosio::table]] payout {
        uint64_t id;
        name account;
        int64_t balance;
        uint16_t steps_left;
        time_point_sec last_step;
        uint64_t primary_key()const { return id; }
        uint64_t by_account()const { return account.value; }
    };
};
    
    
    using agents   = eosio::multi_index<"agent"_n, structures::agent>;
    using grant_id_index = eosio::indexed_by<"grantid"_n, eosio::const_mem_fun<structures::grant, uint64_t, &structures::grant::primary_key> >;
    using grant_grantor_index = eosio::indexed_by<"grantor"_n, eosio::const_mem_fun<structures::grant, uint64_t, &structures::grant::by_grantor> >;
    using grants = eosio::multi_index<"grant"_n, structures::grant, grant_id_index, grant_grantor_index>;
    using params = eosio::multi_index<"param"_n, structures::param>;
    //TODO:
    //using stats = 
    
    using payout_id_index = eosio::indexed_by<"payoutid"_n, eosio::const_mem_fun<structures::payout, uint64_t, &structures::payout::primary_key> >;
    using payout_acc_index = eosio::indexed_by<"payoutacc"_n, eosio::const_mem_fun<structures::payout, uint64_t, &structures::payout::by_account> >;
    using payouts = eosio::multi_index<"payout"_n, structures::payout, payout_id_index, payout_acc_index>;
    
    void update_proxied(agents& agents_table, grants& grants_table, agents::const_iterator agent, int64_t frame_length, bool force = false);
    void update_proxied(name agent_name, symbol purpose_symbol, int64_t frame_length);
    
    void send_scheduled_payout(payouts& payouts_table, name account, int64_t payout_step_lenght, symbol sym);
    void update_payout(name account, asset quantity, symbol_code purpose_code, bool claim_mode = false);
    
    //return: token amount
    int64_t recall_traversal(agents& agents_table, grants& grants_table, name agent_name, int64_t share);
    
    //return: share
    int64_t delegate_traversal(agents& agents_table, grants& grants_table, name agent_name, int64_t amount, bool refill = false);
    
    bool set_proxy_level(name account, uint8_t level, symbol sym, const std::vector<uint8_t>& max_proxies);
    bool set_agent_pct(name grantor_name, name agent_name, int16_t pct, symbol sym, const structures::param& param);
    
    agents::const_iterator get_agent_itr(agents& agents_table, name agent_name, int16_t proxy_level_for_emplaced = -1, bool* emplaced = nullptr);

    void add_proxy(grants& grants_table, agents::const_iterator grantor_as_agent, agents::const_iterator agent, int16_t pct, int64_t share);
    void change_balance(name account, asset quantity, symbol_code purpose_code);
public:
    using contract::contract;
    [[eosio::action]] void create(symbol token_symbol, std::vector<symbol_code> purpose_codes, std::vector<uint8_t> max_proxies, 
        int64_t frame_length, int64_t payout_step_lenght, uint16_t payout_steps_num);
    
    [[eosio::action]] void delegate(name grantor_name, name agent_name, asset quantity, symbol_code purpose_code);
    
    [[eosio::action]] void setagentpct(name grantor_name, name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct);
    [[eosio::action]] void recall     (name grantor_name, name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct);
    
    [[eosio::action]] void withdraw(name account, asset quantity, symbol_code purpose_code);
    [[eosio::action]] void claim(name account, symbol_code token_code, symbol_code purpose_code);
    [[eosio::action]] void cancelwd(name account, asset quantity, symbol_code purpose_code);

    void on_transfer(name from, name to, asset quantity, std::string memo);

    [[eosio::action]] void setproxylvl(name account, uint8_t level, symbol_code token_code, symbol_code purpose_code);
        //use purpose_code == symbol_code() for setting all existing purposes
        
    [[eosio::action]] void updatefunds(name account, symbol_code token_code, symbol_code purpose_code);
        
    [[eosio::action]] void amerce(name account, asset quantity, symbol_code purpose_code);
    //TODO:
    [[eosio::action]] void reward(name account, asset quantity, symbol_code purpose_code);
};
} /// namespace cyber
