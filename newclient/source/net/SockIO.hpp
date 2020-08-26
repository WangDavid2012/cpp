#ifndef __crypto_SOCKETIO_H__
#define __crypto_SOCKETIO_H__

#include "config.h"

//实现网络读写功能
//class SocketIO : Noncopyable
class SocketIO
{
public:
	explicit SocketIO(SOCKET sockfd);

	ssize_t readn(char *buf, size_t count);
	ssize_t writen(const char *buf, size_t count);
	ssize_t readline(char *usrbuf, size_t maxlen);
	ssize_t socketRec(char *ptr, size_t nbytes);

private:
	ssize_t recv_peek(char *buf, size_t len);
	const SOCKET _sockfd;
};
#endif

