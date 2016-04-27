#ifndef PLATFORM_SOCKET_H
#define PLATFORM_SOCKET_H

#include "os_detect.h"
#include "compiler.h" /* COMPILER_CAST */

#ifdef PLATFORM_LINUX
//#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <linux/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

typedef int socket_t;

/* #define SOCKET_CREATE(af, type, prot) socket(af, type, prot) */

#define SOCKET_STATIC_INITITALIZE            /* No need to initialize networking on Linux. */

#define SOCKET_CREATE(af, type, prot)                                   \
    _Pragma("clang diagnostic push")                                    \
    _Pragma("clang diagnostic ignored \"-Wdisabled-macro-expansion\"")  \
    socket(af, type, prot)                                              \
    _Pragma("clang diagnostic pop")
#define SOCKET_CREATE_SUCC(sock_fd)          (sock_fd >= 0)
#define SOCKET_CLOSE(sock_fd)                close(sock_fd)
#define SOCKET_ERRNO                         errno
#define SOCKET_CREATE_NO_ERR

#define SOCKET_SEND(sock_fd,msg,length)      (err = (send(sock_fd, msg, length, 0) == COMPILER_STATIC_CAST(ssize_t, length)) ? 0 : 1);

#else
#ifdef PLATFORM_WINDOWS

#include <windows.h>
#include <Winsock2.h>

typedef int ssize_t; /* Is not defined in unistd.h on windows. */
typedef SOCKET      socket_t;
typedef SOCKADDR_IN sockaddr_in_t;

#define SOCKET_STATIC_INITITALIZE            WSASetup

#define SOCKET_CREATE(af, type, prot)        socket(af, type, prot)
#define SOCKET_CREATE_SUCC(sock_fd)          ((sock_fd) != INVALID_SOCKET)
#define SOCKET_CLOSE(sock_fd)                closesocket(sock_fd)
#define SOCKET_ERRNO                         WSAGetLastError()
#define SOCKET_ERRMSG                        WSAGetLastErrorMessage()

#define SOCKET_SEND(sock_fd,msg,length)

#else
#error No platform defined.
#endif
#endif

#endif /* PLATFORM_SOCKET_H */
