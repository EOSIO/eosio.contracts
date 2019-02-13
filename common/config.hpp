#pragma once

// TODO: Fully migrate to _n and remove
#ifndef UNIT_TEST_ENV
// test env still use N macro, so we continue to use it here
#   define STRINGIFY_(x) #x
#   define STRINGIFY(x) STRINGIFY_(x)
#   define N(x) eosio::name(STRINGIFY(x))
#endif

#ifdef UNIT_TEST_ENV
#   include <eosio/chain/types.hpp>
template <typename T, T... Str>
inline eosio::chain::name operator ""_n() {
   return eosio::chain::name({Str...});
}
#endif

namespace cyber { namespace config {

// contracts
static const auto token_name = "cyber.token"_n;
static const auto internal_name = "cyber"_n;

// permissions
static const auto code_name = "cyber.code"_n;
static const auto owner_name = "owner"_n;
static const auto active_name = "active"_n;
static const auto invoice_name = "invoice"_n;          // for vesting.retire
static const auto super_majority_name = "witn.smajor"_n;
static const auto majority_name = "witn.major"_n;
static const auto minority_name = "witn.minor"_n;

// numbers and time
static constexpr auto _1percent = 100;
static constexpr auto _100percent = 100 * _1percent;
static constexpr auto block_interval_ms = 3000;//1000 / 2;
static constexpr int64_t blocks_per_year = int64_t(365)*24*60*60*1000/block_interval_ms;

#ifndef UNIT_TEST_ENV
    static constexpr auto system_token = eosio::symbol("SYS", 4);
#else
    static const auto system_token = eosio::chain::symbol(4, "SYS");
#endif

static const std::string retire_memo = "retire";

} // config

constexpr int64_t time_to_blocks(int64_t time) {
    return time / (1000 * config::block_interval_ms);
}
constexpr int64_t seconds_to_blocks(int64_t sec) {
    return time_to_blocks(sec * 1e6);
}

} // cyber::config
