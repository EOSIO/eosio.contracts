# Worker Proposal User/Developer Guide

The Worker Proposal System contract allows members of the Telos Blockchain to create worker proposals. Through the WPS contract members of the telos blockchain can outline improvements that they believe benefit Telos. Once a proposal is published, members of Telos can use the Trail Service contract to vote for a proposal. If a proposal passes the proposer can claim the Tokens needed to implement the changes described in their proposal.

# Contract Setup 

The Worker Proposal System contract should be set to the `eosio.saving` account. Or to which ever account will receive the tokens needed to fund worker proposals. 

## Dependencies

The WPS contract requires that the Trail Service contract be set on the `eosio.trail` account. WPS leverages trails extensive voting system in order to track member voting for worker proposals.

## Contract Account Permissions

WPS requires the `active` permission of the account it's published on to include a new actor, `eosio.saving@eosio.code`. This allows WPS to sign inline transactions as `eosio.saving`. An example of this permission is shown below.

TODO: show permissions here

# Actions

* `void submit(name proposer, std::string title, uint16_t cycles, std::string ipfs_location, asset amount, name receiver)`

	The submit action allows members to submit a proposal to the contract. If the proposer has transferred the required `TLOS` fee to `eosio.saving` a `ballot` and `proposal` object will be emplaced in the `eosio.trail` tables.

	`proposer` is the account name of the proposer. The person who owns the submission of the proposal discribed in the following arguments.

	`title` is the title of the proposal being sent by the `proposer`

	`cycles` this argument represents the number of voting cycles, the number of payments, and the length of time the work desribed in the proposal will take to finish.

	`ipfs_location` is the object hash of a document stored on IPFS that describes the proposals goals. The work required, its benefits, costs, schedules, etc.

	`amount` the token amount to be paid to the `receiver` (explained below) if a cycle passes the threshold of required `YES` votes.

	`receiver` the account name that will receive the `amount` described above. 

* `void cancelsub(uint64_t sub_id)`

	The cancelsub action allows members who have called `submit` previously to cancel their submission before the voting starts. 

	*CAUTION: This action does not refund your fee!*

	`sub_id` the unique id of the submission to be cancelled.

* `void openvoting(uint64_t sub_id)`

	The openvoting action starts the voting of the initial proposal.

	`sub_id` the unique id of the submisision to be started.

* `void claim(uint64_t sub_id)`

	The claim action allows the proposer of ``