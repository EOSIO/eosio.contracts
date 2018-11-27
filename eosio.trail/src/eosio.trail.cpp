#include "../include/eosio.trail.hpp"

trail::trail(name self, name code, datastream<const char*> ds) : contract(self, code, ds), environment(self, self.value) {
    if (!environment.exists()) {

        vector<uint64_t> new_totals;

        env_struct = env{
            self, //publisher
            new_totals, //totals
            now(), //time_now
            0 //last_ballot_id
        };

        environment.set(env_struct, self);
    } else {
        env_struct = environment.get();
        env_struct.time_now = now();
    }
}

trail::~trail() {
    if (environment.exists()) {
        environment.set(env_struct, env_struct.publisher);
    }
}

#pragma region Token_Registration

void trail::regtoken(asset max_supply, name publisher, string info_url) {
    require_auth(publisher);

    auto sym = max_supply.symbol;

    registries_table registries(_self, _self.value);
    auto r = registries.find(sym.raw());
    eosio_assert(r == registries.end(), "Token Registry with that symbol already exists in Trail");

    token_settings default_settings;

    registries.emplace(publisher, [&]( auto& a ){
        a.max_supply = max_supply;
        a.supply = asset(0, sym);
        a.publisher = publisher;
        a.info_url = info_url;
        a.settings = default_settings;
    });

    env_struct.totals[0]++; //NOTE: increment total tokens

    print("\nToken Registration: SUCCESS");
}

void trail::setsettings(name publisher, symbol token_symbol, token_settings new_settings) {
    require_auth(publisher);

    registries_table registries(_self, _self.value);
    auto r = registries.find(token_symbol.raw());
    eosio_assert(r != registries.end(), "Token Registry with that symbol doesn't exist");
    auto reg = *r;

    eosio_assert(reg.publisher == publisher, "cannot change settings of another account's registry");

    if (reg.settings.is_initialized) {
        eosio_assert(reg.settings.lock_after_initialize, "settings have been locked");
    } else {
        new_settings.is_initialized = true;
    }

    registries.modify(r, same_payer, [&]( auto& a ) {
        a.settings = new_settings;
    });

    print("\nToken Settings Update: SUCCESS");
}

void trail::unregtoken(symbol token_symbol, name publisher) {
    require_auth(publisher);
    
    registries_table registries(_self, _self.value);
    auto r = registries.find(token_symbol.raw());
    eosio_assert(r != registries.end(), "No Token Registry found matching given symbol");
    auto reg = *r;

    eosio_assert(reg.settings.is_destructible == true, "Token Registry has been set as indestructible");

    registries.erase(r);

    env_struct.totals[0]--;

    print("\nToken Unregistration: SUCCESS");
}

#pragma endregion Token_Registration


#pragma region Token_Actions

void trail::issuetoken(name publisher, name recipient, asset tokens, bool airgrab) {
    require_auth(publisher);

    registries_table registries(_self, _self.value);
    auto r = registries.find(tokens.symbol.raw());
    eosio_assert(r != registries.end(), "registry doesn't exist for that token");
    auto reg = *r;
    eosio_assert(reg.publisher == publisher, "only publisher can issue tokens");

    asset new_supply = (reg.supply + tokens);
    eosio_assert(new_supply <= reg.max_supply, "Issuing tokens would breach max supply");

    registries.modify(r, same_payer, [&]( auto& a ) { //NOTE: update supply
        a.supply = new_supply;
    });

    if (airgrab) { //NOTE: place in airgrabs table to be claimed by recipient
        airgrabs_table airgrabs(_self, publisher.value);
        auto g = airgrabs.find(recipient.value);

        if (g == airgrabs.end()) { //NOTE: new airgrab
            airgrabs.emplace(publisher, [&]( auto& a ){
                a.recipient = recipient;
                a.tokens = tokens;
            });
        } else { //NOTE: add to existing airgrab
            airgrabs.modify(g, same_payer, [&]( auto& a ) {
                a.tokens += tokens;
            });
        }

        print("\nToken Airgrab: SUCCESS");
    } else { //NOTE: publisher pays RAM cost if recipient has no balance entry (airdrop)
        balances_table balances(_self, tokens.symbol.raw());
        auto b = balances.find(recipient.value);

        if (b == balances.end()) { //NOTE: new balance
            balances.emplace(publisher, [&]( auto& a ){
                a.owner = recipient;
                a.tokens = tokens;
            });
        } else { //NOTE: add to existing balance
            balances.modify(b, same_payer, [&]( auto& a ) {
                a.tokens += tokens;
            });
        }

        print("\nToken Airdrop: SUCCESS");
    }

    print("\nAmount: ", tokens);
    print("\nRecipient: ", recipient);
}

