#include "catch.hpp"
#include "QPS/QueryParser.h"
#include "QPS/ParserResponse.h"
#include "QPS/constants/Synonym.h"
#include "QPS/constants/Constants.h"

#include <iostream>

QueryParser qp;

/** 
 * Declarations testing with select statements
 * 
*/
TEST_CASE("Parse correct query with one declaration and one select statement") {
    std::vector<std::string> queryTokens = {"variable", "v", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v")});
    expectedResObject.setSynonym(Synonym::create(Constants::VARIABLE, "v"));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with two declarations and one select statement") {
    std::vector<std::string> queryTokens = {"variable", "v", ";", "assign", "a", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::VARIABLE, "v"));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with two synonyms in one declaration and one select statement") {

    std::vector<std::string> queryTokens = {"variable", "v", ",", "x", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::VARIABLE, "x")});
    expectedResObject.setSynonym(Synonym::create(Constants::VARIABLE, "v"));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with incorrect design entity") {
    std::vector<std::string> queryTokens = {"Var", "v", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with no csv for declaration") {
    std::vector<std::string> queryTokens = {"variable", "v", "x", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with repeated variable declarations") {

    std::vector<std::string> queryTokens = {"variable", "v", ",", "v", ";", "Select", "v"};
    ParserResponse expectedResObject;

    expectedResObject.setSynonym(Synonym::create(Constants::SEMANTIC_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with invalid terminating token") {

    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "_", ")", ";"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with random extra token") {

    // TODO: random should be identified as 
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "random", "pattern", "a", "(", "\"count\"", ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));    

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with invalid integer") {

    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "122s", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with invalid synonym name") {

    std::vector<std::string> queryTokens = {"assign", "1sd", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "122", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

/** 
 * Patterns parsing with valid declarations
 * 
*/
TEST_CASE("Parse correct query with pattern: count constant value on LHS and s partial pattern on RHS") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "_", "\"s\"", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a"));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query ith pattern: variable v on LHS and partial pattern s on RHS") {
    std::vector<std::string> queryTokens = {"variable", "v", ";", "assign", "a", ";", "Select", "a", "pattern", "a", "(", "v", ",", "_", "\"s\"", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a"));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse pattern with undeclared variable count on LHS") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "count", ",", "_", "\"s\"", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SEMANTIC_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with invalid assign syn on pattern") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "s", "(", "\"count\"", ",", "_", "\"s\"", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SEMANTIC_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has unclosed brackets") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "_", "\"s\"", "_"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has random close bracket tokens") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", ")", "\"s\"", "_"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has no open bracket") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "\"count\"", ",", "_", "\"s\"", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has no matching enclosing wildcard") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "\"s\"", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

/**
 * such that parsing with valid declarations
 * 
 */

TEST_CASE("Parse correct query with such that Modifies") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "such", "that", "Modifies", "(", "1", ",", "2", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a"));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}