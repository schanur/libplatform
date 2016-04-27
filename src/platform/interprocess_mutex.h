#ifndef PLATFORM_INTERPROCESS_MUTEX_H
#define PLATFORM_INTERPROCESS_MUTEX_H

#include "os_detect.h"

#ifdef PLATFORM_LINUX
  #error Interprocess mutexes are not implemented on Linux.
#else
  #ifdef PLATFORM_WINDOWS

    #define NOMINMAX
    /* #include <winsock.h> */
    #include <winsock2.h>
    #include <windows.h>

    typedef HANDLE mutex_t;
    #define INTERPROCESS_MUTEX_CREATE(mutex)  ((*mutex = (CreateMutex(NULL, FALSE, NULL))) == NULL)
    /* #define MUTEX_CREATE(mutex)  mutex = CreateMutex(NULL, FALSE, NULL) */
    #define INTERPROCESS_MUTEX_DESTROY(mutex) (CloseHandle(*mutex))
    /* #define MUTEX_LOCK(mutex)    (WaitForSingleObject(*mutex, INFINITE) != WAIT_OBJECT_0) */
    #define INTERPROCESS_MUTEX_LOCK(mutex)    (WaitForSingleObject(*mutex, INFINITE))
    #define INTERPROCESS_MUTEX_UNLOCK(mutex)  (ReleaseMutex(*mutex))

  #else
    #error No platform defined.
  #endif /* PLATFORM_WINDOWS */
#endif /* PLATFORM_LINUX */

#endif /* PLATFORM_INTERPROCESS_MUTEX_H */
