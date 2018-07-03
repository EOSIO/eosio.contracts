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
	OS_NAME=$( cat /etc/os-release | grep ^NAME | cut -d'=' -f2 | sed 's/\"//gI' )

	case "$OS_NAME" in
		"Amazon Linux AMI")
			CXX_COMPILER=g++
			C_COMPILER=gcc
		;;
		"CentOS Linux")
			CXX_COMPILER=g++
			C_COMPILER=gcc
		;;
		"elementary OS")
			CXX_COMPILER=clang++-4.0
			C_COMPILER=clang-4.0
		;;
		"Fedora")
			CXX_COMPILER=g++
			C_COMPILER=gcc
		;;
		"Linux Mint")
			CXX_COMPILER=clang++-4.0
			C_COMPILER=clang-4.0
		;;
		"Ubuntu")
			CXX_COMPILER=clang++-4.0
			C_COMPILER=clang-4.0
		;;
		*)
			printf "\\n\\tUnsupported Linux Distribution. Exiting now.\\n\\n"
			exit 1
	esac
fi


CXX_COMPILER=clang++-4.0

EOSIO_PREFIX=/usr/local

export BOOST=${BOOST}
export PREFIX=${PREFIX}
export INSTALL_PREFIX=/usr/local

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
cmake -DCMAKE_CXX_COMPILER="${CXX_COMPILER}" -DROOT_DIR="${root_dir}" -DEOSIO_INSTALL_PREFIX="${EOSIO_PREFIX}" -DOPENSSL_INSTALL_PREFIX="${OPENSSL}" -DSECP256K1_INSTALL_LIB="${EOSIO_PREFIX}" -DBOOST_ROOT="${BOOST}" ../
make -j8
cp unit_test ../../
popd &> /dev/null
rm -r build
popd &> /dev/null
