#include <eosio.trail.hpp>

trail::trail(account_name self) : contract(self), environment(self, self) {
    if (!environment.exists()) {

        env_struct = env{
            self, //publisher
            0, //total_tokens
            0, //total_voters
            0, //total_ballots
            asset(0, S(4, VOTE)), //vote_supply
            now() //time_now
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

#pragma region Token_Actions

void trail::regtoken(asset native, account_name publisher) {
    require_auth(publisher);

    auto sym = native.symbol.name();

    stats statstable(N(eosio.token), sym);
    auto eosio_existing = statstable.find(sym);
    eosio_assert(eosio_existing == statstable.end(), "Token with symbol already exists in eosio.token" );

    registries_table registries(_self, _self);
    auto r = registries.find(sym);
    eosio_assert(r == registries.end(), "Token Registry with that symbol already exists in Trail");

    //TODO: assert only 1 token per publisher

    registries.emplace(publisher, [&]( auto& a ){
        a.native = native;
        a.publisher = publisher;
    });

    env_struct.total_tokens++;

    print("\nToken Registration: SUCCESS");
}

void trail::unregtoken(asset native, account_name publisher) {
    require_auth(publisher);
    
    auto sym = native.symbol.name();
    registries_table registries(_self, _self);
    auto r = registries.find(sym);

    eosio_assert(r != registries.end(), "Token Registry does not exist.");

    registries.erase(r);

    env_struct.total_tokens--;

    print("\nToken Unregistration: SUCCESS");
}

#pragma endregion Token_Actions

#pragma region Voting_Actions

void trail::regvoter(account_name voter) {
    require_auth(voter);

    voters_table voters(_self, _self);
    auto v = voters.find(voter);

    eosio_assert(v == voters.end(), "Voter already exists");

    voters.emplace(voter, [&]( auto& a ){
        a.voter = voter;
        a.votes = asset(0, S(4, VOTE));
    });

    env_struct.total_voters++;

    print("\nVoterID Registration: SUCCESS");
}

void trail::unregvoter(account_name voter) {
    require_auth(voter);

    voters_table voters(_self, _self);
    auto v = voters.find(voter);

    eosio_assert(v != voters.end(), "Voter Doesn't Exist");

    auto vid = *v;

    env_struct.vote_supply -= vid.votes;

    voters.erase(v);

    env_struct.total_voters--;

    print("\nVoterID Unregistration: SUCCESS");
}

void trail::regballot(account_name publisher, asset voting_token, uint32_t begin_time, uint32_t end_time, string info_url) {
    require_auth(publisher);

    //TODO: check for voting_token existence?

    ballots_table ballots(_self, _self);

    ballots.emplace(publisher, [&]( auto& a ){
        a.ballot_id = ballots.available_primary_key();
        a.publisher = publisher;
        a.info_url = info_url;
        a.no_count = asset(0, voting_token.symbol);
        a.yes_count = asset(0, voting_token.symbol);
        a.abstain_count = asset(0, voting_token.symbol);
        a.unique_voters = uint32_t(0);
        a.begin_time = begin_time;
        a.end_time = end_time;
    });

    env_struct.total_ballots++;

    print("\nBallot Registration: SUCCESS");
}

void trail::unregballot(account_name publisher, uint64_t ballot_id) {
    require_auth(N(eosio.trail));

    ballots_table ballots(_self, _self);
    auto b = ballots.find(ballot_id);

    eosio_assert(b != ballots.end(), "Ballot Doesn't Exist");

    auto bal = *b;

    eosio_assert(bal.status > 0, "ballot voting in progress, cannot unregister");

    ballots.erase(b);

    env_struct.total_ballots--;

    print("\nBallot Deletion: SUCCESS");
}

void trail::mirrorstake(account_name voter, uint32_t lock_period) {
    require_auth(voter);
    eosio_assert(lock_period >= MIN_LOCK_PERIOD, "lock period must be greater than 1 day (86400 secs)");
    eosio_assert(lock_period <= MAX_LOCK_PERIOD, "lock period must be less than 3 months (7,776,000 secs)");

    asset max_votes = get_liquid_tlos(voter) + get_staked_tlos(voter);
    eosio_assert(max_votes.symbol == S(4, TLOS), "only TLOS can be used to get VOTEs"); //NOTE: redundant?
    eosio_assert(max_votes > asset(0, S(4, TLOS)), "must get a positive amount of VOTEs"); //NOTE: redundant?
    
    voters_table voters(N(eosio.trail), N(eosio.trail));
    auto v = voters.find(voter);
    eosio_assert(v != voters.end(), "voter is not registered");

    auto vid = *v;
    eosio_assert(now() >= vid.release_time, "cannot get more votes until lock period is over");

    votelevies_table votelevies(N(eosio.trail), N(eosio.trail));
    auto vl = votelevies.find(voter);

    auto new_votes = asset(max_votes.amount, S(4, VOTE)); //mirroring TLOS amount, not spending/locking it up
    asset decay_amount = calc_decay(voter, new_votes);
    
    if (vl != votelevies.end()) { //NOTE: if no levy found, give levy of 0
        auto levy = *vl;
        asset new_levy = (levy.levy_amount - decay_amount); //subtracting levy

        if (new_levy < asset(0, S(4, VOTE))) {
            new_levy = asset(0, S(4, VOTE));
        }

        new_votes -= new_levy;

        votelevies.modify(vl, 0, [&]( auto& a ) {
            a.levy_amount = new_levy;
        });
    }

    if (new_votes < asset(0, S(4, VOTE))) { //NOTE: can't have less than 0 votes
        new_votes = asset(0, S(4, VOTE));
    }

    voters.modify(v, 0, [&]( auto& a ) {
        a.votes = new_votes;
        a.release_time = now() + lock_period;
    });

    print("\nRegister For Votes: SUCCESS");
}

void trail::castvote(account_name voter, uint64_t ballot_id, uint16_t direction) {
    require_auth(voter);
    eosio_assert(direction >= uint16_t(0) && direction <= uint16_t(2), "Invalid Vote. [0 = NO, 1 = YES, 2 = ABSTAIN]");

    voters_table voters(N(eosio.trail), N(eosio.trail));
    auto v = voters.find(voter);
    eosio_assert(v != voters.end(), "voter is not registered");

    auto vid = *v;

    ballots_table ballots(N(eosio.trail), N(eosio.trail));
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "ballot with given ballot_id doesn't exist");

    auto bal = *b;
    eosio_assert(env_struct.time_now >= bal.begin_time && env_struct.time_now <= bal.end_time, "ballot voting window not open");
    //eosio_assert(vid.release_time >= bal.end_time, "can only vote for ballots that end before your lock period is over...prevents double voting!");

    votereceipts_table votereceipts(N(eosio.trail), voter);
    auto vr_itr = votereceipts.find(ballot_id);
    //eosio_assert(vr_itr == votereceipts.end(), "voter has already cast vote for this ballot");
    
    uint32_t new_voter = 1;

    if (vr_itr == votereceipts.end()) { //NOTE: voter hasn't voted on ballot before
        votereceipts.emplace(voter, [&]( auto& a ){
            a.ballot_id = ballot_id;
            a.direction = direction;
            a.weight = vid.votes;
            a.expiration = bal.end_time;
        });
    } else { //NOTE: vote for ballot_id already exists
        auto vr = *vr_itr;

        if (vr.expiration == bal.end_time && vr.direction != direction) { //NOTE: vote different and for same cycle

            switch (vr.direction) {
                case 0 : bal.no_count -= vid.votes; break;
                case 1 : bal.yes_count -= vid.votes; break;
                case 2 : bal.abstain_count -= vid.votes; break;
            }

            votereceipts.modify(vr_itr, 0, [&]( auto& a ) {
                a.direction = direction;
                a.weight = vid.votes;
            });

            new_voter = 0;

            print("\nVote Recast: SUCCESS");
        } else if (vr.expiration < bal.end_time) { //NOTE: vote for new cycle
            votereceipts.modify(vr_itr, 0, [&]( auto& a ) {
                a.direction = direction;
                a.weight = vid.votes;
                a.expiration = bal.end_time;
            });
        }
    }

    switch (direction) {
        case 0 : bal.no_count += vid.votes; break;
        case 1 : bal.yes_count += vid.votes; break;
        case 2 : bal.abstain_count += vid.votes; break;
    }

    ballots.modify(b, 0, [&]( auto& a ) {
        a.no_count = bal.no_count;
        a.yes_count = bal.yes_count;
        a.abstain_count = bal.abstain_count;
        a.unique_voters += new_voter;
    });

    print("\nVote: SUCCESS");
}

void trail::closevote(account_name publisher, uint64_t ballot_id, uint8_t pass) {
    require_auth(publisher);

    ballots_table ballots(N(eosio.trail), N(eosio.trail));
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "ballot with given ballot_id doesn't exist");

    auto bal = *b;
    eosio_assert(now() >= bal.end_time, "ballot voting window still open");

    ballots.modify(b, 0, [&]( auto& a ) {
        a.status = pass;
    });

}

void trail::nextcycle(account_name publisher, uint64_t ballot_id, uint32_t new_begin_time, uint32_t new_end_time) {
    require_auth(publisher);

    ballots_table ballots(_self, _self);
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "Ballot Doesn't Exist");
    auto bal = *b;

    auto sym = bal.no_count.symbol;

    ballots.emplace(publisher, [&]( auto& a ){
        a.no_count = asset(0, sym);
        a.yes_count = asset(0, sym);
        a.abstain_count = asset(0, sym);
        a.unique_voters = uint32_t(0);
        a.begin_time = new_begin_time;
        a.end_time = new_end_time;
        a.status = false;
    });

}

