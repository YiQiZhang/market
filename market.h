#include <iostream>
#include <sstream>
#include <string>
#include <map>

using std::ostream;
using std::istream;
using std::string;
using std::map;
using std::istringstream;

namespace market{

class Market;
class MarketItem;

ostream &operator<<(ostream &, const Market&);
ostream &operator<<(ostream &, const MarketItem&);

class Market{

friend ostream &operator<<(ostream &, const Market&);

public:
	Market(string s = "top")
	{
		name = s;
	}

	int addItem(istream &is)
	{
		int res = 0;
		int quantity = 0;
		string line;
		
		while(getline(is ,line)) {
			if (line.find("q", 0, 1)) {
				return quantity;
			} else {
				res = m.addItem(line);
				if (res > 0) {
					quantity++;
					cout << *this;
				} else {
					err_quit(string("invalid input line") + line);
				}
			}
		}

		return quantity;
	}

	int addItem(string s)
	{
		string code;
		string enname;
		istringstream is(s);

		is >> code >> enname;
		addItem(MarketItem(code, name));
	}

	int addItem(MarketItem item)
	{
		stocks[item->code] = item;
	}

private:
	string name;
	map<string, MarketItem> stocks;
};

ostream &operator<<(ostream &os, const Market& m)
{
	os << name << "Market Stock list:  " << endl;
	for(const auto &item : stocks) {
		os << item.second << endl;
	}

	return os;
}

class MarketItem{

friend ostream &operator<<(ostream &, const MarketItem&);

public:
	MarketItem(string c, string en) : 
		code(c),
		enname(en) 
	{
	
	}
private:
	string code;
	string enname;
};

ostream &operator<<(ostream &os, const MarketItem& i)
{
  os << '[' << i.code << ']' << i.enname;

  return os;
}

}
