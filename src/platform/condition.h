#ifndef PLATFORM_CONDITION_H
#define PLATFORM_CONDITION_H

#include "os_detect.h"
#include "mutex.h"

#define CONDITION_ERR__NO_ERR      0
#define CONDITION_ERR__INTERRUPTED 0 /* Interrupted by signal. */
#define CONDITION_ERR__TIMEOUT     0
#define CONDITION_ERR__IN_USE      0 /* Cannot destroy because already in use. */

#define CONDITION__NS2MS(ns)       (ns / 1000000)

/* #define CONDITION__GET_ERROR(system_err_code_in, condition_err_code_out) \ */
/*     (switch (system_error_code) {                                       \ */
/*     case                                                                     \ */
/*         }                                                               \ */
/*         ) */

#ifdef PLATFORM_LINUX

  /* #define _XOPEN_SOURCE 700 */
  /* #define _POSIX_C_SOURCE 200809L */

  #include <pthread.h>

  typedef pthread_cond_t       condition_t;
  typedef int                  condition_err_t;
  typedef int                  condition_flag_t;

  #define CONDITION_CREATE(condition)                                             (                      pthread_cond_init           (condition, NULL))
  #define CONDITION_SIGNAL(err,condition)                                         (                err = pthread_cond_signal         (condition))
  #define CONDITION_BROADCAST(err,condition)                                      (                err = pthread_cond_broadcast      (condition))
  #define CONDITION_WAIT(err,condition,mutex)                                     (                err = pthread_cond_wait           (condition, mutex))
  #define CONDITION_WAIT_TIMEOUT(err,condition,mutex,timeout_ns,timeout_flag)     (timeout_flag = (err = pthread_cond_timedwait      (condition, mutex, timeout)) == ETIMEDOUT)
  #define CONDITION_DESTROY(err,condition)                                        (                err = pthread_cond_destroy        (condition))

#else
  #ifdef PLATFORM_WINDOWS

    #ifdef CONDITION_VARIABLE_INIT
      #define NOMINMAX
      #include "WinBase.h"
      #include "Windows.h"

      typedef CONDITION_VARIABLE condition_t;
      typedef BOOL               condition_err_t;
      typedef int                condition_flag_t;

      #define CONDITION_CREATE(condition)                                         (                       InitializeConditionVariable(condition))
      #define CONDITION_SIGNAL(err,condition)                                     (                err = !WakeConditionVariable      (condition))
      #define CONDITION_BROADCAST(err,condition)                                  (                err = !WakeAllConditionVariable   (condition))
      #define CONDITION_WAIT(err,condition,mutex)                                 (                err = !SleepConditionVariableCS   (condition, mutex, INFINITE                    ))
      #define CONDITION_WAIT_TIMEOUT(err,condition,mutex,timeout_ns,timeout_flag) (timeout_flag = (err = !SleepConditionVariableCS   (condition, mutex, CONDITION__NS2MS(timeout_ns))) && GetLastError() == ERROR_TIMEOUT)
      #define CONDITION_DESTROY(err,condition)                                    (err = 0; (void) condition) /* Windows condition variables have no method of destruction. */
    #else
      /* The Windows version does not support conditional variables.
       * We simulate this feature by using
       */
      //#define
    #endif
  #else
    #error No platform defined.
  #endif
#endif

#endif /* PLATFORM_CONDITION_H */
