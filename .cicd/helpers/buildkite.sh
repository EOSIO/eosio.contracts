# load buildkite intrinsic environment variables for use in docker run
function buildkite-intrinsics()
{
    BK_ENV=''
    if [[ -f $BUILDKITE_ENV_FILE ]]; then
        while read -r var; do
            BK_ENV="$BK_ENV --env ${var%%=*}"
        done < "$BUILDKITE_ENV_FILE"
    fi
    echo "$BK_ENV"
}