#include "Tokenizer.h"
#include "Tokenizer.cpp"
#include "catch.hpp"
#include <regex>

using namespace std;

TEST_CASE("TokenizeTest") {
    std::string testStatement = "Hello world testing";

    const char* args[] = { "Hello", "world", "testing"};
    std::vector<std::string> expected(args, std::end(args));

    REQUIRE(tokenize(testStatement) == expected);
}

TEST_CASE("NullStringTest") {
    std::string testStatement = "";
    vector<string> expected;
    REQUIRE(tokenize(testStatement) == expected);
}

TEST_CASE("EmptySpaceBeginningAndEndOfStringTest") {
    std::string testStatement = " Hello ";

    const char* args[] = {"Hello"};
    std::vector<std::string> expected(args, std::end(args));

    REQUIRE(tokenize(testStatement) == expected);
}

TEST_CASE("ExpectFunctionTest") {
    std::string testStatement = " Hello World";
    REQUIRE(expect(testStatement,"Hello") == "Hello");
}

TEST_CASE("ExpectFunctionFailTest") {
    std::string testStatement = " Hello World";
    REQUIRE_THROWS_AS(expect(testStatement,"World"),std::invalid_argument);
}