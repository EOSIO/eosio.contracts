#include <telos.tfvt.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/print.hpp>

telfound::telfound(name self, name code, datastream<const char*> ds) : contract(self, code, ds) {}

telfound::~telfound() {}

void setconfig(name member, uint8_t new_max_seats, uint8_t new_open_seats) {
    require_auth(publisher);
    eosio_assert(new_max_seats >= new_open_seats, "can't have more open seats than max seats");
    //eosio_assert(is_board_member(member), "member is not on the board"); //NOTE: restrict to board members?

    config_table configs(_self, _self.value);
    auto c = configs.find(_self.value);

    config configs_struct = config{
        _self, //publisher
        uint8_t(new_max_seats), //max_board_seats
        uint8_t(new_open_seats), //open_seats
    };

    configs.set(configs_struct, _self);
}

void telfound::nominate(name nominee, name nominator) {
    require_auth(nominator);
    eosio_assert(!is_nominee(nominee), "nominee has already been nominated");
    eosio_assert(!is_board_member(nominee), "nominee is already a board member");

    noms.emplace(get_self(), [&](auto& m) {
        m.nominee = nominee;
    });
}

void telfound::makeissue(name holder, uint32_t begin_time, uint32_t end_time, string info_url) {
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

void telfound::closeissue(name holder, uint64_t ballot_id) {
    require_auth(holder);

    uint8_t status = 1;

    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "closeballot"_n, make_tuple(
		_self,
		ballot_id,
		status
	)).send();
}

void telfound::makelboard(name holder, uint32_t begin_time, uint32_t end_time, string info_url) {
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

void telfound::closelboard(name holder, uint64_t ballot_id) {
    require_auth(holder);

    uint8_t status = 1;

    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "closeballot"_n, make_tuple(
		_self,
		ballot_id,
		status
	)).send();
}


#pragma region Helper_Functions

void telfound::add_to_tfboard(name nominee) {
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

void telfound::rmv_from_tfboard(name member) {
    members_table mems(_self, _self.value);
    auto m = mems.find(nominee.value);
    eosio_assert(m != mems.end(), "member is not on the board");

    mems.erase(m);
}

void telfound::addseats(name member, uint8_t num_seats) {
    require_auth(member);
    eosio_assert(is_board_member(member), "only board members can add seats");

    config_table configs(_self, _self.value);
    auto c = configs.find(_self.value);
    eosio_assert(c != configs.end(), "config doesn't exist");
    auto conf = *c;

    configs.modify(c, same_payer, [&](auto& l) {
        l.max_board_seats += num_seats;
        l.open_seats += num_seats;
    });
}

bool telfound::is_board_member(name user) {
    members_table mems(_self, _self.value);
    auto m = mems.find(user.value);
    
    if (m != mems.end()) {
        return true;
    }

    return false;
}

bool telfound::is_nominee(name user) {
    nominees_table noms(_self, _self.value);
    auto n = noms.find(user.value);

    if (n != noms.end()) {
        return true;
    }

    return false;
}

bool telfound::is_tfvt_holder(name user) {
    balances_table balances(name("eosio.trail"), symbol("TFVT", 0).code().raw());
    auto b = balances.find(user.value);

    if (b != balances.end()) {
        return true;
    }

    return false;
}

bool telfound::is_tfboard_holder(name user) {
    balances_table balances(name("eosio.trail"), symbol("TFBOARD", 0).code().raw());
    auto b = balances.find(user.value);

    if (b != balances.end()) {
        return true;
    }

    return false;
}

#pragma endregion Helper_Functions
