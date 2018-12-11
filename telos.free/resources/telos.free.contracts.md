<h1 class="contract">create</h1>

This human-language contract for the telos.free action CREATE is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

Input parameters:

* **new_account** (12-character name of the new account

* **owner_key** (owner public key used to associate with the account)

* **active_key** (active public key used to associate with the account)

* **key_prefix** (prefix for the owner and active public keys. Set to 'EOS' for chains using EOS public key prefixes)

### Intent

The intention of the authors and the invoker of this contract is to create a new Telos account without cost to the invoker. **The authors intend that only one account ever per individual shall be created using this contract with future accounts being created from the invoker's one free account at invoker's own expense.** This contract shall have no other effect.

### Body

I attest that I am the intended owner or authorized user of the new account to be created: {{new_account}} and that I have not previously used this contract to create a free account for myself or for the same individual for whom I am creating {{new_account}}. **I agree that if I am found by a Telos Elected Arbitrator of having violated this limitation, that I may be held liable for damages in excess of the amount of TLOS used to create the accounts including the full cost of the arbitral trail and arbitrator's fees.**

In invoking this action, I intend to create the account {{new_account}} with the owner public key of {{owner_key}} and the active public key of {{active_key}} for which I control and safely retain the corresponding private keys. The key prefix for the Telos Blockchain Network is `EOS` and I have input {{key_prefix}}.

<h1 class ="contract">configure</h1>

This human-language contract for the telos.free action CONFIGURE is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

Input parameters:

* **max_accounts_per_hour** (maximum number of accounts that the system will create in an hour)

* **stake_cpu_tlos_amount** (amount of TLOS tokens to stake to each new account for CPU resources)

* **stake_net_tlos_amount** (amount of TLOS tokens to stake to each new account for NET resources)

Implied parameters:

* **signer** (account name of the account signing this contract)

### Intent

INTENT. The intention of the authors and the invoker of this contract is to configure the number of new accounts that the `{{telos.free }}` account can create every 60 minutes as well as the number of TLOS tokens allocated to CPU and NET resources for each account. It shall have no other effect.

### Contract Text

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to configure the `{{ telos.free }}` account to be able to create a maximum of {{max_accounts_per_hour}} new accounts per 60 minutes and that each account created will have {{stake_cpu_tlos_amount}} TLOS staked for CPU resources and {{stake_net_tlos_amount}} TLOS staked for NET resources.
