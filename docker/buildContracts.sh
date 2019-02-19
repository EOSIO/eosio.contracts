#!/bin/bash
cd /eosio.contracts
./build.sh
cd build
tar -pczf /artifacts/contracts.tar.gz *
