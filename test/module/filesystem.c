#include "../shared_c/test.h"

#include "platform/filesystem.h"


static void test__filesystem__MKDIR__create_in_dev_shm()
{
    int err = -1;
    PLTF_MKDIR(err, "/dev/shm/libplatform");
    mu_assert(!err);
}

int main(void)
{
    test__filesystem__MKDIR__create_in_dev_shm();
}
