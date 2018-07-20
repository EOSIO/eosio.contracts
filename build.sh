#! /bin/bash

export SOURCE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

function usage()
{
   printf "\tUsage: %s \n\t[Build Option -o <Debug|Release|RelWithDebInfo|MinSizeRel>] \n\t[Avoid Compiling -a]\n\n" "$0" 1>&2
   exit 1
}

RED='\033[0;31m'
NC='\033[0m'

if [ "${SOURCE_DIR}" == "${PWD}" ]; then
   BUILD_DIR="${PWD}/build"
else
   BUILD_DIR="${PWD}"
fi
CMAKE_BUILD_TYPE=Release
START_MAKE=true

if [ $# -ne 0 ]; then
   while getopts ":o:s:ah" opt; do
      case "${opt}" in
         o )
            options=( "Debug" "Release" "RelWithDebInfo" "MinSizeRel" )
            if [[ "${options[*]}" =~ "${OPTARG}" ]]; then
               CMAKE_BUILD_TYPE="${OPTARG}"
            else
               printf "\n\tInvalid argument: %s\n" "${OPTARG}" 1>&2
               usage
               exit 1
            fi
         ;;
         a)
            START_MAKE=false
         ;;
         h)
            usage
            exit 1
         ;;
         \? )
            printf "\n\tInvalid Option: %s\n" "-${OPTARG}" 1>&2
            usage
            exit 1
         ;;
         : )
            printf "\n\tInvalid Option: %s requires an argument.\n" "-${OPTARG}" 1>&2
            usage
            exit 1
         ;;
         * )
            usage
            exit 1
         ;;
      esac
   done
fi

printf "\t=========== Building eosio.contracts ===========\n\n"

#if [ ! -d "/usr/local/eosio" ]; then
#   printf "${RED}Error, please ensure that eosio is installed correctly!\n\n${NC}"
#   exit -1
#fi

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
			printf "\n\tUnsupported Linux Distribution. Exiting now.\n\n"
			exit 1
	esac
fi

printf ">>>>>>>> CMAKE_BUILD_TYPE=%s\n" "${CMAKE_BUILD_TYPE}"

CORES=`getconf _NPROCESSORS_ONLN`

if [ ! -d "${BUILD_DIR}" ]; then
   if ! mkdir -p "${BUILD_DIR}"
   then
      printf "Unable to create build directory %s.\n Exiting now.\n" "${BUILD_DIR}"
      exit 1;
   fi
fi

if ! pushd "${BUILD_DIR}" &> /dev/null
then
   printf "Unable to enter build directory %s.\n Exiting now.\n" "${BUILD_DIR}"
   exit 1;
fi

cmake -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}" -DCXX_COMPILER="${CXX_COMPILER}" -DBOOST_ROOT="${BOOST}" -DEOSIO_INSTALL_PREFIX=/usr/local/eosio "${SOURCE_DIR}"

if [ "${START_MAKE}" == "false" ]; then
   printf "\n>>>>>>>> eosio.contracts has been successfully configured but not yet built.\n\n"
   popd &> /dev/null
   exit 0
fi

make -j${CORES}

printf "\n>>>>>>>> eosio.contracts has been successfully built.\n\n"
popd &> /dev/null
