#include <eosio.wrap/eosio.wrap.hpp>

namespace eosio {

void wrap::exec( name executer, transaction trx) {
   require_auth( get_self() );
   require_auth( executer );

   // Inline execution of the wrapped transaction.
   for (const auto& act: trx.actions) {
      act.send();
   }
}

} /// namespace eosio
