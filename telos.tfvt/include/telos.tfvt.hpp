/**
 * 
 * 
 * @author Craig Branscom
 * @copyright defined in telos/LICENSE.txt
 */

#include "../../eosio.trail/include/trail.voting.hpp"
#include "../../eosio.trail/include/trail.tokens.hpp"

#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;

class [[eosio::contract("telos.tfvt")]] tfvt : public contract {

public:

    tfvt(name self, name code, datastream<const char*> ds);

    ~tfvt();

    #pragma region Constants

    asset const INITIAL_TFVT_MAX_SUPPLY = asset(500, symbol("TFVT", 0)); //TODO: finalize initial supply
    
    asset const INITIAL_TFBOARD_MAX_SUPPLY = asset(12, symbol("TFBOARD", 0)); //TODO: finalize initial supply
    
    token_settings const INITIAL_TFVT_SETTINGS = token_settings{ //TODO: finalize initial tfvt settings
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

    token_settings const INITIAL_TFBOARD_SETTINGS = token_settings{ //TODO: finalize initial tfboard settings
        false, //is_destructible
        false, //is_proxyable
        false, //is_burnable
        false, //is_seizable
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
        uint8_t open_seats = 0;

        uint64_t primary_key() const { return publisher.value; }
        EOSLIB_SERIALIZE(config, (publisher)(max_board_seats)(open_seats))
    };

    
    typedef multi_index<name("nominees"), board_nominee> nominees_table;

    typedef multi_index<name("boardmembers"), board_member> members_table;

    typedef singleton<name("configs"), config> config_table;


    [[eosio::action]] //NOTE: sends inline actions to register and initialize TFVT token registry
    void inittfvt(string initial_info_link);

    [[eosio::action]] //NOTE: sends inline actions to register and initialize TFBOARD token registry
    void inittfboard(string initial_info_link);

    [[eosio::action]]
    void setconfig(name publisher, config new_configs);

    [[eosio::action]]
    void nominate(name nominee, name nominator);

    [[eosio::action]]
    void makeissue(name holder, uint32_t begin_time, uint32_t end_time, string info_url);

    [[eosio::action]]
    void closeissue(name holder, uint64_t ballot_id);

    [[eosio::action]]
    void makeelection(name holder, uint32_t begin_time, uint32_t end_time, string info_url);

    [[eosio::action]]
    void addallcands(name holder, uint64_t ballot_id, vector<candidate> new_cands);

    [[eosio::action]]
    void endelection(name holder, uint64_t ballot_id);



    #pragma region Helper_Functions

    void add_to_tfboard(name nominee);

    void rmv_from_tfboard(name member);

    void addseats(name member, uint8_t num_seats);

    bool is_board_member(name user);

    bool is_nominee(name user);

    bool is_tfvt_holder(name user);

    bool is_tfboard_holder(name user);

    #pragma endregion Helper_Functions

};
