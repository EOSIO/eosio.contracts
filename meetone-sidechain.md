## How to build eosio.system

```
cd eosio.system
eosio-cpp src/eosio.system.cpp -o eosio.system.wasm -I=./include -I=../ -I=../eosio.token/include -I=/usr/local/include
cd ..
cmake .
cd eosio.system
make
```