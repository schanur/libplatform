#! /bin/bash

set -o errexit
set -o nounset
set -o pipefail

HEADER_PATH="src/platform"

function file_included() {
    local HEADER_TO_GREP=${1}
    local HEADER_TO_SERACH=${2}
    local OCCUR_CNT

    # grep -c $(basename ${HEADER_TO_SEARCH}) < ${HEADER_TO_GREP}
    # exit 1
    OCCUR_CNT=$(grep -c "#include \"$(basename ${HEADER_TO_SEARCH})\"" < ${HEADER_TO_GREP} || true)
    case "${OCCUR_CNT}" in
        1)
            true
            ;;
        0)
            echo "${HEADER_TO_SEARCH} is not included in ${HEADER_TO_GREP}"
            ;;
        *)
            echo "Parse error for ${HEADER_TO_SEARCH}: ${OCCUR_CNT}"
            exit 1
            ;;
    esac
}

function main() {
    local ERR=0
    local HEADER
    local HEADER_TO_GREP="${HEADER_PATH}/all.h"
    if [ -f ${HEADER_TO_GREP} ]; then
        for HEADER_TO_SEARCH in ${HEADER_PATH}/*.h; do
            if [ $(basename ${HEADER_TO_SEARCH}) == "all.h" ]; then
                continue
            fi
            # echo "Check ${HEADER_TO_SEARCH}"
            file_included ${HEADER_TO_GREP} ${HEADER_TO_SEARCH}
        done
        exit ${ERR}
    fi
    exit 1
}

main
