#ifndef _MARKET_TCP_H
#define _MARKET_TCP_H

#include <core.h>

namespace Market{

class Stream {
public:
	ssize_t
	receive(char *buf, size_t len)
	{
		size_t nleft;
		ssize_t nread;
		char *ptr;

		ptr = buf;
		nleft = len;
		while(nleft > 0) {
			if ( (nread = read(fileDescriptor(), buf, nleft)) < 0 ) {
				if (errno == EINTR) {
					nread = 0;
				} else {
					return (-1);
				}
			} else if (nread == 0) {
				break;
			}
			nleft -= nread;
			ptr += nread;
		}

		return (len - nleft);
	}

	ssize_t
	send(const char *buf, size_t len)
	{
		size_t nleft;
		ssize_t nwritten;
		const char *ptr;

		ptr = buf;
		nleft = len;
		while(nleft > 0) {
			if ( (nwritten = write(fileDescriptor(), buf, nleft)) <= 0 ) {
				if (nwritten < 0 && errno == EINTR) {
					nwritten = 0;
				} else {
					return (-1);
				}
			}
			nleft -= nwritten;
			ptr += nwritten;
		}

		return len;
	}

	SS *
	addrPointer()
	{
		return &addr;
	}

	socklen_t *
	addrLengthPointer()
	{
		return &addrLen;
	}

	socklen_t
	addrLength() const
	{
		return addrLen;
	}

	virtual int fileDescriptor() const = 0;

	virtual ~Stream() = default;
private:
	SS addr;
	socklen_t addrLen;
};

class TcpStream : public Stream{
public:
	TcpStream() : fd(-1)
	{
	}

	TcpStream(int fp) : fd(fp)
	{
	}

	int
	fileDescriptor() const override
	{
		return fd;
	}

	bool
	setFileDescriptor(int fDescriptor)
	{
		if (fd <= 0 ) {
			fd = fDescriptor;
			return true;
		}

		return false;
	}
private:
	int fd;
};
}
#endif
