#include "../shared_c/test.h"

#include "platform/byte_order.h"


#ifndef PLATFORM_BYTE_ORDER
  #error PLATFORM_BYTE_ORDER not defined
#endif

#ifndef NTOH_16
  #error NTOH_16 not defined
#endif

#ifndef NTOH_32
  #error NTOH_32 not defined
#endif

#ifndef NTOH_64
  #error NTOH_64 not defined
#endif

#ifndef HTON_16
  #error HTON_16 not defined
#endif

#ifndef HTON_32
  #error HTON_32 not defined
#endif

#ifndef HTON_64
  #error HTON_64 not defined
#endif


static void test__byte_order__ntoh()
{
    mu_assert(NTOH_16(0x3412)             == 0x1234);
    mu_assert(NTOH_32(0x78563412)         == 0x12345678);
    mu_assert(NTOH_64(0xf0debc9a78563412) == 0x123456789abcdef0);
}


static void test__byte_order__hton()
{
    mu_assert(HTON_16(0x1234)             == 0x3412);
    mu_assert(HTON_32(0x12345678)         == 0x78563412);
    mu_assert(HTON_64(0x123456789abcdef0) == 0xf0debc9a78563412);
}


int main(void)
{
    test__byte_order__ntoh();
    test__byte_order__hton();

    return 0;
}
