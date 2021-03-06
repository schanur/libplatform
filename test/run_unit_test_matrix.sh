#!/bin/bash
set -o errexit -o nounset -o pipefail # Fail hard and early.

SRC_PATH="../src"
BUILD_PATH="build"

FAST_TEST=0
RUN_SINGLE_TEST=0
SKIP_TO_NUMBER=0

INCLUDE_PATH="-I${SRC_PATH}"

declare -A BUILD_MAP
declare -A COMPILER_WARNINGS_MAP
declare -A STD_SUPPORT_MAP

BUILD_MAP['debug']="-g -O0"
BUILD_MAP['release']="-DNDEBUG -Os"


STD_SUPPORT_MAP['clang-3.8']="                      c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-3.9']="                      c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-4.0']="                      c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-5.0']="                      c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-6.0']="                      c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-7.0']="                      c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-8.0']="                      c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-9']="                        c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-10']="                       c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['clang-latest']="                   c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"

STD_SUPPORT_MAP['gcc-6']="                          c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['gcc-7']="                          c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['gcc-8']="                          c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['gcc-9']="                          c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['gcc-10']="                         c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"
STD_SUPPORT_MAP['gcc-latest']="                     c11 gnu11 c99 gnu99 c90 gnu90 c89 gnu89"

STD_SUPPORT_MAP['x86_64-w64-mingw32-gcc-10']="      c11       c99       c90       c89"
STD_SUPPORT_MAP['x86_64-w64-mingw32-gcc-10-win32']="c11       c99       c90       c89"

STD_SUPPORT_MAP['clang++-3.8']="                               c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-3.9']="                               c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-4.0']="                               c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-5.0']="   c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-6.0']="   c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-7.0']="   c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-8.0']="   c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-9']="     c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-10']="    c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['clang++-latest']="c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"

STD_SUPPORT_MAP['g++-6']="         c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['g++-7']="         c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['g++-8']="         c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['g++-9']="         c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['g++-10']="        c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['g++-latest']="    c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"

STD_SUPPORT_MAP['x86_64-w64-mingw32-g++-10']="      c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"
STD_SUPPORT_MAP['x86_64-w64-mingw32-g++-10-win32']="c++2a gnu++2a c++17 gnu++17 c++14 gnu++14 c++11 gnu++11 c++98 gnu++98"




COMPILER_WARNINGS_MAP['clang']="-Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang-3.8']="-Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang-3.9']="-Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang-4.0']="-Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang-5.0']="-Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang-6.0']="-Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn -Wno-reserved-id-macro"
COMPILER_WARNINGS_MAP['clang-7.0']="-Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang-8.0']="-Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang-9']="  -Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang-10']=" -Werror -Wfatal-errors -Weverything -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['gcc-7']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['gcc-8']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['gcc-9']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['gcc-10']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['x86_64-w64-mingw32-gcc-10']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['x86_64-w64-mingw32-gcc-10-win32']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"

COMPILER_WARNINGS_MAP['clang++-3.8']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang++-3.9']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang++-4.0']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang++-5.0']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang++-6.0']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang++-7.0']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang++-8.0']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang++-9']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['clang++-10']="-Werror -Wfatal-errors -Weverything -Wno-reserved-id-macro -Wno-unknown-pragmas -Wno-weak-vtables -Wno-padded -Wno-c++11-compat-deprecated-writable-strings -Wno-variadic-macros -Wno-missing-noreturn"
COMPILER_WARNINGS_MAP['g++-7']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['g++-8']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['g++-9']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['g++-10']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['x86_64-w64-mingw32-g++-10']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"
COMPILER_WARNINGS_MAP['x86_64-w64-mingw32-g++-10-win32']="-Werror -Wfatal-errors -Wall -Wno-unknown-pragmas -fdiagnostics-color=auto"

declare -A VALGRIND_OPTIONS_MAP
VALGRIND_OPTIONS_MAP['vg_memcheck']="--tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes --show-leak-kinds=all --errors-for-leak-kinds=all"
VALGRIND_OPTIONS_MAP['vg_helgrind']="--tool=helgrind --free-is-write=yes"
VALGRIND_OPTIONS_MAP['vg_drd']="--tool=drd --check-stack-var=yes --exclusive-threshold=1000 --shared-threshold=30 --join-list-vol=100 --free-is-write=yes"
# VALGRIND_OPTIONS_MAP['vg_exp_sgchck']="--tool=exp-sgcheck"

VALGRIND_GLOBAL_OPTION="-q --error-exitcode=9 --trace-children=yes --num-callers=50"

# SUPPRESSION="--suppressions=test/valgrind/suppression/qt.supp"


# From libbivalvia repository (string module).
function fill_tail
{
    local LENGTH="${1}"
    shift
    local STRING="${@}"
    # local FILL_CHARACTER_COUNT
    local PAD="                                  "

    STRING="${STRING}${PAD}"
    echo -n "${STRING:0:${LENGTH}}"
}


