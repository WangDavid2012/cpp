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

//����ģʽ�ĳ�ʼ��
#ifdef _WIN32
string path("D:\\config\\mmj.conf");
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
MmjClient::MmjClient(const std::string &cfgFileName)
{



    for (int i = 0; i < MAX_MMJ_NUM; i++) {
        m_MmjConf.mmj[i].tail = -1;
        m_MmjConf.mmj[i].front = 0;
    }

    std::map<std::string, std::string> mmjConfMap;
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
    for (; it != mmjConfMap.end(); it++) {
        std::cout << it->first << " " << it->second << endl;
    }
    std::cout << endl;
#endif

    //��ȡ����ķ����������������
    std::map<string, string>::iterator iter = mmjConfMap.find("mmjnum");
    if (iter != mmjConfMap.end()) {
        std::string tmp = iter->second;
        m_MmjConf.mmjNum = atoi(tmp.c_str());
    } else {
        return;
    }
    //��ȡ����ģʽ

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

        //��ȡIP��ַ
        iter = mmjConfMap.find(ip);
        if (iter != mmjConfMap.end()) {
            std::string tmp = iter->second;
            //m_MmjConf.serConf[i].ip = tmp;
            m_MmjConf.mmj[i].ip = tmp;
        } else {
            return;
        }

        //��ȡ�˿ڵ�ַ
        iter = mmjConfMap.find(port);
        if (iter != mmjConfMap.end()) {
            std::string tmp = iter->second;
            //m_MmjConf.serConf[i].port = atoi(tmp.c_str());
            m_MmjConf.mmj[i].port = atoi(tmp.c_str());
        } else {
            return;
        }

        //��ȡsocketnum��ַ
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

TcpClient *MmjClient::createClientConnect()
{
    static int num = 0;
    bool serverFailFlag = false;

    std::lock_guard<std::mutex> lg(m_connectMutex);

    mydebug << "the ip is " << m_MmjConf.mmj[0].ip << " the Port is " << m_MmjConf.mmj[0].port << endl;
    mydebug << "the socknum is " << m_MmjConf.mmj[0].socketnum << endl;
    //˫���ȱ�ģʽ
    if (m_MmjConf.mode == 0) {
        mydebug << "˫���ȱ�ģʽ" << std::endl;
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
        //���ñ��û�
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
        mydebug << "���ؾ���ģʽ" << std::endl;
        //���ؾ���ģʽ
        num++;
        for (int i = 0; i < m_MmjConf.mmj[num % m_MmjConf.mmjNum].socketnum; i++) {
            TcpClient *ptmp = new TcpClient(m_MmjConf.mmj[num % m_MmjConf.mmjNum].ip, m_MmjConf.mmj[num % m_MmjConf.mmjNum].port);
            if (ptmp == nullptr) {
                mydebug << m_MmjConf.mmj[num % m_MmjConf.mmjNum].ip << " can't connect!" << endl;
                //����ʧ�ܣ�������һ��
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

//�����У�ʹ�����������ķ�ʽ���Ǻ��ȶ�
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
//     //  ���ʹ�����������ķ�ʽ��ע���һ�еĻ�������Ҫȥ��
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





