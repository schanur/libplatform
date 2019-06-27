#ifndef PLATFORM_FLOATING_POINT_H
#define PLATFORM_FLOATING_POINT_H

#include "os_detect.h"


#ifdef PLATFORM_LINUX


#else
  #ifdef PLATFORM_WINDOWS



  #else
    #error No platform defined.
  #endif
#endif

#endif /* PLATFORM_FLOATING_POINT_H */
