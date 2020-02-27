#include <eosio/action.hpp>
#include <eosio/contract.hpp>
#include <eosio/name.hpp>
#include <eosio/permission.hpp>
#include <vector>

class [[eosio::contract]]
wrongcon : public eosio::contract {
public:
   using contract::contract;

   [[eosio::action]]
   void send( eosio::name contract, eosio::name action_name, std::vector<eosio::permission_level> auths, std::vector<char> payload) {
      eosio::action act;
      act.account = contract;
      act.name = action_name;
      act.authorization = auths;
      act.data = std::move(payload);
      act.send();
   }
};
