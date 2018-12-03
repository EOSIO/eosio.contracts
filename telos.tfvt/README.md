# Telos Foundation Voting Token

## Contract Usage

* `inittfvt(string initial_info_link)`

    This action will register and initialize the TFVT token with the pre-programmed constants.

    `initial_info_link` is the info_link registered to the token registry.

* `inittfboard(string initial_info_link)`

    This action will register and initialize the TFBOARD token with the pre-programmed constants.

    `initial_info_link` is the info_link registered to the token registry.

* `setconfig(name publisher, config new_configs)`

    Sets the contract-level configuration singleton with new values.

    `publisher` is the publisher of the contract. Only this account can change the configuration.

    `new_configs` is the new configuration to set.

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

    The makeelection action will set up a leaderboard on Trail that is votable on by TFVT holders.

    `holder` is the account making the leaderboard.

    `begin_time` and `end_time` are the time points (in seconds) when the ballot will begin.

    `info_url` is the info link for the campaign.

* `addallcands(name holder, uint64_t ballot_id, vector<candidate> new_cands)`

    The setallcands action is a convenience feature that allows all candidates for an election or leaderboard to be set at once.

    `holder` is the account setting the candidates.

    `ballot_id` is the ballot id receiving the candidate set.

    ` new_cands` is the list of new candidates to set to the ballot.

* `endelection(name holder, uint64_t ballot_id)`

    The endelection action will end a leaderboard that was set up through the `makeelection()` action.

    `holder` is the account calling closeissue.

    ` ballot_id` is the ballot id to close.

