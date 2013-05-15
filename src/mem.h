#ifndef PLATFORM_MEM_H
#define PLATFORM_MEM_H

#include "platform_os_detect.h"

#define MEM_PAGE_SIZE 4096

#ifdef PLATFORM_LINUX

#include "sys/mman.h"

#define MEM_READ  PROT_READ
#define MEM_WRITE PROT_WRITE
#define MEM_EXEC  PROT_EXEC

#define MEM_ALLOC_ANON_PAGE(page_cnt,mode) (mmap(NULL, page_cnt * MEM_PAGE_SIZE, mode, MAP_ANONYMOUS, -1, 0)) 
#define MEM_FREE_ANON_PAGE(ptr) (munmap(ptr, page_cnt * MEM_PAGE_SIZE))


#else
#ifdef PLATFORM_WINDOWS

#define MEM_READ
#define MEM_WRITE
#define MEM_EXEC

#else
#error No platform defined.
#endif
#endif


#endif /* PLATFORM_MEM_H */
