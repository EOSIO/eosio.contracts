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
	eosio_assert(new_environment.threshold_pass_voters >= 0 && new_environment.threshold_pass_voters <= 100, "threshold pass_voters must be between 0 and 100");
	eosio_assert(new_environment.threshold_pass_votes >= 0 && new_environment.threshold_pass_votes <= 100, "threshold pass_votes must be between 0 and 100");
	eosio_assert(new_environment.threshold_fee_voters >= 0 && new_environment.threshold_fee_voters <= 100, "threshold fee_voters must be between 0 and 100");
	eosio_assert(new_environment.threshold_fee_votes >= 0 && new_environment.threshold_fee_votes <= 100, "threshold fee_votes must be between 0 and 100");
	require_auth(_self);
	wpenv.set(new_environment, _self);
}

void workerproposal::getdeposit(name owner) {
    require_auth(owner);
	deposits_table deposits(_self, _self.value);
	auto d_itr = deposits.find(owner.value);
    eosio_assert(d_itr != deposits.end(), "Deposit not found");

	auto d = *d_itr;
    require_auth(d.owner);

	action(permission_level{_self, "active"_n}, "eosio.token"_n, "transfer"_n, make_tuple(
		_self,
		d.owner,
		d.escrow,
		std::string("return unused deposit")
	)).send();
	
	deposits.erase(d_itr);
}

