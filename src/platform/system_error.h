#ifndef PLATFORM_SYSTEM_ERROR_H
#define PLATFORM_SYSTEM_ERROR_H

#include "os_detect.h"

#ifdef PLATFORM_LINUX

  #include "string.h"

  #define SYS_ERR_STRERROR

#else
  #ifdef PLATFORM_WINDOWS



  #else
    #error No platform defined.
  #endif
#endif

#endif /* PLATFORM_SYSTEM_ERROR_H */
