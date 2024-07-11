#ifndef PLATFORM_MUTEX_H
#define PLATFORM_MUTEX_H

#include "os_detect.h"

/* #define MUTEX_DEBUG */

#ifdef PLATFORM_LINUX
  #include <pthread.h>

  #ifdef MUTEX_DEBUG
    #define PLATFORM__MUTEX__BREAK_ON_DEADLOCK
    struct mutex_debug_t {
        pthread_mutex_t lock;
        struct lock_position_t {
            char  file    [64];
            char *function;
            int   line;
        } lock_position;
    };
    typedef struct mutex_debug_t mutex_t;
  #else
    typedef pthread_mutex_t mutex_t;
  #endif

  #include <stdio.h>
  #ifdef PLATFORM__MUTEX__BREAK_ON_DEADLOCK
    #ifndef PLATFORM__DBG_MSG_FUNC
      #define PLATFORM__DBG_MSG_FUNC() /**/
    #endif
    #include <stdlib.h>

#define PLATFORM__MUTEX__DBG_MSG_FUNC(previous_lock_line)               \
    fprintf(stderr,                                                     \
            "%s:%i:%s: Mutex deadlock. "                                \
            "Previous locked at line: %i in function %s\n",             \
            __FILE__, __LINE__, __func__,                               \
            previous_lock_line, previous_lock_function                  \
        )

#define MUTEX_CREATE(mutex)                                             \
    {                                                                   \
        int mutex_i;                                                    \
        pthread_mutexattr_t platform_mutex__deadlock_init_attr;         \
        (void) pthread_mutexattr_init(&platform_mutex__deadlock_init_attr); \
        if (pthread_mutexattr_settype(&platform_mutex__deadlock_init_attr, PTHREAD_MUTEX_ERRORCHECK_NP)) { \
            exit(1);                                                    \
        }                                                               \
        pthread_mutex_init(&((mutex)->lock), &platform_mutex__deadlock_init_attr); \
        for (mutex_i = 0; mutex_i < 64; ++mutex_i) {                    \
            (mutex)->lock_position.file    [mutex_i] = 0;               \
            (mutex)->lock_position.function[mutex_i] = 0;               \
        }                                                               \
        (mutex)->lock_position.line = -1;                               \
    }

#define MUTEX_LOCK(mutex)                                               \
    if (!pthread_mutex_lock(&((mutex)->lock))) {                        \
        (mutex)->lock_position.line     = __LINE__;                     \
        (mutex)->lock_position.functoin = __func__;                     \
    } else {                                                            \
        PLATFORM__MUTEX__DBG_MSG_FUNC((mutex)->lock_position.line);     \
        exit(1);                                                        \
    }
    #define MUTEX_DESTROY(mutex)   (    pthread_mutex_destroy(&((mutex)->lock)))
    #define MUTEX_UNLOCK(mutex)    (    pthread_mutex_unlock (&((mutex)->lock)))
  #else
    #define MUTEX_CREATE(mutex)    (    pthread_mutex_init   (   mutex, NULL))
    #define MUTEX_LOCK(mutex)      (    pthread_mutex_lock   (   mutex))
    #define MUTEX_DESTROY(mutex)   (    pthread_mutex_destroy(   mutex))
    #define MUTEX_UNLOCK(mutex)    (    pthread_mutex_unlock (   mutex))
  #endif
  #define   MUTEX_IS_LOCKED

#else
  #ifdef PLATFORM_WINDOWS

    /* TODO: Use lightweight mutex (critical section in windows terms)
     * instead of heavy interprocess locks.
     */
    #define MUTEX__CRITICAL_SECTION_SUPPORTED
    #ifdef MUTEX__CRITICAL_SECTION_SUPPORTED
      #define NOMINMAX
      #include <winsock2.h>
      #include <windows.h>

      typedef CRITICAL_SECTION mutex_t;
      #define MUTEX_CREATE(mutex)  (InitializeCriticalSection(mutex))
      #define MUTEX_DESTROY(mutex) (DeleteCriticalSection    (mutex))
      #define MUTEX_LOCK(mutex)    (EnterCriticalSection     (mutex))
      #define MUTEX_UNLOCK(mutex)  (LeaveCriticalSection     (mutex))

    #else
      #define NOMINMAX
      /* #include <winsock.h> */
      #include <winsock2.h>
      #include <windows.h>

      typedef HANDLE mutex_t;
      #define MUTEX_CREATE(mutex)  ((void) (*mutex = (CreateMutex(NULL, FALSE, NULL))))
      #define MUTEX_DESTROY(mutex) (CloseHandle(*mutex))
      /* #define MUTEX_LOCK(mutex)    (WaitForSingleObject(*mutex, INFINITE) != WAIT_OBJECT_0) */
      #define MUTEX_LOCK(mutex)    (WaitForSingleObject(*mutex, INFINITE))
      #define MUTEX_UNLOCK(mutex)  (ReleaseMutex(*mutex))
    #endif
  #else
    #error No platform defined.
  #endif /* PLATFORM_WINDOWS */
#endif /* PLATFORM_LINUX */

#endif /* PLATFORM_MUTEX_H */
