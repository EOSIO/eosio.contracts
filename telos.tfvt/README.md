# Telos Foundation Voting Token and Telos Foundation Board Token

## Contract Setup



* `setconfig(name publisher, config new_configs)`

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
    * `block_timestamp last_board_election_time` is the last time a board election was concluded.

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

* `makeissue(name holder, uint32_t begin_time, uint32_t end_time, string info_url)`

    The makeissue action will set up a proposal on Trail that is votable on by TFVT holders.

    `holder` is the account making the issue.

    `begin_time` and `end_time` are the time points (in seconds) when the ballot will begin.

    `info_url` is the info link for the campaign.

* `closeissue(name holder, uint64_t ballot_id)`

    The closeissue action will close an ended ballot that was set up through the `makeissue()` action.

    `holder` is the account calling closeissue.

    ` ballot_id` is the ballot id to close.

* `makeelection(name holder, uint32_t begin_time, uint32_t end_time, string info_url)`

    The makeelection action will set up a leaderboard on Trail to elect new members to the Telos Foundation Board that is votable on by TFVT holders.

    `holder` is the account making the leaderboard.

    `begin_time` and `end_time` are the time points (in seconds) when the ballot will begin.

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
