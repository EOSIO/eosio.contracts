#pragma once

#include <eosiolib/eosio.hpp>

namespace eosio {

   class sudo : public contract {
      public:
         sudo( name self ):contract(self){}

         void exec();

   };

} /// namespace eosio