//TODO: search for publisher instead of require as param?
void trail::claimtoken(name claimant, name publisher, symbol token_symbol) {
    require_auth(claimant);

    airgrabs_table airgrabs(_self, publisher.value);
    auto g = airgrabs.find(claimant.value);
    eosio_assert(g != airgrabs.end(), "no airgrab to claim");
    auto grab = *g;
    eosio_assert(grab.recipient == claimant, "cannot claim another account's airdrop");

    balances_table balances(_self, token_symbol.raw());
    auto b = balances.find(claimant.value);

    if (b == balances.end()) { //NOTE: create a wallet, RAM paid by claimant
        balances.emplace(claimant, [&]( auto& a ){
            a.owner = claimant;
            a.tokens = grab.tokens;
        });
    } else { //NOTE: add to existing balance
        balances.modify(b, same_payer, [&]( auto& a ) {
            a.tokens += grab.tokens;
        });
    }

    airgrabs.erase(g); //NOTE: erase airgrab

    print("\nAirgrab Claim: SUCCESS");
}

void trail::burntoken(name publisher, name balance_owner, asset amount) {
    require_auth(publisher);

    registries_table registries(_self, _self.value);
    auto r = registries.find(amount.symbol.raw());
    eosio_assert(r != registries.end(), "registry doesn't exist for that token");
    auto reg = *r;

    eosio_assert(reg.publisher == publisher, "only publisher can recall tokens");
    eosio_assert(reg.settings.is_burnable == true, "Token settings don't allow burning");

    balances_table balances(_self, amount.symbol.raw());
    auto b = balances.find(balance_owner.value);
    eosio_assert(b != balances.end(), "balance owner has no balance to recall");
    auto bal = *b;

    asset new_supply = (reg.supply - amount);

    registries.modify(r, same_payer, [&]( auto& a ) {
        a.supply = new_supply;
    });

    if (bal.tokens - amount <= asset(0, bal.tokens.symbol)) { //NOTE: if balance is less than or equal to zero, erase wallet
        balances.erase(b);
    } else {
        balances.modify(b, same_payer, [&]( auto& a ) { //NOTE: subtract amount from balance
            a.tokens -= amount;
        });
    }
    
    print("\nToken Burn: SUCCESS");
}

void trail::burnairgrab(name publisher, name recipient, asset amount) {
    require_auth(publisher);

    registries_table registries(_self, _self.value);
    auto r = registries.find(amount.symbol.raw());
    eosio_assert(r != registries.end(), "registry doesn't exist for that token");
    auto reg = *r;
    eosio_assert(reg.publisher == publisher, "only publisher can burn airgrabs");
    eosio_assert(reg.settings.is_burnable == true, "token settings don't allow airgrab burning");

    airgrabs_table airgrabs(_self, publisher.value);
    auto g = airgrabs.find(recipient.value);
    eosio_assert(g != airgrabs.end(), "recipient has no airgrab");
    auto grab = *g;

    eosio_assert(reg.supply - amount >= asset(0, reg.supply.symbol), "cannot burn supply below zero"); //NOTE: should never happen
    
    registries.modify(r, same_payer, [&]( auto& a ) {
        a.supply -= amount;
    });

    if (amount - grab.tokens <= asset(0, grab.tokens.symbol)) { //NOTE: new airgrab balance equal to or less than zero
        airgrabs.erase(g);
    } else { //NOTE: airgrab still has balance after reclaim
        airgrabs.modify(g, same_payer, [&]( auto& a ) {
            a.tokens -= amount;
        });
    }

    print("\nAirgrab Burn: SUCCESS");
}

void trail::raisemax(name publisher, asset amount) {
    require_auth(publisher);

    registries_table registries(_self, _self.value);
    auto r = registries.find(amount.symbol.raw());
    eosio_assert(r != registries.end(), "registry doesn't exist for that token");
    auto reg = *r;

    eosio_assert(reg.publisher == publisher, "cannot raise another account's max supply");
    eosio_assert(reg.settings.is_max_mutable == true, "token settings don't allow raising max supply");

    registries.modify(r, same_payer, [&]( auto& a ) {
        a.max_supply += amount;
    });

    print("\nRaise Max Supply: SUCCESS");
}

void trail::lowermax(name publisher, asset amount) {
    require_auth(publisher);

    registries_table registries(_self, _self.value);
    auto r = registries.find(amount.symbol.raw());
    eosio_assert(r != registries.end(), "registry doesn't exist for that token");
    auto reg = *r;

    eosio_assert(reg.publisher == publisher, "cannot lower another account's max supply");
    eosio_assert(reg.settings.is_max_mutable == true, "token settings don't allow lowering max supply");
    eosio_assert(reg.supply <= reg.max_supply - amount, "cannot lower max supply below circulating supply");
    eosio_assert(reg.max_supply - amount >= asset(0, amount.symbol), "cannot lower max supply below 0");

    registries.modify(r, same_payer, [&]( auto& a ) {
        a.max_supply -= amount;
    });

    print("\nLower Max Supply: SUCCESS");
}

