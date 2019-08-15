#ifndef PLATFORM_FILESYSTEM_H
#define PLATFORM_FILESYSTEM_H

#include "os_detect.h"


#ifdef PLATFORM_LINUX

  #include <sys/types.h>
  #include <sys/stat.h>

  /* #define _POSIX_C_SOURCE 200809L */
  #include <linux/limits.h> /* PATH_MAX   */
  #include <limits.h>       /* realpath() */
  #include <stdlib.h>       /* realpath() */
  #include <unistd.h>       /* readlink() */

  #define PLTF_PATH_MAX PATH_MAX

  #define PLTF_MKDIR(err,pathname)                                         (err = (mkdir(pathname, 0711) != -1))

  #ifdef _POSIX_SOURCE
    #define PLTF_ABS_EXECUTABLE_FILENAME(err,filename,filename_buf_size)   (err = (readlink("/proc/self/exe", filename, filename_buf_size) == -1))
  #endif

  #define PLTF_REALPATH(err,path,resolved_path)                            (err = (realpath(path, resolved_path)) == NULL)


/* #define PLTF_CURRENT_WORKING_DIR */
/* #define PLTF_CHANGE_WORKING_DIR */


/* #elif PLATFORM_FREEBSD */
#else
  #ifdef PLATFORM_WINDOWS

    #include <dir.h>

    #define PLTF_MKDIR(err,pathname) (err = (mkdir(pathname) != -1))

  #else
    #error No platform defined.
  #endif
#endif


#endif /* PLATFORM_FILESYSTEM_H */
