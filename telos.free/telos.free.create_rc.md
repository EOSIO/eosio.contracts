## Action - `{{ telos.free.create }}`

This human-language contract for the telos.free action CREATE is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

Input parameters:

_**new_account**_ is the 12-character name of the new account

_**owner_key**_ is the owner public key used to associate with the account

_**active_key**_ is the active public key used to associate with the account

_**key_prefix**_ is the prefix for the owner and active public keys. Set to 'EOS' for chains using EOS public key prefixes

### Intent

The intention of the authors and the invoker of this contract is to create a new Telos account without cost to the invoker. **The authors intend that only one account ever per individual shall be created using this contract with future accounts being created from the invoker's one free account at invoker's own expense.** This contract shall have no other effect.

### Contract Text

I attest that I am the intended owner or authorized user of the new account to be created: {{new_account}} and that I have not previously used this contract to create a free account for myself or for the same individual for whom I am creating {{new_account}}. **I agree that if I am found by a Telos Elected Arbitrator of having violated this limitation, that I may be held liable for damages in excess of the amount of TLOS used to create the accounts including the full cost of the arbitral trail and arbitrator's fees.**

In invoking this action, I intend to create the account {{new_account}} with the owner public key of {{owner_key}} and the active public key of {{active_key}} for which I control and safely retain the corresponding private keys. The key prefix for the Telos Blockchain Network is `EOS` and I have input {{key_prefix}}.