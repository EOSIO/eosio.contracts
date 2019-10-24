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
CDT_COMMANDS="apt-get install -y wget && wget -q $CDT_URL -O eosio.cdt.deb && dpkg -i eosio.cdt.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:/usr/local/eosio/bin:\\\$PATH"
PRE_COMMANDS="$CDT_COMMANDS && cd $MOUNTED_DIR/build/tests"
TEST_COMMANDS="ctest -j $JOBS --output-on-failure -T Test"
COMMANDS="$PRE_COMMANDS && $TEST_COMMANDS"
if [[ $TRAVIS ]]; then
    travis_wait 60 eval docker run $ARGS $(buildkite-intrinsics) $DOCKER_IMAGE bash -c \"$COMMANDS\"
    EXIT_STATUS=$?
else
    set +e
    eval docker run $ARGS $(buildkite-intrinsics) $DOCKER_IMAGE bash -c \"$COMMANDS\"
    EXIT_STATUS=$?
fi
# buildkite
if [[ "$BUILDKITE" == 'true' ]]; then
    cd build
    # upload artifacts
    echo '+++ :arrow_up: Uploading Artifacts'
    echo 'Exporting xUnit XML'
    mv -f ./tests/Testing/$(ls ./tests/Testing/ | grep '2' | tail -n 1)/Test.xml test-results.xml
    echo 'Uploading artifacts'
    buildkite-agent artifact upload test-results.xml
    echo 'Done uploading artifacts.'
fi
# re-throw
if [[ "$EXIT_STATUS" != 0 ]]; then
    echo "Failing due to non-zero exit status from ctest: $EXIT_STATUS"
    exit $EXIT_STATUS
fi