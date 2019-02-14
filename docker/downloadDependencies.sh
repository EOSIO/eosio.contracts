#!/bin/bash
DEPENDENCIES_FILE_PATH='/Users/zachary.butler/Work/eosio.contracts/dependencies'
# get EOSIO
echo "downloadDependencies.sh - Downloading EOSIO source from GitHub..."
EOSIO_VERSION=$(cat $DEPENDENCIES_FILE_PATH | sed 's,//,#,g' | cut -d '#' -f 1 | grep -v 'eos.*cdt.*=' | grep -v 'eos.*contracts.*=' | grep '.*eos.*=' | cut -d '=' -f 2 | awk '{print $1}')
EOSIO_COMMIT=$((curl -s https://api.github.com/repos/EOSIO/eos/git/refs/tags/$EOSIO_VERSION && curl -s https://api.github.com/repos/EOSIO/eos/git/refs/heads/$EOSIO_VERSION) | jq '.object.sha' | grep -v 'null' | tr -d '"' | sed -n '1p') # search GitHub for commit hash by tag and branch, preferring tag if both match
test -z $EOSIO_COMMIT && EOSIO_COMMIT=$(echo $EOSIO_VERSION | tr -d '"' | tr -d "''" | awk '{print $1}') # if both searches returned nothing, the version is probably specified by commit hash already
git clone -n https://github.com/EOSIO/eos.git --recursive --quiet
cd eos
test "$(git cat-file -t $EOSIO_COMMIT 2>/dev/null)" != "commit" && cd .. && echo "downloadDependencies.sh - ERROR: EOSIO tag, branch, or commit \"$EOSIO_VERSION\" not found in github.com/EOSIO/eos$(test $EOSIO_VERSION != $EOSIO_COMMIT && echo " using commit \"${EOSIO_COMMIT:0:7}\"")! Exiting..." && return 1 # exit 1
git checkout $EOSIO_COMMIT --quiet
cd ..
echo "downloadDependencies.sh - Downloaded EOSIO at $EOSIO_COMMIT from \"$EOSIO_VERSION\""'!'
# get CDT
echo "downloadDependencies.sh - Downloading CDT binary from Amazon S3..."
CDT_VERSION=$(cat $DEPENDENCIES_FILE_PATH | sed 's,//,#,g' | cut -d '#' -f 1 | grep 'cdt.*=' | cut -d '=' -f 2 | awk '{print $1}')
CDT_COMMIT=$((curl -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/tags/$CDT_VERSION && curl -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/heads/$CDT_VERSION) | jq '.object.sha' | grep -v 'null' | tr -d '"' | sed -n '1p') # search GitHub for commit hash by tag and branch, preferring tag if both match
test -z $CDT_COMMIT && CDT_COMMIT=$(echo $CDT_VERSION | tr -d '"' | tr -d "''" | awk '{print $1}') # if both searches returned nothing, the version is probably specified by commit hash already
CDT_PKG_NAME=$(aws s3 ls s3://eos-binaries | grep ${CDT_COMMIT:0:7} | grep "ubuntu-18.04_amd64.deb" | tr ' ' '\n' | grep .deb) # get Ubuntu 18.04 *.deb package from S3 bucket by commit hash
test -z $CDT_PKG_NAME && echo "downloadDependencies.sh - ERROR: CDT tag, branch, or commit \"$CDT_VERSION\" not found in s3://eos-binaries$(test $CDT_VERSION != $CDT_COMMIT && echo " using commit \"${CDT_COMMIT:0:7}\"")! Exiting..." && return 1 # exit 1
aws s3 sync s3://eos-binaries . --exclude '*' --include $CDT_PKG_NAME --quiet # download CDT
echo "downloadDependencies.sh - Downloaded CDT at $CDT_COMMIT from \"$CDT_VERSION\""'!'