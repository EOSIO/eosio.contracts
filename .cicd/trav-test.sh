#!/bin/bash
set -e
CPU_CORES=$(getconf _NPROCESSORS_ONLN)
curl -LO https://github.com/EOSIO/eosio.cdt/releases/download/v1.6.2/eosio.cdt_1.6.2-1-ubuntu-18.04_amd64.deb && dpkg -i eosio.cdt_1.6.2-1-ubuntu-18.04_amd64.deb && export PATH=/usr/opt/eosio.cdt/1.6.2/bin:$PATH
[[ -d "build" ]] && rm -rf build
mkdir /workdir/build
cd /workdir/build
echo '$ cmake ..'
cmake ..
echo "$ make -j $CPU_CORES"
make -j $CPU_CORES
cd /workdir/build/tests
TEST_COUNT=$(ctest -N | grep -i 'Total Tests: ' | cut -d ':' -f 2 | awk '{print $1}')
[[ $TEST_COUNT > 0 ]] && echo "$TEST_COUNT tests found." || (echo "ERROR: No tests registered with ctest! Exiting..." && exit 1)
echo "$ ctest -j $CPU_CORES"
ctest -j $CPU_CORES
echo 'Done.'