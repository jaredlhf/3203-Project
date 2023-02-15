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

// Used for testing output
//TEST_CASE("ComplexStringTokenizeTest") {
//    std::string testStatement = "procedure computeCentroid {\n"
//                                "count = 0;\n"
//                                "cenX = 0 ;\n"
//                                "cenY=0;\n"
//                                "call readPoint;\n"
//                                "while ((x!=0) && (y != 0)) {\n"
//                                "count = count + 1;\n"
//                                "cenX =cenX + x;\n"
//                                "cenY= cenY + y;\n"
//                                "call readPoint;\n"
//                                "}\n"
//                                "if (count>=0) then {\n"
//                                "flag = 1;\n"
//                                "} else {\n"
//                                "if (count >= 0) then {\n"
//                                "flag = 1;\n"
//                                "} else {\n"
//                                "cenX = cenX / count;\n"
//                                "cenY = cenY / count;\n"
//                                "}\n"
//                                "normSq = cenX * cenX + cenY * cenY;\n"
//                                "}";
//
//    vector<string> result = t.tokenize((testStatement));
//    for (auto i : result) {
//        std::cout<< i << endl;
//    }
//}

TEST_CASE("GetNextTokenTest") {
    std::string testStatement = " Hello World";
    Tokenizer tokenizer;
    tokenizer.setTokens(t.tokenize(testStatement));
    REQUIRE(tokenizer.getNextToken() == "Hello");
    REQUIRE(tokenizer.getNextToken() == "World");
}