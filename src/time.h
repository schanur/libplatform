#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H 1

#include "os_detect.h"

#ifdef PLATFORM_LINUX
#include <unistd.h>
#define SLEEP_SEC(seconds) sleep(seconds);

#else
#ifdef PLATFORM_WINDOWS
#define SLEEP_SEC(seconds) Sleep(seconds * 1000);

#else
#error No platform defined.
#endif
#endif


#endif /* PLATFORM_TIME_H */
