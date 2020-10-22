---
content_title: RAM as resource
link_text: RAM as resource
---

## What is RAM

RAM is the memory, the storage space, where the blockchain stores data. If your contract needs to store data on the blockchain, like in a database, then it can store it in the blockchain's RAM using either a `multi-index table` or a `singleton`.

### Related documentation articles

- Multi-index table [explainer documentation page](https://developers.eos.io/manuals/eosio.cdt/latest/group__multiindex)

- Multi-index table [how to documentation page](https://developers.eos.io/manuals/eosio.cdt/latest/how-to-guides/multi-index)

- Singleton [reference documentation page](https://developers.eos.io/manuals/eosio.cdt/latest/group__singleton/#singleton-table) 

- Singleton [how to documentation page](https://developers.eos.io/manuals/eosio.cdt/latest/how-to-guides/multi-index/how-to-define-a-singleton)

## RAM High Performance

The EOSIO-based blockchains are known for their high performance, which is achieved also because the data stored on the blockchain is using RAM as the storage medium, and thus access to blockchain data is very fast, helping the performance benchmarks to reach levels no other blockchain has been able to.

## RAM Importance

RAM is a very important resource because of the following reasons

- It is a limited resource, each EOSIO-based blockchain can have a different policy and rules around RAM; for example the public EOS blockchain started with 64GB of RAM and after that the block producers decided to increase the memory with 1KB per block, thus increasing constantly the supply of RAM for its price to not grow too high due to the increased demand from blockchain applications.

- RAM is used in executing many actions sent to the blockchain; creating a new account action, for example, it needs to store in the blockchain memory the new account's information; also when an account accepts a new type of token a new record has to be created, somewhere in the blockchain memory, that holds the balance of the new token accepted, and that memory, the storage space on the blockchain, has to be purchased either by the account that transfers the token or by the account that accepts the new token type.

- When a smart contract used all its allocated RAM it will not be able to store any additional information on the blockchain database until it frees some of the occupied RAM or more is allocated to the smart contract account.

RAM is a scarce resource priced according to the unique Bancor liquidity algorithm which is implemented in the system contract [here](https://github.com/EOSIO/eos/blob/905e7c85714aee4286fa180ce946f15ceb4ce73c/contracts/eosio.system/exchange_state.hpp).

The RAM resource must be bought using the system token, refer to the [cleos manual](https://developers.eos.io/manuals/eos/v2.0/cleos/how-to-guides/how-to-buy-ram) on how to do it via the command line interface.
