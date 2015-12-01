#include <iostream>
#include <string>
#include "market.h"

using std::cin;
using std::cout;
using std::string;

using market::Market;

int main(int argc, char **argv)
{
	string line;
	Market m;

	while (getline(cin, line)) {
		if (line.find("add", 0, 3)) {
			m.addItem(cin);
		} else if (line.find("flow", 0, 4)) {

		} else if (line.find("exit", 0, 4)) {
			cout << "all done!" << endl;
			break;
		} else {
			cout << "invalid operator " << line << endl;
		}
	}

	return 0;
}
