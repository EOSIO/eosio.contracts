#pragma once
#include "test_api_helper.hpp"
#include "../common/config.hpp"

using eosio::chain::symbol_code;

symbol_code to_code(const std::string& arg){return eosio::chain::symbol(0, arg.c_str()).to_symbol_code();};
namespace eosio { namespace testing {

struct cyber_stake_api: base_contract_api {
public:
    cyber_stake_api(golos_tester* tester, name code)
    :   base_contract_api(tester, code){}
    
    std::map<symbol_code, std::map<symbol_code, uint8_t> > _purpose_ids;
    
    symbol get_stake_symbol(symbol token_symbol, symbol_code purpose_code) {
        auto purpose_id = _purpose_ids[token_symbol.to_symbol_code()][purpose_code];
        return symbol(purpose_id, token_symbol.name().c_str());
    }

    ////actions
    action_result create(account_name issuer, symbol token_symbol, std::vector<symbol_code> purpose_codes, 
            std::vector<uint8_t> max_proxies, int64_t frame_length, int64_t payout_step_lenght, uint16_t payout_steps_num) {

        auto& cur_purpose_ids = _purpose_ids[token_symbol.to_symbol_code()];
        for (size_t i = 0; i < purpose_codes.size(); i++)
            cur_purpose_ids[purpose_codes[i]] = i;
        
        return push(N(create), issuer, args()
            ("token_symbol", token_symbol)
            ("purpose_codes", purpose_codes)
            ("max_proxies", max_proxies)
            ("frame_length", frame_length)
            ("payout_step_lenght", payout_step_lenght)
            ("payout_steps_num", payout_steps_num)
        );
    }
    
    action_result delegate(account_name grantor_name, account_name agent_name, asset quantity, symbol_code purpose_code) {
        BOOST_TEST_MESSAGE("--- " << grantor_name <<  " delegates " << quantity 
            <<  "(" << purpose_code << ")" << " to " << agent_name);
        return push(N(delegate), grantor_name, args()
            ("grantor_name", grantor_name)
            ("agent_name", agent_name)
            ("quantity", quantity)
            ("purpose_code", purpose_code)
        );
    }
    
    action_result setgrntterms(account_name grantor_name, account_name agent_name, symbol_code token_code, symbol_code purpose_code, 
        int16_t pct, int16_t break_fee = cyber::config::_100percent, int64_t break_min_own_staked = 0) {
        BOOST_TEST_MESSAGE("--- " << grantor_name <<  " sets grant terms for " << agent_name);
        return push(N(setgrntterms), grantor_name, args()
            ("grantor_name", grantor_name)
            ("agent_name", agent_name)
            ("token_code", token_code)
            ("purpose_code", purpose_code)
            ("pct", pct)
            ("break_fee", break_fee)
            ("break_min_own_staked", break_min_own_staked)        
        );
    }
    
    action_result recall(account_name grantor_name, account_name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct) {
        BOOST_TEST_MESSAGE("--- " << grantor_name <<  " recalls " << pct 
            <<  "(" << token_code << ", " << purpose_code << ")" << " from " << agent_name);
        return push(N(recall), grantor_name, args()
            ("grantor_name", grantor_name)
            ("agent_name", agent_name)
            ("token_code", token_code)
            ("purpose_code", purpose_code)
            ("pct", pct)
        );
    }
    
    action_result withdraw(account_name account, asset quantity, symbol_code purpose_code) {
        return push(N(withdraw), account, args()
            ("account", account)
            ("quantity", quantity)
            ("purpose_code", purpose_code)
        );
    }
    
    action_result cancelwd(account_name account, asset quantity, symbol_code purpose_code) {
        return push(N(cancelwd), account, args()
            ("account", account)
            ("quantity", quantity)
            ("purpose_code", purpose_code)
        );
    }
    
    action_result claim(account_name account, symbol_code token_code, symbol_code purpose_code) {
        return push(N(claim), account, args()
            ("account", account)
            ("token_code", token_code)
            ("purpose_code", purpose_code)
        );
    }
    
