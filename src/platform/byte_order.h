#ifndef PLATFORM_BYTE_ORDER_H
  #define PLATFORM_BYTE_ORDER_H

  #ifdef PLATFORM_BYTE_ORDER
    #error Redefinition of PLATFORM_BYTE_ORDER
  #endif
  #if __BYTE_ORDER == __BIG_ENDIAN
    #define PLATFORM_BYTE_ORDER BIG_ENDIAN
  #else
    #define PLATFORM_BYTE_ORDER LITTLE_ENDIAN
  #endif


  #include "os_detect.h"

  #ifdef PLATFORM_LINUX

    #include <netinet/in.h>
    #define NTOH_16(x) (ntohs(x))
    #define HTON_16(x) (htons(x))
    #define NTOH_32(x) (ntohl(x))
    #define HTON_32(x) (htonl(x))
    #if PLATFORM_BYTE_ORDER == BIG_ENDIAN
      #define NTOH_64(x) (x)
      #define HTON_64(x) (x)
    #else
      #include <byteswap.h>
      #define NTOH_64(x) ((uint64_t) bswap_64(x))
      #define HTON_64(x) ((uint64_t) bswap_64(x))
      /* #define NTOH_64(x) /\**\/ */
      /* #define HTON_64(x) /\**\/ */
    #endif

  #else
    #ifdef PLATFORM_WINDOWS
      #if PLATFORM_BYTE_ORDER != LITTLE_ENDIAN
	#error Wrong byte order. Makros only work on little endian maschines atm.
      #endif
      #include <winsock2.h>
      #include <sys/param.h>

#define NTOH_64(x) (x)
#define HTON_64(x) (x)
      /* #define NTOH_64(x) (ntohll(x)) */
      /* #define HTON_64(x) (htonll(x)) */
    #else
      #error No platform defined.
    #endif
  #endif
#endif /* PLATFORM_BYTE_ORDER_H */
