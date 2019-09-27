#!/bin/bash
# This change will test PR builds on Buildkite.
set -eo pipefail
. ./.cicd/helpers/buildkite.sh
. ./.cicd/helpers/general.sh
. ./.cicd/helpers/dependency-info.sh
mkdir -p $BUILD_DIR
DOCKER_IMAGE=${DOCKER_IMAGE:-eosio/ci-contracts-builder:base-ubuntu-18.04-$EOSIO_COMMIT}
if [[ "$BUILDKITE" == 'true' ]]; then
    buildkite-agent meta-data set cdt-url "$CDT_URL"
    buildkite-agent meta-data set cdt-version "$CDT_VERSION"
    buildkite-agent meta-data set docker-image "$DOCKER_IMAGE"
else
    export CDT_URL
    export CDT_VERSION
    export DOCKER_IMAGE
fi
ARGS=${ARGS:-"--rm -v $(pwd):$MOUNTED_DIR"}
CDT_COMMANDS="apt-get install -y wget && wget -q $CDT_URL -O eosio.cdt.deb && dpkg -i eosio.cdt.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:\\\$PATH"
PRE_COMMANDS="$CDT_COMMANDS && cd $MOUNTED_DIR/build"
BUILD_COMMANDS="cmake -DBUILD_TESTS=true .. && make -j $JOBS"
COMMANDS="$PRE_COMMANDS && $BUILD_COMMANDS"
# retry docker pull to protect against failures due to race conditions with eosio pipeline
INDEX='1'
echo "$ docker pull $DOCKER_IMAGE"
while [[ "$(docker pull $DOCKER_IMAGE 2>&1 | grep -ice "manifest for $DOCKER_IMAGE not found")" != '0' ]]; do
    echo "ERROR: Docker image \"$DOCKER_IMAGE\" not found for eosio commit ${EOSIO_COMMIT:0:7} from \"$EOSIO_VERSION\""'!'
    printf "There must be a successful build against ${EOSIO_COMMIT:0:7} \033]1339;url=https://buildkite.com/EOSIO/eosio/builds?commit=$EOSIO_COMMIT;content=here\a for this container to exist.\n"
    echo "Attempt $INDEX, retry in 60 seconds..."
    echo ''
    INDEX=$(( $INDEX + 1 ))
    sleep 60
done
# run
eval docker run $ARGS $(buildkite-intrinsics) $DOCKER_IMAGE bash -c \"$COMMANDS\"