    action_result setproxylvl(account_name account, symbol_code token_code, symbol_code purpose_code, uint8_t level) {
        BOOST_TEST_MESSAGE("--- " << account <<  " sets proxy level");
        return push(N(setproxylvl), account, args()
            ("account", account)
            ("token_code", token_code)
            ("purpose_code", purpose_code)
            ("level", level)
        );
    }
    action_result setproxyfee(account_name account, symbol_code token_code, symbol_code purpose_code, int16_t fee) {
        return push(N(setproxyfee), account, args()
            ("account", account)
            ("token_code", token_code)
            ("purpose_code", purpose_code)
            ("fee", fee)
        );
    }
    
    action_result updatefunds(account_name account, symbol_code token_code, symbol_code purpose_code) {
        return push(N(updatefunds), account, args()
            ("account", account)
            ("token_code", token_code)
            ("purpose_code", purpose_code)
        );
    }
    
    action_result amerce(account_name issuer, account_name account, asset quantity, symbol_code purpose_code) {
        return push(N(amerce), issuer, args()
            ("account", account)
            ("quantity", quantity)
            ("purpose_code", purpose_code)
        );
    }
    
    action_result reward(account_name issuer, account_name account, asset quantity, symbol_code purpose_code) {
        return push(N(reward), issuer, args()
            ("account", account)
            ("quantity", quantity)
            ("purpose_code", purpose_code)
        );
    }
    
    action_result register_candidate(account_name account, symbol_code token_code) {
        
        auto ret = setproxylvl(account, token_code, symbol_code(), 0);
        if(ret != base_tester::success())
            return ret;
         return push(N(setkey), account, args()
            ("account", account)
            ("token_code", token_code)
            ("signing_key", base_tester::get_public_key(account, "active"))
        );
    }

     ////tables
    variant get_agent(account_name account, symbol token_symbol, symbol_code purpose_code) {
        auto purpose_symbol = get_stake_symbol(token_symbol, purpose_code);
        auto all = _tester->get_all_chaindb_rows(name(), 0, N(stake.agent), false);
        for(auto& v : all) {
            auto o = mvo(v);
            if (v["account"].as<account_name>() == account && 
                v["purpose_id"].as<uint8_t>() == purpose_symbol.decimals() &&
                v["token_code"].as<symbol_code>() == purpose_symbol.to_symbol_code()) 
            {
                o.erase("id");
                o.erase("signing_key");
                v = o;
                return v;
            }
        }
        return variant();
    }

    variant make_agent(
            account_name account, symbol token_symbol, symbol_code purpose_code,
            uint8_t proxy_level, 
            time_point_sec last_proxied_update,
            int64_t balance = 0,
            int64_t proxied = 0,
            int64_t shares_sum = 0,
            int64_t own_share = 0,
            int16_t fee = 0,
            int64_t min_own_staked = 0
        ) {
            auto purpose_symbol = get_stake_symbol(token_symbol, purpose_code);
        return mvo()
            ("purpose_id", purpose_symbol.decimals())
            ("token_code", purpose_symbol.to_symbol_code())
            ("account", account)
            ("proxy_level", proxy_level)
            ("ultimate", !proxy_level)
            ("last_proxied_update", last_proxied_update)
            ("balance", balance)
            ("proxied", proxied)
            ("shares_sum", shares_sum)
            ("own_share", own_share)
            ("fee", fee)
            ("min_own_staked", min_own_staked);
    }
    
    variant get_stats(symbol token_symbol, symbol_code purpose_code) {
        return _tester->get_chaindb_struct(name(), name().value, 
            N(stake.stat), get_stake_symbol(token_symbol, purpose_code).value(), "stat_struct");
    }
    
    variant make_stats(symbol token_symbol, symbol_code purpose_code, int64_t total_staked) {
        return mvo()
            ("id", get_stake_symbol(token_symbol, purpose_code).value())
            ("token_code", token_symbol.to_symbol_code())
            ("purpose_code", purpose_code)
            ("total_staked", total_staked);
    }
    
};

}} // eosio::testing
