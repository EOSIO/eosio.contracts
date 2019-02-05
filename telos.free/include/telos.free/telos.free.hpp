/**
 * Supports creation of free Telos accounts
 * 
 * @author Marlon Williams
 * @copyright defined in telos/LICENSE.txt
 */

#pragma once

#include <eosiolib/action.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>
#include "exchange_state.hpp"

#include <string>

using namespace std;
using namespace eosio;

class [[eosio::contract("telos.free")]] freeaccounts : public contract {
public:
      using contract::contract;

      struct signup_public_key {
            uint8_t        type;
            array<unsigned char,33> data;
      };
      struct permission_level_weight {
            permission_level permission;
            uint16_t weight;
      };
      struct key_weight {
            signup_public_key key;
            uint16_t weight;
      };
      struct wait_weight {
            uint32_t wait_sec;
            uint16_t weight;
      };
      struct authority {
            uint32_t threshold;
            vector<key_weight> keys;
            vector<permission_level_weight> accounts;
            vector<wait_weight> waits;
      };
      struct newaccount {
            name creator;
            name name;
            authority owner;
            authority active;
      };

      [[eosio::action]]
      void create( name account_creator, name account_name, string owner_key, string active_key, string key_prefix );

      [[eosio::action]]
      void configure( int16_t max_accounts_per_hour, int64_t stake_cpu_tlos_amount, int64_t stake_net_tlos_amount );

      [[eosio::action]]
      void addwhitelist(name account_name, uint32_t total_accounts, uint32_t max_accounts);

      [[eosio::action]]
      void removewlist(name account_name);

      struct [[eosio::table]] freeacctcfg {
            name publisher;
            int16_t max_accounts_per_hour = 50;
            int64_t stake_cpu_tlos_amount = 9000;
            int64_t stake_net_tlos_amount = 1000;

            auto primary_key() const { return publisher.value; }

            EOSLIB_SERIALIZE(freeacctcfg, (publisher)(max_accounts_per_hour)(stake_cpu_tlos_amount)(stake_net_tlos_amount))
      };

      struct [[eosio::table]] freeacctlog {
            name account_name;
            uint32_t created_on = 0;

            auto primary_key() const { return account_name.value; }
            uint32_t by_created_on() const    { return created_on;  }

            EOSLIB_SERIALIZE(freeacctlog, (account_name)(created_on))
      };

      struct [[eosio::table]] whitelisted {
            name account_name;
            uint32_t total_accounts = 0;
            uint32_t max_accounts = 0;

            auto primary_key() const { return account_name.value; }

            EOSLIB_SERIALIZE(whitelisted, (account_name)(total_accounts)(max_accounts))
      };

      typedef multi_index<"freeacctlogs"_n, freeacctlog> t_freeaccountlogs;

      typedef multi_index<"whitelstacts"_n, whitelisted> t_whitelisted;

      freeaccounts(name self, name code, datastream<const char*> ds);

      ~freeaccounts();

protected:
      typedef singleton<"config"_n, freeacctcfg> config_singleton;
      config_singleton configuration;
      t_freeaccountlogs freeacctslogtable;
      t_whitelisted whitelistedtable;

      rammarket rammarkettable;
      static constexpr eosio::name             system_account{"eosio"_n};
      static constexpr symbol RAMCORE_symbol = symbol(symbol_code("RAMCORE"), 4);
      static constexpr symbol RAM_symbol     = symbol(symbol_code("RAM"), 0);
      static constexpr symbol TLOS_symbol    = symbol(symbol_code("TLOS"), 4);

      signup_public_key getpublickey(string public_key, string key_prefix);
      freeacctcfg getconfig();
};

/** All alphanumeric characters except for "0", "I", "O", and "l" */
static const char* pszBase58 = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
static const int8_t mapBase58[256] = {
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1, 0, 1, 2, 3, 4, 5, 6,  7, 8,-1,-1,-1,-1,-1,-1,
        -1, 9,10,11,12,13,14,15, 16,-1,17,18,19,20,21,-1,
        22,23,24,25,26,27,28,29, 30,31,32,-1,-1,-1,-1,-1,
        -1,33,34,35,36,37,38,39, 40,41,42,43,-1,44,45,46,
        47,48,49,50,51,52,53,54, 55,56,57,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1,-1,
};

bool DecodeBase58(const char* psz, std::vector<unsigned char>& vch)
{
    // Skip leading spaces.
    while (*psz && isspace(*psz))
        psz++;
    // Skip and count leading '1's.
    int zeroes = 0;
    int length = 0;
    while (*psz == '1') {
        zeroes++;
        psz++;
    }
    // Allocate enough space in big-endian base256 representation.
    int size = strlen(psz) * 733 /1000 + 1; // log(58) / log(256), rounded up.
    std::vector<unsigned char> b256(size);
    // Process the characters.
    static_assert(sizeof(mapBase58)/sizeof(mapBase58[0]) == 256, "mapBase58.size() should be 256"); // guarantee not out of range
    while (*psz && !isspace(*psz)) {
        // Decode base58 character
        int carry = mapBase58[(uint8_t)*psz];
        if (carry == -1)  // Invalid b58 character
            return false;
        int i = 0;
        for (std::vector<unsigned char>::reverse_iterator it = b256.rbegin(); (carry != 0 || i < length) && (it != b256.rend()); ++it, ++i) {
            carry += 58 * (*it);
            *it = carry % 256;
            carry /= 256;
        }
        assert(carry == 0);
        length = i;
        psz++;
    }
    // Skip trailing spaces.
    while (isspace(*psz))
        psz++;
    if (*psz != 0)
        return false;
    // Skip leading zeroes in b256.
    std::vector<unsigned char>::iterator it = b256.begin() + (size - length);
    while (it != b256.end() && *it == 0)
        it++;
    // Copy result into output vector.
    vch.reserve(zeroes + (b256.end() - it));
    vch.assign(zeroes, 0x00);
    while (it != b256.end())
        vch.push_back(*(it++));
    return true;
}

bool decode_base58(const string& str, vector<unsigned char>& vch) {
    return DecodeBase58(str.c_str(), vch);
}
