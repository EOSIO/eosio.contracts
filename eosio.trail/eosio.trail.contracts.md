<h1 class="contract">mirrorcast</h1>
This human-language contract for the `eosio.trail` action `mirrorcast` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

The mirrorcast function is the fundamental action that operates the Trail voting system. Member can only invoke mirrorcast once per day.

### Parameters

* **voter** (name of the account attempting to claim VOTE tokens)

* **token_symbol** (symbol of the token to mirrorcast into Trail)

### Intent

The intention of the authors and the invoker of this contract is to allow a registered voter to receive a 1:1 issuance of VOTE tokens for every TLOS they own in their account (both liquid and staked) a maximum of once per day. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{voter}} and a registered Telos voter and that I intend to claim an issuance of VOTE tokens that matches my current balance of {{token_symbol}} tokens, both staked and unstaked.

<h1 class="contract">castvote</h1>
This human-language contract for the `eosio.trail` action `castvote` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **voter** (name of the account casting its votes)

* **ballot_id** (ID of the ballot measure for which the votes shall be cast)

* **direction** (direction in which votes are cast - 0 = NO, 1 = YES, 2 = ABSTAIN)

### Intent

The intention of the authors and the invoker of this contract is to cast votes in a given ballot measure matching the Member's amount of VOTE tokens in the direction specified by the voter (YES, NO, or ABSTAIN). It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{voter}} and that I intend to cast my VOTE tokens on ballot measure: {{ballot_id}} as: {{direction}}, where the values 0 = NO, 1 = YES, 2 = ABSTAIN. 
