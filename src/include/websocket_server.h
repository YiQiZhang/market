#ifndef _MARKET_WEBSOCKET_SERVER_H_
#define _MARKET_WEBSOCKET_SERVER_H_

#include <core.h>

#define BUF_SIZE 1
#define HEADER_BUF_SIZE 1024 

namespace Market {
namespace Websocket{

class Connection{
friend class Server;
public:
	Connection(const std::string &method,
					const std::string &uri,
					const std::string &version) :
		method(method),
		uri(uri),
		version(version) 
	{
	}

	void
	setHeader(const std::string &key,
			  const std::string &val) 
	{
		headers[key] = val;
	}

	const std::unordered_map<std::string, std::string> &
	getHeaders() const
	{
		return headers;
	}

	const std::string &
	getHeader(const std::string &key) const
	{
		return (*headers.find(key)).second;
	}

	bool
	headerExist(const std::string &key) const
	{
		return headers.find(key) != headers.end();
	}

	std::string
	to_string() const
	{
		std::ostringstream os;

		os << "method: " << method << "\n"
			<< "uri: " << uri << "\n"
			<< "version: " << version << "\n";

		for(const auto &header: headers) {
			os << header.first << "\n" 
				<< header.second << "\n";
		}

		return os.str();
	}
		
private:
	std::string method;
	std::string uri;
	std::string version;
	std::unordered_map<std::string, std::string> headers;
};

class Server{
public:
	static constexpr char MagicString[] = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

	Server(const std::string &host,
			const std::string &port) :
		acceptor(host, port)
	{
	}
	
	void start()
	{
		TcpStream stream = acceptor.acceptRequest();

		std::string content;
		char buf[BUF_SIZE];
		ssize_t n;

		while( (n = stream.receive(buf, BUF_SIZE)) > 0) {
			content.append(buf, n);
		}

		std::cout << content;
		
		// handler header
		std::vector<std::string> headlines = Market::String::explode(content, "\r\n");

		std::vector<std::string> firstline = Market::String::explode("GET / HTTP/1.1", " ");

		Connection connection(firstline[0], firstline[1], firstline[2]);

		for(std::vector<std::string>::size_type beg = 1, end = headlines.size() - 1; beg < end; beg++) {
			std::vector<std::string> line = Market::String::explode(headlines[beg], ":", 1);
			
			connection.setHeader(
				Market::String::trim(line[0]),
				Market::String::trim(line[1])
			);
		}
		
		handShakeResponse(stream, connection);
	}

private:
	TcpAcceptor acceptor;

	string
	buildAcceptKey(const Connection &connection) const
	{
		const char *MagicString;

		std::string ret(connection.getHeader("Sec-Websocket-Key") + MagicString);

		ret = Market::Utils::Base64::Encoding(Market::Utils::Sha1(ret));

		return ret;
	}

	void
	handShakeResponse(TcpStream &stream, Connection &connection)
	{
		std::ostringstream os;
		
		os << connection.version << " 101 Switching Protocols\r\n"
			<< "Upgrade: websocket\r\n"
			<< "Connection: Upgrade\r\n"
			<< "Sec-WebSocket-Accept: " << buildAcceptKey(connection) << "\r\n\r\n";

		std::cout << os.str();

		stream.send(os.str().data(), os.str().size());
	}
};

}
}
#endif
