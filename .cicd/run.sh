#!/usr/bin/env bash
set -eo pipefail
. ./.cicd/helpers/general.sh
. ./$HELPERS_DIR/execute.sh

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

    BUILD_COMMANDS="mkdir -p /workdir/build && cd /workdir/build && cmake .. && make -j$JOBS"
    TEST_COMMANDS="cd /workdir/build && ctest -j$JOBS -V --output-on-failure -T Test"

    # Docker Run Arguments
    ARGS=${ARGS:-"--rm -v $(pwd):/workdir"}
    # Docker Commands
    if [[ $BUILDKITE ]]; then
        [[ $ENABLE_BUILD ]] && append-to-commands $BUILD_COMMANDS
        [[ $ENABLE_TEST ]] && append-to-commands $TEST_COMMANDS
    elif [[ $TRAVIS ]]; then
        ARGS="$ARGS -v /usr/lib/ccache -v $HOME/.ccache:/opt/.ccache -e JOBS -e CCACHE_DIR=/opt/.ccache"
        COMMANDS="ccache -s && $BUILD_COMMANDS && $TEST_COMMANDS"
    fi

    # Docker Run
    docker-run $COMMANDS

fi