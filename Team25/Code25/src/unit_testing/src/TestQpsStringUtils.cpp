#include "QPS/utils/StringUtils.h"
#include "catch.hpp"

// Unit Tests for isValidInt function
TEST_CASE("Valid int with no negative signs should return true") {
	std::string testInput = "123";
	REQUIRE(StringUtils::isValidInt(testInput) == true);
}

TEST_CASE("Valid int with negative sign should return true") {
	std::string testInput = "-123";
	REQUIRE(StringUtils::isValidInt(testInput) == true);
}

TEST_CASE("Empty string should return false") {
	std::string testInput = "";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("Special chars should return false") {
	std::string testInput = "-###";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("Alphabetic string should return false") {
	std::string testInput = "abc";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("Alphabetic string with negative sign should return false") {
	std::string testInput = "-abc";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("Alphabetic string with digits as prefix should return false") {
	std::string testInput = "123c";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("Digits with negative sign at non first char should return false") {
	std::string testInput = "123-";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}