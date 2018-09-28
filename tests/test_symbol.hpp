#pragma once
#define CORE_SYM SY(4, TST)
#define CORE_SYM_NAME "TST"
#define CORE_SYM_STR "4,TST"

struct core_sym {
   static inline eosio::chain::asset from_string(const std::string& s) {
     return eosio::chain::asset::from_string(s + " " CORE_SYM_NAME);
   }
};