void trail::deletewallet(name member, symbol token_symbol) {
    require_auth(member);

    balances_table balances(_self, token_symbol.raw());
    auto b = balances.find(member.value);
    eosio_assert(b != balances.end(), "account doesn't have a wallet of this token to delete");

    registries_table registries(_self, _self.value);
    auto r = registries.find(token_symbol.raw());

    if (r != registries.end()) { //NOTE: registry exists
        auto reg = *r;
        auto bal = *b;

        eosio_assert(reg.settings.is_burnable == true, "Token settings don't allow tokens to be burned");
        
        //NOTE: remove wallet balance from circulating supply
        registries.modify(r, same_payer, [&]( auto& a ) {
            a.supply -= bal.tokens;
        });

        print("\nBalance Safely Removed From Circulation: SUCCESS");
    } else { //NOTE: registry no longer exists
        balances.erase(b);

        print("\nToken Registry Doesn't Exist. Wallet Balance Burned.");
    }

    print("\nWallet Burn: SUCCESS");
}

#pragma endregion Token_Actions


#pragma region Voter_Registration

void trail::regvoter(name voter) {
    require_auth(voter);

    symbol core_symbol = symbol("VOTE", 4);

    balances_table balances(_self, core_symbol.code().raw());
    auto v = balances.find(voter.value);

    eosio_assert(v == balances.end(), "Voter already exists");

    balances.emplace(voter, [&]( auto& a ){
        a.owner = voter;
        a.tokens = asset(0, core_symbol);
    });

    env_struct.totals[1]++;

    print("\nVoter Registration: SUCCESS");
}

void trail::unregvoter(name voter) {
    require_auth(voter);

    symbol core_symbol = symbol("VOTE", 4);

    balances_table voters(_self, core_symbol.code().raw());
    auto v = voters.find(voter.value);

    eosio_assert(v != voters.end(), "Voter Doesn't Exist");

    auto vid = *v;

    //TODO: remove VOTE's from supply? check burnable status?

    voters.erase(v);

    env_struct.totals[1]--;

    print("\nVoterID Unregistration: SUCCESS");
}

#pragma endregion Voter_Registration


#pragma region Voting_Actions

void trail::mirrorcast(name voter, symbol token_symbol) {
    require_auth(voter);

    asset max_votes = get_liquid_tlos(voter) + get_staked_tlos(voter);
	auto new_votes = asset(max_votes.amount, symbol("VOTE", 4));
    eosio_assert(max_votes.symbol == symbol("TLOS", 4), "only TLOS can be used to get VOTEs"); //NOTE: redundant?
    eosio_assert(max_votes > asset(0, symbol("TLOS", 4)), "must get a positive amount of VOTEs"); //NOTE: redundant?

    balances_table balances(_self, new_votes.symbol.code().raw());
    auto b = balances.find(voter.value);
    eosio_assert(b != balances.end(), "voter is not registered"); //TODO: remove? or create wallet if doesn't exist

    counterbalances_table counterbals(_self, new_votes.symbol.code().raw());
    auto cb = counterbals.find(voter.value);
    //eosio_assert(cb != counterbals.end(), "this shouldnt happen"); //TODO: remove this line
    //asset cb_weight = asset(0, max_votes.symbol);
    counter_balance counter_bal;

    auto bal = *b;

    asset decay_amount = get_decay_amount(voter, new_votes.symbol, DECAY_RATE);
    
    if (cb != counterbals.end()) { //NOTE: if no cb found, give cb of 0
        auto counter_bal = *cb;
        eosio_assert(now() - counter_bal.last_decay >= MIN_LOCK_PERIOD, "cannot get more votes until min lock period is over");
        asset new_cb = (counter_bal.decayable_cb - decay_amount); //subtracting total cb

		//TODO: add new_votes to cb?

        if (new_cb < asset(0, symbol("VOTE", 4))) {
            new_cb = asset(0, symbol("VOTE", 4));
        }

        new_votes -= new_cb;

        counterbals.modify(cb, same_payer, [&]( auto& a ) {
            a.decayable_cb = new_cb;
        });
    }

    if (new_votes < asset(0, symbol("VOTE", 4))) { //NOTE: can't have less than 0 votes
        new_votes = asset(0, symbol("VOTE", 4));
    }

    balances.modify(b, same_payer, [&]( auto& a ) { //NOTE: allows decayed counterbalances into circulation
        a.tokens = new_votes;
    });

    print("\nMirrorCast: SUCCESS");
}

