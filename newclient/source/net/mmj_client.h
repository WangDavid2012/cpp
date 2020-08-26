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
OpenDevice��ʱ��api�ӿ�������ӿڲ���������
���ݲ�ͬ��ģʽ��˫���ȱ�ģʽ�͸��ؾ���ģʽ��������socket��Ȼ��devicehandleֵ
��ŵ�һ��������
closeDevie ��ʱ�򣬹ر�socket����
ÿ�η������ݵ�ʱ�򣬻����sessionѡ��һ��device��device����socketfd
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

