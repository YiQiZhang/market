#ifndef _MARKET_TCP_ACCEPTOR_H
#define _MARKET_TCP_ACCEPTOR_H

#include <core.h>

namespace market{

class TcpAcceptor{
public:
	TcpAcceptor(const string& addr, int listen_port)
	{
	}
	TcpAcceptor(int listen_port);
	void accept();
private:
	TcpAcceptor();

	SS serv;
	int port;
	Tcp tcp;
};
}
#endif
