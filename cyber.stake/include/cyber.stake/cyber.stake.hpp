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
#include <tuple>
#include <eosiolib/privileged.h>

#define table_owner name()

namespace cyber {

using eosio::name;
using eosio::asset;
using eosio::symbol;
using eosio::symbol_code;
using eosio::time_point_sec;
using eosio::public_key;
using std::string;

class [[eosio::contract("cyber.stake")]] stake : public eosio::contract {
struct structures {

    struct [[eosio::table]] agent {
        uint64_t id;
        symbol_code purpose_code;
        symbol_code token_code;
        name account;
        
        uint8_t proxy_level;
        bool ultimate;
        time_point_sec last_proxied_update;
        int64_t balance = 0;// aka unproxied funds
        int64_t proxied = 0;// proxed funds
        int64_t shares_sum = 0;
        int64_t own_share = 0;
        int16_t fee = 0;
        int64_t min_own_staked = 0;
        public_key signing_key = {}; //TODO:? move it to a separate struct
        
        uint64_t primary_key()const { return id; }
        using key_t = std::tuple<symbol_code, symbol_code, name>;
        key_t by_key()const { return std::make_tuple(purpose_code, token_code, account); }
        using ultimate_key_t = std::tuple<symbol_code, symbol_code, bool, name>;
        ultimate_key_t by_ultimate()const { return std::make_tuple(purpose_code, token_code, ultimate, account); }
        int64_t get_total_funds()const { return balance + proxied; }
     };
 
    struct [[eosio::table]] grant {
        uint64_t id;
        symbol_code purpose_code;
        symbol_code token_code;
        name grantor_name;
        name agent_name;
        int16_t pct = 0;
        int64_t share = 0;
        int16_t break_fee = config::_100percent;
        int64_t break_min_own_staked = 0;
        
        uint64_t primary_key()const { return id; }
        using key_t = std::tuple<symbol_code, symbol_code, name, name>;
        key_t by_key()const { return std::make_tuple(purpose_code, token_code, grantor_name, agent_name); }
    };
    
    //TODO: use parameter.hpp for this
    struct [[eosio::table]] param {
        uint64_t id;
        symbol token_symbol;
        std::vector<symbol_code> purposes;
        std::vector<uint8_t> max_proxies;
        int64_t frame_length;
        int64_t payout_step_lenght; //TODO: these parameters should
        uint16_t payout_steps_num;  //--/--  depend on the purposes      
        uint64_t primary_key()const { return id; }
        void check_purpose(symbol_code purpose_code) const;
    };
 
    struct [[eosio::table]] payout { 
        uint64_t id;
        symbol_code token_code;
        name account;
        int64_t balance;
        uint16_t steps_left;
        time_point_sec last_step;
        uint64_t primary_key()const { return id; }
        
        using by_account_t = std::tuple<symbol_code, name>;
        by_account_t by_account()const { return std::make_tuple(token_code, account); }
    };
    
    struct [[eosio::table]] stat {
        uint64_t id;
        symbol_code purpose_code;
        symbol_code token_code;
        int64_t total_staked;
        uint64_t primary_key()const { return id; }
        using key_t = std::tuple<symbol_code, symbol_code>;
        key_t by_key()const { return std::make_tuple(purpose_code, token_code); }
    }; 
};

    using agent_id_index = eosio::indexed_by<"agentid"_n, eosio::const_mem_fun<structures::agent, uint64_t, &structures::agent::primary_key> >;
    using agent_key_index = eosio::indexed_by<"bykey"_n, eosio::const_mem_fun<structures::agent, structures::agent::key_t, &structures::agent::by_key> >;
    using agent_ultimate_index = eosio::indexed_by<"byultimate"_n, eosio::const_mem_fun<structures::agent, structures::agent::ultimate_key_t, &structures::agent::by_ultimate> >;
    using agents = eosio::multi_index<"stake.agent"_n, structures::agent, agent_id_index, agent_key_index, agent_ultimate_index>;
    using agents_idx_t = decltype(agents(table_owner, table_owner.value).get_index<"bykey"_n>());
    
