#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio/permission.hpp>

#include <eosio.msig/eosio.msig.hpp>

namespace eosio {

transaction_header get_trx_header(const char* ptr, size_t sz);
bool trx_is_authorized(const std::vector<permission_level>& approvals, const std::vector<char>& packed_trx);

template<typename Function>
std::vector<permission_level> get_approvals_and_adjust_table(name self, name proposer, name proposal_name, Function&& table_op) {
   approvals approval_table( self, proposer.value );
   auto approval_table_iter = approval_table.find( proposal_name.value );
   std::vector<permission_level> approvals_vector;
   invalidations invalidations_table( self, self.value );

   if ( approval_table_iter != approval_table.end() ) {
      approvals_vector.reserve( approval_table_iter->provided_approvals.size() );
      for ( const auto& permission : approval_table_iter->provided_approvals ) {
         auto iter = invalidations_table.find( permission.level.actor.value );
         if ( iter == invalidations_table.end() || iter->last_invalidation_time < permission.time ) {
            approvals_vector.push_back(permission.level);
         }
      }
      table_op( approval_table, approval_table_iter );
   } else {
      old_approvals old_approval_table( self, proposer.value );
      const auto& old_approvals_obj = old_approval_table.get( proposal_name.value, "proposal not found" );
      for ( const auto& permission : old_approvals_obj.provided_approvals ) {
         auto iter = invalidations_table.find( permission.actor.value );
         if ( iter == invalidations_table.end() ) {
            approvals_vector.push_back( permission );
         }
      }
      table_op( old_approval_table, old_approvals_obj );
   }
   return approvals_vector;
}

void multisig::propose( name proposer,
                        name proposal_name,
                        std::vector<permission_level> requested,
                        ignore<transaction> trx )
{
   require_auth( proposer );
   auto& ds = get_datastream();

   const char* trx_pos = ds.pos();
   size_t size = ds.remaining();

   transaction_header trx_header;
   std::vector<action> context_free_actions;
   ds >> trx_header;
   check( trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );
   ds >> context_free_actions;
   check( context_free_actions.empty(), "not allowed to `propose` a transaction with context-free actions" );

   proposals proptable( get_self(), proposer.value );
   check( proptable.find( proposal_name.value ) == proptable.end(), "proposal with the same name exists" );

   auto packed_requested = pack(requested);
   auto res =  check_transaction_authorization(
                  trx_pos, size,
                  (const char*)0, 0,
                  packed_requested.data(), packed_requested.size()
               );

   check( res > 0, "transaction authorization failed" );

   std::vector<char> pkd_trans;
   pkd_trans.resize(size);
   memcpy((char*)pkd_trans.data(), trx_pos, size);

   proptable.emplace( proposer, [&]( auto& prop ) {
         prop.proposal_name      = proposal_name;
         prop.packed_transaction = pkd_trans;
         prop.earliest_exec_time = std::optional<time_point>{};
      });

   approvals apptable( get_self(), proposer.value );
   apptable.emplace( proposer, [&]( auto& a ) {
         a.proposal_name = proposal_name;
         a.requested_approvals.reserve( requested.size() );
         for ( auto& level : requested ) {
            a.requested_approvals.push_back( approval{ level, time_point{ microseconds{0} } } );
         }
      });
}

void multisig::approve( name proposer, name proposal_name, permission_level level,
                        const eosio::binary_extension<eosio::checksum256>& proposal_hash )
{
   if ( level.permission == "eosio.code"_n ) {
       check( get_sender() == level.actor, "wrong contract sent approve action for eosio.code permmission" );
   } else {
      require_auth( level );
   }

   proposals proptable( get_self(), proposer.value );
   auto& prop = proptable.get( proposal_name.value, "proposal not found" );

   if( proposal_hash ) {
      assert_sha256( prop.packed_transaction.data(), prop.packed_transaction.size(), *proposal_hash );
   }

   approvals apptable( get_self(), proposer.value );
   auto apps_it = apptable.find( proposal_name.value );
   if ( apps_it != apptable.end() ) {
      auto itr = std::find_if( apps_it->requested_approvals.begin(), apps_it->requested_approvals.end(), [&](const approval& a) { return a.level == level; } );
      check( itr != apps_it->requested_approvals.end(), "approval is not on the list of requested approvals" );

      apptable.modify( apps_it, proposer, [&]( auto& a ) {
            a.provided_approvals.push_back( approval{ level, current_time_point() } );
            a.requested_approvals.erase( itr );
         });
   } else {
      old_approvals old_apptable( get_self(), proposer.value );
      auto& apps = old_apptable.get( proposal_name.value, "proposal not found" );

      auto itr = std::find( apps.requested_approvals.begin(), apps.requested_approvals.end(), level );
      check( itr != apps.requested_approvals.end(), "approval is not on the list of requested approvals" );

      old_apptable.modify( apps, proposer, [&]( auto& a ) {
            a.provided_approvals.push_back( level );
            a.requested_approvals.erase( itr );
         });
   }

   transaction_header trx_header = get_trx_header(prop.packed_transaction.data(), prop.packed_transaction.size());

   if( prop.earliest_exec_time.has_value() ) { 
      if( !prop.earliest_exec_time->has_value() ) {
         auto table_op = [](auto&&, auto&&){};
         if( trx_is_authorized(get_approvals_and_adjust_table(get_self(), proposer, proposal_name, table_op), prop.packed_transaction) ) {
            proptable.modify( prop, proposer, [&]( auto& p ) {
               p.earliest_exec_time = std::optional<time_point>{ current_time_point() + eosio::seconds(trx_header.delay_sec.value)};
            });
         }
      }
   } else {
      check( trx_header.delay_sec.value == 0, "old proposals are not allowed to have non-zero `delay_sec`; cancel and retry" );
   }
}

void multisig::unapprove( name proposer, name proposal_name, permission_level level ) {
   if ( level.permission == "eosio.code"_n ) {
       check( get_sender() == level.actor, "wrong contract sent unapprove action for eosio.code permmission" );
   } else {
      require_auth( level );
   }

   approvals apptable( get_self(), proposer.value );
   auto apps_it = apptable.find( proposal_name.value );
   if ( apps_it != apptable.end() ) {
      auto itr = std::find_if( apps_it->provided_approvals.begin(), apps_it->provided_approvals.end(), [&](const approval& a) { return a.level == level; } );
      check( itr != apps_it->provided_approvals.end(), "no approval previously granted" );
      apptable.modify( apps_it, proposer, [&]( auto& a ) {
            a.requested_approvals.push_back( approval{ level, current_time_point() } );
            a.provided_approvals.erase( itr );
         });
   } else {
      old_approvals old_apptable( get_self(), proposer.value );
      auto& apps = old_apptable.get( proposal_name.value, "proposal not found" );
      auto itr = std::find( apps.provided_approvals.begin(), apps.provided_approvals.end(), level );
      check( itr != apps.provided_approvals.end(), "no approval previously granted" );
      old_apptable.modify( apps, proposer, [&]( auto& a ) {
            a.requested_approvals.push_back( level );
            a.provided_approvals.erase( itr );
         });
   }

   proposals proptable( get_self(), proposer.value );
   auto& prop = proptable.get( proposal_name.value, "proposal not found" );

   if( prop.earliest_exec_time.has_value() ) { 
      if( prop.earliest_exec_time->has_value() ) {
         auto table_op = [](auto&&, auto&&){};
         if( !trx_is_authorized(get_approvals_and_adjust_table(get_self(), proposer, proposal_name, table_op), prop.packed_transaction) ) {
            proptable.modify( prop, proposer, [&]( auto& p ) {
               p.earliest_exec_time = std::optional<time_point>{};
            });
         }
      }
   } else {
      transaction_header trx_header = get_trx_header(prop.packed_transaction.data(), prop.packed_transaction.size());
      check( trx_header.delay_sec.value == 0, "old proposals are not allowed to have non-zero `delay_sec`; cancel and retry" );
   }
}

void multisig::cancel( name proposer, name proposal_name, name canceler ) {
   require_auth( canceler );

   proposals proptable( get_self(), proposer.value );
   auto& prop = proptable.get( proposal_name.value, "proposal not found" );

   if( canceler != proposer ) {
      check( unpack<transaction_header>( prop.packed_transaction ).expiration < eosio::time_point_sec(current_time_point()), "cannot cancel until expiration" );
   }
   proptable.erase(prop);

   //remove from new table
   approvals apptable( get_self(), proposer.value );
   auto apps_it = apptable.find( proposal_name.value );
   if ( apps_it != apptable.end() ) {
      apptable.erase(apps_it);
   } else {
      old_approvals old_apptable( get_self(), proposer.value );
      auto apps_it = old_apptable.find( proposal_name.value );
      check( apps_it != old_apptable.end(), "proposal not found" );
      old_apptable.erase(apps_it);
   }
}

void multisig::exec( name proposer, name proposal_name, name executer ) {
   require_auth( executer );

   proposals proptable( get_self(), proposer.value );
   auto& prop = proptable.get( proposal_name.value, "proposal not found" );

   datastream<const char*> ds = {prop.packed_transaction.data(), prop.packed_transaction.size()};
   transaction_header trx_header;
   std::vector<action> context_free_actions;
   std::vector<action> actions;
   ds >> trx_header;
   check( trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );
   ds >> context_free_actions;
   check( context_free_actions.empty(), "not allowed to `exec` a transaction with context-free actions" );
   ds >> actions;

   auto table_op = [](auto&& table, auto&& table_iter) { table.erase(table_iter); };
   bool ok = trx_is_authorized(get_approvals_and_adjust_table(get_self(), proposer, proposal_name, table_op), prop.packed_transaction);
   check( ok, "transaction authorization failed" );

   if ( prop.earliest_exec_time.has_value() && prop.earliest_exec_time->has_value() ) {
      check( **prop.earliest_exec_time <= current_time_point(), "too early to execute" );
   } else {
      check( trx_header.delay_sec.value == 0, "old proposals are not allowed to have non-zero `delay_sec`; cancel and retry" );
   }

   for (const auto& act : actions) {
      act.send();
   }

   proptable.erase(prop);
}

void multisig::invalidate( name account ) {
   require_auth( account );
   invalidations inv_table( get_self(), get_self().value );
   auto it = inv_table.find( account.value );
   if ( it == inv_table.end() ) {
      inv_table.emplace( account, [&](auto& i) {
            i.account = account;
            i.last_invalidation_time = current_time_point();
         });
   } else {
      inv_table.modify( it, account, [&](auto& i) {
            i.last_invalidation_time = current_time_point();
         });
   }
}

transaction_header get_trx_header(const char* ptr, size_t sz) {
   datastream<const char*> ds = {ptr, sz};
   transaction_header trx_header;
   ds >> trx_header;
   return trx_header;
}

bool trx_is_authorized(const std::vector<permission_level>& approvals, const std::vector<char>& packed_trx) {
   auto packed_approvals = pack(approvals);
   return check_transaction_authorization(
             packed_trx.data(), packed_trx.size(),
             (const char*)0, 0,
             packed_approvals.data(), packed_approvals.size()
          );
}

} /// namespace eosio
