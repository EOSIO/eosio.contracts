# Arbitration Setup/Usage

The arbitration contract is a tool for Telos Blockchain Network members to contractually apply for arbitration because of grievances within the network.

## Setup

The following steps outline how to initialize the arbitration contract and elect arbitrators.

### Contract Initialization



* `void setconfig(uint16_t max_elected_arbs, uint32_t election_duration, uint32_t start_election, uint32_t arbitrator_term_length, vector<int64_t> fees)`

    The setconfig action initializes the contract config with the given values.

    `max_elected_arbs` is the max number of arbs allowed to be elected at any given time.

    `election_duration` is the length of the election in seconds.

    `start_election` is the length of time in seconds to wait before elections begin.

    `arbitrator_term_length` is the term length of arbitrators in seconds.

    `fees` is the fee structure for arbitratoin cases.

### Arbitrator Applications



* `regarb(name candidate, string creds_ipfs_url)`

    The regarb action will create an arbitrator application for the given candidate. Arbitrator candidates must then be elected in order to begin accepting cases.

    `candidate` is the account name of the candidate applying for an arbitrator position.

    `creds_ipfs_url` is a link (ideally an IPFS hash) to the candidate's credentials. Candidates that fail to supply or supply false credentials will not be considered for election.

* `unregarb(name candidate)`

    The unregarb action will remove the candidate's arbitrator application.

    `candidate` is the account to remove from the candidate's list.

### Arbitrator Election Setup/Management

* `initelection()`

    The initelection action will register an election by sending an inline action to the `regballot()` action on Trail.

Note that adding candidates is done through the 

* `endelection(name candidate)`

    The endelection action will close an existing election that is no longer open for voting.

    `candidate` is the account calling the endelection action.
