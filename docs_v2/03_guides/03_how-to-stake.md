## How to stake

### What staking is

On EOSIO based blockchains, to be able to deploy and then interact with a smart contract via its implemented actions it needs to be backed up by resources allocated on the account where the smart contract is deployed to. The three resource types an EOSIO smart contract developer needs to know about are RAM, CPU and NET. You can __stake__ CPU and NET and you can __buy__ RAM. You will also find that staking/unstaking is at times referred to as delegating/undelegating. The economics of staking is also to provably commit to a promise that you'll hold the staked tokens, either for NET or CPU, for a pre-established period of time, inspite the process of inflation because BPs are rewarded new minted coins for their services every 24 hours.

### Staking tokens for CPU

CPU is processing power, the amount of CPU an account has is measured in microseconds, it is referred to as "cpu bandwidth" on the cleos get account command output and represents the amount of processing time a contract has at its disposal when executing its actions.

To check the amount of CPU staked for an account currently:
```
cleos get account eostutorial1
```

The commands below stake 1.0000 system tokens, in this case SYS, for CPU bandwidth in addition to what the account has already, and adds zero tokens to NET bandwidth.

To stake to itself:
```
cleos system delegatebw eostutorial1 eostutorial1 "0.0000 SYS" "1.0000 SYS" -p eostutorial1@active
```

To stake for another account, below eostutorial2 stakes for eostutorial1 account:
```
cleos system delegatebw eostutorial2 eostutorial1 "0.0000 SYS" "1.0000 SYS" -p eostutorial2@active
```

### Staking tokens for Bandwidth

As CPU and RAM, NET is also a very important resource in EOSIO-based blockchains. NET is data storage measured in bytes and you need to allocate NET according to how much is needed for your transactions to be stored in the blockchain, or more if you wish so, but not less if you want your contract's actions to function. Be careful to not confuse NET with RAM, RAM stores any random data that the contract wants to store in the blockchain, whereas NET although it is also storage space, it measures the size of the transactions.

To check the amount of CPU staked for an account currently:
```
cleos get account eostutorial1
```

The commands below stake 1.0000 system tokens, in this case SYS, for NET bandwidth in addition to what the account has already, and adds zero tokens to CPU bandwidth.

To stake to itself:
```
cleos system delegatebw eostutorial1 eostutorial1 "1.0000 SYS" "0.0000 SYS" -p eostutorial1@active
```

To stake for another account, below eostutorial2 stakes for eostutorial1 account:
```
cleos system delegatebw eostutorial2 eostutorial1 "1.0000 SYS" "0.0000 SYS" -p eostutorial2@active
```
