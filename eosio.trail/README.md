# Trail Service User/Developer Guide

Trail offers a comprehensive suite of blockchain-based voting services available to any prospective voter or contract developer.

## Understanding Trail's Role

Trail was designed to allow maximum flexibility for smart contract developers, while at the same time consolidating many of the boilerplate functions of voting contracts into a single service. 

This paradigm essentially means contract writers can leave the "vote counting" up to Trail and instead focus on how they want to interpret the results of their ballot. Through cross-contract table lookup, any contract can view the results of a ballot and then have their contracts make decisions based on those results.

Trail ballots and elections are also stored indefinitely, allowing lookup throughout the entire history of the service. The only exception to this rule are ballots that operate on cycles. Ballots that operate this way will instead show the most recent cycle of the ballot.

## Ballot Lifecycle

Building a ballot on Trail is simple and gives great flexibility to the developer to build their ballots in any structure they desire. An example ballot and voting contract will be used throughout this guide, and is recommended as an established model for current Trail interface best practices.

### 1. Setting Up Your Contract (Optional)

While setting up an external contract is not required to utilize Trail's services, it is required if developers want to **contractually** act on ballot results. If you aren't interested in having a separate contract and just want to run a ballot or campaign, then proceed to step 2.

For our contract example, we will be making a simple document updater where updates are voted on by the community. The basic interface looks like this:

* `createdoc(string doc_title, string text)`

    The createdoc action will create a new document, retrievable by a document id. The text of the document is stored as a string (not ideal for production, but fine for this example).

* `updatedoc(uint64_t doc_id, string new_text)`

    The updatedoc action simply updates the document with the new text. This will be called after voting has completed to update our document with the text supplied in the proposal (if the proposal passes).

* `makeproposal(uint64_t doc_id, string new_text)`

    The makeproposal action stores the new text retrievable by a proposal id, after first making sure the associated document exists. No vote counts are stored on this contract (remember, that's Trail's job).

* `closeprop(uint64_t prop_id)`

    The closeprop action is important for performing custom logic on ballot results, and simply sends an inline action to Trail's `closeballot()` action upon completion. The `status` field of the ballot allows ballot closers the ability to assign any context to status codes they desire. For example, a voting contract could interpret a status code of `7` to mean `REFUNDED`. However, status codes `0`, `1`, and `2` are reserved for meaning `OPEN`, `PASS`, and `FAIL`, respectively.

### 2. Ballot Registration

Ballot regisration allows any user or developer to create a public ballot that can be voted on by any registered voter that has a balance of the respective voting token.

* `regballot(name publisher, uint8_t ballot_type, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url)`

    The regballot action will register a new ballot with attributes reflecting the given parameters.

    `publisher` is the account publishing the ballot. Only this account will be able to modify and close the ballot.

    `ballot_type` is the type of ballot to create. The following is a list of currently supported Ballot Types (some still in development):

    * `0 = Proposal` : Users vote on a proposal by casting votes in either the YES, NO, or ABSTAIN direction.

    * `1 = Election` : Users vote on a single candidate from a set of candidates. IN DEVELOPMENT...

    * `2 = Leaderboard` : Users vote to rank candidates in descending order based on total votes.

    * `3 = Live Leaderboard` : IN DEVELOPMENT...

    `voting_symbol` is the symbol to be used for counting votes. This is typically `VOTE`, represented symbolically as: `symbol("VOTE", 4)`. Note that custom voting tokens must exist on Trail (by calling regtoken) before being able to create ballots that use them.

    `begin_time` and `end_time` are the beginning and end time of the ballot measured in seconds. Any vote for the ballot can be cast between these two times (inclusively). Additionally, it's important for ballot operators to set the begin_time far enough in the future to give themselves enough time to properly set up their ballots. The current time in seconds can be retrieved from Trail's `environment` singleton, however this value only updates when Trail receives an action (or when someone transfers TLOS) so this value may be off depending on when it was last modified. Simply querying for this value will not update it.

    `info_url` is critical to ensuring voters are able to know exactly what they are voting on when they cast their votes. This parameter can simply be a url to a webpage (or even better, an IPFS hash) that explains what the ballot is for, and should provide sufficient information for voters to make an informed decision. Since some ballots owners will host this information on their own smart contract, this can simply be a pointer to that information as well. However, in order to ensure knowledgable voting, this field should never be left blank. Without providing a link to this information, any malicious actor could launch a misinformation campaign to confuse potential voters.

