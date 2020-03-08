#ifndef PLATFORM_FMEM_H
#define PLATFORM_FMEM_H


#include "os_detect.h"

#if defined(PLATFORM_LINUX)

#include <stdio.h>

typedef FILE* PLTF_FMEM_HDL;

#define PLTF_FMEM_OPEN(err,hdl,buf,buf_size)  (err = (hdl = fmemopen(buf, buf_size, "w")) == NULL)
#define PLTF_FMEM_CLOSE(err,hdl)              (err = (fclose(hdl)) != 0)

#define PLTF_FMEM_WRITE(err,hdl,buf,buf_size) (err = (fwrite(buf, buf_size, 1, hdl)) != 1)
#define PLTF_FMEM_FLUSH(err,hdl)              (err = (fflush(hdl)) != 0)
#elif defined(PLATFORM_WINDOWS)

#else
#error No platform defined.
#endif

#endif /* PLATFORM_FMEM_H */
