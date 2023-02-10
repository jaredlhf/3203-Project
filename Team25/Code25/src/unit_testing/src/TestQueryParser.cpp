#include "catch.hpp"
#include "QPS/QueryParser.h"
#include "QPS/ParserResponse.h"
#include "QPS/constants/Synonym.h"
#include "QPS/constants/Constants.h"

#include <iostream>

using namespace std;

QueryParser qp;

TEST_CASE("Parse correct query with one declaration and one select statement") {
    
    vector<string> queryTokens = {"variable", "v", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v")});
    expectedResObject.setSynonym(Synonym::create(Constants::VARIABLE, "v"));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(expectedResObject, resObj) == true);
}

// TEST_CASE("Parse correct query with two declarations and one select statement") {

//     vector<string> queryTokens = {"variable", "v", ",", "x", ";", "Select", "v"};
//     ParserResponse expectedResObject;
//     expectedResObject.setDeclarations({{"variable", "v", ",", "x"}});
//     expectedResObject.setSynonym("v");

//     ParserResponse resObj = qp.parseQueryTokens(queryTokens);

//     REQUIRE(expectedResObject.compare(expectedResObject, resObj) == true);
// }


// TEST_CASE("Parse query with incorrect design entity") {

//     vector<string> queryTokens = {"Var", "v", ";", "Select", "v"};
//     ParserResponse expectedResObject;
//     expectedResObject.setDeclarations({{"SyntaxError"}});
//     expectedResObject.setSynonym("v");

//     ParserResponse resObj = qp.parseQueryTokens(queryTokens);

//     REQUIRE(expectedResObject.compare(expectedResObject, resObj) == true);
// }

// TEST_CASE("Parse query with repeated variable declarations") {

//     vector<string> queryTokens = {"variable", "v", ",", "v", ";", "Select", "v"};
//     ParserResponse expectedResObject;
//     expectedResObject.setDeclarations({{"SyntaxError"}});
//     expectedResObject.setSynonym("v");

//     ParserResponse resObj = qp.parseQueryTokens(queryTokens);

//     REQUIRE(expectedResObject.compare(expectedResObject, resObj) == true);
// }

