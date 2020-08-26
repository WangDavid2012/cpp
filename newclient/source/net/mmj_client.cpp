#include "mmj_client.h"
#include "tcpclient.hpp"

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>      
#include <fstream>
#include <sstream>
#include <vector>
#include "debug.h"

using std::string;
using std::cout;
using std::endl;
using std::list;
using std::mutex;

//����ģʽ�ĳ�ʼ��
#ifdef _WIN32
string path("D:\\logSDF\\mmj.conf");
#else
string path("/etc/config/mmj.conf");
#endif
MmjClient *MmjClient::pMmjClient = new MmjClient(path);


/****************************************************************
 * \brief ��Ҫ���еĲ���
 *			1����ȡmmj�������ļ���Ȼ����������ļ�����socket���ӣ�Ĭ��ÿ��IP����32��socket����
 *			2��
 * \param[in]  
 * \param[out]
 * \return
 *
 * \author wangzhanbei
 * \history
 * \time 2020/08/22
 *****************************************************************/
MmjClient::MmjClient(const std::string & cfgFileName)
{
	std::map<std::string,std::string> mmjConfMap;

	std::ifstream _in(cfgFileName);  //����һ�������ļ���  ifstream
	if (!_in.good()) {
		_in.close();
		mydebug << "open mmj config file failed,exit!" << endl;
		return;
	}

	std::string line;
	while (getline(_in, line)) {   //��ȡ_in �ļ���ÿһ�����ݣ������ַ�line��
		std::istringstream iss(line);
		std::string key;
		std::string value;
		iss >> key >> value;

		mmjConfMap.insert(make_pair(key, value));
	}
	_in.close();
#ifdef _DEBUG
	std::cout << "******* read the mmjConfig Info " << endl;
	auto it = mmjConfMap.begin();
	for (; it != mmjConfMap.end(); it++)
	{
		std::cout << it->first << " " << it->second << endl;
	}
	std::cout << endl;
#endif

	//��ȡ����ķ����������������
	std::map<string,string>::iterator iter = mmjConfMap.find("mmjnum");
	if (iter != mmjConfMap.end()) {
		std::string tmp = iter->second;
		m_MmjConf.mmjNum = atoi(tmp.c_str());
	}
	else {
		return;
	}
	//��ȡ����ģʽ
	
	iter = mmjConfMap.find("mode");
	if (iter != mmjConfMap.end()) {
		std::string tmp = iter->second;
		m_MmjConf.mode = atoi(tmp.c_str());
	}
	else {
		return;
	}
	mydebug << "************ init m_MmjConf.mmjNum **********" << std::endl;
	for (int i = 0; i < m_MmjConf.mmjNum; i++)
	{
		std::string ip = "ip" + std::to_string(i);
		std::string port = "port"+ std::to_string(i);
		mydebug << ip << " " << port << std::endl;

		iter = mmjConfMap.find(ip);
		if (iter != mmjConfMap.end()) {
			std::string tmp = iter->second;
			m_MmjConf.serConf[i].ip = tmp;
		}
		else {
			return;
		}
		iter = mmjConfMap.find(port);
		if (iter != mmjConfMap.end()) {
			std::string tmp = iter->second;
			m_MmjConf.serConf[i].port = atoi(tmp.c_str());
		}
		else {
			return;
		}
	}
	mydebug << " finish init!" << endl;
}
/**********************************************************
 * \brief ��ȡ����ģʽ��0 ��Ӧ˫���ȱ�ģʽ 1 ��Ӧ���ؾ���ģʽ
 *
 * \param[in]  
 * \param[out]
 * \return
 *
 * \author wangzhanbei
 * \history
 * \time 2020/08/22
 ************************************************************/
int MmjClient::getMmjWorkMode()
{
	return m_MmjConf.mode;
}
/**********************************************************
 * \brief ��ȡ�ͻ������ӵķ��������������
 *
 * \param[in]  
 * \param[out]
 * \return
 *
 * \author wangzhanbei
 * \history
 * \time 2020/08/22
 ************************************************************/
int MmjClient::getManageMmjNum()
{
	return m_MmjConf.mmjNum;
}

TcpClient* MmjClient::createClientConnect()
{
	static int num = 0;
	bool serverFailFlag = false;
	std::vector<TcpClient *> clients;
	//lock_guard �������ڲ����Կ������죿
	std::lock_guard<std::mutex> lg(m_connectMutex);
	
	//˫���ȱ�ģʽ
	if (m_MmjConf.mode == 0) {
		for (int i = 0; i < 32; i++){
			TcpClient *ptmp = new TcpClient(m_MmjConf.serConf[0].ip,m_MmjConf.serConf[0].port);
			if (ptmp == nullptr){
				serverFailFlag = true;
				break;
			}else{
				clients.push_back(ptmp);
			}	
		}
		//���ñ��û�
		if (serverFailFlag){
			clients.clear();
			for (int i = 0; i < 32; i++) {
				TcpClient *ptmp = new TcpClient(m_MmjConf.serConf[1].ip, m_MmjConf.serConf[1].port);
				if (ptmp == nullptr) {
					return nullptr;
				}else {
					clients.push_back(ptmp);
				}
			}
			m_AllIpClient.insert(make_pair(m_MmjConf.serConf[1].ip, clients));
		}else {
			m_AllIpClient.insert(make_pair(m_MmjConf.serConf[0].ip, clients));
		}

	}
	else if (m_MmjConf.mode == 1){
		//���ؾ���ģʽ
		num++;
		for (int i = 0; i < 32; i++) {
			TcpClient *ptmp = new TcpClient(m_MmjConf.serConf[num%m_MmjConf.mmjNum].ip, m_MmjConf.serConf[num%m_MmjConf.mmjNum].port);
			if (ptmp == nullptr) {
				mydebug << m_MmjConf.serConf[num%m_MmjConf.mmjNum].ip << " can't connect!" << endl;
				return nullptr;
			}
			else {
				clients.push_back(ptmp);
			}
		}
		m_AllIpClient.insert(make_pair(m_MmjConf.serConf[num%m_MmjConf.mmjNum].ip, clients));
	}else{
		mydebug << "Error" << std::endl;
		return nullptr;
	}
	return clients.front();
}




MmjClient * MmjClient::getInstance()
{
	return pMmjClient;
}

TcpClient * MmjClient::getConnectionClient(std::string ip)
{
	std::lock_guard<std::mutex> lg(m_socketMutex);
	//map<std::string,std::vector<TcpClient*>>::iterator iter =  m_AllIpClient.find(ip);

	auto iter =  m_AllIpClient.find(ip);
	if (iter == m_AllIpClient.end()){
		return nullptr;
	}
	return iter->second.front();

}


