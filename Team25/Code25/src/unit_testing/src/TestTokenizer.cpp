#include "SP/Tokenizer.h"
#include "SP/Tokenizer.cpp"
#include "catch.hpp"
#include <regex>

using namespace std;
Tokenizer t;
TEST_CASE("TokenizeTest") {
    std::string testStatement = "Hello world testing";

    const char* args[] = { "Hello", "world", "testing"};
    std::vector<std::string> expected(args, std::end(args));

    REQUIRE(t.tokenize(testStatement) == expected);
}

TEST_CASE("NullStringTest") {
    std::string testStatement = "";
    vector<string> expected;
    REQUIRE(t.tokenize(testStatement) == expected);
}

TEST_CASE("EmptytSpaceBeginningAndEndOfStringTest") {
    std::string testStatement = " Hello ";

    const char* args[] = {"Hello"};
    std::vector<std::string> expected(args, std::end(args));

    REQUIRE(t.tokenize(testStatement) == expected);
}

TEST_CASE("GetNextTokenTest") {
    std::string testStatement = " Hello World";
    Tokenizer tokenizer;
    tokenizer.setTokens(t.tokenize(testStatement));
    REQUIRE(tokenizer.getNextToken() == "Hello");
    REQUIRE(tokenizer.getNextToken() == "World");
}