* `unregballot(name publisher, uint64_t ballot_id)`

    The unregballot action deletes an exiting ballot. This action can only be performed before a ballot opens for voting, and only by the publisher of the ballot.

    `publisher` is the account that published the ballot. Only this account can unregister the ballot.

    `ballot_id` is the ballot ID of the ballot to unregister.

### 3. Running A Ballot 

After ballot setup is complete, the only thing left to do is wait for the ballot to open and begin receiving votes. Votes cast on the ballot are live, so it's easy to see the state of the ballot as votes roll in. There are also a few additional features available for ballot runners that want to operate a more complex campaign. This feature set will grow with the development of Trail and as more complex versions of ballots are introduced to the system.

* `nextcycle(name publisher, uint64_t ballot_id, uint32_t new_begin_time, uint32_t new_end_time)`

    The nextcycle action is used to manage voting campaigns that operate in stages. Calling nextcycle will reset the ballot with new begin and end times, as well as reset the vote counts.

    NOTE: nextcycle is currently only allowed on Proposals.

    `publisher` is the account that published the ballot. Only this account is authorized to call nextcycle.

    `ballot_id` is the ballot ID of the ballot to recycle.

    `new_begin_time` and `new_end_time` are the new beginning and end times of the new cycle. The time format is the same as registering the ballot initially.

* `addcandidate(name publisher, uint64_t ballot_id, name new_candidate, string info_link)`

    The addcandidate action creates a new candidate for an election or leaderboard with the supplied information. Candidates can only be added before voting begins.

    `publisher` is the publisher of the ballot. Currently, only the ballot publisher can add new candidates to a ballot.

    `ballot_id` is the ballot ID of the election or leaderboard receiving the candidate.

    `new_candidate` is the account of the new candidate.

    `info_link` is a url to the candidate's information or campaign page.

* `setseats(name publisher, uint64_t ballot_id, uint8_t num_seats)`

    The setseats action sets the number of available seats open on a leaderboard.

    `publisher` is the publisher of the ballot.

    `ballot_id` is the ID of the ballot to set the new seats.

    `num_seats` is the number of seats to set.

### 4. Closing A Ballot

After a ballot has reached it's end time, it will automatically stop accepting votes. The final tally can be seen by querying the respective table with the ballot's reference id.

For instance, if a ballot was created and assigned a ballot_id of 5, you would query the ballots table for ballot_id 5. This will return a table_id and a reference_id. If the table_id were 0, and the reference_id were 17, you would query the proposals table (ballot_type maps to the table_id, so  table_id 0 is the proposals table) for proposal_id 17. 

* `closeballot(name publisher, uint64_t ballot_id, uint8_t pass)`

    The closeballot action is how publishers close out a ballot and render a decision based on the results.

    `publisher` is the publisher of the ballot. Only this account can close the ballot.

    `ballot_id` is the ballot ID of the ballot to close.

    `pass` is the resultant ballot status after reaching a verdict on the votes. This number can represent any end state desired, but `0`, `1`, and `2` are reserved for `OPEN`, `PASS`, and `FAIL` respectively.

## Voter Registration and Participation

All users on the Telos Blockchain Network can register their accounts and receive a VoterID card that's valid for any ballot that counts its votes through Trail's Token Registry system.

### 1. Registration

* `regvoter(name voter, symbol token_symbol)`

    The regvoter action creates an empty wallet for the given token symbol if a token registry of the given symbol exists. If the registered symbol is Trail's core VOTE token, the total_voters value in the `environment` table will be incremented, which can be referenced as a target for meeting quorum requirements.

    `voter` is the name of the account to register with Trail.

    `token_symbol` is the symbol of the token for which to create a wallet.

* `unregvoter(name voter, symbol token_symbol)`

    The unregvoter action unregisters an existing voter from Trail. This action also decrements the number of total voters tracked by the respective token registry.

    `voter` is the name of the account to unregister from Trail.

    `token_symbol` is the symbol of the token for which the voter is unregistering.

### 2. Getting and Casting Votes

