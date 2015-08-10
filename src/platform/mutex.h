#ifndef PLATFORM_MUTEX_H
#define PLATFORM_MUTEX_H

#include "os_detect.h"

#ifdef PLATFORM_LINUX
#include <pthread.h>

typedef pthread_mutex_t mutex_t;
#define MUTEX_CREATE(mutex)  pthread_mutex_init(mutex, NULL)
#define MUTEX_DESTROY(mutex) pthread_mutex_destroy(mutex)
#define MUTEX_LOCK(mutex)    pthread_mutex_lock(mutex)
#define MUTEX_UNLOCK(mutex)  pthread_mutex_unlock(mutex)

#else
#ifdef PLATFORM_WINDOWS

/* #include <winsock.h> */
#include <winsock2.h>
#include <windows.h>

typedef HANDLE mutex_t;
#define MUTEX_CREATE(mutex)  ((*mutex = (CreateMutex(NULL, FALSE, NULL))) == NULL)
/* #define MUTEX_CREATE(mutex)  mutex = CreateMutex(NULL, FALSE, NULL) */
#define MUTEX_DESTROY(mutex) (CloseHandle(*mutex))
/* #define MUTEX_LOCK(mutex)    (WaitForSingleObject(*mutex, INFINITE) != WAIT_OBJECT_0) */
#define MUTEX_LOCK(mutex)    (WaitForSingleObject(*mutex, INFINITE))
#define MUTEX_UNLOCK(mutex)  (ReleaseMutex(*mutex))

#else
#error No platform defined.
#endif
#endif

#endif /* PLATFORM_MUTEX_H */
