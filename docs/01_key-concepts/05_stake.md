---
content_title: Staking on EOSIO based blockchains
link_text: Staking on EOSIO based blockchains
---

## Fundamental Resources

EOSIO based blockchains work with three fundamental resources:

* [RAM](02_ram.md),
* [CPU](03_cpu.md) and
* [NET](04_net.md).

## How Tp Allocate Resources

Smart contracts deployed on EOSIO based blockchains need sufficient fundamental resources, RAM, CPU and NET, for the blockchain to be able to execute their code.

### Stake NET and CPU

The CPU and NET resources are allocated by the smart contract developer via the staking mechanism on the account where the smart contract is deployed to, refer to the [cleos manual](https://developers.eos.io/manuals/eos/v2.0/cleos/how-to-guides/how-to-stake-resource) on how to do it via the command line interface.

You will also find that staking/unstaking is at times referred to as delegating/undelegating. The economics of staking is also to provably commit to a promise that you'll hold the staked tokens, either for NET or CPU, for a pre-established period of time, in spite of inflation caused by minting new tokens in order to reward BPs for their services every 24 hours.

When you stake tokens for CPU and NET, you gain access to system resources proportional to the total amount of tokens staked by all other users for the same resource at the same time. This means you can perform transactions at no cost but in the limitations of the staked tokens. The staked tokens guarantee the proportional amount of resources regardless of any variations in the free market. If a smart contract used all its allocated CPU and NET, it needs to wait 24 hours when the system will replenish them or allocate more resources.

### Buy RAM

The RAM resource must be bought using the system token, refer to the [cleos manual](https://developers.eos.io/manuals/eos/v2.0/cleos/how-to-guides/how-to-buy-ram) on how to do it via the command line interface. When a smart contract used all its allocated RAM it will not be able to store any additional information on the blockchain database until it frees some of the occupied RAM or more is allocated to the smart contract account.