void trail::castvote(name voter, uint64_t ballot_id, uint16_t direction) {
    require_auth(voter);

    ballots_table ballots(_self, _self.value);
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "ballot with given ballot_id doesn't exist");
    auto bal = *b;

    // balances_table balances(_self, _self.value);
    // auto v = balances.find(voter.value);
    // eosio_assert(v != balances.end(), "voter is not registered");

    bool vote_success = false;

    //TODO: factor out get_weight?
    //TODO: assert vote_weight > 0?

    switch (bal.table_id) {
        case 0 : 
            eosio_assert(direction >= uint16_t(0) && direction <= uint16_t(2), "Invalid Vote. [0 = NO, 1 = YES, 2 = ABSTAIN]");
            vote_success = vote_for_proposal(voter, ballot_id, bal.reference_id, direction);
            break;
        case 1 : 
            eosio_assert(true == false, "feature still in development...");
            //vote_success = vote_for_election(voter, ballot_id, bal.reference_id, direction);
            break;
        case 2 : 
            vote_success = vote_for_leaderboard(voter, ballot_id, bal.reference_id, direction);
            break;
    }

}

void trail::deloldvotes(name voter, uint16_t num_to_delete) {
    require_auth(voter);

    votereceipts_table votereceipts(_self, voter.value);
    auto itr = votereceipts.begin();

    while (itr != votereceipts.end() && num_to_delete > 0) {
        if (itr->expiration < env_struct.time_now) { //NOTE: votereceipt has expired
            itr = votereceipts.erase(itr); //NOTE: returns iterator to next element
            num_to_delete--;
        } else {
            itr++;
        }
    }

}

#pragma endregion Voting_Actions


#pragma region Proxy_Registration

//void regproxy();

#pragma endregion Proxy_Registration


#pragma region Proxy_Actions



#pragma endregion Proxy_Actions


#pragma region Ballot_Registration

//TODO: change symbol param to symbol_code?
void trail::regballot(name publisher, uint8_t ballot_type, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url) {
    require_auth(publisher);
    eosio_assert(ballot_type >= 0 && ballot_type <= 2, "invalid ballot type"); //NOTE: update valid range as new ballot types are developed

    //TODO: check for voting_token existence?

    uint64_t new_ref_id;

    switch (ballot_type) {
        case 0 : 
            new_ref_id = make_proposal(publisher, voting_symbol, begin_time, end_time, info_url);
            env_struct.totals[2]++;
            break;
        case 1 : 
            eosio_assert(true == false, "feature still in development...");
            //new_ref_id = make_election(publisher, voting_symbol, begin_time, end_time, info_url);
            //env_struct.totals[3]++;
            break;
        case 2 : 
            new_ref_id = make_leaderboard(publisher, voting_symbol, begin_time, end_time, info_url);
            env_struct.totals[4]++;
            break;
    }

    ballots_table ballots(_self, _self.value);

    uint64_t new_ballot_id = ballots.available_primary_key();

    env_struct.last_ballot_id = new_ballot_id;

    ballots.emplace(publisher, [&]( auto& a ) {
        a.ballot_id = new_ballot_id;
        a.table_id = ballot_type;
        a.reference_id = new_ref_id;
    });

    print("\nBallot ID: ", new_ballot_id);
}

void trail::unregballot(name publisher, uint64_t ballot_id) {
    require_auth(publisher);

    ballots_table ballots(_self, _self.value);
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "Ballot Doesn't Exist");
    auto bal = *b;

    bool del_success = false;

    switch (bal.table_id) {
        case 0 : 
            del_success = delete_proposal(bal.reference_id, publisher);
            env_struct.totals[2]--;
            break;
        case 1 : 
            eosio_assert(true == false, "feature still in development...");
            //del_success = delete_election(bal.reference_id, publisher);
            //env_struct.totals[3]--;
            break;
        case 2 : 
            del_success = delete_leaderboard(bal.reference_id, publisher);
            env_struct.totals[4]--;
            break;
    }

    if (del_success) {
        ballots.erase(b);
    }

    print("\nBallot ID Deleted: ", bal.ballot_id);
}

#pragma endregion Ballot_Registration


#pragma region Ballot_Actions

void trail::addcandidate(name publisher, uint64_t ballot_id, name new_candidate, string info_link) {
    require_auth(publisher);

	//TODO: check not adding more candidates than seats available

    ballots_table ballots(_self, _self.value);
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "ballot with given ballot_id doesn't exist");
    auto bal = *b;
    eosio_assert(bal.table_id == 2, "ballot type doesn't support candidates");

    leaderboards_table leaderboards(_self, _self.value);
    auto l = leaderboards.find(bal.reference_id);
    eosio_assert(l != leaderboards.end(), "leaderboard doesn't exist");
    auto board = *l;

    eosio_assert(board.publisher == publisher, "cannot add candidate to another account's leaderboard");

    candidate new_candidate_struct = candidate{
        new_candidate,
        info_link,
        asset(0, board.voting_symbol),
        0
    };

    leaderboards.modify(*l, same_payer, [&]( auto& a ) {
        a.candidates = board.candidates;
		a.status = uint8_t(5);
    });

    print("\nAdd Candidate: SUCCESS");
}

