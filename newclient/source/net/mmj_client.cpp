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

//单例模式的初始化
#ifdef _WIN32
string path("D:\\logSDF\\mmj.conf");
#else
string path("/etc/config/mmj.conf");
#endif
MmjClient *MmjClient::pMmjClient = new MmjClient(path);


/****************************************************************
 * \brief 需要进行的操作
 *			1、读取mmj的配置文件，然后根据配置文件创建socket连接，默认每个IP创建32个socket连接
 *			2、
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

	std::ifstream _in(cfgFileName);  //定义一个输入文件流  ifstream
	if (!_in.good()) {
		_in.close();
		mydebug << "open mmj config file failed,exit!" << endl;
		return;
	}

	std::string line;
	while (getline(_in, line)) {   //读取_in 文件的每一行数据，放入字符line中
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

	//获取管理的服务器密码机的数量
	std::map<string,string>::iterator iter = mmjConfMap.find("mmjnum");
	if (iter != mmjConfMap.end()) {
		std::string tmp = iter->second;
		m_MmjConf.mmjNum = atoi(tmp.c_str());
	}
	else {
		return;
	}
	//获取工作模式
	
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
 * \brief 获取工作模式：0 对应双机热备模式 1 对应负载均衡模式
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
 * \brief 获取客户端连接的服务器密码机数量
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
	//lock_guard 作用域内不可以拷贝构造？
	std::lock_guard<std::mutex> lg(m_connectMutex);
	
	//双机热备模式
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
		//启用备用机
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
		//负载均衡模式
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


