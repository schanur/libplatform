#ifndef PLATFORM_OS_DETECT_H
#define PLATFORM_OS_DETECT_H

/* #define PLATFORM_WINDOWS */

#if !defined(PLATFORM_WINDOWS) && !defined(PLATFORM_LINUX)
#if defined(_MSC_VER) || defined(__cygwin__) || defined(__MINGW32__)
#define PLATFORM_WINDOWS
#else
#define PLATFORM_LINUX
#endif
#endif


#if !defined(PLATFORM_WINDOWS) && !defined(PLATFORM_LINUX)
#error No platform detected
#endif

#endif /* PLATFORM_OS_DETECT_H */
