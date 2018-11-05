/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosio.system/native_subcontract.hpp>
#include <eosio.system/core_module.hpp>
#include <eosio.system/name_auction_module.hpp>

namespace eosiosystem {

   void native_subcontract::newaccount( name  creator,
                                        name  newact,
                                        ignore<authority> /* owner */,
                                        ignore<authority> /* active */ )
   {
      if( creator != _self ) {
         uint64_t tmp = newact.value >> 4;
         bool has_dot = false;

         for( uint32_t i = 0; i < 12; ++i ) {
           has_dot |= !(tmp & 0x1f);
           tmp >>= 5;
         }
         if( has_dot ) { // or is less than 12 characters
            auto suffix = newact.suffix();
            if( suffix == newact ) {
               _mm.get_module<name_auction_module>().assert_and_remove_winning_bid( newact, creator );
            } else {
               eosio_assert( creator == suffix, "only suffix may create this account" );
            }
         }
   }

   void native_subcontract::setabi( name account, const std::vector<char>& abi )
   {
      auto& aht =
      eosio::multi_index< "abihash"_n, abi_hash >  table(_self, _self.value);
      auto itr = table.find( acnt.value );
      if( itr == table.end() ) {
         table.emplace( acnt, [&]( auto& row ) {
            row.owner= acnt;
            sha256( const_cast<char*>(abi.data()), abi.size(), &row.hash );
         });
      } else {
         table.modify( itr, same_payer, [&]( auto& row ) {
            sha256( const_cast<char*>(abi.data()), abi.size(), &row.hash );
         });
      }
   }

} /// namespace eosiosystem
