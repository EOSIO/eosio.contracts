#include "contracts.hpp"
#include "eosio.system_tester.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/test/unit_test.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/testing/tester.hpp>

#include <Runtime/Runtime.h>

#include <fc/io/json.hpp>
#include <fc/static_variant.hpp>

#ifdef NON_VALIDATING_TEST
#define TESTER tester
#else
#define TESTER validating_tester
#endif

using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;

inline constexpr auto operator""_n(const char* s, std::size_t) { return string_to_name(s); }

#define CHECK_ASSERT(S, M)                                                                                             \
   try {                                                                                                               \
      S;                                                                                                               \
      BOOST_ERROR("exception eosio_assert_message_exception is expected");                                             \
   } catch (eosio_assert_message_exception & e) {                                                                      \
      if (e.top_message() != "assertion failure with message: " M)                                                     \
         BOOST_ERROR("expected \"assertion failure with message: " M "\" got \"" + e.top_message() + "\"");            \
   }

static const fc::microseconds abi_serializer_max_time{1'000'000};

class assert_tester : public TESTER {
 public:
   using TESTER::push_transaction;
   void push_transaction(name signer, const std::string& s) {
      auto v = json::from_string(s);
      outfile << "push_transaction " << json::to_pretty_string(v) << "\n";

      signed_transaction trx;
      for (auto& a : v["actions"].get_array()) {
         variant_object data;
         from_variant(a["data"], data);
         action act;
         act.account       = a["account"].as<name>();
         act.name          = a["name"].as<name>();
         act.authorization = a["authorization"].as<vector<permission_level>>();
         act.data = abi_ser.variant_to_binary(abi_ser.get_action_type(act.name), data, abi_serializer_max_time);
         trx.actions.emplace_back(std::move(act));
      }

      try {
         set_transaction_headers(trx);
         trx.sign(get_private_key(signer, "active"), control->get_chain_id());
         push_transaction(trx);
         outfile << "transaction pushed\n";
      } catch (fc::exception& e) {
         outfile << "Exception: " << e.top_message() << "\n";
      }
   }

   assert_tester(const std::string& test_name)
       : TESTER(), test_name{test_name}, outfile{ASSERT_DATA_DIR + test_name + ".actual"}, abi{contracts::assert_abi()},
         abi_ser(json::from_string(std::string{abi.data(), abi.data() + abi.size()}).as<abi_def>(),
                 abi_serializer_max_time) {

      set_code("eosio"_n, contracts::bios_wasm());
      set_abi("eosio"_n, contracts::bios_abi().data());

      create_account("eosio.assert"_n);
      set_code("eosio.assert"_n, contracts::assert_wasm());
      set_abi("eosio.assert"_n, contracts::assert_abi().data());
   }

   struct row {
      uint64_t primary_key;
      bytes    value;
   };

   auto get_table(name account, name scope, name table) {
      std::vector<row> rows;
      const auto&      db  = control->db();
      const auto*      tbl = db.find<table_id_object, by_code_scope_table>(boost::make_tuple(account, scope, table));
      if (!tbl)
         return rows;
      auto& idx = db.get_index<key_value_index, by_scope_primary>();
      for (auto it = idx.lower_bound(std::make_tuple(tbl->id, 0)); it != idx.end() && it->t_id == tbl->id; ++it)
         rows.push_back(row{it->primary_key, bytes{it->value.begin(), it->value.end()}});
      return rows;
   }

   void diff_table(name account, name scope, name table, const std::string& type, std::vector<row>& existing) {
      outfile << "table: " << account << " " << scope << " " << table << "\n";
      auto updated = get_table(account, scope, table);

      std::map<uint64_t, std::pair<optional<bytes>, optional<bytes>>> comparison;
      for (auto& x : existing)
         comparison[x.primary_key].first = x.value;
      for (auto& x : updated)
         comparison[x.primary_key].second = x.value;

      auto str = [&](bytes& b) {
         auto        s = "\n" + json::to_pretty_string(abi_ser.binary_to_variant(type, b, abi_serializer_max_time));
         std::string result;
         for (auto ch : s)
            if (ch == '\n')
               result += "\n        ";
            else
               result += ch;
         return result;
      };

      for (auto& x : comparison) {
         if (!x.second.first)
            outfile << "    add row:" << str(*x.second.second) << "\n";
         else if (!x.second.second)
            outfile << "    del row:" << str(*x.second.first) << "\n";
         else if (*x.second.first != *x.second.second)
            outfile << "    change row:" << str(*x.second.second) << "\n";
      }
      existing = std::move(updated);
   }

