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
	Connection(TcpStream *stem) :
		stem(stem),
		handShaked(false)
	{
	}

	bool
	hasHandShaked() const
	{
		return handShaked;
	}

	void
	parseHeader(const std::string &headerStr)
	{
		if (handShaked == true) {
			return;
		}

		// handler header
		std::vector<std::string> headlines = Market::String::explode(headerStr, "\r\n");

		std::vector<std::string> firstline = Market::String::explode(headlines[0], " ");

		method = firstline[0];
		uri = firstline[1];
		version = firstline[2];

		for(std::vector<std::string>::size_type beg = 1, end = headlines.size() - 1; beg < end; beg++) {
			std::vector<std::string> line = Market::String::explode(headlines[beg], ":", 1);
			
			setHeader(
				Market::String::trim(line[0]),
				Market::String::trim(line[1])
			);
		}

		handShaked = true;
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

	TcpStream *
	stream()
	{
		return stem;
	}
		
private:
	TcpStream *stem;
	std::string method;
	std::string uri;
	std::string version;
	bool handShaked;
	std::unordered_map<std::string, std::string> headers;

	void
	setHeader(const std::string &key, const std::string &val)
	{
		headers[key] = val;
	}
};

class Frame {
	static constexpr int OPCODE_CONTINUE = 0;
	static constexpr int OPCODE_TEXT = 1;
	static constexpr int OPCODE_BINARY = 2;
public:
	Frame(char * buf, int len)
	{
	}
private:
	int opcode;
	bool isFin;
	uint64_t length;
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
		TcpStream *stream = acceptor.acceptRequest();
		Connection *connection = new Connection(stream);

		std::string content;
		char buf[BUF_SIZE];
		ssize_t n;
		std::string::size_type delimPost;

		while( (n = stream->receive(buf, BUF_SIZE)) > 0) {
			content.append(buf, n);

			if (!connection->hasHandShaked()) {
				// hand shake request
				if ((delimPost = content.find("\r\n\r\n")) != std::string::npos) {
					std::string requestContent(content, 0, delimPost);
					handleClientHandShakeRequest(connection, requestContent);
					content = content.substr(delimPost + 4);
				}
			} else {
				if (content.size() >= 2) {
					std::cout << Market::Debug::toBinaryString(content) << std::endl;

					unsigned char firstByte = content.c_str()[0];
					bool isFin = false;
					int opcode = 0;
					if (firstByte & 0x80) {
						isFin = true;
					}
					opcode = firstByte & 0xF;

					unsigned char secByte = content.c_str()[1];
					bool isMask = false;
					if (secByte & 0x80) {
						isMask = true;
					}
					
					unsigned short payloadType = secByte & 0x7f;
					uint64_t payloadLen;
					if (payloadType <= 125) {
						payloadLen = payloadType;
					} 
					
				}

			}
		}
	}

private:
	TcpAcceptor acceptor;
	std::unordered_map<int, Connection *> connections;

	void
	handleClientHandShakeRequest(Connection *connection, const string &content)
	{
		connection->parseHeader(content);
		sendHandShakeResponse(connection);
	}

	void
	sendHandShakeResponse(Connection *connection)
	{
		std::ostringstream os;
		
		os << connection->version << " 101 Switching Protocols\r\n"
			<< "Upgrade: websocket\r\n"
			<< "Connection: Upgrade\r\n"
			<< "Sec-WebSocket-Accept: " << buildAcceptKey(*connection) << "\r\n\r\n";

		connection->stream()->send(os.str().data(), os.str().size());
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
};

}
}
#endif
