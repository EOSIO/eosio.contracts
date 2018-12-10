## Action - `{{ telos.free.configure_rc }}`

This human-language contract for the telos.free action CONFIGURE is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

Input parameters:

_**max_accounts_per_hour**_ is the maximum number of accounts that the system will create in an hour.

_**stake_cpu_tlos_amount**_ is the amount of TLOS tokens to stake to each new account for CPU resources.

_**stake_net_tlos_amount**_ is the amount of TLOS tokens to stake to each new account for NET resources.

Implied parameters:

_**signer**_ is the account name of the account signing this contract.

### Intent

INTENT. The intention of the authors and the invoker of this contract is to configure the number of new accounts that the `{{telos.free }}` account can create every 60 minutes as well as the number of TLOS tokens allocated to CPU and NET resources for each account. It shall have no other effect.

### Contract Text

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to configure the `{{ telos.free }}` account to be able to create a maximum of {{max_accounts_per_hour}} new accounts per 60 minutes and that each account created will have {{stake_cpu_tlos_amount}} TLOS staked for CPU resources and {{stake_net_tlos_amount}} TLOS staked for NET resources.