/**
 * The ratify/amend contract is used to submit proposals for ratifying and amending major documents in the Telos Network. Users register their
 * account through the Trail Service, where they will be issued a VoterID card that tracks and stores their vote participation. Once registered,
 * users can then cast votes equal to their weight of staked TLOS on proposals to update individual clauses within a document. Submitting a 
 * proposal requires a deposit of TLOS. The deposit will be refunded if proposal reaches a minimum threshold of participation and acceptance
 * by registered voters (even if the proposal itself fails to pass).
 * 
 * @author Craig Branscom
 * @copyright defined in telos/LICENSE.txt
 */

//#include <trail.voting.hpp>
//#include <trail.system.hpp>

#include <eosiolib/eosio.hpp>
#include <eosiolib/permission.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;

class [[eosio::contract("eosio.amend")]] ratifyamend : public contract {
    public:

        ratifyamend(name self, name code, datastream<const char*> ds);

        ~ratifyamend();

		[[eosio::action]]
        void insertdoc(string title, vector<string> clauses);

		[[eosio::action]]
        void makeproposal(string prop_title, uint64_t doc_id, uint8_t new_clause_num, string new_ipfs_url, name proposer);

		[[eosio::action]]
        void addclause(uint64_t prop_id, uint8_t new_clause_num, string new_ipfs_url, name proposer);

		[[eosio::action]]
        void linkballot(uint64_t prop_id, uint64_t ballot_id, name proposer);

		[[eosio::action]]
        void readyprop(uint64_t prop_id, name proposer);

	   	[[eosio::action]]
        void closeprop(uint64_t proposal_id, name proposer);

    protected:

        struct [[eosio::table, eosio::contract("eosio.amend")]] document {
            uint64_t document_id;
            string document_title;
            vector<string> clauses; //vector of ipfs urls
            uint32_t last_amend;

            uint64_t primary_key() const { return document_id; }
            EOSLIB_SERIALIZE(document, (document_id)(document_title)(clauses)(last_amend))
        };

        struct [[eosio::table, eosio::contract("eosio.amend")]] proposal {
            uint64_t proposal_id;
            uint64_t ballot_id;
            name proposer;

            uint64_t document_id; //document to amend
            string proposal_title;
            vector<uint8_t> new_clause_nums; //maps each successive key to respective ipfs_url
            vector<string> new_ipfs_urls;

            uint32_t begin_time;
            uint32_t end_time;
            uint8_t status; // 0 = BUILDING, 1 = READY, 2 = PASS, 3 = FAIL

            uint64_t primary_key() const { return proposal_id; }
            EOSLIB_SERIALIZE(proposal, (proposal_id)(ballot_id)(proposer)
                (document_id)(proposal_title)(new_clause_nums)(new_ipfs_urls)
                (begin_time)(end_time)(status))
        };

        struct [[eosio::table("configs"), eosio::contract("eosio.amend")]] config {
            name publisher;

            uint32_t expiration_length;

            uint64_t primary_key() const { return publisher.value; }
            EOSLIB_SERIALIZE(config, (publisher)
                (expiration_length))
        };

    #pragma region Tables

    typedef multi_index<"documents"_n, document> documents_table;

    typedef multi_index<"proposals"_n, proposal> proposals_table;

    typedef singleton<"configs"_n, config> configs_singleton;
    configs_singleton configs;
    config configs_struct;

    #pragma endregion Tables

    #pragma region Helper_Functions

    void update_thresh();

    void update_doc(uint64_t document_id, vector<uint8_t> new_clause_nums, vector<string> new_ipfs_urls);

    proposals_table::const_iterator find_proposal(uint64_t proposal_id) {
        proposals_table proposals(_self, _self.value);
        auto p = proposals.find(proposal_id);

        if (p != proposals.end()) {
            return p;
        }

        return proposals.end();
    }

    #pragma endregion Helper_Functions
};
