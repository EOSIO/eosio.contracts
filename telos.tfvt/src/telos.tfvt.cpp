#include <telos.tfvt.hpp>
#include <eosiolib/symbol.hpp>
//#include <eosiolib/print.hpp>

tfvt::tfvt(name self, name code, datastream<const char*> ds)
: contract(self, code, ds), configs(get_self(), get_self().value) {
	_config = configs.exists() ? configs.get() : get_default_config();
}

tfvt::~tfvt() {
	if(configs.exists()) configs.set(_config, get_self());
}

tfvt::config tfvt::get_default_config() {
	auto c = config {
		get_self(),			//publisher
		uint8_t(12),		//max seats
		uint8_t(0)			//open seats
		uint32_t(5) 		//holder_quorum_divisor
		uint32_t(2) 		//board_quorum_divisor
		uint32_t(2000000)	//issue_duration
		uint32_t(1200)  	//start_delay
		uint32_t(2000000)   //leaderboard_duration
		uint32_t(14515200) 	//election_frequency
	};
	configs.set(c, get_self());
	return c;
}

#pragma region Actions

void tfvt::inittfvt(string initial_info_link) {
    require_auth(_self);
    
    action(permission_level{_self, name("active")}, name("eosio.trail"), name("regtoken"), make_tuple(
		INITIAL_TFVT_MAX_SUPPLY, //max_supply
		_self, //publisher
		initial_info_link //info_url
	)).send();

    action(permission_level{_self, name("active")}, name("eosio.trail"), name("initsettings"), make_tuple(
		_self, //publisher
		INITIAL_TFVT_MAX_SUPPLY.symbol, //token_symbol
		INITIAL_TFVT_SETTINGS //new_settings
	)).send();

    print("\nTFVT Registration and Initialization Actions Sent...");
}

void tfvt::inittfboard(string initial_info_link) {
    require_auth(_self);
    
    action(permission_level{_self, name("active")}, name("eosio.trail"), name("regtoken"), make_tuple(
		INITIAL_TFBOARD_MAX_SUPPLY, //max_supply
		_self, 						//publisher
		initial_info_link 			//info_url
	)).send();

    action(permission_level{_self, name("active")}, name("eosio.trail"), name("initsettings"), make_tuple(
		_self, //publisher
		INITIAL_TFBOARD_MAX_SUPPLY.symbol, //token_symbol
		INITIAL_TFBOARD_SETTINGS //new_settings
	)).send();

    print("\nTFBOARD Registration and Initialization Actions Sent...");
}

void tfvt::setconfig(name member, config new_config) {
    require_auth("tf"_n);
    eosio_assert(new_config.max_board_seats >= new_config.open_seats, "can't have more open seats than max seats");
	eosio_assert(new_config.holder_quorum_divisor > 0, "holder_quorum_divisor must be a non-zero number");
	eosio_assert(new_config.board_quorum_divisor > 0, "board_quorum_divisor must be a non-zero number");
	eosio_assert(new_config.issue_duration > 0, "issue_duration must be a non-zero number");
	eosio_assert(new_config.start_delay > 0, "start_delay must be a non-zero number");

	new_config.publisher = _config.publisher;
	new_config.open_seats = _config.open_seats;
    config_table configs(_self, _self.value);
    configs.set(new_config, _self);
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

void tfvt::makeissue(ignore<name> holder, 
		ignore<string> info_url,
		ignore<name> issue_name,
		ignore<transaction> transaction) {

	name 	_holder;
	name	_issue_name;
	string _info_url;
	eosio::transaction _trx;

	_ds >> _holder >> _info_url >> _issue_name >> _trx;

    require_auth(_holder);

	eosio_assert(is_holder(_holder) || is_board_member(_holder), "proposer must be TFVT holder");

	ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
	uint64_t next_ballot_id = ballots.available_primary_key();
	uint32_t begin_time = now() + _config.start_delay;
	uint32_t end_time = begin_time + _config.issue_duration;

    action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "regballot"_n, make_tuple(
		get_self(),
		uint8_t(0), 			//NOTE: makes a proposal on Trail
		symbol("TFBOARD", 0),
		begin_time,
        end_time,
        _info_url
	)).send();

	issues_table issues(get_self(), get_self().value);
	issues.emplace(_holder, [&](auto& issue) {
		issue.id = next_ballot_id;
		issue.transaction = _trx;
		issue.issue_name = _issue_name;
	});
}

