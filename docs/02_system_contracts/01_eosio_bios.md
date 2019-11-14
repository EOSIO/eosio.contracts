## eosio.bios system contract

The `eosio.bios` is the first sample of system smart contract provided by `block.one` through the EOSIO platform. It is a minimalist system contract because it only supplies the actions that are absolutely critical to bootstrap a chain and nothing more. This allows for a chain agnostic approach to bootstrapping a chain.

The actions implemented and publicly exposed by `eosio.bios` system contract are: setpriv, setalimits, setglimits, setprods, setparams, reqauth, setabi.

|Action name|Action description|
|---|---|
|setpriv|Set privilege status for an account.|
|setalimits|Set the resource limits of an account|
|setglimits|Not implemented yet.|
|setprods|Set a new list of active producers, that is, a new producers' schedule.|
|setparams|Set the blockchain parameters.|
|reqauth|Check if an account has authorization to access the current action.|
|setabi|Set the abi for a contract identified by an account name.|

The above actions are enough to serve the functionality of a basic blockchain, however, a keen eye would notice that the actions listed above do not allow for creation of an account, nor updating permissions, and other important features. As we mentioned earlier, this sample system contract is minimalist in its implementation, therefore it relies also on some native EOSIO actions. These native actions are not implemented in the `eosio.bios` system contract, they are implemented at the EOSIO chain core level. In the `eosio.bios` contract they are simply declared and have no implementation, so they can show in the contracts ABI definition, and therefore users can push these actions to the account that holds the `eosio.bios` contract. When one of these actions are pushed to the chain, to the `eosio.bios` contract account holder, via a `cleos` command for example, the corresponding native action is executed by the blockchain first, [see the code here](https://github.com/EOSIO/eos/blob/3fddb727b8f3615917707281dfd3dd3cc5d3d66d/libraries/chain/apply_context.cpp#L58), and then the `eosio.bios` contract `apply` method is invoked, [see the code here](https://github.com/EOSIO/eos/blob/3fddb727b8f3615917707281dfd3dd3cc5d3d66d/libraries/chain/apply_context.cpp#L69), but having no implementation and not being part of the `EOSIO_DISPATCH`, at the contract level, this action will be a NOP, it will do nothing when called from core EOSIO code.

Below are listed the actions which are declared in the `eosio.bios` contract, mapped one-to-one with the native EOSIO actions, but having no implementation at the contract level:

|Action name|Description|
|---|---|
|newaccount|Called after a new account is created. This code enforces resource-limit rules for new accounts as well as new account naming conventions.|
|updateauth|Updates the permission for an account.|
|deleteauth|Delete permission for an account.|
|linkauth|Assigns a specific action from a contract to a permission you have created.|
|unlinkauth|Assigns a specific action from a contract to a permission you have created.|
|canceldelay|Allows for cancellation of a deferred transaction.|
|onerror|Called every time an error occurs while a transaction was processed.|
|setcode|Allows for update of the contract code of an account.|