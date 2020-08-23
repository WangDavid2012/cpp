#include "TcpClient.hpp"
#include "Socket.hpp"
#include "InetAddress.hpp"
#include "debug.h"
#include <time.h>




static SOCKET createSocketFd()
{
	SOCKET fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//if (fd == -1) {
	//	exit(EXIT_FAILURE);
	//}
	//mydebug << "the  m_socket is :" << fd << endl;
	return fd;
}


TcpClient::TcpClient(const string & ip, unsigned short port)
	: m_connected_flag(false)
	, m_used_flag(false)
	, m_addr(ip, port)
	, m_socket(createSocketFd())
	, m_socket_io(m_socket.fd())
	, m_sockfd(m_socket.fd())
{
	m_socket.setSocketTimeout(20);
	start();
}


void TcpClient::start()
{

	const struct sockaddr_in * servaddr = m_addr.getSockAddrInet();
	int ret = connect(m_sockfd, (struct sockaddr *)servaddr, sizeof(sockaddr));
	if (ret < 0) {
		mydebug << "connect error" << endl;
	}
	if (ret == 0) {
		m_connected_flag = true;
	}
	else {
		mydebug << "connect error" << endl;
	}
}

bool TcpClient::isBusy()
{
	return m_used_flag;
}
void TcpClient::setStatus(bool status)
{
	this->m_used_flag = status;
}
bool TcpClient::isConnected()
{
	return m_connected_flag;
}



SOCKET TcpClient::getfd()
{
	return m_sockfd;
}
int TcpClient::Write(const char *buf, int count)
{
	mydebug << "*****************wirten ************" << endl;

	return m_socket_io.writen(buf, count);


}
int TcpClient::Read(char *buf, int lenth)
{

	mydebug << "*****************read ************" << endl;
	return m_socket_io.readn(buf, lenth);


}