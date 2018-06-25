#! /bin/bash

CONTRACT_NAME="eosio.system"
unamestr=`uname`

if [[ "${unamestr}" == 'Darwin' ]]; then
   PREFIX=/usr/local
   OPENSSL=/usr/local/opt/openssl
else
   PREFIX=~/opt
   BOOST=~/opt/boost/include
   OPENSSL=/usr/include/openssl
fi

mkdir -p bin/${CONTRACT_NAME}
### BUILD THE CONTRACT
EOSCLANG="${PREFIX}/wasm/bin/clang++ -I/usr/local/include/libc++/upstream/include -I/usr/local/include/musl/upstream/include -I/usr/local/include -Ideps/eosio.token/include -I${BOOST}"
LINK="${PREFIX}/wasm/bin/llvm-link -only-needed "
LLC="${PREFIX}/wasm/bin/llc -thread-model=single --asm-verbose=false"
S2W="/usr/local/bin/eosio-s2wasm "
W2W="/usr/local/bin/eosio-wast2wasm "

deps=( "eosio.token" )

for dep in "${deps[@]}"; do
   pushd ./deps/${dep} &> /dev/null
   ./build.sh notests
   popd &> /dev/null
done

echo "building eosio.system"
${EOSCLANG}  -Iinclude -c -emit-llvm -O3 --std=c++14 --target=wasm32 -nostdinc -DBOOST_DISABLE_ASSERTS -DBOOST_EXCEPTION_DISABLE -nostdlib -nostdlibinc -ffreestanding -nostdlib -fno-threadsafe-statics -fno-rtti -fno-exceptions -o ${CONTRACT_NAME}.bc src/${CONTRACT_NAME}.cpp
${LINK} -o linked.bc ${CONTRACT_NAME}.bc /usr/local/usr/share/eosio/contractsdk/lib/eosiolib.bc /usr/local/usr/share/eosio/contractsdk/lib/libc++.bc /usr/local/usr/share/eosio/contractsdk/lib/libc.bc
${LLC} -o ${CONTRACT_NAME}.s linked.bc
${S2W} -o ${CONTRACT_NAME}.wast -s 16384 ${CONTRACT_NAME}.s
${W2W} ${CONTRACT_NAME}.wast bin/${CONTRACT_NAME}/${CONTRACT_NAME}.wasm -n
cp abi/${CONTRACT_NAME}.abi bin/${CONTRACT_NAME}/${CONTRACT_NAME}.abi

if [[ "$1" == 'notests' ]]; then
   rm ${CONTRACT_NAME}.bc linked.bc ${CONTRACT_NAME}.wast ${CONTRACT_NAME}.s
   exit 0
fi

contract_dir=`pwd`
pushd tests &> /dev/null
mkdir build 
pushd build &> /dev/null
cmake -DCONTRACT_DIR="${contract_dir}" -DEOSIO_INSTALL_PREFIX="/usr/local" -DOPENSSL_INSTALL_PREFIX="${OPENSSL}" -DSECP256K1_INSTALL_LIB="/usr/local" ../
make -j8
popd &> /dev/null
popd &> /dev/null
cp tests/build/unit_test bin/
rm -r tests/build

if [[ "$1" == 'noinstall' ]]; then
   rm ${CONTRACT_NAME}.bc linked.bc ${CONTRACT_NAME}.wast ${CONTRACT_NAME}.s
   exit 0
fi

### INSTALL THE HEADERS
cp -r include/* /usr/local/include
cp build/unit_tests bin/

rm ${CONTRACT_NAME}.bc linked.bc ${CONTRACT_NAME}.wast ${CONTRACT_NAME}.s
