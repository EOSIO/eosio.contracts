#include <eosio.assert/eosio.assert.hpp>

#include <eosiolib/contract.hpp>
#include <eosiolib/dispatcher.hpp>
#include <eosiolib/ignore.hpp>

namespace assert_contract {

using bytes = std::vector<char>;

bytes get_action_bytes() {
   bytes result(action_data_size());
   read_action_data(result.data(), result.size());
   return result;
}

struct[[eosio::contract("eosio.assert")]] asserter : eosio::contract {
   using contract::contract;

   manifests           manifest_table{_self, _self.value};
   manifests_id_index  manifest_id_idx = manifest_table.get_index<"id"_n>();
   chains              chain_table{_self, _self.value};
   stored_chain_params chain = chain_table.get_or_default();

   [[eosio::action]] void setchain(ignore<checksum256> chain_id, ignore<string> chain_name, ignore<checksum256> icon) {
      require_auth("eosio"_n);
      auto hash = eosio::sha256(_ds.pos(), _ds.remaining());
      _ds >> chain.chain_id;
      _ds >> chain.chain_name;
      _ds >> chain.icon;
      chain.hash = hash;
      chain_table.set(chain, _self);
   };

   [[eosio::action("add.manifest")]] void add_manifest(
       ignore<name> account, ignore<std::string> domain, ignore<std::string> appmeta,
       ignore<vector<contract_action>> whitelist) {
      auto hash   = eosio::sha256(_ds.pos(), _ds.remaining());
      auto stored = stored_manifest{
          .unique_id = chain.next_unique_id++,
          .id        = hash,
      };
      _ds >> stored.account;
      _ds >> stored.domain;
      _ds >> stored.appmeta;
      _ds >> stored.whitelist;

      require_auth(stored.account);
      auto it = manifest_id_idx.find(stored.id_key());
      eosio_assert(it == manifest_id_idx.end(), "manifest already present");
      manifest_table.emplace(stored.account, [&](auto& x) { x = stored; });
      chain_table.set(chain, _self);
   };

   [[eosio::action("del.manifest")]] void del_manifest(checksum256 id) {
      auto it = manifest_id_idx.find(id);
      eosio_assert(it != manifest_id_idx.end(), "manifest not found");
      require_auth(it->account);
      manifest_id_idx.erase(it);
   };

   bool in(contract_action action, const std::vector<contract_action>& actions) {
      return std::find(actions.begin(), actions.end(), action) != actions.end() || //
             std::find(actions.begin(), actions.end(), contract_action{action.contract, name{0}}) != actions.end() ||
             std::find(actions.begin(), actions.end(), contract_action{name{0}, action.action}) != actions.end() ||
             std::find(actions.begin(), actions.end(), contract_action{name{0}, name{0}}) != actions.end();
   }

   static std::string hash_to_str(const checksum256& hash) {
      static const char table[] = "0123456789abcdef";
      auto              bytes   = hash.extract_as_byte_array();
      std::string       result;
      for (uint8_t byte : bytes) {
         result += table[byte >> 4];
         result += table[byte & 0xf];
      }
      return result;
   }

   [[eosio::action()]] void require(
       const checksum256& chain_params_hash, const checksum256& manifest_id, const vector<contract_action>& actions,
       const vector<checksum256>& abi_hashes) {
      if (!(chain_params_hash == chain.hash))
         eosio_assert(
             false,
             ("chain hash is " + hash_to_str(chain.hash) + " but user expected " + hash_to_str(chain_params_hash))
                 .c_str());
      auto it = manifest_id_idx.find(manifest_id);
      eosio_assert(it != manifest_id_idx.end(), "manifest not found");
      std::vector<name> contracts;
      for (auto& action : actions) {
         auto contract_it = std::lower_bound(contracts.begin(), contracts.end(), action.contract);
         if (contract_it == contracts.end() || *contract_it != action.contract)
            contracts.insert(contract_it, action.contract);
         if (!in(action, it->whitelist))
            eosio_assert(
                false,
                (action.action.to_string() + "@" + action.contract.to_string() + " is not in whitelist").c_str());
      }
      abi_hash_table table{"eosio"_n, "eosio"_n.value};
      eosio_assert(abi_hashes.size() == contracts.size(), "incorrect number of abi hashes");
      for (size_t i = 0; i < abi_hashes.size(); ++i) {
         auto        it = table.find(contracts[i].value);
         checksum256 hash{};
         if (it != table.end())
            hash = it->hash;
         if (!(abi_hashes[i] == hash))
            eosio_assert(
                false, (contracts[i].to_string() + " abi hash is " + hash_to_str(hash) + " but user expected " +
                        hash_to_str(abi_hashes[i]))
                           .c_str());
      }
   }
};

#define CALL(n, m)                                                                                                     \
   case eosio::name(#n).value: eosio::execute_action(receiver, code, &asserter::m); break;

extern "C" void apply(eosio::name receiver, eosio::name code, eosio::name action) {
   if (code != receiver)
      return;
   switch (action.value) {
      CALL(setchain, setchain)
      CALL(add.manifest, add_manifest)
      CALL(del.manifest, del_manifest)
      CALL(require, require)
   }
}

} // namespace assert_contract
