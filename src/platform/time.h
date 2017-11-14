#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H 1

#include "os_detect.h"

#ifdef PLATFORM_LINUX
#include <unistd.h>
#define SLEEP_SEC(seconds)             sleep(seconds);
#define SLEEP_MSEC(milliseconds)       usleep(1000 * milliseconds)
#define CLOCK_GETTIME(clk_id,time_ptr) clock_gettime(clk_id, time_ptr)

#else
#ifdef PLATFORM_WINDOWS

//#if 0
#include <windows.h> /* Sleep() */

#define SLEEP_SEC(seconds)             Sleep(seconds * 1000);
#define SLEEP_MSEC(milliseconds)       Sleep(milliseconds);
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
