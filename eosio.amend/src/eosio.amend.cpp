#include <eosio.amend.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/print.hpp>

ratifyamend::ratifyamend(name self, name code, datastream<const char*> ds) : contract(self, code, ds), configs(self, self.value) {
    if (!configs.exists()) {
        configs_struct = config{
            _self, //publisher
            uint32_t(5000) //expiration_length in seconds (default is 5,000,000 or ~58 days)
        };
        configs.set(configs_struct, _self);
    } else {
        configs_struct = configs.get();     
    }
}

ratifyamend::~ratifyamend() {}

void ratifyamend::insertdoc(string title, vector<string> clauses) {
    require_auth(_self); //only contract owner can insert new document
    
    documents_table documents(_self, _self.value);

    uint64_t doc_id = documents.available_primary_key();

    documents.emplace(_self, [&]( auto& a ){
        a.document_id = doc_id;
        a.document_title = title;
        a.clauses = clauses;
    });

    print("\nDocument Insertion: SUCCESS");
    print("\nAssigned Document ID: ", doc_id);
}

void ratifyamend::makeproposal(string prop_title, uint64_t doc_id, uint8_t new_clause_num, string new_ipfs_url, name proposer) {
    require_auth(proposer);

    documents_table documents(_self, _self.value);
    auto d = documents.find(doc_id);
    eosio_assert(d != documents.end(), "Document Not Found");
    auto doc = *d;

    eosio_assert(new_clause_num <= doc.clauses.size() + 1 && new_clause_num >= 0, "new clause num is not valid");

    //NOTE: 100.0000 TLOS fee, refunded if proposal passes or meets specified lower thresholds
    action(permission_level{ proposer, "active"_n }, "eosio.token"_n, "transfer"_n, make_tuple(
    	proposer,
        _self,
        asset(int64_t(1000000), symbol("TLOS", 4)),
        std::string("Ratify/Amend Proposal Fee")
	)).send();

    proposals_table proposals(_self, _self.value);
    auto prop_id = proposals.available_primary_key();

    vector<uint8_t> clause_nums; 
    clause_nums.push_back(new_clause_num);
    
    vector<string> clause_urls;
    clause_urls.push_back(new_ipfs_url);

    proposals.emplace(proposer, [&]( auto& a ){
        a.proposal_id = prop_id;
        a.ballot_id = 0;
        a.proposer = proposer;

        a.document_id = doc_id;
        a.proposal_title = prop_title;
        a.new_clause_nums = clause_nums;
        a.new_ipfs_urls = clause_urls;

        a.begin_time = 0;
        a.end_time = 0;
        a.status = 0;
    });

    print("\nProposal: SUCCESS");
    print("\nAssigned Proposal ID: ", prop_id);
}

void ratifyamend::addclause(uint64_t prop_id, uint8_t new_clause_num, string new_ipfs_url, name proposer) {
    require_auth(proposer);

    proposals_table proposals(_self, _self.value);
    auto p = proposals.find(prop_id);
    eosio_assert(p != proposals.end(), "proposal doesn't exist");
    auto prop = *p;

    eosio_assert(prop.proposer == proposer, "can't add clauses to proposal you don't own");
    eosio_assert(prop.status == 0, "proposal is no longer in building stage");

    documents_table documents(_self, _self.value);
    auto d = documents.find(prop.document_id);
    eosio_assert(d != documents.end(), "Document Not Found");
    auto doc = *d;

    eosio_assert(new_clause_num <= doc.clauses.size() + 1 && new_clause_num >= 0, "new clause num is not valid");
    bool existing_clause = false;

    for (int i = 0; i < prop.new_clause_nums.size(); i++) {
        if (prop.new_clause_nums[i] == new_clause_num) {
            existing_clause = true;
        }
    }

    eosio_assert(existing_clause = false, "clause number to add already exists in proposal");

    prop.new_clause_nums.push_back(new_clause_num);
    prop.new_ipfs_urls.push_back(new_ipfs_url);

    proposals.modify(p, same_payer, [&]( auto& a ) {
        a.new_clause_nums = prop.new_clause_nums;
        a.new_ipfs_urls = prop.new_ipfs_urls;
    });

    print("\nAdd Clause: SUCCESS");
}

void ratifyamend::linkballot(uint64_t prop_id, uint64_t ballot_id, name proposer) {
    require_auth(proposer);

    proposals_table proposals(_self, _self.value);
    auto p = proposals.find(prop_id);
    eosio_assert(p != proposals.end(), "proposal with given id doesn't exist");
    auto prop = *p;

    ballots_table ballots(_self, _self.value);
    auto b = ballots.find(ballot_id);
    eosio_assert(b != ballots.end(), "ballot with given id doesn't exist");
    auto bal = *b;

    eosio_assert(bal.publisher == proposer, "cannot link to a ballot made by another account");

    proposals.modify(p, same_payer, [&]( auto& a ) {
        a.ballot_id = bal.ballot_id;

        a.begin_time = bal.begin_time;
        a.end_time = bal.end_time;
    });

    print("\nBallot Link: SUCCESS");
}

