// In the future?
// #include <thread>

#include <algorithm>

#include <eosio/action.hpp>

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
      //    internal_use_do_not_use::send_context_free_inline(const_cast<char*>(act.data.data()), act.data.size());
      // }};

      // auto execute_ctx_actions{
      //    [&trx.actions](const action& act) {
      //    internal_use_do_not_use::send_inline(const_cast<char*>(act.data.data()), act.data.size());
      // }};

      // std::thread t0{execute_ctx_free_actions};
      // std::thread t1{execute_ctx_actions};
      // t0.join();
      // t1.join();

      // auto send_action{
      //    [&](const action& act) {
      //       // std::vector<std::byte> serialized_action(16,0); // Initial 16 bytes for `account` and `name`.
      //       act.send();
      // }};

      // std::for_each(trx.context_free_actions.cbegin(), trx.context_free_actions.cend(), send_action);
      // std::for_each(trx.actions.cbegin(), trx.actions.cend(), send_action);

      
      // Assert at the proposal stage that there are no ctx free actions.
      // for (const auto& act: trx.context_free_actions) {
      //    act.send();
      //    internal_use_do_not_use::send_context_free_inline(const_cast<char*>(act.data.data()), act.data.size());
      //    // serialized_action.resize(16);
      //    // serialized_action.clear();
      // }

      for (const auto& act: trx.actions) {
          act.send();
         // internal_use_do_not_use::send_inline(const_cast<char*>(act.data.data()), act.data.size());
         // serialized_action.resize(16);
         // serialized_action.clear();
      }
   }
}

} /// namespace eosio


// 1) Going to have to iterate over the actions in the transaction and send them inline.
// 2) Going to have to look at the action type to see how this is done.
// 3) ignore, ignores deserializing as an optimization.
// 4) Send inline intrinsic.
// 5) There are two member functions in the action type: Send and Send-Context-Free.
