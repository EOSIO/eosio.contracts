#pragma once
#include "test_api_helper.hpp"

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
        return push(N(delegate), grantor_name, args()
            ("grantor_name", grantor_name)
            ("agent_name", agent_name)
            ("quantity", quantity)
            ("purpose_code", purpose_code)
        );
    }
    
    action_result setagentpct(account_name grantor_name, account_name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct) {
        return push(N(setagentpct), grantor_name, args()
            ("grantor_name", grantor_name)
            ("agent_name", agent_name)
            ("token_code", token_code)
            ("purpose_code", purpose_code)
            ("pct", pct)
        );
    }
    
    action_result recall(account_name grantor_name, account_name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct) {
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
    
    action_result setproxylvl(account_name account, uint8_t level, symbol_code token_code, symbol_code purpose_code) {
        return push(N(setproxylvl), account, args()
            ("account", account)
            ("level", level)
            ("token_code", token_code)
            ("purpose_code", purpose_code)
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
    
     ////tables
    variant get_agent(account_name account, symbol token_symbol, symbol_code purpose_code) {
        return get_struct(get_stake_symbol(token_symbol, purpose_code).value(), N(agent), account.value, "agent_struct");
     }
     
    variant make_agent(
            account_name account, 
            uint8_t proxy_level, 
            time_point_sec last_proxied_update,
            int64_t balance = 0,
            int64_t proxied = 0,
            int64_t shares_sum = 0,
            int64_t own_share = 0,
            int16_t fee = 0,
            int64_t min_own_staked = 0
        ) {
        return mvo()
            ("account", account)
            ("proxy_level", proxy_level)
            ("last_proxied_update", last_proxied_update)
            ("balance", balance)
            ("proxied", proxied)
            ("shares_sum", shares_sum)
            ("own_share", own_share)
            ("fee", fee)
            ("min_own_staked", min_own_staked);
    }
};


}} // eosio::testing
