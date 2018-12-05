/**
 * Arbitration Implementation. See function bodies for further notes.
 * 
 * @author Craig Branscom, Peter Bue, Ed Silva, Douglas Horn
 * @copyright defined in telos/LICENSE.txt
 */

#include <eosio.arbitration/eosio.arbitration.hpp>

arbitration::arbitration(name s, name code, datastream<const char *> ds)
    : eosio::contract(s, code, ds), configs(_self, _self.value) {

  _config = configs.exists() ? configs.get() : get_default_config();
}

arbitration::~arbitration() {
  if (configs.exists()) configs.set(_config, get_self());
}

void arbitration::setconfig(uint16_t max_elected_arbs, uint32_t election_duration, 
uint32_t start_election, uint32_t arbitrator_term_length, vector<int64_t> fees) {
  require_auth("eosio"_n);

  eosio_assert(max_elected_arbs < uint16_t(21), "Maximum elected arbitrators must be less than 22."); 
  eosio_assert(max_elected_arbs > uint16_t(0), "Arbitraitors must be greater than 0");
  _config = config{get_self(),       // publisher
                   max_elected_arbs,
                   election_duration,
                   start_election,
                   fees,
                   arbitrator_term_length,
                   now()};

  print("\nSettings Configured: SUCCESS");
}

void arbitration::initelection() {
  require_auth("eosio"_n);

  eosio_assert(!_config.auto_start_election, "Election is on auto start mode.");

  ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
  
  _config.ballot_id = ballots.available_primary_key();
  
  _config.auto_start_election = true;

  arbitrators_table arbitrators(_self, _self.value);

  uint8_t available_seats = 0;
  if (has_available_seats(arbitrators, available_seats)) {
    start_new_election(available_seats);
  }

  print("\nElection started: SUCCESS");
}

void arbitration::regarb(name candidate, string creds_ipfs_url) {
  require_auth(candidate);
  
  ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
  auto b = ballots.get(_config.ballot_id, "ballot doesn't exist");

  leaderboards_table leaderboards("eosio.trail"_n, "eosio.trail"_n.value);
  auto board = leaderboards.get(b.reference_id, "leaderboard doesn't exist");

  eosio_assert(board.status != uint8_t(CLOSED), "A new hasn't started. Use initelection action to start a new election.");

  candidates_table candidates(_self, _self.value);

  auto c = candidates.find(candidate.value);
  eosio_assert(c == candidates.end(), "Candidate is already an applicant");

  arbitrators_table arbitrators(_self, _self.value);
  auto arb = arbitrators.find(candidate.value);

  if (arb != arbitrators.end()) {
    eosio_assert(now() < arb->term_length, "Arbitrator seat didn't expire");

    arbitrators.modify(arb, same_payer, [&](auto &a) {
      a.arb_status = SEAT_EXPIRED;
    });
  }

  if(now() < board.begin_time) {
    action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "addcandidate"_n,
         make_tuple(get_self(), 
           _config.ballot_id, 
           candidate, 
           creds_ipfs_url
          )
        ).send();
  }
  
  candidates.emplace(_self, [&](auto &c) {
    c.cand_name = candidate;
    c.credential_link = creds_ipfs_url;
    c.applied_time = now();
  });

  print("\nArb Application: SUCCESS");
}

void arbitration::unregarb(name candidate) {
  require_auth(candidate);
  
  candidates_table candidates(_self, _self.value);
  auto c = candidates.find(candidate.value);  

  eosio_assert(c != candidates.end(), "Candidate isn't an applicant");

  ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
  auto b = ballots.get(_config.ballot_id, "ballot doesn't exist");

  leaderboards_table leaderboards("eosio.trail"_n, "eosio.trail"_n.value);
  auto board = leaderboards.get(b.reference_id, "leaderboard doesn't exist");
  
  if(now() < board.begin_time) {
    action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "rmvcandidate"_n,
      make_tuple(get_self(), 
        _config.ballot_id, 
        candidate
      )
    ).send();
    candidates.erase(c);
  }

  print("\nCancel Application: SUCCESS");
}

