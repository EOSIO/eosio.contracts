#!/usr/bin/env bash
set -eo pipefail
. ./.cicd/helpers/general.sh

mkdir -p $BUILD_DIR

CDT_VERSION=${CDT_VERSION:-1.6.2}
FULL_TAG=${FULL_TAG:-eosio/ci-contracts-builder:base-ubuntu-18.04-trav-poc-standardization}
ARGS=${ARGS:-"--rm -v $(pwd):$MOUNTED_DIR"}
CDT_COMMANDS="curl -LO https://github.com/EOSIO/eosio.cdt/releases/download/v$CDT_VERSION/eosio.cdt_$CDT_VERSION-1-ubuntu-18.04_amd64.deb && dpkg -i eosio.cdt_$CDT_VERSION-1-ubuntu-18.04_amd64.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:$PATH"

[[ -z $CDT_VERSION ]] && echo "Please specify CDT_VERSION." && exit 1

PRE_COMMANDS="cd $MOUNTED_DIR/build && $CDT_COMMANDS"
BUILD_COMMANDS="cmake .. && make -j $JOBS"

COMMANDS="$PRE_COMMANDS && $BUILD_COMMANDS"

[[ $BUILDKITE == true ]] && $CICD_DIR/contracts-docker.sh

# Load BUILDKITE Environment Variables for use in docker run
if [[ -f $BUILDKITE_ENV_FILE ]]; then
    evars=""
    while read -r var; do
        evars="$evars --env ${var%%=*}"
    done < "$BUILDKITE_ENV_FILE"
fi

eval docker run $ARGS $evars $FULL_TAG bash -c \"$COMMANDS\"