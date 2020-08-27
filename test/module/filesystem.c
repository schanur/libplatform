#include "../shared_c/test.h"

#include "platform/filesystem.h"
#include <string.h>


static void test__filesystem__MKDIR__create_in_dev_shm()
{
    int pltf_err = -1;
    PLTF_MKDIR(pltf_err, "/dev/shm/libplatform");
    mu_assert(!pltf_err);
}


#ifdef _POSIX_SOURCE
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
    test__filesystem__MKDIR__create_in_dev_shm();
#ifdef _POSIX_SOURCE
    test__filesystem__PLTF_ABS_EXECUTABLE_FILENAME();
#endif

    return 0;
}