void trail::deloldvotes(account_name voter, uint16_t num_to_delete) {
    require_auth(voter);

    votereceipts_table votereceipts(N(eosio.trail), voter);
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

#pragma region Reactions

void trail::update_from_levy(account_name from, asset amount) {
    votelevies_table fromlevies(N(eosio.trail), N(eosio.trail));
    auto vl_from_itr = fromlevies.find(from);
    
    if (vl_from_itr == fromlevies.end()) {
        fromlevies.emplace(N(eosio.trail), [&]( auto& a ){
            a.voter = from;
            a.levy_amount = asset(0, S(4, VOTE));
            a.last_decay = env_struct.time_now;
        });
    } else {
        auto vl_from = *vl_from_itr;
        asset new_levy = vl_from.levy_amount - amount;

        if (new_levy < asset(0, S(4, VOTE))) {
            new_levy = asset(0, S(4, VOTE));
        }

        fromlevies.modify(vl_from_itr, 0, [&]( auto& a ) {
            a.levy_amount = new_levy;
            a.last_decay = env_struct.time_now;
        });
    }
}

void trail::update_to_levy(account_name to, asset amount) {
    votelevies_table tolevies(N(eosio.trail), N(eosio.trail));
    auto vl_to_itr = tolevies.find(to);

    if (vl_to_itr == tolevies.end()) {
        tolevies.emplace(N(eosio.trail), [&]( auto& a ){
            a.voter = to;
            a.levy_amount = asset(0, S(4, VOTE));
            a.last_decay = env_struct.time_now;
        });
    } else {
        auto vl_to = *vl_to_itr;
        asset new_levy = vl_to.levy_amount + amount;

        tolevies.modify(vl_to_itr, 0, [&]( auto& a ) {
            a.levy_amount = new_levy;
            a.last_decay = env_struct.time_now;
        });
    }
}

asset trail::calc_decay(account_name voter, asset amount) {
    votelevies_table votelevies(N(eosio.trail), N(eosio.trail));
    auto vl_itr = votelevies.find(voter);

    uint32_t time_delta;

    if (vl_itr != votelevies.end()) {
        auto vl = *vl_itr;
        time_delta = env_struct.time_now - vl.last_decay;
        return asset(int64_t(time_delta / 60), S(4, VOTE));
    }

    return asset(0, S(4, VOTE));
}

#pragma endregion Reactions

//EOSIO_ABI(trail, )

extern "C" {
    void apply(uint64_t self, uint64_t code, uint64_t action) {
        trail trailservice(self);
        if(code == self && action == N(regtoken)) {
            execute_action(&trailservice, &trail::regtoken);
        } else if (code == self && action == N(unregtoken)) {
            execute_action(&trailservice, &trail::unregtoken);
        } else if (code == self && action == N(regvoter)) {
            execute_action(&trailservice, &trail::regvoter);
        } else if (code == self && action == N(unregvoter)) {
            execute_action(&trailservice, &trail::unregvoter);
        } else if (code == self && action == N(regballot)) {
            execute_action(&trailservice, &trail::regballot);
        } else if (code == self && action == N(unregballot)) {
            execute_action(&trailservice, &trail::unregballot);
        } else if (code == self && action == N(mirrorstake)) {
            execute_action(&trailservice, &trail::mirrorstake);
        } else if (code == self && action == N(castvote)) {
            execute_action(&trailservice, &trail::castvote);
        } else if (code == self && action == N(closevote)) {
            execute_action(&trailservice, &trail::closevote);
        } else if (code == self && action == N(nextcycle)) {
            execute_action(&trailservice, &trail::nextcycle);
        } else if (code == self && action == N(deloldvotes)) {
            execute_action(&trailservice, &trail::deloldvotes);
        } else if (code == N(eosio.token) && action == N(transfer)) { //NOTE: updates vote_levy after transfers
            auto args = unpack_action_data<transfer_args>();
            trailservice.update_from_levy(args.from, asset(args.quantity.amount, S(4, VOTE)));
            trailservice.update_to_levy(args.to, asset(args.quantity.amount, S(4, VOTE)));
        }
    } //end apply
}; //end dispatcher
