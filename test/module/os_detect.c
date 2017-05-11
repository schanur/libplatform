#include "../shared_c/test.h"

#include "platform/os_detect.h"


/* Test if exactly one platform is defined.
 */
#if (defined(PLATFORM_LINUX) && defined(PLATFORM_WINDOWS))
#error More than one platform defined.
#endif
#if !(defined(PLATFORM_LINUX) || defined(PLATFORM_WINDOWS))
#error No platform defined.
#endif


int main(void) {

    return 0;
}
