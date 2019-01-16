# eosio.contracts

## Version : 1.5.2

The design of the EOSIO blockchain calls for a number of smart contracts that are run at a privileged permission level in order to support functions such as block producer registration and voting, token staking for CPU and network bandwidth, RAM purchasing, multi-sig, etc.  These smart contracts are referred to as the system, token, msig and wrap (formerly known as sudo) contracts.

This repository contains examples of these privileged contracts that are useful when deploying, managing, and/or using an EOSIO blockchain.  They are provided for reference purposes:

   * [eosio.system](https://github.com/eosio/eosio.contracts/tree/master/eosio.system)
   * [eosio.msig](https://github.com/eosio/eosio.contracts/tree/master/eosio.msig)
   * [eosio.wrap](https://github.com/eosio/eosio.contracts/tree/master/eosio.wrap)

The following unprivileged contract(s) are also part of the system.
   * [eosio.token](https://github.com/eosio/eosio.contracts/tree/master/eosio.token)

Dependencies:
* [eosio v1.4.x](https://github.com/EOSIO/eos/releases/tag/v1.4.6) to [v1.6.x](https://github.com/EOSIO/eos/releases/tag/v1.6.0)
* [eosio.cdt v1.4.x](https://github.com/EOSIO/eosio.cdt/releases/tag/v1.4.1) to [v1.5.x](https://github.com/EOSIO/eosio.cdt/releases/tag/v1.5.0)

To build the contracts and the unit tests:
* First, ensure that your __eosio__ is compiled to the core symbol for the EOSIO blockchain that intend to deploy to.
* Second, make sure that you have ```sudo make install```ed __eosio__.
* Then just run the ```build.sh``` in the top directory to build all the contracts and the unit tests for these contracts.

After build:
* The unit tests executable is placed in the _build/tests_ and is named __unit_test__.
* The contracts are built into a _bin/\<contract name\>_ folder in their respective directories.
* Finally, simply use __cleos__ to _set contract_ by pointing to the previously mentioned directory.
