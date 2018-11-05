/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/multi_index.hpp>
#include <eosiolib/system.h>
#include <optional>

namespace eosio_ex {

   template<typename T, name::raw Payer, bool DefaultInitialize = true>
   class lazy_singleton
   {
   public:
      constexpr static name table_name{T::table_name};
      constexpr static name payer{Payer};

      struct row {
         T value;

         uint64_t primary_key() const { return table_name.value; }

         EOSLIB_SERIALIZE( row, (value) )
      };

      using table = eosio::multi_index<table_name, row>;

      lazy_singleton( name code, uint64_t scope )
      :_cache()
      ,_table( code, scope )
      {
         auto itr = _table.find( table_name.value );
         if( itr != _table.end() ) {
            _cache.emplace( itr->value );
         } else if( DefaultInitialize ) {
            _cache.emplace();
            _dirty = true;
         }
      }

      ~lazy_singleton() {
         if( !_flush_on_exit ) return;

         flush();
      }

      void cancel_flush_on_exit() { _flush_on_exit = false; }

      inline bool exists()const {
         return _cache.has_value();
      }

      inline const T& get()const {
         if( !_cache ) {
            eosio_assert( false, "singleton does not exist" );
         }
         return *_cache;
      }

      const T& force_update_and_get() {
         auto itr = _table.find( table_name.value  );
         if( itr == _table.end() ) {
            eosio_assert( false, "singleton does not exist" );
         }
         _cache = itr->value;
         _dirty = false;
         return *_cache;
      }

      const T& get_or_default() {
         if( !_cache ) {
            _cache.emplace();
            _dirty = true;
         }
         return *_cache;
      }

      template<typename Lambda>
      const T& get_or_create( Lambda&& constructor ) {
         if( _cache ) {
            return *_cache;
         }

         auto itr = _table.find( table_name.value );
         if( itr != _table.end() ) {
            _cache = itr->value;
         } else {
            _table.emplace( payer, [&]( row& r ) {
               constructor( r.value );
               _cache = r.value;
            });
         }

         return *_cache;
      }

      template<typename Lambda>
      void modify( Lambda&& updater ) {
         if( !_cache ) {
            get_or_create( std::forward<Lambda>(updater) );
            return;
         }

         updater( *_cache );
         _dirty = true;
      }

      void remove() {
         auto itr = _table.find( table_name.value );
         if( itr != _table.end() ) {
            _table.erase( itr );
         }
         _cache.reset();
         _dirty = false;
      }

      void flush() {
         if( !_dirty || !_cache ) return;

         auto itr = _t.find( table_name.value );
         if( itr != _t.end() ) {
            _table.modify( itr, payer, [&](row& r) { r.value = *_cache; } );
         } else {
            _table.emplace( payer, [&](row& r) { r.value = *_cache; } );
         }

         _dirty = false;
      }

   private:
      std::optional<T> _cache;
      table            _table;
      bool             _dirty = false;
      bool             _flush_on_exit = true;

   };
} /// namespace eosio_ex
