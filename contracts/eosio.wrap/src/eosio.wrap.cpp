// In the future?
// #include <thread>

#include <eosio.wrap/eosio.wrap.hpp>

namespace eosio {

   void wrap::exec( name executer, transaction trx) {
   // Redundant require auth to make sure the contract itself is executing the action??
   // How can this be executed when 15/21 producers must sign off on the action?
   // Won't `eosio.wrap` have to pay for all of the resources now?
   require_auth( get_self() ); 
   require_auth( executer );

   // Inline execution of the wrapped transaction.
   {
      wrap::exec_action exec_act{ get_self(), { get_self(), "active"_n } };

      // In the future?
      // auto execute_ctx_free_actions{
      //    [&trx.context_free_actions](const action& act) {
      //       exec_act.send( executer, act );
      // }};

      // auto execute_ctx_actions{
      //    [&trx.actions](const action& act) {
      //       exec_act.send( executer, act );
      // }};

      // std::thread t0{execute_ctx_free_actions};
      // std::thread t1{execute_ctx_actions};
      // t0.join();
      // t1.join();

      for (const auto& act: trx.context_free_actions) {
         exec_act.send( executer, act );
      }

      for (const auto& act: trx.actions) {
         exec_act.send( executer, act );
      }
   }
}

} /// namespace eosio


// 1) Going to have to iterate over the actions in the transaction and send them inline.
// 2) Going to have to look at the action type to see how this is done.
// 3) ignore, ignores deserializing as an optimization.
// 4) Send inline intrinsic.
// 5) There are two member functions in the action type: Send and Send-Context-Free.
// 6) 
