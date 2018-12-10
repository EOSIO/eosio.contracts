## Smart Contract - `{{ telos.free }}`

This human-language contract for the `{{ telos.free }}` smart contract is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Intent

This smart contract was designed to be used in streamlining the creation of a first Telos account for users who have no current account. It solves the problem of needing an existing Telos account to create a new one. It is not intended to ever create more than one account per individual. Additional accounts should be created by Telos Members from their own accounts. Creating multiple new free accounts is abuse of this smart contract.

### Actions and Inputs

This smart contract has two actions: `configure()` and `create()`. 

#### Action: `configure` 

Purpose: To configure the number of new accounts that the `{{ telos.free }}` account can create every 60 minutes as well as the number of TLOS tokens allocated to CPU and NET resources for each account.

Input | Input Type | Description
------|------------|------------
_**max_accounts_per_hour**_ | int16_t | the maximum number of accounts that the system will create in an hour.
_**stake_cpu_tlos_amount**_ | int64_t | the amount of TLOS tokens to stake to each new account for CPU resources.
_**stake_net_tlos_amount**_ | int64_t | is the amount of TLOS tokens to stake to each new account for NET resources.

#### Action: `create`

Purpose: To create a new user account and set the owner and active public keys.

Input | Input Type | Description
------|------------|------------
_**new_account**_ | name | the 12-character name of the new account
_**owner_key**_ | string | the owner public key used to associate with the account
_**active_key**_ | string | the active public key used to associate with the account
_**key_prefix**_ | string | the prefix for the owner and active public keys. Set to 'EOS' for chains using EOS public key prefixes, such as Telos.

### Contract Text

I attest that I am the intended owner or authorized user of either existing account {{signer}} or the new account to be created: {{new_account}} and that if I am creating a new account, I have not previously used this contract to create a free account for myself or for the same individual for whom I am creating {{new_account}}. **I agree that if I am found by a Telos Elected Arbitrator of having violated this limitation, that I may be held liable for damages in excess of the amount of TLOS used to create the accounts including the full cost of the arbitral trail and arbitrator's fees.**
