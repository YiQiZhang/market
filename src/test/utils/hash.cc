#include <core.h>
#include <gtest/gtest.h>

TEST(UtilsTest, Sha1) {
	EXPECT_EQ("2aae6c35c94fcfb415dbe95f408b9ce91ee846ed", Market::Utils::Hash::Sha1("hello world"));
}

TEST(UtilsTest, base64Encoding) {
	EXPECT_EQ(
		"MmFhZTZjMzVjOTRmY2ZiNDE1ZGJlOTVmNDA4YjljZTkxZWU4NDZlZA==", 
		Market::Utils::Base64::Encoding(Market::Utils::Hash::Sha1("hello world"))
	);
}
