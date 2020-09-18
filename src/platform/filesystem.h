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

  #include <errno.h>        /* ENOENT */

  #define PLTF_PATH_MAX PATH_MAX


  #define PLTF_MKDIR(err,pathname)                                         (err = (mkdir(pathname, 0711) != 0))
  #define PLTF_RMDIR(err,pathname)                                         (err = (rmdir(pathname)       != 0))
  #define PLTF_DIR_EXIST(err,pathname,dir_exists)                \
  do {                                                           \
      int stat_err;                                              \
      struct stat statbuf;                                       \
                                                                 \
      err = 0;                                                   \
      stat_err   = stat(pathname, &statbuf) == -1;               \
      dir_exists = (!stat_err && S_ISDIR(statbuf.st_mode));      \
  } while (0)

  #ifdef _POSIX_SOURCE
    #define PLTF_ABS_EXECUTABLE_FILENAME(err,filename,filename_buf_size)   (err = (readlink("/proc/self/exe", filename, filename_buf_size) == -1))
  #endif

  #define PLTF_REALPATH(err,path,resolved_path)                            (err = (realpath(path, resolved_path)) == NULL)


/* #define PLTF_CURRENT_WORKING_DIR */
/* #define PLTF_CHANGE_WORKING_DIR */


/* #elif PLATFORM_FREEBSD */
#elif defined(PLATFORM_WINDOWS)

  #include <dir.h>     /* mkdir() */
  #include <windows.h> /* RemoveDirectoryA() */
  #include <windef.h>  /* bool datatype */

  #define PLTF_PATH_MAX PATH_MAX

  #define PLTF_MKDIR(err,pathname)                                         (err = (mkdir(pathname)            == -1))
  #define PLTF_RMDIR(err,pathname)                                         (err = (RemoveDirectoryA(pathname) ==  0))
  #define PLTF_DIR_EXIST(err,pathname,dir_exists)                       \
    do {                                                                \
        DWORD attrib = GetFileAttributes(pathname);                     \
        err          = 0;                                               \
        dir_exists   = (attrib != INVALID_FILE_ATTRIBUTES) && (attrib & FILE_ATTRIBUTE_DIRECTORY); \
    } while (0)

#else
  #error No platform defined.
#endif



#endif /* PLATFORM_FILESYSTEM_H */