void workerproposal::submit(name proposer, std::string title, uint16_t cycles, std::string ipfs_location, asset amount, name receiver) {
    require_auth(proposer);
	
	// calc fee
    uint64_t fee_amount = uint64_t(amount.amount) * uint64_t( wp_env_struct.fee_percentage ) / uint64_t(100);
    fee_amount = fee_amount > wp_env_struct.fee_min ? fee_amount :  wp_env_struct.fee_min;
	asset fee = asset(fee_amount, symbol("TLOS", 4));

	deposits_table deposits(_self, _self.value);
	auto d_itr = deposits.find(proposer.value);
	eosio_assert(d_itr != deposits.end(), "Deposit not found, please transfer your TLOS fee");
	auto d = *d_itr;
	eosio_assert(d.escrow >= fee, "Deposit amount is less than fee, please transfer more TLOS");

	if(d.escrow > fee) {
	    asset outstanding = d.escrow - fee;
		deposits.modify(d, same_payer, [&](auto& depo) {
			depo.escrow = outstanding;
		});
	} else {
		deposits.erase(d_itr);
	}

	ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
	uint32_t begin_time = now() + wp_env_struct.start_delay;
	uint32_t end_time = now() + wp_env_struct.start_delay + wp_env_struct.cycle_duration;
	uint64_t next_ballot_id = ballots.available_primary_key();
	action(permission_level{_self, "active"_n}, "eosio.trail"_n, "regballot"_n, make_tuple(
		_self,
		uint8_t(0),
		symbol("VOTE",4),
		begin_time,
		end_time,
		ipfs_location
	)).send();

    submissions_table submissions(_self, _self.value);
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

void workerproposal::claim(uint64_t sub_id) {
    submissions_table submissions(_self, _self.value);
    auto& sub = submissions.get(sub_id, "Worker Proposal Not Found");

	require_auth(sub.proposer);

    ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
    auto& bal = ballots.get(sub.ballot_id, "Ballot ID doesn't exist");
	
	proposals_table props_table("eosio.trail"_n, "eosio.trail"_n.value);
	auto& prop = props_table.get(bal.reference_id, "Proposal Not Found");

    eosio_assert(prop.end_time < now(), "Cycle is still open");
    
    eosio_assert(prop.status == uint8_t(0), "Proposal is closed");

    environment_singleton environment("eosio.trail"_n, "eosio.trail"_n.value);
    auto e = environment.get();

    asset outstanding = asset(0, symbol("TLOS", 4));
    asset total_votes = (prop.yes_count + prop.no_count + prop.abstain_count); //total votes cast on proposal
    asset non_abstain_votes = (prop.yes_count + prop.no_count); 

    //pass thresholds
    uint64_t voters_pass_thresh = (e.totals[1] * wp_env_struct.threshold_pass_voters) / 100;
    asset votes_pass_thresh = (non_abstain_votes * wp_env_struct.threshold_pass_votes) / 100;

    //fee refund thresholds
    uint64_t voters_fee_thresh = (e.totals[1] * wp_env_struct.threshold_fee_voters) / 100; 
    asset votes_fee_thresh = (total_votes * wp_env_struct.threshold_fee_votes) / 100; 

    auto updated_fee = sub.fee;

    // print("\n GET FEE BACK WHEN <<<< ", prop.yes_count, " >= ", votes_fee_thresh," && ", uint64_t(prop.unique_voters), " >= ", voters_fee_thresh);
    if( sub.fee && prop.yes_count.amount > 0 && prop.yes_count >= votes_fee_thresh && prop.unique_voters >= voters_fee_thresh) {
        if(sub.receiver == sub.proposer){
            outstanding += asset(int64_t(sub.fee), symbol("TLOS", 4));
        }else{
            action(permission_level{ _self, "active"_n }, "eosio.token"_n, "transfer"_n, make_tuple(
                _self,
                sub.proposer,
                outstanding,
                std::string("Worker proposal funds")
            )).send();
        }
        updated_fee = 0;
    }

    // print("\n GET MUNI WHEN <<<< ", prop.yes_count, " > ", votes_pass_thresh, " && ", uint64_t(prop.unique_voters), " >= ", voters_pass_thresh);
    if( prop.yes_count > votes_pass_thresh && prop.unique_voters >= voters_pass_thresh ) {
        outstanding += asset(int64_t(sub.amount), symbol("TLOS", 4));
    }
    
    // print("\n numbers : ", e.totals[1], " * ", wp_env_struct.threshold_pass_voters, " | ", wp_env_struct.threshold_fee_voters, " ---- ", total_votes, " ", votes_ratio, " ", prop.yes_count.amount, " ", prop.no_count.amount, " ", divider);
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

    if(prop.cycle_count == uint16_t(sub.cycles - 1)) { //Close ballot because it was the last cycle for the submission.
        // print("\n>>>>>>> CLOSE");
        uint8_t new_status = 1;
		action(permission_level{ _self, "active"_n }, "eosio.trail"_n, "closeballot"_n, make_tuple(
			_self,
			sub.ballot_id,
			new_status
		)).send();
    } else if(prop.cycle_count < uint16_t(sub.cycles - 1)) { //Start next cycle because number of cycles hasn't been reached.
        // print("\n>>>>>>> CYCLE");
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

// note : this gets called when eosio.saving transfers OUT tokens too 
// => deposits.owner eosio.saving will contain the entire sum of what was paid out , EVER (including fees and everything)
void workerproposal::transfer_handler(name from, asset quantity) {
	if(quantity.symbol == symbol("TLOS", 4)) {
		deposits_table deposits(_self, _self.value);
		auto d = deposits.find(from.value);

		if(d == deposits.end()) {
			deposits.emplace(get_self(), [&](auto& depo) {
				depo.owner = from;
				depo.escrow = quantity;
			});
		} else {
			deposits.modify(d, same_payer, [&](auto& depo) {
				depo.escrow += quantity;
			});
		}
	}

	print("\nDeposit Complete");
}

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

        if(code == self && action == name("claim").value) {
            execute_action(name(self), name(code), &workerproposal::claim);
        } else if (code == self && action == name("getdeposit").value) {
            execute_action(name(self), name(code), &workerproposal::getdeposit);
        } else if (code == self && action == name("submit").value) {
            execute_action(name(self), name(code), &workerproposal::submit);
        } else if (code == self && action == name("setenv").value) {
            execute_action(name(self), name(code), &workerproposal::setenv);
        } else if (code == name("eosio.token").value && action == name("transfer").value) {
            workerproposal work(name(self), name(code), ds);
            auto args = unpack_action_data<transfer_args>();
            work.transfer_handler(args.from, args.quantity);
        }
    } //end apply
}; //end dispatcher
