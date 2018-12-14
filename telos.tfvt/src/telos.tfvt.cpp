#include <telos.tfvt.hpp>
#include <eosiolib/symbol.hpp>
//#include <eosiolib/print.hpp>

tfvt::tfvt(name self, name code, datastream<const char*> ds)
: contract(self, code, ds), configs(get_self(), get_self().value) {
	print("\n exists?: ", configs.exists());
	_config = configs.exists() ? configs.get() : get_default_config();
}

tfvt::~tfvt() {
	if(configs.exists()) configs.set(_config, get_self());
}

tfvt::config tfvt::get_default_config() {
	auto c = config {
		get_self(),			//publisher
		uint8_t(12),		//max seats
		uint8_t(12),        //open seats
		uint64_t(0),		//open_election_id
		uint32_t(5), 		//holder_quorum_divisor
		uint32_t(2), 		//board_quorum_divisor
		uint32_t(2000000),	//issue_duration
		uint32_t(1200),  	//start_delay
		uint32_t(2000000),  //leaderboard_duration
		uint32_t(14515200),	//election_frequency
		uint32_t(0),		//last_board_election_time
		false				//is_active_election
	};
	configs.set(c, get_self());
	return c;
}

#pragma region Actions

void tfvt::inittfvt(string initial_info_link) {
    require_auth(get_self());
    
    action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("regtoken"), make_tuple(
		INITIAL_TFVT_MAX_SUPPLY, //max_supply
		get_self(), //publisher
		initial_info_link //info_url
	)).send();

    action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("initsettings"), make_tuple(
		get_self(), //publisher
		INITIAL_TFVT_MAX_SUPPLY.symbol, //token_symbol
		INITIAL_TFVT_SETTINGS //new_settings
	)).send();

    print("\nTFVT Registration and Initialization Actions Sent...");
}

void tfvt::inittfboard(string initial_info_link) {
    require_auth(get_self());
    
    action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("regtoken"), make_tuple(
		INITIAL_TFBOARD_MAX_SUPPLY, //max_supply
		get_self(), 						//publisher
		initial_info_link 			//info_url
	)).send();

    action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("initsettings"), make_tuple(
		get_self(), //publisher
		INITIAL_TFBOARD_MAX_SUPPLY.symbol, //token_symbol
		INITIAL_TFBOARD_SETTINGS //new_settings
	)).send();
	
	asset board_token = asset(1, symbol("TFBOARD", 0));
	action(permission_level{get_self(), "active"_n }, "eosio.trail"_n, "issuetoken"_n,
		std::make_tuple(
			get_self(),		//account to update
			get_self(),
			board_token,
			false
		)
	).send();

    print("\nTFBOARD Registration and Initialization Actions Sent...");
}

void tfvt::setconfig(name member, config new_config) { 
    require_auth("tf"_n);
	configs.remove();
    eosio_assert(new_config.max_board_seats >= new_config.open_seats, "can't have more open seats than max seats");
	eosio_assert(new_config.holder_quorum_divisor > 0, "holder_quorum_divisor must be a non-zero number");
	eosio_assert(new_config.board_quorum_divisor > 0, "board_quorum_divisor must be a non-zero number");
	eosio_assert(new_config.issue_duration > 0, "issue_duration must be a non-zero number");
	eosio_assert(new_config.start_delay > 0, "start_delay must be a non-zero number");
	eosio_assert(new_config.leaderboard_duration > 0, "leaderboard_duration must be a non-zero number");
	eosio_assert(new_config.election_frequency > 0, "election_frequency must be a non-zero number");

	// NOTE : this will break an ongoing election check for makeelection 
	if(new_config.max_board_seats >= _config.max_board_seats){
		new_config.open_seats = new_config.max_board_seats - _config.max_board_seats + _config.open_seats;

		auto extra_seats = new_config.max_board_seats - _config.max_board_seats;
		if(extra_seats > 0){
			asset board_token = asset(extra_seats, symbol("TFBOARD", 0));
			action(permission_level{"tf"_n, "active"_n }, "eosio.trail"_n, "raisemax"_n,
				std::make_tuple(
					get_self(),
					board_token
				)
			).send();
		}
	}else if(new_config.max_board_seats > _config.max_board_seats - _config.open_seats){
		new_config.open_seats = new_config.max_board_seats - (_config.max_board_seats - _config.open_seats);
	}else{
		new_config.open_seats = 0;
	}

	new_config.publisher = _config.publisher;
	new_config.open_election_id = _config.open_election_id;
	new_config.last_board_election_time = _config.last_board_election_time;
	new_config.is_active_election = _config.is_active_election;

	_config = new_config;
	configs.set(_config, get_self());
}

