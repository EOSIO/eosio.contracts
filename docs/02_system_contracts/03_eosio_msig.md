## [eosio.msig system contract](action-reference/eosio.msig)

The `eosio.msig` allows for the creation of proposed transactions which require authorization from a list of accounts, approval of the proposed transactions by those accounts required to approve it, and finally, it also allows the execution of the approved transactions on the blockchain.

The workflow to propose, review, approve and then executed a transaction is describe in details [here](../04_guides/06_how-to-sign-a-multisig-transaction-with-eosio.msig.md), and in short it can be described by the following:
- first you create a transaction json file, 
- then you submit this proposal to the `eosio.msig` contract, and you also insert the account permissions required to approve this proposal into the command that submits the proposal to the blockchain,
- the proposal then gets stored on the blockchain by the `eosio.msig` contract, and is accessible for review and approval to those accounts required to approve it,
- after each of the appointed accounts required to approve the proposed transactions reviews and approves it, you can execute the proposed transaction.  The `eosio.msig` contract will execute it automatically, but not before validating that the transaction has not expired, it is not cancelled, and it has been signed by all the permissions in the initial proposal's required permission list.

The actions implemented and publicly exposed by the `eosio.msig` contract are detailed in the [eosio.msig reference documentation](action-reference/eosio.msig).

