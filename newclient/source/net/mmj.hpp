#include "Tcpclient.hpp"
#include <list>
#include <mutex>
#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
#include <string>
#include <mutex>
#include <map>
#include <vector>
#include <queue>
#include <condition_variable>



class MMJ {
public:
	MMJ(const std::string &ip,int port,int num);
	TcpClient *getclient();


private:
	std::string m_ip;
	int m_port;
	int m_socketnum;
	int timeoutvalue;
	std::vector<TcpClient*> arra_mmj;
	std::condition_variable mmj_condition_variable;
	std::mutex mmj_mutex;




};