/**
 * This contract defines the TIP-5 Single Token Interface.
 * 
 * For a full developer walkthrough, see the README.md here: 
 * 
 * @author Craig Branscom
 */

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/singleton.hpp>

using namespace eosio;
using namespace std;

class registry : public contract {

    public:
        registry(name self, name code, datastream<const char*> ds);

        ~registry();

        //NOTE: Developers edit here
        string const TOKEN_NAME = "Telos Test Token";
        asset const INITIAL_MAX_SUPPLY = asset(int64_t(10000), symbol("TEST", 2));
        asset const INITIAL_SUPPLY = asset(int64_t(0), symbol("TEST", 2));

        // ABI Actions
        [[eosio::action]] void mint(name recipient, asset tokens);

        [[eosio::action]] void transfer(name sender, name recipient, asset tokens);

        [[eosio::action]] void allot(name sender, name recipient, asset tokens);

        [[eosio::action]] void unallot(name sender, name recipient, asset tokens);

        [[eosio::action]] void claimallot(name sender, name recipient, asset tokens);

        [[eosio::action]] void createwallet(name recipient);

        [[eosio::action]] void deletewallet(name owner);
        
        struct [[eosio::table]] tokenconfig {
            name publisher;
            string token_name;
            asset max_supply;
            asset supply;

            uint64_t primary_key() const { return publisher.value; }
            EOSLIB_SERIALIZE(tokenconfig, (publisher)(token_name)(max_supply)(supply))
        };
        
        struct [[eosio::table]] balance {
            name owner;
            asset tokens;

            uint64_t primary_key() const { return owner.value; }
            EOSLIB_SERIALIZE(balance, (owner)(tokens))
        };

        struct [[eosio::table]] allotment {
            name recipient;
            name sender;
            asset tokens;

            uint64_t primary_key() const { return recipient.value; }
            uint64_t by_sender() const { return sender.value; }
            EOSLIB_SERIALIZE(allotment, (recipient)(sender)(tokens))
        };

        typedef multi_index<name("balances"), balance> balances_table;

        typedef multi_index<name("allotments"), allotment, 
            indexed_by<name("sender"), const_mem_fun<allotment, uint64_t, &allotment::by_sender>>> allotments_table;

        typedef eosio::singleton<name("tokenconfig"), tokenconfig> config_singleton;
        config_singleton _config;
        tokenconfig config;

        //NOTE: Helper Functions
        void add_balance(name recipient, asset tokens, name payer);

        void sub_balance(name owner, asset tokens);

        void add_allot(name sender, name recipient, asset tokens, name payer);

        void sub_allot(name sender, name recipient, asset tokens);
};