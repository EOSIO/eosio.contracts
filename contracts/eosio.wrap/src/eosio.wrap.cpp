#include <eosio.wrap/eosio.wrap.hpp>

namespace eosio {

void wrap::exec( name executer, transaction trx) {
   require_auth( get_self() );
   require_auth( executer );

   check( trx.context_free_actions.empty(), "not allowed to `exec` a transaction with context-free actions" );

   // Inline execution of the wrapped transaction.
   for (const auto& act: trx.actions) {
      act.send();
   }
}

} /// namespace eosio
