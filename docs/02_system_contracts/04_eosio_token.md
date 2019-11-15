## [eosio.token system contract](action-reference/eosio.token)

The `eosio.token` contract defines the structures and actions that allow users to create, issue, and manage tokens for EOSIO based blockchains.

The `eosio.token` sample contract demonstrates one way to implement a smart contract which allows for creation and management of tokens. This contract gives anyone the ability to create a token. It is possible for one to create a similar contract which suits different needs.  However, it is recommended that if one only needs a token with the above listed actions, that one uses the `eosio.token` contract instead of developing their own.

The `eosio.token` contract class also implements two useful public static methods: `get_supply` and `get_balance`. The first allows one to check the total supply of a specified token, created by an account and the second allows one to check the balance of a token for a specified account (the token creator account has to be specified as well).

The `eosio.token` contract manages the set of tokens, accounts and their corresponding balances, by using two internal multi-index structures: the `accounts` and `stats`. The `accounts` multi-index table holds, for each row, instances of `account` object and the `account` object holds information about the balance of one token. The `accounts` table is scoped to an eosio account, and it keeps the rows indexed based on the token's symbol.  This means that when one queries the `accounts` multi-index table for an account name the result is all the tokens that account holds at the moment.

Similarly, the `stats` multi-index table, holds instances of `currency_stats` objects for each row, which contains information about current supply, maximum supply, and the creator account for a symbol token. The `stats` table is scoped to the token symbol.  Therefore, when one queries the `stats` table for a token symbol the result is one single entry/row corresponding to the queried symbol token if it was previously created, or nothing, otherwise.

The actions implemented and publicly exposed by the `eosio.token` contract are detailed in the [eosio.token reference documentation](action-reference/eosio.token).