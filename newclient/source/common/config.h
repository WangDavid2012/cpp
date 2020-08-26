#ifndef _CONFIG_H_
#define _CONFIG_H_





#ifdef _WIN32

#include <io.h>
#include <direct.h>
#include <limits.h>
#include <process.h>
#include <winsock2.h>
#include <Ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

typedef  unsigned int ssize_t;
typedef int socklen_t;


#else
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <netdb.h>

typedef int SOCKET;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
#define SOCKET_ERROR (-1)

#endif






#endif

