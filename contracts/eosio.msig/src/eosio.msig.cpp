#include <eosio/action.hpp>
#include <eosio/crypto.hpp>
#include <eosio/permission.hpp>

#include <eosio.msig/eosio.msig.hpp>

namespace eosio {

void multisig::propose( ignore<name> proposer,
                        ignore<name> proposal_name,
                        // ignore<time_point> exec_time,
                        ignore<time_point> delay_seconds,
                        ignore<std::vector<permission_level>> requested,
                        ignore<transaction> trx )
{
   name _proposer;
   name _proposal_name;
   // time_point _exec_time;
   time_point _delay_seconds;
   std::vector<permission_level> _requested;
   transaction_header _trx_header;

   _ds >> _proposer >> _proposal_name >> _delay_seconds >> _requested;
   // _ds >> _proposer >> _proposal_name >> _exec_time >> _requested;

   const char* trx_pos = _ds.pos();
   size_t size    = _ds.remaining();
   _ds >> _trx_header;

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
   // check( exec_time < current_time_point(), "impossible to send a transaction backward in time" );

   std::vector<char> pkd_trans;
   pkd_trans.resize(size);
   memcpy((char*)pkd_trans.data(), trx_pos, size);
   proptable.emplace( _proposer, [&]( auto& prop ) {
      prop.proposal_name      = _proposal_name;
      prop.packed_transaction = pkd_trans;
      prop.earliest_exec_time = time_point{eosio::microseconds::maximum()};
      prop.delay_seconds      = _delay_seconds;
      // prop.earliest_exec_time = (exec_time != eosio::microseconds::maximum()) ? exec_time : eosio::microseconds::maximum();
   });

   approvals apptable( get_self(), _proposer.value );
   apptable.emplace( _proposer, [&]( auto& a ) {
      a.proposal_name       = _proposal_name;
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

   /// New logic.
   // - If `earliest_exec_time` is not equal to `eosio::microseconds::maximum()`.
   //   - `return`.
   // - Call `_get_approvals` to get the set of approvals.
   // - Then pack it.
   // - Call `check_transaction_authorization` to see if the set of approvals succeed.
   // - If succeeds?
   //   - Change `earliest_exec_time` to specified time. ("specified time" == (delay_seconds + current_time())).
   // - If does not succeed.
   //   - `return`.
   if (prop.earliest_exec_time.value_or() != time_point{eosio::microseconds::maximum()}) {
      return; 
   } else {
      auto packed_provided_approvals = pack(_get_approvals(proposer, proposal_name));
      auto res =  check_transaction_authorization(
                     prop.packed_transaction.data(), prop.packed_transaction.size(),
                     (const char*)0, 0,
                     packed_provided_approvals.data(), packed_provided_approvals.size()
                  );
      if (res > 0) {
         auto prop_it = proptable.find( proposal_name.value );
         proptable.modify( prop_it, proposer, [&]( auto& p ) {
            p.earliest_exec_time = time_point{prop.delay_seconds.value_or() + current_time_point()};
         });
      } else {
         return;
      }
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

   /// New logic.
   // - If `earliest_exec_time` is equal to `eosio::microseconds::maximum()`.
   //   - `return`.
   // - Call `_get_approvals` to get the set of approvals.
   // - Then pack it.
   // - Call `check_transaction_authorization` to see if the set of approvals succeed.
   // - If succeeds?
   //   - `return`.
   // - If does not succeed.
   //   - Change `earliest_exec_time` to `eosio::microseconds::maximum()`.
   // proposals proptable( get_self(), proposer.value );
   // auto& prop = proptable.get( proposal_name.value, "proposal not found" );
   
   // if (prop.earliest_exec_time.value_or() == time_point{eosio::microseconds::maximum()}) {
   //    return; 
   // } else {
   //    auto packed_provided_approvals = pack(_get_approvals(proposer, proposal_name));
   //    auto res =  check_transaction_authorization(
   //                   prop.packed_transaction.data(), prop.packed_transaction.size(),
   //                   (const char*)0, 0,
   //                   packed_provided_approvals.data(), packed_provided_approvals.size()
   //                );
   //    if (res > 0) {
   //       return;
   //    } else {
   //       auto prop_it = proptable.find( proposal_name.value );
   //       proptable.modify( prop_it, proposer, [&]( auto& p ) {
   //          p.earliest_exec_time = time_point{eosio::microseconds::maximum()};
   //       });
   //    }
   // }
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
   transaction_header trx_header;
   datastream<const char*> ds( prop.packed_transaction.data(), prop.packed_transaction.size() );
   ds >> trx_header;
   check( trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );

   auto packed_provided_approvals = pack(_get_approvals(proposer, proposal_name));
   auto res =  check_transaction_authorization(
                  prop.packed_transaction.data(), prop.packed_transaction.size(),
                  (const char*)0, 0,
                  packed_provided_approvals.data(), packed_provided_approvals.size()
               );

   check( res > 0, "transaction authorization failed" );

   send_deferred( (uint128_t(proposer.value) << 64) | proposal_name.value, executer,
                  prop.packed_transaction.data(), prop.packed_transaction.size() );

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

std::vector<permission_level> multisig::_get_approvals(const name& proposer, const name& proposal_name) {
   approvals apptable( get_self(), proposer.value );
   auto apps_it = apptable.find( proposal_name.value );
   std::vector<permission_level> approvals;
   invalidations inv_table( get_self(), get_self().value );
   if ( apps_it != apptable.end() ) {
      approvals.reserve( apps_it->provided_approvals.size() );
      for ( auto& p : apps_it->provided_approvals ) {
         auto it = inv_table.find( p.level.actor.value );
         if ( it == inv_table.end() || it->last_invalidation_time < p.time ) {
            approvals.push_back(p.level);
         }
      }
      apptable.erase(apps_it);
   } else {
      old_approvals old_apptable( get_self(), proposer.value );
      auto& apps = old_apptable.get( proposal_name.value, "proposal not found" );
      for ( auto& level : apps.provided_approvals ) {
         auto it = inv_table.find( level.actor.value );
         if ( it == inv_table.end() ) {
            approvals.push_back( level );
         }
      }
      old_apptable.erase(apps);
   }
   return approvals;
}

} /// namespace eosio
