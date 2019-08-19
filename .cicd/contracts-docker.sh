#!/bin/bash
set -e # exit on failure of any "simple" command (excludes &&, ||, or | chains)
# variables
echo '+++ :evergreen_tree: Configuring Environment'
CONTRACTS_ROOT="$(pwd)"
DIGEST=''
[[ "$DOCKER_PASSWORD" == '' ]] && (echo '+++ :no_entry: ERROR: Docker Hub password not found!' && exit 1)
DOCKER_ROOT="$CONTRACTS_ROOT/docker"
DOCKER_USERNAME='b1automation'
DOCKER_FILE="$DOCKER_ROOT/dockerfile"
[[ "$RAW_PIPELINE_CONFIG" == '' ]] && export RAW_PIPELINE_CONFIG="$1"
[[ "$RAW_PIPELINE_CONFIG" == '' ]] && export RAW_PIPELINE_CONFIG='pipeline.jsonc'
[[ "$PIPELINE_CONFIG" == '' ]] && export PIPELINE_CONFIG='pipeline.json'
SANITIZED_BRANCH="$(echo $BUILDKITE_BRANCH | tr '/' '_')" # '/' ruins docker hub URLs
SANITIZED_TAG="$(echo $BUILDKITE_TAG | tr '/' '_')"
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
# get eosio
echo '+++ :arrow_down: Pulling EOSIO Docker Image'
DOCKER_IMAGE="eosio/ci-contracts-builder:base-ubuntu-18.04-$EOSIO_COMMIT"
docker pull $DOCKER_IMAGE
echo "Docker image downloaded with eosio ${EOSIO_COMMIT:0:7}."
echo ''
echo 'To see this image yourself, run:'
echo "$ docker pull eosio/ci-contracts-builder:base-ubuntu-18.04-$EOSIO_COMMIT"
# get cdt
echo '+++ :minidisc: Getting CDT Binary from Amazon S3'
CDT_PKG_NAME=$(aws s3 ls s3://eos-binaries | grep ${CDT_COMMIT:0:7} | grep 'ubuntu-18.04_amd64.deb' | tr ' ' '\n' | grep '.deb') # get Ubuntu 18.04 *.deb package from S3 bucket by commit hash
echo "Found \"$CDT_PKG_NAME\" in s3://eos-binaries. Downloading..."
test -z $CDT_PKG_NAME && echo "ERROR: CDT tag, branch, or commit \"$CDT_VERSION\" not found in s3://eos-binaries$(test $CDT_VERSION != $CDT_COMMIT && echo " using commit \"${CDT_COMMIT:0:7}\"")! Exiting..." && exit 1
aws s3 cp s3://eos-binaries/$CDT_PKG_NAME ./$CDT_PKG_NAME --quiet # download CDT
echo "Downloaded CDT at $CDT_COMMIT from \"$CDT_VERSION\""'!'
# create dockerfile
echo '+++ :pencil: Writing Auto-Generated Scripts'
echo 'Creating dockerfile...'
echo "FROM $DOCKER_IMAGE as builder" > $DOCKER_FILE
cat "$DOCKER_ROOT/external-dependencies.dockerpart" | grep '' >> $DOCKER_FILE
echo "ENV CMAKE_FRAMEWORK_PATH='/usr/local'"
echo '# put cdt into container' >> $DOCKER_FILE
echo "ADD ./$CDT_PKG_NAME /$CDT_PKG_NAME" >> $DOCKER_FILE
echo '# some version of contracts is already here for whatever reason, delete it' >> $DOCKER_FILE
echo 'RUN rm -rf /contracts' >> $DOCKER_FILE
echo '# install cdt' >> $DOCKER_FILE
echo "RUN /usr/bin/dpkg -i \"/$CDT_PKG_NAME\" && rm /$CDT_PKG_NAME" >> $DOCKER_FILE
cat "$DOCKER_ROOT/environment.dockerpart" | grep '' >> $DOCKER_FILE
echo "Created dockerfile at $DOCKER_FILE."
# put auto-generated files in artifacts for debugging (must be done before build in case build fails)
if [[ "$DEBUG" == 'true' ]]; then
    echo '+++ :arrow_up: Uploading Artifacts'
    cd "$DOCKER_ROOT"
    echo 'Uploading dockerfile...'
    buildkite-agent artifact upload dockerfile
    cd "$CONTRACTS_ROOT"
    echo 'Done uploading dockerfile.'
fi
# build Docker image
echo '+++ :docker: Building Docker Image'
docker build -t eosio/ci-contracts-builder:latest -t eosio/ci-contracts-builder:$BUILDKITE_COMMIT -t eosio/ci-contracts-builder:$SANITIZED_BRANCH $([[ "$SANITIZED_TAG" != '' ]] && echo "-t eosio/ci-contracts-builder:$SANITIZED_TAG ")-f "$DOCKER_FILE" .
# tag
echo '+++ :label: Tagging Image'
docker tag eosio/ci-contracts-builder:latest eosio/ci-contracts-builder:$BUILDKITE_COMMIT
docker tag eosio/ci-contracts-builder:latest eosio/ci-contracts-builder:$SANITIZED_BRANCH
[[ "$SANITIZED_TAG" != '' ]] && docker tag eosio/ci-contracts-builder:latest eosio/ci-contracts-builder:$SANITIZED_TAG
# push
echo '+++ :arrow_up: Pushing Image'
echo "Authenticating with Docker Hub as $DOCKER_USERNAME..."
echo "$DOCKERHUB_PASSWORD" | docker login -u "$DOCKERHUB_USERNAME" --password-stdin
echo 'Pushing...'
docker push eosio/ci-contracts-builder:$BUILDKITE_COMMIT
docker push eosio/ci-contracts-builder:$SANITIZED_BRANCH
[[ "$SANITIZED_TAG" != '' ]] && docker push eosio/ci-contracts-builder:$SANITIZED_TAG
docker push eosio/ci-contracts-builder:latest
# clean up
echo '+++ :put_litter_in_its_place: Cleaning Up'
docker rmi eosio/ci-contracts-builder:latest
docker rmi eosio/ci-contracts-builder:$BUILDKITE_COMMIT
docker rmi eosio/ci-contracts-builder:$SANITIZED_BRANCH
[[ "$SANITIZED_TAG" != '' ]] && docker rmi eosio/ci-contracts-builder:$SANITIZED_TAG
echo '+++ :white_check_mark: Done!'
echo 'See this container for yourself:'
echo "$ docker pull eosio/ci-contracts-builder:$BUILDKITE_COMMIT"
echo "$ docker run -it eosio/ci-contracts-builder:$BUILDKITE_COMMIT /bin/bash"
