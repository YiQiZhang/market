#ifndef _MARKET_TCP_ACCEPTOR_H
#define _MARKET_TCP_ACCEPTOR_H

#include <core.h>

#define LISTENQ 10

namespace market{

using std::map;

class TcpAcceptor{
public:
	TcpAcceptor(const string &host, const string &listenPort) : 
		host(host),
		port(listenPort)
	{
		int fd;
		struct addrinfo *res, *ressave;

		std::memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_flags = AI_PASSIVE;
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		if (getaddrinfo(host.c_str(), listenPort.c_str(), &hints, &res) != 0)
			logger(MERR_FATAL, "tcp_listen server fail");

		ressave = res;

		do {
			fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
			if (fd < 0) {
				logger(MERR_NOTICE, "socket fail");
				continue;
			}

			// TODO: set socket opt
			if (bind(fd, res->ai_addr, res->ai_addrlen) == 0) {
				break; // success
			}

			close(fd);
		} while((res = res->ai_next) != NULL);

		if (res == NULL) {
			logger(MERR_FATAL, "tcp listen error");
		}

		listen(fd, LISTENQ);

		addrlen = res->ai_addrlen;
		listenFd = fd;

		freeaddrinfo(ressave);
	}

	TcpAcceptor(const string &listenPort) : TcpAcceptor(string(), listenPort)
	{
	}

	const string &
	listenHost() const
	{
		return host;
	}

	const string &
	listenPort() const
	{
		return port;
	}

	int
	listenFileDescriptor() const
	{
		return listenFd;
	}

	socklen_t
	addrLength() const
	{
		return addrlen;
	}

	TcpStream
	acceptRequest()
	{
		int fd;
		TcpStream stream;
		if ( (fd = accept(listenFd, (SA *)stream.addrPointer(), stream.addrLengthPointer())) < 0 ) {
			
			logger(MERR_FATAL, "accept fail");
		}

		stream.setFileDescriptor(fd);
		return stream;
	}
private:
	TcpAcceptor();

	string host;

	string port;

	struct addrinfo hints;

	int listenFd;

	socklen_t addrlen;
};
}
#endif
