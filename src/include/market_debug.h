#ifndef _MARKET_DEBUG_H_
#define _MARKET_DEBUG_H_

#include <core.h>
#include <openssl/sha.h>

namespace Market{
namespace Debug {
static std::string
toBinaryString(unsigned char c)
{
	std::string ret;

	for(int i = 7; i >= 0; --i) {
		ret += (c & (1 << i)) ? '1' : '0';
	}

	return ret;
}

static std::string
toBinaryString(const std::string &s, const std::string &space = " ", int count = 4)
{
	std::string ret;

	ret += "\n===============binary begin========================\n";

	for(std::string::size_type i = 0; i < s.size(); ++i) {
		ret += toBinaryString(s.c_str()[i]) + space;

		if ((i + 1) % count == 0) {
			ret += "\n";
		}
	}
	ret += "\n=================binary end=========================\n";

	return ret;
}

}
}

#endif
