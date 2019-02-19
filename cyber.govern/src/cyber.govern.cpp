#include <cyber.govern/cyber.govern.hpp>
#include <eosiolib/privileged.hpp> 
#include <cyber.stake/cyber.stake.hpp>
#include <cyber.govern/config.hpp>

using namespace cyber::config;

namespace cyber {

void govern::update(name producer) {
    require_auth(_self);
    eosio::print("govern::update, producer is ", producer, "\n");
    
    auto state = state_singleton(_self, _self.value);
    if (!state.exists()) {
        state.set(state_info{ .last_producers_num = 1 }, _self);
    }
    
    auto top_producers = stake::get_top(producers_num, system_token.code());
    eosio_assert(top_producers.size() <= std::numeric_limits<uint16_t>::max(), "SYSTEM: incorrect producers num");
    auto cur_producers_num = static_cast<uint16_t>(top_producers.size());
    if (cur_producers_num >= state.get().last_producers_num) {
        auto packed_schedule = pack(top_producers);
        if (set_proposed_producers(packed_schedule.data(),  packed_schedule.size()) >= 0) {
            state.set(state_info{ .last_producers_num = cur_producers_num }, _self);
        }
    }
}

}

EOSIO_DISPATCH( cyber::govern, (update))
