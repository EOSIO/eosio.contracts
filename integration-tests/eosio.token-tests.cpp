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

   // eosio.token fails to check precision. Verify this broken behavior is still broken.
   t.create("alice"_n, asset{ 1, symbol{ "NKT", 50 } });
})

TEST_ENTRY
