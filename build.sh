#! /bin/bash

printf "\t=========== Building eosio.contracts ===========\n\n"

RED='\033[0;31m'
NC='\033[0m'

#if [ ! -d "/usr/local/eosio" ]; then
#   printf "${RED}Error, please ensure that eosio is installed correctly!\n\n${NC}"
#   exit -1
#fi

if [ ! -d "/usr/local/eosio.wasmsdk" ]; then
   printf "${RED}Error, please ensure that eosio.wasmsdk is installed correctly!\n\n${NC}"
   exit -1
fi

CORES=`getconf _NPROCESSORS_ONLN`
mkdir -p build
pushd build &> /dev/null
cmake ../
make -j${CORES}
popd &> /dev/null
