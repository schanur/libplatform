#ifndef PLATFORM_BYTE_ORDER_H
  #define PLATFORM_BYTE_ORDER_H

  #ifdef PLATFORM_BYTE_ORDER
    #error Redefinition of PLATFORM_BYTE_ORDER
  #endif

  #define PLATFORM_BIG_ENDIAN    0
  #define PLATFORM_LITTLE_ENDIAN 1

  #include "os_detect.h"

  #include "compiler.h" /* STATIC_CAST */

  #ifdef PLATFORM_LINUX
    #include <endian.h>

    /* #ifndef PLATFORM_BIG_ENDIAN */
    /*   #define PLATFORM_BIG_ENDIAN    0 */
    /* #endif */
    /* #ifndef PLATFORM_LITTLE_ENDIAN */
    /*   #define PLATFORM_LITTLE_ENDIAN 1 */
    /* #endif */

    #if __BYTE_ORDER == __BIG_ENDIAN
      #define PLATFORM_BYTE_ORDER PLATFORM_BIG_ENDIAN
    #else
      #define PLATFORM_BYTE_ORDER PLATFORM_LITTLE_ENDIAN
    #endif
  #else
    /* For the moment we assume Windows is little endian all the
     * time.
     */
    #define PLATFORM_BYTE_ORDER PLATFORM_LITTLE_ENDIAN
  #endif



  #include "os_detect.h"

  #ifdef PLATFORM_LINUX

    #include <netinet/in.h>
    #define   NTOH_16(x) (ntohs(x))
    #define   HTON_16(x) (htons(x))
    #define   NTOH_32(x) (ntohl(x))
    #define   HTON_32(x) (htonl(x))
    #if PLATFORM_BYTE_ORDER == PLATFORM_BIG_ENDIAN
      #define NTOH_64(x) (x)
      #define HTON_64(x) (x)
    #else
      #include <byteswap.h>
      #define NTOH_64(x) (COMPILER_STATIC_CAST(uint64_t, bswap_64(x)))
      #define HTON_64(x) (COMPILER_STATIC_CAST(uint64_t, bswap_64(x)))
    #endif

  #else
    #ifdef PLATFORM_WINDOWS
      #if PLATFORM_BYTE_ORDER != PLATFORM_LITTLE_ENDIAN
        #error Wrong byte order. Makros only work on little endian maschines atm.
      #endif
      #include <winsock2.h>
      #include "inttypes_wrapper.h"

      #define NTOH_16(x) (ntohs (x))
      #define HTON_16(x) (htons (x))
      #define NTOH_32(x) (ntohl (x))
      #define HTON_32(x) (htonl (x))
      #define NTOH_64(x) (((COMPILER_STATIC_CAST(uint64_t, NTOH_32((x) & 0xffffffffUL))) << 32) | NTOH_32(COMPILER_STATIC_CAST(uint32_t, ((x) >> 32))))
      #define HTON_64(x) (((COMPILER_STATIC_CAST(uint64_t, HTON_32((x) & 0xffffffffUL))) << 32) | HTON_32(COMPILER_STATIC_CAST(uint32_t, ((x) >> 32))))
    #else
      #error No platform defined.
    #endif
  #endif
#endif /* PLATFORM_BYTE_ORDER_H */
