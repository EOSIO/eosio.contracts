/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/contract.hpp>
#include <eosiolib/module_manager.hpp>

namespace eosio_ex {

   template<typename ModuleManager, typename Module = void>
   class contract_with_modules : public contract {
   public:
      static_assert( detail::has_type_v<typename Module::tables, decltype(ModuleManager::_module_tables)>, "Module not in Manager" );

      contract_with_modules( name self, name code, datastream<const char*> ds )
      :contract( self, code, ds )
      ,_mm( self )
      ,_module( _mm )
      {}

   protected:
      ModuleManager _mm;
      Module        _module;
   };

   template<typename ModuleManager<
   class contract_with_modules<ModuleManager, void> : public contract {
   public:
      static_assert( detail::has_type_v<typename Module::tables, decltype(ModuleManager::_module_tables)>, "Module not in Manager" );

      contract_with_modules( name self, name code, datastream<const char*> ds )
      :contract( self, code, ds )
      ,_mm( self )
      {}

   protected:
      ModuleManager _mm;
   }

} /// namespace eosio_ex
