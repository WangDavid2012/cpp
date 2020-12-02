#include "mmj_client.h"
#include "Tcpclient.hpp"

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
using std::unique_lock;


#define SOCKNUM 8

//单例模式的初始化
#ifdef _WIN32
string path("D:\\config\\mmj.conf");
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
MmjClient::MmjClient(const std::string &cfgFileName)
{



    for (int i = 0; i < MAX_MMJ_NUM; i++) {
        m_MmjConf.mmj[i].tail = -1;
        m_MmjConf.mmj[i].front = 0;
    }

    std::map<std::string, std::string> mmjConfMap;
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
    for (; it != mmjConfMap.end(); it++) {
        std::cout << it->first << " " << it->second << endl;
    }
    std::cout << endl;
#endif

    //获取管理的服务器密码机的数量
    std::map<string, string>::iterator iter = mmjConfMap.find("mmjnum");
    if (iter != mmjConfMap.end()) {
        std::string tmp = iter->second;
        m_MmjConf.mmjNum = atoi(tmp.c_str());
    } else {
        return;
    }
    //获取工作模式

    iter = mmjConfMap.find("mode");
    if (iter != mmjConfMap.end()) {
        std::string tmp = iter->second;
        m_MmjConf.mode = atoi(tmp.c_str());
    } else {
        return;
    }




    mydebug << "************ init m_MmjConf.mmjNum **********" << std::endl;
    for (int i = 0; i < m_MmjConf.mmjNum; i++) {
        std::string ip = "ip" + std::to_string(i);
        std::string port = "port" + std::to_string(i);
        std::string socketnum = "socketnum" + std::to_string(i);

        mydebug << ip << " " << port << " " << socketnum << std::endl;

        //读取IP地址
        iter = mmjConfMap.find(ip);
        if (iter != mmjConfMap.end()) {
            std::string tmp = iter->second;
            //m_MmjConf.serConf[i].ip = tmp;
            m_MmjConf.mmj[i].ip = tmp;
        } else {
            return;
        }

        //读取端口地址
        iter = mmjConfMap.find(port);
        if (iter != mmjConfMap.end()) {
            std::string tmp = iter->second;
            //m_MmjConf.serConf[i].port = atoi(tmp.c_str());
            m_MmjConf.mmj[i].port = atoi(tmp.c_str());
        } else {
            return;
        }

        //读取socketnum地址
        iter = mmjConfMap.find(socketnum);
        if (iter != mmjConfMap.end()) {
            std::string tmp = iter->second;
            //m_MmjConf.serConf[i].socketnum = atoi(tmp.c_str());
            m_MmjConf.mmj[i].socketnum = atoi(tmp.c_str());
        } else {
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

TcpClient *MmjClient::createClientConnect()
{
    static int num = 0;
    bool serverFailFlag = false;

    std::lock_guard<std::mutex> lg(m_connectMutex);

    mydebug << "the ip is " << m_MmjConf.mmj[0].ip << " the Port is " << m_MmjConf.mmj[0].port << endl;
    mydebug << "the socknum is " << m_MmjConf.mmj[0].socketnum << endl;
    //双机热备模式
    if (m_MmjConf.mode == 0) {
        mydebug << "双机热备模式" << std::endl;
        for (int i = 0; i < m_MmjConf.mmj[0].socketnum; i++) {
            TcpClient *ptmp = new TcpClient(m_MmjConf.mmj[0].ip, m_MmjConf.mmj[0].port);
            if (ptmp == nullptr) {
                serverFailFlag = true;
                break;
            } else {
                mydebug << "ip" << m_MmjConf.serConf[0].ip << " Creat socket fd " << ptmp->getfd() << std::endl;
                m_MmjConf.mmj[0].arra_mmj.push_back(ptmp);
                //m_MmjConf.mmj[0].tail = (m_MmjConf.mmj[0].tail + 1) % (m_MmjConf.mmj[0].socketnum);
            }
        }
        //启用备用机
        if (serverFailFlag) {
            for (int i = 0; i < m_MmjConf.mmj[1].socketnum; i++) {
                TcpClient *ptmp = new TcpClient(m_MmjConf.mmj[1].ip, m_MmjConf.mmj[1].port);
                if (ptmp == nullptr) {
                    return nullptr;
                } else {
                    m_MmjConf.mmj[1].arra_mmj.push_back(ptmp);
                }
            }
            return m_MmjConf.mmj[1].arra_mmj[0];

        } else {
            return  m_MmjConf.mmj[0].arra_mmj[0];
        }




    } else if (m_MmjConf.mode == 1) {
        mydebug << "负载均衡模式" << std::endl;
        //负载均衡模式
        num++;
        for (int i = 0; i < m_MmjConf.mmj[num % m_MmjConf.mmjNum].socketnum; i++) {
            TcpClient *ptmp = new TcpClient(m_MmjConf.mmj[num % m_MmjConf.mmjNum].ip, m_MmjConf.mmj[num % m_MmjConf.mmjNum].port);
            if (ptmp == nullptr) {
                mydebug << m_MmjConf.mmj[num % m_MmjConf.mmjNum].ip << " can't connect!" << endl;
                //连接失败，连接下一个
                num++;
            } else {
                m_MmjConf.mmj[num % m_MmjConf.mmjNum].arra_mmj.push_back(ptmp);
            }
        }
        if (num == m_MmjConf.mmjNum) {
            return	nullptr;
        } else {
            return 	m_MmjConf.mmj[num % m_MmjConf.mmjNum].arra_mmj[0];
        }

    } else {
        mydebug << "Error" << std::endl;
        return nullptr;
    }
}




MmjClient *MmjClient::getInstance()
{
    return pMmjClient;
}

//测试中，使用条件变量的方式不是很稳定
// TcpClient *MmjClient::getConnectionClient(std::string ip)
// {
//
//     int index = 0;
// 	{
// 		std::lock_guard<std::mutex> lock1(m_socketMutex);
// 		for (index = 0; index < m_MmjConf.mmjNum; index++) {
// 			if (m_MmjConf.mmj[index].ip == ip)
// 				break;
// 		}
// 		if (index == m_MmjConf.mmjNum) {
// 			std::cout << "The ip address error!" << std::endl;
// 			return nullptr;
// 		}
// 	}
//
//
//     //  如果使用条件变量的方式，注意第一行的互斥锁需要去掉
// 	while (m_MmjConf.mmj[index].front == m_MmjConf.mmj[index].tail) {
// 		std::cout << "********************wait start ****************" << endl;
// 		m_MmjConf.mmj[index].mmj_condition_variable.wait(unique_lock<mutex>(m_MmjConf.mmj[index].mmj_mutex), \
// 			[&]() {return (m_MmjConf.mmj[index].front != m_MmjConf.mmj[index].tail); });
// 		std::cout << "********************wait end ****************" << endl;
// 	}
//
//     if (m_MmjConf.mmj[index].front == m_MmjConf.mmj[index].tail) {
//         return nullptr;
//     }
// 	std::lock_guard<std::mutex> lock(m_socketMutex);
//     int loc = m_MmjConf.mmj[index].front;
//     m_MmjConf.mmj[index].front =  (m_MmjConf.mmj[index].front + 1) % m_MmjConf.mmj[index].socketnum;
//     return m_MmjConf.mmj[index].arra_mmj[loc];
//
// }
//
// int  MmjClient::putConnectionClient(std::string ip, TcpClient *socketclient)
// {
//
//     std::lock_guard<std::mutex> lock(m_socketMutex);
//     int index = 0;
//     for (index = 0; index < m_MmjConf.mmjNum; index++) {
//         if (m_MmjConf.mmj[index].ip == ip)
//             break;
//     }
//     if (index == m_MmjConf.mmjNum)
//         return -1;
//     m_MmjConf.mmj[index].tail =  (m_MmjConf.mmj[index].tail + 1) % m_MmjConf.mmj[index].socketnum;
// // 	printf("the front = %d, the tail = %d \n",m_MmjConf.mmj[index].front,m_MmjConf.mmj[index].tail);
//     m_MmjConf.mmj[index].mmj_condition_variable.notify_one();
//     return 0;
// }



TcpClient *MmjClient::getConnectionClient(std::string ip)
{

    std::lock_guard<std::mutex> lock(m_socketMutex);
    int index = 0;
    for (index = 0; index < m_MmjConf.mmjNum; index++) {
        if (m_MmjConf.mmj[index].ip == ip)
            break;
    }
    if (index == m_MmjConf.mmjNum) {
        std::cout << "The ip address error!" << std::endl;
        return nullptr;
    }
    std::vector<TcpClient *>::iterator it = m_MmjConf.mmj[index].arra_mmj.begin();

    for (; it != m_MmjConf.mmj[index].arra_mmj.end(); it++) {
        if (!(*it)->isBusy()) {
            (*it)->setStatus(true);
            break;
        }
    }

    if (it != m_MmjConf.mmj[index].arra_mmj.end()) {
        return *it;
    }else {
        mydebug << "error status" << endl;
        return nullptr;
    }
}

int  MmjClient::putConnectionClient(TcpClient *socketclient)
{
    std::lock_guard<std::mutex> lock(m_socketMutex);
    socketclient->setStatus(false);
    return 0;
}