void arbitration::endelection(name candidate) {
   require_auth(candidate);
   
   ballots_table ballots("eosio.trail"_n, "eosio.trail"_n.value);
   auto b = ballots.get(_config.ballot_id, "ballot doesn't exist");

   leaderboards_table leaderboards("eosio.trail"_n, "eosio.trail"_n.value);
   auto board = leaderboards.get(b.reference_id, "leaderboard doesn't exist");
   
   eosio_assert(now() > board.end_time, "election isn't ended.");
   
   // sort board candidates by votes
   auto board_candidates = board.candidates;

   sort(board_candidates.begin(), board_candidates.end(), [](const auto &c1, const auto &c2) { return c1.votes >= c2.votes; });
   
   //resolve tie clonficts.
   if(board_candidates.size() > board.available_seats) {
      board_candidates.resize(board.available_seats + 1);
      auto first_cand_out = board_candidates[board_candidates.size() - 1];

      // remove candidates that are tied with first_cand_out
      uint8_t tied_cands = 1;
      for(auto i = board_candidates.size() - 2; i >= 0; i--) {
         auto cand = board_candidates[i];
         if(cand.votes == first_cand_out.votes) tied_cands++;
      }

      if(tied_cands > 0) board_candidates.resize(board_candidates.size() - tied_cands);
   
   }

   candidates_table candidates(_self, _self.value);
   
   auto cand = candidates.find(candidate.value);
   eosio_assert(cand != candidates.end(), "Candidate isn't an applicant.");
   
   arbitrators_table arbitrators(_self, _self.value);
   
   std::vector<permission_level_weight> arbs_perms;  
   // get available seats (up to 21)
  
   // in case there are still candidates (not all tied)
   if(board_candidates.size() > 0) {
      for (int i = 0; i < board.available_seats && i < board_candidates.size(); i++) {
         auto cand_votes = board_candidates[i].votes.amount;
         if(cand_votes == 0) continue;

         name cand_name = board_candidates[i].member;  
         auto c = candidates.find(cand_name.value);
         
         if (c != candidates.end()) {
            // remove candidates from candidates table / arbitration contract
            candidates.erase(c);
            
            // add candidates to arbitration table / arbitration contract
            add_arbitrator(arbitrators, cand_name);
            
            // add ard to list of permissions  
            arbs_perms.emplace_back( permission_level_weight { permission_level{  cand_name,  "active"_n }, 1 });
         
         } else {
            print("\ncandidate: ", name{cand_name}, " was not found.");
         }
      }

      // add current arbitrators to permission list
      for(const auto &a : arbitrators) {
        if(a.arb_status != uint16_t(SEAT_EXPIRED)) {
          arbs_perms.emplace_back( permission_level_weight { permission_level{  a.arb,  "active"_n }, 1 });
        }
      }

      // permissions need to be sorted 
      sort(arbs_perms.begin(), arbs_perms.end(), [](const auto &first, const auto &second) { return first.permission.actor.value < second.permission.actor.value; });

      // review update auth permissions and weights.
      uint32_t weight = arbs_perms.size() > 0 ? ( 2 * arbs_perms.size() ) / 3 + 1 : 0;
      action(permission_level{get_self(), "owner"_n }, "eosio"_n, "updateauth"_n,
               std::make_tuple(
                  get_self(), 
                  name("active"), 
                  name("owner"),
                  authority {
                     weight, 
                     std::vector<key_weight>{},
                     arbs_perms,
                     std::vector<wait_weight>{}
                     }
                  )
            ).send();
   }

   // close ballot action.
   action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "closeballot"_n, 
            make_tuple(
               get_self(), 
               _config.ballot_id, 
               uint8_t(CLOSED)
               )
         ).send(); 

   // start new election with remaining candidates 
   // and new candidates that registered after past election had started.
   uint8_t available_seats = 0;
   auto remaining_candidates = distance(candidates.begin(), candidates.end());

   if ( remaining_candidates > 0 && has_available_seats(arbitrators, available_seats) ) {
      _config.ballot_id = ballots.available_primary_key();
      
      start_new_election(available_seats);

      for (const auto &c : candidates) {
         action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "addcandidate"_n,
            make_tuple(get_self(), 
               _config.ballot_id, 
               c, 
               c.credential_link
            )
         ).send(); 
      }
      
      print("\nA new election has started.");
   } else {
      for(const auto &cand : candidates) {
        candidates.erase(c);
      }
      _config.auto_start_election = false;
      print("\nThere aren't enough seats available or candidates to start a new election.\nUse init action to start a new election.");
   }
}

