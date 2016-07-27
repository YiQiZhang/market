#ifndef _MARKET_CORE_H_
#define _MARKET_CORE_H_


/**
 * c std library
 * <strings.h>
 * functions:
 * memset
 * memcpy
 * memcmp
 */
#include <strings.h>

/**
 * c++ std library
 */
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>


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
 */
#include <netinet/in.h>
#define SA struct sockaddr
#define SS struct sockaddr_storage
#include <arpa/inet.h>
#include <sys/socket.h>

/**
 * market app
 */
#include <tcp.h>
#include <logger.h>
#include <network_helper.h>
#endif
