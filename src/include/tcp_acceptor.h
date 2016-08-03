#ifndef _MARKET_TCP_ACCEPTOR_H
#define _MARKET_TCP_ACCEPTOR_H

#include <core.h>

#define LISTENQ 10

namespace Market{

class TcpAcceptor{
public:
	TcpAcceptor(const std::string &host, const std::string &listenPort) : 
		host(host),
		port(listenPort)
	{
		int fd;
		struct addrinfo *res, *ressave;

		std::memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_flags = AI_PASSIVE;
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		const char *hostPtr = host.empty() ? NULL : host.c_str();
		int code;
		if ( (code = getaddrinfo(hostPtr, listenPort.c_str(), &hints, &res)) != 0) {

			logger(MERR_FATAL, gai_strerror(code));
		}

		ressave = res;

		do {
			fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
			if (fd < 0) {
				logger(MERR_NOTICE, "socket fail");
				continue;
			}

			setSocketOptions(fd);
			if (bind(fd, res->ai_addr, res->ai_addrlen) == 0) {
				break; // success
			} else {
				logger(MERR_NOTICE, std::string("bind fail: ") + strerror(errno));
			}

			close(fd);
		} while((res = res->ai_next) != NULL);

		if (res == NULL) {
			logger(MERR_FATAL, "tcp listen error");
		}

		if (listen(fd, LISTENQ) < 0) {
			logger(MERR_NOTICE, std::string("listen fail: ") + strerror(errno));
		}

		addrlen = res->ai_addrlen;
		listenFd = fd;

		freeaddrinfo(ressave);
	}

	TcpAcceptor(const std::string &listenPort) : TcpAcceptor("", listenPort)
	{
	}

	const std::string &
	listenHost() const
	{
		return host;
	}

	const std::string &
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

	TcpStream *
	acceptRequest()
	{
		int fd;
		TcpStream *stream = new TcpStream();

		while ( (fd = accept(listenFd, (SA *)stream->addrPointer(), stream->addrLengthPointer())) < 0 ) {
			logger(MERR_NOTICE, std::string("accept fail: ") + strerror(errno));
		}

		stream->setFileDescriptor(fd);

		return stream;
	}
private:
	TcpAcceptor();

	std::string host;

	std::string port;

	struct addrinfo hints;

	int listenFd;

	socklen_t addrlen;

	void
	setSocketOptions(int fd)
	{
		// TODO: set socket opt
		char yes = '1';
		if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			logger(MERR_NOTICE, std::string("set socket option failed: ") + strerror(errno));
		}
	}
};
}
#endif
