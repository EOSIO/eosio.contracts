#include <eosio.token/eosio.token.hpp>
#include <eosio/tester.hpp>

using namespace eosio;

namespace eosio {

inline bool operator!=(const token::currency_stats& a, const token::currency_stats& b) {
   return a.supply != b.supply || a.max_supply != b.max_supply || a.issuer != b.issuer;
}

} // namespace eosio

struct token_tester {
   test_chain chain;

   token_tester() {
      chain.create_account("alice"_n);
      chain.create_account("bob"_n);
      chain.create_account("carol"_n);
      chain.create_code_account("eosio.token"_n);
      chain.set_code("eosio.token"_n, "contracts/eosio.token/eosio.token.wasm");
   }

   chain_types::transaction_trace create(name issuer, const asset& maximum_supply,
                                         const char* expected_except = nullptr) {
      return chain.transact({ token::create_action{ "eosio.token"_n, { "eosio.token"_n, "active"_n } }.to_action(
                                  issuer, maximum_supply) },
                            expected_except);
   }

   chain_types::transaction_trace issue(name issuer, name to, const asset& quantity, const string& memo,
                                        const char* expected_except = nullptr) {
      return chain.transact(
            { token::issue_action{ "eosio.token"_n, { issuer, "active"_n } }.to_action(to, quantity, memo) },
            expected_except);
   }

   chain_types::transaction_trace retire(name issuer, const asset& quantity, const string& memo,
                                         const char* expected_except = nullptr) {
      return chain.transact(
            { token::retire_action{ "eosio.token"_n, { issuer, "active"_n } }.to_action(quantity, memo) },
            expected_except);
   }

   chain_types::transaction_trace transfer(name from, name to, const asset& quantity, const string& memo,
                                           const char* expected_except = nullptr) {
      return chain.transact(
            { token::transfer_action{ "eosio.token"_n, { from, "active"_n } }.to_action(from, to, quantity, memo) },
            expected_except);
   }

   chain_types::transaction_trace open(name owner, const symbol& symbol, name ram_payer,
                                       const char* expected_except = nullptr) {
      return chain.transact(
            { token::open_action{ "eosio.token"_n, { ram_payer, "active"_n } }.to_action(owner, symbol, ram_payer) },
            expected_except);
   }

   chain_types::transaction_trace close(name owner, const symbol& symbol, const char* expected_except = nullptr) {
      return chain.transact({ token::close_action{ "eosio.token"_n, { owner, "active"_n } }.to_action(owner, symbol) },
                            expected_except);
   }

   auto get_stats(symbol_code sym_code) {
      token::stats statstable("eosio.token"_n, sym_code.raw());
      return statstable.get(sym_code.raw());
   }

   std::optional<token::account> get_account_optional(name owner, symbol_code sym_code) {
      token::accounts accountstable("eosio.token"_n, owner.value);
      auto            it = accountstable.find(sym_code.raw());
      if (it != accountstable.end())
         return *it;
      else
         return {};
   }
}; // token_tester

TEST_CASE(create_tests, [] {
   token_tester t;

   t.create("alice"_n, s2a("1000.000 TKN"));
   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "TKN" }), //
                        (token::currency_stats{
                              .supply     = s2a("0.000 TKN"),
                              .max_supply = s2a("1000.000 TKN"),
                              .issuer     = "alice"_n,
                        }));
})

TEST_CASE(create_negative_max_supply, [] {
   token_tester t;
   t.create("alice"_n, s2a("-1000.000 TKN"), "max-supply must be positive");
})

TEST_CASE(symbol_already_exists, [] {
   token_tester t;

   t.create("alice"_n, s2a("1000 TKN"));
   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "TKN" }), //
                        (token::currency_stats{
                              .supply     = s2a("0 TKN"),
                              .max_supply = s2a("1000 TKN"),
                              .issuer     = "alice"_n,
                        }));
   t.create("alice"_n, s2a("100 TKN"), "token with symbol already exists");
})

TEST_CASE(create_max_supply, [] {
   token_tester t;

   t.create("alice"_n, s2a("4611686018427387903 TKN"));
   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "TKN" }), //
                        (token::currency_stats{
                              .supply     = s2a("0 TKN"),
                              .max_supply = s2a("4611686018427387903 TKN"),
                              .issuer     = "alice"_n,
                        }));

   auto too_big = s2a("4611686018427387903 NKT");
   ++too_big.amount;
   t.create("alice"_n, too_big, "invalid supply");
})

TEST_CASE(precision_too_high, [] {
   token_tester t;

   t.create("alice"_n, asset{ 1, symbol{ "TKN", 18 } });
   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "TKN" }), //
                        (token::currency_stats{
                              .supply     = s2a("0.000000000000000000 TKN"),
                              .max_supply = s2a("0.000000000000000001 TKN"),
                              .issuer     = "alice"_n,
                        }));

   // eosio.token fails to check precision. Verify this broken behavior is still present.
   t.create("alice"_n, asset{ 1, symbol{ "NKT", 50 } });
})

TEST_CASE(issue_tests, [] {
   token_tester t;

   t.create("alice"_n, s2a("1000.000 TKN"));
   t.issue("alice"_n, "alice"_n, s2a("500.000 TKN"), "hola");
   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "TKN" }), //
                        (token::currency_stats{
                              .supply     = s2a("500.000 TKN"),
                              .max_supply = s2a("1000.000 TKN"),
                              .issuer     = "alice"_n,
                        }));
   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "TKN" }), s2a("500.000 TKN"));
   t.issue("alice"_n, "alice"_n, s2a("500.001 TKN"), "hola", "quantity exceeds available supply");
   t.issue("alice"_n, "alice"_n, s2a("-1.000 TKN"), "hola", "must issue positive quantity");
   t.issue("alice"_n, "alice"_n, s2a("1.000 TKN"), "hola");
})

