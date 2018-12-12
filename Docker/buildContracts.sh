#!/bin/bash
cd /eosio.contracts
./build.sh
tar -pczf contracts.tar.gz build/*