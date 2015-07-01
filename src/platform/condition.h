#ifndef PLATFORM_CONDITION_H
#define PLATFORM_CONDITION_H

#include "os_detect.h"

#ifdef PLATFORM_LINUX

#define _XOPEN_SOURCE 700
#define _POSIX_C_SOURCE 200809L


#include "pthread.h"

typedef pthread_cond_t condition_t;

#define CONDITION_CREATE(condition)                     pthread_cond_init     (condition, NULL)
//#define CONDITION_CREATE(condition,flags)               pthread_cond_init     (condition, NULL)

#define CONDITION_SIGNAL(condition)                     pthread_cond_signal   (condition)
#define CONDITION_BROADCAST(condition)                  pthread_cond_broadcast(condition)
#define CONDITION_WAIT(condition,mutex)                 pthread_cond_wait     (condition, mutex)
#define CONDITION_WAIT_TIMEOUT(condition,mutex,timeout) pthread_cond_timedwait(condition, mutex, timeout)
#define CONDITION_DESTROY(condition)                    pthread_cond_destroy  (condition)

#else
#ifdef PLATFORM_WINDOWS


#else
#error No platform defined.
#endif
#endif

#endif /* PLATFORM_CONDITION_H */
