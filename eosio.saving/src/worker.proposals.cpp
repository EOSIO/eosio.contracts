#include <worker.proposals.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using eosio::print;

workerproposal::workerproposal(name self, name code, datastream<const char*> ds) : contract(self, code, ds), wpenv(self, self.value) {
    if (!wpenv.exists()) {

        wp_env_struct = wp_env{
			_self,
            2500000, // cycle duration in seconds (default 2,500,000 or 5,000,000 blocks or ~29 days)
            3, // percent from requested amount (default 3%)
            500000, // minimum fee amount (default 50 TLOS)
			86400 // delay before voting starts on a submission in seconds (~1 day)
        };

        wpenv.set(wp_env_struct, _self);
    } else {
        wp_env_struct = wpenv.get();     
    }
}

workerproposal::~workerproposal() { }

void workerproposal::setenv(wp_env new_environment) {
	eosio_assert(new_environment.cycle_duration > 0, "cycle duraction must be a non-zero number");
	eosio_assert(new_environment.fee_percentage > 0, "fee_percentage must be a non-zero number");
	eosio_assert(new_environment.start_delay > 0, "start_delay must be a non-zero number");
	eosio_assert(new_environment.fee_min > 0, "fee_min must be a non-zero number");
	require_auth(_self);
	wpenv.set(new_environment, _self);
}

void workerproposal::submit(name proposer, std::string title, uint16_t cycles, std::string ipfs_location, asset amount, name receiver) {
    require_auth(proposer);
	
	// calc fee
    uint64_t fee_amount = uint64_t(amount.amount) * uint64_t( wp_env_struct.fee_percentage ) / uint64_t(100);
    fee_amount = fee_amount > wp_env_struct.fee_min ? fee_amount :  wp_env_struct.fee_min;

    // transfer the fee
    action(permission_level{ proposer, "active"_n }, "eosio.token"_n, "transfer"_n, make_tuple(
    	proposer,
        "eosio.saving"_n,
        asset(int64_t(fee_amount), symbol("TLOS", 4)),
        std::string("Worker Proposal Fee")
	)).send();
	
	ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
	uint32_t begin_time = now() + wp_env_struct.start_delay;
	uint32_t end_time = now() + wp_env_struct.cycle_duration;
	uint64_t next_ballot_id = ballots.available_primary_key();
	action(permission_level{_self, "active"_n}, "eosio.trail"_n, "regballot"_n, make_tuple(
		_self,
		0,
		symbol("VOTE", 4),
		begin_time,
		end_time,
		ipfs_location
	)).send();

    submissions submissions(_self, _self.value);
    submissions.emplace( proposer, [&]( submission& info ){
        info.id             = submissions.available_primary_key();
        info.ballot_id      = next_ballot_id;
        info.proposer       = proposer;
        info.receiver       = receiver;
        info.title          = title;
        info.ipfs_location  = ipfs_location;
        info.cycles         = cycles;
        info.amount         = uint64_t(amount.amount);
        info.fee            = fee_amount;
    });
}

// void workerproposal::linkballot(uint64_t prop_id, uint64_t ballot_id, name proposer) {
//     require_auth(proposer);

//     proposals proptable(_self, _self.value);
//     auto p = proptable.find(prop_id);
//     eosio_assert(p != proptable.end(), "Proposal with given id doesn't exist");
//     auto prop = *p;

//     ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
//     auto b = ballots.find(ballot_id);
//     eosio_assert(b != ballots.end(), "Ballot with given id doesn't exist");
//     auto bal = *b;

//     eosio_assert(bal.publisher == proposer, "Cannot link to a ballot made by another account");

//     proptable.modify(p, same_payer, [&]( auto& a ) {
//         a.ballot_id     = bal.ballot_id;
//         a.begin_time    = bal.begin_time;
//         a.end_time      = bal.end_time;
//         a.status        = 1; // ACTIVE
//     });

//     print("\nBallot Link: SUCCESS");
// }

void workerproposal::claim(uint64_t sub_id) {
    submissions submissions(_self, _self.value);
    auto sub = submissions.get(sub_id, "Worker Proposal Not Found");

	require_auth(sub.proposer);

    ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
    auto bal = ballots.get(sub.ballot_id, "Ballot ID doesn't exist");
	
	proposals_table props_table("eosio.trail"_n, "eosio.trail"_n.value);
	auto prop = props_table.get(bal.reference_id, "Proposal Not Found");

    eosio_assert(prop.end_time < now(), "Cycle is still open");
    
    eosio_assert(prop.status == 1, "Proposal is closed");

    environment_singleton environment("eosio.trail"_n, "eosio.trail"_n.value);
    auto e = environment.get();

    asset outstanding = asset(0, symbol("TLOS", 4));
    asset total_votes = (prop.yes_count + prop.no_count + prop.abstain_count); //total votes cast on proposal

    //pass thresholds
    uint64_t quorum_thresh = (e.totals[1] / 10); // 10% of all registered voters

    //fee refund thresholds
    uint64_t q_fee_refund_thresh = (e.totals[1] / 20); //0.1% of all TLOS tokens voting // 5% of voters for test (TODO: change to votes quorum)
    asset p_fee_refund_thresh = total_votes / 5; //20% of total votes

    if( sub.fee && prop.yes_count.amount > 0 && prop.yes_count >= p_fee_refund_thresh && prop.unique_voters >= q_fee_refund_thresh) {
        outstanding += asset(int64_t(sub.fee), symbol("TLOS", 4));
        sub.fee = 0;
    }

    if(prop.yes_count > prop.no_count && prop.unique_voters >= quorum_thresh) {
        outstanding += asset(int64_t(sub.amount), symbol("TLOS", 4));
    }

    if(outstanding.amount > 0) {
        action(permission_level{ _self, "active"_n }, "eosio.token"_n, "transfer"_n, make_tuple(
            _self,
            sub.receiver,
            outstanding,
            std::string("Worker proposal funds")
        )).send();
    } else {
        print("\nNothing to claim from the last cycle");
    }

    if(prop.cycle_count == sub.cycles - 1) { //Close ballot because it was the last cycle for the submission.
        prop.status = 1;
		action(permission_level{ _self, "active"_n }, "eosio.trail"_n, "closeballot"_n, make_tuple(
			_self,
			sub.ballot_id,
			prop.status
		)).send();
    } else if(prop.cycle_count < sub.cycles - 1) { //Start next cycle because number of cycles hasn't been reached.
		uint32_t begin_time = now() + wp_env_struct.start_delay;
		uint32_t end_time = now() + wp_env_struct.cycle_duration;
		action(permission_level{ _self, "active"_n }, "eosio.trail"_n, "nextcycle"_n, make_tuple(
			_self,
			sub.ballot_id,
			begin_time,
			end_time
		)).send();
	}

    submissions.modify(sub, same_payer, [&]( auto& a ) {
        a.fee = sub.fee;
    });
}

EOSIO_DISPATCH(workerproposal, (submit)(claim))