* `mirrorcast(name voter, symbol token_symbol)`

    The mirrorstake function is the fundamental action that operates the Trail voting system. Registered voters may call mirrorstake to receive a 1:10000 issuance of VOTE tokens for every TLOS they own in their account (both liquid and staked) for a period of time equal to the given lock period. Users cannot call mirrorstake again until the lock period has ended.

    `voter` is the name of the account attempting to mirror their TLOS for VOTES.

    `token_symbol` is the symbol of the token to mirrorcast into Trail. Currently only supports mirrorcasting TLOS.

* `castvote(name voter, uint64_t ballot_id, uint16_t direction)`

    The castvote action will cast all a user's VOTE tokens on the given ballot. Note that this does not **spend** the user's VOTE tokens, it only applies their full weight to the ballot. Calling castvote again on the same ballot with a different direction will recast your votes (if the registry allows recasting), with the only exception being ballots that have been moved to another cycle. Casting votes on the same ballot, but on a different cycle will cast the votes normally (as if it were a new ballot).

    `voter` is the account that is casting votes.

    `ballot_id` is the id of the ballot for which to cast the votes.

    `direction` is the direction in which to cast the votes. The default mappings for proposals are `0 = NO, 1 = YES, 2 = ABSTAIN`. For elections and leaderboards, the direction corresponds to the index of the candidates vector. For instance, a direction of 2 would cast a vote for the candidate name that was returned from resolving `candidates[2]` (the third candidate in the list).

### 3. Clearing Out Old Vote Receipts

* `deloldvotes(name voter, uint16_t num_to_delete)`

    The deloldvotes action is a way to clear out old votes and allows voters to reclaim RAM that has been allocated for storing vote receipts.

    Note that Trail has been designed to be tolerant of users deleting their vote receipts. Trail will never delete a vote receipt that is still applicable to an open ballot.

    `voter` is the account for which old receipts will be deleted.

    `num_to_delete` is the number of receipts the voter wished to delete. This actio will run until it deletes specified number of receipts, or until it reaches the end of the list. Passing in a hard number allows voters to carefully manage their NET and CPU expenditure.

## Custom Token Lifecycle

Trail allows any Telos Blockchain Network user to create and manage their own custom tokens, which can also be used to vote on any ballot that has been configured to count votes based on that token.

### About Token Registries

Trail stores metadata about tokens in a custom data structure called a Token Registry. This stucture automatically updates when actions are called that would modify any part of the registry's state.

### 1. Registering a New Token

* `regtoken(asset max_supply, name publisher, string info_url)`

    The regtoken action creates a new token in Trail, and sets it with the default token settings.

    `max_supply` is the total number of tokens allowed to simultaneously exist in circulation. The token symbol is extracted from this value. This action will fail if a token already exists with the same symbol.

    `publisher` is the name of the publisher that will own the token registry. Only this account will be able to issue new tokens, change settings, and execute a few other token related actions.

    `info_url` is a url link (ideally an IPFS link) that prospective voters can follow to get more information about the token and it's purpose.

### 2. Initializing A Token Registry

* `initsettings(name publisher, symbol token_symbol, token_settings new_settings)`

    This action sets all the allowable token features for the given registry.

    `publisher` is the publisher of the token registry. Only this account may initialize the registry.

    `token_symbol` is the symbol of the token registry to initialize.

    `new_settings` is the set of new settings with which to initialize the token registry.

    The following is a list of all the supported token features:

    * `is_destructible` allows the registry to be erased completely by the publisher.
    * `is_proxyable` allows managed tokens to be proxiable to users that have been registered as a valid proxy.
    * `is_burnable` allows tokens to be burned from circulation, either by the publisher or the token holder. 
    * `is_seizable` allows the tokens to be seized by the publisher.
    * `is_max_mutable` allows the registry's max_supply field to be adjusted through an action call. Only the publisher can call the `raisemax` and `lowermax` actions.
    * `is_transferable` allows the tokens to be transferred to other users.
    * `is_recastable` allows tokens to be recastable on ballots, replacing the old vote with the new vote.
    * `is_initialized` shows whether the registry has been initialized.
    * `counterbal_decay_rate` is the rate at which token counterbalances decay. This value represents the number of seconds needed to pass in order to decay the counterbalance by 1 whole token.
    * `lock_after_initialize` forces the registry settings to permanently lock after initialization.

### 3. Managing A Token Registry

