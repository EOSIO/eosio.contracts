/**
 * 
 * 
 * @author Craig Branscom
 * @copyright defined in telos/LICENSE.txt
 */

#include <trail.voting.hpp>
#include <trail.tokens.hpp>

#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>

using namespace std;
using namespace eosio;

class [[eosio::contract("telos.tfvt")]] tfvt : public contract {

public:

    tfvt(name self, name code, datastream<const char*> ds);

    ~tfvt();
	#pragma region native

	struct permission_level_weight {
      permission_level  permission;
      uint16_t          weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( permission_level_weight, (permission)(weight) )
   };

   struct key_weight {
      eosio::public_key  key;
      uint16_t           weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( key_weight, (key)(weight) )
   };

   struct wait_weight {
      uint32_t           wait_sec;
      uint16_t           weight;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( wait_weight, (wait_sec)(weight) )
   };

   struct authority {
      uint32_t                              threshold = 0;
      std::vector<key_weight>               keys;
      std::vector<permission_level_weight>  accounts;
      std::vector<wait_weight>              waits;

      // explicit serialization macro is not necessary, used here only to improve compilation time
      EOSLIB_SERIALIZE( authority, (threshold)(keys)(accounts)(waits) )
   };

	#pragma endregion native

    #pragma region Constants

	enum ISSUE_STATE {
		FAIL = 2,
		COUNT = 0,
		TIE = 3,
		PASS = 1
	};

    asset const INITIAL_TFVT_MAX_SUPPLY = asset(500, symbol("TFVT", 0)); //TODO: finalize initial supply
    
    asset const INITIAL_TFBOARD_MAX_SUPPLY = asset(13, symbol("TFBOARD", 0)); //TODO: finalize initial supply
    
    token_settings const INITIAL_TFVT_SETTINGS = token_settings { //TODO: finalize initial tfvt settings
        false, //is_destructible
        false, //is_proxyable
        false, //is_burnable
        false, //is_seizable
        true, //is_max_mutable
        false, //is_transferable
        true, //is_recastable
        false, //is_initialized
        uint32_t(500), //counterbal_decay_rate (not applicable since non-transferable)
        true, //lock_after_initialize
    };

    token_settings const INITIAL_TFBOARD_SETTINGS = token_settings { //TODO: finalize initial tfboard settings
        false, //is_destructible
        false, //is_proxyable
        true, //is_burnable
        true, //is_seizable
        true, //is_max_mutable
        false, //is_transferable
        false, //is_recastable
        false, //is_initialized
        uint32_t(500), //counterbal_decay_rate (not applicable since non-transferable)
        true, //lock_after_initialize
    };

    #pragma endregion Constants

    struct [[eosio::table]] board_nominee {
        name nominee;
        
        uint64_t primary_key() const { return nominee.value; }
        EOSLIB_SERIALIZE(board_nominee, (nominee))
    };

    struct [[eosio::table]] board_member {
        name member;

        uint64_t primary_key() const { return member.value; }
        EOSLIB_SERIALIZE(board_member, (member))
    };

    struct [[eosio::table]] config {
        name publisher;
        uint8_t max_board_seats = 12; //NOTE: adjustable by board members
        uint8_t open_seats = 12;
		uint64_t open_election_id = 0;
		uint32_t holder_quorum_divisor = 5;
		uint32_t board_quorum_divisor = 2;
		uint32_t issue_duration = 2000000;
		uint32_t start_delay = 1200;
		uint32_t leaderboard_duration = 2000000;
		uint32_t election_frequency = 14515200;
		uint32_t last_board_election_time;

        uint64_t primary_key() const { return publisher.value; }
        EOSLIB_SERIALIZE(config, (publisher)(max_board_seats)(open_seats)(open_election_id)(holder_quorum_divisor)
			(board_quorum_divisor)(issue_duration)(start_delay)(leaderboard_duration)(election_frequency)(last_board_election_time))
    };

	struct [[eosio::table]] issue {
		name proposer;
		name issue_name;
		uint64_t ballot_id;
		eosio::transaction transaction;

		uint64_t primary_key() const { return proposer.value; }
		EOSLIB_SERIALIZE(issue, (proposer)(issue_name)(ballot_id)(transaction))
	};

	//TODO: create multisig compatible packed_trx table for proposals.
    
    typedef multi_index<name("nominees"), board_nominee> nominees_table;

    typedef multi_index<name("boardmembers"), board_member> members_table;

	typedef multi_index<name("issues"), issue> issues_table;

    typedef singleton<name("config"), config> config_table;
	config_table configs;
  	config _config;


    [[eosio::action]] //NOTE: sends inline actions to register and initialize TFVT token registry
    void inittfvt(string initial_info_link);

    [[eosio::action]] //NOTE: sends inline actions to register and initialize TFBOARD token registry
    void inittfboard(string initial_info_link);

    [[eosio::action]]
    void setconfig(name publisher, config new_config);

    [[eosio::action]]
    void nominate(name nominee, name nominator);

    [[eosio::action]]
    void makeissue(ignore<name> holder,
		ignore<string> info_url,
		ignore<name> issue_name,
		ignore<transaction> transaction);

    [[eosio::action]]
    void closeissue(name holder, name proposer);

    [[eosio::action]]
    void makeelection(name holder, string info_url);

    //[[eosio::action]]
    //void addallcands(name holder, vector<candidate> new_cands);

	[[eosio::action]]
	void addcand(name nominee, string info_link);

	[[eosio::action]]
	void removecand(name candidate);

    [[eosio::action]]
    void endelection(name holder);

	// [[eosio::action]]
	// void setboard(vector<name> members);

	[[eosio::action]]
	void removemember(name member_to_remove);

	//TODO: board member multisig kick action
			//Starts run off leaderboard at start/end

	//TODO: the ability to create and manage new positions

    #pragma region Helper_Functions
	config get_default_config();

    void add_to_tfboard(name nominee);

    void rmv_from_tfboard(name member);

    void addseats(name member, uint8_t num_seats);

    bool is_board_member(name user);

    bool is_nominee(name user);

    bool is_tfvt_holder(name user);

    bool is_tfboard_holder(name user);

	bool is_term_expired();

	void remove_and_seize_all();

	void remove_and_seize(name member);

	void set_permissions(vector<permission_level_weight> perms);

	uint8_t get_occupied_seats();

	vector<permission_level_weight> perms_from_members();

    #pragma endregion Helper_Functions

};