    using grant_id_index = eosio::indexed_by<"grantid"_n, eosio::const_mem_fun<structures::grant, uint64_t, &structures::grant::primary_key> >;
    using grant_key_index = eosio::indexed_by<"bykey"_n, eosio::const_mem_fun<structures::grant, structures::grant::key_t, &structures::grant::by_key> >;
    using grants = eosio::multi_index<"stake.grant"_n, structures::grant, grant_id_index, grant_key_index>;
    using grants_idx_t = decltype(grants(table_owner, table_owner.value).get_index<"bykey"_n>());
    
    using params = eosio::multi_index<"stake.param"_n, structures::param>;
    
    using stat_id_index = eosio::indexed_by<"statid"_n, eosio::const_mem_fun<structures::stat, uint64_t, &structures::stat::primary_key> >;
    using stat_key_index = eosio::indexed_by<"bykey"_n, eosio::const_mem_fun<structures::stat, structures::stat::key_t, &structures::stat::by_key> >;

    using stats = eosio::multi_index<"stake.stat"_n, structures::stat, stat_id_index, stat_key_index>;

    using payout_id_index = eosio::indexed_by<"payoutid"_n, eosio::const_mem_fun<structures::payout, uint64_t, &structures::payout::primary_key> >;
    using payout_acc_index = eosio::indexed_by<"payoutacc"_n, eosio::const_mem_fun<structures::payout, structures::payout::by_account_t, &structures::payout::by_account> >;
    using payouts = eosio::multi_index<"payout"_n, structures::payout, payout_id_index, payout_acc_index>;
    
    void update_stake_proxied(symbol_code purpose_code, symbol_code token_code, name agent_name, int64_t frame_length, bool force) {
        ::update_stake_proxied(purpose_code.raw(), token_code.raw(), agent_name.value, frame_length, static_cast<int>(force));
    }
    
    void send_scheduled_payout(payouts& payouts_table, name account, int64_t payout_step_lenght, symbol sym);
    void update_payout(name account, asset quantity, symbol_code purpose_code, bool claim_mode = false);

    //return: share
    int64_t delegate_traversal(symbol_code purpose_code, symbol_code token_code, agents_idx_t& agents_idx, grants_idx_t& grants_idx, name agent_name, int64_t amount, bool refill = false);
    
    bool set_proxy_level(name account, symbol_code purpose_code, symbol_code token_code, const std::vector<uint8_t>& max_proxies, uint8_t level);
    bool set_grant_terms(name grantor_name, name agent_name, int16_t pct, int16_t break_fee, int64_t break_min_own_staked, 
        symbol_code purpose_code, symbol_code token_code, const structures::param& param);
    
    agents_idx_t::const_iterator get_agent_itr(symbol_code purpose_code, symbol_code token_code, agents_idx_t& agents_idx, name agent_name, int16_t proxy_level_for_emplaced = -1, agents* agents_table = nullptr, bool* emplaced = nullptr);
    void add_proxy(symbol_code purpose_code, symbol_code token_code, grants& grants_table, const structures::agent& grantor_as_agent, const structures::agent& agent, 
        int16_t pct, int64_t share, int16_t break_fee = -1, int64_t break_min_own_staked = -1);

    void change_balance(name account, asset quantity, symbol_code purpose_code);
    void update_stats(const structures::stat& stat_arg, name payer = name());
    
    template<typename Lambda>
    void modify_agent(name account, symbol_code token_code, symbol_code purpose_code, Lambda f) {
        require_auth(account);
        params params_table(table_owner, table_owner.value);
        const auto& param = params_table.get(token_code.raw(), "no staking for token");
        if (!purpose_code) {
            eosio_assert(param.purposes.size(), "no purposes");
            purpose_code = param.purposes[0];
        }
        agents agents_table(table_owner, table_owner.value);
        auto agents_idx = agents_table.get_index<"bykey"_n>();
        auto agent = get_agent_itr(purpose_code, token_code, agents_idx, account);
        agents_idx.modify(agent, name(), f);
    }
    static void check_grant_terms(const structures::agent& agent, int16_t break_fee, int64_t break_min_own_staked);

    const auto& get_param(const stake::params& params_table, symbol_code purpose_code, symbol_code token_code, bool strict = true) const;
    
public:

    static inline std::vector<std::pair<name, public_key> > get_top(uint16_t n, symbol_code token_code) {
        params params_table(table_owner, table_owner.value);
        const auto& param = params_table.get(token_code.raw(), "no staking for token");
        agents agents_table(table_owner, table_owner.value);
        auto agents_idx = agents_table.get_index<"byultimate"_n>();
        
        struct agent_info {
            name account;
            mutable public_key signing_key;
            mutable int64_t balance = 0;
            mutable uint8_t entries = 0;
            bool operator <(const agent_info& rhs)const { return account < rhs.account; };
        };
        std::set<agent_info> agents_set;
        for (auto& p : param.purposes) {
            auto agent_itr = agents_idx.lower_bound(std::make_tuple(p, token_code, true, name()));
            while ((agent_itr != agents_idx.end()) &&
                   (agent_itr->purpose_code == p) &&
                   (agent_itr->token_code   == token_code) &&
                    agent_itr->ultimate)
            {
                auto itm = agents_set.emplace(agent_info{agent_itr->account, agent_itr->signing_key});
                itm.first->balance += agent_itr->balance;
                itm.first->entries++;
                if((itm.first->signing_key == public_key{}) && (agent_itr->signing_key != public_key{}))
                    itm.first->signing_key = agent_itr->signing_key;
                ++agent_itr;
            }
        }
        eosio_assert(param.purposes.size() < std::numeric_limits<uint8_t>::max(), "SYSTEM: too many proxy purposes");
        uint8_t purposes_num = static_cast<uint8_t>(param.purposes.size());
        
        std::vector<agent_info> agents_vector;
        agents_vector.reserve(agents_set.size());
        for (auto i = agents_set.begin(); i != agents_set.end(); ++i) {
            if(i->entries == purposes_num && i->signing_key != public_key{})
                agents_vector.emplace_back(*i);
        }
        size_t ret_size = std::min(static_cast<size_t>(n), agents_vector.size());
        auto agents_mid = agents_vector.begin() + ret_size;
        std::partial_sort(agents_vector.begin(), agents_mid, agents_vector.end(), [](const agent_info& lhs, const agent_info& rhs) {
            return std::tie(lhs.balance, lhs.account) > std::tie(rhs.balance, rhs.account);
        });
        
        std::vector<std::pair<name, public_key> > ret;
        ret.reserve(ret_size);

        for (auto i = agents_vector.begin(); i != agents_mid; ++i)
            ret.emplace_back(std::make_pair(i->account, i->signing_key));
        
        std::sort(ret.begin(), ret.end(), [](const std::pair<name, public_key>& lhs, const std::pair<name, public_key>& rhs) {
            return lhs.first < rhs.first;
        });
        return ret;
    }

    using contract::contract;
    [[eosio::action]] void create(symbol token_symbol, std::vector<symbol_code> purpose_codes, std::vector<uint8_t> max_proxies, 
        int64_t frame_length, int64_t payout_step_lenght, uint16_t payout_steps_num);

    [[eosio::action]] void delegate(name grantor_name, name agent_name, asset quantity, symbol_code purpose_code);
    
    [[eosio::action]] void setgrntterms(name grantor_name, name agent_name, symbol_code token_code, symbol_code purpose_code, 
        int16_t pct, int16_t break_fee, int64_t break_min_own_staked);
    [[eosio::action]] void recall     (name grantor_name, name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct);
    
    [[eosio::action]] void withdraw(name account, asset quantity, symbol_code purpose_code);
    [[eosio::action]] void claim(name account, symbol_code token_code, symbol_code purpose_code);
    [[eosio::action]] void cancelwd(name account, asset quantity, symbol_code purpose_code);
 
    void on_transfer(name from, name to, asset quantity, std::string memo);

    [[eosio::action]] void setproxylvl(name account, symbol_code token_code, symbol_code purpose_code, uint8_t level);
        //use purpose_code == symbol_code() for setting all existing purposes

    [[eosio::action]] void setproxyfee(name account, symbol_code token_code, symbol_code purpose_code, int16_t fee);
    [[eosio::action]] void setminstaked(name account, symbol_code token_code, symbol_code purpose_code, int64_t min_own_staked);
    [[eosio::action]] void setkey(name account, symbol_code token_code, public_key signing_key);
    
    [[eosio::action]] void updatefunds(name account, symbol_code token_code, symbol_code purpose_code);
        
    [[eosio::action]] void amerce(name account, asset quantity, symbol_code purpose_code);

    [[eosio::action]] void reward(name account, asset quantity, symbol_code purpose_code);
};
} /// namespace cyber
