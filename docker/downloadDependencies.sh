#!/bin/bash
CONTRACTS_PATH='/eosio.contracts' # location in Docker container, not your local machine
CONTRACTS_PATH="${CONTRACTS_PATH/#\~/$HOME}" # perform parameter expansion for paths including '~'
# get EOSIO
echo "downloadDependencies.sh - Cloning EOSIO source from GitHub..."
EOSIO_VERSION=$(cat $CONTRACTS_PATH/dependencies | sed 's,//,#,g' | cut -d '#' -f 1 | grep -v 'eos.*cdt.*=' | grep -v 'eos.*contracts.*=' | grep '.*eos.*=' | cut -d '=' -f 2 | awk '{print $1}')
EOSIO_COMMIT=$((curl -s https://api.github.com/repos/EOSIO/eos/git/refs/tags/$EOSIO_VERSION && curl -s https://api.github.com/repos/EOSIO/eos/git/refs/heads/$EOSIO_VERSION) | jq '.object.sha' | grep -v 'null' | tr -d '"' | sed -n '1p') # search GitHub for commit hash by tag and branch, preferring tag if both match
test -z $EOSIO_COMMIT && EOSIO_COMMIT=$(echo $EOSIO_VERSION | tr -d '"' | tr -d "''" | awk '{print $1}') # if both searches returned nothing, the version is probably specified by commit hash already
git clone -n https://github.com/EOSIO/eos.git --quiet
echo "downloadDependencies.sh - Cloned EOSIO. Checking out ${EOSIO_COMMIT:0:7}..."
cd eos
test "$(git cat-file -t $EOSIO_COMMIT 2>/dev/null)" != "commit" && cd .. && echo "downloadDependencies.sh - ERROR: EOSIO tag, branch, or commit \"$EOSIO_VERSION\" not found in github.com/EOSIO/eos$(test $EOSIO_VERSION != $EOSIO_COMMIT && echo " using commit \"${EOSIO_COMMIT:0:7}\"")! Exiting..." && exit 1
git checkout $EOSIO_COMMIT --quiet
git submodule update --recursive --init --quiet
echo "downloadDependencies.sh - Checked out EOSIO at $EOSIO_COMMIT from \"$EOSIO_VERSION\""'!'
echo "$CONTRACTS_BRANCH:$EOSIO_COMMIT" > /etc/eosio-version # this is necessary for our eos CMake VersionMacros which construct the string returned from "$ nodeos --version"; CONTRACTS_BRANCH is a build-arg passed from pipeline.yml into the Docker container
echo "downloadDependencies.sh - Wrote \"/etc/eosio-version\"."
cd ..
# get CDT
echo "downloadDependencies.sh - Getting CDT binary from Amazon S3..."
CDT_VERSION=$(cat $CONTRACTS_PATH/dependencies | sed 's,//,#,g' | cut -d '#' -f 1 | grep 'cdt.*=' | cut -d '=' -f 2 | awk '{print $1}')
CDT_COMMIT=$((curl -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/tags/$CDT_VERSION && curl -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/heads/$CDT_VERSION) | jq '.object.sha' | grep -v 'null' | tr -d '"' | sed -n '1p') # search GitHub for commit hash by tag and branch, preferring tag if both match
test -z $CDT_COMMIT && CDT_COMMIT=$(echo $CDT_VERSION | tr -d '"' | tr -d "''" | awk '{print $1}') # if both searches returned nothing, the version is probably specified by commit hash already
CDT_PKG_NAME=$(aws s3 ls s3://eos-binaries | grep ${CDT_COMMIT:0:7} | grep "ubuntu-18.04_amd64.deb" | tr ' ' '\n' | grep '.deb') # get Ubuntu 18.04 *.deb package from S3 bucket by commit hash
echo "downloadDependencies.sh - Found \"$CDT_PKG_NAME\" in s3://eos-binaries. Downloading..."
test -z $CDT_PKG_NAME && echo "downloadDependencies.sh - ERROR: CDT tag, branch, or commit \"$CDT_VERSION\" not found in s3://eos-binaries$(test $CDT_VERSION != $CDT_COMMIT && echo " using commit \"${CDT_COMMIT:0:7}\"")! Exiting..." && exit 1
aws s3 cp s3://eos-binaries/$CDT_PKG_NAME ./$CDT_PKG_NAME --quiet # download CDT
echo "downloadDependencies.sh - Downloaded CDT at $CDT_COMMIT from \"$CDT_VERSION\""'!'