#!/bin/bash
set -eo pipefail
. ./.cicd/helpers/general.sh
. ./.cicd/helpers/dependency-info.sh
mkdir -p $BUILD_DIR
DOCKER_IMAGE="$(buildkite-agent meta-data get docker-image)"
ARGS=${ARGS:-"--rm -v $(pwd):$MOUNTED_DIR"}
CDT_COMMANDS="apt-get install -y wget && wget -q $CDT_URL -O eosio.cdt.deb && dpkg -i eosio.cdt.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:/usr/local/eosio/bin:\\\$PATH"
PRE_COMMANDS="$CDT_COMMANDS && cd $MOUNTED_DIR/build/tests"
TEST_COMMANDS="ctest -j $JOBS"
COMMANDS="$PRE_COMMANDS && $TEST_COMMANDS"
# Load BUILDKITE Environment Variables for use in docker run
if [[ -f $BUILDKITE_ENV_FILE ]]; then
    evars=""
    while read -r var; do
        evars="$evars --env ${var%%=*}"
    done < "$BUILDKITE_ENV_FILE"
fi
if [[ $TRAVIS ]]; then
    travis_wait 60 eval docker run $ARGS $evars $DOCKER_IMAGE bash -c \"$COMMANDS\"
else
eval docker run $ARGS $evars $DOCKER_IMAGE bash -c \"$COMMANDS\"
fi