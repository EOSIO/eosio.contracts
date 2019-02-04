#pragma once
#include "test_api_helper.hpp"

namespace eosio { namespace testing {
    
struct cyber_token_api: base_contract_api {
    cyber_token_api(golos_tester* tester, name code, symbol sym)
    :   base_contract_api(tester, code)
    ,   _symbol(sym) {}

    symbol _symbol;

    //// token actions
    action_result create(account_name issuer, asset maximum_supply) {
        return push(N(create), _code, args()
            ("issuer", issuer)
            ("maximum_supply", maximum_supply)
        );
    }

    action_result issue(account_name issuer, account_name to, asset quantity, string memo) {
        return push(N(issue), issuer, args()
            ("to", to)
            ("quantity", quantity)
            ("memo", memo)
        );
    }

    action_result open(account_name owner, symbol symbol, account_name payer) {
        return push(N(open), owner, args()
            ("owner", owner)
            ("symbol", symbol)
            ("ram_payer", payer)
        );
    }
    
    action_result close(account_name owner, symbol symbol) {
        return push(N(close), owner, args()
            ("owner", owner)
            ("symbol", symbol)
        );
    }

    action_result transfer(account_name from, account_name to, asset quantity, string memo = "") {
        return push(N(transfer), from, args()
            ("from", from)
            ("to", to)
            ("quantity", quantity)
            ("memo", memo)
        );
    }

    //// token tables
    variant get_stats() {
        auto sname = _symbol.to_symbol_code().value;
        auto v = get_struct(sname, N(stat), sname, "currency_stats");
        if (v.is_object()) {
            auto o = mvo(v);
            o["supply"] = o["supply"].as<asset>().to_string();
            o["max_supply"] = o["max_supply"].as<asset>().to_string();
            v = o;
        }
        return v;
    }

    variant get_account(account_name acc) {
        auto v = get_struct(acc, N(accounts), _symbol.to_symbol_code().value, "account");
        if (v.is_object()) {
            auto o = mvo(v);
            o["balance"] = o["balance"].as<asset>().to_string();
            v = o;
        }
        return v;
    }

    std::vector<variant> get_accounts(account_name user) {
        return _tester->get_all_chaindb_rows(_code, user, N(accounts), false);
    }

    //// helpers
    int64_t to_shares(double x) const {
        return x * _symbol.precision();
    }
    asset make_asset(double x = 0) const {
        return asset(to_shares(x), _symbol);
    }
    string asset_str(double x = 0) {
        return make_asset(x).to_string();
    }

};


}} // eosio::testing
