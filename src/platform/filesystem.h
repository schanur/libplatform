#ifndef PLATFORM_FILESYSTEM_H
#define PLATFORM_FILESYSTEM_H

#include "os_detect.h"


#ifdef PLATFORM_LINUX

  #include <sys/types.h>
  #include <sys/stat.h>

#define PLTF_MKDIR(err,pathname)     (err = (mkdir(pathname, 0711) != -1))

#else
  #ifdef PLATFORM_WINDOWS

    #include <dir.h>

    #define PLTF_MKDIR(err,pathname) (err = (mkdir(pathname) != -1))

  #else
    #error No platform defined.
  #endif
#endif


#endif /* PLATFORM_FILESYSTEM_H */
