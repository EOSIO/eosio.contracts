#include <cyber.govern/cyber.govern.hpp>
#include <eosiolib/privileged.hpp> 
#include <cyber.stake/cyber.stake.hpp>
#include <cyber.govern/config.hpp>

using namespace cyber::config;

namespace cyber {

void govern::setignored(std::vector<name> ignored_producers) {
    require_auth(_self);
    auto state = state_singleton(_self, _self.value);
    auto s = state.get();
    s.ignored_producers = ignored_producers;
    state.set(s, _self);
}

void govern::onblock(name producer) {
    require_auth(_self);
    
    auto state = state_singleton(_self, _self.value);
    auto s = state.get_or_default(structures::state_info { .block_num = 0, .last_producers_num = 1 });
    
    if (std::find(s.ignored_producers.begin(), s.ignored_producers.end(), producer) != s.ignored_producers.end()) {
        return;
    }
    s.block_num++;
    
    eosio::print("govern::onblock: producer = ", producer, "; block = ", s.block_num, "\n");
    
    producers producers_table(_self, _self.value);
    if (s.block_num % config::sum_up_interval == 0) {
        sum_up(producers_table);
    }
    if (s.block_num % config::reward_for_staked_interval == 0) {
        update_and_reward_producers(producers_table);
    }
    
    auto prod_itr = producers_table.end();
    if (producer != config::internal_name) {
        prod_itr = producers_table.find(producer.value);
        eosio_assert(prod_itr != producers_table.end(), "SYSTEM: producer does not exist");
        check_missing_blocks(producers_table, prod_itr, s.block_num);
    }
    
    if (maybe_promote_active_producers(s)) {
        s.active_producers_num = s.pending_active_producers.size();
        s.pending_active_producers.clear();
    }
    
    if (prod_itr != producers_table.end()) {
        producers_table.modify(prod_itr, name(), [&](auto& a) {
            a.confirmed_balance += a.pending_balance + config::block_reward;
            a.pending_balance = 0;
            a.last_block_produced = s.block_num;
        });
    }

    state.set(s, _self);
}

govern::change_of_participants govern::get_change_of_producers(producers& producers_table, std::vector<name> new_producers, bool active_only) {
    std::sort(new_producers.begin(), new_producers.end());
    std::vector<name> old_producers;
    old_producers.reserve(new_producers.size());
    
    auto prod_itr = producers_table.begin();
    while (prod_itr != producers_table.end()) {
        if (!active_only || prod_itr->is_active()) {
            old_producers.emplace_back(prod_itr->account);
        }
        ++prod_itr;
    }
    
    change_of_participants ret;
   
    std::set_difference(new_producers.begin(), new_producers.end(), old_producers.begin(), old_producers.end(), 
        std::inserter(ret.hired, ret.hired.begin()));
    
    std::set_difference(old_producers.begin(), old_producers.end(), new_producers.begin(), new_producers.end(),
        std::inserter(ret.fired, ret.fired.begin()));
    
    return ret;
}

void govern::setactprods(std::vector<name> pending_active_producers) {

    require_auth(_self);
    std::sort(pending_active_producers.begin(), pending_active_producers.end());
    auto state = state_singleton(_self, _self.value);
    auto s = state.get();
    
    s.pending_active_producers = pending_active_producers;
    state.set(s, _self);
    
}

bool govern::maybe_promote_active_producers(const structures::state_info& s) {
    if (!s.pending_active_producers.size()) {
        return false;
    }
    eosio_assert(s.block_num, "SYSTEM: incorrect block_num val");
    
    producers producers_table(_self, _self.value);
    auto change_of_producers = get_change_of_producers(producers_table, s.pending_active_producers, true);
    
    for (const auto& prod : change_of_producers.hired) {
        auto prod_itr = producers_table.find(prod.value);
        if (prod_itr != producers_table.end()) {
            producers_table.modify(prod_itr, name(), [&](auto& a) { a.commencement_block = s.block_num; });
        }
        else {
            producers_table.emplace(_self, [&]( auto &a ) { a = structures::producer {
                .account = prod,
                .elected = false,
                .last_block_produced = s.block_num - 1,
                .commencement_block = s.block_num
            };});
        }
    }
    for (const auto& prod : change_of_producers.fired) {
        auto prod_itr = producers_table.find(prod.value);
        check_missing_blocks(producers_table, prod_itr, s.block_num);
        if (prod_itr != producers_table.end()) {
            producers_table.modify(prod_itr, name(), [&](auto& a) { a.commencement_block = 0; });
        }
    }
    return true;
}

void govern::shrink_to_active_producers(producers& producers_table, std::vector<std::pair<name, public_key> >& arg) {
    if (arg.size() > config::active_producers_num) {
        std::partial_sort(
            arg.begin() + config::active_top_producers_num, 
            arg.begin() + config::active_producers_num,
            arg.end(),
            [&producers_table](const std::pair<name, public_key>& lhs, const std::pair<name, public_key>& rhs) {
                auto lhs_prod_itr = producers_table.find(lhs.first.value);
                auto rhs_prod_itr = producers_table.find(rhs.first.value);

                auto lhs_last_block_produced = lhs_prod_itr != producers_table.end() ?
                    lhs_prod_itr->last_block_produced : std::numeric_limits<uint32_t>::max();
                auto rhs_last_block_produced = rhs_prod_itr != producers_table.end() ?
                    rhs_prod_itr->last_block_produced : std::numeric_limits<uint32_t>::max();
                return std::tie(lhs_last_block_produced, lhs.first) < std::tie(rhs_last_block_produced, rhs.first);
            });
        arg.resize(config::active_producers_num);
    }
}

void govern::update_and_reward_producers(producers& producers_table) {
    auto state = state_singleton(_self, _self.value);
    auto s = state.get();
    auto new_producers = stake::get_top(config::elected_producers_num, system_token.code());
    eosio_assert(new_producers.size() <= std::numeric_limits<uint16_t>::max(), "SYSTEM: incorrect producers num");
    if (new_producers.size() < s.last_producers_num)
        return;
        
    std::vector<name> new_elected_producer_names;
    new_elected_producer_names.reserve(new_producers.size());
    for (const auto& prod : new_producers) {
        new_elected_producer_names.emplace_back(prod.first);
    }

    shrink_to_active_producers(producers_table, new_producers);

    auto packed_schedule = pack(new_producers);
    if (set_proposed_producers(packed_schedule.data(),  packed_schedule.size()) >= 0) {
        s.last_producers_num = static_cast<uint16_t>(new_producers.size());
    }
    
    auto change_of_producers = get_change_of_producers(producers_table, new_elected_producer_names, false);
    eosio_assert(s.block_num || change_of_producers.hired.empty(), "SYSTEM: incorrect block_num val");
    for (const auto& prod : change_of_producers.hired) {
        producers_table.emplace(_self, [&]( auto &a ) { a = structures::producer {
            .account = prod,
            .elected = true,
            .last_block_produced = s.block_num - 1
        };});
    }
    
    for (const auto& prod : change_of_producers.fired) {
        auto prod_itr = producers_table.find(prod.value);
        producers_table.modify(prod_itr, name(), [&](auto& a) { a.elected = false; });
    }
    
    for (auto prod_itr = producers_table.begin(); prod_itr != producers_table.end(); ++prod_itr) {
        producers_table.modify(prod_itr, name(), [&](auto& a) { a.pending_balance += config::reward_of_elected; });
    }
    state.set(s, _self);
    
}

void govern::check_missing_blocks(producers& producers_table, producers::const_iterator prod_itr, uint32_t block_num) {
    auto state = state_singleton(_self, _self.value);
    eosio_assert(prod_itr->is_active(), ("SYSTEM: producer " + prod_itr->account.to_string() + " not active").c_str());
    auto last_block = std::max(prod_itr->last_block_produced, prod_itr->commencement_block - 1);

    eosio_assert(block_num > last_block, "SYSTEM: incorrect block_num val");
    eosio_assert(state.get().active_producers_num, "SYSTEM: incorrect active_producers_num val");
    
    //TODO:? producer_repetitions
    auto period = state.get().active_producers_num;
    auto max_diff = (period * 2) - 1;
    auto diff = block_num - last_block;
    auto missing_blocks_num = diff > max_diff ? ((diff - max_diff) / period) + 1 : 0;
    
    if (missing_blocks_num > config::allowable_number_of_missing_blocks) {
        producers_table.modify(prod_itr, name(), [&](auto& a) {
            a.pending_balance = std::min(a.pending_balance, static_cast<decltype(a.pending_balance)>(0));
            a.confirmed_balance -= missing_blocks_num * config::missing_block_amerce;
        });
    }
}

void govern::sum_up(producers& producers_table) {
    for (auto prod_itr = producers_table.begin(); prod_itr != producers_table.end();) {
        if (prod_itr->confirmed_balance < 0) {
            INLINE_ACTION_SENDER(cyber::stake, amerce)(config::stake_name, {config::issuer_name, config::active_name},
                {prod_itr->account, asset(-prod_itr->confirmed_balance, system_token), symbol_code(0)});
        }
        else if (prod_itr->confirmed_balance > 0) {
            INLINE_ACTION_SENDER(cyber::stake, reward)(config::stake_name, {config::issuer_name, config::active_name},
                {prod_itr->account, asset(prod_itr->confirmed_balance, system_token), symbol_code(0)});
        }
        
        if (prod_itr->elected || prod_itr->is_active()) {
            producers_table.modify(prod_itr, name(), [&](auto& a) { a.confirmed_balance = 0; });
            ++prod_itr;
        }
        else {
            prod_itr = producers_table.erase(prod_itr);
        }
    }
}

}

EOSIO_DISPATCH( cyber::govern, (onblock)(setactprods)(setignored))