void tfvt::closeissue(name holder, uint64_t ballot_id) {
    require_auth(holder);
    uint8_t status = 1;
	//TODO: check quorum values
	//TODO: tiebreaker logic here
	//TODO: if issue passes send pack_trx to msig then erase trx
			//if issue fails then erase trx

	registries_table registries("eosio.trail"_n, "eosio.trail"_n.value);
	auto r = registries.get(symbol("TFVT", 0).code().raw(), "TFVT registry not found, this shouldn't happen");
	uint32_t total_voters = r.settings.total_voters;

	ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
	auto b = ballots.get(ballot_id, "ballot does not exist");

	proposals_table proposals("eosio.trail"_n, "eosio.trail"_n.value);
	auto p = proposals.get(b.reference_id, "proposal not found");
	
	uint32_t unique_voters = p.unique_voters;

	uint32_t quorum_threshold = total_voters / _config.board_quorum_divisor;

	//IF: unique_voters > quorum_t
		//then count
	//ELSE: fail

	//if count
		//IF: yes votes simple majority
			//then pass
		//ELIF: tie
			//then tie
		//ELSE:
			//then fail


	//IF: pass
		//then send inline to create msig
			//erase issue

	//IF: fail
		//then erase issue

	//IF: tie
		//then send inline for new TFVT ballot
		//then update issue with new ballot_id


	issues_table issues(get_self(), get_self().value);
	auto issue = issues.get(ballot_id, "issue not found");

	members_table members(get_self(), get_self().value);

	std::vector<permission_level> requested;

	auto itr = members.begin();

    while (itr != members.end()) {
		print("adding permission_level: ", name{itr->member});
		requested.emplace_back(permission_level(itr->member, "active"_n));
		itr++;
    }

	print("sending inline");
	action(permission_level{_self, name("active")}, name("eosio.msig"), name("propose"), make_tuple(
		get_self(),
		issue.issue_name,
		requested,
		issue.transaction
	)).send();

    action(permission_level{_self, "active"_n}, "eosio.trail"_n, "closeballot"_n, make_tuple(
		_self,
		ballot_id,
		status
	)).send();
}

void tfvt::makeelection(name holder, string info_url) {
    require_auth(holder);
    eosio_assert(is_tfvt_holder(holder) || is_tfboard_holder(holder), "caller must be a TFVT or TFBOARD holder");
	eosio_assert(now() - _config.last_board_election_time.slot > _config.election_frequency, "it isn't time for the next election");


	uint32_t begin_time = now() + _config.start_delay;
	uint32_t end_time = begin_time + _config.leaderboard_duration;

    action(permission_level{_self, name("active")}, name("eosio.trail"), name("regballot"), make_tuple(
		_self,
		uint8_t(2), 			//NOTE: makes a leaderboard on Trail
		symbol("TFVT", 0),
		begin_time,
        end_time,
        info_url
	)).send();
}

void tfvt::setboard(vector<name> members) {
	require_auth(get_self());

	members_table mems(get_self(), get_self().value);
	std::vector<permission_level_weight> board_perms;
	for(name member : members) {
		print("emplace board member: ", name{member});
		mems.emplace(get_self(), [&](auto& m) {
			m.member = member;
		});

		board_perms.emplace_back(
			permission_level_weight{ permission_level{
				member,
				"active"_n
			}, 1}
		);
	}
	uint16_t weight = _config.max_board_seats / 4;
	board_perms.emplace_back(
		permission_level_weight{ permission_level{
				get_self(),
				"eosio.code"_n
			}, weight}
	);
	action(permission_level{get_self(), "owner"_n }, "eosio"_n, "updateauth"_n,
		std::make_tuple(
			get_self(),    						//account to update
			name("active"), 					//authority name to update
			name("owner"),						//parent authority
			authority {							//authority update object 
				weight, 
				std::vector<key_weight>{},
				board_perms,
				std::vector<wait_weight>{}
			}
		)
	).send();
}

void tfvt::addallcands(name holder, uint64_t ballot_id, vector<candidate> new_cands) {
    require_auth(holder);
    eosio_assert(is_tfvt_holder(holder) || is_tfboard_holder(holder), "caller must be a TFVT or TFBOARD holder");

    for (candidate c : new_cands) {
        eosio_assert(is_nominee(c.member), "candidates must be a nonimee");
    }

    //NOTE: requires {_self}@eosio.code to send
    action(permission_level{_self, name("active")}, name("eosio.trail"), name("setallcands"), make_tuple(
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

    sort(board_candidates.begin(), board_candidates.end(), [](const auto &c1, const auto &c2) { return c1.votes >= c2.votes; });

	std::vector<permission_level_weight> board_perms;
    //add first n candidates after sorting by votes, where n is available seats on leaderboard
    for (uint8_t n = 0; n < board.available_seats; n++) {
        add_to_tfboard(board.candidates[n].member);
		
		//tie checking logic here

		board_perms.emplace_back(
			permission_level_weight{ permission_level{
				board.candidates[n].member,
				"active"_n
			}, 1}
		);
    }
    
    //TODO: send setallstats() inline to trail
	//TODO: update tf@active permission
			//set threhold to low 1/4 or 1/5 of total board members
	uint16_t weight = _config.max_board_seats / 4;
	board_perms.emplace_back(
		permission_level_weight{ permission_level{
				get_self(),
				"eosio.code"_n
			}, weight}
	);
	action(permission_level{get_self(), "owner"_n }, "eosio"_n, "updateauth"_n,
		std::make_tuple(
			get_self(), 
			name("active"), 
			name("owner"),
			authority {
				weight, 
				std::vector<key_weight>{},
				board_perms,
				std::vector<wait_weight>{}
			}
		)
	).send();


    action(permission_level{_self, name("active")}, name("eosio.trail"), name("closeballot"), make_tuple(
		_self,
		ballot_id,
		status
	)).send();

	//TODO: start run off if needed.
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

EOSIO_DISPATCH(tfvt, (inittfvt)(inittfboard)(setconfig)(setboard)(nominate)(makeissue)(closeissue)(makeelection)(endelection))
