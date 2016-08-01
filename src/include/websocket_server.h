#ifndef _MARKET_WEBSOCKET_SERVER_H_
#define _MARKET_WEBSOCKET_SERVER_H_

#include <core.h>

#define BUF_SIZE 1
#define HEADER_BUF_SIZE 1024 
#define WEBSOCKET_MAGIC_STRING "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

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
		return headers.at(key);
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
			os << '"' << header.first << "\", size: " << header.first.size() <<  "\n" 
				<< '"' << header.second << "\", size: " << header.second.size() << "\n";
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
		std::string::size_type delimPost;

		while( (n = stream.receive(buf, BUF_SIZE)) > 0) {
			content.append(buf, n);

			if ((delimPost = content.find("\r\n\r\n")) != std::string::npos) {
				std::string request(content, 0, delimPost);
				handleClientHandShakeRequest(stream, request);
				content = content.substr(0, delimPost + 4);
			}
		}
	}

private:
	TcpAcceptor acceptor;

	void
	handleClientHandShakeRequest(TcpStream &stream, const string &content)
	{

		std::cout << content << std::endl;
		
		// handler header
		std::vector<std::string> headlines = Market::String::explode(content, "\r\n");

		std::vector<std::string> firstline = Market::String::explode(headlines[0], " ");

		Connection connection(firstline[0], firstline[1], firstline[2]);

		for(std::vector<std::string>::size_type beg = 1, end = headlines.size() - 1; beg < end; beg++) {
			std::vector<std::string> line = Market::String::explode(headlines[beg], ":", 1);
			
			connection.setHeader(
				Market::String::trim(line[0]),
				Market::String::trim(line[1])
			);
		}

		std::cout << connection.to_string() << std::endl;

		handShakeResponse(stream, connection);
	}

	string
	buildAcceptKey(const Connection &connection) const
	{
		std::string ret(connection.getHeader("Sec-WebSocket-Key") + WEBSOCKET_MAGIC_STRING);

		unsigned char digest[SHA_DIGEST_LENGTH];

		Market::Utils::Hash::Sha1Hex(ret, &digest[0]);
	
		ret = Market::Utils::Base64::Encoding(std::string((char *)&digest[0], SHA_DIGEST_LENGTH));

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
