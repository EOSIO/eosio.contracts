#include <boost/test/unit_test.hpp>
#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>

#include <eosio/chain/wast_to_wasm.hpp>
#include <Runtime/Runtime.h>

#include <fc/variant_object.hpp>

#include <contracts.hpp>
#include "test_symbol.hpp"

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;
using namespace std;

using mvo = fc::mutable_variant_object;

class eosio_trail_tester : public tester
{
  public:
	abi_serializer abi_ser;
	abi_serializer token_abi_ser;

	eosio_trail_tester()
	{
		produce_blocks( 2 );

		create_accounts({N(craig), N(ed), N(peter)});
		produce_blocks( 2 );

		create_accounts({N(eosio.token), N(eosio.ram), N(eosio.ramfee), N(eosio.stake),
						 N(eosio.bpay), N(eosio.vpay), N(eosio.saving), N(eosio.names)});
		produce_blocks( 2 );

		set_code(N(eosio.token), contracts::token_wasm());
		create(N(eosio), asset(10000000000));
		issue(N(eosio), N(eosio), asset(300000000), "Initial amount!");
		set_abi(N(eosio.token), contracts::token_abi().data());
		{
			const auto &accnt = control->db().get<account_object, by_name>(N(eosio.token));
			abi_def abi;
			BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
			token_abi_ser.set_abi(abi, abi_serializer_max_time);
		}

		produce_blocks();
		deploy_contract();
		produce_blocks( 2 );
	}

	void deploy_contract() {
      set_code( N(eosio.trail), contracts::trail_wasm() );
      set_abi( N(eosio.trail), contracts::trail_abi().data() );

      {
         const auto& accnt = control->db().get<account_object,by_name>( N(eosio.trail) );
         abi_def abi;
         BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
         abi_ser.set_abi(abi, abi_serializer_max_time);
      }
   }

	action_result create(account_name issuer,
						 asset maximum_supply)
	{

		return push_action(N(eosio.token), N(create), mvo()("issuer", issuer)("maximum_supply", maximum_supply));
	}

	action_result issue(account_name issuer, account_name to, asset quantity, string memo)
	{
		return push_action(issuer, N(issue), mvo()("to", to)("quantity", quantity)("memo", memo));
	}

	action_result transfer(account_name from,
						   account_name to,
						   asset quantity,
						   string memo)
	{
		return push_action(from, N(transfer), mvo()("from", from)("to", to)("quantity", quantity)("memo", memo));
	}

	action_result push_action(const account_name &signer, const action_name &name, const variant_object &data)
	{
		string action_type_name = abi_ser.get_action_type(name);

		action act;
		act.account = N(eosio.token);
		act.name = name;
		act.data = abi_ser.variant_to_binary(action_type_name, data, abi_serializer_max_time);

		return base_tester::push_action(std::move(act), uint64_t(signer));
	}

	fc::variant get_account(account_name acc, const string &symbolname)
	{
		auto symb = eosio::chain::symbol::from_string(symbolname);
		auto symbol_code = symb.to_symbol_code().value;
		vector<char> data = get_row_by_account(N(eosio.token), acc, N(accounts), symbol_code);
		return data.empty() ? fc::variant() : abi_ser.binary_to_variant("account", data, abi_serializer_max_time);
	}

	transaction_trace_ptr create_account_with_resources( account_name a, account_name creator, asset ramfunds, bool multisig,
                                                        asset net = core_sym::from_string("10.0000"), asset cpu = core_sym::from_string("10.0000") ) {
      signed_transaction trx;
      set_transaction_headers(trx);

      authority owner_auth;
      if (multisig) {
         // multisig between account's owner key and creators active permission
         owner_auth = authority(2, {key_weight{get_public_key( a, "owner" ), 1}}, {permission_level_weight{{creator, config::active_name}, 1}});
      } else {
         owner_auth =  authority( get_public_key( a, "owner" ) );
      }

      trx.actions.emplace_back( vector<permission_level>{{creator,config::active_name}},
                                newaccount{
                                   .creator  = creator,
                                   .name     = a,
                                   .owner    = owner_auth,
                                   .active   = authority( get_public_key( a, "active" ) )
                                });

      trx.actions.emplace_back( get_action( config::system_account_name, N(buyram), vector<permission_level>{{creator,config::active_name}},
                                            mvo()
                                            ("payer", creator)
                                            ("receiver", a)
                                            ("quant", ramfunds) )
                              );

      trx.actions.emplace_back( get_action( config::system_account_name, N(delegatebw), vector<permission_level>{{creator,config::active_name}},
                                            mvo()
                                            ("from", creator)
                                            ("receiver", a)
                                            ("stake_net_quantity", net )
                                            ("stake_cpu_quantity", cpu )
                                            ("transfer", 0 )
                                          )
                                );

      set_transaction_headers(trx);
      trx.sign( get_private_key( creator, "active" ), control->get_chain_id()  );
      return push_transaction( trx );
   }

   //TODO: Create functions from eosio.trial contract
};