function is_cpp_compiler
{
    local COMPILER_NAME="${1}"
    local IS_CPP_COMPILER=0

    if [ "${COMPILER_NAME: -2}" = "++" ]; then
        IS_CPP_COMPILER=1
    fi

    echo "${IS_CPP_COMPILER}"
}


function pp_test_number
{
    local TEST_NO="${1}"

    echo -n "[$(fill_tail 6 "${TEST_NO}")]"
}


function pp_execution_type
{
    local EXECUTION_TYPE="${1}"

    echo -n "[$(fill_tail 13 "${EXECUTION_TYPE}")]"
}


function pp_language
{
    local LANGUAGE="${1}"

    echo -n "[$(fill_tail 3 "${LANGUAGE}")]"
}


function pp_compiler
{
    local COMPILER="${1}"

    echo -n "[$(fill_tail 31 "${COMPILER}")]"
}


function pp_language_standard
{
    local STD="${1}"

    echo -n "[$(fill_tail 7 "${STD}")]"
}


function pp_module
{
    local MODULE="${1}"

    echo -n "[$(fill_tail 25 "${MODULE}")]"
}


function pp_build
{
    local BUILD="${1}"

    echo -n "[$(fill_tail 7 "${BUILD}")]"
}


function llvm_c_compiler_list
{
    ls /usr/bin/clang-[0-9]*
}


function gcc_c_compiler_list
{
    ls /usr/bin/gcc-[0-9]*
}


function gcc_c_windows_cross_compiler_list
{
    ls -d /usr/bin/* | grep -E "x86_64-w64-mingw32-gcc-[0-9]+(?:|-win32)$"
}


function llvm_cpp_compiler_list
{
    ls /usr/bin/clang++-[0-9]*
}


function gcc_cpp_compiler_list
{
    ls /usr/bin/g++-[0-9]*
}


function gcc_cpp_windows_cross_compiler_list
{
    ls -d /usr/bin/* | grep -E "x86_64-w64-mingw32-g++-[0-9]+(?:|-win32)$"
}


# Return a list of available compilers based on selected language.
function compiler_list
{
    LANGUAGE="${1}"

    case "${LANGUAGE}" in
        'c')
            if [ ${FAST_TEST} -eq 1 ]; then
                # Print first installed Clang C compiler.
                llvm_c_compiler_list | cut -f 1 -d ' '
            else
                llvm_c_compiler_list
                gcc_c_compiler_list
                gcc_c_windows_cross_compiler_list
            fi
            ;;
        'cpp')
            if [ ${FAST_TEST} -eq 1 ]; then
                # Print first installed Clang C++ compiler.
                llvm_cpp_compiler_list | cut -f 1 -d ' '
            else
                llvm_cpp_compiler_list
                gcc_cpp_compiler_list
                gcc_cpp_windows_cross_compiler_list
            fi
            ;;
        *)
            echo "Unsupported language: ${LANGUAGE}" >&2
            exit 1
            ;;
    esac
}


function c_language_standard_list
{
    local COMPILER_NAME="${1}"

    # echo "$COMPILER_NAME" >&2
    # echo

    if [ ${FAST_TEST} -eq 1 ]; then
        echo 'c99'
    else
        echo "${STD_SUPPORT_MAP[${COMPILER_NAME}]}"
    fi
}


function cpp_language_standard_list
{
    local COMPILER_NAME="${1}"

    if [ ${FAST_TEST} -eq 1 ]; then
        echo 'c++11'
    else
        echo "${STD_SUPPORT_MAP[${COMPILER_NAME}]}"
    fi
}


function language_standard_list_by_compiler_name
{
    COMPILER_NAME="${1}"
    case "${COMPILER_NAME}" in
        clang-*|gcc-*|*mingw32-gcc*)
            c_language_standard_list   "${COMPILER_NAME}"
            ;;
        clang++-*|g++-*|*mingw32-g++*)
            cpp_language_standard_list "${COMPILER_NAME}"
            ;;
        *)
            echo "Unsupported compiler: ${COMPILER_NAME}" >&2
            exit 1
            ;;
    esac
}


function module_list
{
    find module/ -type f -name "*.c"
}


function build_list
{
    if [ ${FAST_TEST} -eq 1 ]; then
        echo 'release'
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
        echo "native vg_memcheck vg_helgrind vg_drd"
        # vg_exp_sgchck
    fi
}


function language_list
{
    if [ ${FAST_TEST} -eq 1 ]; then
        echo 'c'
    else
        echo "c cpp"
    fi
}


function compile_and_run_test
{
    local EXECUTION_TYPE="${1}"
    local LANGUAGE="${2}"
    local COMPILER="${3}"
    local LANG_STD="${4}"
    local BUILD="${5}"
    local MODULE_FILENAME="${6}"
    local MODULE_NAME="$(basename "${MODULE_FILENAME}" | sed -e 's/\..*//g')"
    local MINGW_BUILD=0
    if [[ "${COMPILER}" =~ mingw32 ]]; then
        MINGW_BUILD=1
    fi
    echo "$(pp_test_number ${TEST_NUMBER}) $(pp_execution_type ${EXECUTION_TYPE}) $(pp_language ${LANGUAGE}) $(pp_language_standard ${LANG_STD}) $(pp_compiler ${COMPILER}) $(pp_build ${BUILD}) $(pp_module ${MODULE_NAME})"

    local IS_CPP_COMPILER
    local COMPILER_WARNINGS="${COMPILER_WARNINGS_MAP[${COMPILER}]}"
    local TEST_BINARY_NAME="${MODULE_NAME}__${LANGUAGE}__${LANG_STD}__${COMPILER}__${BUILD}__${EXECUTION_TYPE}"
    local TEST_BINARY_FILENAME="${BUILD_PATH}/${TEST_BINARY_NAME}"
    local TEST_PREPROCESSED_SRC_FILENAME="${BUILD_PATH}/${TEST_BINARY_NAME}.preprocessed_src"
    local COMPILE_CMD
    local EXTRA_LINKER_ARGS="";

    if [ $(is_cpp_compiler "${COMPILER}") -eq 1 ]; then
        MODULE_FILENAME="${MODULE_FILENAME}pp"
    fi

    if [[ ${MINGW_BUILD} -eq 1 ]]; then
        EXTRA_LINKER_ARGS="-lws2_32"
    fi

    COMPILE_CMD="     ${COMPILER}    -D_DEFAULT_SOURCE -Werror --std=${LANG_STD} ${BUILD_MAP[${BUILD}]} ${COMPILER_WARNINGS} ${INCLUDE_PATH} ${MODULE_FILENAME} -o ${TEST_BINARY_FILENAME}           ${EXTRA_LINKER_ARGS}"
    PREPROCESSOR_CMD="${COMPILER} -E -D_DEFAULT_SOURCE -Werror --std=${LANG_STD} ${BUILD_MAP[${BUILD}]} ${COMPILER_WARNINGS} ${INCLUDE_PATH} ${MODULE_FILENAME} -o ${TEST_PREPROCESSED_SRC_FILENAME} ${EXTRA_LINKER_ARGS}"

    if [ ! -f "${TEST_BINARY_FILENAME}" ]; then
        # echo "${COMPILE_CMD}"
        # ${PREPROCESSOR_CMD}
        ${COMPILE_CMD}
    fi

    if [ "${EXECUTION_TYPE}" = 'native' ]; then
        if [[ ${MINGW_BUILD} -eq 1 ]]; then
            TEST_BINARY_FILENAME="${TEST_BINARY_FILENAME}.exe"
            wine "${TEST_BINARY_FILENAME}"
        else
            "${TEST_BINARY_FILENAME}"
        fi
    else
        if [[ ${MINGW_BUILD} -eq 1 ]]; then
            echo "Running wine binaries with valgrind is not implemented. Skipping. "
            return
        else
            VALGRIND_CMD="valgrind ${VALGRIND_GLOBAL_OPTION} ${VALGRIND_OPTIONS_MAP[${EXECUTION_TYPE}]} ${TEST_BINARY_FILENAME}"
        # echo ${VALGRIND_CMD}
            ${VALGRIND_CMD}
        fi
    fi
}


