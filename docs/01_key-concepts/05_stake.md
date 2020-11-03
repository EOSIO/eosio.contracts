---
content_title: Staking on EOSIO-based blockchains
link_text: Staking on EOSIO-based blockchains
---

## System Resources

EOSIO-based blockchains work with three system resources:

* [RAM](02_ram.md),
* [CPU](03_cpu.md) and
* [NET](04_net.md).

## How To Allocate System Resources

Smart contracts deployed on EOSIO-based blockchains need sufficient system resources, RAM, CPU and NET, for the blockchain to be able to execute their code.

### Stake NET and CPU

The CPU and NET system resources are allocated by the smart contract developer via the staking mechanism on the account where the smart contract is deployed to. Refer to the [cleos manual](https://developers.eos.io/manuals/eos/v2.0/cleos/how-to-guides/how-to-stake-resource) on how to do it via the command line interface.

You will also find that staking/unstaking is at times referred to as delegating/undelegating. The economics of staking is also to provably commit to a promise that you will hold the staked tokens, either for NET or CPU, for a pre-established period of time, in spite of inflation caused by minting new tokens in order to reward BPs for their services every 24 hours.

When you stake tokens for CPU and NET, you gain access to system resources proportional to the total amount of tokens staked by all other users for the same system resource at the same time. This means you can perform transactions at no cost but in the limits of the staked tokens. The staked tokens guarantee the proportional amount of resources regardless of any variations in the free market.
If a smart contract consumes all its allocated CPU and NET, it needs to wait for the current 24 hours window to finish, when the system will replenish available resources.
Another option is to allocated more resources through the staking mechanism.

Each 24 hours window starts at 00:00:00 UTC and ends at 23:59:59 UTC of the same day. For example, let us assume you staked an amount of system tokens for CPU which gives to your smart contract account 500 ms of CPU time. You can now send actions to your smart contract and the blockchain will execute them. When the blockchain executes a transaction, which corresponds to an action of your smart contract, it subtracts the time it takes to execute the transaction from the total amount of 500 ms and updates the mount of CPU remained available. At any point in time, if you inspect the account's CPU balance, you will see the total amount staked and the amount consumed up to the last executed transaction on behalf of your smart contract.
Each day on the 00:00:00 UTC time the whole amount of available CPU and NET is replenished and your account can use again 500 ms of CPU. However, if you inspect the account's CPU balance, after the replenishing time, it is possible you will see the CPU balance consumed has the same value as before the replenishing time. That is explained because the account's status of CPU and NET is updated at the execution of an action belonging to the smart contract. If no action was executed, after the 24 hours window ended, the account's CPU and NET consumed balances are not updated yet although the full amount of CPU and NET are available. Therefore to see the updated CPU and NET balances, you have to execute an action belonging to the smart contract, and after that inspect its CPU and NET balances to observe the available resources updated.

When smart contract actions use the allocated resources, the amount that can be used in one transaction is limited by predefine [maximum CPU](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1blockchain__parameters#variable-max_transaction_cpu_usage), [minimum CPU](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1blockchain__parameters#variable-min_transaction_cpu_usage), and [maximum NET](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1blockchain__parameters#variable-max_transaction_net_usage) limits. Transactions executed by the blockchain contain one or more actions, and each transaction must consume an amount of CPU and NET which is in the limits defined by the aforementioned blockchain settings.

### Buy RAM

The RAM resource must be bought using the system token. Refer to the [cleos manual](https://developers.eos.io/manuals/eos/v2.0/cleos/how-to-guides/how-to-buy-ram) to learn how to do it via the command line interface. When a smart contract consumes all its allocated RAM it is not be able to store any additional information on the blockchain database until it frees some of the occupied RAM or more RAM is allocated to the smart contract account through the RAM buying process.
