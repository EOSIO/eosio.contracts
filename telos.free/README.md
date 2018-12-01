# Telos Free Account Creation Contract

One of the promises of the Telos Blockchain Network is to provide the first 1,000,000 accounts for free. To help make this promise a reality, this smart contract was designed to support the creation of free Telos accounts for users taking advantage of tools such as Sqrl. In this document, we briefly describe how the Free Account Creation smart contract works.

There are two actions allowed in this contract:
* `configure( int16_t max_accounts_per_hour )`
* `create( name new_account, string owner_key, string active_key, string key_prefix )`

## Configuring Account Creation Limits
To minimize the creation of spam accounts on the Telos Network, the `configure` action accepts a `max_accounts_per_hour` value to limit the number of free accounts that can be created every 60 minutes. This defaults to 50 accounts.

## Creating Accounts
The `create` action requires four (4) parameters before an account can be successfully created.

`new_account` - this is the 12-character name of the new account
`owner_key` - this is the owner public key used to associate with the account
`active_key` - this is the active public key used to associate with the account
`key_prefix` - this is the prefix for the owner and active public keys. Set to 'EOS' for chains using EOS public key prefixes

## How It Works
Once configured with a `max_accounts_per_hour` value, calls to the `create` action performs the following steps:

1. Verify that the number of accounts created within the last hour does not exceed `max_accounts_per_hour`
2. Validates the owner and active public keys
3. Allocates `2 TLOS` worth of resources for the account. `1 TLOS` is used to `buyram`, `0.50 TLOS` delegated to CPU and `0.50` TLOS delegated to bandwidth
4. The system's `newaccount`, `buyram`, and `delegatebw` actions are then called with the aforementioned settings
5. An entry is created in the `freeacctlogs` table for auditing







