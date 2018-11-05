/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/name.hpp>
#include <eosiolib/system.h>

#include <tuple>
#include <map>
#include <type_traits>

namespace eosio_ex { namespace module {

   namespace detail {
      template<typename T, typename Tuple>
      struct has_type;

      template<typename T, typename... Us>
      struct has_type<T, std::tuple<Us...>> : std::disjunction<std::is_same<T, Us>...> {};

      template<typename T, typename... Us>
      inline constexpr bool has_type_v = has_type<T, Us...>::value;

      template<typename T, typename U>
      struct identity {
         identity( T v ) : value(v) {}
         T value;
      };

   }

   template<typename... Tables>
   class tables {
   public:
      static constexpr std::size_t num_tables = sizeof...(Tables);

      tables( eosio::name self ) : _self(self), _tables() {}

      template<typename Table>
      auto get_table( uint64_t scope ) -> std::add_lvalue_reference_t<Table>
      {
         static_assert( detail::has_type_v<std::map<uint64_t, Table>, decltype(_tables)>, "Table not in Module" );
         auto& table_map = std::get<std::map<uint64_t, Table>>(_tables);

         auto itr1 = table_map.find( scope );
         if( itr1 != table_map.end() )
            return itr1->second;

         auto [itr2, inserted] = table_map.emplace( std::piecewise_construct,
                                                    std::forward_as_tuple( scope ),
                                                    std::forward_as_tuple( _self, scope ) );
         return itr2->second;
      }

      template<typename Table>
      auto get_table( uint64_t scope )const -> std::add_lvalue_reference_t<Table>
      {
         static_assert( detail::has_type_v<std::map<uint64_t, Table>, decltype(_tables)>, "Table not in Module" );
         auto& table_map = std::get<std::map<uint64_t, Table>>(_tables);

         auto itr = table_map.find( scope );
         if( itr == table_map.end() ) {
            eosio_assert( false, "cannot create table");
         }

         return itr1->second;
      }


      template<typename Table>
      auto get_table() -> std::add_lvalue_reference_t<Table>
      {
         return get_table<Table>( _self.value );
      }

      template<typename Table>
      auto get_table()const -> std::add_lvalue_reference_t<Table>
      {
         return get_table<Table>( _self.value );
      }

   private:
      eosio::name                               _self;
      std::tuple<std::map<uint64_t, Tables>...> _tables;
   };

   template<typename... ModulesTables>
   class manager {
   public:
      manager( eosio::name self )
      :_self(self)
      ,_module_tables( detail::identity<eosio::name, ModulesTables>( self ).value... )
      {}

      template<typename Module>
      auto get_module() -> Module
      {
         static_assert( detail::has_type_v<typename Module::tables, decltype(_module_tables)>, "Module not in Manager" );
         return Module{ *this };
      }

      inline auto get_self()const -> eosio::name
      {
         return _self;
      }

   private:
      eosio::name                             _self;
      std::tuple<typename Modules::tables...> _module_tables;

      template<typename ModuleManager, typename ModuleTables>
      friend class module_base;
   };

   template<typename ModuleManager, typename ModuleTables>
   class module_base : public ModuleTables {
   public:
      static_assert( detail::has_type_v<typename ModuleTables::tables, decltype(ModuleManager::_module_tables)>, "Module not in Manager" );

      using module_base_type = module_base<ModuleManager, ModuleTables>;

      explicit module_base( ModuleManager& mm )
      :_mm(mm), _module_tables(std::get<typename Module::tables>(_mm._module_tables))
      {}

   protected:
      template<typename Table>
      inline auto get_table( uint64_t scope ) -> std::add_lvalue_reference_t<Table>
      {
         return _module_tables.template get_table<Table>( scope );
      }

      template<typename Table>
      inline auto get_table( uint64_t scope )const -> std::add_lvalue_reference_t<Table>
      {
         return _module_tables.template get_table<Table>( scope );
      }

      template<typename Table>
      inline auto get_table() -> std::add_lvalue_reference_t<Table>
      {
         return _module_tables.template get_table<Table>();
      }

      template<typename Table>
      inline auto get_table()const -> std::add_lvalue_reference_t<Table>
      {
         return _module_tables.template get_table<Table>();
      }

      template<typename Module>
      inline auto get_module() -> Module
      {
         return _mm.get_module<Module>();
      }

      inline auto get_self()const -> eosio::name
      {
         return _mm.get_self();
      }

   private:
      ModuleManager&  _mm;
      typename Module::tables& _module_tables;
   };

} } /// namespace eosio_ex::module
