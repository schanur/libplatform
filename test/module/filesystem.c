#include "../shared_c/test.h"

#include "platform/os_detect.h"
#include "platform/filesystem.h"
#include <string.h>


#if (PLTF_OS == PLTF_OS_LINUX)
static const char *test__filesystem__test_directory__create_destroy = "/dev/shm/libplatform";
#elif (PLTF_OS == PLTF_OS_WINDOWS)
static const char *test__filesystem__test_directory__create_destroy = "c:/windows/temp/libplatform_test_filesystem";
#else
error No OS defined
#endif


static void test__filesystem__prepare_clean_test_working_directory()
{
    int pltf_err   = -1;
    int dir_exists = -1; /* invalid value. */

    PLTF_DIR_EXIST(pltf_err, test__filesystem__test_directory__create_destroy, dir_exists);
    mu_assert(pltf_err != -1);
    mu_assert(!pltf_err);
    mu_assert(dir_exists != -1);

    if (dir_exists) {
        /* Directory exists because the test did run earlier and it did not clean up properly. */
        /* printf("directory exists: we delete it first: %s\n", test__filesystem__test_directory__create_destroy); */
        PLTF_RMDIR(pltf_err, test__filesystem__test_directory__create_destroy);
        mu_assert(pltf_err != -1);
        mu_assert(!pltf_err);
    }
}


static void test__filesystem__MKDIR_and_RMDIR__create_in_dev_shm()
{
    int pltf_err   = -1;
    int dir_exists = -1;

    PLTF_DIR_EXIST(pltf_err, test__filesystem__test_directory__create_destroy, dir_exists);
    mu_assert(pltf_err != -1);
    mu_assert(!pltf_err);
    mu_assert(!dir_exists);

    PLTF_MKDIR(pltf_err, test__filesystem__test_directory__create_destroy);
    mu_assert(!pltf_err);

    PLTF_DIR_EXIST(pltf_err, test__filesystem__test_directory__create_destroy, dir_exists);
    mu_assert(!pltf_err);
    mu_assert(dir_exists);

    PLTF_RMDIR(pltf_err, test__filesystem__test_directory__create_destroy);
    mu_assert(!pltf_err);

    PLTF_DIR_EXIST(pltf_err, test__filesystem__test_directory__create_destroy, dir_exists);
    mu_assert(!pltf_err);
    mu_assert(!dir_exists);
}


#ifndef PLATFORM_WINDOWS
static void test__filesystem__PLTF_ABS_EXECUTABLE_FILENAME()
{
    char filename[PLTF_PATH_MAX];
    int  pltf_err = -1;
    memset(filename, 0 , PLTF_PATH_MAX);
    PLTF_ABS_EXECUTABLE_FILENAME(pltf_err, filename, PLTF_PATH_MAX);
    mu_assert(!pltf_err);
    mu_assert(strlen(filename) > 0);
}
#endif


int main(void)
{
    test__filesystem__prepare_clean_test_working_directory();
    test__filesystem__MKDIR_and_RMDIR__create_in_dev_shm();
#ifndef PLATFORM_WINDOWS
    test__filesystem__PLTF_ABS_EXECUTABLE_FILENAME();
#endif

    return 0;
}
