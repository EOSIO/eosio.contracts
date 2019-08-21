#!/usr/bin/env bash
set -eo pipefail
echo ""
. ./.cicd/helpers/general.sh
. ./.cicd/helpers/dependency-info.sh

mkdir -p $BUILD_DIR

FULL_TAG=${FULL_TAG:-eosio/ci-contracts-builder:base-ubuntu-18.04-$BRANCH}
ARGS=${ARGS:-"--rm -v $(pwd):$MOUNTED_DIR"}
CDT_COMMANDS="apt-get install -y wget && wget -q $CDT_URL -O eosio.cdt.deb && dpkg -i eosio.cdt.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:$PATH"

PRE_COMMANDS="$CDT_COMMANDS && cd $MOUNTED_DIR/build"
BUILD_COMMANDS="cmake .. && make -j $JOBS"

COMMANDS="$PRE_COMMANDS && $BUILD_COMMANDS"

# Load BUILDKITE Environment Variables for use in docker run
if [[ -f $BUILDKITE_ENV_FILE ]]; then
    evars=""
    while read -r var; do
        evars="$evars --env ${var%%=*}"
    done < "$BUILDKITE_ENV_FILE"
fi
echo 'derp3'
eval docker run $ARGS $evars $FULL_TAG bash -c \"$COMMANDS\"