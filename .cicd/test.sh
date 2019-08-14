#!/usr/bin/env bash
set -eo pipefail
. ./.cicd/helpers/general.sh

mkdir -p $BUILD_DIR

FULL_TAG=${FULL_TAG:-eosio/ci-contracts-builder:17ee214-889efb1}
ARGS=${ARGS:-"--rm -v $(pwd):$MOUNTED_DIR"}

PRE_COMMANDS="cd $MOUNTED_DIR/build"
TEST_COMMANDS="ctest -j $JOBS"

COMMANDS="$PRE_COMMANDS && $TEST_COMMANDS"

# Load BUILDKITE Environment Variables for use in docker run
if [[ -f $BUILDKITE_ENV_FILE ]]; then
    evars=""
    while read -r var; do
        evars="$evars --env ${var%%=*}"
    done < "$BUILDKITE_ENV_FILE"
fi

eval docker run $ARGS $evars $FULL_TAG bash -c \"$COMMANDS\"