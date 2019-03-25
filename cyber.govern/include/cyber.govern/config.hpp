#pragma once
#include <common/config.hpp>

namespace cyber { namespace config {
    
static const auto issuer_name = internal_name;
    
static const auto sum_up_interval = 701;
static const auto reward_for_staked_interval = 113;

static const auto balances_update_window = sum_up_interval * block_interval_ms / 1000;

static constexpr uint16_t active_producers_num = 21;
static constexpr uint16_t elected_producers_num = 37;
static constexpr uint16_t active_reserve_producers_num = 1;

static_assert(active_producers_num >= active_reserve_producers_num, "wrong producers num");
static constexpr uint16_t active_top_producers_num = active_producers_num - active_reserve_producers_num;

static constexpr uint8_t allowable_number_of_missing_blocks = 1;

//TODO: should be calculated:
static constexpr int64_t block_reward = 5;
static constexpr int64_t reward_of_elected = 33;
static int64_t missing_block_amerce = 100;

}

} // cyber::config
