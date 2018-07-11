# eosio.contracts

## Version : 1.1.0

The design of the EOSIO blockchain calls for a number of smart contracts that are run at a privileged permission level in order to support functions such as block producer registration and voting, token staking for CPU and network bandwidth, RAM purchasing, multi-sig, etc.  These smart contracts are referred to as the system, token, msig and sudo contracts.

This repository contains examples of these priviledged contracts that are useful when depoying, managing, and/or using an EOSIO blockchain.  They are provided for reference purposes:

   * [eosio.system](https://github.com/eosio/eosio.contracts/tree/master/eosio.system)

   * [eosio.msig](https://github.com/eosio/eosio.contracts/tree/master/eosio.msig)
   * [eosio.sudo](https://github.com/eosio/eosio.contracts/tree/master/eosio.sudo)
   
The following unpriviledged contract(s) are also part of the system. 
   * [eosio.token](https://github.com/eosio/eosio.contracts/tree/master/eosio.token)

Dependencies:
* [eosio v1.0.8](https://github.com/eosio/eos/tree/v1.0.8)
* [eosio.wasmsdk v1.0.0](https://github.com/eosio/eosio.wasmsdk/tree/v1.0.0)

To build the contracts and the unit tests:
* First, ensure that your __eosio__ is compiled to the core symbol for the EOSIO blockchain that intend to deploy to.
* Second, make sure that you have ```sudo make install```ed __eosio__.
* Then just run the ```build.sh``` in the top directory to build all the contracts and the unit tests for these contracts.

After build:
* The unit tests executable is placed in the _build/tests_ and is named __unit_test__.
* The contracts are built into a _bin/\<contract name\>_ folder in their respective directories.
* Finally, simply use __cleos__ to _set contract_ by pointing to the previously mentioned directory.
