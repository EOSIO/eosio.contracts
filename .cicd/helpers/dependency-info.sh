#!/usr/bin/env bash
set -eo pipefail
[[ "$RAW_PIPELINE_CONFIG" == '' ]] && export RAW_PIPELINE_CONFIG="$1"
[[ "$RAW_PIPELINE_CONFIG" == '' ]] && export RAW_PIPELINE_CONFIG='pipeline.jsonc'
[[ "$PIPELINE_CONFIG" == '' ]] && export PIPELINE_CONFIG='pipeline.json'
# read dependency file
if [[ -f "$RAW_PIPELINE_CONFIG" ]]; then
    echo 'Reading pipeline configuration file...'
    cat "$RAW_PIPELINE_CONFIG" | grep -Po '^[^"/]*("((?<=\\).|[^"])*"[^"/]*)*' | jq -c .\"eosio-dot-contracts\" > "$PIPELINE_CONFIG"
    CDT_VERSION=$(cat "$PIPELINE_CONFIG" | jq -r '.dependencies."eosio.cdt"')
    EOSIO_VERSION=$(cat "$PIPELINE_CONFIG" | jq -r '.dependencies.eosio')
else
    echo 'ERROR: No pipeline configuration file or dependencies file found!'
    exit 1
fi
if [[ $TRAVIS ]]; then
    AUTH="-H \"Authorization: token $key\""
fi

# search GitHub for commit hash by tag and branch, preferring tag if both match
CDT_COMMIT=$((curl $AUTH -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/tags/$CDT_VERSION && curl $AUTH -s https://api.github.com/repos/EOSIO/eosio.cdt/git/refs/heads/$CDT_VERSION) | jq '.object.sha' | sed "s/null//g" | sed "/^$/d" | tr -d '"' | sed -n '1p')

EOSIO_COMMIT=$((curl $AUTH -s https://api.github.com/repos/EOSIO/eos/git/refs/tags/$EOSIO_VERSION && curl $AUTH -s https://api.github.com/repos/EOSIO/eos/git/refs/heads/$EOSIO_VERSION) | jq '.object.sha' | sed "s/null//g" | sed "/^$/d" | tr -d '"' | sed -n '1p')

test -z "$CDT_COMMIT" && CDT_COMMIT=$(echo $CDT_VERSION | tr -d '"' | tr -d "''" | cut -d ' ' -f 1) # if both searches returned nothing, the version is probably specified by commit hash already
echo "Using cdt ${CDT_COMMIT:0:7} from \"$CDT_VERSION\"..."
test -z "$EOSIO_COMMIT" && EOSIO_COMMIT=$(echo $EOSIO_VERSION | tr -d '"' | tr -d "''" | cut -d ' ' -f 1) # if both searches returned nothing, the version is probably specified by commit hash already
echo "Using eosio ${EOSIO_COMMIT:0:7} from \"$EOSIO_VERSION\"..."

export CDT_URL="https://eos-public-oss-binaries.s3-us-west-2.amazonaws.com/${CDT_COMMIT:0:7}-eosio.cdt-ubuntu-18.04_amd64.deb"