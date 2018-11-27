#include <worker.proposals.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using eosio::print;

workerproposal::workerproposal(name self, name code, datastream<const char*> ds) : contract(self, code, ds), wpenv(self, self.value) {
    if (!wpenv.exists()) {

        wp_env_struct = wp_env{
			_self,
            2500000,    // cycle duration in seconds (default 2,500,000 or 5,000,000 blocks or ~29 days)
            3,          // percent from requested amount (default 3%)
            500000,     // minimum fee amount (default 50 TLOS)
			86400,      // delay before voting starts on a submission in seconds (~1 day)
            5,          // % of all registered voters to pass (minimum, including exactly this value)
            50,         // % yes over no, to consider it passed (strictly over this value)
            4,          // % of all registered voters to refund fee (minimum, including exactly this value)
            20          // % of yes to give fee back
        };

        wpenv.set(wp_env_struct, _self);
    } else {
        wp_env_struct = wpenv.get();     
    }
}

workerproposal::~workerproposal() { }

void workerproposal::setenv(wp_env new_environment) {
	eosio_assert(new_environment.cycle_duration > 0, "cycle duration must be a non-zero number");
	eosio_assert(new_environment.fee_percentage > 0, "fee_percentage must be a non-zero number");
	eosio_assert(new_environment.start_delay > 0, "start_delay must be a non-zero number");
	eosio_assert(new_environment.fee_min > 0, "fee_min must be a non-zero number");
	eosio_assert(new_environment.threshold_pass_voters >= 0 && new_environment.threshold_pass_voters <= 100, "threshold_pass_voters must be between 0 and 100");
	eosio_assert(new_environment.threshold_pass_votes >= 0 && new_environment.threshold_pass_votes <= 100, "threshold_pass_votes must be between 0 and 100");
	eosio_assert(new_environment.threshold_fee_voters >= 0 && new_environment.threshold_fee_voters <= 100, "threshold_fee_voters must be between 0 and 100");
	eosio_assert(new_environment.threshold_fee_votes >= 0 && new_environment.threshold_fee_votes <= 100, "threshold_fee_votes must be between 0 and 100");
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
		uint8_t(0),
		symbol("VOTE",4),
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
    auto& sub = submissions.get(sub_id, "Worker Proposal Not Found");

	require_auth(sub.proposer);

    ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
    auto& bal = ballots.get(sub.ballot_id, "Ballot ID doesn't exist");
	
	proposals_table props_table("eosio.trail"_n, "eosio.trail"_n.value);
	auto& prop = props_table.get(bal.reference_id, "Proposal Not Found");

    print( "\n",
        "prop_id:", prop.prop_id,
        ", publisher:", prop.publisher,
        ", info_url:", string(prop.info_url),
        ", no_count:", prop.no_count,
        ", yes_count:", prop.yes_count,
        ", abstain_count:", prop.abstain_count,
        ", unique_voters:", uint64_t(prop.unique_voters),
        ", begin_time:", uint64_t(prop.begin_time),
        ", end_time:", uint64_t(prop.end_time),
        ", cycle_count:", uint64_t(prop.cycle_count),
        ", status:", uint64_t(prop.status)
    );
    eosio_assert(prop.end_time < now(), "Cycle is still open");
    
    eosio_assert(prop.status == uint8_t(0), "Proposal is closed");

    environment_singleton environment("eosio.trail"_n, "eosio.trail"_n.value);
    auto e = environment.get();

    asset outstanding = asset(0, symbol("TLOS", 4));
    asset total_votes = (prop.yes_count + prop.no_count + prop.abstain_count); //total votes cast on proposal

    //pass thresholds
    uint64_t quorum_thresh = (e.totals[1] * wp_env_struct.threshold_pass_voters) / 100;
    auto divider = prop.yes_count.amount + prop.no_count.amount;
    if(divider < 0) divider = 1;
    double votes_ratio = (prop.yes_count.amount / divider);

    //fee refund thresholds
    uint64_t q_fee_refund_thresh = (e.totals[1] * wp_env_struct.threshold_fee_voters) / 100; 
    asset p_fee_refund_thresh = (total_votes * wp_env_struct.threshold_fee_votes) / 100; 

    print("nums : ", e.totals[1], " * ", wp_env_struct.threshold_pass_voters, " | ", wp_env_struct.threshold_fee_voters, " ---- ", total_votes, " ", votes_ratio);

    auto updated_fee = sub.fee;
    if( sub.fee && prop.yes_count.amount > 0 && prop.yes_count >= p_fee_refund_thresh && prop.unique_voters >= q_fee_refund_thresh) {
        print("\n GET FEE BACK <<<< ", int64_t(sub.fee), " ", prop.yes_count," ", uint64_t(prop.unique_voters), " >= ", q_fee_refund_thresh);
        outstanding += asset(int64_t(sub.fee), symbol("TLOS", 4));
        updated_fee = 0;
    }

    if( votes_ratio > (wp_env_struct.threshold_pass_votes / 100) && prop.unique_voters >= quorum_thresh ) {
        print("\n GET MUNI <<<< ", votes_ratio, " > ", (wp_env_struct.threshold_pass_votes / 100)," ", uint64_t(prop.unique_voters), " >= ", quorum_thresh);
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
        print("\n>>>>>>> CLOSE");
        uint8_t new_status = 1;
		action(permission_level{ _self, "active"_n }, "eosio.trail"_n, "closeballot"_n, make_tuple(
			_self,
			sub.ballot_id,
			new_status
		)).send();
    } else if(prop.cycle_count < sub.cycles - 1) { //Start next cycle because number of cycles hasn't been reached.
        print("\n>>>>>>> CYCLE");
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
        a.fee = updated_fee;
    });
}

EOSIO_DISPATCH(workerproposal, (submit)(claim)(setenv))
