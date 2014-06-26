#ifndef PLATFORM_SOCKET_H
#define PLATFORM_SOCKET_H

#include "os_detect.h"

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
#define SOCKET_CREATE(af, type, prot) socket(af, type, prot)
#define SOCKET_CREATE_SUCC(sock_fd)   (sock_fd >= 0)
#define SOCKET_CLOSE(sock_fd)         close(sock_fd)
#define SOCKET_ERRNO                  errno
#define SOCKET_CREATE_NO_ERR

#else
#ifdef PLATFORM_WINDOWS
typedef int ssize_t; /* Is not defined in unistd.h on windows. */
typedef SOCKET socket_t;
#define SOCKET_CREATE(af, type, prot) socket(af, type, prot)
#define SOCKET_CREATE_SUCC(sock_fd)   ((sock_fd) != INVALID_SOCKET)
#define SOCKET_CLOSE(sock_fd)         closesocket(sock_fd)
#define SOCKET_ERRNO                  WSAGetLastError()
#define SOCKET_ERRMSG                 WSAGetLastErrorMessage()

#else
#error No platform defined.
#endif
#endif

#endif /* PLATFORM_SOCKET_H */