TEST_CASE(retire_tests, [] {
   token_tester t;

   t.create("alice"_n, s2a("1000.000 TKN"));
   t.issue("alice"_n, "alice"_n, s2a("500.000 TKN"), "hola");
   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "TKN" }), //
                        (token::currency_stats{
                              .supply     = s2a("500.000 TKN"),
                              .max_supply = s2a("1000.000 TKN"),
                              .issuer     = "alice"_n,
                        }));

   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "TKN" }), s2a("500.000 TKN"));
   t.retire("alice"_n, s2a("200.000 TKN"), "hola");

   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "TKN" }), //
                        (token::currency_stats{
                              .supply     = s2a("300.000 TKN"),
                              .max_supply = s2a("1000.000 TKN"),
                              .issuer     = "alice"_n,
                        }));
   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "TKN" }), s2a("300.000 TKN"));

   // should fail to retire more than current balance
   t.retire("alice"_n, s2a("500.000 TKN"), "hola", "overdrawn balance");

   t.transfer("alice"_n, "bob"_n, s2a("200.000 TKN"), "hola");
   // should fail to retire since tokens are not on the issuer's balance
   t.retire("alice"_n, s2a("300.000 TKN"), "hola", "overdrawn balance");
   // transfer tokens back
   t.transfer("bob"_n, "alice"_n, s2a("200.000 TKN"), "hola");

   t.retire("alice"_n, s2a("300.000 TKN"), "hola");
   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "TKN" }), //
                        (token::currency_stats{
                              .supply     = s2a("0.000 TKN"),
                              .max_supply = s2a("1000.000 TKN"),
                              .issuer     = "alice"_n,
                        }));

   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "TKN" }), s2a("0.000 TKN"));

   // trying to retire tokens with zero balance
   t.retire("alice"_n, s2a("1.000 TKN"), "hola", "overdrawn balance");
})

TEST_CASE(transfer_tests, [] {
   token_tester t;

   t.create("alice"_n, s2a("1000 CERO"));
   t.issue("alice"_n, "alice"_n, s2a("1000 CERO"), "hola");

   TESTER_REQUIRE_EQUAL(t.get_stats(symbol_code{ "CERO" }), //
                        (token::currency_stats{
                              .supply     = s2a("1000 CERO"),
                              .max_supply = s2a("1000 CERO"),
                              .issuer     = "alice"_n,
                        }));

   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "CERO" }), s2a("1000 CERO"));
   t.transfer("alice"_n, "bob"_n, s2a("300 CERO"), "hola");
   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "CERO" }), s2a("700 CERO"));
   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "bob"_n, symbol_code{ "CERO" }), s2a("300 CERO"));

   t.transfer("alice"_n, "bob"_n, s2a("701 CERO"), "hola", "overdrawn balance");
   t.transfer("alice"_n, "bob"_n, s2a("-1000 CERO"), "hola", "must transfer positive quantity");
})

TEST_CASE(open_tests, [] {
   token_tester t;

   t.create("alice"_n, s2a("1000 CERO"));

   TESTER_REQUIRE_EQUAL(t.get_account_optional("alice"_n, symbol_code("CERO")), std::nullopt);
   t.issue("alice"_n, "bob"_n, s2a("1000 CERO"), "", "tokens can only be issued to issuer account");
   t.issue("alice"_n, "alice"_n, s2a("1000 CERO"), "issue");

   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "CERO" }), s2a("1000 CERO"));
   TESTER_REQUIRE_EQUAL(t.get_account_optional("bob"_n, symbol_code("CERO")), std::nullopt);

   t.open("nonexistent"_n, symbol{ "CERO", 0 }, "alice"_n, "owner account does not exist");
   t.open("bob"_n, symbol{ "CERO", 0 }, "alice"_n);

   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "bob"_n, symbol_code{ "CERO" }), s2a("0 CERO"));
   t.transfer("alice"_n, "bob"_n, s2a("200 CERO"), "hola");
   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "bob"_n, symbol_code{ "CERO" }), s2a("200 CERO"));

   t.open("carol"_n, symbol{ "INVALID", 0 }, "alice"_n, "symbol does not exist");
   t.open("carol"_n, symbol{ "CERO", 1 }, "alice"_n, "symbol precision mismatch");
})

TEST_CASE(close_tests, [] {
   token_tester t;

   t.create("alice"_n, s2a("1000 CERO"));
   TESTER_REQUIRE_EQUAL(t.get_account_optional("alice"_n, symbol_code("CERO")), std::nullopt);

   t.issue("alice"_n, "alice"_n, s2a("1000 CERO"), "hola");
   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "CERO" }), s2a("1000 CERO"));

   t.transfer("alice"_n, "bob"_n, s2a("1000 CERO"), "hola");
   TESTER_REQUIRE_EQUAL(token::get_balance("eosio.token"_n, "alice"_n, symbol_code{ "CERO" }), s2a("0 CERO"));

   t.close("alice"_n, symbol{ "CERO", 0 });
   TESTER_REQUIRE_EQUAL(t.get_account_optional("alice"_n, symbol_code("CERO")), std::nullopt);
})

TEST_ENTRY
