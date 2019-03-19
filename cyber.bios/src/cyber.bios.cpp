#include <cyber.bios/cyber.bios.hpp>
#include <cyber.bios/config.hpp>
#include <cyber.govern/cyber.govern.hpp>

namespace cyber {
    
using namespace cyber::config;

void bios::onblock(ignore<block_header> header) {
    require_auth(_self);
    
    eosio::block_timestamp timestamp;
    name producer;
    _ds >> timestamp >> producer;
    INLINE_ACTION_SENDER(govern, onblock)(govern_name, {{govern_name, active_name}}, {producer});
    //TODO: update names
}
}

EOSIO_DISPATCH( cyber::bios, (setglimits)(setprods)(setparams)(reqauth)(setabi)(setcode)(onblock) )
