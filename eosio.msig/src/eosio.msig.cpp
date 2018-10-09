#include <eosio.msig/eosio.msig.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/permission.hpp>

namespace eosio {

static time_point current_time_point() {
   const static time_point ct{ microseconds{ static_cast<int64_t>( current_time() ) } };
   return ct;
}

/*
propose function manually parses input data (instead of taking parsed arguments from dispatcher)
because parsing data in the dispatcher uses too much CPU in case if proposed transaction is big

If we use dispatcher the function signature should be:

void multisig::propose( name proposer,
                        name proposal_name,
                        std::vector<permission_level> requested,
                        transaction  trx)
*/

void multisig::propose() {
   constexpr size_t max_stack_buffer_size = 512;
   size_t size = action_data_size();
   char* buffer = (char*)( max_stack_buffer_size < size ? malloc(size) : alloca(size) );
   read_action_data( buffer, size );

   name proposer;
   name proposal_name;
   std::vector<permission_level> requested;
   transaction_header trx_header;

   datastream<const char*> ds( buffer, size );
   ds >> proposer >> proposal_name >> requested;

   size_t trx_pos = ds.tellp();
   ds >> trx_header;

   require_auth( proposer );
   eosio_assert( trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );
   //eosio_assert( trx_header.actions.size() > 0, "transaction must have at least one action" );

   proposals proptable( _self, proposer.value );
   eosio_assert( proptable.find( proposal_name.value ) == proptable.end(), "proposal with the same name exists" );

   auto packed_requested = pack(requested);
   auto res = ::check_transaction_authorization( buffer+trx_pos, size-trx_pos,
                                                 (const char*)0, 0,
                                                 packed_requested.data(), packed_requested.size()
                                               );
   eosio_assert( res > 0, "transaction authorization failed" );

   proptable.emplace( proposer, [&]( auto& prop ) {
      prop.proposal_name       = proposal_name;
      prop.packed_transaction  = std::vector<char>( buffer+trx_pos, buffer+size );
   });

   approvals apptable(  _self, proposer.value );
   apptable.emplace( proposer, [&]( auto& a ) {
      a.proposal_name       = proposal_name;
      a.requested_approvals.reserve( requested.size() );
      for ( auto& level : requested ) {
         a.requested_approvals.push_back( approval{ level, time_point{ microseconds{0} } } );
      }
   });
}

void multisig::approve( name proposer, name proposal_name, permission_level level ) {
   require_auth( level );

   approvals apptable(  _self, proposer.value );
   auto apps_it = apptable.find( proposal_name.value );
   if ( apps_it != apptable.end() ) {
      auto itr = std::find_if( apps_it->requested_approvals.begin(), apps_it->requested_approvals.end(), [&](const approval& a) { return a.level == level; } );
      eosio_assert( itr != apps_it->requested_approvals.end(), "approval is not on the list of requested approvals" );

      apptable.modify( apps_it, proposer, [&]( auto& a ) {
            a.provided_approvals.push_back( approval{ level, current_time_point() } );
            a.requested_approvals.erase( itr );
         });
   } else {
      old_approvals old_apptable(  _self, proposer.value );
      auto& apps = old_apptable.get( proposal_name.value, "proposal not found" );

      auto itr = std::find( apps.requested_approvals.begin(), apps.requested_approvals.end(), level );
      eosio_assert( itr != apps.requested_approvals.end(), "approval is not on the list of requested approvals" );

      old_apptable.modify( apps, proposer, [&]( auto& a ) {
            a.provided_approvals.push_back( level );
            a.requested_approvals.erase( itr );
         });
   }
}

void multisig::unapprove( name proposer, name proposal_name, permission_level level ) {
   require_auth( level );

   approvals apptable(  _self, proposer.value );
   auto apps_it = apptable.find( proposal_name.value );
   if ( apps_it != apptable.end() ) {
      auto itr = std::find_if( apps_it->provided_approvals.begin(), apps_it->provided_approvals.end(), [&](const approval& a) { return a.level == level; } );
      eosio_assert( itr != apps_it->provided_approvals.end(), "no approval previously granted" );
      apptable.modify( apps_it, proposer, [&]( auto& a ) {
            a.requested_approvals.push_back( approval{ level, current_time_point() } );
            a.provided_approvals.erase( itr );
         });
   } else {
      old_approvals old_apptable(  _self, proposer.value );
      auto& apps = old_apptable.get( proposal_name.value, "proposal not found" );
      auto itr = std::find( apps.provided_approvals.begin(), apps.provided_approvals.end(), level );
      eosio_assert( itr != apps.provided_approvals.end(), "no approval previously granted" );
      old_apptable.modify( apps, proposer, [&]( auto& a ) {
            a.requested_approvals.push_back( level );
            a.provided_approvals.erase( itr );
         });
   }
}

void multisig::cancel( name proposer, name proposal_name, name canceler ) {
   require_auth( canceler );

   proposals proptable( _self, proposer.value );
   auto& prop = proptable.get( proposal_name.value, "proposal not found" );

   if( canceler != proposer ) {
      eosio_assert( unpack<transaction_header>( prop.packed_transaction ).expiration < eosio::time_point_sec(current_time_point()), "cannot cancel until expiration" );
   }
   proptable.erase(prop);

   //remove from new table
   approvals apptable(  _self, proposer.value );
   auto apps_it = apptable.find( proposal_name.value );
   if ( apps_it != apptable.end() ) {
      apptable.erase(apps_it);
   } else {
      old_approvals old_apptable(  _self, proposer.value );
      auto apps_it = old_apptable.find( proposal_name.value );
      eosio_assert( apps_it != old_apptable.end(), "proposal not found" );
      old_apptable.erase(apps_it);
   }
}

void multisig::exec( name proposer, name proposal_name, name executer ) {
   require_auth( executer );

   proposals proptable( _self, proposer.value );
   auto& prop = proptable.get( proposal_name.value, "proposal not found" );
   transaction_header trx_header;
   datastream<const char*> ds( prop.packed_transaction.data(), prop.packed_transaction.size() );
   ds >> trx_header;
   eosio_assert( trx_header.expiration >= eosio::time_point_sec(current_time_point()), "transaction expired" );

   approvals apptable(  _self, proposer.value );
   auto apps_it = apptable.find( proposal_name.value );
   std::vector<permission_level> approvals;
   invalidations inv_table( _self, _self.value );
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
      old_approvals old_apptable(  _self, proposer.value );
      auto& apps = old_apptable.get( proposal_name.value, "proposal not found" );
      for ( auto& level : apps.provided_approvals ) {
         auto it = inv_table.find( level.actor.value );
         if ( it == inv_table.end() ) {
            approvals.push_back( level );
         }
      }
      old_apptable.erase(apps);
   }
   auto packed_provided_approvals = pack(approvals);
   auto res = ::check_transaction_authorization( prop.packed_transaction.data(), prop.packed_transaction.size(),
                                                 (const char*)0, 0,
                                                 packed_provided_approvals.data(), packed_provided_approvals.size()
                                                 );
   eosio_assert( res > 0, "transaction authorization failed" );

   send_deferred( (uint128_t(proposer.value) << 64) | proposal_name.value, executer.value,
                  prop.packed_transaction.data(), prop.packed_transaction.size() );

   proptable.erase(prop);
}

void multisig::invalidate( name account ) {
   require_auth( account );
   invalidations inv_table( _self, _self.value );
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

} /// namespace eosio

EOSIO_ABI( eosio::multisig, (propose)(approve)(unapprove)(cancel)(exec)(invalidate) )
