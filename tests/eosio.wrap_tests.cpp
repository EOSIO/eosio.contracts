#include <boost/test/unit_test.hpp>

#include <Runtime/Runtime.h>

#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>

#include <fc/log/logger.hpp>
#include <fc/variant_object.hpp>

#include "contracts.hpp"

using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;

using mvo = fc::mutable_variant_object;

class eosio_wrap_tester : public tester {
public:

   eosio_wrap_tester() {
      create_accounts( { "eosio.msig"_n, "prod1"_n, "prod2"_n, "prod3"_n, "prod4"_n, "prod5"_n, "alice"_n, "bob"_n, "carol"_n } );
      produce_block();


      base_tester::push_action(config::system_account_name, "setpriv"_n,
                               config::system_account_name,  mutable_variant_object()
                               ("account", "eosio.msig")
                               ("is_priv", 1)
      );

      set_code( "eosio.msig"_n, contracts::msig_wasm() );
      set_abi( "eosio.msig"_n, contracts::msig_abi().data() );

      produce_blocks();

      signed_transaction trx;
      set_transaction_headers(trx);
      authority auth( 1, {}, {{{config::system_account_name, config::active_name}, 1}} );
      trx.actions.emplace_back( vector<permission_level>{{config::system_account_name, config::active_name}},
                                newaccount{
                                   .creator  = config::system_account_name,
                                   .name     = "eosio.wrap"_n,
                                   .owner    = auth,
                                   .active   = auth,
                                });

      set_transaction_headers(trx);
      trx.sign( get_private_key( config::system_account_name, "active" ), control->get_chain_id()  );
      push_transaction( trx );

      base_tester::push_action(config::system_account_name, "setpriv"_n,
                                 config::system_account_name,  mutable_variant_object()
                                 ("account", "eosio.wrap")
                                 ("is_priv", 1)
      );

      auto system_private_key = get_private_key( config::system_account_name, "active" );
      set_code( "eosio.wrap"_n, contracts::wrap_wasm(), &system_private_key );
      set_abi( "eosio.wrap"_n, contracts::wrap_abi().data(), &system_private_key );

      produce_blocks();

      set_authority( config::system_account_name, config::active_name,
                     authority( 1, {{get_public_key( config::system_account_name, "active" ), 1}},
                                   {{{config::producers_account_name, config::active_name}, 1}} ),
                     config::owner_name,
                     { { config::system_account_name, config::owner_name } },
                     { get_private_key( config::system_account_name, "active" ) }
                   );

      set_producers( {"prod1"_n, "prod2"_n, "prod3"_n, "prod4"_n, "prod5"_n} );

      produce_blocks();

      const auto& accnt = control->db().get<account_object,by_name>( "eosio.wrap"_n );
      abi_def abi;
      BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
      abi_ser.set_abi(abi, abi_serializer_max_time);

      while( control->pending_block_producer().to_string() == "eosio" ) {
         produce_block();
      }
   }

   void propose( name proposer, name proposal_name, vector<permission_level> requested_permissions, const transaction& trx ) {
      push_action( "eosio.msig"_n, "propose"_n, proposer, mvo()
                     ("proposer",      proposer)
                     ("proposal_name", proposal_name)
                     ("requested",     requested_permissions)
                     ("trx",           trx)
      );
   }

   void approve( name proposer, name proposal_name, name approver ) {
      push_action( "eosio.msig"_n, "approve"_n, approver, mvo()
                     ("proposer",      proposer)
                     ("proposal_name", proposal_name)
                     ("level",         permission_level{approver, config::active_name} )
      );
   }

   void unapprove( name proposer, name proposal_name, name unapprover ) {
      push_action( "eosio.msig"_n, "unapprove"_n, unapprover, mvo()
                     ("proposer",      proposer)
                     ("proposal_name", proposal_name)
                     ("level",         permission_level{unapprover, config::active_name})
      );
   }

   transaction wrap_exec( account_name executer, const transaction& trx, uint32_t expiration = base_tester::DEFAULT_EXPIRATION_DELTA );

   transaction reqauth( account_name from, const vector<permission_level>& auths, uint32_t expiration = base_tester::DEFAULT_EXPIRATION_DELTA );

