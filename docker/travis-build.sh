#!/bin/bash
set -e
CPU_CORES=$(getconf _NPROCESSORS_ONLN)
cd /eosio.contracts
[[ -d "build" ]] && rm -rf build
mkdir build
cd build
echo '$ cmake ..'
cmake ..
echo "$ make -j $CPU_CORES"
make -j $CPU_CORES
echo "$ ctest -j $CPU_CORES"
ctest -j $CPU_CORES
echo 'Done.'