void arbitration::filecase(name claimant, uint16_t class_suggestion, string ev_ipfs_url) {
  require_auth(claimant);
	eosio_assert(class_suggestion >= UNDECIDED && class_suggestion <= MISC, "class suggestion must be between 0 and 14"); //TODO: improve this message to include directions
	validate_ipfs_url(ev_ipfs_url);

	action(permission_level{ claimant, "active"_n}, "eosio.token"_n, "transfer"_n, make_tuple(
		claimant,
		get_self(),
		asset(int64_t(1000000), symbol("TLOS", 4)), //TODO: Check initial filing fee
		std::string("Arbitration Case Filing Fee")
	)).send();

	casefiles_table casefiles(_self, _self.value);
  vector<name> arbs; //empty vector of arbitrator accounts
	vector<claim> claims;
	auto case_id = casefiles.available_primary_key();
    casefiles.emplace(_self, [&]( auto& a ){
        a.case_id = case_id;
        a.claimant = claimant;
		    a.respondant = name(0);
        a.claims = claims;
        a.arbitrators = arbs;
        a.case_status = CASE_SETUP;
        a.last_edit = now();
    });

	addclaim(case_id, class_suggestion, ev_ipfs_url, claimant);

  print("\nCased Filed!");
} 

void arbitration::addclaim(uint64_t case_id, uint16_t class_suggestion, string ev_ipfs_url, name claimant) { 
  require_auth(claimant);
	eosio_assert(class_suggestion >= UNDECIDED && class_suggestion <= MISC, "class suggestion must be between 0 and 14"); //TODO: improve this message to include directions
	validate_ipfs_url(ev_ipfs_url);

	casefiles_table casefiles(_self, _self.value);
	auto c = casefiles.get(case_id, "Case Not Found");
	print("\nProposal Found!");

	require_auth(c.claimant);
	eosio_assert(c.case_status == CASE_SETUP, "claims cannot be added after CASE_SETUP is complete.");

	vector<uint64_t> accepted_ev_ids;

	auto new_claims = c.claims;
	new_claims.emplace_back(claim { class_suggestion, vector<string>{ev_ipfs_url}, accepted_ev_ids, UNDECIDED });
	casefiles.modify(c, same_payer, [&](auto& a) { 
		a.claims = new_claims;
	});

	print("\nClaim Added!");
}

void arbitration::removeclaim(uint64_t case_id, uint16_t claim_num, name claimant) {
  require_auth(claimant);

	casefiles_table casefiles(_self, _self.value);
	auto c = casefiles.get(case_id, "Case Not Found");
	
	require_auth(c.claimant);
	eosio_assert(c.case_status == CASE_SETUP, "claims cannot be removed after CASE_SETUP is complete.");

	vector<claim> new_claims = c.claims;
	eosio_assert(new_claims.size() > 0, "no claims to remove");
	eosio_assert(claim_num < new_claims.size(), "claim number does not exist");
	new_claims.erase(new_claims.begin() + claim_num);

	casefiles.modify(c, same_payer, [&](auto& a) {
		a.claims = new_claims;
	});

	print("\nClaim Removed!");
}

void arbitration::shredcase(uint64_t case_id, name claimant) {
  require_auth(claimant);

  casefiles_table casefiles(_self, _self.value);
  auto c_itr = casefiles.find(case_id);
  print("\nProposal Found!");
  eosio_assert(c_itr != casefiles.end(), "Case Not Found");

  require_auth(c_itr->claimant);
  eosio_assert(c_itr->case_status == CASE_SETUP, "cases can only be shredded during CASE_SETUP");

  casefiles.erase(c_itr);

  print("\nCase Shredded!");
}

