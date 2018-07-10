#! /bin/bash

printf "\t=========== Building eosio.contracts ===========\n\n"

RED='\033[0;31m'
NC='\033[0m'

if [ ! -d "/usr/local/eosio" ]; then
   printf "${RED}Error, please ensure that eosio is installed correctly!\n\n${NC}"
   exit -1
fi

if [ ! -d "/usr/local/eosio.wasmsdk" ]; then
   printf "${RED}Error, please ensure that eosio.wasmsdk is installed correctly!\n\n${NC}"
   exit -1
fi

unamestr=`uname`
if [[ "${unamestr}" == 'Darwin' ]]; then
   BOOST=/usr/local
   CXX_COMPILER=g++
else
   BOOST=~/opt/boost
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

CORES=`getconf _NPROCESSORS_ONLN`
mkdir -p build
pushd build &> /dev/null
cmake -DCXX_COMPILER="${CXX_COMPILER}" -DBOOST_ROOT="${BOOST}" -DEOSIO_INSTALL_PREFIX=/usr/local ../
make -j${CORES}
popd &> /dev/null
