/**
 * Arbitration Implementation. See function bodies for further notes.
 * 
 * @author Craig Branscom, Peter Bue, Ed Silva, Douglas Horn
 * @copyright defined in telos/LICENSE.txt
 */

#include <arbitration/arbitration.hpp>

arbitration::arbitration(name s, name code, datastream<const char *> ds)
    : eosio::contract(s, code, ds) {

    }

arbitration::~arbitration() {}

void arbitration::setconfig(uint16_t max_arbs, uint32_t default_time, vector<int64_t> fees) { }
void arbitration::applyforarb(name candidate, string creds_ipfs_url) { } //TODO: rename to arbapply(), newarbapp()
void arbitration::cancelarbapp(name candidate) { } //TODO: rename to arbunapply(), rmvarbapply()
void arbitration::voteforarb(name candidate, uint16_t direction, name voter) { }
void arbitration::endelection(name candidate) { } //automate in constructor?
void arbitration::filecase(name claimant, uint16_t class_suggestion, string ev_ipfs_url) { } //NOTE: filing a case doesn't require a respondent
void arbitration::addclaim(uint64_t case_id, uint16_t class_suggestion, string ev_ipfs_url, name claimant) { } //NOTE: adds subsequent claims to a case
void arbitration::removeclaim(uint64_t case_id, uint16_t claim_num, name claimant){ } //NOTE: Claims can only be removed by a claimant during case setup. Enfore that have atleas one claim before awaiting arbs
void arbitration::shredcase(uint64_t case_id, name claimant) { } //NOTE: member-level case removal, called during CASE_SETUP
void arbitration::readycase(uint64_t case_id, name claimant) { }
void arbitration::vetoarb(uint64_t case_id, name arb, name selector) { }
void arbitration::dismisscase(uint64_t case_id, name arb, string ipfs_url) { } //TODO: require rationale?
void arbitration::closecase(uint64_t case_id, name closer, string ipfs_url){ } //TODO: require decision?
void arbitration::dismissev(uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb, string ipfs_url) {  } //NOTE: moves to dismissed_evidence table
void arbitration::acceptev(uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb, string ipfs_url) { } //NOTE: moves to evidence_table and assigns ID
void arbitration::arbstatus(uint16_t new_status, name arb) { }
void arbitration::casestatus(uint64_t case_id, uint16_t new_status, name arb) { }
void arbitration::changeclass(uint64_t case_id, uint16_t claim_index, uint16_t new_class, name arb) { }
void arbitration::recuse(uint64_t case_id, string rationale, name arb) { }
void arbitration::dismissarb(name arb) { }

EOSIO_DISPATCH( arbitration, (setconfig)(applyforarb)(cancelarbapp)(voteforarb)(endelection)
                             (filecase)(addclaim)(removeclaim)(shredcase)(readycase)
                             (vetoarb)(dismisscase)(closecase)(dismissev)(acceptev)
                             (arbstatus)(casestatus)(changeclass)(recuse)(dismissarb) )
