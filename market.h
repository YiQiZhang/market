#include "includes.h"

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


class MarketItem{

friend class Market;
friend ostream &operator<<(ostream &, const MarketItem&);

public:
	MarketItem(const string &c = "nocode", const string &en = "noname") : 
		code(c),
		enname(en) 
	{
	
	}

	MarketItem(const MarketItem &mi) :
		code(mi.code),
		enname(mi.enname)
	{

	}

	MarketItem &operator=(const MarketItem &rhs)
	{
		code = rhs.code;
		enname = rhs.enname;

		return *this;
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


class Market{

friend ostream &operator<<(ostream &, const Market&);

public:
	Market(const string &s = "top")
	{
		name = s;
	}

	int addItem(istream &is)
	{
		int res = 0;
		int quantity = 0;
		string line;
		
		while(getline(is ,line)) {
			if (isCmd(line, "q")) {
				return quantity;
			} else {
				res = addItem(line);
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

	int addItem(const string &s)
	{
		string code;
		string enname;
		istringstream is(s);

		is >> code >> enname;
		return addItem(MarketItem(code, enname));
	}

	int addItem(const MarketItem &item)
	{
		stocks[item.code] = item;

		return 1;
	}

private:
	string name;
	map<string, MarketItem> stocks;
};

ostream &operator<<(ostream &os, const Market& m)
{
	os << m.name << "Market Stock list:  " << endl;
	for(const auto &item : m.stocks) {
		os << item.second << endl;
	}

	return os;
}

}
