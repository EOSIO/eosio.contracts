#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio/permission.hpp>

#include <eosio.msig/eosio.msig.hpp>

namespace eosio {

template<typename Function>
bool approvals_satisfy_trx_authorization(name self, name proposer, name proposal_name, const std::vector<char>& packed_trx, Function&& table_op);

template<typename Function>
std::vector<permission_level> get_approvals_and_adjust_table(name self, name proposer, name proposal_name, Function&& table_op);

void multisig::propose( ignore<name> proposer,
                        ignore<name> proposal_name,
                        ignore<std::vector<permission_level>> requested,
                        ignore<transaction> trx )
{
   name _proposer;
   name _proposal_name;
   std::vector<permission_level> _requested;

   _ds >> _proposer >> _proposal_name >> _requested;

   const char* trx_pos = _ds.pos();
   size_t size = _ds.remaining();
   transaction_header _trx_header = get_trx_header(trx_pos, size);
   require_auth( _proposer );
   check( _trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );

   proposals proptable( get_self(), _proposer.value );
   check( proptable.find( _proposal_name.value ) == proptable.end(), "proposal with the same name exists" );

   auto packed_requested = pack(_requested);
   auto res =  check_transaction_authorization(
                  trx_pos, size,
                  (const char*)0, 0,
                  packed_requested.data(), packed_requested.size()
               );

   check( res > 0, "transaction authorization failed" );

   std::vector<char> pkd_trans;
   pkd_trans.resize(size);
   memcpy((char*)pkd_trans.data(), trx_pos, size);
   proptable.emplace( _proposer, [&]( auto& prop ) {
      prop.proposal_name      = _proposal_name;
      prop.packed_transaction = pkd_trans;
      prop.earliest_exec_time = std::optional<time_point>{};
   });

   approvals apptable( get_self(), _proposer.value );
   apptable.emplace( _proposer, [&]( auto& a ) {
      a.proposal_name = _proposal_name;
      a.requested_approvals.reserve( _requested.size() );
      for ( auto& level : _requested ) {
         a.requested_approvals.push_back( approval{ level, time_point{ microseconds{0} } } );
      }
   });
}

void multisig::approve( name proposer, name proposal_name, permission_level level,
                        const eosio::binary_extension<eosio::checksum256>& proposal_hash )
{
   require_auth( level );

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

   // Question for code review.
   if ( prop.earliest_exec_time.has_value() ) {
      if ( prop.earliest_exec_time.value().has_value() ) {
         return;
      } else {
         auto table_op = [](auto&&, auto&&){};
         if ( approvals_satisfy_trx_authorization(get_self(), proposer, proposal_name, prop.packed_transaction, table_op) ) {
            auto prop_it = proptable.find( proposal_name.value );
            proptable.modify( prop_it, proposer, [&]( auto& p ) {
               p.earliest_exec_time = std::optional<time_point>{ current_time_point() + eosio::seconds(trx_header.delay_sec.value)};
            });
         } else {
            return;
         }
      }
   } else {
      check( trx_header.delay_sec.value == 0, "old proposals are not allowed to have non-zero `delay_sec`; cancel and retry" );
   }
}

void multisig::unapprove( name proposer, name proposal_name, permission_level level ) {
   require_auth( level );

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

   if ( prop.earliest_exec_time.has_value() ) {
      if ( prop.earliest_exec_time.value().has_value() ) {
         auto table_op = [](auto&&, auto&&){};
         if ( approvals_satisfy_trx_authorization(get_self(), proposer, proposal_name, prop.packed_transaction, table_op) ) {
            return;
         } else {
            auto prop_it = proptable.find( proposal_name.value );
            proptable.modify( prop_it, proposer, [&]( auto& p ) {
               p.earliest_exec_time = std::optional<time_point>{};
            });
         }
      } else {
         return;
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
   transaction_header trx_header = get_trx_header(prop.packed_transaction.data(), prop.packed_transaction.size());
   check( trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );

   auto table_op = [](auto&& table, auto&& table_iter) { table.erase(table_iter); };
   bool ok = approvals_satisfy_trx_authorization(get_self(), proposer, proposal_name, prop.packed_transaction, table_op);
   check( ok, "transaction authorization failed" );

   if ( prop.earliest_exec_time.has_value() && prop.earliest_exec_time.value().has_value() ) {
      check( prop.earliest_exec_time.value().value() <= current_time_point(), "too early to execute" );
   } else {
      check( trx_header.delay_sec.value == 0, "old proposals are not allowed to have non-zero `delay_sec`; cancel and retry" );
   }

   datastream<const char*> ds = {prop.packed_transaction.data(), prop.packed_transaction.size()};
   transaction_header _;
   std::vector<action> context_free_actions;
   std::vector<action> actions;
   ds >> _;
   ds >> context_free_actions;
   ds >> actions;

   for (const auto& act : context_free_actions) {
      act.send();
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

template<typename Function>
bool approvals_satisfy_trx_authorization(name self, name proposer, name proposal_name, const std::vector<char>& packed_trx, Function&& table_op) {
   std::vector<permission_level> approvals_vector = get_approvals_and_adjust_table(self, proposer, proposal_name, table_op);
   return trx_is_authorized(approvals_vector, packed_trx);
}

template<typename Function>
std::vector<permission_level> get_approvals_and_adjust_table(name self, name proposer, name proposal_name, Function&& table_op) {
   approvals approval_table( self, proposer.value );
   auto approval_table_iter = approval_table.find( proposal_name.value );
   std::vector<permission_level> approvals_vector;
   invalidations invalidations_table( self, self.value );

   if ( approval_table_iter != approval_table.end() ) {
      approvals_vector.reserve( approval_table_iter->provided_approvals.size() );
      for ( auto& permission : approval_table_iter->provided_approvals ) {
         auto iter = invalidations_table.find( permission.level.actor.value );
         if ( iter == invalidations_table.end() || iter->last_invalidation_time < permission.time ) {
            approvals_vector.push_back(permission.level);
         }
      }
      table_op( approval_table, approval_table_iter );
   } else {
      old_approvals old_approval_table( self, proposer.value );
      auto& old_approvals_iter = old_approval_table.get( proposal_name.value, "proposal not found" );
      for ( const auto& permission : old_approvals_iter.provided_approvals ) {
         auto iter = invalidations_table.find( permission.actor.value );
         if ( iter == invalidations_table.end() ) {
            approvals_vector.push_back( permission );
         }
      }
      table_op( old_approval_table, old_approvals_iter );
   }
   return approvals_vector;
}

transaction_header get_trx_header(const char* ptr, size_t sz) {
   datastream<const char*> ds{ptr, sz};
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
