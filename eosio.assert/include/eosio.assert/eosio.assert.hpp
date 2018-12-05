#pragma once

#include <eosiolib/crypto.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/singleton.hpp>

namespace assert_contract {

using namespace eosio;
using std::string;
using std::vector;

struct [[ eosio::contract("eosio.assert"), eosio::table("chain.params") ]] stored_chain_params {
   checksum256 chain_id;
   string      chain_name;
   checksum256 icon;
   checksum256 hash;
   uint64_t    next_unique_id = 1;
};

using chains = singleton<"chain.params"_n, stored_chain_params>;

struct contract_action {
   name contract;
   name action;
};

inline bool operator==(const contract_action& a, const contract_action& b) {
   return std::tie(a.contract, a.action) == std::tie(b.contract, b.action);
}

struct [[ eosio::contract("eosio.assert"), eosio::table("manifests") ]] stored_manifest {
   uint64_t                     unique_id = 0;
   checksum256                  id;
   name                         account;
   std::string                  domain;
   std::string                  appmeta;
   std::vector<contract_action> whitelist;

   uint64_t    primary_key() const { return unique_id; }
   checksum256 id_key() const { return id; }
};

using manifests = eosio::multi_index<
    "manifests"_n, stored_manifest,
    indexed_by<"id"_n, eosio::const_mem_fun<stored_manifest, checksum256, &stored_manifest::id_key>>>;
using manifests_id_index = decltype(std::declval<manifests>().get_index<"id"_n>());

struct abi_hash {
   name        owner;
   checksum256 hash;

   uint64_t primary_key() const { return owner.value; }
};

using abi_hash_table = eosio::multi_index<"abihash"_n, abi_hash>;

} // namespace assert_contract
