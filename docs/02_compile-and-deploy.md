## How to compile the eosio.contracts

### Preconditions
`eosio.cdt` should be installed already, if you do not have it already follow the [`eosio.cdt` installation instructions steps](https://github.com/EOSIO/eosio.cdt/tree/master/#binary-releases). To verify if you have `eosio.cdt` installed and its version run the following command 

```sh
eosio-cpp -v
```

To compile the `eosio.contracts` execute the following commands.

On all platforms except macOS:
```sh
cd you_local_path_to/eosio.contracts/
rm -fr build
mkdir build
cd build
cmake ..
make -j$( nproc )
cd ..
```

For macOS
```sh
cd you_local_path_to/eosio.contracts/
rm -fr build
mkdir build
cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
cd ..
```

### After build:
* If the build was configured to also build unit tests, the unit tests executable is placed in the _build/tests_ folder and is named __unit_test__.
* The contracts (both `.wasm` and `.abi` files) are built into their corresponding _build/contracts/\<contract name\>_ folder.
* Finally, simply use __cleos__ to _set contract_ by pointing to the previously mentioned directory for the specific contract.

## To deploy eosio.bios contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testerbios`
```
cleos set contract testerbios you_local_path_to/eosio.contracts/build/contracts/eosio.bios/ -p testerbios
```

## To deploy eosio.msig contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testermsig`
```
cleos set contract testermsig you_local_path_to/eosio.contracts/build/contracts/eosio.msig/ -p testermsig
```

## To deploy eosio.system contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testersystem`
```
cleos set contract testersystem you_local_path_to/eosio.contracts/build/contracts/eosio.system/ -p testersystem
```

## To deploy eosio.token contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testertoken`
```
cleos set contract testertoken you_local_path_to/eosio.contracts/build/contracts/eosio.token/ -p testertoken
```

## To deploy eosio.wrap contract execute the following command:
Let's assume your account name to which you want to deploy the contract is `testerwrap`
```
cleos set contract testerwrap you_local_path_to/eosio.contracts/build/contracts/eosio.wrap/ -p testerwrap
```