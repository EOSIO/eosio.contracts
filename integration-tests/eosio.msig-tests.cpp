#include <eosio.bios/eosio.bios.hpp>
#include <eosio.msig/eosio.msig.hpp>
#include <eosio.token/eosio.token.hpp>
#include <eosio/tester.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using namespace eosio;
using eosiobios::bios;

namespace eosio {

inline bool operator!=(const token::currency_stats& a, const token::currency_stats& b) {
   return a.supply != b.supply || a.max_supply != b.max_supply || a.issuer != b.issuer;
}

} // namespace eosio

struct approve_args {
   name             proposer      = {};
   name             proposal_name = {};
   permission_level level         = {};

   EOSLIB_SERIALIZE(approve_args, (proposer)(proposal_name)(level))
};

struct msig_tester {
   test_chain chain;

   msig_tester() {
      chain.set_code("eosio"_n, "contracts/eosio.bios/eosio.bios.wasm");
      chain.create_code_account("eosio.msig"_n, true);
      chain.create_account("eosio.stake"_n);
      chain.create_account("eosio.ram"_n);
      chain.create_account("eosio.ramfee"_n);
      chain.create_account("alice"_n);
      chain.create_account("bob"_n);
      chain.create_account("carol"_n);
      chain.set_code("eosio.msig"_n, "contracts/eosio.msig/eosio.msig.wasm");
   }

   chain_types::transaction_trace propose(name proposer, name proposal_name, std::vector<permission_level> requested,
                                          transaction trx, const char* expected_except = nullptr) {
      return chain.transact({ multisig::propose_action{ "eosio.msig"_n, { proposer, "active"_n } }.to_action(
                                  proposer, proposal_name, std::move(requested), std::move(trx)) },
                            expected_except);
   }

   chain_types::transaction_trace approve(name proposer, name proposal_name, permission_level level,
                                          const char* expected_except = nullptr) {
      return chain.transact({ { level, "eosio.msig"_n, "approve"_n, approve_args{ proposer, proposal_name, level } } },
                            expected_except);
   }

   chain_types::transaction_trace exec(name proposer, name proposal_name, name executer,
                                       const char* expected_except = nullptr) {
      return chain.transact({ multisig::exec_action{ "eosio.msig"_n, { executer, "active"_n } }.to_action(
                                  proposer, proposal_name, executer) },
                            expected_except);
   }

}; // msig_tester

BOOST_FIXTURE_TEST_CASE(propose_approve_execute, msig_tester) {
   propose("alice"_n, "first"_n, { { "alice"_n, "active"_n } },
           chain.make_transaction(
              { bios::reqauth_action{ "eosio"_n, { "alice"_n, "active"_n } }.to_action("alice"_n) }));

   // fail to execute before approval
   exec("alice"_n, "first"_n, "alice"_n, "transaction authorization failed");

   // approve and execute
   approve("alice"_n, "first"_n, { "alice"_n, "active"_n });
   BOOST_TEST(!chain.exec_deferred());
   exec("alice"_n, "first"_n, "alice"_n);

   auto receipt = chain.exec_deferred();
   BOOST_TEST(!chain.exec_deferred());
   BOOST_TEST(receipt.has_value());
   expect(*receipt);
   BOOST_TEST(std::get<0>(*receipt).action_traces.size() == 1);
} // propose_approve_execute
