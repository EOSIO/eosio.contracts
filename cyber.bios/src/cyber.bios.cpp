#include <cyber.bios/cyber.bios.hpp>
#include <cyber.bios/config.hpp>
#include <cyber.govern/cyber.govern.hpp>
#include <cyber.govern/config.hpp>
#include <cyber.stake/cyber.stake.hpp>

namespace cyber {
    
using namespace cyber::config;

void bios::onblock(ignore<block_header> header) {
    require_auth(_self);
    
    eosio::block_timestamp timestamp;
    name producer;
    _ds >> timestamp >> producer;
    
    auto state = state_singleton(_self, _self.value);
    
    if (!state.exists()) {
        state.set(state_info{ .last_govern_update = time_point_sec(0) }, _self);
    }
    
    eosio::print("bios::onblock, producer is ", producer, "\n");
    const int64_t now = ::now();
    auto s = state.get();
    if (now - s.last_govern_update.utc_seconds >= govern_update_window) {
        INLINE_ACTION_SENDER(govern, update)(govern_name, {{govern_name, active_name}}, {producer});
        s.last_govern_update = time_point_sec(now);
    }
    
    state.set(s, _self);
}
}

EOSIO_DISPATCH( cyber::bios, (setglimits)(setprods)(setparams)(reqauth)(setabi)(setcode)(onblock) )
