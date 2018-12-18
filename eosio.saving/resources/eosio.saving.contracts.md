<h1 class="contract">submit</h1>
This human-language contract for the `eosio.saving` action `submit` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **proposer** (account name of the proposer, who owns the proposal submission)

* **title** (title of the proposal)

* **cycles** (number of voting cycles the proposal will recur)

* **ipfs_location** (object hash of a document stored on IPFS that describes the proposals goals, the work required, its benefits, costs, schedules, etc.)

* **amount** (token amount to be paid to the receiver if a cycle passes the threshold of required YES votes)

### Intent

The intention of the authors and the invoker of this contract is to allow Members to submit a proposal to the contract and to emplace a ballot and proposal object in the eosio.trail tables provided the proposer has transferred the required TLOS fee to `eosio.saving`. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{proposer}} and that I intend to submit a worker proposal entitled, {{title}} described by the document stored at {{ipfs_location}} with the intention that the proposal shall recur for {{cycles}} cycles and pay {{amount}} to the designated receivers.

<h1 class="contract">cancelsub</h1>
This human-language contract for the `eosio.saving` action `cancelsub` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **sub_id** (unique id of the submission to be cancelled)

* **signer** (account name of the signer - _implied parameter_)

### Intent

The intention of the authors and the invoker of this contract is to cancel the submission of a previously submitted proposal prior to the start of voting, **without refunding the submission fee**. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to cancel the submission of my proposal, {{sub_id}}. I acknowledge that I will not receive a refund of any submission fee paid.

<h1 class="contract">openvoting</h1>
This human-language contract for the `eosio.saving` action `openvoting` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **sub_id** (unique id of the submission to be opened for voting)

* **signer** (account name of the signer - _implied parameter_)

### Intent

The intention of the authors and the invoker of this contract is to commence the voting period of the designated proposal. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to commence the voting period of the worker proposal: {{sub_id}}.

<h1 class="contract">claim</h1>
This human-language contract for the `eosio.saving` action `claim` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **sub_id** (unique id of the submission to be claimed)

* **signer** (account name of the signer - _implied parameter_)

### Intent

The intention of the authors and the invoker of this contract is to claim for the proposer of a voter-approved worker proposal: {{sub_id}}, the amount of TLOS described in its proposal submission. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to claim the allocated amount of TLOS from the voter-approved worker proposal: {{sub_id}} for its submitter. **I acknowledge that paid worker proposals that do not deliver their promised work products or services, or otherwise fail to deliver on what the Telos voters approved are subject to arbitration proceedings to reclaim funds for undelivered work.
