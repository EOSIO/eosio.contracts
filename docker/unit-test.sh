#!/bin/bash
set -e # exit on failure of any "simple" command (excludes &&, ||, or | chains)
CPU_CORES=$(getconf _NPROCESSORS_ONLN)
echo "$CPU_CORES cpu cores detected."
cd /eosio.contracts/build/tests
echo "$ ctest -j $CPU_CORES --output-on-failure -T Test"
ctest -j $CPU_CORES --output-on-failure -T Test
mv /eosio.contracts/build/tests/Testing/$(ls /eosio.contracts/build/tests/Testing/ | grep '20' | tail -n 1)/Test.xml /artifacts/Test.xml