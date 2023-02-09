
#include "SP/ExpressionParser.h"
#include "SP/ExpressionParser.cpp"
#include "catch.hpp"
#include <regex>
#include <iostream>

using namespace std;
ExpressionParser e;
TEST_CASE("ValidExpressionTest") {
    REQUIRE(e.verifyExpr("x + y") == true);
}

TEST_CASE("ValidExpressionBracketTest") {
    REQUIRE(e.verifyExpr("(x + y)") == true);
}

TEST_CASE("ValidExpressionMultiplyTest") {
    REQUIRE(e.verifyExpr("x + (2 * y)") == true);
}

TEST_CASE("ValidComplicatedExpressionTest") {
    REQUIRE(e.verifyExpr("x/3 + (2 * y) % (z - 3)") == true);
}

TEST_CASE("InvalidExpressionSuccessiveOperatorTest") {
    REQUIRE(e.verifyExpr("x +  * y") == false);
}

TEST_CASE("InvalidBracketMatchTest") {
    REQUIRE(e.verifyExpr("(x )+ y)") == false);
}

TEST_CASE("InvalidExpressionTest") {
    REQUIRE(e.verifyExpr("(x") == false);
}