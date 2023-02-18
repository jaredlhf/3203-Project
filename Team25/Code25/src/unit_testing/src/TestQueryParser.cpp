#include "catch.hpp"
#include "QPS/QueryParser.h"
#include "QPS/ParserResponse.h"
#include "QPS/constants/Synonym.h"
#include "QPS/constants/Constants.h"

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
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setAssignSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setPatternClause(Clause::create(Constants::PATTERN, Value::create("\"count\""), Wildcard::create("s")));
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: variable v on LHS and partial pattern s on RHS") {
    std::vector<std::string> queryTokens = {"variable", "v", ";", "assign", "a", ";", "Select", "a", "pattern", "a", "(", "v", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setAssignSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setPatternClause(Clause::create(Constants::PATTERN, Synonym::create(Constants::VARIABLE, "v"), Wildcard::create("s")));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

// from bug
TEST_CASE("Parse correct query with pattern: wildcard on LHS and partial pattern x on RHS") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "_\"x\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a1"));
    expectedResObject.setAssignSynonym(Synonym::create(Constants::ASSIGN, "a1"));
    expectedResObject.setPatternClause(Clause::create(Constants::PATTERN, Wildcard::create(), Wildcard::create("x")));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: wildcard on both sides") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a1"));
    expectedResObject.setAssignSynonym(Synonym::create(Constants::ASSIGN, "a1"));
    expectedResObject.setPatternClause(Clause::create(Constants::PATTERN, Wildcard::create(), Wildcard::create()));

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

TEST_CASE("Parse pattern with empty string on first param") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "", ",", "_", "\"s\"", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse pattern with empty string on second param") {
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"1\"", ",", "_", "", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));

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
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "that", "Modifies", "(", "1", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setSuchThatClause(Clause::create(Constants::MODIFIES, Value::create("1"), Synonym::create(Constants::VARIABLE, "x")));
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

// from bug
TEST_CASE("Parse correct query with such that Follows*") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "such", "that", "Follows*", "(", "a1", ",", "s2", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a1"));
    expectedResObject.setSuchThatClause(Clause::create(Constants::FOLLOWSST, Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")));
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with syntax and semantic error should return syntax error") {
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "d", "such", "that", "Modifies", "1", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, ""));
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

/**
 * full complex query with valid declarations
 *
 */

TEST_CASE("Parse correct complex query with such that -> pattern") {
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "that", "Modifies", "(", "1", ",", "x", ")",
                                            "pattern", "a", "(", "\"x\"", ",", "_\"count\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setSuchThatClause(Clause::create(Constants::MODIFIES, Value::create("1"), Synonym::create(Constants::VARIABLE, "x")));
    expectedResObject.setAssignSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setPatternClause(Clause::create(Constants::PATTERN, Value::create("\"x\""), Wildcard::create("count")));
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct complex query with pattern -> such that") {
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"x\"", ",", "_\"count\"_", ")",
                                            "such", "that", "Modifies", "(", "1", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setSuchThatClause(Clause::create(Constants::MODIFIES, Value::create("1"), Synonym::create(Constants::VARIABLE, "x")));
    expectedResObject.setAssignSynonym(Synonym::create(Constants::ASSIGN, "a"));
    expectedResObject.setPatternClause(Clause::create(Constants::PATTERN, Value::create("\"x\""), Wildcard::create("count")));
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}