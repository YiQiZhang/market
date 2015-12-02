#ifndef _MARKET_LIB_FUNCTIONS_H
#define _MARKET_LIB_FUNCTIONS_H

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;


void err_quit(const string &s)
{
  cout << s << endl;
  exit(-1);
}

bool
isCmd(const string &input, const string &cmd)
{
	string::size_type n;
	if ( (n = input.find(cmd)) != string::npos )
		return true;
	else 
		return false;
}

#endif
