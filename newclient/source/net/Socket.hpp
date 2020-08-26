#ifndef _SOCKET_H__
#define _SOCKET_H__


#include "InetAddress.hpp"
#include "config.h"
#include <time.h>            




typedef struct sockaddr SA;

class Socket
{
public:
	explicit Socket(SOCKET sockfd);
	~Socket();
	SOCKET fd()const;
	void bindAddress(const InetAddress &addr);
	void listen();
	SOCKET accept();

	void shutdownWrite();
	void setTcpNoDelay(bool on);
	void setReusePort(bool on);
	void setReuseAddr(bool on);
	void setKeepAlive(bool on);
	int setSocketTimeout(int timeout);
	static InetAddress getLocalAddr(SOCKET sockfd);
	static InetAddress getPeerAddr(SOCKET sockfd);
private:
	const SOCKET _sockfd;

};
#endif