void tfvt::makeissue(ignore<name> holder, 
		ignore<string> info_url,
		ignore<name> issue_name,
		ignore<transaction> transaction) {

	name 	_holder;
	string _info_url;
	name	_issue_name;
	eosio::transaction _trx;

	_ds >> _holder >> _info_url >> _issue_name >> _trx;

    require_auth(_holder);

	eosio_assert(is_tfvt_holder(_holder) || is_tfboard_holder(_holder), "caller must be a TFVT or TFBOARD holder");

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
	issues.emplace(get_self(), [&](auto& issue) {
		issue.proposer = _holder;
		issue.issue_name = _issue_name;
		issue.ballot_id = next_ballot_id;
		issue.transaction = _trx;
	});
}

void tfvt::closeissue(name holder, name proposer) {
    require_auth(holder);
	eosio_assert(is_tfvt_holder(holder) || is_tfboard_holder(holder), "caller must be a TFVT or TFBOARD holder");

	issues_table issues(get_self(), get_self().value);
	auto i_iter = issues.find(proposer.value);
	eosio_assert(i_iter != issues.end(), "issue not found");
	auto issue = *i_iter;

	ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
	auto ballot = ballots.get(issue.ballot_id, "ballot does not exist");

	proposals_table proposals("eosio.trail"_n, "eosio.trail"_n.value);
	auto prop = proposals.get(ballot.reference_id, "proposal not found");

	registries_table registries("eosio.trail"_n, "eosio.trail"_n.value);
	auto registry = registries.get(prop.no_count.symbol.code().raw(), "registry not found, this shouldn't happen");
	uint32_t total_voters = registry.total_voters;
	
	uint32_t unique_voters = prop.unique_voters;
     
	uint32_t quorum_threshold = total_voters / (_config.board_quorum_divisor - 1);
	ISSUE_STATE state = FAIL;
	if(unique_voters > quorum_threshold)
		state = COUNT;
	
	if(state == COUNT) {
		if(prop.yes_count > prop.no_count)
			state = PASS;
		else if(prop.yes_count == prop.no_count)
			state = TIE;
		else
			state = FAIL;
	}

	if(state == PASS) {
		members_table members(get_self(), get_self().value);
		std::vector<permission_level> requested;
		auto itr = members.begin();

		while (itr != members.end()) {
			// print("adding permission_level: ", name{itr->member});
			requested.emplace_back(permission_level(itr->member, "active"_n));
			itr++;
		}	
		
		action(permission_level{get_self(), name("active")}, name("eosio.msig"), name("propose"), make_tuple(
			get_self(),
			issue.issue_name,
			requested,
			issue.transaction
		)).send();
	} 

	if(state == FAIL || state == PASS) {
		
		issues.erase(i_iter);
	}

	if(state == TIE) {
		uint64_t next_ballot_id = ballots.available_primary_key();
		uint32_t begin_time = now() + _config.start_delay;
		uint32_t end_time = begin_time + _config.issue_duration;
		action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "regballot"_n, make_tuple(
			get_self(),					//proposer name
			uint8_t(0), 				//ballot_type uint8_t
			symbol("TFVT", 0),			//voting_symbol symbol
			begin_time,					//begin_time uint32_t
			end_time,					//end_time uint32_t
			prop.info_url				//info_url string
		)).send();

		issues.modify(issue, same_payer, [&](auto& i) {
			i.ballot_id = next_ballot_id;
		});
	}

    action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "closeballot"_n, make_tuple(
		get_self(),
		issue.ballot_id,
		uint8_t(state)
	)).send();
}

void tfvt::nominate(name nominee, name nominator) {
    require_auth(nominator);
	eosio_assert(is_tfvt_holder(nominator), "caller must be a TFVT holder");

    nominees_table noms(get_self(), get_self().value);
    auto n = noms.find(nominee.value);
    eosio_assert(n == noms.end(), "nominee has already been nominated");

    noms.emplace(get_self(), [&](auto& m) {
        m.nominee = nominee;
    });
}

void tfvt::makeelection(name holder, string info_url) {
    require_auth(holder);
	eosio_assert(!_config.is_active_election, "there is already an election is progress");
    eosio_assert(is_tfvt_holder(holder) || is_tfboard_holder(holder), "caller must be a TFVT or TFBOARD holder");
	eosio_assert(_config.open_seats > 0 || is_term_expired(), "it isn't time for the next election");

	ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
	_config.open_election_id = ballots.available_primary_key(); 

	uint32_t begin_time = now() + _config.start_delay;
	uint32_t end_time = begin_time + _config.leaderboard_duration;

    action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("regballot"), make_tuple(
		get_self(),
		uint8_t(2), 			//NOTE: makes a leaderboard on Trail
		symbol("TFVT", 0),
		begin_time,
        end_time,
        info_url
	)).send();

	uint8_t available_seats = _config.open_seats;
	if(is_term_expired()){
		available_seats = _config.max_board_seats;
	}

    action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("setseats"), make_tuple(
		get_self(),
		_config.open_election_id, 			//NOTE: adds available seats to a leaderboard on Trail
		available_seats
	)).send();

	//NOTE: this prevents makeelection from being called multiple times.
	//NOTE2 : this gets overwritten by setconfig
	_config.open_seats = 0;
	_config.is_active_election = true;
}

