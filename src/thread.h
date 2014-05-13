#ifndef PLATFORM_THREAD_H
#define PLATFORM_THREAD_H

#include "os_detect.h"
#include "mutex.h"

#include <assert.h>

#ifdef PLATFORM_LINUX
#include <pthread.h>
typedef pthread_t      thread_handle_t;
typedef pthread_cond_t thread_cond_t;

struct thread_wait_t {
	thread_cond_t             cond_wake;
	mutex_t                   mutex_wake;
};

/* Makros to spawn and end threads. */
#define THREAD_CREATE(err,hdl,func,args) (err = pthread_create(&hdl, NULL, func, (void*) args))
#define THREAD_KILL(err,hdl)             
#define THREAD_END(err,hdl)
#define THREAD_JOIN(err,hdl,ret)         (err = pthread_join  (&hdl, &ret))
//#define THREAD_SIGNAL()

#define THREAD_COND_SAFE_WAIT(wait_var, compare, call)                  \
    do {                                                                \
        MUTEX_LOCK(&(wait_var->mutex_wake));                            \
        while (compare) {                                               \
            THREAD_COND_WAIT(wait_var);                                 \
        }                                                               \
        call;                                                           \
        MUTEX_UNLOCK(&(wait_var->mutex_wake));                          \
    } while (0);

#define THREAD_CALL /* No special calling convention required on posix OS.*/
#else

#ifdef PLATFORM_WINDOWS
typedef HANDLE   thread_handle_t;
typedef uint32_t thread_ret_t;
#define THREAD_CREATE(ERR, HDL, FUNC, ARGS) (err = ((unsigned long) (HDL = (thread_handle_t) _beginthreadex(NULL, 0, &FUNC, (void*) ARGS, 0, NULL))) == 1L)
#define THREAD_END _endthreadex()

#define THREAD_COND_INIT(cond)                 (pthread_cond_init(cond, NULL))
#define THREAD_COND_SIGNAL(cond)               (pthread_cond_signal(cond))
#define THREAD_COND_BROADCAST(cond)            (pthread_cond_broadcast(cond)))
#define THREAD_COND_WAIT(cond,mutex)           (pthread_cond_wait(cond, mutex))
#define THREAD_COND_TIMEDWAIT(cond,mutex,time) (pthread_cond_timedwait(cond, mutex, time))
#define THREAD_COND_DESTROY(cond)              (pthread_cond_destroy(cond))


#define THREAD_CALL __stdcall /* For managed code (.NET) use __clrcall instead. */

#else
#error No platform defined.
#endif
#endif

#endif /* PLATFORM_THREAD_H */
