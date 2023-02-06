
#include "sp/Parser.h"
#include "sp/Parser.cpp"
#include "catch.hpp"
#include <regex>
#include <string>

using namespace std;

TEST_CASE("ValidVariableTest") {
    REQUIRE(isValidVariableName("x") == true);
}

TEST_CASE("ValidVariableWithNumberTest") {
    REQUIRE(isValidVariableName("x9") == true);
}

TEST_CASE("InvalidVariableTest") {
    REQUIRE(isValidVariableName("9x") == false);
}

TEST_CASE("ValidNumberTest") {
    REQUIRE(isNumber("91247") == true);
}

TEST_CASE("InvalidNumberTest") {
    REQUIRE(isNumber("9x") == false);
}

TEST_CASE("AssignStatementTest") {
    const char* args[] = {"y", "=", "x", "+", "1", ";"};
    std::vector<std::string> expected(args, std::end(args));

    parseAssign(expected);
}
