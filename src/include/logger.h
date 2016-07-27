#ifndef _MARKET_LOGGER_H
#define _MARKET_LOGGER_H

#include <core.h>

#define MERR_FATAL 1

namespace market{

using std::string;
using std::cout;
using std::endl;

void
logger(int type, const string& errmsg)
{
	cout << errmsg << endl;
}
}
#endif
