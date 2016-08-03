#include <core.h>
#include <gtest/gtest.h>

TEST(StringTest, StringTrim) {
	EXPECT_EQ("abc", Market::String::trim(" abc "));
	EXPECT_EQ("abc", Market::String::trim("abc "));
	EXPECT_EQ("abc", Market::String::trim(" abc"));
	EXPECT_EQ("abc", Market::String::trim("abc"));
}

TEST(StringTest, ExplodeSingleCharDelimiter) {
	std::string testString;
	std::vector<std::string> res;

	testString = "a b c";
	res = Market::String::explode(testString, " ");
	EXPECT_EQ(3, res.size());
	EXPECT_EQ("a", res[0]);
	EXPECT_EQ("b", res[1]);
	EXPECT_EQ("c", res[2]);

	testString = "a b c ";
	res = Market::String::explode(testString, " ");
	EXPECT_EQ(4, res.size());
	EXPECT_EQ("a", res[0]);
	EXPECT_EQ("b", res[1]);
	EXPECT_EQ("c", res[2]);
	EXPECT_EQ("", res[3]);

	testString = " a b c";
	res = Market::String::explode(testString, " ");
	EXPECT_EQ(4, res.size());
	EXPECT_EQ("", res[0]);
	EXPECT_EQ("a", res[1]);
	EXPECT_EQ("b", res[2]);
	EXPECT_EQ("c", res[3]);
}

TEST(StringTest, ExplodeMultipleCharsDelimiter) {
	std::string testString;
	std::vector<std::string> res;

	testString = "GET /index HTTP/1.1\r\nHost: www.domain.com\r\nConnection: keep-alive";
	res = Market::String::explode(testString, "\r\n");
	EXPECT_EQ(3, res.size());
	EXPECT_EQ("GET /index HTTP/1.1", res[0]);
	EXPECT_EQ("Host: www.domain.com", res[1]);
	EXPECT_EQ("Connection: keep-alive", res[2]);
}

TEST(StringTest, ExplodeLimitCount) {
	std::string testString;
	std::vector<std::string> res;

	testString = "Host: www.domain.com:8888";
	res = Market::String::explode(testString, ":", 1);
	EXPECT_EQ(2, res.size());
	EXPECT_EQ("Host", res[0]);
	EXPECT_EQ(" www.domain.com:8888", res[1]);
}
