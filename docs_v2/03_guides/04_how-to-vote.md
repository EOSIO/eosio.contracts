## How to vote

### What voting is

In a EOSIO-based network the blockchain is kept alive by nodes which are interconnected into a mesh, communicating with each other via peer to peer protocols. Some of these blocks are elected, via a __voting__ process, by the token holders to be producer nodes. They produce blocks, validate them and reach consensus on what transactions are allowed in each block, their order, and what blocks are finalized and stored forever in the blockchain memory. This way the governance, the mechanism by which collective decisions are made, of the blockchain is achieved through the 21 active block producers which are appointed by token holders' __votes__. It's the 21 active block producers which continuously create the blockchain by creating blocks, and securing them by validating them, and reaching consensus. Consensus is reached when 2/3+1 active block producers agree on validity of a block, that is all transactions contained in it and their order.

### How to vote

To __vote__ block producers execute below command, which allows one account to vote for as up to 30 block producer identified by their account name; in this particular example account eostutorial1 votes for 3 producers accounts: accountprod1, accountprod2 and accountprod3.
```
cleos system voteproducer prods eostutorial1 accountprod1 accountprod2 accountprod3
```