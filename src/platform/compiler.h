#ifndef PLATFORM_COMPILER_H
#define PLATFORM_COMPILER_H

#include "os_detect.h"

#ifdef PLATFORM_LINUX
  #define COMPILER_ALIGN(alignment,var) var    __attribute__ ((aligned (alignment)))
  //#define COMPILER_PUSH_PACK(bytes)
  #define COMPILER_NORETURN(func)       func   __attribute__ ((noreturn))

  #define COMPILER_WEAK_SYMBOL(symbol)  symbol __attribute__ ((weak))

#else
  #ifdef PLATFORM_WINDOWS
    #define COMPILER_ALIGN(alignment, var) __declspec(align(alignment)) var
    #define COMPILER_NORETURN(func)        __declspec(noreturn)         func
    #define COMPILER_WEAK_SYMBOL(symbol)   __declspec(selectany)        symbol

    #ifndef _MSC_VER
      #error _MSC_VER not defined
    #endif

    #define __func__ __FUNCTION__

    #if _MSC_VER <= 1500 /* Visual Studio 2008 or older. */
      #define NO_C_STD_COMPLIANT_STDINT_HEADER
    #endif

  #else
    #error No platform defined.
  #endif
#endif

#ifdef __cplusplus
  #define COMPILER_REINTERPRET_CAST(type,value) (reinterpret_cast<type>(value))
  #define COMPILER_STATIC_CAST(type,value)      (static_cast     <type>(value))
#else
  #define COMPILER_REINTERPRET_CAST(type,value) ((type) value)
  #define COMPILER_STATIC_CAST(type,value)      ((type) value)
#endif



#endif /* PLATFORM_COMPILER_H */
