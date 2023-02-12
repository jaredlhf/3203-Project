
#include "SP/ExpressionParser.h"
#include "SP/ExpressionParser.cpp"
#include "catch.hpp"
#include <regex>
#include <iostream>

using namespace std;
ExpressionParser e;
TEST_CASE("ValidExpressionTest") {
    REQUIRE(e.isExpr("x + y") == true);
}

TEST_CASE("ValidExpressionBracketTest") {
    REQUIRE(e.isExpr("(x + y)") == true);
}

TEST_CASE("ValidExpressionMultiplyTest") {
    REQUIRE(e.isExpr("x + (2 * y)") == true);
}

TEST_CASE("ValidComplicatedExpressionTest") {
    REQUIRE(e.isExpr("x/3 + (2 * y) % (z - 3)") == true);
}

TEST_CASE("InvalidExpressionSuccessiveOperatorTest") {
    REQUIRE(e.isExpr("x +  * y") == false);
}

TEST_CASE("InvalidBracketMatchTest") {
    REQUIRE(e.isExpr("(x )+ y)") == false);
}

TEST_CASE("InvalidExpressionTest") {
    REQUIRE(e.isExpr("(x") == false);
}

TEST_CASE("LessThanOrEqualTest") {
    REQUIRE(e.isRelExpr("x <= 3") == true);
}


TEST_CASE("MoreThanOrEqualTest") {
    REQUIRE(e.isRelExpr("x >= 3") == true);
}


TEST_CASE("NotEqualTest") {
    REQUIRE(e.isRelExpr("x != 3") == true);
}


TEST_CASE("EqualTest") {
    REQUIRE(e.isRelExpr("x == 3") == true);
}


TEST_CASE("LessThanTest") {
    REQUIRE(e.isRelExpr("x < 3") == true);
}


TEST_CASE("MoreThanTest") {
    REQUIRE(e.isRelExpr("x > 3") == true);
}

TEST_CASE("BracketRelTest") {
    REQUIRE(e.isRelExpr("(x > 3)") == true);
}

TEST_CASE("InvalidRelCloseBracketTest") {
    REQUIRE(e.isRelExpr("(x > 3") == false);
}

TEST_CASE("InvalidRelBracketTest") {
    REQUIRE(e.isRelExpr("x (> 3") == false);
}

TEST_CASE("InvalidRelOperatorTest") {
    REQUIRE(e.isRelExpr("x => 3") == false);
}

TEST_CASE("ValidNotEqualCondExprTest") {
    REQUIRE(e.isCondExpr("!(x>3)") == true);
}


TEST_CASE("ValidAndCondExprTest") {
    REQUIRE(e.isCondExpr("((x>3) && (y>5))") == true);
}


TEST_CASE("ValidOrCondExprTest") {
    REQUIRE(e.isCondExpr("((x>3)||(y>5))") == true);
}

TEST_CASE("ValidOrCondExpr2Test") {
    REQUIRE(e.isCondExpr("(x > 6)") == true);
}

TEST_CASE("InvalidOrCondExpr2Test") {
    REQUIRE(e.isCondExpr("(x + 6)") == false);
}