void arbitration::readycase(uint64_t case_id, name claimant) {
  require_auth(claimant);

  casefiles_table casefiles(_self, _self.value);
  auto c = casefiles.get(case_id, "Case Not Found");

  require_auth(c.claimant);
  eosio_assert(c.case_status == CASE_SETUP, "cases can only be readied during CASE_SETUP");
  eosio_assert(c.claims.size() >= 1, "cases must have atleast one claim");

  casefiles.modify(c, same_payer, [&](auto &a) { 
      c.case_status = AWAITING_ARBS; 
    });

  print("\nCase Readied!");
}

void arbitration::closecase(uint64_t case_id, name arb, string ipfs_url) {
  require_auth(arb);
  validate_ipfs_url(ipfs_url);

  casefiles_table casefiles(_self, _self.value);
  auto c = casefiles.get(case_id, "no case found for given case_id");
  eosio_assert(c.case_status == ENFORCEMENT, "case hasn't been enforced");

  auto arb_case = std::find(c.arbitrators.begin(), c.arbitrators.end(), arb);
  eosio_assert(arb_case != c.arbitrators.end(), "arbitrator isn't selected for this case.");

  auto new_ipfs_list = c.findings_ipfs;
  new_ipfs_list.emplace_back(ipfs_url);

  casefiles.modify(c, same_payer, [&](auto &cf) {
    cf.findings_ipfs = new_ipfs_list;
    cf.case_status = COMPLETE;
    cf.last_edit = now();
  });

  print("\nCase Close: SUCCESS");
}

void arbitration::dismisscase(uint64_t case_id, name arb, string ipfs_url) {
  require_auth(arb);
  validate_ipfs_url(ipfs_url);

  casefiles_table casefiles(_self, _self.value);
  auto c = casefiles.get(case_id, "no case found for given case_id");

  auto arb_case = std::find(c.arbitrators.begin(), c.arbitrators.end(), arb);
  eosio_assert(arb_case != c.arbitrators.end(), "arbitrator isn't selected for this case.");
  eosio_assert(c.case_status == CASE_INVESTIGATION, "case is dismissed or complete");

  auto new_ipfs_list = c.findings_ipfs;
  new_ipfs_list.emplace_back(ipfs_url);

  casefiles.modify(c, same_payer, [&](auto &cf) {
    cf.findings_ipfs = new_ipfs_list;
    cf.case_status = DISMISSED;
    cf.last_edit = now();
  });

  print("\nCase Dismissed: SUCCESS");
}

void arbitration::dismissev(uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb, string ipfs_url) {
  require_auth(arb);
  validate_ipfs_url(ipfs_url);

  casefiles_table casefiles(_self, _self.value);
  auto c = casefiles.get(case_id, "Case not found");
  auto arb_case = std::find(c.arbitrators.begin(), c.arbitrators.end(), arb);

  eosio_assert(arb_case != c.arbitrators.end(), "only arbitrator can dismiss case");
  eosio_assert(claim_index < 0 || claim_index >= c.claims.size(), "claim_index is out of range");

  vector<claim> new_claims = c.claims;
  auto clm = c.claims[claim_index];

  eosio_assert(ev_index < 0 || ev_index >= clm.accepted_ev_ids.size(), "ev_index is out of range");

  vector<uint64_t> new_accepted_ev_ids = clm.accepted_ev_ids;
  new_accepted_ev_ids.erase(clm.accepted_ev_ids.begin() + ev_index);
  clm.accepted_ev_ids = new_accepted_ev_ids;
  new_claims[claim_index] = clm;

  casefiles.modify(c, same_payer, [&](auto &cf) {
    cf.claims = new_claims;
    cf.last_edit = now();
  });

  dismissed_evidence_table d_evidences(_self, _self.value);
  auto dev_id = d_evidences.available_primary_key();

  d_evidences.emplace(_self, [&](auto &dev) {
    dev.ev_id = dev_id;
    dev.ipfs_url = ipfs_url;
  });
  print("\nEvidence dismissed");
}

