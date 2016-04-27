#ifndef PLATFORM_TYPE_SIZE_H
#define PLATFORM_TYPE_SIZE_H

#include "inttypes_wrapper.h"
#include "os_detect.h"
//#include "inttypes_wrapper.h"

#include <limits.h>

#ifdef PLATFORM_LINUX
  #if UINT_MAX == UINTMAX_C(4294967295)
    #define INT_SIZE UINT8_C(4)
  #else
    #if UINT_MAX == UINTMAX_C(18446744073709551615)
      #define INT_SIZE UINT8_C(8)
    #else
      #error Unknown integer width.
    #endif
  #endif

  #if UINTPTR_MAX == UINTMAX_C(4294967295)
    #define SIZE_T_SIZE UINT8_C(4)
  #else
    #if UINTPTR_MAX == UINTMAX_C(18446744073709551615)
      #define SIZE_T_SIZE UINT8_C(8)
    #else
      #error Unknown integer width.
    #endif
  #endif
#else
  #ifdef PLATFORM_WINDOWS
    #ifndef NO_C_STD_COMPLIANT_STDINT_HEADER
      //#error NO_C_STD_COMPLIANT_STDINT_HEADER not set.
    #endif

    #if UINT_MAX == 0xffffffffUL
      #define INT_SIZE 4
    #else
      #if UINT_MAX == 0xffffffffffffffffULL
        #define INT_SIZE 8
      #else
        #error Unknown integer width.
      #endif
    #endif

    #if UINTPTR_MAX == 0xffffffffULL
      #define SIZE_T_SIZE 4
    #else
      #if UINTPTR_MAX == 0xffffffffffffffffULL
        #define SIZE_T_SIZE 8
      #else
        /* FIXME */
        #define SIZE_T_SIZE 4
        //#error Unknown integer width.
      #endif
    #endif
  #else
    #error Unsupported platform.
  #endif
#endif

#endif /* PLATFORM_TYPE_SIZE_H */
