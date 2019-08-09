#!/usr/bin/env bash
set -eo pipefail
. ./.cicd/helpers/general.sh
. ./$HELPERS_DIR/execute.sh

# Replace the FULL_TAG to build contracts off a different EOS version.
[[ "$RAW_PIPELINE_CONFIG" == '' ]] && export RAW_PIPELINE_CONFIG="$1"
[[ "$RAW_PIPELINE_CONFIG" == '' ]] && export RAW_PIPELINE_CONFIG='pipeline.jsonc'
[[ "$PIPELINE_CONFIG" == '' ]] && export PIPELINE_CONFIG='pipeline.json'
# read dependency file
echo '+++ :gear: Reading Pipeline Configuration File'
if [[ -f "$RAW_PIPELINE_CONFIG" ]]; then
    echo 'Reading pipeline configuration file...'
    cat "$RAW_PIPELINE_CONFIG" | grep -Po '^[^"/]*("((?<=\\).|[^"])*"[^"/]*)*' | jq -c .\"eosio-dot-contracts\" > "$PIPELINE_CONFIG"
    EOSIO_VERSION=$(cat "$PIPELINE_CONFIG" | jq -r '.dependencies.eosio')
    CDT_VERSION=$(cat "$PIPELINE_CONFIG" | jq -r '.dependencies."eosio.cdt"')
else
    echo 'ERROR: No pipeline configuration file or dependencies file found!'
    echo "PIPELINE_CONFIG = \"$PIPELINE_CONFIG\""
    echo "RAW_PIPELINE_CONFIG = \"$RAW_PIPELINE_CONFIG\""
    echo '$ pwd'
    pwd
    echo '$ ls'
    ls
    exit 1
fi
EOSIO_COMMIT=$((curl -s https://api.github.com/repos/EOSIO/eos/git/refs/tags/$EOSIO_VERSION && curl -s https://api.github.com/repos/EOSIO/eos/git/refs/heads/$EOSIO_VERSION) | jq '.object.sha' | grep -v 'null' | tr -d '"' | sed -n '1p') # search GitHub for commit hash by tag and branch, preferring tag if both match
test -z "$EOSIO_COMMIT" && EOSIO_COMMIT=$(echo $EOSIO_VERSION | tr -d '"' | tr -d "''" | cut -d ' ' -f 1) # if both searches returned nothing, the version is probably specified by commit hash already
echo "Using eosio ${EOSIO_COMMIT:0:7} from \"$EOSIO_VERSION\"..."
CDT_COMMIT=$((curl -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/tags/$CDT_VERSION && curl -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/heads/$CDT_VERSION) | jq '.object.sha' | grep -v 'null' | tr -d '"' | sed -n '1p') # search GitHub for commit hash by tag and branch, preferring tag if both match
test -z "$CDT_COMMIT" && CDT_COMMIT=$(echo $CDT_VERSION | tr -d '"' | tr -d "''" | cut -d ' ' -f 1) # if both searches returned nothing, the version is probably specified by commit hash already
echo "Using cdt ${CDT_COMMIT:0:7} from \"$CDT_VERSION\"..."

export FULL_TAG="eosio/ci-contracts-builder:${EOSIO_COMMIT:0:7}-${CDT_COMMIT:0:7}"
. ./$HELPERS_DIR/docker.sh

BUILD_COMMANDS="mkdir -p /workdir/build && cd /workdir/build && cmake -DCMAKE_CXX_COMPILER='clang++' -DCMAKE_C_COMPILER='clang' -DCMAKE_FRAMEWORK_PATH='/usr/local' .. && make -j $JOBS"
TEST_COMMANDS="cd /workdir/build/tests && ctest -j $JOBS -V --output-on-failure -T Test"

# Docker Run Arguments
ARGS=${ARGS:-"--rm -v $(pwd):/workdir"}
# Docker Commands
if [[ $BUILDKITE ]]; then
    [[ $ENABLE_BUILD ]] && append-to-commands $BUILD_COMMANDS
    [[ $ENABLE_TEST ]] && append-to-commands $TEST_COMMANDS
elif [[ $TRAVIS ]]; then
    ARGS="$ARGS -e JOBS"
    COMMANDS="ccache -s && $BUILD_COMMANDS && $TEST_COMMANDS"
fi

# Docker Run
docker-run $COMMANDS

# export FULL_TAG="eosio/ci-contracts-builder:base-ubuntu-18.04-latest"
# export FULL_TAG="eosio/producer:eos-binaries-trav-poc-contract-tests-1.8.0-e13ec7f756e78d9baf994c5d3a7bd643653d834b"
# export CDT_VERSION="1.6.2"
# [[ -z $CDT_VERSION ]] && echo "Please specify CDT_VERSION." && exit 1
# CDT_COMMANDS="curl -LO https://github.com/EOSIO/eosio.cdt/releases/download/v$CDT_VERSION/eosio.cdt_$CDT_VERSION-1-ubuntu-18.04_amd64.deb && dpkg -i eosio.cdt_$CDT_VERSION-1-ubuntu-18.04_amd64.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:$PATH"
    # append-to-commands $CDT_COMMANDS