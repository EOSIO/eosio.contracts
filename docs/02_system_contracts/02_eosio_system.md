## [eosio.system system contract](action-reference/eosio.system)

The `eosio.system` contract is another smart contract that Block.one provides an implementation for as a sample system contract.  It is a version of `eosio.bios` only this time it is not minimalist, it contains more elaborated structures, classes, methods, and actions needed for an EOSIO based blockchain core functionality.

Just like the `eosio.bios` sample contract there are a few actions which are not implemented at the contract level (`newaccount`, `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, `canceldelay`, `onerror`, `setabi`, `setcode`), they are just declared in the contract so they will show in the contract's ABI and users will be able to push those actions to the chain via the account holding the 'eosio.system' contract, but the implementation is at the EOSIO core level. They are referred to as EOSIO native actions.

The actions implemented and publicly exposed by the `eosio.system` system contract are detailed in the [eosio.system reference documentation](action-reference/eosio.system).