void trail::setseats(name publisher, uint64_t ballot_id, uint8_t num_seats) {
    require_auth(publisher);

    ballots_table ballots(_self, _self.value);
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "ballot with given ballot_id doesn't exist");
    auto bal = *b;

    leaderboards_table leaderboards(_self, _self.value);
    auto l = leaderboards.find(bal.reference_id);
    eosio_assert(l != leaderboards.end(), "leaderboard doesn't exist");
    auto board = *l;

    eosio_assert(now() < board.begin_time, "cannot set seats after voting has begun");
    eosio_assert(board.publisher == publisher, "cannot set seats for another account's leaderboard");

    leaderboards.modify(l, same_payer, [&]( auto& a ) {
        a.available_seats = num_seats;
    });

    print("\nSet Available Seats: SUCCESS");
}

void trail::closeballot(name publisher, uint64_t ballot_id, uint8_t pass) {
    require_auth(publisher);

    ballots_table ballots(_self, _self.value);
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "ballot with given ballot_id doesn't exist");
    auto bal = *b;

    bool close_success = false;

    switch (bal.table_id) {
        case 0 : 
            close_success = close_proposal(bal.reference_id, pass, publisher);
            break;
        case 1 : 
            eosio_assert(true == false, "feature still in development...");
            //close_success = close_election(bal.reference_id, pass);
            break;
        case 2: 
            close_success = close_leaderboard(bal.reference_id, pass, publisher);
            break;
    }

    print("\nBallot ID Closed: ", bal.ballot_id);
}

//NOTE: currently only supports proposals
void trail::nextcycle(name publisher, uint64_t ballot_id, uint32_t new_begin_time, uint32_t new_end_time) {
    require_auth(publisher);

    ballots_table ballots(_self, _self.value);
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "Ballot Doesn't Exist");
    auto bal = *b;

    //TODO: support cycles for other ballot types?
    eosio_assert(bal.table_id == 0, "ballot type doesn't support cycles");

    proposals_table proposals(_self, _self.value);
    auto p = proposals.find(bal.reference_id);
    eosio_assert(p != proposals.end(), "proposal doesn't exist");
    auto prop = *p;

    auto sym = prop.no_count.symbol; //NOTE: uses same voting symbol as before

    proposals.modify(p, same_payer, [&]( auto& a ) {
        a.no_count = asset(0, sym);
        a.yes_count = asset(0, sym);
        a.abstain_count = asset(0, sym);
        a.unique_voters = uint32_t(0);
        a.begin_time = new_begin_time;
        a.end_time = new_end_time;
        a.cycle_count += 1;
        a.status = 0;
    });

}

#pragma endregion Ballot_Actions


#pragma region Helper_Functions

uint64_t trail::make_proposal(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url) {

    proposals_table proposals(_self, _self.value);
    uint64_t new_prop_id = proposals.available_primary_key();

    proposals.emplace(publisher, [&]( auto& a ) {
        a.prop_id = new_prop_id;
        a.publisher = publisher;
        a.info_url = info_url;
        a.no_count = asset(0, voting_symbol);
        a.yes_count = asset(0, voting_symbol);
        a.abstain_count = asset(0, voting_symbol);
        a.unique_voters = uint32_t(0);
        a.begin_time = begin_time;
        a.end_time = end_time;
        a.cycle_count = 0;
        a.status = 0;
    });

    print("\nProposal Creation: SUCCESS");

    return new_prop_id;
}

bool trail::delete_proposal(uint64_t prop_id, name publisher) {
    proposals_table proposals(_self, _self.value);
    auto p = proposals.find(prop_id);
    eosio_assert(p != proposals.end(), "proposal doesn't exist");
    auto prop = *p;

    eosio_assert(now() < prop.begin_time, "cannot delete proposal once voting has begun");
	eosio_assert(prop.publisher == publisher, "cannot delete another account's proposal");
    eosio_assert(prop.cycle_count == 0, "proposal must be on initial cycle to delete");
    //TODO: eosio_assert that status > 0?

    proposals.erase(p);

    print("\nProposal Deletion: SUCCESS");

    return true;
}

