#ifndef _MARKET_CORE_H_
#define _MARKET_CORE_H_

/**
 * system call
 *
 * <unistd.h>
 * functions:
 * read
 * write
 *
 * <sys/types.h>
 * size_t used for sizes of objects
 * ssize_t used for a count of bytes or an error indication
 *
 */
#include <unistd.h>
#include <sys/types.h>

/**
 * c std library
 */

/**
 * c++ std library
 *
 * <cstring>
 * memset
 * memcpy
 * memcmp
 *
 * <cctype>
 * isspace
 */
#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <regex>

#include <cstring>
#include <cctype>


/**
 * network library
 *
 * <netinet/in.h>
 * data structure:
 * struct in_addr
 * struct sockaddr_in
 * struct in6_addr
 * struct sockaddr_in6
 * struct sockaddr
 * struct sockaddr_storage
 *
 * functions:
 * htons
 * htonl
 * ntohs
 * ntohl
 *
 * <arpa/inet.h>
 * functions:
 * inet_aton
 * inet_addr
 * inet_ntoa
 * inet_pton
 * inet_ntop
 *
 * <sys/socket.h>
 * functions:
 * socket
 * listen
 * bind
 * accept
 *
 * <netdb.h>
 * data structure:
 * struct addrinfo
 */
#include <netinet/in.h>
#define SA struct sockaddr
#define SS struct sockaddr_storage
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

/**
 * market includes
 */
#include <network_helper.h>

/**
 * market class
 */
#include <market_utils.h>
#include <market_string.h>
#include <logger.h>
#include <stream.h>
#include <tcp_acceptor.h>
#include <websocket_server.h>
#endif
