/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#undef CHAINDB_ANOTHER_CONTRACT_PROTECT
#define CHAINDB_ANOTHER_CONTRACT_PROTECT(_CHECK, _MSG)
   
#include <algorithm>
#include <cyber.stake/cyber.stake.hpp>
#include <cyber.token/cyber.token.hpp>
#include <common/dispatchers.hpp>
#include <common/parameter_ops.hpp>
#include <common/util.hpp>

namespace cyber {
    
const auto& stake::get_param(const stake::params& params_table, symbol_code purpose_code, symbol_code token_code, bool strict) const {
    const auto& ret = params_table.get(token_code.raw(), "no staking for token");
    eosio_assert(!strict || std::find(ret.purposes.begin(), ret.purposes.end(), purpose_code) != ret.purposes.end(), 
        ("unknown purpose: " + purpose_code.to_string()).c_str());
    return ret;
}
    
int64_t stake::delegate_traversal(symbol_code purpose_code, symbol_code token_code, stake::agents_idx_t& agents_idx, stake::grants_idx_t& grants_idx, name agent_name, int64_t amount, bool refill) {
    
    auto agent = get_agent_itr(purpose_code, token_code, agents_idx, agent_name);
    auto total_funds = agent->get_total_funds();
    eosio_assert((total_funds == 0) == (agent->shares_sum == 0), "SYSTEM: incorrect total_funds or shares_sum");
    auto own_funds = total_funds && agent->shares_sum ? safe_prop(total_funds, agent->own_share, agent->shares_sum) : 0;
    eosio_assert((own_funds >= agent->min_own_staked) || refill, "insufficient agent funds");
    if(amount == 0)
        return 0;

    auto remaining_amount = amount;
    auto grant_itr = grants_idx.lower_bound(
        std::make_tuple(purpose_code, token_code, agent_name, name()));
    while ((grant_itr != grants_idx.end()) &&
           (grant_itr->purpose_code   == purpose_code) &&
           (grant_itr->token_code   == token_code) &&
           (grant_itr->grantor_name == agent_name))
    {
        auto to_delegate = safe_pct(amount, grant_itr->pct);
        remaining_amount -= to_delegate;
        eosio_assert(remaining_amount >= 0, "SYSTEM: incorrect remaining_amount");
        auto delegated = delegate_traversal(purpose_code, token_code, agents_idx, grants_idx, grant_itr->agent_name, to_delegate, true);
        grants_idx.modify(grant_itr, name(), [&](auto& g) {
            g.share += delegated;
            g.granted += to_delegate;
        });
        ++grant_itr;
    }
    eosio_assert(remaining_amount <= amount, "SYSTEM: incorrect remaining_amount");
    
    auto ret = total_funds && agent->shares_sum ? safe_prop(agent->shares_sum, amount, total_funds) : amount;
    
    agents_idx.modify(agent, name(), [&](auto& a) {
        a.balance += remaining_amount;
        a.proxied += amount - remaining_amount;
        a.shares_sum += ret;
    });
    
    return ret;
}

void stake::add_proxy(symbol_code purpose_code, symbol_code token_code, grants& grants_table, const structures::agent& grantor_as_agent, const structures::agent& agent, 
        int16_t pct, int64_t share, int64_t granted, int16_t break_fee, int64_t break_min_own_staked) {

    auto now = ::now();
    eosio_assert(agent.last_proxied_update == time_point_sec(now), 
        ("SYSTEM: outdated last_proxied_update val: last update = " + 
        std::to_string(agent.last_proxied_update.sec_since_epoch()) + 
        ", now = " + std::to_string(now)).c_str());
    eosio_assert(grantor_as_agent.proxy_level > agent.proxy_level, 
        ("incorrect proxy levels: grantor " + std::to_string(grantor_as_agent.proxy_level) + 
        ", agent " + std::to_string(agent.proxy_level)).c_str());
    grants_table.emplace(grantor_as_agent.account, [&]( auto &item ) { item = structures::grant {
        .id = grants_table.available_primary_key(),
        .purpose_code = purpose_code,
        .token_code = token_code,
        .grantor_name = grantor_as_agent.account,
        .agent_name = agent.account,
        .pct = pct,
        .share = share,
        .granted = granted,
        .break_fee = break_fee < 0 ? agent.fee : break_fee,
        .break_min_own_staked = break_min_own_staked < 0 ? agent.min_own_staked : break_min_own_staked
    };});
}
 
void stake::delegate(name grantor_name, name agent_name, asset quantity, symbol_code purpose_code) {
    require_auth(grantor_name);
    eosio_assert(quantity.amount > 0, "quantity must be positive");
    params params_table(table_owner, table_owner.value);
    const auto& param = get_param(params_table, purpose_code, quantity.symbol.code());
    
    update_stake_proxied(purpose_code, quantity.symbol.code(), agent_name, param.frame_length, true);
    
    agents agents_table(table_owner, table_owner.value);
    auto agents_idx = agents_table.get_index<"bykey"_n>();
    auto token_code = quantity.symbol.code();
    
    auto grantor_as_agent = get_agent_itr(purpose_code, token_code, agents_idx, grantor_name);   
    eosio_assert(quantity.amount <= grantor_as_agent->balance, "insufficient balance");
    auto agent = get_agent_itr(purpose_code, token_code, agents_idx, agent_name);
    grants grants_table(table_owner, table_owner.value);
    auto grants_idx = grants_table.get_index<"bykey"_n>();
    
    auto delegated = delegate_traversal(purpose_code, token_code, agents_idx, grants_idx, agent_name, quantity.amount);
    uint8_t proxies_num = 0;
    auto grant_itr = grants_idx.lower_bound(std::make_tuple(purpose_code, token_code, grantor_name, name()));
    while ((grant_itr != grants_idx.end()) &&
           (grant_itr->purpose_code == purpose_code) &&
           (grant_itr->token_code   == token_code) &&
           (grant_itr->grantor_name == grantor_name))
    {
        ++proxies_num;
        if (grant_itr->agent_name == agent_name) {
            grants_idx.modify(grant_itr, name(), [&](auto& g) {
                g.share += delegated;
                g.granted += quantity.amount; 
            });
            delegated = 0;
        }
        ++grant_itr;
    }
    
    if (delegated) {
        eosio_assert(proxies_num < param.max_proxies[grantor_as_agent->proxy_level - 1], "proxy cannot be added");
        add_proxy(purpose_code, token_code, grants_table, *grantor_as_agent, *agent, 0, delegated, quantity.amount);
    }
    
    agents_idx.modify(grantor_as_agent, name(), [&](auto& a) {
        a.balance -= quantity.amount;
        a.proxied += quantity.amount;
    });
}

void stake::recall(name grantor_name, name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct) {
    ::recall_stake_proxied(purpose_code.raw(), token_code.raw(), grantor_name.value, agent_name.value, pct);
}

void stake::check_grant_terms(const structures::agent& agent, int16_t break_fee, int64_t break_min_own_staked) {
    eosio_assert(break_fee < 0 || agent.fee <= break_fee, "break_fee can't be less than current agent fee");
    eosio_assert(break_min_own_staked <= agent.min_own_staked, "break_min_own_staked can't be greater than current min_own_staked value");
}

bool stake::set_grant_terms(name grantor_name, name agent_name, int16_t pct, int16_t break_fee, int64_t break_min_own_staked, 
        symbol_code purpose_code, symbol_code token_code, const structures::param& param) {
    agents agents_table(table_owner, table_owner.value);
    auto agents_idx = agents_table.get_index<"bykey"_n>();
    grants grants_table(table_owner, table_owner.value);
    auto grants_idx = grants_table.get_index<"bykey"_n>();

    int16_t pct_sum = 0;
    bool changed = false;
    bool agent_found = false;
    uint8_t proxies_num = 0;
    auto grant_itr = grants_idx.lower_bound(std::make_tuple(purpose_code, token_code, grantor_name, name()));
    while ((grant_itr != grants_idx.end()) &&
           (grant_itr->purpose_code   == purpose_code) &&
           (grant_itr->token_code   == token_code) &&
           (grant_itr->grantor_name == grantor_name))
    {
         ++proxies_num;
        if (grant_itr->agent_name == agent_name) {
            check_grant_terms(*get_agent_itr(purpose_code, token_code, agents_idx, agent_name), break_fee, break_min_own_staked);
            changed = changed
                || grant_itr->pct != pct
                || grant_itr->break_fee != break_fee
                || grant_itr->break_min_own_staked != break_min_own_staked;
            agent_found = true;
            if(pct || grant_itr->share) {
                grants_idx.modify(grant_itr, name(), [&](auto& g) {
                    g.pct = pct;
                    g.break_fee = break_fee;
                    g.break_min_own_staked = break_min_own_staked;
                });
                pct_sum += pct;
                ++grant_itr;
            }
            else
                grant_itr = grants_idx.erase(grant_itr);
        }
        else {
            pct_sum += grant_itr->pct;
            ++grant_itr;
        }
        eosio_assert(pct_sum <= config::_100percent, "too high pct value\n");
    }
    if (!agent_found && pct) {
        auto grantor_as_agent = get_agent_itr(purpose_code, token_code, agents_idx, grantor_name, param.max_proxies.size(), &agents_table);
        eosio_assert(proxies_num < param.max_proxies[grantor_as_agent->proxy_level - 1], "proxy cannot be added");
        auto agent = get_agent_itr(purpose_code, token_code, agents_idx, agent_name);
        check_grant_terms(*agent, break_fee, break_min_own_staked);
        update_stake_proxied(purpose_code, token_code, agent_name, param.frame_length, true);
    
        add_proxy(purpose_code, token_code, grants_table, *grantor_as_agent, *agent, pct, 0, 0, break_fee, break_min_own_staked);
        changed = true;
    }
    return changed;
} 

void stake::setgrntterms(name grantor_name, name agent_name, symbol_code token_code, symbol_code purpose_code, int16_t pct, int16_t break_fee, int64_t break_min_own_staked) {
    eosio_assert(0 <= pct && pct <= config::_100percent, "pct must be between 0% and 100% (0-10000)");
    eosio_assert(0 <= break_fee && break_fee <= config::_100percent, "break_fee must be between 0% and 100% (0-10000)");
    eosio_assert(0 <= break_min_own_staked, "break_min_own_staked can't be negative");
    
    require_auth(grantor_name);
    params params_table(table_owner, table_owner.value);
    const auto& param = get_param(params_table, purpose_code, token_code, static_cast<bool>(purpose_code));
    
    bool changed = false;
    if (static_cast<bool>(purpose_code))
        changed = set_grant_terms(grantor_name, agent_name, pct, break_fee, break_min_own_staked, 
            purpose_code, token_code, param) || changed;
    else
        for (auto& p : param.purposes)
            changed = set_grant_terms(grantor_name, agent_name, pct, break_fee, break_min_own_staked, 
                p, token_code, param) || changed;
    
    eosio_assert(changed, "agent pct has not been changed");
}

void stake::on_transfer(name from, name to, asset quantity, std::string memo) {
    if (_self != to || memo == config::reward_memo)
        return;
    auto token_code = quantity.symbol.code();
    auto purpose_code = symbol_code(memo.c_str());
    params params_table(table_owner, table_owner.value);
    const auto& param = get_param(params_table, purpose_code, token_code);
    
    {
        agents agents_table(table_owner, table_owner.value);
        auto agents_idx = agents_table.get_index<"bykey"_n>();
        get_agent_itr(purpose_code, token_code, agents_idx, from, param.max_proxies.size(), &agents_table);
        update_stake_proxied(purpose_code, token_code, from, param.frame_length, false);
    }

    agents agents_table(table_owner, table_owner.value);
    auto agents_idx = agents_table.get_index<"bykey"_n>();
    grants grants_table(table_owner, table_owner.value);
    auto grants_idx = grants_table.get_index<"bykey"_n>();
    
    auto agent = get_agent_itr(purpose_code, token_code, agents_idx, from, param.max_proxies.size(), &agents_table);
    
    auto share = delegate_traversal(purpose_code, token_code, agents_idx, grants_idx, from, quantity.amount);
    agents_idx.modify(agent, name(), [&](auto& a) { a.own_share += share; });
    update_stats(structures::stat {
        .id = 0,
        .token_code = token_code,
        .purpose_code = purpose_code,
        .total_staked = quantity.amount
    }, from);
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
    params params_table(table_owner, table_owner.value);
    const auto& param = get_param(params_table, purpose_code, token_code);
    payouts payouts_table(_self, purpose_code.raw());
    send_scheduled_payout(payouts_table, account, param.payout_step_lenght, param.token_symbol);
    
    if(claim_mode)
        return;
    
    update_stake_proxied(purpose_code, token_code, account, param.frame_length, false);
     
    agents agents_table(table_owner, table_owner.value);
    auto agents_idx = agents_table.get_index<"bykey"_n>();
    auto agent = get_agent_itr(purpose_code, token_code, agents_idx, account);

    grants grants_table(table_owner, table_owner.value);
    auto grants_idx = grants_table.get_index<"bykey"_n>();
    
    auto total_funds = agent->get_total_funds();
    eosio_assert((total_funds == 0) == (agent->shares_sum == 0), "SYSTEM: incorrect total_funds or shares_sum");
    
    int64_t balance_diff = 0;
    int64_t shares_diff = 0;
    if (quantity.amount > 0) {
        eosio_assert(quantity.amount <= agent->balance, "insufficient funds");

        eosio_assert(total_funds > 0, "no funds to withdrawal");
        auto own_funds = safe_prop(total_funds, agent->own_share, agent->shares_sum);
        eosio_assert(own_funds - quantity.amount >= agent->min_own_staked, "insufficient agent funds");

        balance_diff = -quantity.amount;
        shares_diff = -safe_prop(agent->shares_sum, quantity.amount, total_funds);
        eosio_assert(-shares_diff <= agent->own_share, "SYSTEM: incorrect shares_to_withdraw val");
        
        payouts_table.emplace(account, [&]( auto &item ) { item = structures::payout {
            .id = payouts_table.available_primary_key(),
            .token_code = token_code,
            .account = account,
            .balance = quantity.amount,
            .steps_left = param.payout_steps_num,
            .last_step = time_point_sec(::now())
        };});
    }
    else {
        quantity.amount = -quantity.amount;
        auto acc_index = payouts_table.get_index<"payoutacc"_n>();
        auto payout_lb_itr = acc_index.lower_bound(std::make_tuple(token_code, account));

        int64_t amount_sum = 0;
        auto payout_itr = payout_lb_itr;
        while ((payout_itr != acc_index.end()) && (payout_itr->token_code == token_code) && (payout_itr->account == account)) {
            amount_sum += payout_itr->balance;
        }
        eosio_assert(amount_sum >= quantity.amount, "insufficient funds");
        
        while ((payout_itr != acc_index.end()) && (payout_itr->token_code == token_code) && (payout_itr->account == account)) {
            auto cur_amount = quantity.amount ? safe_prop(payout_itr->balance, quantity.amount, amount_sum) : payout_itr->balance;
            balance_diff += cur_amount;
            if (cur_amount < payout_itr->balance) {
                acc_index.modify(payout_itr, name(), [&](auto& p) { p.balance -= cur_amount; });
                ++payout_itr;
            }
            else
                payout_itr = acc_index.erase(payout_itr);
        }
        //TODO:? due to rounding, balance_diff usually will be less than requested. should we do something about it?
        shares_diff = total_funds ? safe_prop(agent->shares_sum, balance_diff, total_funds) : balance_diff;
    }
    
    agents_idx.modify(agent, name(), [&](auto& a) {
        a.balance += balance_diff;
        a.shares_sum += shares_diff;
        a.own_share += shares_diff;
    });
    
    update_stats(structures::stat {
        .id = 0,
        .token_code = token_code,
        .purpose_code = purpose_code,
        .total_staked = balance_diff
    });
}
 
void stake::update_stats(const structures::stat& stat_arg, name payer) {
    stats stats_table(table_owner, table_owner.value);
    auto stat_index = stats_table.get_index<"bykey"_n>();
    auto stat = stat_index.find(std::make_tuple(stat_arg.purpose_code, stat_arg.token_code));

    if (stat == stat_index.end() && payer != name()) {
        eosio_assert(stat_arg.total_staked >= 0, "SYSTEM: incorrect total_staked");
        stats_table.emplace(payer, [&](auto& s) { s = stat_arg; s.id = stats_table.available_primary_key(); });
    }
    else if (stat != stat_index.end()) {
        stat_index.modify(stat, name(), [&](auto& s) { 
            s.total_staked += stat_arg.total_staked; 
            s.enabled = s.enabled || stat_arg.enabled;
        });
    }
    else {
        eosio_assert(false, "stats doesn't exist");
    }
}

void stake::send_scheduled_payout(payouts& payouts_table, name account, int64_t payout_step_lenght, symbol sym) {
    const int64_t now = ::now();
    eosio_assert(payout_step_lenght > 0, "SYSTEM: incorrect payout_step_lenght val");
    
    auto acc_index = payouts_table.get_index<"payoutacc"_n>();
    auto payout_itr = acc_index.lower_bound(std::make_tuple(sym.code(), account)); 
    int64_t amount = 0;
    while ((payout_itr != acc_index.end()) && (payout_itr->token_code == sym.code()) && (payout_itr->account == account)) {
        auto seconds_passed = now - payout_itr->last_step.utc_seconds;
        eosio_assert(seconds_passed >= 0, "SYSTEM: incorrect seconds_passed val");
        auto steps_passed = std::min(seconds_passed / payout_step_lenght, static_cast<int64_t>(payout_itr->steps_left));
        if (steps_passed) {
            if(steps_passed != payout_itr->steps_left) {
                auto cur_amount = safe_prop(payout_itr->balance, steps_passed, payout_itr->steps_left);
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

void stake::setproxyfee(name account, symbol_code token_code, symbol_code purpose_code, int16_t fee) {
    eosio_assert(0 <= fee && fee <= config::_100percent, "fee must be between 0% and 100% (0-10000)");
    modify_agent(account, token_code, purpose_code, [fee](auto& a) { a.fee = fee; } );
}

void stake::setminstaked(name account, symbol_code token_code, symbol_code purpose_code, int64_t min_own_staked) {
    eosio_assert(0 <= min_own_staked, "min_own_staked can't be negative");
    modify_agent(account, token_code, purpose_code, [min_own_staked](auto& a) { a.min_own_staked = min_own_staked; } );
}

void stake::setkey(name account, symbol_code token_code, public_key signing_key) {
    modify_agent(account, token_code, symbol_code(0), [signing_key](auto& a) { a.signing_key = signing_key; } );
}

void stake::setproxylvl(name account, symbol_code token_code, symbol_code purpose_code, uint8_t level) {
    require_auth(account);
    params params_table(table_owner, table_owner.value);
    const auto& param = get_param(params_table, purpose_code, token_code, static_cast<bool>(purpose_code));
    
    bool changed = false;
    if (static_cast<bool>(purpose_code))
        changed = set_proxy_level(account, purpose_code, token_code, param.max_proxies, level) || changed;
    else
        for (auto& p : param.purposes)
            changed = set_proxy_level(account, p, token_code, param.max_proxies, level) || changed;
    eosio_assert(changed, "proxy level has not been changed");
} 
 
bool stake::set_proxy_level(name account, symbol_code purpose_code, symbol_code token_code, const std::vector<uint8_t>& max_proxies, uint8_t level) {
    eosio::print("set_proxy_level for ", account, " ", int(level), "\n");
    eosio_assert(level <= max_proxies.size(), "level too high");
    agents agents_table(table_owner, table_owner.value);
    auto agents_idx = agents_table.get_index<"bykey"_n>();
    bool emplaced = false;
    auto agent = get_agent_itr(purpose_code, token_code, agents_idx, account, level, &agents_table, &emplaced);
    bool changed = emplaced || (level != agent->proxy_level);
    grants grants_table(table_owner, table_owner.value);
    auto grants_idx = grants_table.get_index<"bykey"_n>();
    uint8_t proxies_num = 0;
    auto grant_itr = grants_idx.lower_bound(std::make_tuple(purpose_code, token_code, account, name()));
    while ((grant_itr != grants_idx.end()) &&
           (grant_itr->purpose_code   == purpose_code) &&
           (grant_itr->token_code   == token_code) &&
           (grant_itr->grantor_name == account))
    { 
         ++proxies_num;
         ++grant_itr;
    }
    eosio_assert(level || !proxies_num, "can't set an ultimate level because the user has a proxy");
    eosio_assert(!level || proxies_num <= max_proxies[level - 1], "can't set proxy level, user has too many proxies");

    if(!emplaced) {
        agents_idx.modify(agent, name(), [&](auto& a) { a.proxy_level = level; a.ultimate = !level; });
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
    params params_table(table_owner, table_owner.value);
    eosio_assert(params_table.find(token_symbol.code().raw()) == params_table.end(), "already exists");
    
    params_table.emplace(issuer, [&](auto& p) { p = {
        .id = token_symbol.code().raw(),
        .token_symbol = token_symbol,
        .purposes = purpose_codes,
        .max_proxies = max_proxies,
        .frame_length = frame_length,
        .payout_step_lenght = payout_step_lenght,
        .payout_steps_num = payout_steps_num
        };});
}

void stake::enable(symbol token_symbol, symbol_code purpose_code) {
    auto token_code = token_symbol.code();
    auto issuer = eosio::token::get_issuer(config::token_name, token_code);
    require_auth(issuer);
    params params_table(table_owner, table_owner.value);
    get_param(params_table, purpose_code, token_code);
    update_stats(structures::stat {
        .id = 0,
        .token_code = token_code,
        .purpose_code = purpose_code,
        .total_staked = 0,
        .enabled = true
    }, issuer);
}

stake::agents_idx_t::const_iterator stake::get_agent_itr(symbol_code purpose_code, symbol_code token_code, stake::agents_idx_t& agents_idx, name agent_name, int16_t proxy_level_for_emplaced, agents* agents_table, bool* emplaced) {
    auto key = std::make_tuple(purpose_code, token_code, agent_name);
    auto agent = agents_idx.find(key);
    
    if (emplaced)
        *emplaced = false;

    if(proxy_level_for_emplaced < 0) {
        eosio_assert(agent != agents_idx.end(), ("agent " + agent_name.to_string() + " doesn't exist").c_str());
    }
    else if(agent == agents_idx.end()) {

        eosio_assert(static_cast<bool>(agents_table), "SYSTEM: agents_table can't be null");
        (*agents_table).emplace(agent_name, [&](auto& a) { a = {
            .id = agents_table->available_primary_key(),
            .purpose_code = purpose_code,
            .token_code = token_code,
            .account = agent_name,
            .proxy_level = static_cast<uint8_t>(proxy_level_for_emplaced),
            .ultimate = !proxy_level_for_emplaced,
            .last_proxied_update = time_point_sec(::now())
        };});
        
        agent = agents_idx.find(key);
        if (emplaced)
            *emplaced = true;
    }
    return agent;
}

void stake::updatefunds(name account, symbol_code token_code, symbol_code purpose_code) {
    //require_auth(anyone);
    params params_table(table_owner, table_owner.value);
    const auto& param = get_param(params_table, purpose_code, token_code, static_cast<bool>(purpose_code));
    if (static_cast<bool>(purpose_code))
        update_stake_proxied(purpose_code, token_code, account, param.frame_length, false);
    else
        for (auto& p : param.purposes)
            update_stake_proxied(p, token_code, account, param.frame_length, false);
}

int64_t stake::update_purpose_balance(name issuer, agents_idx_t& agents_idx, name account, symbol_code token_code, symbol_code purpose_code, int64_t total_amount, int64_t total_balance) {
    if (!total_balance)
        return 0;
    
    auto agent = get_agent_itr(purpose_code, token_code, agents_idx, account);

    auto amount = total_balance < 0 ? total_amount : safe_prop(total_amount, agent->balance, total_balance);
    if (amount < 0)
        amount = std::max(amount, -agent->balance);
    
    if (agent->get_total_funds()) {
        agents_idx.modify(agent, name(), [&](auto& a) { a.balance += amount; });
    }
    else {
        agents_idx.modify(agent, name(), [&](auto& a) {
            a.balance = amount;
            a.shares_sum = amount;
            a.own_share = amount;
        });
    }
    
    update_stats(structures::stat {
        .id = 0,
        .token_code = token_code,
        .purpose_code = purpose_code,
        .total_staked = amount
    }, issuer);
    return amount;
}

void stake::change_balance(name account, asset quantity, symbol_code purpose_code) {
    eosio_assert(quantity.is_valid(), "invalid quantity");
    auto token_code = quantity.symbol.code();
    auto issuer = eosio::token::get_issuer(config::token_name, token_code);
    require_auth(issuer);
    params params_table(table_owner, table_owner.value);
    const auto& param = get_param(params_table, purpose_code, token_code, static_cast<bool>(purpose_code));

    agents agents_table(table_owner, table_owner.value);
    auto agents_idx = agents_table.get_index<"bykey"_n>();
    
    int64_t actual_amount = 0;
    if (static_cast<bool>(purpose_code))
        actual_amount = update_purpose_balance(issuer, agents_idx, account, token_code, purpose_code, quantity.amount);
    else {
        int64_t total_balance = 0;
        for (auto& p : param.purposes) {
            total_balance += get_agent_itr(p, token_code, agents_idx, account)->balance;
        }
        
        eosio_assert(param.purposes.size(), "no purpose");
        auto last_purpose_itr = param.purposes.end();
        --last_purpose_itr;
        auto total_amount = quantity.amount;
        auto left_amount = total_amount;
        for (auto purpose_itr = param.purposes.begin(); purpose_itr != last_purpose_itr; ++purpose_itr) {
            auto cur_actual_amount = update_purpose_balance(issuer, agents_idx, account, token_code, *purpose_itr, total_amount, total_balance);
            left_amount -= cur_actual_amount;
            actual_amount += cur_actual_amount;
        }
        actual_amount += update_purpose_balance(issuer, agents_idx, account, token_code, param.purposes.back(), left_amount);
    }
    
    if (quantity.amount < 0) {
        quantity.amount = -actual_amount;
        INLINE_ACTION_SENDER(eosio::token, transfer)(config::token_name, {_self, config::active_name},
            {_self, issuer, quantity, ""});
        INLINE_ACTION_SENDER(eosio::token, retire)(config::token_name, {issuer, config::amerce_name}, {quantity, ""});
    }
    else {
        //we don't need actual_amount in this case
        INLINE_ACTION_SENDER(eosio::token, issue)(config::token_name, {issuer, config::reward_name}, {issuer, quantity, ""});
        INLINE_ACTION_SENDER(eosio::token, transfer)(config::token_name, {issuer, config::reward_name},
            {issuer, _self, quantity, config::reward_memo});    
    }
}

void stake::amerce(name account, asset quantity, symbol_code purpose_code) {
    eosio_assert(quantity.amount > 0, "quantity must be positive");
    eosio::print("stake::amerce: account = ", account, ", quantity = ", quantity, "\n");
    quantity.amount = -quantity.amount;
    change_balance(account, quantity, purpose_code);
}

void stake::reward(name account, asset quantity, symbol_code purpose_code) {
    eosio_assert(quantity.amount > 0, "quantity must be positive");
    eosio::print("stake::reward: account = ", account, ", quantity = ", quantity, "\n");
    change_balance(account, quantity, purpose_code);
}

} /// namespace cyber

DISPATCH_WITH_TRANSFER(cyber::stake, cyber::config::token_name, on_transfer,
    (create)(enable)(delegate)(setgrntterms)(recall)(withdraw)(claim)(cancelwd)
    (setproxylvl)(setproxyfee)(setminstaked)(setkey)
    (updatefunds)(amerce)(reward)
)