bool trail::vote_for_proposal(name voter, uint64_t ballot_id, uint64_t prop_id, uint16_t direction) {
    
    proposals_table proposals(_self, _self.value);
    auto p = proposals.find(prop_id);
    eosio_assert(p != proposals.end(), "proposal doesn't exist");
    auto prop = *p;

    eosio_assert(env_struct.time_now >= prop.begin_time && env_struct.time_now <= prop.end_time, "ballot voting window not open");
    //eosio_assert(vid.release_time >= bal.end_time, "can only vote for ballots that end before your lock period is over...prevents double voting!");

    votereceipts_table votereceipts(_self, voter.value);
    auto vr_itr = votereceipts.find(ballot_id);
    //eosio_assert(vr_itr == votereceipts.end(), "voter has already cast vote for this ballot");
    
    uint32_t new_voter = 1;
    asset vote_weight = get_vote_weight(voter, prop.no_count.symbol);

    if (vr_itr == votereceipts.end()) { //NOTE: voter hasn't voted on ballot before

        vector<uint16_t> new_directions;
        new_directions.emplace_back(direction);

        votereceipts.emplace(voter, [&]( auto& a ){
            a.ballot_id = ballot_id;
            a.directions = new_directions;
            a.weight = vote_weight;
            a.expiration = prop.end_time;
        });

        print("\nVote Cast: SUCCESS");
        
    } else { //NOTE: vote for ballot_id already exists
        auto vr = *vr_itr;

        if (vr.expiration == prop.end_time && vr.directions[0] != direction) { //NOTE: vote different and for same cycle

            switch (vr.directions[0]) { //NOTE: remove old vote weight from proposal
                case 0 : prop.no_count -= vr.weight; break;
                case 1 : prop.yes_count -= vr.weight; break;
                case 2 : prop.abstain_count -= vr.weight; break;
            }

            vr.directions[0] = direction;

            votereceipts.modify(vr_itr, same_payer, [&]( auto& a ) {
                a.directions = vr.directions;
                a.weight = vote_weight;
            });

            new_voter = 0;

            print("\nVote Recast: SUCCESS");
        } else if (vr.expiration < prop.end_time) { //NOTE: vote for new cycle on same proposal
            
            vr.directions[0] = direction;

            votereceipts.modify(vr_itr, same_payer, [&]( auto& a ) {
                a.directions = vr.directions;
                a.weight = vote_weight;
                a.expiration = prop.end_time;
            });

            print("\nVote Cast For New Cycle: SUCCESS");
        }
    }

    switch (direction) { //NOTE: update proposal with new weight
        case 0 : prop.no_count += vote_weight; break;
        case 1 : prop.yes_count += vote_weight; break;
        case 2 : prop.abstain_count += vote_weight; break;
    }

    proposals.modify(p, same_payer, [&]( auto& a ) {
        a.no_count = prop.no_count;
        a.yes_count = prop.yes_count;
        a.abstain_count = prop.abstain_count;
        a.unique_voters += new_voter;
    });

    return true;
}

bool trail::close_proposal(uint64_t prop_id, uint8_t pass, name publisher) {
    proposals_table proposals(_self, _self.value);
    auto p = proposals.find(prop_id);
    eosio_assert(p != proposals.end(), "proposal doesn't exist");
    auto prop = *p;

    eosio_assert(now() > prop.end_time, "can't close proposal while voting is still open");
	eosio_assert(prop.publisher == publisher, "cannot close another account's proposal");

    proposals.modify(p, same_payer, [&]( auto& a ) {
        a.status = pass;
    });

    return true;
}


uint64_t trail::make_election(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url) {
    elections_table elections(_self, _self.value);

    uint64_t new_elec_id = elections.available_primary_key();
    vector<candidate> empty_candidate_list;

    elections.emplace(publisher, [&]( auto& a ) {
        a.election_id = new_elec_id;
        a.publisher = publisher;
        a.info_url = info_url;
        a.candidates = empty_candidate_list;
        a.unique_voters = 0;
        a.voting_symbol = voting_symbol;
        a.begin_time = begin_time;
        a.end_time = end_time;
    });

    print("\nElection Creation: SUCCESS");

    return new_elec_id;
}

bool trail::delete_election(uint64_t elec_id, name publisher) {
    elections_table elections(_self, _self.value);
    auto e = elections.find(elec_id);
    eosio_assert(e != elections.end(), "election doesn't exist");
    auto elec = *e;

    eosio_assert(now() < elec.begin_time, "cannot delete election once voting has begun");
    eosio_assert(elec.publisher == publisher, "cannot delete another account's election");

    elections.erase(e);

    print("\nElection Deletion: SUCCESS");

    return true;
}

bool close_election(uint64_t elec_id, uint8_t pass, name publisher) {
    //TODO: implement
    return true;
}

bool delete_election(uint64_t elec_id, name publisher) {
    //TODO: implement
    return true;
}


uint64_t trail::make_leaderboard(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url) {
    require_auth(publisher);

    leaderboards_table leaderboards(_self, _self.value);
    uint64_t new_board_id = leaderboards.available_primary_key();

	candidate test_cand = candidate{
        name("voteraaaaaac"),
        "Qm2",
        asset(0, symbol("VOTE", 4)),
        0
    };

    vector<candidate> candidates;
	candidates.emplace_back(test_cand);

    leaderboards.emplace(publisher, [&]( auto& a ) {
        a.board_id = new_board_id;
        a.publisher = publisher;
        a.info_url = info_url;
        a.candidates = candidates;
        a.unique_voters = uint32_t(0);
        a.voting_symbol = voting_symbol;
        a.available_seats = 0;
        a.begin_time = begin_time;
        a.end_time = end_time;
        a.status = 0;
    });

    print("\nLeaderboard Creation: SUCCESS");

    return new_board_id;
}

