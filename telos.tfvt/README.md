# Telos Foundation Voting Token and Telos Foundation Board Token

## Contract Setup

### Permissions Setup

`owner` : multisig accounts, tf@eosio.code (weight of eosio.code should be enough to sign by itself)

`active` : multisig accounts, tf@eosio.code (weight of eosio.code should be enough to sign by itself)

### Config Setup

* `setconfig(name publisher, config new_config)`

    The setconfig action will overwrite the old config settings with new a new config.

    `publisher` is the publisher of the contract. Only this account can change the configuration.

    `new_configs` is the new configuration to set. 
    
    The current config object contains the following fields:

    * `name publisher` is the name of the account publishing the contract. The setconfig action will revert this field back to the original publisher who initialized the contract, no matter what value is supplied here. This ensures the contract owner is immutable, but the rest of the config is still alterable.
    * `uint8_t max_board_seats` is the max number of board seats the contract will allow at any given time.
    * `uint8_t open_seats` is the number of opens eats on the board, and thus will need filling on the next election. This value will be reverted back to the previous value to ensure open seats can't be arbitrarily added.
    * `uint64_t open_election_id` is the Trail ballot id of the currently running election. This value will revert back to the old value to ensure the ballot id can never be lost.
    * `uint32_t holder_quorum_divisor` is the divisor value required to calculate a TFVT holder quorum threshold. Ex: `5` would equal a quorum threshold of 20%.
    * `uint32_t board_quorum_divisor` is the divisor value required to calculate a TFBOARD member quorum threshold. Ex: `2` would equal a quorum threshold of 50%.
    * `uint32_t issue_duration` is the length in seconds an issue ballot will remain open for voting on Trail.
    * `uint32_t start_delay` is the wait time in seconds before an issue or election will begin voting, from when the `makeelection()` or `makeissue()` actions were successfully sent.
    * `uint32_t leaderboard_duration` is the length in seconds of an election created by the `makeelection()` action.
    * `uint32_t election_frequency` is the amount of time in seconds that must pass before a new election (excluding runoff elections) can begin.
    * `uint32_t last_board_election_time` is the last time a board election was concluded.

* `inittfvt(string initial_info_link)`

    This action will register and initialize the TFVT token on Trail with the pre-programmed constants.

    `initial_info_link` is the info_link registered to the new token registry.

* `inittfboard(string initial_info_link)`

    This action will register and initialize the TFBOARD token on Trail with the pre-programmed constants.

    `initial_info_link` is the info_link registered to the new token registry.

## Contract Usage

* `nominate(name nominee, name nominator)`

    This action nominates an account to be a board member. 

    `nominee` is the account being nominated.

    `nominator` is the account nominating. This account must be a TFVT or TFBOARD holder to nominate.

* `makeissue(name holder, string info_url, name issue_name, transaction transaction)`

    The makeissue action will set up a proposal on Trail that is votable on by TFVT holders.

    `holder` is the account making the issue.

    `info_url` is the info link for the campaign.

    `issue_name` is the name of the issue as an account name.

    `transaction` is the transaction to send if the issue proposal passes.

* `closeissue(name holder, name proposer)`

    The closeissue action will close an ended ballot that was set up through the `makeissue()` action.

    `holder` is the account calling closeissue.

    `proposer` is the name of the account that proposed the issue.

* `makeelection(name holder, string info_url)`

    The makeelection action will set up a leaderboard on Trail to elect new members to the Telos Foundation Board that is votable on by TFVT holders.

    `holder` is the account making the leaderboard.

    `info_url` is the info link for the campaign.

* `addcand(name candidate, string info_link)`

    The addcand action will add a nominee to the list of candidates on an existing election leaderboard in Trail. Note that adding candidates to elections can only happen before voting begins.

    `candidate` is the name of the nominee being added to the election.

    `info_link` is a link (ideally an IPFS hash) to the nominee's campaign information.

* `removecand(name candidate)`

    The removecand action will remove a candidate on an existing election. Note that a candidate cannot be removed once voting has begun.

    `candidate` is the name of the candidate to remove.

* `endelection(name holder)`

    The endelection action will end a leaderboard that was set up through the `makeelection()` action. This action will also automatically resolve ties and launch a runoff election for seats that still remain open.

    `holder` is the account calling closeissue.

    Note that because elections are ran on leaderboard logic (as multiple seats must be able to run at the same time) ties will only trigger a runoff election when a chain of ties (of any length) reaches the final available seat or beyond. Should this occur, this contract will drop each account in the tie chain and initiate a runoff election for the unfilled board seats.

    For example, suppose an election is held with 5 available seats, and 9 candidates. After voting has ended and candidates have been ranked based on total votes, a tie chain occurs from ranks 3 - 7. Ranks 1 and 2 would be placed in the board, and ranks 8 and 9 would be ignored. Then, a runoff election would be triggered for the remaining 3 board seats (as seats 3 - 5 were not assigned due to a tie chain reaching the final seat) and candidate ranks 3 -7 would enter the election and proceed as normal. Note that runoff elections are decided by `TFVT` token holders, not `TFBOARD` members.

