---
content_title: RAM as resource
link_text: RAM as resource
---

RAM is the memory, storage space, where the blockchain stores data. If your contract needs to store data on the blockchain, like in a database, then it can store it in the blockchain's RAM using either a `multi-index table`, which is explained [here](https://developers.eos.io/manuals/eosio.cdt/latest/group__multiindex) and its usages [here](https://developers.eos.io/manuals/eosio.cdt/latest/how-to-guides/multi-index) or a `singleton`, with its definition found [here](https://developers.eos.io/manuals/eosio.cdt/latest/group__singleton/#singleton-table) and a sample of its usage [here](https://developers.eos.io/manuals/eosio.cdt/latest/how-to-guides/multi-index/how-to-define-a-singleton).

The EOSIO-based blockchains are known for their high performance, which is achieved also because the data stored on the blockchain is using RAM as the storage medium, and thus access to blockchain data is very fast, helping the performance benchmarks to reach levels no other blockchain has been able to.

RAM is a very important resource because of the following reasons: it is a limited resource, each EOSIO-based blockchain can have a different policy and rules around RAM, for example the public EOS blockchain started with 64GB of RAM and after that the block producers decided to increase the memory with 1KiB (1024 bytes) per day, thus increasing constantly the supply of RAM for the price of RAM to not grow too high because of the increased demand from blockchain applications; also RAM it is used in executing many actions that are available on the blockchain, creating a new account for example (it needs to store in the blockchain memory the new account's information), also when an account accepts a new type of token a new record has to be created somewhere in the blockchain memory that holds the balance of the new token accepted, and that memory, the storage space on the blockchain, has to be purchased either by the account that transfers the token or by the account that accepts the new token type.

RAM is a scarce resource priced according to the unique Bancor liquidity algorithm which is implemented in the system contract [here](https://github.com/EOSIO/eos/blob/905e7c85714aee4286fa180ce946f15ceb4ce73c/contracts/eosio.system/exchange_state.hpp).
