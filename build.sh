#! /bin/bash

contracts=( "eosio.token"
            "eosio.system"
            "eosio.msig"
            "eosio.sudo" )

unamestr=`uname`
if [[ "${unamestr}" == 'Darwin' ]]; then
   PREFIX=/usr/local
   BOOST=/usr/local
   OPENSSL=/usr/local/opt/openssl
else
   PREFIX=~/opt
   BOOST=~/opt/boost/include
   OPENSSL=/usr/include/openssl
fi

EOSIO_PREFIX=/usr/local

export BOOST=${BOOST}
export PREFIX=${PREFIX}

### Build all the contracts

for contract in "${contracts[@]}"; do
   pushd ${contract} &> /dev/null
   echo "Building ${contract}..."
   CONTRACT_NAME="${contract}"
   ./build.sh
   popd &> /dev/null
done


if [ "$1" == "notests" ]; then
   exit 0
fi

### Build the unit tests
root_dir=`pwd`
pushd tests &> /dev/null
mkdir -p build
pushd build &> /dev/null
cmake -DROOT_DIR="${root_dir}" -DEOSIO_INSTALL_PREFIX="${EOSIO_PREFIX}" -DOPENSSL_INSTALL_PREFIX="${OPENSSL}" -DSECP256K1_INSTALL_LIB="${EOSIO_PREFIX}" -DBOOST_ROOT="${BOOST}" ../
make -j8
cp unit_test ../../
popd &> /dev/null
rm -r build
popd &> /dev/null
