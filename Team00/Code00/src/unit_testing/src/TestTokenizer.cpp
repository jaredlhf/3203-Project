#include "Tokenizer.h"
#include "Tokenizer.cpp"
#include "catch.hpp"
using namespace std;

void match(bool b) {
    REQUIRE(b);
}

TEST_CASE("TokenizeTest") {
    std::string testStatement = "Hello world testing";
    const char* args[] = { "Hello", "world", "testing"};
    std::vector<std::string> expected(args, std::end(args));
    std::vector<std::string> output = tokenize(testStatement);

    match(output == expected);
}

TEST_CASE("NullStringTest") {
    std::string testStatement = "";
    vector<string> expected;
    std::vector<std::string> output = tokenize(testStatement);

    match(output == expected);
}