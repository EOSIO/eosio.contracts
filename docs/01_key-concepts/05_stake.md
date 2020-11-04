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

EOSIO-based blockchain accounts need sufficient system resources, RAM, CPU and NET, to interact with the smart contracts deployed on the blockchain.

### Stake NET and CPU

The CPU and NET system resources are allocated by the account owner via the staking mechanism. Refer to the [cleos manual](https://developers.eos.io/manuals/eos/v2.0/cleos/how-to-guides/how-to-stake-resource) on how to do it via the command line interface.

You will also find that staking/unstaking is at times referred to as delegating/undelegating. The economics of staking is also to provably commit to a promise that you will hold the staked tokens, either for NET or CPU, for a pre-established period of time, in spite of inflation caused by minting new tokens in order to reward BPs for their services every 24 hours.

When you stake tokens for CPU and NET, you gain access to system resources proportional to the total amount of tokens staked by all other users for the same system resource at the same time. This means you can execute transactions at no cost but in the limits of the staked tokens. The staked tokens guarantee the proportional amount of resources regardless of any variations in the free market.

If an account consumes all its allocated CPU and NET resources, it has two options:

* It can wait for the blockchain to replenish the consumed resources. You can read more details below about the [system resources replenish algorithm].(05_stake.md#System-Resources-Replenish-Algorithm).
* It can allocate more resources through the staking mechanism.

When an account uses the allocated resources, the amount that can be used in one transaction is limited by predefine [maximum CPU](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1blockchain__parameters#variable-max_transaction_cpu_usage), [minimum CPU](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1blockchain__parameters#variable-min_transaction_cpu_usage), and [maximum NET](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1blockchain__parameters#variable-max_transaction_net_usage) limits. Transactions executed by the blockchain contain one or more actions, and each transaction must consume an amount of CPU and NET which is in the limits defined by the aforementioned blockchain settings.

#### System Resources Replenish Algorithm

EOSIO-based blockchains replenish automatically the consumed system resources, CPU and NET. Before a transaction is executed, by the blockchain, it firsts calculates how much resources, the account executing the transaction, can consume. The calculation uses an exponential moving average with linear extrapolation when data is missing, and it multiplies the currently accumulated average by `(number of blocks in the window - number of blocks since last update) / (number of blocks in the window)`. The window is set as 24 hours window.

This formula has the following outcomes:

* If an account waited `number of blocks in the window` without executing any transaction it resets to zero usage.

* If an account issues a transaction with every block it would always be `(number of blocks in the window - 1) / (number of blocks in the window)`, a very small value, very close to zero. Mathematically it _never_ reaches zero but the EOSIO implementation truncates off the tiny numbers to zero.

* The accounts that execute transactions more often than the ones that execute less transactions, replenish their resources slower than the later. In other words, the more transactions an account executes the slower the replenish of resources.

### Buy RAM

The RAM resource must be bought using the system token. Refer to the [cleos manual](https://developers.eos.io/manuals/eos/v2.0/cleos/how-to-guides/how-to-buy-ram) to learn how to do it via the command line interface. When an account consumes all its allocated RAM can not store any additional information on the blockchain database until it frees some of the occupied RAM or more RAM is allocated to the account through the RAM buying process.
