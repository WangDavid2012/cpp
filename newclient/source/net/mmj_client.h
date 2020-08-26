#pragma once


#include "tcpclient.hpp"
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



typedef struct _ServerConf {
	std::string ip;
	int port;
	int timeoutvalue;
}ServerConf;

typedef struct _MmjClientConf {
	int mode;
	int mmjNum;
	ServerConf serConf[32];
}MmjConf;


/*********************************************************************
OpenDevice的时候，api接口与网络接口产生关联，
根据不同的模式（双机热备模式和负载均衡模式），创建socket，然后将devicehandle值
存放到一个链表中
closeDevie 的时候，关闭socket连接
每次发送数据的时候，会根据session选择一个device，device中有socketfd
********************************************************************/

class MmjClient
{
private:
	MmjClient(const std::string &cfgFileName);   
public:
	int getMmjWorkMode();
	int getManageMmjNum();
	TcpClient* createClientConnect();
	static MmjClient *getInstance();

	TcpClient* getConnectionClient(std::string ip);
private:
	static MmjClient *pMmjClient;
	MmjConf m_MmjConf;

	std::map<std::string, std::vector<TcpClient*> > m_AllIpClient;
	std::mutex m_connectMutex;
	std::mutex m_socketMutex;
	
	 
};