void arbitration::acceptev(uint64_t case_id, uint16_t claim_index, uint16_t ev_index, name arb, string ipfs_url) {
  require_auth(arb);
  validate_ipfs_url(ipfs_url);

  casefiles_table casefiles(_self, _self.value);
  auto c = casefiles.get(case_id, "Case not found");
  auto arb_case = std::find(c.arbitrators.begin(), c.arbitrators.end(), arb);

  eosio_assert(arb_case != c.arbitrators.end(), "only arbitrator can accept");
  eosio_assert(claim_index < 0 || claim_index >= c.claims.size(), "claim_index is out of range");

  vector<claim> new_claims = c.claims;
  auto clm = c.claims[claim_index];

  eosio_assert(ev_index < 0 || ev_index >= clm.submitted_pending_evidence.size(), "ev_index is out of range");

  vector<string> new_submitted_pending_evidence = clm.submitted_pending_evidence;
  new_submitted_pending_evidence.erase(clm.submitted_pending_evidence.begin() +
                                       ev_index);
  clm.submitted_pending_evidence = new_submitted_pending_evidence;
  new_claims[claim_index] = clm;

  casefiles.modify(c, same_payer, [&](auto &cf) {
    cf.claims = new_claims;
    cf.last_edit = now();
  });

  evidence_table evidences(_self, _self.value);
  auto ev_id = evidences.available_primary_key();

  evidences.emplace(_self, [&](auto &ev) {
    ev.ev_id = ev_id;
    ev.ipfs_url = ipfs_url;
  });

  print("\nEvidence accepted");
}

void arbitration::arbstatus(uint16_t new_status, name arb) {
  require_auth(arb);

  arbitrators_table arbitrators(_self, _self.value);
  auto ptr_arb = arbitrators.get(arb.value, "Arbitrator not found");

  eosio_assert(new_status >= 0 || new_status <= 3, "arbitrator status doesn't exist");

  arbitrators.modify(ptr_arb, same_payer, [&](auto &a) { 
      a.arb_status = new_status; 
    });

  print("\nArbitrator status updated: SUCCESS");
}

void arbitration::casestatus(uint64_t case_id, uint16_t new_status, name arb) {
  require_auth(arb);

  casefiles_table casefiles(_self, _self.value);
  auto c = casefiles.get(case_id, "no case found for given case_id");
  auto arb_case = std::find(c.arbitrators.begin(), c.arbitrators.end(), arb);

  eosio_assert(arb_case != c.arbitrators.end(), "arbitrator isn't selected for this case.");
  eosio_assert(c.case_status != DISMISSED || c.case_status != COMPLETE, "case is dismissed or complete");

  casefiles.modify(c, same_payer, [&](auto &cf) {
    cf.case_status = new_status;
    cf.last_edit = now();
  });

  print("\nCase updated: SUCCESS");
}

void arbitration::changeclass(uint64_t case_id, uint16_t claim_index, uint16_t new_class, name arb) {
  require_auth(arb);

  casefiles_table casefiles(_self, _self.value);
  auto c = casefiles.get(case_id, "no case found for given case_id");
  auto arb_case = std::find(c.arbitrators.begin(), c.arbitrators.end(), arb);

  eosio_assert(arb_case != c.arbitrators.end(), "arbitrator isn't selected for this case.");
  eosio_assert(claim_index < 0 || claim_index >= c.claims.size(), "claim_index is out of range");

  vector<claim> new_claims = c.claims;
  new_claims[claim_index].class_suggestion = new_class;

  casefiles.modify(c, same_payer, [&](auto &cf) {
    cf.claims = new_claims;
    cf.last_edit = now();
  });

  print("\nClaim updated: SUCCESS");
}

void arbitration::recuse(uint64_t case_id, string rationale, name arb) {
  // rationale ???
  require_auth(arb);

  casefiles_table casefiles(_self, _self.value);
  auto c = casefiles.get(case_id, "no case found for given case_id");
  auto arb_case = std::find(c.arbitrators.begin(), c.arbitrators.end(), arb);

  eosio_assert(arb_case != c.arbitrators.end(), "arbitrator isn't selected for this case.");

  vector<name> new_arbs = c.arbitrators;
  remove(new_arbs.begin(), new_arbs.end(), arb);

  casefiles.modify(c, same_payer, [&](auto &cf) {
    cf.arbitrators = new_arbs;
    cf.last_edit = now();
  });

  print("\nArbitrator was removed from the case");
}

