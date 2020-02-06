#!/bin/bash
set -eo pipefail
. ./.cicd/helpers/buildkite.sh
. ./.cicd/helpers/general.sh
mkdir -p $BUILD_DIR
if [[ "$BUILDKITE" == 'true' ]]; then
    CDT_URL="$(buildkite-agent meta-data get cdt-url)"
    CDT_VERSION="$(buildkite-agent meta-data get cdt-version)"
    DOCKER_IMAGE="$(buildkite-agent meta-data get docker-image)"
else # Actions
    . ./.cicd/helpers/dependency-info.sh
    DOCKER_IMAGE=${DOCKER_IMAGE:-eosio/ci-contracts-builder:base-ubuntu-18.04-$SANITIZED_EOSIO_VERSION}
fi
ARGS=${ARGS:-"--rm -v $(pwd):$MOUNTED_DIR"}
CDT_COMMANDS="dpkg -i $MOUNTED_DIR/eosio.cdt.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:\\\$PATH"
PRE_COMMANDS="$CDT_COMMANDS && cd $MOUNTED_DIR/build/tests"
TEST_COMMANDS="ctest -j $JOBS --output-on-failure -T Test"
COMMANDS="$PRE_COMMANDS && $TEST_COMMANDS"
curl -sSf $CDT_URL --output eosio.cdt.deb
set +e
echo "docker run $ARGS $(buildkite-intrinsics) $DOCKER_IMAGE bash -c \"$COMMANDS\""
eval docker run $ARGS $(buildkite-intrinsics) $DOCKER_IMAGE bash -c \"$COMMANDS\"
EXIT_STATUS=$?
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
