#!/bin/bash
set -o errexit -o nounset -o pipefail

SRC_PATH="../src"
BUILD_PATH="build"

FAST_TEST=0

C_INCLUDE_PATH="-I${SRC_PATH}"

declare -A COMPILER_WARNINGS_MAP

COMPILER_WARNINGS_MAP['clang']="-Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['gcc']="-Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"

declare -A VALGRIND_OPTIONS_MAP
VALGRIND_OPTIONS_MAP['vg_memcheck']="--tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --show-leak-kinds=all --errors-for-leak-kinds=all"
VALGRIND_OPTIONS_MAP['vg_helgrind']="--tool=helgrind --free-is-write=yes"
VALGRIND_OPTIONS_MAP['vg_drd']="--tool=drd --check-stack-var=yes --exclusive-threshold=1000 --shared-threshold=30 --join-list-vol=100 --free-is-write=yes"
VALGRIND_OPTIONS_MAP['vg_exp_sgchck']="--tool=exp-sgcheck"

VALGRIND_GLOBAL_OPTION="-q --error-exitcode=9 --trace-children=yes --num-callers=50"

# SUPPRESSION="--suppressions=test/valgrind/suppression/qt.supp"


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

    echo -n "[$(fill_tail 13 ' ' ${EXECUTION_TYPE})]"
}

function llvm_c_compiler_list
{
    echo 'clang'
}

function gcc_compiler_list
{
    echo 'gcc'
}

function c_compiler_list
{
    if [ ${FAST_TEST} -eq 1 ]; then
        echo 'clang'
    else
        llvm_c_compiler_list
        gcc_compiler_list
    fi
}

function module_list
{
    find module/ -type f
}

function build_list
{
    if [ ${FAST_TEST} -eq 1 ]; then
        echo 'debug'
    else
        echo "debug release"
    fi
}

function execution_type_list
{
    if [ ${FAST_TEST} -eq 1 ]; then
        echo 'native'
    else
        # Order is important. All Valgrind runs do not compile but assume
        # "native" had already done the job.
        echo "native vg_memcheck vg_helgrind vg_drd vg_exp_sgchck"
    fi
}

case ${#} in
    0)
        true
        ;;
    1)
        case ${1} in
            '-f')
                FAST_TEST=1
                ;;
            *)
                echo "Unknown argument: ${1}"
                exit 1
                ;;
        esac
        ;;
    *)
        echo "Too many arguments: ${*}"
        exit 1
        ;;
esac

if [ -d ${BUILD_PATH} ]; then
    echo "Delete build files"
    (cd "${BUILD_PATH}" && rm -f -- *__*__*__*)
else
    mkdir -p ${BUILD_PATH}
fi

for EXECUTION_TYPE in $(execution_type_list); do
    for C_COMPILER in $(c_compiler_list); do
        for BUILD in $(build_list); do
            for MODULE_FILENAME in $(module_list); do
                MODULE_NAME=$(basename ${MODULE_FILENAME} | sed -e 's/\..*//g')
                COMPILER_WARNINGS="${COMPILER_WARNINGS_MAP[${C_COMPILER}]}"
                TEST_BINARY_NAME="${MODULE_NAME}__${C_COMPILER}__${BUILD}__${EXECUTION_TYPE}"
                TEST_BINARY_FILENAME="${BUILD_PATH}/${TEST_BINARY_NAME}"
                echo "$(pp_execution_type ${EXECUTION_TYPE}) $(pp_compiler ${C_COMPILER}) $(pp_build ${BUILD}) $(pp_module ${MODULE_NAME})"
                COMPILE_CMD="${C_COMPILER} ${COMPILER_WARNINGS} ${C_INCLUDE_PATH} ${MODULE_FILENAME} -o ${TEST_BINARY_FILENAME}"
                if [ ${EXECUTION_TYPE} = 'native' ]; then
                    ${COMPILE_CMD}
                    ${TEST_BINARY_FILENAME}
                else
                    ${COMPILE_CMD}
                    VALGRIND_CMD="valgrind ${VALGRIND_GLOBAL_OPTION} ${VALGRIND_OPTIONS_MAP[${EXECUTION_TYPE}]} ${TEST_BINARY_FILENAME}"
                    # echo ${VALGRIND_CMD}
                    ${VALGRIND_CMD}
                fi
            done
        done
    done
done
