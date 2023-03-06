#include "QPS/utils/StringUtils.h"
#include "catch.hpp"
#include <iostream>

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

// Unit Tests for createPostFixNotation function

TEST_CASE("createPostFixNotation String infix expression with '+' arithmetic operations") {
	std::string infix = "a+b+c+d";
	std::string postfix = "(a)(b)+(c)+(d)+";
	std::string result = StringUtils::createPostFixNotation(infix);
	REQUIRE(result == postfix);
}


TEST_CASE("createPostFixNotation String infix expression with '+', '-' arithmetic operations") {
	std::string infix = "a+b-c";
	std::string postfix = "(a)(b)+(c)-";
	std::string result = StringUtils::createPostFixNotation(infix);
	REQUIRE(result == postfix);
}

TEST_CASE("createPostFixNotation String infix expression with '+', '-' and brackets arithmetic operations") {
	std::string infix = "a-(b+c)";
	std::string postfix = "(a)(b)(c)+-";
	std::string result = StringUtils::createPostFixNotation(infix);
	REQUIRE(result == postfix);
}

TEST_CASE("createPostFixNotation String infix expression with '+' and brackets arithmetic operations") {
	std::string infix = "(a+b)+c";
	std::string postfix = "(a)(b)+(c)+";
	std::string result = StringUtils::createPostFixNotation(infix);
	REQUIRE(result == postfix);
}

TEST_CASE("createPostFixNotation String infix expression with '+', '*' arithmetic operations") {
	std::string infix = "a+b*c";
	std::string postfix = "(a)(b)(c)*+";
	std::string result = StringUtils::createPostFixNotation(infix);
	REQUIRE(result == postfix);
}

TEST_CASE("createPostFixNotation String infix expression with '+', '-', '*' arithmetic operations") {
	std::string infix1 = "a+b*c-d";
	std::string postfix1 = "(a)(b)(c)*+(d)-";
	std::string result1 = StringUtils::createPostFixNotation(infix1);
	REQUIRE(result1 == postfix1);


	std::string infix2 = "v+x*y+z*t";
	std::string postfix2 = "(v)(x)(y)*+(z)(t)*+";
	std::string result2 = StringUtils::createPostFixNotation(infix2);
	REQUIRE(result2 == postfix2);
}

TEST_CASE("createPostFixNotation String infix expression with '+', '-', '*' and brackets arithmetic operations") {
	std::string infix = "(a+b)*c-d";
	std::string postfix = "(a)(b)+(c)*(d)-";
	std::string result = StringUtils::createPostFixNotation(infix);
	REQUIRE(result == postfix);
}

TEST_CASE("createPostFixNotation String infix expression with '+' and tab spacing arithmetic operations") {
	std::string infix = "x	";
	std::string postfix = "(x)";
	std::string result = StringUtils::createPostFixNotation(infix);
	REQUIRE(result == postfix);
}

TEST_CASE("createPostFixNotation String infix expression with multi-char variables, '+' arithmetic operations") {
	std::string infix = "abc + def + ghi";
	std::string postfix = "(abc)(def)+(ghi)+";
	std::string result = StringUtils::createPostFixNotation(infix);
	REQUIRE(result == postfix);
}

// Unit Tests for postFixInFullpostFix function

TEST_CASE("postFixInFullpostFix String full same variables and same ops postfix successful expression match") {
	std::string postfix = "(a)(b)+";
	std::string fullPostFix = "(a)(b)+";
	REQUIRE(StringUtils::postFixInFullpostFix(postfix, fullPostFix) == true);
}

TEST_CASE("postFixInFullpostFix String full same variable different ops '+', '-' postfix fail expression match") {
	std::string postfix = "(a)(b)+";
	std::string fullPostFix = "(a)(b)-";
	REQUIRE(StringUtils::postFixInFullpostFix(postfix, fullPostFix) == false);
}

TEST_CASE("postFixInFullpostFix String full postfix same variable, same ops, different ordering fail expression match") {
	std::string postfix = "(a)(b)+";
	std::string fullPostFix = "(b)(a)+";
	REQUIRE(StringUtils::postFixInFullpostFix(postfix, fullPostFix) == false);
}

TEST_CASE("postFixInFullpostFix String full postfix same multi-char variable, same ops postfix successful expression match") {
	std::string postfix = "(abc)(def)+";
	std::string fullPostFix = "(abc)(def)+(ghi)+";
	REQUIRE(StringUtils::postFixInFullpostFix(postfix, fullPostFix) == true);
}

TEST_CASE("postFixInFullpostFix String partial postfix same variable and same ops successful expression match") {
	std::string postfix1 = "(x)";
	std::string postfix2 = "(y)";
	std::string postfix3 = "(z)";
	std::string postfix4 = "(t)";
	std::string postfix5 = "(v)";
	std::string postfix6 = "(x)(y)*";
	std::string postfix7 = "(z)(t)*";
	std::string postfix8 = "(v)(x)(y)*+";
	std::string fullPostFix = "(v)(x)(y)*+(z)(t)*+";
	REQUIRE(StringUtils::postFixInFullpostFix(postfix1, fullPostFix) == true);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix2, fullPostFix) == true);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix3, fullPostFix) == true);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix4, fullPostFix) == true);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix5, fullPostFix) == true);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix6, fullPostFix) == true);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix7, fullPostFix) == true);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix8, fullPostFix) == true);
}

TEST_CASE("postFixInFullpostFix String partial postfix same variable and same ops fail expression match") {
	std::string postfix1 = "(v)(x)+";
	std::string postfix2 = "(y)(z)+";
	std::string postfix3 = "(x)(y)*(z)+";
	std::string fullPostFix = "(v)(x)(y)*+(z)(t)*+";
	REQUIRE(StringUtils::postFixInFullpostFix(postfix1, fullPostFix) == false);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix2, fullPostFix) == false);
	REQUIRE(StringUtils::postFixInFullpostFix(postfix3, fullPostFix) == false);
} 