bool trail::delete_leaderboard(uint64_t board_id, name publisher) {
    leaderboards_table leaderboards(_self, _self.value);
    auto b = leaderboards.find(board_id);
    eosio_assert(b != leaderboards.end(), "leaderboard doesn't exist");
    auto board = *b;

    eosio_assert(now() < board.begin_time, "cannot delete leaderboard once voting has begun");
    eosio_assert(board.publisher == publisher, "cannot delete another account's leaderboard");

    leaderboards.erase(b);

    print("\nleaderboard Deletion: SUCCESS");

    return true;
}

bool trail::vote_for_leaderboard(name voter, uint64_t ballot_id, uint64_t board_id, uint16_t direction) {
    leaderboards_table leaderboards(_self, _self.value);
    auto b = leaderboards.find(board_id);
    eosio_assert(b != leaderboards.end(), "leaderboard doesn't exist");
    auto board = *b;

    eosio_assert(env_struct.time_now >= board.begin_time && env_struct.time_now <= board.end_time, "ballot voting window not open");
    //eosio_assert(vid.release_time >= bal.end_time, "can only vote for ballots that end before your lock period is over...prevents double voting!");

    votereceipts_table votereceipts(_self, voter.value);
    auto vr_itr = votereceipts.find(ballot_id);
    //eosio_assert(vr_itr == votereceipts.end(), "voter has already cast vote for this ballot");
    
    uint32_t new_voter = 1;
    asset vote_weight = get_vote_weight(voter, board.voting_symbol);

    if (vr_itr == votereceipts.end()) { //NOTE: voter hasn't voted on ballot before

        vector<uint16_t> new_directions;
        new_directions.emplace_back(direction);

        votereceipts.emplace(voter, [&]( auto& a ){
            a.ballot_id = ballot_id;
            a.directions = new_directions;
            a.weight = vote_weight;
            a.expiration = board.end_time;
        });

        print("\nVote Cast: SUCCESS");
        
    } else { //NOTE: vote for ballot_id already exists
        auto vr = *vr_itr;

        if (vr.expiration == board.end_time && !has_direction(direction, vr.directions)) { //NOTE: hasn't voted for candidate before

            new_voter = 0;
            vr.directions.emplace_back(direction);

            votereceipts.modify(vr_itr, same_payer, [&]( auto& a ) {
                a.directions = vr.directions;
            });

            print("\nVote Recast: SUCCESS");

        }//TODO: implement recasting vote for same candidate
        
    }

    //NOTE: update leaderboard with new weight
    board.candidates[direction].votes += vote_weight;

    leaderboards.modify(b, same_payer, [&]( auto& a ) {
        a.candidates = board.candidates;
        a.unique_voters += new_voter;
    });

    return true;
}

bool trail::close_leaderboard(uint64_t board_id, uint8_t pass, name publisher) {
    leaderboards_table leaderboards(_self, _self.value);
    auto b = leaderboards.find(board_id);
    eosio_assert(b != leaderboards.end(), "leaderboard doesn't exist");
    auto board = *b;

    eosio_assert(now() > board.end_time, "cannot close leaderboard while voting is still open");
    eosio_assert(board.publisher == publisher, "cannot close another account's leaderboard");

    leaderboards.modify(b, same_payer, [&]( auto& a ) {
        a.status = pass;
    });

    return true;
}



asset trail::get_vote_weight(name voter, symbol voting_symbol) {

    balances_table balances(_self, voting_symbol.code().raw());
    auto b = balances.find(voter.value);

    if (b == balances.end()) { //NOTE: no balance found, returning 0
        return asset(0, voting_symbol);
    } else {
        auto bal = *b;
        return bal.tokens;
    }

    // if (voting_symbol == symbol("VOTE", 4)) {
    //     voters_table voters(_self, _self.value);
    //     auto v = voters.find(voter.value);
    //     eosio_assert(v != voters.end(), "voter isn't registered");
    //     auto vid = *v;

    //     return vid.votes;
    // } else {
    //     eosio_assert(is_registered_token(voting_token), "token is not registered");

    //     balances_table balances(_self, voting_token.raw());
    //     auto b = balances.find(voter.value);
    //     eosio_assert(b != balances.end(), "voter doesn't have a balance of the voting token");
    //     auto bal = *b;
        
    //     return bal.tokens;   
    // }
}

bool trail::has_direction(uint16_t direction, vector<uint16_t> direction_list) {

    for (uint16_t item : direction_list) {
        if (item == direction) {
            return true;
        }
    }

    return false;
}

