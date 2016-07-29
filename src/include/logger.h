#ifndef _MARKET_LOGGER_H
#define _MARKET_LOGGER_H

#include <core.h>

#define MERR_FATAL 1
#define MERR_NOTICE 2

namespace Market{

void
logger(int type, const string& errmsg)
{
	std::cout << errmsg << std::endl;
	if (type == MERR_FATAL) {
		exit(1);
	}
}
}
#endif
