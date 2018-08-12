#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H 1

#include "os_detect.h"

#include "assertion.h"

#ifdef PLATFORM_LINUX
  #include <unistd.h> /* sleep() */

  #include <time.h>   /* nanosleep() */


  #ifdef _SOURCE_POSIX

    /* Currently only supported on Unix like systems. The currently
     * highest supported time resolution on Windows implemented in this
     * library is milliseconds.
     */
    #define PL_PRIVATE_SLEEP_NSEC_CHECK(err,remaining,time,factor)        \
      do {                                                                \
          long            nanoseconds;                                    \
          struct timespec req, rem;                                       \
          ASSERT_RT(time >= 0);                                           \
          nanoseconds = time * factor;                                    \
          req.tv_sec  = ((time_t) nanoseconds) / 1000000000;              \
          req.tv_nsec = ((long)   nanoseconds) % 1000000000;              \
          err         = nanosleep(&req , &rem);                           \
          remaining   = (rem.tv_sec * 1000000000 + rem.tv_nsec) / factor; \
      } while (0);

    #define PL_PRIVATE_SLEEP_NSEC(nanoseconds)                            \
      do {                                                                \
          struct timespec req, rem;                                       \
          ASSERT_RT(nanoseconds >= 0);                                    \
          req.tv_sec  = ((time_t) nanoseconds) / 1000000000;              \
          req.tv_nsec = ((long)   nanoseconds) % 1000000000;              \
          (void) nanosleep(&req , &rem);                                  \
      } while (0);

    #define SLEEP_NSEC_CHECK(err,remaining,nanoseconds) PL_PRIVATE_SLEEP_NSEC_CHECK(err, remaining, nanoseconds, 1)
    #define SLEEP_NSEC(nanoseconds) PL_PRIVATE_SLEEP_NSEC(nanoseconds)

    /* Usleep is deprecated in newer Posix versions. We use nanosleep
     * instead. TODO: We can use usleep on older systems.
     */
    /* #define SLEEP_MSEC(milliseconds)       usleep(1000 * milliseconds) */

    #define SLEEP_USEC_CHECK(err,remaining,microseconds) PL_PRIVATE_SLEEP_NSEC_CHECK(err, remaining, microseconds, 1000)
    #define SLEEP_USEC(microseconds)                                      \
      do {                                                                \
          ASSERT_RT(microseconds < )
          SLEEP_NSEC(microseconds * 1000)                                 \
}     while (0);

    #define SLEEP_MSEC_CHECK(err,remaining,milliseconds) PL_PRIVATE_SLEEP_NSEC_CHECK(err, remaining, milliseconds, 1000000)
    #define SLEEP_MSEC(milliseconds) SLEEP_NSEC(milliseconds * 1000000)

  #endif /*_SOURCE_POSIX */


  #define SLEEP_SEC(seconds)             ASSERT_RT((int) seconds >= 0); sleep(seconds);

  #define CLOCK_GETTIME(clk_id,time_ptr) clock_gettime(clk_id, time_ptr)

#else
  #ifdef PLATFORM_WINDOWS

  //#if 0
  #include <windows.h> /* Sleep() */

  #define SLEEP_MSEC(milliseconds)       ASSERT_RT(seconds >= 0); Sleep(milliseconds);

  #define SLEEP_SEC(seconds)             ASSERT_RT(seconds >= 0); Sleep(seconds * 1000);

  #define CLOCK_GETTIME(clk_id,time_ptr)
  /* typedef long time_t; */

  /* struct timespec_t { */
  /*     time_t tv_sec; */
  /*     long   tv_nsec; */
  /* }; */
  /* struct timespec_t { */
  /*     int64_t tv_sec; */
  /*     long    tv_nsec; */
  /* }; */
  //#endif


  #else
    #error No platform defined.
  #endif
#endif


#endif /* PLATFORM_TIME_H */
