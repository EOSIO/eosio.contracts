<h1 class="contract">addclause</h1>
This human-language contract for the `eosio.amend` action `addclause()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **sub_id** (proposal ID number of the submission for which to add the clause)

* **new_clause_num**  (clause number to update)

* **new_ipfs_url** (link to the new clause text)

### Intent

The intention of the authors and the invoker of this contract is to make a new clause to an existing ratification or amendment proposal. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{proposer}} and that I intend to submit a new clause to ratification or amendment Proposal number: {{sub_id}}, with clause number: {{ new_clause_num }} which is comprised of the exact text stored at this IPFS location {{new_ipfs_url}}.

<h1 class="contract">cancelsub</h1>
This human-language contract for the `eosio.amend` action `cancelsub()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

_**sub_id** (proposal ID number of the submission to be cancelled)

### Intent

The intention of the authors and the invoker of this contract is to cancel a voting submission. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to cancel voting on the issue election designated with the ID number: {{sub_id}}.

<h1 class="contract">closeprop</h1>
This human-language contract for the `eosio.amend` action `closeprop()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **sub_id** (proposal ID number of the submission to be closed and finalized)

### Intent

The intention of the authors and the invoker of this contract is to close a voting submission that has finished its voting period and execute the result. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to close out voting and finalize results for the issue election designated with the ID number: {{sub_id}}.

<h1 class="contract">getdeposit</h1>
This human-language contract for the `eosio.amend` action `getdeposit()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **owner** (name of the account that owns the deposit)

### Intent

The intention of the authors and the invoker of this contract is to claim for its owner, the depost that the owner made in order to submit a proposal. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to instruct this contract to send the rafify and amend deposit that is owned by the account {{owner}}.

<h1 class="contract">insertdoc</h1>
This human-language contract for the `eosio.amend` action `insertdoc()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **title** (title of the document)

* **clauses** (a list of clauses that make up the document - ideally, each clause would be its own IPFS hash)

### Intent

The intention of the authors and the invoker of this contract is to add a new document to the table of Telos Core Governance documents. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{proposer}} and that I intend to submit a add a new document entitled, {{ title }} to the table of Telos Core Governance documents. {{title}} is comprised of the clauses {{vector: clauses}}.

<h1 class="contract">makeproposal</h1>
This human-language contract for the `eosio.amend` action `makeproposal()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **sub_title** (title of the submission)

* **doc_id** (document id for which the proposal will update)

* **new_clause_num** (new clause number to update)

* **new_ipfs_url** (link to the new clause text)

* **proposer** (proposer of the submission)

### Intent

The intention of the authors and the invoker of this contract is to make a new proposal and call regballot() on the Trail Service with the given values and to store the metadata of the proposal on this contract in order to record the values submitted with this contract. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to submit a proposal to the Telos Members under the name {{proposer}} to ratify or amend the Telos Core Governance document with the ID number {{doc_id}} as described herein. My proposal, entitled {{sub_title}} proposes to change the document's clause number: {{new_clause_num}} with the exact text stored at this IPFS location {{new_ipfs_url}}, if the text is different than the current text of this clause, or to ratify the existing clause if the text is identical. I may add additional clauses to this proposal.

<h1 class="contract">openvoting</h1>
This human-language contract for the `eosio.amend` action `openvoting()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **sub_id** (proposal ID number of the submission for which to open voting)

### Intent

The intention of the authors and the invoker of this contract is to open an amendment issue for voting. It shall have no other effect.

### Contract Text

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to open voting on the issue election designated with the ID number: {{sub_id}}.

<h1 class="contract">setenv</h1>
This human-language contract for the `eosio.amend` action `setenv()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **new_environment** (new environment to set)

### Intent

The intention of the authors and the invoker of this contract is to set the config for a new contract environment. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to set the config for an new contract environment to {{new_environment}}.
