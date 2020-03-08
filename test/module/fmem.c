/* #define _DEFAULT_SOURCE */

#include "../shared_c/test.h"

#include "platform/fmem.h"

#include <string.h> /* strcmp() */

static void test__fmem__open_close()
{
    int           err;
    PLTF_FMEM_HDL hdl;
    char          buf[1024];

    PLTF_FMEM_OPEN(err, hdl, buf, sizeof(buf));
    mu_assert(!err);
    PLTF_FMEM_CLOSE(err, hdl);
    mu_assert(!err);
}


static void test__fmem__write_and_flush__compare_memory()
{
    int           err;
    PLTF_FMEM_HDL hdl;
    char          buf[1024];
    char          test_write_str[] = "test123";

    memset(buf, 0, sizeof(buf));
    PLTF_FMEM_OPEN(err, hdl, buf, sizeof(buf));
    mu_assert(!err);

    PLTF_FMEM_WRITE(err, hdl, test_write_str, sizeof(test_write_str));
    mu_assert(!err);
    PLTF_FMEM_FLUSH(err,hdl);
    mu_assert(!err);
    mu_assert(!strcmp(test_write_str, buf));

    PLTF_FMEM_CLOSE(err, hdl);
    mu_assert(!err);
}


int main(void)
{
    test__fmem__open_close();
    test__fmem__write_and_flush__compare_memory();

    return 0;
}
