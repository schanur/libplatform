#ifndef PLATFORM_CPPLIB_H
#define PLATFORM_CPPLIB_H

#include "os_detect.h"

#ifdef PLATFORM_LINUX

#define STD__MIN std::min
#define STD__MAX std::max

#else
#ifdef PLATFORM_WINDOWS

#define STD__MIN min
#define STD__MAX max

#else
#error No platform defined.
#endif
#endif


#endif /* PLATFORM_CPPLIB_H */