void tfvt::addcand(name nominee, string info_link) {
	require_auth(nominee);
	eosio_assert(is_nominee(nominee), "only nominees can be added to the election");

	// TODO check if election has started

    action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("addcandidate"), make_tuple(
		get_self(), 				//publisher
		_config.open_election_id, 	//ballot_id
		nominee, 					//new_candidate
		info_link					//info_link
	)).send();
}

void tfvt::removecand(name candidate) {
	require_auth(candidate);
	eosio_assert(is_nominee(candidate), "candidate is not a nominee");

    action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("rmvcandidate"), make_tuple(
		get_self(), 				//publisher
		_config.open_election_id, 	//ballot_id
		candidate 					//new_candidate
	)).send();
}

void tfvt::endelection(name holder) {
    require_auth(holder);
    eosio_assert(is_tfvt_holder(holder) || is_tfboard_holder(holder), "caller must be a TFVT or TFBOARD holder");
	eosio_assert(_config.is_active_election, "there is no active election to end");
	uint8_t status = 1;

    ballots_table ballots(name("eosio.trail"), name("eosio.trail").value);
    auto bal = ballots.get(_config.open_election_id);
    
    leaderboards_table leaderboards(name("eosio.trail"), name("eosio.trail").value);
    auto board = leaderboards.get(bal.reference_id);
    auto board_candidates = board.candidates;

    sort(board_candidates.begin(), board_candidates.end(), [](const auto &c1, const auto &c2) { return c1.votes > c2.votes; });
	
	if(board_candidates.size() > board.available_seats) {
		auto first_cand_out = board_candidates[board.available_seats];
		board_candidates.resize(board.available_seats);
		
		// count candidates that are tied with first_cand_out
		uint8_t tied_cands = 0;
		for(int i = board_candidates.size() - 1; i >= 0; i--) {
			if(board_candidates[i].votes == first_cand_out.votes) 
			tied_cands++;
		}

		// remove all tied candidates
		if(tied_cands > 0) board_candidates.resize(board_candidates.size() - tied_cands);
	}

	if(board_candidates.size() > 0 && is_term_expired()) {
		remove_and_seize_all();
		_config.last_board_election_time = now();
	}

    for (int n = 0; n < board_candidates.size(); n++) {
		if(board_candidates[n].votes > asset(0, board_candidates[n].votes.symbol))
        	add_to_tfboard(board_candidates[n].member);
    }
    
	vector<permission_level_weight> currently_elected = perms_from_members(); //NOTE: needs testing

	if(currently_elected.size() > 0)
		set_permissions(currently_elected);
	
	members_table members(_self, _self.value);

	_config.open_seats = _config.max_board_seats - uint8_t(std::distance(members.begin(), members.end()));

	action(permission_level{get_self(), name("active")}, name("eosio.trail"), name("closeballot"), make_tuple(
		get_self(),
		_config.open_election_id,
		status
	)).send();
	_config.is_active_election = false;
}

void tfvt::removemember(name member_to_remove) {
	require_auth2(get_self().value, "major"_n.value);
	remove_and_seize(member_to_remove);
	
	auto perms = perms_from_members();
	set_permissions(perms);
}

#pragma endregion Actions


#pragma region Helper_Functions

void tfvt::add_to_tfboard(name nominee) {
    nominees_table noms(get_self(), get_self().value);
    auto n = noms.find(nominee.value);
    eosio_assert(n != noms.end(), "nominee doesn't exist in table");

    members_table mems(get_self(), get_self().value);
    auto m = mems.find(nominee.value);
    eosio_assert(m == mems.end(), "nominee is already a board member");

    noms.erase(n); //NOTE remove from nominee table

    mems.emplace(get_self(), [&](auto& m) { //NOTE: emplace in boardmembers table
        m.member = nominee;
    });
	print("\nsending issuetokens inline to ", nominee);
	asset board_token = asset(1, symbol("TFBOARD", 0));
	action(permission_level{get_self(), "active"_n }, "eosio.trail"_n, "issuetoken"_n,
		std::make_tuple(
			get_self(),		//account to update
			nominee,
			board_token,
			false
		)
	).send();
}

