# eosio.contracts

## Version : 1.0.0

This repo houses the following contracts
   * [eosio.system](https://github.com/eosio/eosio.contracts/tree/master/eosio.system)
   * [eosio.token](https://github.com/eosio/eosio.contracts/tree/master/eosio.token)
   * [eosio.msig](https://github.com/eosio/eosio.contracts/tree/master/eosio.msig)
   * [eosio.sudo](https://github.com/eosio/eosio.contracts/tree/master/eosio.sudo)

Dependencies:
* [eos v1.0.8](https://github.com/eosio/eos/tree/v1.0.8)

To build the contracts and the unit tests:
* First, ensure that your __eos__ is compiled to the symbol that you are wanting to target.
* Second, make sure that you have ```sudo make install```ed __eos__.
* Then just run the ```build.sh``` in the top directory to build all the contracts and the unit tests for these contracts. If you want to skip building the unit tests, the option ```notests``` can be given to ```build.sh```.
* Or, you can run the ```build.sh``` in a given contract folder to only build that contract.

After build:
* The unit tests executable is placed in the top directory and is named __unit_test__.
* The contracts are built into a _bin/\<contract name\>_ folder in their respective directories.
* Finally, simply use __cleos__ to _set contract_ by pointing to the previously mentioned directory.
