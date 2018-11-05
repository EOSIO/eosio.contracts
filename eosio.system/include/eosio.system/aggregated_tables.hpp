/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/module_manager.hpp>

#include <eosio.system/core_tables.hpp>
#include <eosio.system/ram_tables.hpp>


namespace eosiosystem {

   using contract_modules =   eosio::module::manager<
                                 core_tables,
                                 ram_tables,
                                 name_auction_tables
                              >;

} /// namespace eosiosystem