   struct table {
      name             account;
      name             scope;
      name             table;
      std::string      type;
      std::vector<row> rows;
   };

   void diff_table(table& t) { diff_table(t.account, t.scope, t.table, t.type, t.rows); }

   void heading(const std::string& s) { outfile << "\n" << s << "\n=========================\n"; }

   void check_file() {
      outfile.close();
      if (write_mode)
         BOOST_REQUIRE_EQUAL(
             0, system(("cp " ASSERT_DATA_DIR + test_name + ".actual " ASSERT_DATA_DIR + test_name + ".expected").c_str()));
      else
         BOOST_REQUIRE_EQUAL(
             0, system(("colordiff " ASSERT_DATA_DIR + test_name + ".expected " ASSERT_DATA_DIR + test_name + ".actual").c_str()));
   }

   std::string           test_name;
   mutable std::ofstream outfile;
   std::vector<char>     abi;
   abi_serializer        abi_ser;
};

BOOST_AUTO_TEST_SUITE(assert)

BOOST_AUTO_TEST_CASE(setchain) try {
   assert_tester        t{"setchain"};
   assert_tester::table manifests{"eosio.assert"_n, "eosio.assert"_n, "manifests"_n, "stored_manifest"};
   assert_tester::table chain_params{"eosio.assert"_n, "eosio.assert"_n, "chain.params"_n, "stored_chain_params"};
   t.create_account("someone"_n);

   t.heading("setchain: missing authority");
   t.push_transaction("someone"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "setchain",
         "authorization": [{
            "actor":             "someone",
            "permission":        "active",
         }],
         "data": {
            "chain_id":          "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF",
            "chain_name":        "My Mega Sidechain",
            "icon":              "BEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEF"
         },
      }]
   })");
   t.diff_table(chain_params);

   t.heading("setchain");
   t.push_transaction("eosio"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "setchain",
         "authorization": [{
            "actor":             "eosio",
            "permission":        "active",
         }],
         "data": {
            "chain_id":          "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF",
            "chain_name":        "My Mega Sidechain",
            "icon":              "BEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEF"
         },
      }]
   })");
   t.diff_table(chain_params);

   t.heading("setchain: update");
   t.push_transaction("eosio"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "setchain",
         "authorization": [{
            "actor":             "eosio",
            "permission":        "active",
         }],
         "data": {
            "chain_id":          "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF",
            "chain_name":        "Renamed",
            "icon":              "123412341234123412341234123412341234123412341234123412341234FEED"
         },
      }]
   })");
   t.diff_table(chain_params);

   t.check_file();
}
FC_LOG_AND_RETHROW() // setchain

