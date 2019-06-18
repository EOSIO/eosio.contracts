#!/usr/bin/env bash
set -eo pipefail

function usage() {
   printf "Usage: $0 OPTION...
  -e DIR      Directory where EOSIO is installed. (Default: $HOME/eosio/X.Y)
  -c DIR      Directory where EOSIO.CDT is installed. (Default: /usr/local/eosio.cdt)
  -y          Noninteractive mode (Uses defaults for each prompt.)
  -h          Print this help menu.
   \\n" "$0" 1>&2
   exit 1
}

if [ $# -ne 0 ]; then
  while getopts "e:c:yh" opt; do
    case "${opt}" in
      e )
        EOSIO_INSTALL_DIR=$OPTARG
      ;;
      c )
        CDT_INSTALL_DIR=$OPTARG
      ;;
      y )
        NONINTERACTIVE=true
        PROCEED=true
      ;;
      h )
        usage
      ;;
      ? )
        echo "Invalid Option!" 1>&2
        usage
      ;;
      : )
        echo "Invalid Option: -${OPTARG} requires an argument." 1>&2
        usage
      ;;
      * )
        usage
      ;;
    esac
  done
fi

printf "\t=========== Building eosio.contracts ===========\n\n"

# Load helper functions.
. ./scripts/helper.sh

# Prompt user for installation of eosio.
eosio-directory-prompt
# Prompt user for installation of eosio.cdt.
cdt-directory-prompt

RED='\033[0;31m'
NC='\033[0m'

CORES=`getconf _NPROCESSORS_ONLN`
mkdir -p build
pushd build &> /dev/null
cmake ../
make -j${CORES}
popd &> /dev/null

# TODO: Test cases of multiple EOSIO installations.
# TODO: Test custom EOSIO installation.