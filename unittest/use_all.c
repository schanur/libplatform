#include "platform_all.h"

#include "stdio.h"
#include <assert.h>

/* Test if exactly one platform is defined.
 */
#if (defined(PLATFORM_LINUX) && defined(PLATFORM_WINDOWS))
#error More than one platform defined.
#endif
#if !(defined(PLATFORM_LINUX) || defined(PLATFORM_WINDOWS))
#error No platfoem defiend.
#endif 

void test_align()
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
    
    assert(!(aligned_2 & 1));
    printf("%u\n", aligned_2);
    assert(!(aligned_4 & 3));
    printf("%u\n", aligned_4);
    assert(!(aligned_8 & 7));
    printf("%u\n", aligned_8);
    assert(!(aligned_16 & 15));
    printf("%u\n", aligned_16);
    assert(!(aligned_32 & 31));
    printf("%u\n", aligned_32);
    assert(!(aligned_64 & 63));
    printf("%u\n", aligned_64);
    assert(!(aligned_128 & 127));
    printf("%u\n", aligned_128);
    assert(!(aligned_256 & 255));
    printf("%u\n", aligned_256);
    assert(!(aligned_512 & 511));
    printf("%u\n", aligned_512);
    assert(!(aligned_1024 & 1023));
    printf("%u\n", aligned_1024);
    assert(!(aligned_2048 & 2047));
    printf("%u\n", aligned_2048);
    assert(!(aligned_4096 & 4095));
    printf("%u\n", aligned_4096);
    assert(!(aligned_8192 & 8191));
    printf("%u\n", aligned_8192);
}

thread_ret_t THREAD_CALL test_thread_func(void *data)
{
             int err       = 0;
    unsigned int thread_id = (unsigned int) data;
    
    printf("thread: end: ret: %d", err);
    return ((thread_ret_t) err);
}

int test_thread() {

}

int test_socket_client()
{

}

int test_socket_server()
{

}

int test_socket()
{

}

int main(void)
{
	test_align();
	test_thread();
	test_socket();
	return (0);
}
