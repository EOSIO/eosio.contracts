#include <eosio/action.hpp>
#include <eosio/contract.hpp>
#include <eosio/transaction.hpp>
#include <vector>

/// `eosio.code` is a virtual permission (there is no private or public
/// key associated with it). Therefore, this test tests how `eosio.msig`
/// contract reacts to a smart contract submitting a proposal and
/// approving/unnapproving itself.
class [[eosio::contract]]
sendinline : public eosio::contract {
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