#pragma endregion Helper_Functions


#pragma region Reactions

void trail::update_from_cb(name from, asset amount) {
    counterbalances_table fromcbs(_self, amount.symbol.code().raw());
    auto cb_itr = fromcbs.find(from.value);
    
    if (cb_itr == fromcbs.end()) {
        fromcbs.emplace(_self, [&]( auto& a ){ //TODO: change ram payer to user? may prevent TLOS transfers
            a.owner = from;
            a.decayable_cb = asset(0, symbol("VOTE", 4));
			a.persistent_cb = asset(0, symbol("VOTE", 4));
            a.last_decay = env_struct.time_now;
        });
    } else {
        auto from_cb = *cb_itr;
        asset new_cb = from_cb.decayable_cb - amount;

        if (new_cb < asset(0, symbol("VOTE", 4))) {
            new_cb = asset(0, symbol("VOTE", 4));
        }

        fromcbs.modify(cb_itr, same_payer, [&]( auto& a ) {
            a.decayable_cb = new_cb;
            //a.last_decay = env_struct.time_now;
        });
    }
}

void trail::update_to_cb(name to, asset amount) {
    counterbalances_table tocbs(_self, amount.symbol.code().raw());
    auto cb_itr = tocbs.find(to.value);

    if (cb_itr == tocbs.end()) {
        tocbs.emplace(_self, [&]( auto& a ){ //TODO: change ram payer to user? may prevent TLOS transfers
            a.owner = to;
            a.decayable_cb = asset(amount.amount, symbol("VOTE", 4));
			a.persistent_cb = asset(0, symbol("VOTE", 4));
            a.last_decay = env_struct.time_now;
        });
    } else {
        auto to_cb = *cb_itr;
        asset new_cb = to_cb.decayable_cb + amount;

        tocbs.modify(cb_itr, same_payer, [&]( auto& a ) {
            a.decayable_cb = new_cb;
            //a.last_decay = env_struct.time_now;
        });
    }
}

asset trail::get_decay_amount(name voter, symbol token_symbol, uint32_t decay_rate) {
    counterbalances_table counterbals(_self, token_symbol.code().raw());
    auto cb_itr = counterbals.find(voter.value);

    uint32_t time_delta;

    if (cb_itr != counterbals.end()) {
        auto cb = *cb_itr;
        time_delta = env_struct.time_now - cb.last_decay;
        return asset(int64_t(time_delta / decay_rate) * 10000, symbol("VOTE", 4)); //TODO: apply proper precision, currently only works for precision 4
    }

    return asset(0, symbol("VOTE", 4));
}

#pragma endregion Reactions

//EOSIO_DISPATCH(trail, )

extern "C" {
    void apply(uint64_t self, uint64_t code, uint64_t action) {

        size_t size = action_data_size();
        constexpr size_t max_stack_buffer_size = 512;
        void* buffer = nullptr;
        if( size > 0 ) {
            buffer = max_stack_buffer_size < size ? malloc(size) : alloca(size);
            read_action_data(buffer, size);
        }
        datastream<const char*> ds((char*)buffer, size);

        trail trailservice(name(self), name(code), ds);

        if(code == self && action == name("regtoken").value) {
            execute_action(name(self), name(code), &trail::regtoken);
        } else if (code == self && action == name("unregtoken").value) {
            execute_action(name(self), name(code), &trail::unregtoken);
        } else if (code == self && action == name("regvoter").value) {
            execute_action(name(self), name(code), &trail::regvoter);
        } else if (code == self && action == name("unregvoter").value) {
            execute_action(name(self), name(code), &trail::unregvoter);
        } else if (code == self && action == name("regballot").value) {
            execute_action(name(self), name(code), &trail::regballot);
        } else if (code == self && action == name("unregballot").value) {
            execute_action(name(self), name(code), &trail::unregballot);
        } else if (code == self && action == name("mirrorcast").value) {
            execute_action(name(self), name(code), &trail::mirrorcast);
        } else if (code == self && action == name("castvote").value) {
            execute_action(name(self), name(code), &trail::castvote);
        } else if (code == self && action == name("closeballot").value) {
            execute_action(name(self), name(code), &trail::closeballot);
        } else if (code == self && action == name("nextcycle").value) {
            execute_action(name(self), name(code), &trail::nextcycle);
        } else if (code == self && action == name("deloldvotes").value) {
            execute_action(name(self), name(code), &trail::deloldvotes);
        } else if (code == name("eosio.token").value && action == name("transfer").value) { //NOTE: updates vote_levy after transfers
            auto args = unpack_action_data<transfer_args>();
            trailservice.update_from_cb(args.from, asset(args.quantity.amount, symbol("VOTE", 4)));
            trailservice.update_to_cb(args.to, asset(args.quantity.amount, symbol("VOTE", 4)));
        }
    } //end apply
}; //end dispatcher
