#ifndef PLATFORM_DYNLIB_H
#define PLATFORM_DYNLIB_H

#include "os_detect.h"

#ifdef PLATFORM_LINUX
#include <dlfcn.h>
typedef void* dyn_lib_t;
#define LOAD_DYN_LIB(lib_file) dlopen(lib_file, RTLD_LAZY)
#define UNLOAD_DYN_LIB dlclose
#define GET_FUNC_ADDR dlsym


#else
#ifdef PLATFORM_WINDOWS
/* #include <winsock32.h> */
#include <winsock2.h>
#include <windows.h>
typedef HMODULE dyn_lib_t;
#define LOAD_DYN_LIB LoadLibrary
#define UNLOAD_DYN_LIB FreeLibrary
#define GET_FUNC_ADDR GetProcAddress


#else
#error No platform defined.
#endif
#endif

#endif /* PLATFORM_DYNLIB_H */

