#include "includes.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

using market::Market;


int main(int argc, char **argv)
{
	string line;
	Market m;

	while (getline(cin, line)) {
		cout << "server main get a input line: " << line << endl;
		if (isCmd(line, "add")) {
			cout << "go to addItem" << endl;
			m.addItem(cin);
		} else if (isCmd(line, "flow")) {

		} else if (isCmd(line, "exit")) {
			cout << "all done!" << endl;
			break;
		} else {
			cout << "invalid operator " << line << endl;
		}
	}

	return 0;
}