case ${#} in
    0)
        true
        ;;
    1)
        case "${1}" in
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

if [ -d "${BUILD_PATH}" ]; then
    echo "Delete build files"
    (cd "${BUILD_PATH}" && rm -f -- *__*__*__*)
else
    mkdir -p "${BUILD_PATH}"
fi

TEST_NUMBER=0
FORWARD_TO_NUMBER=0
SKIP_FROM_NUMBER=10000000000

# FORWARD_TO_NUMBER=513
# SKIP_FROM_NUMBER=514

for                     EXECUTION_TYPE  in $(execution_type_list); do
    for                 LANGUAGE        in $(language_list); do
        for             ABS_COMPILER    in $(compiler_list "${LANGUAGE}"); do
            COMPILER="$(basename ${ABS_COMPILER})"
            for         LANG_STD        in $(language_standard_list_by_compiler_name "${COMPILER}"); do
                for     BUILD           in $(build_list); do
                    for MODULE_FILENAME in $(module_list); do



                    (( TEST_NUMBER += 1 ))
                    if [ ${FORWARD_TO_NUMBER} -gt ${TEST_NUMBER} ]; then
                        continue
                    fi
                    if [ ${SKIP_FROM_NUMBER}  -le ${TEST_NUMBER} ]; then
                        continue
                    fi

                    LANG_MODULE_FILENAME="${MODULE_FILENAME}"
                    if [ "${LANGUAGE}" = "cpp" ]; then
                        LANG_MODULE_FILENAME="${MODULE_FILENAME}pp"
                    fi
                    compile_and_run_test "${EXECUTION_TYPE}" "${LANGUAGE}" "${COMPILER}" "${LANG_STD}" "${BUILD}" "${LANG_MODULE_FILENAME}"

                    done
                done
            done
        done
    done
done

echo ${TEST_NUMBER}
