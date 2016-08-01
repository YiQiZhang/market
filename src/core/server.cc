#include <core.h>

int 
main(int argc, char **argv)
{
	std::cout << "hello world! i am market server" << std::endl;
	
	Market::Websocket::Server server("", "9999");
	server.start();

	std::cout << "exit normal" << std::endl;

	return 0;
}
