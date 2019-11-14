## eosio.wrap system contract
The `eosio.wrap` system contract allows block producers to bypass authorization checks or run privileged actions with 15/21 producer approval and thus simplifies block producers superuser actions. It also makes these actions easier to audit.

It does not give block producers any additional powers or privileges that do not already exist within the EOSIO based blockchains. As it is implemented, in an EOSIO based blockchain, 15/21 block producers can change an account's permissions or modify an account's contract code if they decided it is beneficial for the blockchain and community. 

However, the current method is opaque and leaves undesirable side effects on specific system accounts, and thus the `eosio.wrap `contract solves this matter by providing an easier method of executing important governance actions.

The only action implemented by the `eosio.wrap` system contract is the `exec` action. This action allows for execution of a transaction, which is passed to the `exec` method in the form of a packed transaction in json format via the 'trx' parameter and the `executer` account that executes the transaction. The same `executer` account will also be used to pay the RAM and CPU fees needed to execute the transaction.

Why is it easier for governance actions to be executed via this contract?
The answer to this question is explained in detailed [here](../04_guides/07_how-to-use-eosio.wrap.md)