#ifndef PLATFORM_MEM_H
#define PLATFORM_MEM_H

#include "os_detect.h"

#define PLTF__MEM_PAGE_SIZE 4096

#ifdef PLATFORM_LINUX

#include "sys/mman.h"

#define PLTF__MEM_READ  PROT_READ
#define PLTF__MEM_WRITE PROT_WRITE
#define PLTF__MEM_EXEC  PROT_EXEC

#define PLTF__MEM_ALLOC_ANON_PAGE(page_cnt,mode) (mmap  (NULL, page_cnt * MEM_PAGE_SIZE, mode, MAP_ANONYMOUS, -1, 0))
#define PLTF__MEM_FREE_ANON_PAGE(ptr)            (munmap(ptr,  page_cnt * MEM_PAGE_SIZE))


#else
#ifdef PLATFORM_WINDOWS

#define PLTF__MEM_READ
#define PLTF__MEM_WRITE
#define PLTF__MEM_EXEC

#else
#error No platform defined.
#endif
#endif


#endif /* PLATFORM_MEM_H */
