#include "../include/telos.tfvt.hpp"
#include <eosiolib/symbol.hpp>
//#include <eosiolib/print.hpp>

tfvt::tfvt(name self, name code, datastream<const char*> ds) : contract(self, code, ds) {}

tfvt::~tfvt() {}


#pragma region Actions

void tfvt::inittfvt(string initial_info_link) {
    require_auth(_self);
    
    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "regtoken"_n, make_tuple(
		INITIAL_TFVT_MAX_SUPPLY, //max_supply
		_self, //publisher
		initial_info_link //info_url
	)).send();

    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "initsettings"_n, make_tuple(
		_self, //publisher
		INITIAL_TFVT_MAX_SUPPLY.symbol, //token_symbol
		INITIAL_TFVT_SETTINGS //new_settings
	)).send();

    print("\nTFVT Registration and Initialization Actions Sent...");
}

void tfvt::inittfboard(string initial_info_link) {
    require_auth(_self);
    
    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "regtoken"_n, make_tuple(
		INITIAL_TFBOARD_MAX_SUPPLY, //max_supply
		_self, //publisher
		initial_info_link //info_url
	)).send();

    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "initsettings"_n, make_tuple(
		_self, //publisher
		INITIAL_TFBOARD_MAX_SUPPLY.symbol, //token_symbol
		INITIAL_TFBOARD_SETTINGS //new_settings
	)).send();

    print("\nTFBOARD Registration and Initialization Actions Sent...");
}

void tfvt::setconfig(name member, config new_configs) {
    require_auth(member);
    eosio_assert(new_configs.max_board_seats >= new_configs.open_seats, "can't have more open seats than max seats");
    //eosio_assert(is_board_member(member), "member is not on the board"); //NOTE: restrict to board members?

    config_table configs(_self, _self.value);
    configs.set(new_configs, _self);
}

void tfvt::nominate(name nominee, name nominator) {
    require_auth(nominator);
    eosio_assert(!is_board_member(nominee), "nominee is already a board member");

    nominees_table noms(_self, _self.value);
    auto n = noms.find(nominee.value);
    eosio_assert(n == noms.end(), "nominee has already been nominated");

    noms.emplace(get_self(), [&](auto& m) {
        m.nominee = nominee;
    });
}

void tfvt::makeissue(name holder, uint32_t begin_time, uint32_t end_time, string info_url) {
    require_auth(holder);

    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "regballot"_n, make_tuple(
		_self,
		uint8_t(0), //NOTE: makes a proposal on Trail
		symbol("TFVT", 0),
		begin_time,
        end_time,
        info_url
	)).send();
}

void tfvt::closeissue(name holder, uint64_t ballot_id) {
    require_auth(holder);

    uint8_t status = 1;

    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "closeballot"_n, make_tuple(
		_self,
		ballot_id,
		status
	)).send();
}

void tfvt::makeelection(name holder, uint32_t begin_time, uint32_t end_time, string info_url) {
    require_auth(holder);
    eosio_assert(is_tfvt_holder(holder) || is_tfboard_holder(holder), "caller must be a TFVT or TFBOARD holder");
    
    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "regballot"_n, make_tuple(
		_self,
		uint8_t(2), //NOTE: makes a leaderboard on Trail
		symbol("TFVT", 0),
		begin_time,
        end_time,
        info_url
	)).send();

}

void tfvt::addallcands(name holder, uint64_t ballot_id, vector<candidate> new_cands) {
    require_auth(holder);
    eosio_assert(is_tfvt_holder(holder) || is_tfboard_holder(holder), "caller must be a TFVT or TFBOARD holder");

    for (candidate c : new_cands) {
        eosio_assert(is_nominee(c.member), "candidates must be a nonimee");
    }

    //NOTE: requires {_self}@eosio.code to send
    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "setallcands"_n, make_tuple(
		_self, //publisher
		ballot_id, //ballot_id
		new_cands //new_candidates
	)).send();

}

void tfvt::endelection(name holder, uint64_t ballot_id) {
    require_auth(holder);
    eosio_assert(is_tfvt_holder(holder) || is_tfboard_holder(holder), "caller is not a tfvt or tfboard token holder");

    uint8_t status = 1;

    ballots_table ballots(name("eosio.trail"), name("eosio.trail").value);
    auto bal = ballots.get(ballot_id);
    
    leaderboards_table leaderboards(name("eosio.trail"), name("eosio.trail").value);
    auto board = leaderboards.get(bal.reference_id);

    auto board_candidates = board.candidates;
    //TODO: does >= resolve ties?
    sort(board_candidates.begin(), board_candidates.end(), [](const auto &c1, const auto &c2) { return c1.votes >= c2.votes; });

    //add first n candidates after sorting by votes, where n is available seats on leaderboard
    for (uint8_t n = 0; n < board.available_seats; n++) {
        add_to_tfboard(board.candidates[n].member);
    }
    
    //TODO: send setallstats() inline to trail

    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "closeballot"_n, make_tuple(
		_self,
		ballot_id,
		status
	)).send();
}

#pragma endregion Actions


#pragma region Helper_Functions

void tfvt::add_to_tfboard(name nominee) {
    nominees_table noms(_self, _self.value);
    auto n = noms.find(nominee.value);
    eosio_assert(n != noms.end(), "nominee doesn't exist in table");

    members_table mems(_self, _self.value);
    auto m = mems.find(nominee.value);
    eosio_assert(m == mems.end(), "nominee is already a board member");

    noms.erase(n); //NOTE remove from nominee table

    mems.emplace(get_self(), [&](auto& m) { //NOTE: emplace in boardmembers table
        m.member = nominee;
    });
}

void tfvt::rmv_from_tfboard(name member) {
    members_table mems(_self, _self.value);
    auto m = mems.find(member.value);
    eosio_assert(m != mems.end(), "member is not on the board");

    mems.erase(m);
}

void tfvt::addseats(name member, uint8_t num_seats) {
    require_auth(member);
    eosio_assert(is_board_member(member), "only board members can add seats");

    config_table configs(_self, _self.value);
    auto c = configs.get();

    config configs_struct = config{
        _self, //publisher
        c.max_board_seats += num_seats, //max_board_seats
        c.open_seats += num_seats //open_seats
    };

    configs.set(configs_struct, _self);
}

bool tfvt::is_board_member(name user) {
    members_table mems(_self, _self.value);
    auto m = mems.find(user.value);
    
    if (m != mems.end()) {
        return true;
    }

    return false;
}

bool tfvt::is_nominee(name user) {
    nominees_table noms(_self, _self.value);
    auto n = noms.find(user.value);

    if (n != noms.end()) {
        return true;
    }

    return false;
}

bool tfvt::is_tfvt_holder(name user) {
    balances_table balances(name("eosio.trail"), symbol("TFVT", 0).code().raw());
    auto b = balances.find(user.value);

    if (b != balances.end()) {
        return true;
    }

    return false;
}

bool tfvt::is_tfboard_holder(name user) {
    balances_table balances(name("eosio.trail"), symbol("TFBOARD", 0).code().raw());
    auto b = balances.find(user.value);

    if (b != balances.end()) {
        return true;
    }

    return false;
}

#pragma endregion Helper_Functions

EOSIO_DISPATCH(tfvt, (inittfvt)(inittfboard)(setconfig)(nominate)(makeissue)(closeissue)(makeelection)(endelection))