   abi_serializer abi_ser;
};

transaction eosio_wrap_tester::wrap_exec( account_name executer, const transaction& trx, uint32_t expiration ) {
   fc::variants v;
   v.push_back( fc::mutable_variant_object()
                  ("actor", executer)
                  ("permission", name{config::active_name})
              );
  v.push_back( fc::mutable_variant_object()
                 ("actor", "eosio.wrap")
                 ("permission", name{config::active_name})
             );
   auto act_obj = fc::mutable_variant_object()
                     ("account", "eosio.wrap")
                     ("name", "exec")
                     ("authorization", v)
                     ("data", fc::mutable_variant_object()("executer", executer)("trx", trx) );
   transaction trx2;
   set_transaction_headers(trx2, expiration);
   action act;
   abi_serializer::from_variant( act_obj, act, get_resolver(), abi_serializer_max_time );
   trx2.actions.push_back( std::move(act) );
   return trx2;
}

transaction eosio_wrap_tester::reqauth( account_name from, const vector<permission_level>& auths, uint32_t expiration ) {
   fc::variants v;
   for ( auto& level : auths ) {
      v.push_back(fc::mutable_variant_object()
                  ("actor", level.actor)
                  ("permission", level.permission)
      );
   }
   auto act_obj = fc::mutable_variant_object()
                     ("account", name{config::system_account_name})
                     ("name", "reqauth")
                     ("authorization", v)
                     ("data", fc::mutable_variant_object() ("from", from) );
   transaction trx;
   set_transaction_headers(trx, expiration);
   action act;
   abi_serializer::from_variant( act_obj, act, get_resolver(), abi_serializer_max_time );
   trx.actions.push_back( std::move(act) );
   return trx;
}

BOOST_AUTO_TEST_SUITE(eosio_wrap_tests)

