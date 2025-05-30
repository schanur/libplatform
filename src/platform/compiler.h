#ifndef PLATFORM_COMPILER_H
#define PLATFORM_COMPILER_H

#include "os_detect.h"


#define PLTF_COMPILER_GCC     10
#define PLTF_COMPILER_MINGW32 12
#define PLTF_COMPILER_CLANG   20
#define PLTF_COMPILER_MSC     30

#if defined(__clang__)
#define PLTF_COMPILER PLTF_COMPILER_CLANG
#elif defined(_MSC_VER)
#define PLTF_COMPILER PLTF_COMPILER_MSC
#elif defined(__GNUC__)
#define PLTF_COMPILER PLTF_COMPILER_GCC
#else
#error Unknown Compiler
#endif


#define PLATFORM_PRIVATE_STR_INTERN(s)                                      #s
#define PLATFORM_PRIVATE_STR(x,y)                                           PLATFORM_PRIVATE_STR_INTERN(x ## y)

#if defined(PLATFORM_LINUX) || __MINGW32__
  #define PLATFORM_PRIVATE_DO_PRAGMA(x)                                     _Pragma (#x)
  #define PLATFORM_PRIVATE_PRAGMA(compiler,x)                               PLATFORM_PRIVATE_DO_PRAGMA(compiler diagnostic x)
#else
  #define PLATFORM_PRIVATE_DO_PRAGMA(x)                                     __pragma (#x)
  #define PLATFORM_PRIVATE_PRAGMA(compiler,x)                               PLATFORM_PRIVATE_DO_PRAGMA(warning(x))
#endif

#if defined(__clang__)
  # define COMPILER_DISABLE_WARNING(gcc_unused,clang_option,msvc_unused)    PLATFORM_PRIVATE_PRAGMA(clang,push) PLATFORM_PRIVATE_PRAGMA(clang,ignored PLATFORM_PRIVATE_STR(-W,clang_option))
  # define COMPILER_ENABLE_WARNING(gcc_unused,clang_option,msvc_unused)     PLATFORM_PRIVATE_PRAGMA(clang,pop)
#elif defined(_MSC_VER)
  # define COMPILER_DISABLE_WARNING(gcc_unused,clang_unused,msvc_errorcode) PLATFORM_PRIVATE_PRAGMA(msvc,push)  PLATFORM_PRIVATE_PRAGMA(warning(disable:##msvc_errorcode))
  # define COMPILER_ENABLE_WARNING(gcc_unused,clang_unused,msvc_errorcode)  PLATFORM_PRIVATE_PRAGMA(msvc,pop)
#elif defined(__GNUC__)
  #if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
    # define COMPILER_DISABLE_WARNING(gcc_option,clang_unused,msvc_unused)  PLATFORM_PRIVATE_PRAGMA(GCC,push)   \
                                                                            PLATFORM_PRIVATE_PRAGMA(GCC,ignored PLATFORM_PRIVATE_STR(-W,gcc_option))
    # define COMPILER_ENABLE_WARNING(gcc_option,clang_unused,msvc_unused)   PLATFORM_PRIVATE_PRAGMA(GCC,pop)
  #else
    # define COMPILER_DISABLE_WARNING(gcc_option,clang_unused,msvc_unused)  PLATFORM_PRIVATE_PRAGMA(GCC,ignored PLATFORM_PRIVATE_STR(-W,gcc_option))
    # define COMPILER_ENABLE_WARNING(gcc_option,clang_option,msvc_unused)   PLATFORM_PRIVATE_PRAGMA(GCC,warning PLATFORM_PRIVATE_STR(-W,gcc_option))
  #endif
#endif


/* Incomplete: Verified for Clang */
#define COMPILER_DISABLE_WARNING_DOUBLE_PROMOTION                           COMPILER_DISABLE_WARNING(double-promotion, double-promotion, 42)
#define COMPILER_ENABLE_WARNING_DOUBLE_PROMOTION                            COMPILER_ENABLE_WARNING (double-promotion, double-promotion, 42)

/* TODO: Find numeric value for MS compiler. */
#define COMPILER_DISABLE_WARNING_CAST_QUALIFIER                             COMPILER_DISABLE_WARNING(cast-qual, cast-qual, -1)
#define COMPILER_ENABLE_WARNING_CAST_QUALIFIER                              COMPILER_ENABLE_WARNING (cast-qual, cast-qual, -1)

/* TODO: Find numeric value for MS compiler. */
#define COMPILER_DISABLE_WARNING_UNUSED_FUNCTION                            COMPILER_DISABLE_WARNING(unused-function,       unused-function,      -1)
#define COMPILER_ENABLE_WARNING_UNUSED_FUNCTION                             COMPILER_ENABLE_WARNING (unused-function,       unused-function,      -1)

/* TODO: Find numeric value for MS compiler. */
#define COMPILER_DISABLE_WARNING_UNUSED_LOCAL_TYPEDEF                       COMPILER_DISABLE_WARNING(unused-local-typedefs, unused-local-typedef, -1)
#define COMPILER_ENABLE_WARNING_UNUSED_LOCAL_TYPEDEF                        COMPILER_ENABLE_WARNING (unused-local-typedefs, unused-local-typedef, -1)

/* TODO: Find numeric value for MS compiler. */
#define COMPILER_DISABLE_WARNING_FORMAT_STR_IS_NOT_STR_LITERAL              COMPILER_DISABLE_WARNING(format-nonliteral, format-nonliteral, -1)
#define COMPILER_ENABLE_WARNING_FORMAT_STR_IS_NOT_STR_LITERAL               COMPILER_ENABLE_WARNING (format-nonliteral, format-nonliteral, -1)


#if defined(PLATFORM_LINUX) || defined(__MINGW32__)
  #define COMPILER_ALIGN(alignment,var)    var             __attribute__ ((aligned (alignment)))
/*#define COMPILER_PUSH_PACK(bytes)*/
  #define COMPILER_NORETURN(func_sig)      void func_sig   __attribute__ ((noreturn))

  #define PLTF_COMPILER_PACKED(structure)  structure       __attribute__ ((packed))
  #define COMPILER_WEAK_SYMBOL(symbol)     symbol          __attribute__ ((weak))

  /* #define COMPILER_PUSH_WARNING() */
#else
  #ifdef PLATFORM_WINDOWS
    #define COMPILER_ALIGN(alignment, var) __declspec(align(alignment)) var
    #define COMPILER_NORETURN(func_sig)    __declspec(noreturn)         func_sig
    #define COMPILER_WEAK_SYMBOL(symbol)   __declspec(selectany)        symbol


    #define __func__ __FUNCTION__

    #ifndef __MINGW32__
      #ifndef _MSC_VER
        #error _MSC_VER not defined
      #endif
      #if _MSC_VER <= 1500 /* Visual Studio 2008 or older. */
        #define NO_C_STD_COMPLIANT_STDINT_HEADER
      #endif
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
