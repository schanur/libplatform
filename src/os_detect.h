#ifndef PLATFORM_OS_DETECT_H
#define PLATFORM_OS_DETECT_H

#if !defined(PLATFORM_WINDOWS) && !defined(PLATFORM_LINUX)
#ifdef _MSC_VER
#define PLATFORM_WINDOWS
#else
#define PLATFORM_LINUX
#endif
#endif

#endif /* PLATFORM_OS_DETECT_H */
