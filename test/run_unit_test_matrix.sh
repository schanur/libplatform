#!/bin/bash
set -o errexit -o nounset -o pipefail

SRC_PATH="../src"
BUILD_PATH="build"

C_INCLUDE_PATH="-I${SRC_PATH}"

declare -A COMPILER_WARNINGS_MAP

COMPILER_WARNINGS_MAP['clang']="-Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['gcc']="-Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"


# From libbivalvia repository (string module).
function fill_tail {
    local LENGTH=${1}
    local FILL_CHARACTER=${2}
    shift; shift
    local STRING="${@}"
    local FILL_CHARACTER_COUNT

    (( FILL_CHARACTER_COUNT=${LENGTH}-${#STRING} ))
    for I in $(seq 1 ${FILL_CHARACTER_COUNT}); do
        STRING="${STRING}${FILL_CHARACTER}"
    done

    echo -n "${STRING}"
}

function pp_compiler {
    local COMPILER=$1

    echo -n "[$(fill_tail 5 ' ' ${COMPILER})]"
}

function pp_module {
    local MODULE=$1

    echo -n "[$(fill_tail 25 ' ' ${MODULE})]"
}

function pp_build {
    local BUILD=$1

    echo -n "[$(fill_tail 7 ' ' ${BUILD})]"
}

function pp_execution_type {
    local EXECUTION_TYPE=$1

    echo -n "[$(fill_tail 8 ' ' ${EXECUTION_TYPE})]"
}

function llvm_c_compiler_list
{
    echo "clang"
}

function gcc_compiler_list
{
    echo "gcc"
}

function c_compiler_list
{
    llvm_c_compiler_list
    gcc_compiler_list
}

function module_list
{
    find module/ -type f
}

function build_list
{
    echo "debug release"
}

function execution_type_list
{
    # echo "native valgrind"
    echo "native"
}

if [ ! -d ${BUILD_PATH} ]; then
    mkdir -p ${BUILD_PATH}
fi

for C_COMPILER in $(c_compiler_list); do
    for BUILD in $(build_list); do
        for EXECUTION_TYPE in $(execution_type_list); do
            for MODULE_FILENAME in $(module_list); do
                MODULE_NAME=$(basename ${MODULE_FILENAME} | sed -e 's/\..*//g')
                COMPILER_WARNINGS="${COMPILER_WARNINGS_MAP[${C_COMPILER}]}"

                TEST_BINARY_NAME="${MODULE_NAME}__${C_COMPILER}__${BUILD}__${EXECUTION_TYPE}"
                TEST_BINARY_FILENAME="${BUILD_PATH}/${TEST_BINARY_NAME}"
                echo "$(pp_compiler ${C_COMPILER}) $(pp_build ${BUILD}) $(pp_execution_type ${EXECUTION_TYPE}) $(pp_module ${MODULE_NAME})"
                COMPILE_CMD="${C_COMPILER} ${COMPILER_WARNINGS} ${C_INCLUDE_PATH} ${MODULE_FILENAME} -o ${TEST_BINARY_FILENAME}"
                # echo ${COMPILE_CMD}
                ${COMPILE_CMD}
                ${TEST_BINARY_FILENAME}
            done
        done
    done
done
