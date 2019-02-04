/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <algorithm>
#include <cyber.stake/cyber.stake.hpp>
#include <cyber.token/cyber.token.hpp>
#include <common/dispatchers.hpp>
#include <common/parameter_ops.hpp>

namespace cyber {
 
int64_t stake::recall_traversal(agents& agents_table, grants& grants_table, name agent_name, int64_t share) {
    auto agent = get_agent_itr(agents_table, agent_name);
    eosio_assert(share >= 0, "SYSTEM: share can't be negative");
    eosio_assert(share <= agent->shares_sum, "SYSTEM: incorrect share val");
    if(share == 0)
        return 0;
    auto share_fee = static_cast<int64_t>((static_cast<int128_t>(share) * agent->fee) / config::_100percent);
    auto share_net = share - share_fee;
    auto balance_ret = static_cast<int64_t>((static_cast<int128_t>(share_net) * agent->balance) / agent->shares_sum);
    eosio_assert(balance_ret <= agent->balance, "SYSTEM: incorrect balance_ret val");
    
    auto proxied_ret = 0;
    auto grantor_index = grants_table.get_index<"grantor"_n>();
    auto grant_itr = grantor_index.lower_bound(agent_name.value);
    while ((grant_itr != grantor_index.end()) && (grant_itr->grantor_name == agent_name)) {
        auto to_recall = static_cast<int64_t>((static_cast<int128_t>(share_net) * grant_itr->share) / agent->shares_sum);
        proxied_ret += recall_traversal(agents_table, grants_table, grant_itr->agent_name, to_recall);
        grantor_index.modify(grant_itr, name(), [&](auto& g) { g.share -= to_recall; });
        ++grant_itr;
    }
    eosio_assert(proxied_ret <= agent->proxied, "SYSTEM: incorrect proxied_ret val");
    
    agents_table.modify(agent, name(), [&](auto& a) {
        a.balance -= balance_ret;
        a.proxied -= proxied_ret;
        a.own_share += share_fee;
        a.shares_sum -= share_net;
    });
    return balance_ret + proxied_ret;
}

int64_t stake::delegate_traversal(agents& agents_table, grants& grants_table, name agent_name, int64_t amount, bool refill) {
    auto agent = get_agent_itr(agents_table, agent_name);
    auto total_funds = agent->get_total_funds();
    eosio_assert((total_funds == 0) == (agent->shares_sum == 0), "SYSTEM: incorrect total_funds or shares_sum");
    auto own_funds = total_funds && agent->shares_sum ? 
        static_cast<int64_t>((static_cast<int128_t>(agent->own_share) * total_funds) / agent->shares_sum) : 0;
    eosio_assert((own_funds >= agent->min_own_staked) || refill, "insufficient agent funds");
    if(amount == 0)
        return 0;

    auto remaining_amount = amount;
    auto grantor_index = grants_table.get_index<"grantor"_n>();
    auto grant_itr = grantor_index.lower_bound(agent_name.value);
    while ((grant_itr != grantor_index.end()) && (grant_itr->grantor_name == agent_name)) {
        auto to_delegate = static_cast<int64_t>((static_cast<int128_t>(amount) * grant_itr->pct) / config::_100percent);
        remaining_amount -= to_delegate;
        eosio_assert(remaining_amount >= 0, "SYSTEM: incorrect remaining_amount");
        auto delegated = delegate_traversal(agents_table, grants_table, grant_itr->agent_name, to_delegate, true);
        grantor_index.modify(grant_itr, name(), [&](auto& g) { g.share += delegated; });
        ++grant_itr;
    }
    eosio_assert(remaining_amount <= amount, "SYSTEM: incorrect remaining_amount");
    
    auto ret = total_funds && agent->shares_sum ?
        static_cast<int64_t>((static_cast<int128_t>(amount) * agent->shares_sum) / total_funds) : amount;
    
    agents_table.modify(agent, name(), [&](auto& a) {
        a.balance += remaining_amount;
        a.proxied += amount - remaining_amount;
        a.shares_sum += ret;
    });
    
    return ret;
}

void stake::update_proxied(agents& agents_table, grants& grants_table, agents::const_iterator agent, int64_t frame_length, bool force) {
    const int64_t now = ::now();
    if ((now - agent->last_proxied_update.utc_seconds >= frame_length) || force) {
        int64_t new_proxied = 0;
        int64_t unstaked = 0;
        auto grantor_index = grants_table.get_index<"grantor"_n>();
        auto grant_itr = grantor_index.lower_bound(agent->account.value);
        while ((grant_itr != grantor_index.end()) && (grant_itr->grantor_name == agent->account)) {
            auto proxy_agent = get_agent_itr(agents_table, grant_itr->agent_name);
            update_proxied(agents_table, grants_table, proxy_agent, frame_length, force);
            if (proxy_agent->proxy_level < agent->proxy_level) {
                if (proxy_agent->shares_sum)
                    new_proxied += static_cast<int64_t>((static_cast<int128_t>(grant_itr->share) * proxy_agent->get_total_funds()) / proxy_agent->shares_sum);
                ++grant_itr;
            }
            else {
                unstaked += recall_traversal(agents_table, grants_table, grant_itr->agent_name, grant_itr->share);
                grant_itr = grantor_index.erase(grant_itr);
            }
            
        }
        agents_table.modify(agent, name(), [&](auto& a) {
            a.balance += unstaked;
            a.proxied = new_proxied;
            a.last_proxied_update = time_point_sec(now);
        });
    }
}

symbol stake::structures::param::get_purpose_symbol(symbol_code token_code, symbol_code purpose_code)const {
    auto purpose_itr = purpose_ids.find(purpose_code);
    eosio_assert(purpose_itr != purpose_ids.end(), ("unknown purpose: " + purpose_code.to_string()).c_str());
    return symbol(token_code, purpose_itr->second);
}

void stake::add_proxy(grants& grants_table, agents::const_iterator grantor_as_agent, agents::const_iterator agent, int16_t pct, int64_t share) {
    eosio_assert(agent->last_proxied_update == time_point_sec(now()), "SYSTEM: outdated last_proxied_update val");
    eosio_assert(grantor_as_agent->proxy_level > agent->proxy_level, 
        ("incorrect proxy levels: grantor " + std::to_string(grantor_as_agent->proxy_level) + 
        ", agent " + std::to_string(agent->proxy_level)).c_str());
    grants_table.emplace(grantor_as_agent->account, [&]( auto &item ) { item = structures::grant {
        .id = grants_table.available_primary_key(),
        .grantor_name = grantor_as_agent->account,
        .agent_name = agent->account,
        .pct = pct,
        .share = share
    };});
}

void stake::delegate(name grantor_name, name agent_name, asset quantity, symbol_code purpose_code) {
    require_auth(grantor_name);
    
    params params_table(_self, quantity.symbol.code().raw());
    const auto& param = params_table.get(quantity.symbol.code().raw(), "no staking for token");
    
    auto sym = param.get_purpose_symbol(quantity.symbol.code(), purpose_code);
    agents agents_table(_self, sym.raw());
    
    auto grantor_as_agent = get_agent_itr(agents_table, grantor_name);   
    eosio_assert(quantity.amount <= grantor_as_agent->balance, "insufficient balance");
    auto agent = get_agent_itr(agents_table, agent_name);
    grants grants_table(_self, sym.raw());
    
    update_proxied(agents_table, grants_table, agent, param.frame_length, true);
    
    auto delegated = delegate_traversal(agents_table, grants_table, agent_name, quantity.amount);
    
    uint8_t proxies_num = 0;
    auto grantor_index = grants_table.get_index<"grantor"_n>();
    auto grant_itr = grantor_index.lower_bound(grantor_name.value);
    while ((grant_itr != grantor_index.end()) && (grant_itr->grantor_name == grantor_name)) {
        ++proxies_num;
        if (grant_itr->agent_name == agent_name) {
            grantor_index.modify(grant_itr, name(), [&](auto& g) { g.share += delegated; });
            delegated = 0;
        }
        ++grant_itr;
    }
    
    if (delegated) {
        eosio_assert(proxies_num < param.max_proxies[grantor_as_agent->proxy_level - 1], "proxy cannot be added");
        add_proxy(grants_table, grantor_as_agent, agent, 0, delegated);
    }
    
    agents_table.modify(grantor_as_agent, name(), [&](auto& a) {
        a.balance -= quantity.amount;
        a.proxied += quantity.amount;
    });
    
}

void stake::recall(name grantor_name, name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct) {
    eosio_assert(1 <= pct && pct <= config::_100percent, "pct must be between 0.01% and 100% (1-10000)");
    require_auth(grantor_name);
    params params_table(_self, token_code.raw());
    const auto& param = params_table.get(token_code.raw(), "no staking for token");
    
    auto sym = param.get_purpose_symbol(token_code, purpose_code);
    
    agents agents_table(_self, sym.raw());
    grants grants_table(_self, sym.raw());
    
    auto grantor_as_agent = get_agent_itr(agents_table, grantor_name);
    
    update_proxied(agents_table, grants_table, grantor_as_agent, param.frame_length);
    
    int64_t amount = 0;
    auto grantor_index = grants_table.get_index<"grantor"_n>();
    auto grant_itr = grantor_index.lower_bound(grantor_name.value);
    while ((grant_itr != grantor_index.end()) && (grant_itr->grantor_name == grantor_name)) {
        if (grant_itr->agent_name == agent_name) { //TODO:? index
            auto to_recall = static_cast<int64_t>((static_cast<int128_t>(grant_itr->share) * pct) / config::_100percent);
            amount = recall_traversal(agents_table, grants_table, grant_itr->agent_name, to_recall);
            if (grant_itr->pct || grant_itr->share > to_recall) {
                grantor_index.modify(grant_itr, name(), [&](auto& g) { g.share -= to_recall; });
                ++grant_itr;
            }
            else
                grant_itr = grantor_index.erase(grant_itr);
        }
        else
            ++grant_itr;
    }
    eosio_assert(amount > 0, "amount to recall must be positive");
    agents_table.modify(grantor_as_agent, name(), [&](auto& a) {
        a.balance += amount;
        a.proxied -= amount;
    });
}

bool stake::set_agent_pct(name grantor_name, name agent_name, int16_t pct, symbol sym, const structures::param& param) {
    eosio::print("set_agent_pct: ", grantor_name, " -> ", agent_name, " ", static_cast<int64_t>(pct));
    grants grants_table(_self, sym.raw());
    auto grantor_index = grants_table.get_index<"grantor"_n>();
    auto grant_itr = grantor_index.lower_bound(grantor_name.value);
    int16_t pct_sum = 0;
    bool changed = false;
    bool agent_found = false;
    uint8_t proxies_num = 0;
    while ((grant_itr != grantor_index.end()) && (grant_itr->grantor_name == grantor_name)) {
         ++proxies_num;
        if (grant_itr->agent_name == agent_name) {
            changed = changed || grant_itr->pct != pct;
            agent_found = true;
            if(pct || grant_itr->share) {
                grantor_index.modify(grant_itr, name(), [&](auto& g) { g.pct = pct; });
                pct_sum += pct;
                ++grant_itr;
            }
            else
                grant_itr = grantor_index.erase(grant_itr);
        }
        else {
            pct_sum += grant_itr->pct;
            ++grant_itr;
        }
        eosio_assert(pct_sum <= config::_100percent, "too high pct value\n");
    }
    if (!agent_found && pct) {
        agents agents_table(_self, sym.raw());
        auto grantor_as_agent = get_agent_itr(agents_table, grantor_name, param.max_proxies.size());
        eosio_assert(proxies_num < param.max_proxies[grantor_as_agent->proxy_level - 1], "proxy cannot be added");
        auto agent = get_agent_itr(agents_table, agent_name);
        update_proxied(agents_table, grants_table, agent, param.frame_length, true);
        add_proxy(grants_table, grantor_as_agent, agent, pct, 0);
        changed = true;
    }
    return changed;
}

void stake::setagentpct(name grantor_name, name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct) {
    eosio_assert(0 <= pct && pct <= config::_100percent, "pct must be between 0% and 100% (0-10000)");
    require_auth(grantor_name);
    params params_table(_self, token_code.raw());
    const auto& param = params_table.get(token_code.raw(), "no staking for token");
    bool changed = false;
    if (static_cast<bool>(purpose_code))
        changed = set_agent_pct(grantor_name, agent_name, pct, param.get_purpose_symbol(token_code, purpose_code), param) || changed;
    else
        for (auto& p : param.purpose_ids)
            changed = set_agent_pct(grantor_name, agent_name, pct, symbol(token_code, p.second), param) || changed;
    
    eosio_assert(changed, "agent pct has not been changed");
}

void stake::on_transfer(name from, name to, asset quantity, std::string memo) {
    if (_self != to || memo == config::reward_memo)
        return;
        
    auto purpose_code = symbol_code(memo.c_str());
    params params_table(_self, quantity.symbol.code().raw());
    const auto& param = params_table.get(quantity.symbol.code().raw(), "no staking for token");
    
    auto sym = param.get_purpose_symbol(quantity.symbol.code(), purpose_code);
    
    agents agents_table(_self, sym.raw());
    grants grants_table(_self, sym.raw());
    
    auto agent = get_agent_itr(agents_table, from, param.max_proxies.size());
    
    update_proxied(agents_table, grants_table, agent, param.frame_length);

    auto share = delegate_traversal(agents_table, grants_table, from, quantity.amount);
    agents_table.modify(agent, name(), [&](auto& a) { a.own_share += share; });
}

void stake::claim(name account, symbol_code token_code, symbol_code purpose_code) {
    update_payout(account, asset(0, symbol(token_code, 0)), purpose_code, true);
}

void stake::withdraw(name account, asset quantity, symbol_code purpose_code) {
    eosio_assert(quantity.amount > 0, "must withdraw positive quantity");
    update_payout(account, quantity, purpose_code);
}

void stake::cancelwd(name account, asset quantity, symbol_code purpose_code) {
    eosio_assert(quantity.amount >= 0, "quantity can't be negative");
    quantity.amount = -quantity.amount;
    update_payout(account, quantity, purpose_code);
}

void stake::update_payout(name account, asset quantity, symbol_code purpose_code, bool claim_mode) {
    require_auth(account);
    auto token_code = quantity.symbol.code();
    params params_table(_self, token_code.raw());
    const auto& param = params_table.get(token_code.raw(), "no staking for token");
    auto sym = param.get_purpose_symbol(token_code, purpose_code);
    payouts payouts_table(_self, sym.raw());
    send_scheduled_payout(payouts_table, account, param.payout_step_lenght, param.token_symbol);
    
    if(claim_mode)
        return;
    
    agents agents_table(_self, sym.raw());
    auto agent = get_agent_itr(agents_table, account);

    grants grants_table(_self, sym.raw());
    update_proxied(agents_table, grants_table, agent, param.frame_length);
        
    auto total_funds = agent->get_total_funds();
    eosio_assert((total_funds == 0) == (agent->shares_sum == 0), "SYSTEM: incorrect total_funds or shares_sum");
    
    int64_t balance_diff = 0;
    int64_t shares_diff = 0;
    if (quantity.amount > 0) {
        eosio_assert(quantity.amount <= agent->balance, "insufficient funds");

        eosio_assert(total_funds > 0, "no funds to withdrawal");
        auto own_funds = static_cast<int64_t>((static_cast<int128_t>(agent->own_share) * total_funds) / agent->shares_sum);
        eosio_assert(own_funds - quantity.amount >= agent->min_own_staked, "insufficient agent funds");

        balance_diff = -quantity.amount;
        shares_diff = -static_cast<int64_t>((static_cast<int128_t>(quantity.amount) * agent->shares_sum) / total_funds); 
        eosio_assert(-shares_diff <= agent->own_share, "SYSTEM: incorrect shares_to_withdraw val");
        
        payouts_table.emplace(account, [&]( auto &item ) { item = structures::payout {
            .id = payouts_table.available_primary_key(),
            .account = account,
            .balance = quantity.amount,
            .steps_left = param.payout_steps_num,
            .last_step = time_point_sec(::now())
        };});
        
    }
    else {
        quantity.amount = -quantity.amount;
        auto acc_index = payouts_table.get_index<"payoutacc"_n>();
        auto payout_lb_itr = acc_index.lower_bound(account.value);

        int64_t amount_sum = 0;
        auto payout_itr = payout_lb_itr;
        while ((payout_itr != acc_index.end()) && (payout_itr->account == account)) {
            amount_sum += payout_itr->balance;
        }
        eosio_assert(amount_sum >= quantity.amount, "insufficient funds");
        
        while ((payout_itr != acc_index.end()) && (payout_itr->account == account)) {
            auto cur_amount = quantity.amount ? 
                static_cast<int64_t>((static_cast<int128_t>(payout_itr->balance) * quantity.amount) / amount_sum) : 
                payout_itr->balance;
            balance_diff += cur_amount;
            if (cur_amount < payout_itr->balance) {
                acc_index.modify(payout_itr, name(), [&](auto& p) { p.balance -= cur_amount; });
                ++payout_itr;
            }
            else
                payout_itr = acc_index.erase(payout_itr);
        }
        //TODO:? due to rounding, balance_diff usually will be less than requested. should we do something about it?
        shares_diff = total_funds ? static_cast<int64_t>((static_cast<int128_t>(balance_diff) * agent->shares_sum) / total_funds) : balance_diff; 
    }
    
    agents_table.modify(agent, name(), [&](auto& a) {
        a.balance += balance_diff;
        a.shares_sum += shares_diff;
        a.own_share += shares_diff;
    });
}

void stake::send_scheduled_payout(payouts& payouts_table, name account, int64_t payout_step_lenght, symbol sym) {
    const int64_t now = ::now();
    eosio_assert(payout_step_lenght > 0, "SYSTEM: incorrect payout_step_lenght val");
    
    auto acc_index = payouts_table.get_index<"payoutacc"_n>();
    auto payout_itr = acc_index.lower_bound(account.value);
    int64_t amount = 0;
    while ((payout_itr != acc_index.end()) && (payout_itr->account == account)) {
        auto seconds_passed = now - payout_itr->last_step.utc_seconds;
        eosio_assert(seconds_passed >= 0, "SYSTEM: incorrect seconds_passed val");
        auto steps_passed = std::min(seconds_passed / payout_step_lenght, static_cast<int64_t>(payout_itr->steps_left));
        if (steps_passed) {
            if(steps_passed != payout_itr->steps_left) {
                auto cur_amount = static_cast<int64_t>((static_cast<int128_t>(payout_itr->balance) * steps_passed) / payout_itr->steps_left);
                acc_index.modify(payout_itr, name(), [&](auto& p) {
                    p.balance -= cur_amount;
                    p.steps_left -= steps_passed;
                    p.last_step = time_point_sec(p.last_step.utc_seconds + (steps_passed * payout_step_lenght));
                });
                ++payout_itr;
            }
            else {
                amount += payout_itr->balance;
                payout_itr = acc_index.erase(payout_itr);
            }
        }
        else
            ++payout_itr;
    }
    if(amount) {
        INLINE_ACTION_SENDER(eosio::token, transfer)(config::token_name, {_self, config::active_name},
            {_self, account, asset(amount, sym), "unstaked tokens"});
    }
}

void stake::setproxylvl(name account, uint8_t level, symbol_code token_code, symbol_code purpose_code) {
    require_auth(account);
    params params_table(_self, token_code.raw());

    const auto& param = params_table.get(token_code.raw(), "no staking for token");
    bool changed = false;
    if (static_cast<bool>(purpose_code))
        changed = set_proxy_level(account, level, param.get_purpose_symbol(token_code, purpose_code), param.max_proxies) || changed;
    else
        for (auto& p : param.purpose_ids)
            changed = set_proxy_level(account, level, symbol(token_code, p.second), param.max_proxies) || changed;
    eosio_assert(changed, "proxy level has not been changed");
}

bool stake::set_proxy_level(name account, uint8_t level, symbol sym, const std::vector<uint8_t>& max_proxies) {
    eosio_assert(level <= max_proxies.size(), "level too high");
    agents agents_table(_self, sym.raw());
    bool emplaced{false};
    auto agent = get_agent_itr(agents_table, account, level, &emplaced);
    bool changed = emplaced || (level != agent->proxy_level);
    grants grants_table(_self, sym.raw());
    auto grantor_index = grants_table.get_index<"grantor"_n>();
    auto grant_itr = grantor_index.lower_bound(account.value);
    uint8_t proxies_num = 0;
    while ((grant_itr != grantor_index.end()) && (grant_itr->grantor_name == account)) {
         ++proxies_num;
         ++grant_itr;
    }
    eosio_assert(level || !proxies_num, "can't set an ultimate level because the user has a proxy");
    eosio_assert(!level || proxies_num <= max_proxies[level - 1], "can't set proxy level, user has too many proxies");
        
    if(!emplaced) {
        agents_table.modify(agent, name(), [&](auto& a) { a.proxy_level = level; });
    }
    return changed;
}

void stake::create(symbol token_symbol, std::vector<symbol_code> purpose_codes, std::vector<uint8_t> max_proxies, 
        int64_t frame_length, int64_t payout_step_lenght, uint16_t payout_steps_num) 
{
    eosio::print("create stake for ", token_symbol.code(), "\n");
    eosio_assert(max_proxies.size(), "no proxy levels are specified");
    eosio_assert(max_proxies.size() < std::numeric_limits<uint8_t>::max(), "too many proxy levels");
    if (max_proxies.size() > 1)
        for (size_t i = 1; i < max_proxies.size(); i++) {
            eosio_assert(max_proxies[i - 1] >= max_proxies[i], "incorrect proxy levels");
        }
    auto issuer = eosio::token::get_issuer(config::token_name, token_symbol.code());
    require_auth(issuer);
    params params_table(_self, token_symbol.code().raw());
    eosio_assert(params_table.find(token_symbol.code().raw()) == params_table.end(), "already exists");
    std::map<symbol_code, uint8_t> purpose_ids;
    for (size_t i = 0; i < purpose_codes.size(); i++)
        purpose_ids[purpose_codes[i]] = i;
    
    params_table.emplace(issuer, [&](auto& p) { p = {
        .token_symbol = token_symbol,
        .purpose_ids = purpose_ids,
        .max_proxies = max_proxies,
        .frame_length = frame_length,
        .payout_step_lenght = payout_step_lenght,
        .payout_steps_num = payout_steps_num
        };});
}

stake::agents::const_iterator stake::get_agent_itr(agents& agents_table, name agent_name, int16_t proxy_level_for_emplaced, bool* emplaced) {
    auto agent = agents_table.find(agent_name.value);
    if (emplaced)
        *emplaced = false;
        
    if(proxy_level_for_emplaced < 0) {
        eosio_assert(agent != agents_table.end(), ("agent " + agent_name.to_string() + " doesn't exist").c_str());
    }
    else if(agent == agents_table.end()) {
        agent = agents_table.emplace(agent_name, [&](auto& a) { a = {
            .account = agent_name,
            .proxy_level = static_cast<uint8_t>(proxy_level_for_emplaced),
            .last_proxied_update = time_point_sec(::now())
        };});
        if (emplaced)
            *emplaced = true;
    }
    return agent;
}

void stake::update_proxied(name agent_name, symbol purpose_symbol, int64_t frame_length) {
    agents agents_table(_self, purpose_symbol.raw());
    grants grants_table(_self, purpose_symbol.raw());
    update_proxied(agents_table, grants_table, get_agent_itr(agents_table, agent_name), frame_length);
}

void stake::updatefunds(name account, symbol_code token_code, symbol_code purpose_code) {
    //require_auth(anyone);
    params params_table(_self, token_code.raw());
    const auto& param = params_table.get(token_code.raw(), "no staking for token");
    if (static_cast<bool>(purpose_code))
        update_proxied(account, param.get_purpose_symbol(token_code, purpose_code), param.frame_length);
    else
        for (auto& p : param.purpose_ids)
            update_proxied(account, symbol(token_code, p.second), param.frame_length);
}

void stake::change_balance(name account, asset quantity, symbol_code purpose_code) {
    eosio_assert(quantity.is_valid(), "invalid quantity");
    auto issuer = eosio::token::get_issuer(config::token_name, quantity.symbol.code());
    require_auth(issuer);
    params params_table(_self, quantity.symbol.code().raw());
    const auto& param = params_table.get(quantity.symbol.code().raw(), "no staking for token");
    
    auto sym = param.get_purpose_symbol(quantity.symbol.code(), purpose_code);
    agents agents_table(_self, sym.raw());
    auto agent = get_agent_itr(agents_table, account);
    if (quantity.amount < 0)
        quantity.amount = std::max(quantity.amount, -agent->balance);
    
    agents_table.modify(agent, name(), [&](auto& a) { a.balance += quantity.amount; });
    
    if (quantity.amount < 0) {
        quantity.amount = -quantity.amount;
        INLINE_ACTION_SENDER(eosio::token, transfer)(config::token_name, {_self, config::active_name},
            {_self, issuer, quantity, ""});
        INLINE_ACTION_SENDER(eosio::token, retire)(config::token_name, {issuer, config::amerce_name}, {quantity, ""});
    }
    else {
        INLINE_ACTION_SENDER(eosio::token, issue)(config::token_name, {issuer, config::reward_name}, {issuer, quantity, ""});
        INLINE_ACTION_SENDER(eosio::token, transfer)(config::token_name, {issuer, config::reward_name},
            {issuer, _self, quantity, config::reward_memo});    
    }
}

void stake::amerce(name account, asset quantity, symbol_code purpose_code) {
    eosio_assert(quantity.amount > 0, "quantity must be positive");
    quantity.amount = -quantity.amount;
    change_balance(account, quantity, purpose_code);
}

void stake::reward(name account, asset quantity, symbol_code purpose_code) {
    eosio_assert(quantity.amount > 0, "quantity must be positive");
    change_balance(account, quantity, purpose_code);
}


} /// namespace cyber

DISPATCH_WITH_TRANSFER(cyber::stake, cyber::config::token_name, on_transfer,
    (create)(delegate)(setagentpct)(recall)(withdraw)(claim)(cancelwd)(setproxylvl)(updatefunds)(amerce)(reward)
)
