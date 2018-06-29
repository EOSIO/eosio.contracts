#! /bin/bash

contracts=( "eosio.token"
            "eosio.system"
            "eosio.msig"
            "eosio.sudo" )

unamestr=`uname`
if [[ "${unamestr}" == 'Darwin' ]]; then
   PREFIX=/usr/local
   OPENSSL=/usr/local/opt/openssl
else
   PREFIX=~/opt
   BOOST=~/opt/boost/include
   OPENSSL=/usr/include/openssl
fi

### Build all the contracts

for contract in "${contracts[@]}"; do
   pushd ${contract} &> /dev/null
   echo "Building ${contract}..."
   CONTRACT_NAME="${contract}"
   ./build.sh ${PREFIX}
   popd &> /dev/null
done


### Build the unit tests
root_dir=`pwd`
pushd tests &> /dev/null
mkdir -p build
pushd build &> /dev/null
cmake -DROOT_DIR="${root_dir}" -DEOSIO_INSTALL_PREFIX="${PREFIX}" -DOPENSSL_INSTALL_PREFIX="${OPENSSL}" -DSECP256K1_INSTALL_LIB="${PREFIX}" ../
make -j8
cp unit_test ../../
popd &> /dev/null
rm -r build
popd &> /dev/null
