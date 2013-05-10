#ifndef PLATFORM_SHM_H
#define PLATFORM_SHM_H

#include "platform_os_detect.h"

#ifdef PLATFORM_LINUX

#define _XOPEN_SOURCE 700
#define _POSIX_C_SOURCE 200809L
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef int shm_t;

#define PAD(QWE, WER) QWE WER
//#define PADAA(QWE) otv_t QWE

//; char pad[sizeof(void*) - 1]

#define SHM_OPEN(name, flags)  shm_open(name, flags, 1)
#define SHM_CLOSE(name)

/*#define SHM_CREATE
#define SHM_ATTACH
#define SHM_DEATTACH
#define SHM_DESTROY*/

#else
#ifdef PLATFORM_WINDOWS


#else
#error No platform defined.
#endif
#endif

#endif /* PLATFORM_SHM_H */
