#pragma once
#include "test_api_helper.hpp"
#include "../common/config.hpp"

namespace eosio { namespace testing {

struct cyber_govern_api: base_contract_api {
public:
    cyber_govern_api(golos_tester* tester, name code)
    :   base_contract_api(tester, code){}

     ////tables
    variant get_producers_group(bool active = true, bool elected = true) {
        auto all = _tester->get_all_chaindb_rows(_code, _code.value, N(producer), false);
        std::vector<account_name> ret_vec;
        for(auto& v : all) {
            if (v["elected"].as<bool>() == elected && static_cast<bool>(v["commencement_block"].as<uint32_t>()) == active) {
                ret_vec.emplace_back(v["account"].as<account_name>());
            }
        }
        variant ret;
        to_variant(ret_vec, ret);
        return ret;
    }
    
    variant make_producers_group(std::vector<account_name> accounts) {
        std::sort(accounts.begin(), accounts.end());
        variant ret;
        to_variant(accounts, ret);
        return ret;
    }
    
};

}} // eosio::testing