void ratifyamend::readyprop(uint64_t prop_id, name proposer) {
    require_auth(proposer);

    proposals_table proposals(_self, _self.value);
    auto p = proposals.find(prop_id);
    eosio_assert(p != proposals.end(), "Proposal Not Found");
    auto prop = *p;

    eosio_assert(prop.status == 0, "proposal is no longer in building stage");

    proposals.modify(p, same_payer, [&]( auto& a ) {
        a.status = uint8_t(1);
    });

    print("\nReady Proposal: SUCCESS");
}

void ratifyamend::closeprop(uint64_t proposal_id, name proposer) {
    proposals_table proposals(_self, _self.value);
    auto p = proposals.find(proposal_id);
    eosio_assert(p != proposals.end(), "Proposal Not Found");
    auto prop = *p;

    ballots_table ballots(_self, _self.value);
    auto b = ballots.find(prop.ballot_id);
    eosio_assert(b != ballots.end(), "Ballot ID doesn't exist");
    auto bal = *b;

    eosio_assert(bal.end_time < now(), "Proposal is still open");
    eosio_assert(prop.status == 0 && bal.status == 0, "Proposal is already closed");

    environment_singleton environment(_self, _self.value);
    auto e = environment.get();

    asset total_votes = (bal.yes_count + bal.no_count + bal.abstain_count); //total votes cast on proposal

    //pass thresholds
    uint64_t quorum_thresh = (e.total_voters / 20); // 5% of all registered voters
    asset pass_thresh = ((bal.yes_count + bal.no_count) / 3) * 2; // 66.67% yes votes over no votes

    //refund thresholds - both must be met for a refund - proposal pass triggers automatic refund
    uint64_t q_refund_thresh = (e.total_voters / 25); //4% of all registered voters
    asset p_refund_thresh = total_votes / 4; //25% yes votes of total_votes

    uint8_t result_status = 2;

    if (bal.unique_voters >= quorum_thresh && bal.yes_count >= pass_thresh) { //proposal passed, refund granted

        proposals.modify(p, same_payer, [&]( auto& a ) {
            a.status = 1;
        });

        action(permission_level{ _self, "active"_n }, "eosio.token"_n, "transfer"_n, make_tuple(
            _self,
            prop.proposer,
            asset(int64_t(1000000), symbol("TLOS", 4)),
            std::string("Ratify/Amend Proposal Fee Refund")
        )).send();

        update_doc(prop.document_id, prop.new_clause_nums, prop.new_ipfs_urls);

        result_status = 1;

    } else if (bal.unique_voters >= q_refund_thresh && bal.yes_count >= p_refund_thresh) { //proposal failed, refund granted

        proposals.modify(p, same_payer, [&]( auto& a ) {
            a.status = 2;
        });

        action(permission_level{ _self, "active"_n }, "eosio.token"_n, "transfer"_n, make_tuple(
            _self,
            prop.proposer,
            asset(int64_t(1000000), symbol("TLOS", 4)),
            std::string("Ratify/Amend Proposal Fee Refund")
        )).send();
        
    } else { //proposal failed, refund witheld

        proposals.modify(p, same_payer, [&]( auto& a ) {
            a.status = 2;
        });

        print("\nProposal refund witheld");
    }

    //NOTE: for now, called separately by proposer
    //Inline action to Trail to close vote
    // action(permission_level{ proposer, N(active) }, N(eosio.trail), N(closevote), make_tuple(
    //     prop.proposer,
    //     prop.ballot_id,
    //     result_status
    // )).send();
}

#pragma region Helper_Functions

void ratifyamend::update_doc(uint64_t document_id, vector<uint8_t> new_clause_nums, vector<string> new_ipfs_urls) {
    documents_table documents(_self, _self.value);
    auto d = documents.find(document_id);
    auto doc = *d;

    auto doc_size = doc.clauses.size();
    for (int i = 0; i < new_clause_nums.size(); i++) {
        
        if (new_clause_nums[i] < doc.clauses.size()) { //update existing clause
            doc.clauses[new_clause_nums[i]] = new_ipfs_urls.at(i);
        } else { //add new clause
            doc.clauses.push_back(new_ipfs_urls.at(i));
        }
    }

    documents.modify(d, same_payer, [&]( auto& a ) {
        a.clauses = doc.clauses;
    });
}

#pragma endregion Helper_Functions

EOSIO_DISPATCH(ratifyamend, (insertdoc)(makeproposal)(addclause)(linkballot)(closeprop))
