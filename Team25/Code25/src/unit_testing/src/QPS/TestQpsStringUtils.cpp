#include "QPS/utils/StringUtils.h"
#include "catch.hpp"

// Unit Tests for isValidInt function
TEST_CASE("isValidInt Valid int with no negative signs should return true") {
	std::string testInput = "123";
	REQUIRE(StringUtils::isValidInt(testInput) == true);
}

TEST_CASE("isValidInt Valid int with negative sign should return true") {
	std::string testInput = "-123";
	REQUIRE(StringUtils::isValidInt(testInput) == true);
}

TEST_CASE("isValidInt Empty string should return false") {
	std::string testInput = "";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("isValidInt Special chars should return false") {
	std::string testInput = "-###";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("isValidInt Alphabetic string should return false") {
	std::string testInput = "abc";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("isValidInt Alphabetic string with negative sign should return false") {
	std::string testInput = "-abc";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("isValidInt Alphabetic string with digits as prefix should return false") {
	std::string testInput = "123c";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

TEST_CASE("isValidInt Digits with negative sign at non first char should return false") {
	std::string testInput = "123-";
	REQUIRE(StringUtils::isValidInt(testInput) == false);
}

// Unit Tests for spaceifyString function
TEST_CASE("spaceifyString String with a normal int returns itself") {
	std::string test = "123";
	std::string expected = "123";
	REQUIRE(StringUtils::spaceifyString(test) == expected);
}

TEST_CASE("spaceifyString String with a normal string token returns itself") {
	std::string test = "main";
	std::string expected = "main";
	REQUIRE(StringUtils::spaceifyString(test) == expected);
}

TEST_CASE("spaceifyString String with a simple expression returns the right result") {
	std::string test = "1+2";
	std::string expected = "1 + 2";
	REQUIRE(StringUtils::spaceifyString(test) == expected);
}

TEST_CASE("spaceifyString String with a complex expression returns the right result") {
	std::string test = "x+(z*y1)+1";
	std::string expected = "x +  ( z * y1 )  + 1";
	REQUIRE(StringUtils::spaceifyString(test) == expected);
}

TEST_CASE("spaceifyString String with a complex expression with multichar tokens returns the right result") {
	std::string test = "xyz+(z1w*y1)+12";
	std::string expected = "xyz +  ( z1w * y1 )  + 12";
	REQUIRE(StringUtils::spaceifyString(test) == expected);
}

// Unit Tests for splitString function
TEST_CASE("splitString String with a normal int returns list of itself") {
	std::string test = "123";
	std::vector<std::string> expected = { "123" };
	REQUIRE(StringUtils::splitString(test) == expected);
}

TEST_CASE("splitString String with a normal string token returns list of itself") {
	std::string test = "main";
	std::vector<std::string> expected = { "main" };
	REQUIRE(StringUtils::splitString(test) == expected);
}

TEST_CASE("splitString String with a simple expression returns the right result") {
	std::string test = "1 + 2";
	std::vector<std::string> expected = { "1", "+", "2" };
	REQUIRE(StringUtils::splitString(test) == expected);
}

TEST_CASE("splitString String with a complex expression returns the right result") {
	std::string test = "x +  ( z * y1 )  + 1";
	std::vector<std::string> expected = { "x", "+", "(", "z", "*", "y1", ")", "+",  "1" };
	REQUIRE(StringUtils::splitString(test) == expected);
}

TEST_CASE("splitString String with a complex expression with multichar tokens returns the right result") {
	std::string test = "xyz +  ( z1w * y1 )  + 12";
	std::vector<std::string> expected = { "xyz", "+", "(", "z1w", "*", "y1", ")", "+",  "12" };
	REQUIRE(StringUtils::splitString(test) == expected);
}

// Unit Tests for tokenInOp function
TEST_CASE("tokenInOp String with a normal int as both args returns true") {
	std::string op = "123";
	std::string token = "123";
	REQUIRE(StringUtils::tokenInOp(op, token) == true);
}

TEST_CASE("tokenInOp String with a normal string as both args return true") {
	std::string op = "main";
	std::string token = "main";
	REQUIRE(StringUtils::tokenInOp(op, token) == true);
}

TEST_CASE("tokenInOp String with a normal string as a substr of another string return false") {
	std::string op = "main";
	std::string token = "mainprogram";
	REQUIRE(StringUtils::tokenInOp(op, token) == false);
}

TEST_CASE("tokenInOp String with a normal string as a substr of another space separated string return true") {
	std::string op = "main";
	std::string token = "main program";
	REQUIRE(StringUtils::tokenInOp(op, token) == false);
}

TEST_CASE("tokenInOp String with a int in a simple expression returns the right result") {
	std::string op = "12+2";
	std::string token = "12";
	REQUIRE(StringUtils::tokenInOp(op, token) == true);
}

TEST_CASE("tokenInOp String with a strtoken in a simple expression returns the right result") {
	std::string op = "12+send2";
	std::string token = "send2";
	REQUIRE(StringUtils::tokenInOp(op, token) == true);
}


TEST_CASE("tokenInOp String with a substr of strtoken in a simple expression returns the right result") {
	std::string op = "12+send2";
	std::string token = "2";
	REQUIRE(StringUtils::tokenInOp(op, token) == false);
}

TEST_CASE("tokenInOp String with int in a complex expression returns the right result") {
	std::string op = "x+(z*y1)+100";
	std::string token = "100";
	REQUIRE(StringUtils::tokenInOp(op, token) == true);
}

TEST_CASE("tokenInOp String with substr of int in a complex expression returns the right result") {
	std::string op = "x+(z*y1)+100";
	std::string token = "10";
	REQUIRE(StringUtils::tokenInOp(op, token) == false);
}

TEST_CASE("tokenInOp String with a str token in complex expression returns the right result") {
	std::string op = "xyz+(z1w*y1)+12";
	std::string token = "z1w";
	REQUIRE(StringUtils::tokenInOp(op, token) == true);
}

TEST_CASE("tokenInOp String with a substr of str token in complex expression returns the right result") {
	std::string op = "xyz+(z1w*y1)+12";
	std::string token = "z1";
	REQUIRE(StringUtils::tokenInOp(op, token) == false);
}