Trail offers a wide range of token features designed to offer maximum flexibility and control for registry operators, while at the same time ensuring the transparency and security of registry operations for token holders.

* `issuetoken(name publisher, name recipient, asset tokens, bool airgrab)`

    The issuetoken action is the primary way for new tokens to be introduced into circulation. Only the registry pulisher has the authority to issue new tokens.

    `publisher` is the name of the account that published the registry.

    `recipient` is the name of the recipient intended to receive the issuance.

    `tokens` is the amount of tokens to mint for the recipient. This action will fail if the number of tokens to issue would breach the max supply allowed by the registry.

    `airgrab` is a boolean value that when true will place the issued tokens in an airgrab table, retrievable only by the recipient. False will do an airdrop instead, where the tokens are dropped straight into the recipient's wallet. If the user doesn't have a wallet (meaning they haven't called regtoken for that symbol, or have not claimed an airgrab of that token) a wallet will be created for them, with the RAM cost fronted by the publisher.

* `claimairgrab(name claimant, name publisher, symbol token_symbol)`

    The claimairgrab action is called by a user to claim an existing airgrab that has been issued to their account.

    `claimant` is the account attempting to claim the airgrab. If the claimant doesn't already have a wallet of the claimed token, a new wallet will be created to store the claimed tokens, with the RAM costs paid by the claimant (this is equivalent to calling the regvoter action for the given token symbol).

    `publisher` is the name of the account that published the respective token registry (and therefore is the account that issued the airgrab).

    `token_symbol` is the symbol of the token being claimed in the airgrab.

* `burntoken(name balance_owner, asset amount)`

    The burntoken action is used to burn tokens from a user's wallet. This action is only callable by the registry publisher, and if the registry allows token burning.

    `balance_owner` is the owner of the balance being burned. User's can only burn their own balances, not the balances of other accounts.

    `amount` is the number of tokens to burn from circulation.

* `seizetoken(name publisher, name owner, asset tokens)`

    The seizetoken action is called by the publisher to seize a balance of tokens from another account. Only the publisher can seize tokens, and only if the registry's settings allow it. This is a very powerful function that should only be used when absolutely necessary.

    `publisher` is the name of the account that published the token registry.

    `owner` is the name of the account from which tokens are to be seized.

    `tokens` is the amount of tokens to seize from the user.

* `seizeairgrab(name publisher, name recipient, asset amount)`

    The seizeairgrab action is called by the publisher to seize an issued airgrab that hasn't already been claimed by the recipient. This action is only callable by the publisher, and if the registry allows token seizures.

    `publisher` is the name of the account that published the registry.

    `recipient` is the name of the account that the airgrab was intended for.

    `amount` is the number of tokens to seize from the airgrab. If this seizure takes all the tokens, the empty airgrab is erased afterward.

* `raisemax(name publisher, asset amount)`

    The raisemax action will raise the max supply of the respecitve registry.

    `publisher` is the name of the account that published the registry.

    `amount` is the amount by which to raise the max supply.

* `lowermax(name publisher, asset amount)`

    The lowermax action will lower the max supply of the respective token registry.

    `publisher` is the name of the account that published the registry.

    `amount` is the amount by which to lower the max supply.

* `transfer(name sender, name recipient, asset amount)`

    The transfer action is called by a token holder to send tokens to another account. This action is callable by any token holder, but only if the registry allows token transfers.

    It's important for registry operators to understand that allowing token transferability opens up numerous attack vectors for ballots that run off those tokens. Trail offers a suite of features that either completely eliminate or **significantly** reduce (depending on how registry operators choose to initialize their settings) the ability of malicious users to violate the integrity of ballots. 
    
    Allowing transferability lets users essentially vote-wash their tokens by voting, then transferring their balance to a new account, then re-voting. Trail combats these sybil vectors by automatically implementing a counterbalance system that follows tokens through transfers and only allows voters to vote the difference between their token balance and their counterbalance. Tokens that allow transferability automatically inherit the counterbalance system and will execute on each token transfer. The counterbalances also decay at an adjustable rate, meaning users who want to vote their newly received balance must simply wait for their counterbalance to decay to an acceptable level and then vote.

    `sender` is the name of the account sending the tokens.

    `recipient` is the name of the account receiving the tokens.

    `amount` is the amount of tokens to be sent.
