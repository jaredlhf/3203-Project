#include "catch.hpp"
#include "QPS/QueryParser.h"
#include "QPS/ParserResponse.h"
#include <iostream>

using namespace std;

QueryParser qp;

TEST_CASE("Parse correct query with one declaration and one select statement") {
    
    vector<string> queryTokens = {"variable", "v", ";", "select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({{"variable", "v"}});
    expectedResObject.setSynonym("v");

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(expectedResObject, resObj) == true);
}

TEST_CASE("Parse correct query with two declarations and one select statement") {

    vector<string> queryTokens = {"variable", "v", ",", "x", ";", "select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({{"variable", "v", ",", "x"}});
    expectedResObject.setSynonym("v");

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(expectedResObject, resObj) == true);
}


TEST_CASE("Parse query with incorrect design entity") {

    vector<string> queryTokens = {"Var", "v", ";", "select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({{"SyntaxError"}});
    expectedResObject.setSynonym("v");

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(expectedResObject, resObj) == true);
}

TEST_CASE("Parse query with repeated variable declarations") {

    vector<string> queryTokens = {"variable", "v", ",", "v", ";", "select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({{"SyntaxError"}});
    expectedResObject.setSynonym("v");

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(expectedResObject, resObj) == true);
}

