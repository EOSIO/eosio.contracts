#include <eosio.sudo/eosio.sudo.hpp>

namespace eosio {

/*
exec function manually parses input data (instead of taking parsed arguments from dispatcher)
because parsing data in the dispatcher uses too much CPU if the included transaction is very big

If we use dispatcher the function signature should be:

void sudo::exec( name executer,
                 transaction  trx )
*/

void sudo::exec(ignore<name>, ignore<transaction>) {
   require_auth( _self );

   constexpr size_t max_stack_buffer_size = 512;

   name executer;

   _ds >> executer;

   require_auth( executer );

   send_deferred( (uint128_t(executer.value) << 64) | current_time(), executer.value, _ds.pos(), _ds.remaining() );
}

} /// namespace eosio

EOSIO_DISPATCH( eosio::sudo, (exec) )