BOOST_AUTO_TEST_CASE(add_manifest) try {
   assert_tester        t{"add_manifest"};
   assert_tester::table manifests{"eosio.assert"_n, "eosio.assert"_n, "manifests"_n, "stored_manifest"};
   assert_tester::table chain_params{"eosio.assert"_n, "eosio.assert"_n, "chain.params"_n, "stored_chain_params"};
   t.create_account("dapp1"_n);
   t.create_account("dapp2"_n);

   t.heading("add.manifest: missing authority");
   t.push_transaction("dapp2"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "add.manifest",
         "authorization": [{
            "actor":             "dapp2",
            "permission":        "active",
         }],
         "data": {
            "account":           "dapp1",
            "appmeta":           "distributed app 1",
            "domain":            "https://nowhere",
            "whitelist":         [],
         },
      }]
   })");

   t.heading("add.manifest");
   t.push_transaction("dapp1"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "add.manifest",
         "authorization": [{
            "actor":             "dapp1",
            "permission":        "active",
         }],
         "data": {
            "account":           "dapp1",
            "appmeta":           "distributed app 1",
            "domain":            "https://nowhere",
            "whitelist":         [],
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.heading("add.manifest: duplicate");
   t.produce_block();
   t.push_transaction("dapp1"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "add.manifest",
         "authorization": [{
            "actor":             "dapp1",
            "permission":        "active",
         }],
         "data": {
            "account":           "dapp1",
            "appmeta":           "distributed app 1",
            "domain":            "https://nowhere",
            "whitelist":         [],
         },
      }]
   })");

   t.heading("add.manifest: whitelist");
   t.produce_block();
   t.push_transaction("dapp1"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "add.manifest",
         "authorization": [{
            "actor":             "dapp1",
            "permission":        "active",
         }],
         "data": {
            "account":           "dapp1",
            "appmeta":           "distributed app 1",
            "domain":            "https://nowhere",
            "whitelist":         [{
               "contract":       "contract.2",
               "action":         ""
            }, {
               "contract":       "contract.1",
               "action":         "just.this"
            }, {
               "contract":       "contract.3",
               "action":         ""
            }]
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.heading("del.manifest: not found");
   t.push_transaction("dapp2"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "del.manifest",
         "authorization": [{
            "actor":             "dapp2",
            "permission":        "active",
         }],
         "data": {
            "id":                "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF",
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.heading("del.manifest: wrong auth");
   t.push_transaction("dapp2"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "del.manifest",
         "authorization": [{
            "actor":             "dapp2",
            "permission":        "active",
         }],
         "data": {
            "id":                "50e7051e63420d2912dbbf72e32bc511722057311544d4b3226706354f787433",
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.heading("del.manifest");
   t.push_transaction("dapp1"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "del.manifest",
         "authorization": [{
            "actor":             "dapp1",
            "permission":        "active",
         }],
         "data": {
            "id":                "50e7051e63420d2912dbbf72e32bc511722057311544d4b3226706354f787433",
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.heading("del.manifest");
   t.push_transaction("dapp1"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "del.manifest",
         "authorization": [{
            "actor":             "dapp1",
            "permission":        "active",
         }],
         "data": {
            "id":                "49b4217257a723b59bbe6ff46e2d504734e3c4a5233938a4a843ed2bce380e2a",
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.check_file();
}
FC_LOG_AND_RETHROW() // add_manifest

BOOST_AUTO_TEST_CASE(require) try {
   assert_tester        t{"require"};
   assert_tester::table manifests{"eosio.assert"_n, "eosio.assert"_n, "manifests"_n, "stored_manifest"};
   assert_tester::table chain_params{"eosio.assert"_n, "eosio.assert"_n, "chain.params"_n, "stored_chain_params"};
   t.create_account("dapp1"_n);
   t.create_account("wild"_n);
   t.create_account("user"_n);

   t.heading("setchain");
   t.push_transaction("eosio"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "setchain",
         "authorization": [{
            "actor":             "eosio",
            "permission":        "active",
         }],
         "data": {
            "chain_id":          "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF",
            "chain_name":        "My Mega Sidechain",
            "icon":              "BEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEF"
         },
      }]
   })");
   t.diff_table(chain_params);

   t.heading("add.manifest");
   t.push_transaction("dapp1"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "add.manifest",
         "authorization": [{
            "actor":             "dapp1",
            "permission":        "active",
         }],
         "data": {
            "account":           "dapp1",
            "appmeta":           "distributed app 1",
            "domain":            "https://nowhere",
            "whitelist":         [{
               "contract":       "contract.2",
               "action":         ""
            }, {
               "contract":       "contract.1",
               "action":         "just.this"
            }, {
               "contract":       "",
               "action":         "transfer"
            }]
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.heading("add.manifest");
   t.push_transaction("wild"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "add.manifest",
         "authorization": [{
            "actor":             "wild",
            "permission":        "active",
         }],
         "data": {
            "account":           "wild",
            "appmeta":           "distributed app 1",
            "domain":            "https://nowhere",
            "whitelist":         [{
               "contract":       "",
               "action":         ""
            }],
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.heading("require: wrong chain");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF",
            "manifest_id":       "BEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEF",
            "actions":           [],
            "abi_hashes":        []
         },
      }]
   })");

   t.heading("require: unknown manifest");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "BEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEF",
            "actions":           [],
            "abi_hashes":        []
         },
      }]
   })");

   t.heading("require");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "c9bfa4363ea2c08df2bb41f5393fec96b323a399cd57783f2c0535f66326e3d2",
            "actions":           [],
            "abi_hashes":        []
         },
      }]
   })");

   t.heading("require: simple match whitelist");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "c9bfa4363ea2c08df2bb41f5393fec96b323a399cd57783f2c0535f66326e3d2",
            "actions":           [{
               "contract":       "contract.1",
               "action":         "just.this"
            }],
            "abi_hashes":        ["0000000000000000000000000000000000000000000000000000000000000000"]
         },
      }]
   })");

   t.heading("require: whitelist wild action");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "c9bfa4363ea2c08df2bb41f5393fec96b323a399cd57783f2c0535f66326e3d2",
            "actions":           [{
               "contract":       "contract.2",
               "action":         "foo"
            }],
            "abi_hashes":        ["0000000000000000000000000000000000000000000000000000000000000000"]
         },
      }]
   })");

   t.heading("require: whitelist wild contract");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "c9bfa4363ea2c08df2bb41f5393fec96b323a399cd57783f2c0535f66326e3d2",
            "actions":           [{
               "contract":       "unknown",
               "action":         "transfer"
            }],
            "abi_hashes":        ["0000000000000000000000000000000000000000000000000000000000000000"]
         },
      }]
   })");

   t.heading("require: whitelist full wild");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "4fc817b2e2d537b4a7311df3faeaafcbdfe35b25b19269e89da818a06a4a2997",
            "actions":           [{
               "contract":       "unk.account",
               "action":         "unk.action"
            }],
            "abi_hashes":        ["0000000000000000000000000000000000000000000000000000000000000000"]
         },
      }]
   })");

   t.heading("require: whitelist doesn't match");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "c9bfa4363ea2c08df2bb41f5393fec96b323a399cd57783f2c0535f66326e3d2",
            "actions":           [{
               "contract":       "unk.account",
               "action":         "unk.action"
            }],
            "abi_hashes":        ["0000000000000000000000000000000000000000000000000000000000000000"]
         },
      }]
   })");

   t.check_file();
}
FC_LOG_AND_RETHROW() // require

