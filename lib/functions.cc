#ifndef _MARKET_LIB_FUNCTIONS_H
#define _MARKET_LIB_FUNCTIONS_H

#include <iostream>
#include <string>

void err_quit(const string &s)
{
  std::cout << s << endl;
  exit(-1);
}

#endif
