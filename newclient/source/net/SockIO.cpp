#include "debug.h"
#include "config.h"
#include "SockIO.hpp"
#include <time.h>

#pragma warning(disable:4996)

#define MY_GET_ULONG_BE(n,b,i)                             \
{                                                       \
    (n) = ( (unsigned long) (b)[(i)    ] << 24 )        \
        | ( (unsigned long) (b)[(i) + 1] << 16 )        \
        | ( (unsigned long) (b)[(i) + 2] <<  8 )        \
        | ( (unsigned long) (b)[(i) + 3]       );       \
}


SocketIO::SocketIO(SOCKET sockfd) : _sockfd(sockfd)
{

}








ssize_t SocketIO::readn(char *buf, size_t n)
{

	size_t  nleft;
	ssize_t nread;
	char   *ptr;

	ptr = buf;
	nleft = n;
	while (nleft > 0) {


#ifdef _WIN32
		nread = ::recv(_sockfd, ptr, nleft, 0);
#else
		nread = read(_sockfd, ptr, nleft);
#endif
		if (nread < 0) {
			if (errno == EINTR)
				nread = 0;
			else
				return -1;
		}
		else if (nread == 0)
			break;

		nleft -= nread;
		ptr += nread;
	}
	return n - nleft;
}

ssize_t SocketIO::writen(const char *buf, size_t n)
{

	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	mydebug << "****the write socket is :" << _sockfd << endl;
	ptr = buf;
	nleft = n;
	while (nleft > 0) {
#ifdef _WIN32
		nwritten = ::send(_sockfd, ptr, nleft, 0);
#else
		nwritten = write(_sockfd, ptr, nleft);
#endif

		if (nwritten <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}

		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;

}



ssize_t SocketIO::recv_peek(char *buf, size_t len)
{
	int nread;
	do {
		nread = ::recv(_sockfd, buf, len, MSG_PEEK);
	} while (nread == -1 && errno == EINTR);

	return nread;
}

ssize_t SocketIO::readline(char *usrbuf, size_t maxlen)
{
	size_t nleft = maxlen - 1;
	char *bufp = usrbuf;
	size_t total = 0;
	ssize_t nread;
	while (nleft > 0) {

		nread = recv_peek(bufp, nleft);
		if (nread <= 0)
			return nread;


		unsigned int i;
		for (i = 0; i < nread; ++i) {
			if (bufp[i] == '\n') {

				size_t nsize = i + 1;
				if (readn(bufp, nsize) != static_cast<ssize_t>(nsize))
					return -1;
				bufp += nsize;
				total += nsize;
				*bufp = 0;
				return total;
			}
		}

		if (readn(bufp, nread) != nread)
			return -1;
		bufp += nread;
		total += nread;
		nleft -= nread;
	}
	*bufp = 0;
	return maxlen - 1;
}









ssize_t SocketIO::socketRec(char *buff, size_t len)
{
	int  nError, readlen, rsocket;
	int  trycount = 3;
	struct timeval timeout;
	fd_set fds;

	struct  linger xxlinger;
	xxlinger.l_onoff = 1;
	xxlinger.l_linger = 0;
	unsigned int index = 0;

	mydebug << "******socketfd :" << _sockfd << endl;

	while (len > 0) {

		while (1) {

			FD_ZERO(&fds);
			FD_SET((unsigned int)_sockfd, &fds);
			timeout.tv_sec = 20;
			timeout.tv_usec = 0;
			nError = select(_sockfd + 1, &fds, NULL, NULL, &timeout);
			if (nError > 0) {
				if (FD_ISSET(_sockfd, &fds)) {
					readlen = recv(_sockfd, buff, len, 0);
					if (readlen > 0) {
						len -= readlen;
						if (len < 0) {
						}
						if (len) {
							index += readlen;
						}
						else {
							break;
						}
					}
					else {
						if (trycount) {
							trycount--;
							continue;
						}
						else {
							debug_printf("SDR_SOCKET_SOCKREADTIMEOUT 2\n");
							return  -1;
						}
					}
				}
			}
		}// while (1)
	}
	if (len) {
		return -1;
	}
	return 0;
}



