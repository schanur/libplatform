#ifndef PLATFORM_COMPILER_H
#define PLATFORM_COMPILER_H

#include "os_detect.h"

#ifdef PLATFORM_LINUX
#define COMPILER_ALIGN(alignment,var) var  __attribute__ ((aligned (alignment)))
//#define COMPILER_PUSH_PACK(bytes)
#define COMPILER_NORETURN(func)       func __attribute__ ((noreturn))

#else
#ifdef PLATFORM_WINDOWS
#define COMPILER_ALIGN(alignment, var) __declspec(align(alignment)) var
#define COMPILER_NORETURN(func)        __declspec(noreturn) func

#else
#error No platform defined.
#endif
#endif


#endif /* PLATFORM_COMPILER_H */
