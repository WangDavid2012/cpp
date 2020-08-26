#include "Socket.hpp"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>






#ifdef _UNIX
int closesocket(int fd)
{
	return close(fd);
}
#endif

Socket::Socket(SOCKET sockfd)
	:_sockfd(sockfd) {

}

Socket::~Socket() {
	::closesocket(_sockfd);
	mydebug << "close socket:" << _sockfd << endl;
}


void Socket::bindAddress(const InetAddress &addr)
{
	if (::bind(_sockfd, (SA*)addr.getSockAddrInet(), sizeof(addr)) == -1) {
		debug_printf("stderr bind address error!");
		exit(EXIT_FAILURE);
	}
}

SOCKET Socket::accept()
{
	SOCKET fd = ::accept(_sockfd, NULL, NULL);
	//if (fd == -1) {
	//	debug_printf("stderr accept error!");
	//	exit(EXIT_FAILURE);
	//}
	return fd;
}

void Socket::shutdownWrite()
{
#ifdef _WIN32
	if (::shutdown(_sockfd, SD_SEND) == -1) {
		debug_printf("stderr shutdown error!");
		closesocket(_sockfd);
	}
#else
	if (::shutdown(_sockfd, SHUT_WR) == -1) {
		debug_printf("stderr shutdown error!");
		closesocket(_sockfd);
	}
#endif
}

void Socket::setTcpNoDelay(bool on)
{
	int optval = on ? 1 : 0;
	if (::setsockopt(_sockfd,
		IPPROTO_TCP,
		TCP_NODELAY,
		(const char *)&optval,
		static_cast<socklen_t>(sizeof optval)) == -1) {
		debug_printf("stderr setTcpNoDelay error!");
		exit(EXIT_FAILURE);
	}

}

void Socket::setReuseAddr(bool on)
{
	int optval = on ? 1 : 0;
	if (::setsockopt(_sockfd,
		SOL_SOCKET,
		SO_REUSEADDR,
		(const char *)&optval,
		static_cast<socklen_t>(sizeof optval)) == -1) {
		debug_printf("stderr setTcpNoDelay error!");
		exit(EXIT_FAILURE);
	}
}

int Socket::setSocketTimeout(int TimeOut)
{
	struct  linger    xxlinger;
	xxlinger.l_onoff = 2;
	xxlinger.l_linger = 0;
	::setsockopt(_sockfd, SOL_SOCKET, SO_LINGER, (const char *)&xxlinger, sizeof(xxlinger));

#ifdef _UNIX
	struct  timeval timeout;
	timeout.tv_sec = TimeOut;
	timeout.tv_usec = 0;
	::setsockopt(_sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char  *)&timeout, sizeof(timeout));
	::setsockopt(_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char  *)&timeout, sizeof(timeout));
#else
	DWORD outTime = TimeOut * 1000;
	::setsockopt(_sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char  *)&outTime, sizeof(outTime));
	::setsockopt(_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char  *)&outTime, sizeof(outTime));
#endif
	return 0;


}







void Socket::setReusePort(bool on)
{
#ifdef SO_REUSEPORT
	int optval = on ? 1 : 0;
	int ret = ::setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&optval,
		static_cast<socklen_t>(sizeof optval));
	if (ret < 0) {
		debug_printf("stderr setTcpNoDelay error!");
		//exit(EXIT_FAILURE);
	}
#else
	if (on)
		debug_printf("stderr SO_REUSEPORT is not supported!");
#endif
}

void Socket::setKeepAlive(bool on)
{
	int optval = on ? 1 : 0;
	if (::setsockopt(_sockfd,
		SOL_SOCKET,
		SO_KEEPALIVE,
		(const char *)&optval,
		static_cast<socklen_t>(sizeof optval)) == -1) {
		debug_printf("stderr setTcpNoDelay error!");
		//exit(EXIT_FAILURE);
	}
}

InetAddress Socket::getLocalAddr(SOCKET sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof addr;
	if (::getsockname(sockfd, (SA*)&addr, &len) == -1) {
		debug_printf("stderr getLocalAddress!");
		exit(EXIT_FAILURE);
	}
	return InetAddress(addr);
}

InetAddress Socket::getPeerAddr(SOCKET sockfd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof addr;
	if (::getpeername(sockfd, (SA*)&addr, &len) == -1) {
		debug_printf("stderr getPeerAddress!");
		exit(EXIT_FAILURE);
	}

	return InetAddress(addr);
}

void Socket::listen()
{
	if (::listen(_sockfd, 5) == -1) {
		debug_printf("stderr listen address error!");
		exit(EXIT_FAILURE);
	}
}

SOCKET Socket::fd() const
{
	return _sockfd;
}