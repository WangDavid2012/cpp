#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>  
#include<string.h>  
#include<errno.h>
#include <signal.h>
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"
#include <event2/event-config.h>
#include <WinSock2.h>


//socket �ķ���˳���





#define IP_ADDRESS ("127.0.0.1")
#define PORT (9951)

void accept_cb(evutil_socket_t fd, short events, void* arg);
void socket_read_cb(evutil_socket_t fd, short events, void *arg);
int tcp_server_init(int port, int listen_num);

int test2(int argc, char** argv)
{
	//�����׽��ֿ�  
	WSADATA wsaData;
	int iRet = 0;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet != 0)
	{
		//cout << "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!" << endl;;
		return -1;
	}
	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		WSACleanup();
		//cout << "WSADATA version is not correct!" << endl;
		return -1;
	}
	int listener = tcp_server_init(PORT, 10);
	if (listener == -1)
	{
		perror(" tcp_server_init error ");
		return -1;
	}
	struct event_base* base = event_base_new();
	//��Ӽ����ͻ������������¼�  
	struct event* ev_listen = event_new(base, listener, EV_READ | EV_PERSIST,
		accept_cb, base);
	event_add(ev_listen, NULL);
	event_base_dispatch(base);
	WSACleanup();
	return 0;
}

void accept_cb(evutil_socket_t fd, short events, void* arg)
{
	evutil_socket_t sockfd;
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	sockfd = ::accept(fd, (struct sockaddr*)&client, &len);
	evutil_make_socket_nonblocking(sockfd);
	printf("accept a client %d\n", sockfd);
	struct event_base* base = (event_base*)arg;
	//������Ϊ�˶�̬����һ��event�ṹ��  
	struct event *ev = event_new(NULL, -1, 0, NULL, NULL);
	//����̬�����Ľṹ����Ϊevent�Ļص�����  
	event_assign(ev, base, sockfd, EV_READ | EV_PERSIST,
		socket_read_cb, (void*)ev);
	event_add(ev, NULL);
}

void socket_read_cb(int fd, short events, void *arg)
{
	char msg[4096];
	struct event *ev = (struct event*)arg;
	int len = recv(fd, msg, sizeof(msg) - 1, 0);
	if (len <= 0)
	{
		printf("some error happen when read\n");
		event_free(ev);
		closesocket(fd);
		return;
	}
	msg[len] = '\0';
	printf("recv the client msg: %s\n", msg);
	char reply_msg[4096] = "I have recvieced the msg: ";
	strcat(reply_msg + strlen(reply_msg), msg);
	int ret = send(fd, reply_msg, strlen(reply_msg), 0);
}

int tcp_server_init(int port, int listen_num)
{
	int errno_save;
	int listener;
	listener = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listener == -1)
		return -1;
	//�����ΰ�ͬһ����ַ��Ҫ����socket��bind֮��  
	evutil_make_listen_socket_reuseable(listener);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(port);
	if (::bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
		errno_save = errno;
		evutil_closesocket(listener);
		errno = errno_save;
		return -1;
	}
	if (::listen(listener, listen_num) < 0) {
		errno_save = errno;
		evutil_closesocket(listener);
		errno = errno_save;
		return -1;
	}
	//��ƽ̨ͳһ�ӿڣ����׽�������Ϊ������״̬  
	evutil_make_socket_nonblocking(listener);
	return listener;
}