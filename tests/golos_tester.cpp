#include "golos_tester.hpp"
#include <eosio/chain/permission_object.hpp>

namespace eosio { namespace testing {

using std::vector;
using std::string;

uint64_t hash64(const std::string& s) {
    return fc::sha256::hash(s.c_str(), s.size())._hash[0];
}


void golos_tester::install_contract(
    account_name acc, const vector<uint8_t>& wasm, const vector<char>& abi, bool produce, const private_key_type* signer
) {
    set_code(acc, wasm, signer);
    set_abi (acc, abi.data(), signer);
    if (produce)
        produce_block();
    const auto& accnt = control->db().get<account_object,by_name>(acc);
    abi_def abi_d;
    BOOST_CHECK_EQUAL(abi_serializer::to_abi(accnt.abi, abi_d), true);
    _abis[acc].set_abi(abi_d, abi_serializer_max_time);
    _chaindb.add_abi(acc, abi_d);
};

vector<permission> golos_tester::get_account_permissions(account_name a) {
    vector<permission> r;
    const auto& d = control->db();
    const auto& perms = d.get_index<permission_index,by_owner>();
    auto perm = perms.lower_bound(boost::make_tuple(a));
    while (perm != perms.end() && perm->owner == a) {
        name parent;
        if (perm->parent._id) {
            const auto* p = d.find<permission_object,by_id>(perm->parent);
            if (p) {
                parent = p->name;
            }
        }
        r.push_back(permission{perm->name, parent, perm->auth.to_authority()});
        ++perm;
    }
    return r;
}

// this method do produce_block() internaly and checks that chain_has_transaction()
base_tester::action_result golos_tester::push_and_check_action(
    account_name code,
    action_name name,
    account_name signer,
    const variant_object& data
) {
    auto& abi = _abis[code];
    action act;
    act.account = code;
    act.name    = name;
    act.data    = abi.variant_to_binary(abi.get_action_type(name), data, abi_serializer_max_time);
    return base_tester::push_action(std::move(act), uint64_t(signer));
}

base_tester::action_result golos_tester::push_action(
    account_name code,
    action_name name,
    account_name signer,
    const variant_object& data
) {
    try {
        base_tester::push_action(code, name, signer, data);
    } catch (const fc::exception& ex) {
        edump((ex.to_detail_string()));
        return error(ex.top_message());
    }
    return success();
}

base_tester::action_result golos_tester::push_action_msig_tx(
    account_name code,
    action_name name,
    vector<permission_level> perms,
    vector<account_name> signers,
    const variant_object& data
) {
    auto& abi = _abis[code];
    action act;
    act.account = code;
    act.name    = name;
    act.data    = abi.variant_to_binary(abi.get_action_type(name), data, abi_serializer_max_time);
    for (const auto& perm : perms) {
        act.authorization.emplace_back(perm);
    }

    signed_transaction tx;
    tx.actions.emplace_back(std::move(act));
    set_transaction_headers(tx);
    for (const auto& a : signers) {
        tx.sign(get_private_key(a, "active"), control->get_chain_id());
    }
    return push_tx(std::move(tx));
}

base_tester::action_result golos_tester::push_tx(signed_transaction&& tx) {
    try {
        push_transaction(tx);
    } catch (const fc::exception& ex) {
        edump((ex.to_detail_string()));
        return error(ex.top_message()); // top_message() is assumed by many tests; otherwise they fail
        //return error(ex.to_detail_string());
    }
    produce_block();
    BOOST_REQUIRE_EQUAL(true, chain_has_transaction(tx.id()));
    return success();
}

// table helpers
const table_id_object* golos_tester::find_table(name code, uint64_t scope, name tbl) const {
    auto tid = control->db().find<table_id_object, by_code_scope_table>(std::make_tuple(code, scope, tbl));
    return tid;
}

vector<char> golos_tester::get_tbl_row(name code, uint64_t scope, name tbl, uint64_t id) const {
    vector<char> data;
    const auto& tid = find_table(code, scope, tbl);
    if (tid) {
        const auto& db = control->db();
        const auto& idx = db.get_index<chain::key_value_index, chain::by_scope_primary>();
        auto itr = idx.lower_bound(std::make_tuple(tid->id, id));
        if (itr != idx.end() && itr->t_id == tid->id) {
            data.resize(itr->value.size());
            memcpy(data.data(), itr->value.data(), data.size());
        }
    }
    return data;
}

variant golos_tester::get_tbl_struct(name code, uint64_t scope, name tbl, uint64_t id, const string& n) const {
    vector<char> data = get_tbl_row(code, scope, tbl, id);
    const auto& abi = _abis.at(code);
    return data.empty() ? variant() : abi.binary_to_variant(n, data, abi_serializer_max_time);
}

variant golos_tester::get_tbl_singleton(name code, uint64_t scope, name tbl, const string& n) const {
    return get_tbl_struct(code, scope, tbl, tbl, n);
}

vector<vector<char>> golos_tester::get_all_rows(name code, uint64_t scope, name table, bool strict) const {
    vector<vector<char>> ret;
    const auto& db = control->db();
    const auto* t_id = db.find<chain::table_id_object, chain::by_code_scope_table>(std::make_tuple(code, scope, table));
    if (strict)
        BOOST_REQUIRE_EQUAL(true, static_cast<bool>(t_id));
    else if (!static_cast<bool>(t_id))
        return ret;
    const auto& idx = db.get_index<chain::key_value_index, chain::by_scope_primary>();
    for (auto itr = idx.lower_bound(std::make_tuple(t_id->id, 0)); itr != idx.end() && itr->t_id == t_id->id; ++itr) {
        ret.push_back(vector<char>());
        auto& data = ret.back();
        data.resize(itr->value.size());
        memcpy(data.data(), itr->value.data(), data.size());
    }
    return ret;
}

variant golos_tester::get_chaindb_struct(name code, uint64_t scope, name tbl, uint64_t id,
    const string& n
) const {
    variant r;
    try {
        r = _chaindb.value_by_pk({code, scope, tbl}, id);
    } catch (...) {
        // key not found
    }
    return r;
}

variant golos_tester::get_chaindb_singleton(name code, uint64_t scope, name tbl,
    const string& n
) const {
    return get_chaindb_struct(code, scope, tbl, tbl, n);
}

vector<variant> golos_tester::get_all_chaindb_rows(name code, uint64_t scope, name tbl, bool strict) const {
    vector<variant> all;
    auto info = _chaindb.lower_bound({code, scope, tbl, N(primary)}, nullptr, 0);
    cyberway::chaindb::cursor_request cursor = {code, info.cursor};
    auto v = _chaindb.value_at_cursor(cursor);
    if (strict) {
        BOOST_TEST_REQUIRE(!v.is_null());
    } else if (v.is_null()) {
        return all;
    }

    auto prev = _chaindb.current(cursor);
    do {
        all.push_back(v);
        auto pk = _chaindb.next(cursor);
        if (pk == prev || pk == 0xFFFFFFFFFFFFFFFF) {   // TODO: magic is bad, update `value_at_cursor` to return `null` as end
            break;
        }
        prev = pk;
        v = _chaindb.value_at_cursor(cursor);
    } while (!v.is_null());
    return all;
}

void golos_tester::delegate_authority(account_name from, std::vector<account_name> to, 
        account_name code, action_name type, permission_name req, permission_name parent, permission_name prov) {
            
    authority auth(1, {});
    for (auto u : to) {
        auth.accounts.emplace_back(permission_level_weight{.permission = {u, prov}, .weight = 1});
    }
    std::sort(auth.accounts.begin(), auth.accounts.end(),
        [](const permission_level_weight& l, const permission_level_weight& r) {
            return std::tie(l.permission.actor, l.permission.permission) <
                std::tie(r.permission.actor, r.permission.permission);
        });
    set_authority(from, req, auth, parent);
    link_authority(from, code, req, type);
    
}

}} // eosio::tesing
