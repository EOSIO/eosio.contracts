#!/usr/bin/env bash
set -eo pipefail

[[ "$RAW_PIPELINE_CONFIG" == '' ]] && export RAW_PIPELINE_CONFIG="$1"
[[ "$RAW_PIPELINE_CONFIG" == '' ]] && export RAW_PIPELINE_CONFIG='pipeline.jsonc'
[[ "$PIPELINE_CONFIG" == '' ]] && export PIPELINE_CONFIG='pipeline.json'
# read dependency file
echo '+++ :gear: Reading Pipeline Configuration File'
if [[ -f "$RAW_PIPELINE_CONFIG" ]]; then
    echo 'Reading pipeline configuration file...'
    cat "$RAW_PIPELINE_CONFIG" | grep -Po '^[^"/]*("((?<=\\).|[^"])*"[^"/]*)*' | jq -c .\"eosio-dot-contracts\" > "$PIPELINE_CONFIG"
    EOSIO_BRANCH=$(cat "$PIPELINE_CONFIG" | jq -r '.dependencies.eosio')
    CDT_BRANCH=$(cat "$PIPELINE_CONFIG" | jq -r '.dependencies."eosio.cdt"')
    CDT_VERSION=$(cat "$PIPELINE_CONFIG" | jq -r '.dependencies."cdt-version"')
else
    echo 'ERROR: No pipeline configuration file or dependencies file found!'
    exit 1
fi
EOSIO_COMMIT=$((curl -s https://api.github.com/repos/EOSIO/eos/git/refs/tags/$EOSIO_BRANCH && curl -s https://api.github.com/repos/EOSIO/eos/git/refs/heads/$EOSIO_BRANCH) | jq '.object.sha' | grep -v 'null' | tr -d '"' | sed -n '1p') # search GitHub for commit hash by tag and branch, preferring tag if both match
test -z "$EOSIO_COMMIT" && EOSIO_COMMIT=$(echo $EOSIO_BRANCH | tr -d '"' | tr -d "''" | cut -d ' ' -f 1) # if both searches returned nothing, the version is probably specified by commit hash already
echo "Using eosio ${EOSIO_COMMIT:0:7} from \"$EOSIO_BRANCH\"..."
CDT_COMMIT=$((curl -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/tags/$CDT_BRANCH && curl -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/heads/$CDT_BRANCH) | jq '.object.sha' | grep -v 'null' | tr -d '"' | sed -n '1p') # search GitHub for commit hash by tag and branch, preferring tag if both match
test -z "$CDT_COMMIT" && CDT_COMMIT=$(echo $CDT_BRANCH | tr -d '"' | tr -d "''" | cut -d ' ' -f 1) # if both searches returned nothing, the version is probably specified by commit hash already
echo "Using cdt ${CDT_COMMIT:0:7} from \"$CDT_BRANCH\"..."

export BRANCH=$(echo $EOSIO_BRANCH | sed 's/\//\_/')
export CDT_URL="https://eos-public-oss-binaries.s3-us-west-2.amazonaws.com/${CDT_COMMIT:0:7}-eosio.cdt_${CDT_VERSION}-ubuntu-18.04_amd64.deb"