## Board Actions

* `void removemember(name member_to_remove)`

    This action is an administrative-level kick from the Telos Foundation Board. This action is only callable by a multi-sig from a number of board members that satisfy the `major` permission of the `tf` account.

    `member_to_remove` is the account name of the board member to remove.

## Contract Flow

The TFVT contract allows `TFVT` tokens holders to nominate candidates for board member elections, start/end elections, and start/end issues. `TFVT` holders are the first class citizen of the Telos Foundation contract. Holders can elect their own representatives and help guide the destiny of the Telos Foundation.

### Election Flow

`TFBOARD` member terms occur every `14515200` seconds or `(0 yr 5 mon. 2 w 4 day)`. The below list of actions is how a `TFVT` holder could guide the election. This list is written in chronological order.

* `nominate`, this action is called by a `TFVT` holder called the Nominator. The Nominator would then nominate an account called the Nominee. Once a nominee has been nominated. They are now elegible to add themselves to any future `TFBOARD` election. If they win in an election, they are removed from the `nominees` table and must be nominated again in the future.

* `makeelection`, this action is called by a `TFVT` holder in order to start a new election cycle. This action will fail if it isn't time for another election. Once this action is executed a coupled `ballot` and `leaderboard` are created in trail which allows `TFVT` holders to vote for the `nominees` that add themselves to the election.

* `addcand`, this action is called by a previously nominated `nominee` to add themselves to the `leaderboard` object in trail. Once added they eligible to receive votes from `TFVT` holders.

Once the `leaderboard`'s `begin_time` has been exceeded, then voting can begin. `TFVT` holders only need cast their vote through trail. In order to cast their vote, they first will need to know what `ballot_id` to vote on. In the case of `telos.tfvt` this can be found in the `config` table of the contract (example below). 

* `eosio.trail::castvote` (see `eosio.trail` [README](...) for more information), once you know the `ballot_id`, a holder can start casting their votes. In this system a holder can cast their vote for as many candidates as they choose, but they can never vote for the same candidate twice. `eosio.trail` is an abstract voting contract, meaning the what you are voting on could be a proposal or an election. The meaning of these proposals and election are interpreted by their publisher. In the case of `telos.tfvt` the election is an election for board members. So the example below has been explained with that context in mind. 

`eosio.trail::castvote(voter, ballot_id, direction)`, in this case the `ballot_id` argument is the `open_election_id` value found in the `config` table on the `telos.tfvt` contract. The `direction` argument is the candidate you wish to vote for, this number ranges from `0 to N - 1` where N is the total number of candidates. The voter is of course, who ever is doing the voting.

How do I know who I'm voting for? Well the easiest way would be to use a tool that is designed to make this easy, but if you are stubborn here is how you find out.

The candidates for a leaderboard election are stored in `eosio.trail`, so we need to first look there. A `ballot` represents two (currently) forms of election, `proposals` and `leaderboards`. A proposal is a `yes/no` voting system, `leaderboards` are more of an election where there can be multiple seats and multiple candidates. In our case, `TFVT` is setting up a leaderboard election. In order to find the leaderboard follow the steps below.

* Look up the `open_election_id` in the `tf` `config` table.
	* `teclos --url {endpoint} get table tf tf config`

* Look up the `board_id` from the `reference_id` in the ballot.
	* `teclos --url {endpoint} get table eosio.trail eosio.trail ballots --lower {open_election_id}`

* Look up the `leaderboard` using the `board_id` from the last step. 
	* `teclos --url {endpoint} get table eosio.trail eosio.trail leaderboards --lower {board_id}`

* Now you should see the `leaderboard` object. The `candidates[]` will show reveal to you who you want to vote for and what their `direction` value should be.

* `eosio.trail::castvote(voter, open_election_id, direction)` done!

* Once the `end_time` of the `leaderboard` is exceeded, voting end. A `TFVT` holder can now end the election.

* `endelection` a `TFVT` holder can now call endelection to end this current round. The `candidates` we have votes will be added to the board. Those new boardmemebers will have signature in the `tf` account authorities, and can now vote on issues.

* If the number of winner isn't equal to `config.max_seats` a run off election can be started by calling `makeelection` again.
