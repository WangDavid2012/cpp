#ifndef _TCPCLIENT_H__
#define _TCPCLIENT_H__

#include <string>
#include "Socket.hpp"
#include "SockIO.hpp"
#include "InetAddress.hpp"
#include <list>
#include "config.h"

using std::string;
using std::list;

class TcpClient
{
public:
	TcpClient(const string & ip, unsigned short port);
	bool isBusy();                    //判断该客户端是否在使用中
	void setStatus(bool status);      //设置连接使用状态
	bool isConnected();               //判断该客户端是否还在正常连接
	void start();
	int Write(const char *buf, int count);
	int Read(char *buf, int lenth);
	SOCKET getfd();
	std::string gettcpip();

private:
	bool            m_used_flag;
	bool            m_connected_flag;
	InetAddress 	m_addr;
	Socket 			m_socket;
	SocketIO 	    m_socket_io;
	SOCKET          m_sockfd;
	std::string     m_ip;
};

#endif
