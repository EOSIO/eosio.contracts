#!/usr/bin/env bash
set -eo pipefail
. ./.cicd/helpers/general.sh
. ./$HELPERS_DIR/execute.sh

export FULL_TAG="eosio/producer:eos-binaries-trav-poc-contract-support-1.8.0-c00bf047d29a188806fba877e5fed08b6d8fe984"
export CDT_VERSION="1.6.2"

if [[ $(uname) == Darwin ]]; then

    cd $ROOT_DIR
    ccache -s
    mkdir -p build
    cd build
    execute cmake ..
    execute make -j$JOBS
    cd ..
    
else # Linux

    . ./$HELPERS_DIR/docker.sh
    
    # Generate Base Images
    # execute ./.cicd/generate-base-images.sh
    [[ -z $CDT_VERSION ]] && echo "Please specify CDT_VERSION." && exit 1
    CDT_INSTALL="curl -LO https://github.com/EOSIO/eosio.cdt/releases/download/v$CDT_VERSION/eosio.cdt_$CDT_VERSION-1-ubuntu-18.04_amd64.deb && dpkg -i eosio.cdt_$CDT_VERSION-1-ubuntu-18.04_amd64.deb && export PATH=/usr/opt/eosio.cdt/1.6.2/bin:$PATH"
    BUILD_COMMANDS="mkdir -p /workdir/build && cd /workdir/build && cmake -DCMAKE_CXX_COMPILER='clang++' -DCMAKE_C_COMPILER='clang' -DCMAKE_FRAMEWORK_PATH='/usr/local' .. && make -j$JOBS"
    TEST_COMMANDS="cd /workdir/build/tests && ctest -j$JOBS -V --output-on-failure -T Test"

    # Docker Run Arguments
    ARGS=${ARGS:-"--rm -v $(pwd):/workdir"}
    # Docker Commands
    append-to-commands $CDT_INSTALL
    if [[ $BUILDKITE ]]; then
        [[ $ENABLE_BUILD ]] && append-to-commands $BUILD_COMMANDS
        [[ $ENABLE_TEST ]] && append-to-commands $TEST_COMMANDS
    elif [[ $TRAVIS ]]; then
        ARGS="$ARGS -v /usr/lib/ccache -v $HOME/.ccache:/opt/.ccache -e JOBS -e CCACHE_DIR=/opt/.ccache"
        TRAV_COMMANDS="ccache -s && $BUILD_COMMANDS && $TEST_COMMANDS"
        append-to-commands $TRAV_COMMANDS
    fi
    # Docker Run
    docker-run $COMMANDS

fi