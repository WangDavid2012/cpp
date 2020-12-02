#pragma once


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


#define MAX_MMJ_NUM 32



typedef struct _ServerConf {
	std::string ip;
	int port;
	int timeoutvalue;
}ServerConf;


typedef struct _Server_MMJ {
	std::string ip;
	int port;
	int socketnum;
	int timeoutvalue;
	int front;
	int tail;
	std::vector<TcpClient*> arra_mmj;
	std::condition_variable mmj_condition_variable;
	std::condition_variable not_full;
	std::condition_variable not_empty;
	std::mutex mmj_mutex;
	std::mutex mtx;
}ServerMMJ;



typedef struct _MmjClientConf {
	int mode;
	int mmjNum;
	ServerConf serConf[32];
	ServerMMJ mmj[MAX_MMJ_NUM];
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
	TcpClient * createClientConnect();
	static MmjClient *getInstance();

	TcpClient* getConnectionClient(std::string ip);
	int  putConnectionClient(TcpClient *socketclient);
private:
	static MmjClient *pMmjClient;
	MmjConf m_MmjConf;

	std::map<std::string, std::deque<TcpClient*> > m_AllIpClient;
	std::mutex m_connectMutex;
	std::mutex m_socketMutex;
	std::condition_variable m_condition;
};