void arbitration::dismissarb(name arb) {
  require_auth2(arb.value, "active"_n.value); // REQUIRES 2/3+1 Vote from eosio.prods for MSIG
  // require_auth2("eosio.prods"_n.value, "active"_n.value); //REQUIRES 2/3+1
  // Vote from eosio.prods for MSIG

  arbitrators_table arbitrators(_self, _self.value);
  auto a = arbitrators.get(arb.value, "Arbitrator Not Found");

  eosio_assert(a.arb_status != INACTIVE, "Arbitrator is already inactive");

  arbitrators.modify(a, same_payer, [&](auto &a) {
       a.arb_status = INACTIVE; 
    });

  print("\nArbitrator Dismissed!");
}

#pragma region Helper_Functions

void arbitration::validate_ipfs_url(string ipfs_url) {
	//TODO: Base58 character checker 
	eosio_assert(!ipfs_url.empty(), "ev_ipfs_url cannot be empty, evidence for claims must be submitted.");
	eosio_assert(ipfs_url.length() == 53 && ipfs_url.substr(0, 5) == "/ipfs/", "invalid ipfs string, valid schema: /ipfs/<hash>/");
}

arbitration::config arbitration::get_default_config() {
  vector<int64_t> fees{100000, 200000, 300000};
  auto c = config{
      get_self(),  // publisher
      uint16_t(0), // max_elected_arbs
      uint32_t(0), // election_duration
      uint32_t(0), // start_election
      fees,        // fee_structure
      uint32_t(0), // arbitrator_term_length
      now()        // last_time_edited
  };
  configs.set(c, get_self());

  return c;
}

void arbitration::start_new_election(uint8_t available_seats) {
  uint32_t begin_time = now() + _config.start_election;
  uint32_t end_time = begin_time + _config.election_duration;

  action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "regballot"_n,
         make_tuple(get_self(),         // publisher
                    uint8_t(2),         // ballot_type (2 == leaderboard)
                    symbol("VOTE", 4),  // voting_symbol
                    begin_time,         // begin_time
                    end_time,           // end_time
                    std::string("")     // info_url
                  )
                ).send();

  action(permission_level{get_self(), "active"_n}, "eosio.trail"_n, "setseats"_n,
         make_tuple(get_self(),
          _config.ballot_id, 
          available_seats
        )
      ).send();

      print("\nNew election has started.");
}

bool arbitration::has_available_seats(arbitrators_table &arbitrators, uint8_t &available_seats) {
  uint8_t occupied_seats = 0;
  
  for (auto &arb : arbitrators) {
    // check if arb seat is expired
    if (now() > arb.term_length && arb.arb_status != uint16_t(SEAT_EXPIRED)) {
      arbitrators.modify(arb, same_payer, [&](auto &a) {
        a.arb_status = uint16_t(SEAT_EXPIRED);
      });
    }

    if(arb.arb_status != uint16_t(SEAT_EXPIRED)) occupied_seats++;
  }

  available_seats = uint8_t(_config.max_elected_arbs - occupied_seats);
  
  return available_seats > 0;
}

void arbitration::add_arbitrator(arbitrators_table &arbitrators, name arb_name) {
  auto arb = arbitrators.find(arb_name.value);
 
  if (arb == arbitrators.end()) {
    arbitrators.emplace(_self, [&](auto &a) {
      a.arb = arb_name;
      a.arb_status = uint16_t(UNAVAILABLE);
      a.open_case_ids = vector<uint64_t>();
      a.closed_case_ids = vector<uint64_t>();
    });
  } else {
    arbitrators.modify(arb, same_payer, [&](auto &a){
      a.arb_status = uint16_t(UNAVAILABLE);
    });
  }
}

#pragma endregion Helper_Functions

EOSIO_DISPATCH( arbitration, (setconfig)(initelection)(regarb)(unregarb)(endelection)
                             (filecase)(addclaim)(removeclaim)(shredcase)(readycase)
                             (dismisscase)(closecase)(dismissev)(acceptev)
                             (arbstatus)(casestatus)(changeclass)(recuse)(dismissarb) )
