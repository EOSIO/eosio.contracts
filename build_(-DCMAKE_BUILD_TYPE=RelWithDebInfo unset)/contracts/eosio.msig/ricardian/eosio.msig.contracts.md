<h1 class="contract">approve</h1>

---
spec_version: "0.2.0"
title: Approve Proposed Transaction
summary: '{{nowrap level.actor}} approves the {{nowrap proposal_name}} proposal'
icon: http://127.0.0.1/ricardian_assets/eosio.contracts/icons/multisig.png#4fb41d3cf02d0dd2d35a29308e93c2d826ec770d6bb520db668f530764be7153
---

{{level.actor}} approves the {{proposal_name}} proposal proposed by {{proposer}} with the {{level.permission}} permission of {{level.actor}}.

<h1 class="contract">cancel</h1>

---
spec_version: "0.2.0"
title: Cancel Proposed Transaction
summary: '{{nowrap canceler}} cancels the {{nowrap proposal_name}} proposal'
icon: http://127.0.0.1/ricardian_assets/eosio.contracts/icons/multisig.png#4fb41d3cf02d0dd2d35a29308e93c2d826ec770d6bb520db668f530764be7153
---

{{canceler}} cancels the {{proposal_name}} proposal submitted by {{proposer}}.

<h1 class="contract">exec</h1>

---
spec_version: "0.2.0"
title: Execute Proposed Transaction
summary: '{{nowrap executer}} executes the {{nowrap proposal_name}} proposal'
icon: http://127.0.0.1/ricardian_assets/eosio.contracts/icons/multisig.png#4fb41d3cf02d0dd2d35a29308e93c2d826ec770d6bb520db668f530764be7153
---

{{executer}} executes the {{proposal_name}} proposal submitted by {{proposer}} if the minimum required approvals for the proposal have been secured.

<h1 class="contract">invalidate</h1>

---
spec_version: "0.2.0"
title: Invalidate All Approvals
summary: '{{nowrap account}} invalidates approvals on outstanding proposals'
icon: http://127.0.0.1/ricardian_assets/eosio.contracts/icons/multisig.png#4fb41d3cf02d0dd2d35a29308e93c2d826ec770d6bb520db668f530764be7153
---

{{account}} invalidates all approvals on proposals which have not yet executed.

<h1 class="contract">propose</h1>

---
spec_version: "0.2.0"
title: Propose Transaction
summary: '{{nowrap proposer}} creates the {{nowrap proposal_name}}'
icon: http://127.0.0.1/ricardian_assets/eosio.contracts/icons/multisig.png#4fb41d3cf02d0dd2d35a29308e93c2d826ec770d6bb520db668f530764be7153
---

{{proposer}} creates the {{proposal_name}} proposal for the following transaction:
{{to_json trx}}

The proposal requests approvals from the following accounts at the specified permission levels:
{{#each requested}}
   + {{this.permission}} permission of {{this.actor}}
{{/each}}

If the proposed transaction is not executed prior to {{trx.expiration}}, the proposal will automatically expire.

<h1 class="contract">unapprove</h1>

---
spec_version: "0.2.0"
title: Unapprove Proposed Transaction
summary: '{{nowrap level.actor}} revokes the approval previously provided to {{nowrap proposal_name}} proposal'
icon: http://127.0.0.1/ricardian_assets/eosio.contracts/icons/multisig.png#4fb41d3cf02d0dd2d35a29308e93c2d826ec770d6bb520db668f530764be7153
---

{{level.actor}} revokes the approval previously provided at their {{level.permission}} permission level from the {{proposal_name}} proposal proposed by {{proposer}}.
