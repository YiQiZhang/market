#include <core.h>

#define BUF_SIZE 4

using std::cout;
using std::endl;
using std::string;
using market::TcpAcceptor;
using market::TcpStream;

int main(int argc, char **argv)
{
	cout << "hello world! i am market server" << endl;
	TcpAcceptor server("9999");
	
	TcpStream stream = server.acceptRequest();

	string content;
	char buf[BUF_SIZE];
	ssize_t n;

	while( (n = stream.receive(buf, BUF_SIZE)) > 0) {
		cout << buf;
	}

	cout << "exit hehe" << endl;

	return 0;
}
