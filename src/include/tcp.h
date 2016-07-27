#ifndef _MARKET_TCP_H
#define _MARKET_TCP_H

#include <core.h>

using std::string;

namespace market{

class Tcp {
public:
	Tcp(const string& addr) : addr_string(addr)
	{
		family = get_family_by_addr(addr_string);

		if ((sockfd = socket(family, SOCK_STREAM, IPPROTO_TCP)) < 0)
			logger(MERR_FATAL, "socket() error");
	}
	
	int socketfd() const;
private:
	string addr_string;
	int sockfd;
	int family;

	Tcp(){}
};
}
#endif
