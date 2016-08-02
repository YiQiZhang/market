#ifndef _MARKET_STRING_H_
#define _MARKET_STRING_H_

#include <core.h>

namespace Market{
class String{
public:
	String() = default;
	~String() = default;

	static std::string
	trim(const std::string &s)
	{
		std::string::size_type beg = s.find_first_not_of(' '), 
								end = s.find_last_not_of(' ');

		return s.substr(beg, end - beg + 1);
	}

	static std::vector<string>
	explode(const std::string &s, const std::string &delim, int count = 0)
	{
		std::vector<string> ret;
		std::string::size_type pos = 0, oldpos = pos;

		if (count == 0) {
			count = -1;
		}

		while( ((pos = s.find(delim, pos)) != std::string::npos) &&
			   (count < 0 || count > 0)) {
			ret.push_back(s.substr(oldpos, pos - oldpos));
			pos += delim.size();
			oldpos = pos;
			count--;
		}

		if (oldpos <= s.size()) {
			ret.push_back(std::string(s, oldpos));
		}

		return ret;
	}
};
}
#endif
