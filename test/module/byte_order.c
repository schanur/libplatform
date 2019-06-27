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


static void test__byte_order__()
{

}

int main(void)
{
    test__byte_order__();

    return 0;
}
