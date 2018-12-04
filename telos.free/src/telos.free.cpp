/**
 * Supports creation of free Telos accounts
 * 
 * @author Marlon Williams
 * @copyright defined in telos/LICENSE.txt
 */

#include <telos.free/telos.free.hpp>

using eosio::print;

freeaccounts::freeaccounts(name self, name code, datastream<const char*> ds) : 
contract(self, code, ds), 
configuration(self, self.value),
freeacctslogtable(self, self.value),
rammarkettable(system_account, system_account.value)
 {
    if (!configuration.exists()) {
        configuration.set(freeacctcfg {
            self,               // publisher
            int16_t(50),        // max_accounts_per_hour
            int16_t(9000),      // stake_cpu_tlos_amount
            int16_t(1000),      // stake_net_tlos_amount
        }, self);
    } else {
        configuration.get();
    }
}

freeaccounts::~freeaccounts() {
}

void freeaccounts::create( name account_name, string owner_key, string active_key, string key_prefix)
{
    // verify that we're within our account creation per hour threshold
    uint64_t accounts_created = 0;
    for (const auto& account : freeacctslogtable)
    {
        uint64_t secs_since_created = now() - account.created_on;
        if (secs_since_created <= 3600) {
            accounts_created++;
        }
    }

    auto config = getconfig();
    eosio_assert(accounts_created < config.max_accounts_per_hour, "You have exceeded the maximum number of accounts per hour");

    signup_public_key owner_pubkey = getpublickey(owner_key, key_prefix);
    signup_public_key active_pubkey = getpublickey(active_key, key_prefix);

    key_weight owner_pubkey_weight = {
        .key = owner_pubkey,
        .weight = 1,
    };
    key_weight active_pubkey_weight = {
        .key = active_pubkey,
        .weight = 1,
    };
    authority owner = authority{
        .threshold = 1,
        .keys = {owner_pubkey_weight},
        .accounts = {},
        .waits = {}
    };
    authority active = authority{
        .threshold = 1,
        .keys = {active_pubkey_weight},
        .accounts = {},
        .waits = {}
    };
    newaccount new_account = newaccount{
        .creator = _self,
        .name = account_name,
        .owner = owner,
        .active = active
    };

    // dynamically discover ram pricing
    uint32_t four_kb = 4096;
    auto itr = rammarkettable.find(RAMCORE_symbol.raw());
    auto tmp = *itr;
    asset ram_price = tmp.convert( asset(four_kb, RAM_symbol), TLOS_symbol);
    ram_price.amount = (ram_price.amount * 200 + 199) / 199; // add ram fee

    asset stake_net(config.stake_net_tlos_amount, TLOS_symbol);
    asset stake_cpu(config.stake_cpu_tlos_amount, TLOS_symbol);

    action(
            permission_level{ _self, "active"_n, },
            "eosio"_n,
            "newaccount"_n,
            new_account
    ).send();

    action(
            permission_level{ _self, "active"_n},
            "eosio"_n,
            "buyram"_n,
            make_tuple(_self, account_name, ram_price)
    ).send();

    action(
            permission_level{ _self, "active"_n},
            "eosio"_n,
            "delegatebw"_n,
            make_tuple(_self, account_name, stake_net, stake_cpu, false)
    ).send();

    // record entry for audit purposes
    freeacctslogtable.emplace( _self, [&]( freeacctlog& entry ){
        entry.account_name  = account_name;
        entry.created_on    = now();
    });
}

void freeaccounts::configure(int16_t max_accounts_per_hour, int64_t stake_cpu_tlos_amount, int64_t stake_net_tlos_amount)
{
    require_auth(_self);
    eosio_assert(max_accounts_per_hour >= 0 && max_accounts_per_hour <= 1000, "Max accounts per hour outside of the range allowed");
    eosio_assert(stake_cpu_tlos_amount >= 100 && stake_cpu_tlos_amount <= 50000, "Staked TLOS for CPU outside of the range allowed");
    eosio_assert(stake_net_tlos_amount >= 100 && stake_net_tlos_amount <= 50000, "Staked TLOS for NET outside of the range allowed");
    
    auto config = getconfig();
    config.max_accounts_per_hour = max_accounts_per_hour;
    config.stake_cpu_tlos_amount = stake_cpu_tlos_amount;
    config.stake_net_tlos_amount = stake_net_tlos_amount;
    configuration.set(config, _self);
}

freeaccounts::freeacctcfg freeaccounts::getconfig() {
    return configuration.get_or_create(_self, freeacctcfg {});
}

freeaccounts::signup_public_key freeaccounts::getpublickey (string public_key, string key_prefix) {
    auto result = mismatch(key_prefix.begin(), key_prefix.end(), public_key.begin());
    eosio_assert(result.first == key_prefix.end(), "Public key prefix doesn't match key supplied");
    auto base58substr = public_key.substr(key_prefix.length());

    vector<unsigned char> vch;
    eosio_assert(decode_base58(base58substr, vch), "Decoding public key failed");
    eosio_assert(vch.size() == 37, "Invalid public key");

    array<unsigned char,33> key_data;
    copy_n(vch.begin(), 33, key_data.begin());

    capi_checksum160 check_pubkey;
    ripemd160(reinterpret_cast<char *>(key_data.data()), 33, &check_pubkey);
    eosio_assert(memcmp(&check_pubkey.hash, &vch.end()[-4], 4) == 0, "Invalid Owner key");
    
    freeaccounts::signup_public_key pubkey = {
        .type = 0,
        .data = key_data,
    };

    return pubkey;
}

EOSIO_DISPATCH( freeaccounts, (configure)(create) )