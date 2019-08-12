## How to compile the eosio.contracts

To compile the eosio.contracts execute the following commands.

On all platforms except macOS:
```
cd you_local_path_to/eosio.contracts/
rm -fr build
mkdir build
cd build
cmake ..
make -j$( nproc )
cd ..
```

For macOS
```
cd you_local_path_to/eosio.contracts/
rm -fr build
mkdir build
cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
cd ..
```

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