BOOST_FIXTURE_TEST_CASE( wrap_exec_direct, eosio_wrap_tester ) try {
   transaction trx = reqauth( "bob"_n, {permission_level{"bob"_n, config::active_name}} );
   signed_transaction wrap_trx( wrap_exec( "alice"_n, trx ), {}, {} );
   
   wrap_trx.sign( get_private_key( "alice"_n, "active" ), control->get_chain_id() );
   for( const auto& actor : {"prod1", "prod2", "prod3", "prod4"} ) {
       wrap_trx.sign( get_private_key( actor, "active" ), control->get_chain_id() );
   }

   transaction_trace_ptr trx_trace;
   trx_trace = push_transaction( wrap_trx );

   produce_block();
   wdump((fc::json::to_pretty_string(trx_trace)));

   BOOST_REQUIRE( bool(trx_trace) );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, trx_trace->receipt->status );
   BOOST_REQUIRE_EQUAL( 2, trx_trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, trx_trace->action_traces[0].action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, trx_trace->action_traces[0].creator_action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, trx_trace->action_traces[0].closest_unnotified_ancestor_action_ordinal );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", action_name{trx_trace->action_traces[0].receiver} );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", name{trx_trace->action_traces[0].act.account} );
   BOOST_REQUIRE_EQUAL( "exec", name{trx_trace->action_traces[0].act.name} );
   BOOST_REQUIRE_EQUAL( "alice", name{trx_trace->action_traces[0].act.authorization[0].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{trx_trace->action_traces[0].act.authorization[0].permission} );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", name{trx_trace->action_traces[0].act.authorization[1].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{trx_trace->action_traces[0].act.authorization[1].permission} );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{2}, trx_trace->action_traces[1].action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, trx_trace->action_traces[1].creator_action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, trx_trace->action_traces[1].closest_unnotified_ancestor_action_ordinal );
   BOOST_REQUIRE_EQUAL( "eosio", action_name{trx_trace->action_traces[1].receiver} );
   BOOST_REQUIRE_EQUAL( "eosio", name{trx_trace->action_traces[1].act.account} );
   BOOST_REQUIRE_EQUAL( "reqauth", name{trx_trace->action_traces[1].act.name} );
   BOOST_REQUIRE_EQUAL( "bob", name{trx_trace->action_traces[1].act.authorization[0].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{trx_trace->action_traces[1].act.authorization[0].permission} );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( wrap_with_msig, eosio_wrap_tester ) try {
   transaction trx = reqauth( "bob"_n, {permission_level{"bob"_n, config::active_name}} );
   signed_transaction wrap_trx( wrap_exec( "alice"_n, trx), {}, {} );

   propose( "carol"_n, "first"_n,
            { {"alice"_n, "active"_n},
              {"prod1"_n, "active"_n}, {"prod2"_n, "active"_n}, {"prod3"_n, "active"_n}, {"prod4"_n, "active"_n}, {"prod5"_n, "active"_n} },
            wrap_trx );
   
   approve( "carol"_n, "first"_n, "alice"_n ); // alice must approve since she is the executer of the wrap::exec action
   
   // More than 2/3 of block producers approve
   approve( "carol"_n, "first"_n, "prod1"_n );
   approve( "carol"_n, "first"_n, "prod2"_n );
   approve( "carol"_n, "first"_n, "prod3"_n );
   approve( "carol"_n, "first"_n, "prod4"_n );

   transaction_trace_ptr trx_trace;
   transaction_trace_ptr deferred_trx_trace;

   // Now the proposal should be ready to execute
   trx_trace = push_action( "eosio.msig"_n, "exec"_n, "alice"_n, mvo()
                              ("proposer",      "carol")
                              ("proposal_name", "first")
                              ("executer",      "alice")
   );

   control->applied_transaction.connect(
   [&]( std::tuple<const transaction_trace_ptr&, const signed_transaction&> p ) {
      const auto& t = std::get<0>(p);
      if( t->scheduled ) { deferred_trx_trace = t; }
   } );
   
   produce_block();
   wdump((fc::json::to_pretty_string(trx_trace)));
   wdump((fc::json::to_pretty_string(deferred_trx_trace)));

   BOOST_REQUIRE( bool(trx_trace) );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, trx_trace->receipt->status );
   BOOST_REQUIRE_EQUAL( 1, trx_trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, trx_trace->action_traces[0].action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, trx_trace->action_traces[0].creator_action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, trx_trace->action_traces[0].closest_unnotified_ancestor_action_ordinal );
   BOOST_REQUIRE_EQUAL( "eosio.msig", action_name{trx_trace->action_traces[0].receiver} );
   BOOST_REQUIRE_EQUAL( "eosio.msig", name{trx_trace->action_traces[0].act.account} );
   BOOST_REQUIRE_EQUAL( "exec", name{trx_trace->action_traces[0].act.name} );
   BOOST_REQUIRE_EQUAL( "alice", name{trx_trace->action_traces[0].act.authorization[0].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{trx_trace->action_traces[0].act.authorization[0].permission} );

   BOOST_REQUIRE( bool(deferred_trx_trace) );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, deferred_trx_trace->receipt->status );
   BOOST_REQUIRE_EQUAL( 2, deferred_trx_trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, deferred_trx_trace->action_traces[0].action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, deferred_trx_trace->action_traces[0].creator_action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, deferred_trx_trace->action_traces[0].closest_unnotified_ancestor_action_ordinal );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", action_name{deferred_trx_trace->action_traces[0].receiver} );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", name{deferred_trx_trace->action_traces[0].act.account} );
   BOOST_REQUIRE_EQUAL( "exec", name{deferred_trx_trace->action_traces[0].act.name} );
   BOOST_REQUIRE_EQUAL( "alice", name{deferred_trx_trace->action_traces[0].act.authorization[0].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{deferred_trx_trace->action_traces[0].act.authorization[0].permission} );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", name{deferred_trx_trace->action_traces[0].act.authorization[1].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{deferred_trx_trace->action_traces[0].act.authorization[1].permission} );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{2}, deferred_trx_trace->action_traces[1].action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, deferred_trx_trace->action_traces[1].creator_action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, deferred_trx_trace->action_traces[1].closest_unnotified_ancestor_action_ordinal );
   BOOST_REQUIRE_EQUAL( "eosio", action_name{deferred_trx_trace->action_traces[1].receiver} );
   BOOST_REQUIRE_EQUAL( "eosio", name{deferred_trx_trace->action_traces[1].act.account} );
   BOOST_REQUIRE_EQUAL( "reqauth", name{deferred_trx_trace->action_traces[1].act.name} );
   BOOST_REQUIRE_EQUAL( "bob", name{deferred_trx_trace->action_traces[1].act.authorization[0].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{deferred_trx_trace->action_traces[1].act.authorization[0].permission} );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( wrap_with_msig_unapprove, eosio_wrap_tester ) try {
   transaction trx = reqauth( "bob"_n, {permission_level{"bob"_n, config::active_name}} );
   signed_transaction wrap_trx( wrap_exec( "alice"_n, trx ), {}, {} );

   propose( "carol"_n, "first"_n,
            { {"alice"_n, "active"_n},
              {"prod1"_n, "active"_n}, {"prod2"_n, "active"_n}, {"prod3"_n, "active"_n}, {"prod4"_n, "active"_n}, {"prod5"_n, "active"_n} },
            wrap_trx );

   approve( "carol"_n, "first"_n, "alice"_n ); // alice must approve since she is the executer of the wrap::exec action

   // 3 of the 4 needed producers approve
   approve( "carol"_n, "first"_n, "prod1"_n );
   approve( "carol"_n, "first"_n, "prod2"_n );
   approve( "carol"_n, "first"_n, "prod3"_n );

   // first producer takes back approval
   unapprove( "carol"_n, "first"_n, "prod1"_n );

   // fourth producer approves but the total number of approving producers is still 3 which is less than two-thirds of producers
   approve( "carol"_n, "first"_n, "prod4"_n );

   produce_block();

   // The proposal should not have sufficient approvals to pass the authorization checks of eosio.wrap::exec.
   BOOST_REQUIRE_EXCEPTION( push_action( "eosio.msig"_n, "exec"_n, "alice"_n, mvo()
                                          ("proposer",      "carol")
                                          ("proposal_name", "first")
                                          ("executer",      "alice")
                                       ), eosio_assert_message_exception,
                                          eosio_assert_message_is("transaction authorization failed")
   );
} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE( wrap_with_msig_producers_change, eosio_wrap_tester ) try {
   create_accounts( { "newprod1"_n } );

   transaction trx = reqauth( "bob"_n, {permission_level{"bob"_n, config::active_name}} );
   signed_transaction wrap_trx( wrap_exec( "alice"_n, trx, 36000 ), {}, {} );

   propose( "carol"_n, "first"_n,
            { {"alice"_n, "active"_n},
              {"prod1"_n, "active"_n}, {"prod2"_n, "active"_n}, {"prod3"_n, "active"_n}, {"prod4"_n, "active"_n}, {"prod5"_n, "active"_n} },
            wrap_trx );

   approve( "carol"_n, "first"_n, "alice"_n ); // alice must approve since she is the executer of the wrap::exec action

   // 2 of the 4 needed producers approve
   approve( "carol"_n, "first"_n, "prod1"_n );
   approve( "carol"_n, "first"_n, "prod2"_n );

   produce_block();

   set_producers( {"prod1"_n, "prod2"_n, "prod3"_n, "prod4"_n, "prod5"_n, "newprod1"_n} ); // With 6 producers, the 2/3+1 threshold becomes 5

   while( control->active_producers().producers.size() != 6 ) {
      produce_block();
   }

   // Now two more block producers approve which would have been sufficient under the old schedule but not the new one.
   approve( "carol"_n, "first"_n, "prod3"_n );
   approve( "carol"_n, "first"_n, "prod4"_n );

   produce_block();

   // The proposal has four of the five requested approvals but they are not sufficient to satisfy the authorization checks of eosio.wrap::exec.
   BOOST_REQUIRE_EXCEPTION( push_action( "eosio.msig"_n, "exec"_n, "alice"_n, mvo()
                                          ("proposer",      "carol")
                                          ("proposal_name", "first")
                                          ("executer",      "alice")
                                       ), eosio_assert_message_exception,
                                          eosio_assert_message_is("transaction authorization failed")
   );

   // Unfortunately the new producer cannot approve because they were not in the original requested approvals.
   BOOST_REQUIRE_EXCEPTION( approve( "carol"_n, "first"_n, "newprod1"_n ),
                            eosio_assert_message_exception,
                            eosio_assert_message_is("approval is not on the list of requested approvals")
   );

   // But prod5 still can provide the fifth approval necessary to satisfy the 2/3+1 threshold of the new producer set
   approve( "carol"_n, "first"_n, "prod5"_n );

   transaction_trace_ptr trx_trace;
   transaction_trace_ptr deferred_trx_trace;

   // Now the proposal should be ready to execute
   trx_trace = push_action( "eosio.msig"_n, "exec"_n, "alice"_n, mvo()
                              ("proposer",      "carol")
                              ("proposal_name", "first")
                              ("executer",      "alice")
   );

   control->applied_transaction.connect(
   [&]( std::tuple<const transaction_trace_ptr&, const signed_transaction&> p ) {
      const auto& t = std::get<0>(p);
      if( t->scheduled ) { deferred_trx_trace = t; }
   } );
   
   produce_block();
   wdump((fc::json::to_pretty_string(trx_trace)));
   wdump((fc::json::to_pretty_string(deferred_trx_trace)));

   BOOST_REQUIRE( bool(trx_trace) );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, trx_trace->receipt->status );
   BOOST_REQUIRE_EQUAL( 1, trx_trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, trx_trace->action_traces[0].action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, trx_trace->action_traces[0].creator_action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, trx_trace->action_traces[0].closest_unnotified_ancestor_action_ordinal );
   BOOST_REQUIRE_EQUAL( "eosio.msig", action_name{trx_trace->action_traces[0].receiver} );
   BOOST_REQUIRE_EQUAL( "eosio.msig", name{trx_trace->action_traces[0].act.account} );
   BOOST_REQUIRE_EQUAL( "exec", name{trx_trace->action_traces[0].act.name} );
   BOOST_REQUIRE_EQUAL( "alice", name{trx_trace->action_traces[0].act.authorization[0].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{trx_trace->action_traces[0].act.authorization[0].permission} );

   BOOST_REQUIRE( bool(deferred_trx_trace) );
   BOOST_REQUIRE_EQUAL( transaction_receipt::executed, deferred_trx_trace->receipt->status );
   BOOST_REQUIRE_EQUAL( 2, deferred_trx_trace->action_traces.size() );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, deferred_trx_trace->action_traces[0].action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, deferred_trx_trace->action_traces[0].creator_action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{0}, deferred_trx_trace->action_traces[0].closest_unnotified_ancestor_action_ordinal );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", action_name{deferred_trx_trace->action_traces[0].receiver} );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", name{deferred_trx_trace->action_traces[0].act.account} );
   BOOST_REQUIRE_EQUAL( "exec", name{deferred_trx_trace->action_traces[0].act.name} );
   BOOST_REQUIRE_EQUAL( "alice", name{deferred_trx_trace->action_traces[0].act.authorization[0].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{deferred_trx_trace->action_traces[0].act.authorization[0].permission} );
   BOOST_REQUIRE_EQUAL( "eosio.wrap", name{deferred_trx_trace->action_traces[0].act.authorization[1].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{deferred_trx_trace->action_traces[0].act.authorization[1].permission} );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{2}, deferred_trx_trace->action_traces[1].action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, deferred_trx_trace->action_traces[1].creator_action_ordinal );
   BOOST_REQUIRE_EQUAL( fc::unsigned_int{1}, deferred_trx_trace->action_traces[1].closest_unnotified_ancestor_action_ordinal );
   BOOST_REQUIRE_EQUAL( "eosio", action_name{deferred_trx_trace->action_traces[1].receiver} );
   BOOST_REQUIRE_EQUAL( "eosio", name{deferred_trx_trace->action_traces[1].act.account} );
   BOOST_REQUIRE_EQUAL( "reqauth", name{deferred_trx_trace->action_traces[1].act.name} );
   BOOST_REQUIRE_EQUAL( "bob", name{deferred_trx_trace->action_traces[1].act.authorization[0].actor} );
   BOOST_REQUIRE_EQUAL( "active", name{deferred_trx_trace->action_traces[1].act.authorization[0].permission} );
} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
