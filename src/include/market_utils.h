#ifndef _MARKET_UTILS_H_
#define _MARKET_UTILS_H_

#include <core.h>
#include <openssl/sha.h>

namespace Market{
class Utils {
public:
	Utils() = default;

	static std::string
	sha1(const std::string &s)
	{
		unsigned char digest[SHA_DIGEST_LENGTH];
		char ret[SHA_DIGEST_LENGTH*2];
		SHA1((unsigned char *) s.data(), s.size(), digest);

		for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
			std::sprintf(&ret[i*2], "%02x", digest[i]);
		}

		return std::string(&ret[0], SHA_DIGEST_LENGTH * 2);
	}
};
}

#endif
