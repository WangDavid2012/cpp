#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "InetAddress.hpp"



static_assert(sizeof(InetAddress) == sizeof(struct sockaddr_in), "InetAddress Error");

InetAddress::InetAddress(unsigned short port)
{
#ifdef _WIN32
	memset(&_addr, 0, sizeof(_addr));
#else
	bzero(&_addr, sizeof(_addr));
#endif
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
#ifdef _UNIX
	//windows 没有此项定义
	_addr.sin_addr.s_addr = INADDR_ANY;
#endif

}

InetAddress::InetAddress(const string &ip, unsigned short port)
{

#ifdef _WIN32
	memset(&_addr, 0, sizeof(_addr));
#else
	bzero(&_addr, sizeof(_addr));
#endif

	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
#ifdef _WIN32
	_addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
#else
	//给 _addr.sin_addr变量赋值
	if (inet_aton(ip.c_str(), &_addr.sin_addr) == 0) { //新方法
		debug_printf("stderr ip invalid!");
		exit(EXIT_FAILURE);
	}
#endif

}
InetAddress::InetAddress(const struct sockaddr_in &addr)
	:_addr(addr)
{
}

string InetAddress::toIp() const
{
	return inet_ntoa(_addr.sin_addr);//字符串

}

unsigned short InetAddress::toPort() const
{
	return ntohs(_addr.sin_port);
}

const struct sockaddr_in * InetAddress::getSockAddrInet()const {
	return &_addr;
}