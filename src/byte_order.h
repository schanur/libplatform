#ifndef PLATFORM_BYTE_ORDER_H
#define PLATFORM_BYTE_ORDER_H

#include "platform_os_detect.h"

#ifdef PLATFORM_LINUX

#include <netinet/in.h>
#define NTOH_16(x) (ntohs(x))
#define HTON_16(x) (htons(x))
#define NTOH_32(x) (ntohl(x))
#define HTON_32(x) (htonl(x))
#if __BYTE_ORDER == __BIG_ENDIAN
#define NTOH_64(x) (x)
#define HTON_64(x) (x)
#else
#include <byteswap.h>
#define NTOH_64(x) (bswap_64(x))
#define HTON_64(x) (bswap_64(x))
#endif

#else
#ifdef PLATFORM_WINDOWS

#else
#error No platform defined.
#endif
#endif


#endif /* PLATFORM_BYTE_ORDER_H */
