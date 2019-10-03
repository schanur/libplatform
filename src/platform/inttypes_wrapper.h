#ifndef PLATFORM_INTTYPES_WRAPPER_H
#define PLATFORM_INTTYPES_WRAPPER_H

#include "os_detect.h"
#include "compiler.h"

#ifdef PLATFORM_LINUX
  #include <stdint.h>
  #include <inttypes.h>
  #include <limits.h>
  #include <unistd.h> /* size_t */

  #define PRIsize_t "zu"

#else
  #ifdef PLATFORM_WINDOWS
    #if 1 == 1
    //#ifdef NO_C_STD_COMPLIANT_STDINT_HEADER
      /* The location of the stdint.h file has to be added to
       * "Additional include path" variable in visual studio.
       */
      #include "stdint.h"

      #define SIZE_T size_t

      /* #ifdef UINT_MIN */
      /*   #error UINT_MIN already defined. */
      /* #endif */
      /* #ifdef UINT_MAX */
      /*   #error UINT_MAX already defined. */
      /* #endif */
      /* #ifdef INT_MIN */
      /*   #error INT_MIN already defined. */
      /* #endif */
      /* #ifdef INT_MAX */
      /*   #error INT_MAX already defined. */
      /* #endif */

      /* #define UINT_MIN  0 */
      #ifdef _WIN64
        /* #define UINT_MAX  18446744073709551615 */
        /* #define INT_MIN  -9223372036854775808 */
        /* #define INT_MAX   9223372036854775807 */
      #else
        /* #define UINT_MAX  4294967295 */
        /* #define INT_MIN  -2147483648 */
        /* #define INT_MAX   2147483647 */
      #endif

      #ifdef _WIN64
        #define PRIsize_t PRIu64
      #else
        #define PRIsize_t PRIu32
      #endif

    #else
      /* Use default version. */
      #include <stdint.h>
    #endif
  #else
    #error Integer type wrapper is not implemented for detected target platform.
  #endif
#endif

#endif /* PLATFORM_INTTYPES_WRAPPER_H */
