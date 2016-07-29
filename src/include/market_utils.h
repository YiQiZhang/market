#ifndef _MARKET_UTILS_H_
#define _MARKET_UTILS_H_

#include <core.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

namespace Market{
class Utils {
public:
	Utils() = default;

	static std::string
	sha1(const std::string &s)
	{
		CryptoPP::SHA1 hash;
		std::string digest;

		CryptoPP::StringSource(s, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

		return digest;
	}
};
}

#endif
