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

TEST_CASE("GetNextTokenTest") {
    std::string testStatement = " Hello World";
    Tokenizer tokenizer;
    tokenizer.setTokens(tokenize(testStatement));
    REQUIRE(tokenizer.getNextToken() == "Hello");
    REQUIRE(tokenizer.getNextToken() == "World");
}