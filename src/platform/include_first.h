#ifndef PLATFORM_INCLUDE_FIRST_H
#define PLATFORM_INCLUDE_FIRST_H

#include "os_detect.h"


#if defined(PLATFORM_LINUX)

#ifndef _DEFAULT_SOURCE
  #error _DEFAULT_SOURCE is required to be defined. Compile with -D_DEFAULT_SOURCE.
/* #define _DEFAULT_SOURCE */
#endif

#elif defined(PLATFORM_WINDOWS)

#else
#error No platform defined.
#endif


#endif /* PLATFORM_INCLUDE_FIRST_H */
