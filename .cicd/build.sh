#!/bin/bash
set -eo pipefail
. ./.cicd/helpers/general.sh
. ./.cicd/helpers/dependency-info.sh
mkdir -p $BUILD_DIR
FULL_TAG=${FULL_TAG:-eosio/ci-contracts-builder:base-ubuntu-18.04-$EOSIO_COMMIT}
ARGS=${ARGS:-"--rm -v $(pwd):$MOUNTED_DIR"}
CDT_COMMANDS="apt-get install -y wget && wget -q $CDT_URL -O eosio.cdt.deb && dpkg -i eosio.cdt.deb && export PATH=/usr/opt/eosio.cdt/$CDT_VERSION/bin:/usr/local/eosio/bin:\\\$PATH"
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
# retry docker pull to protect against failures due to race conditions with eosio pipeline
INDEX='1'
echo "$ docker pull $FULL_TAG"
while [[ "$(docker pull $FULL_TAG 2>&1 | grep -ice "manifest for $FULL_TAG not found")" != '0' ]]; do
    echo "ERROR: Docker image \"$FULL_TAG\" not found for eosio commit ${EOSIO_COMMIT:0:7} from \"$EOSIO_VERSION\""'!'
    printf "There must be a successful build against ${EOSIO_COMMIT:0:7} \033]1339;url=https://eos-coverage.s3-us-west-2.amazonaws.com/build-$BUILDKITE_BUILD_NUMBER/code-coverage-report/index.html;content=here\a for this container to exist.\n"
    echo "Attempt $INDEX, retry in 60 seconds..."
    echo ''
    INDEX=$(( $INDEX + 1 ))
    sleep 60
done
# run
eval docker run $ARGS $evars $FULL_TAG bash -c \"$COMMANDS\"