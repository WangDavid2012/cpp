#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include "config.h"


#include <string>
using std::string;

//主要作用是给网络中使用的IP地址赋值 
//给sockaddr_in这个变量赋值，同时对外提供接口，读取ip，port
class InetAddress {

public:
	explicit InetAddress(unsigned short port);
	explicit InetAddress(const string &ip, unsigned short port);   //使用到了此
	explicit InetAddress(const struct sockaddr_in &addr);
	const struct sockaddr_in *getSockAddrInet() const;
	string toIp()const;
	unsigned short toPort()const;
private:
	struct sockaddr_in _addr;

};
#endif
