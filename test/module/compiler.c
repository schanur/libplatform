#include "../shared_c/test.h"

/* #include <stdio.h> */
/* #include <assert.h> */

#include "platform/compiler.h"

#include "platform/inttypes_wrapper.h"
#include "platform/lang.h"


static void test__compiler__align()
{
    COMPILER_ALIGN(2,    uint32_t aligned_2);
    COMPILER_ALIGN(4,    uint32_t aligned_4);
    COMPILER_ALIGN(8,    uint32_t aligned_8);
    COMPILER_ALIGN(16,   uint32_t aligned_16);
    COMPILER_ALIGN(32,   uint32_t aligned_32);
    COMPILER_ALIGN(64,   uint32_t aligned_64);
    COMPILER_ALIGN(128,  uint32_t aligned_128);
    COMPILER_ALIGN(256,  uint32_t aligned_256);
    COMPILER_ALIGN(512,  uint32_t aligned_512);
    COMPILER_ALIGN(1024, uint32_t aligned_1024);
    COMPILER_ALIGN(2048, uint32_t aligned_2048);
    COMPILER_ALIGN(4096, uint32_t aligned_4096);
    COMPILER_ALIGN(8192, uint32_t aligned_8192);

    aligned_2    = 2;
    aligned_4    = 4;
    aligned_8    = 8;
    aligned_16   = 16;
    aligned_32   = 32;
    aligned_64   = 64;
    aligned_128  = 128;
    aligned_256  = 256;
    aligned_512  = 512;
    aligned_1024 = 1024;
    aligned_2048 = 2048;
    aligned_4096 = 4096;
    aligned_8192 = 8192;

    /* printf("%p, %u\n", (void *) &aligned_2, aligned_2); */
    /* printf("%p, %u\n", (void *) &aligned_4, aligned_4); */
    /* printf("%p, %u\n", (void *) &aligned_8, aligned_8); */
    /* printf("%p, %u\n", (void *) &aligned_16, aligned_16); */
    /* printf("%p, %u\n", (void *) &aligned_32, aligned_32); */
    /* printf("%p, %u\n", (void *) &aligned_64, aligned_64); */
    /* printf("%p, %u\n", (void *) &aligned_128, aligned_128); */
    /* printf("%p, %u\n", (void *) &aligned_256, aligned_256); */
    /* printf("%p, %u\n", (void *) &aligned_512, aligned_512); */
    /* printf("%p, %u\n", (void *) &aligned_1024, aligned_1024); */
    /* printf("%p, %u\n", (void *) &aligned_2048, aligned_2048); */
    /* printf("%p, %u\n", (void *) &aligned_4096, aligned_4096); */
    /* printf("%p, %u\n", (void *) &aligned_8192, aligned_8192); */

    mu_assert(!(aligned_2 & 1));
    mu_assert(!(aligned_4 & 3));
    mu_assert(!(aligned_8 & 7));
    mu_assert(!(aligned_16 & 15));
    mu_assert(!(aligned_32 & 31));
    mu_assert(!(aligned_64 & 63));
    mu_assert(!(aligned_128 & 127));
    mu_assert(!(aligned_256 & 255));
    mu_assert(!(aligned_512 & 511));
    mu_assert(!(aligned_1024 & 1023));
    mu_assert(!(aligned_2048 & 2047));
    mu_assert(!(aligned_4096 & 4095));
    mu_assert(!(aligned_8192 & 8191));
}


/* gets never called. But compiled should not warn about that the
 * function will never exit. noreturn function attribute is also
 * tested.
 */
COMPILER_DISABLE_WARNING_UNUSED_FUNCTION
COMPILER_NORETURN(test_compiler__disable_warning__no_return(void));

void test_compiler__disable_warning__no_return(void)
{
    while (1);
}
COMPILER_ENABLE_WARNING_UNUSED_FUNCTION


PLTF_COMPILER_PACKED(
    struct test__compiler__packed__inner_struct {
        char test1;
        int  test2;
    }
    );

struct test__compiler__packed__outer_struct {
    struct test__compiler__packed__inner_struct inner1;
    struct test__compiler__packed__inner_struct inner2;
    struct test__compiler__packed__inner_struct inner3;
    struct test__compiler__packed__inner_struct inner4;
};


static void test__compiler__packed()
{
    mu_assert(sizeof(struct test__compiler__packed__outer_struct) == 20);
}


static void test__compiler__disable_warning__double_promotion()
{
    COMPILER_DISABLE_WARNING_DOUBLE_PROMOTION
    float  a = 1.1f;
    double b = 1.1;
    double c = a * b;
    (void) c;
    COMPILER_ENABLE_WARNING_DOUBLE_PROMOTION
}


static void test__compiler__disable_warning__cast_qualifier()
{
    /* COMPILER_DISABLE_WARNING_CAST_QUALIFIER */
    /* char        buffer[1]; */
    /* const char* ptr = buffer; */
    /* char*       casted_value = COMPILER_REINTERPRET_CAST(char *, ptr); */
    /* (void) casted_value; */
    /* COMPILER_ENABLE_WARNING_CAST_QUALIFIER */
}


static void test__compiler__disable_warning__unused_local_typedef()
{
    COMPILER_DISABLE_WARNING_UNUSED_LOCAL_TYPEDEF
    typedef char unused_typedef;
    COMPILER_ENABLE_WARNING_UNUSED_LOCAL_TYPEDEF
}


static void test__compiler__reinterpret_cast()
{
    int   a = 1;
    float b;

    b = COMPILER_STATIC_CAST(float, a);
    (void) b;
}


static void test__compiler__static_cast()
{
    int   *a = NULL_PTR;
    float *b;

    b = COMPILER_REINTERPRET_CAST(float *, a);
    (void) b;
}


int main(void)
{
    test__compiler__align();
    test__compiler__packed();

    test__compiler__disable_warning__double_promotion();
    test__compiler__disable_warning__cast_qualifier();
    test__compiler__disable_warning__unused_local_typedef();

    test__compiler__reinterpret_cast();
    test__compiler__static_cast();

    return mu_test_status;
}