void tfvt::rmv_from_tfboard(name member) {
    members_table mems(get_self(), get_self().value);
    auto m = mems.find(member.value);
    eosio_assert(m != mems.end(), "member is not on the board");

    mems.erase(m);
}

void tfvt::addseats(name member, uint8_t num_seats) {
    require_auth(get_self());

    config_table configs(get_self(), get_self().value);
    auto c = configs.get();

	c.max_board_seats += num_seats;
	c.open_seats += num_seats;

    configs.set(c, get_self());
}

bool tfvt::is_board_member(name user) {
    members_table mems(get_self(), get_self().value);
    auto m = mems.find(user.value);
    
    if (m != mems.end()) {
        return true;
    }

    return false;
}

bool tfvt::is_nominee(name user) {
    nominees_table noms(get_self(), get_self().value);
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

bool tfvt:: is_tfboard_holder(name user) {
    balances_table balances(name("eosio.trail"), symbol("TFBOARD", 0).code().raw());
    auto b = balances.find(user.value);

    if (b != balances.end()) {
        return true;
    }

    return false;
}

bool tfvt::is_term_expired() {
	return now() - _config.last_board_election_time > _config.election_frequency;
}

void tfvt::remove_and_seize_all() {
	members_table members(get_self(), get_self().value);
	asset amount_to_seize = asset(1, symbol("TFBOARD", 0));

	auto itr = members.begin();
	vector<name> to_seize;
	while(itr != members.end()) {
		to_seize.emplace_back(itr->member);
		itr = members.erase(itr);
	}
	
	if(to_seize.size() > 0){
		action(permission_level{get_self(), "active"_n }, "eosio.trail"_n, "seizebygroup"_n,
			std::make_tuple(
				get_self(),		//account to update
				to_seize,
				amount_to_seize
			)
		).send();

		asset amount_to_burn = asset(to_seize.size(), symbol("TFBOARD", 0));
		action(permission_level{get_self(), "active"_n }, "eosio.trail"_n, "burntoken"_n,
			std::make_tuple(
				get_self(),
				amount_to_burn
			)
		).send();
	}
}

void tfvt::remove_and_seize(name member) {
	members_table members(get_self(), get_self().value);
	asset amount_to_seize = asset(1, symbol("TFBOARD", 0));
	auto m = members.get(member.value, "board member not found");

	members.erase(m);

	action(permission_level{get_self(), "active"_n }, "eosio.trail"_n, "seizetoken"_n,
		std::make_tuple(
			get_self(),		//account to update
			member,
			amount_to_seize
		)
	).send();
}

void tfvt::set_permissions(vector<permission_level_weight> perms) {
	auto self = get_self();
	uint16_t active_weight = perms.size() < 4 ? 1 : (perms.size() / 4);

	perms.emplace_back(
		permission_level_weight{ permission_level{
				self,
				"eosio.code"_n
			}, active_weight}
	);
	sort(perms.begin(), perms.end(), [](const auto &first, const auto &second) { return first.permission.actor.value < second.permission.actor.value; });
	
	action(permission_level{get_self(), "owner"_n }, "eosio"_n, "updateauth"_n,
		std::make_tuple(
			get_self(), 
			name("active"), 
			name("owner"),
			authority {
				active_weight, 
				std::vector<key_weight>{},
				perms,
				std::vector<wait_weight>{}
			}
		)
	).send();

	auto tf_it = std::find_if(perms.begin(), perms.end(), [&self](const permission_level_weight &lvlw) {
        return lvlw.permission.actor == self; 
    });
	perms.erase(tf_it);

	uint16_t major_weight = perms.size() < 3 ? 1 : ((perms.size() / 3) * 2);
	action(permission_level{get_self(), "owner"_n }, "eosio"_n, "updateauth"_n,
		std::make_tuple(
			get_self(), 
			name("major"), 
			name("owner"),
			authority {
				major_weight, 
				std::vector<key_weight>{},
				perms,
				std::vector<wait_weight>{}
			}
		)
	).send();
}

vector<tfvt::permission_level_weight> tfvt::perms_from_members() {
	members_table members(get_self(), get_self().value);
	auto itr = members.begin();
	
	vector<permission_level_weight> perms;
	while(itr != members.end()) {
			perms.emplace_back(permission_level_weight{ permission_level{
				itr->member,
				"active"_n
			}, 1});
		itr++;
	}

	return perms;
}

#pragma endregion Helper_Functions

//(setboard)
EOSIO_DISPATCH(tfvt, (inittfvt)(inittfboard)(setconfig)(nominate)(makeissue)
	(closeissue)(makeelection)(addcand)(removecand)(endelection)(removemember))
