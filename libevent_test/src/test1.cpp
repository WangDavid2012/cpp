#ifndef UNIX
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif 


#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"
#include <event2/event-config.h>
#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <functional>
#include <future>




#define IP_ADDRESS ("172.16.100.112")
#define PORT (9999)

int tcp_connect_server(const char* server_ip, int port);
void cmd_msg_cb(evutil_socket_t fd, char* msg);
void socket_read_cb(evutil_socket_t fd, short events, void *arg);


DWORD WINAPI Fun1Proc(LPVOID lpParameter)
{
	char t_cin[1024];
	int sockfd = (int)lpParameter;
	while (1) {
		memset(t_cin, 0, 1024);
		std::cin >> t_cin;
		if (strcmp(t_cin, "exit") == 0) {
			break;
		}
		cmd_msg_cb(sockfd, t_cin);
	}
	exit(1);
	return 0;
}


/************************************************************************/
/* ʹ�õ���C++11�ṩ���߳̽ӿں���                                                                     */
/************************************************************************/

int client_test()
{
#ifndef UNIX
	WSADATA wsaData;
	int iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet != 0)
	{
		return -1;
	}
	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		WSACleanup();
		return -1;
	}
#endif
	//�������������Ƿ������˵�IP��ַ���˿ں�  
	int sockfd = tcp_connect_server(IP_ADDRESS, PORT);
	if (sockfd == -1)
	{
		perror("tcp_connect error ");
		return -1;
	}
	printf("connect to server successful\n");
	struct event_base* base = event_base_new();
	struct event *ev_sockfd = event_new(base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, NULL);
	event_add(ev_sockfd, NULL);

	std::thread thread_connect(Fun1Proc, (void*)sockfd);
	thread_connect.detach();
	event_base_dispatch(base);

#ifndef UNIX
	WSACleanup();
#endif

	printf("finished \n");
	return 0;
}

/***************************************************************
	ʹ�õ���windows�ṩ���߳̽ӿں���
***************************************************************/
int test1()
{
	//�����׽��ֿ�  
	WSADATA wsaData;
	int iRet = 0;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet != 0)
	{
		return -1;
	}

	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		WSACleanup();
		return -1;
	}
	//�������������Ƿ������˵�IP��ַ���˿ں�  
	int sockfd = tcp_connect_server(IP_ADDRESS, PORT);
	if (sockfd == -1)
	{
		perror("tcp_connect error ");
		return -1;
	}
	printf("connect to server successful\n");
	struct event_base* base = event_base_new();
	struct event *ev_sockfd = event_new(base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, NULL);
	event_add(ev_sockfd, NULL);
	//�����̷߳�������
	HANDLE hThread1 = CreateThread(NULL, 0, Fun1Proc, (void*)sockfd, 0, NULL);
	CloseHandle(hThread1);

	event_base_dispatch(base);
	WSACleanup();
	printf("finished \n");
	return 0;
}




void cmd_msg_cb(evutil_socket_t fd, char* msg)
{
	//���ն˵���Ϣ���͸���������  
	int ret = send(fd, (const char*)msg, strlen((char*)msg), 0);
	if (ret <= 0)
	{
		return;
	}
	printf("send:%s\n", (char*)msg);
}
void socket_read_cb(evutil_socket_t fd, short events, void *arg)
{
	char msg[1024];
	//Ϊ�˼�����������Ƕ�һ�����ݵ����  
	int len = recv(fd, msg, sizeof(msg) - 1, 0);
	if (len <= 0)
	{
		perror("read fail ");
		exit(1);
	}
	msg[len] = '\0';
	printf("recv %s from server\n", msg);
}

void socket_bufferevent_read_cb(struct bufferevent *bev, void *args)
{
	char msg[1024];
	//Ϊ�˼�����������Ƕ�һ�����ݵ����  
	int n = 0;
	evutil_socket_t fd = bufferevent_getfd(bev);
	while ((n = bufferevent_read(bev, msg, 1024)) > 10)
	{
		msg[n] = '\0';
		std::cout << "fd = " << fd;
		std::cout << "\tread from server:" << msg << std::endl;
	}


	//int len = recv(fd, msg, sizeof(msg) - 1, 0);
	//if (len <= 0)
	//{
	//	perror("read fail ");
	//	exit(1);
	//}
	//msg[len] = '\0';
	//printf("recv %s from server\n", msg);
}



int tcp_connect_server(const char* server_ip, int port)
{
	int sockfd, status, save_errno;
	SOCKADDR_IN  server_addr;

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(server_ip);
	server_addr.sin_port = htons(port);

	sockfd = ::socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd == -1)
		return sockfd;


	status = ::connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (status == -1)
	{
		save_errno = errno;   //����  
		closesocket(sockfd);
		errno = save_errno;   //the close may be error  
		return -1;
	}

	evutil_make_socket_nonblocking(sockfd);
	return sockfd;
}
void SendData_task_cb(struct bufferevent *bev, void *data)
{
	bufferevent_write(bev, data, 20);
	return;
}


int ClientInit()
{
#ifndef UNIX
	WSADATA wsaData;
	int iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet != 0)
	{
		return -1;
	}
	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		WSACleanup();
		return -1;
	}
#endif
	//�������������Ƿ������˵�IP��ַ���˿ں�  
	int sockfd = tcp_connect_server(IP_ADDRESS, PORT);
	if (sockfd == -1)
	{
		perror("tcp_connect error ");
		return -1;
	}
	printf("connect to server successful\n");
	struct event_base* base = event_base_new();

	struct bufferevent *bev = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, socket_bufferevent_read_cb, NULL, NULL, NULL);
	bufferevent_enable(bev, EV_READ | EV_PERSIST);

	//std::thread thread_connect(Fun1Proc, (void*)sockfd);

	unsigned char data[20] = "wangzhanbei";
	std::thread thread_connect(SendData_task_cb, bev, (void*)data);
	thread_connect.detach();

	event_base_dispatch(base);

#ifndef UNIX
	WSACleanup();
#endif

	printf("finished \n");
	return 0;
}


//���һ�����ݷ��͸�ʽ
typedef struct FrameData
{
	//���Խṹ��
	//	��ʱʱ��
	//	socket_fd
	//����  ����/����
	unsigned int lenth;
	unsigned char data[1024];
}FrameData;


/****************************************************
�ͻ��˷�������ģʽ��ƣ�
	1���ͻ��˷�������ʱ�����÷��ͺ�����������ɺ�
	2��ͬʱ����һ�����̣��ȴ�Ӧ��
	����/���������������̣����̼�ͬ����ƣ���������ʹ�ã�
********************************************/