BOOST_AUTO_TEST_CASE(require_abi_hash) try {
   assert_tester t{"require_abi_hash"};
   t.create_account("wild"_n);
   t.create_account("user"_n);
   t.create_account("foo"_n);
   t.create_account("bar"_n);
   t.create_account("baz"_n);
   t.set_abi("foo"_n, contracts::util::test_foo_abi().data());
   t.set_abi("bar"_n, contracts::util::test_bar_abi().data());
   t.set_abi("baz"_n, contracts::util::test_baz_abi().data());
   assert_tester::table manifests{"eosio.assert"_n, "eosio.assert"_n, "manifests"_n, "stored_manifest"};
   assert_tester::table chain_params{"eosio.assert"_n, "eosio.assert"_n, "chain.params"_n, "stored_chain_params"};

   t.heading("setchain");
   t.push_transaction("eosio"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "setchain",
         "authorization": [{
            "actor":             "eosio",
            "permission":        "active",
         }],
         "data": {
            "chain_id":          "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF",
            "chain_name":        "My Mega Sidechain",
            "icon":              "BEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEFBEEF"
         },
      }]
   })");
   t.diff_table(chain_params);

   t.heading("hash: add.manifest");
   t.push_transaction("wild"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "add.manifest",
         "authorization": [{
            "actor":             "wild",
            "permission":        "active",
         }],
         "data": {
            "account":           "wild",
            "appmeta":           "distributed app 1",
            "domain":            "https://nowhere",
            "whitelist":         [{
               "contract":       "",
               "action":         ""
            }],
         },
      }]
   })");
   t.diff_table(chain_params);
   t.diff_table(manifests);

   t.heading("hash: unknown");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "4fc817b2e2d537b4a7311df3faeaafcbdfe35b25b19269e89da818a06a4a2997",
            "actions":           [{
               "contract":       "unk.account",
               "action":         "unk.action"
            }],
            "abi_hashes":        ["0000000000000000000000000000000000000000000000000000000000000000"]
         },
      }]
   })");

   t.heading("hash: 1");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "4fc817b2e2d537b4a7311df3faeaafcbdfe35b25b19269e89da818a06a4a2997",
            "actions":           [{
               "contract":       "bar",
               "action":         "unk.action"
            }],
            "abi_hashes":        ["d6878c7fc285a65df6cf02cad9e11532321e6c5a3dc48f6f9fd150bc1b90c378"]
         },
      }]
   })");

   t.heading("hash: 3");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "4fc817b2e2d537b4a7311df3faeaafcbdfe35b25b19269e89da818a06a4a2997",
            "actions":           [{
               "contract":       "baz",
               "action":         "unk.action"
            },{
               "contract":       "foo",
               "action":         "unk.action"
            },{
               "contract":       "baz",
               "action":         "another"
            },{
               "contract":       "foo",
               "action":         "whoa"
            },{
               "contract":       "bar",
               "action":         "unk.action"
            }],
            "abi_hashes":        [
                                    "d6878c7fc285a65df6cf02cad9e11532321e6c5a3dc48f6f9fd150bc1b90c378",
                                    "58e2dec1abd4dcbf8121736b39b07f5db4a1dd29025c44023c7a37d305e40b14",
                                    "b82da7015d860512403b6fec2188ffb8b1803d07df654bb79986465f2d5895c6",
                                 ]
         },
      }]
   })");

   t.heading("hash: mismatch");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "4fc817b2e2d537b4a7311df3faeaafcbdfe35b25b19269e89da818a06a4a2997",
            "actions":           [{
               "contract":       "baz",
               "action":         "unk.action"
            },{
               "contract":       "foo",
               "action":         "unk.action"
            },{
               "contract":       "baz",
               "action":         "another"
            },{
               "contract":       "foo",
               "action":         "whoa"
            },{
               "contract":       "bar",
               "action":         "unk.action"
            }],
            "abi_hashes":        [
                                    "d6878c7fc285a65df6cf02cad9e11532321e6c5a3dc48f6f9fd150bc1b90c378",
                                    "1231231231231231231231231231231231231231231231231231231231231233",
                                    "b82da7015d860512403b6fec2188ffb8b1803d07df654bb79986465f2d5895c6",
                                 ]
         },
      }]
   })");

   t.heading("hash: wrong number of hashes");
   t.push_transaction("user"_n, R"({
      "actions": [{
         "account":              "eosio.assert",
         "name":                 "require",
         "authorization": [{
            "actor":             "user",
            "permission":        "active",
         }],
         "data": {
            "chain_params_hash": "a5e2578a54c35885716a63d70d4b51b227d8aa47ad9a3163c733b79160bb513c",
            "manifest_id":       "4fc817b2e2d537b4a7311df3faeaafcbdfe35b25b19269e89da818a06a4a2997",
            "actions":           [{
               "contract":       "baz",
               "action":         "unk.action"
            },{
               "contract":       "foo",
               "action":         "unk.action"
            },{
               "contract":       "baz",
               "action":         "another"
            },{
               "contract":       "foo",
               "action":         "whoa"
            },{
               "contract":       "bar",
               "action":         "unk.action"
            }],
            "abi_hashes":        [
                                    "d6878c7fc285a65df6cf02cad9e11532321e6c5a3dc48f6f9fd150bc1b90c378",
                                    "b82da7015d860512403b6fec2188ffb8b1803d07df654bb79986465f2d5895c6",
                                 ]
         },
      }]
   })");

   t.check_file();
}
FC_LOG_AND_RETHROW() // require_abi_hash

BOOST_AUTO_TEST_SUITE_END()
