#ifndef PLATFORM_OS_DETECT_H
#define PLATFORM_OS_DETECT_H


#define PLTF_OS_LINUX        10
#define PLTF_OS_OSX          20
#define PLTF_OS_WINDOWS      30

#define PLTF_OS_ANDROID      80
#define PLTF_OS_APPLE_IOS    90

#define PLTF_OS_BEOS         120


#define PLTF_OS_TYPE_POSIX   1000
#define PLTF_OS_TYPE_WINDOWS 1100


#if defined(_MSC_VER) || defined(__cygwin__) || defined(__MINGW32__)
  #define PLATFORM_WINDOWS
  #define PLTF_OS PLTF_OS_WINDOWS
#else
  #define PLATFORM_LINUX
  #define PLTF_OS PLTF_OS_LINUX
#endif


#if (PLTF_OS == PLTF_OS_LINUX) || (PLTF_OS == PLTF_OS_OSX)
#define PLTF_OS_TYPE PLTF_OS_TYPE_POSIX
#endif

#if PLTF_OS == PLTF_OS_WINDOWS
  #define PLTF_OS_TYPE PLTF_OS_TYPE_WINDOWS
#endif



#ifndef PLTF_OS
#error No platform detected
#endif

#endif /* PLATFORM_OS_DETECT_H */
