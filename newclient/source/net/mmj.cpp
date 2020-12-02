#include "mmj.hpp"

MMJ::MMJ(const std::string & ip, int port, int num)
	:m_ip(ip)
	, m_port(port)
	, m_socketnum(num)
{
}

TcpClient * MMJ::getclient()
{
	return nullptr;
}
