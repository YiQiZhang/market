#include <core.h>
#include <gtest/gtest.h>

TEST(StringTest, StringTrim) {
	EXPECT_EQ("abc", Market::String::trim(" abc "));
	EXPECT_EQ("abc", Market::String::trim("abc "));
	EXPECT_EQ("abc", Market::String::trim(" abc"));
	EXPECT_EQ("abc", Market::String::trim("abc"));
}

TEST(StringTest, Explode) {
	std::string testString("a b c ");
	std::vector<std::string> res(Market::String::explode(testString, " "));

	EXPECT_EQ(4, res.size());
	EXPECT_EQ("a", res[0]);
	EXPECT_EQ("b", res[1]);
	EXPECT_EQ("c", res[2]);
	EXPECT_EQ("", res[3]);

}
