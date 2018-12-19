#!/bin/bash
cd /eosio.contracts
./build.sh
cd build
tar -pczf contracts.tar.gz *