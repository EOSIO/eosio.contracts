#!/bin/bash
set -eo pipefail
. ./.cicd/helpers/buildkite.sh
. ./.cicd/helpers/general.sh
mkdir -p $BUILD_DIR
if [[ "$BUILDKITE" == 'true' ]]; then
    CDT_URL="$(buildkite-agent meta-data get cdt-url)"
    CDT_VERSION="$(buildkite-agent meta-data get cdt-version)"
    DOCKER_IMAGE="$(buildkite-agent meta-data get docker-image)"
fi
ARGS=${ARGS:-"--rm -v $(pwd):$MOUNTED_DIR"}
CDT_COMMANDS="apt-get install -y wget && wget -q $CDT_URL -O eosio.cdt.deb && dpkg -i eosio.cdt.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:\\\$PATH"
PRE_COMMANDS="$CDT_COMMANDS && cd $MOUNTED_DIR/build/tests"
TEST_COMMANDS="ctest -j $JOBS"
COMMANDS="$PRE_COMMANDS && $TEST_COMMANDS"
eval docker run $ARGS $(buildkite-intrinsics) $DOCKER_IMAGE bash -c \"$COMMANDS\"