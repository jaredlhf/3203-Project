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
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::VARIABLE, "v")});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with two declarations and one select statement") {
    std::vector<std::string> queryTokens = {"variable", "v", ";", "assign", "a", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::VARIABLE, "v")});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with two synonyms in one declaration and one select statement") {

    std::vector<std::string> queryTokens = {"variable", "v", ",", "x", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::VARIABLE, "x")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::VARIABLE, "v")});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with two synonyms in one declaration and select statement with two variables") {

    std::vector<std::string> queryTokens = {"variable", "v", ",", "x", ";", "Select", "<", "v", ",", "x", ">"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::VARIABLE, "x")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::VARIABLE, "x")});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with two synonyms in one declaration and select statement with boolean") {

    std::vector<std::string> queryTokens = {"variable", "v", ",", "x", ";", "Select", "BOOLEAN"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::VARIABLE, "x")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::BOOLEAN, "")});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with two synonyms in one declaration and select statement with one undeclared variable and one valid variable") {

    std::vector<std::string> queryTokens = {"variable", "v", ",", "x", ";", "Select", "<", "z", ",", "x", ">"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::SEMANTIC_ERROR, "")});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with two declarations but no semicolon") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "v", "assign", "a", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with incorrect design entity") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"Var", "v", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with no csv for declaration") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "v", "x", ";", "Select", "v"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with repeated variable declarations") {
    std::shared_ptr<Synonym> SEMANTIC_ERROR_SYNONYM = Synonym::create(Constants::SEMANTIC_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "v", ",", "v", ";", "Select", "v"};
    ParserResponse expectedResObject;

    expectedResObject.setSelectSynonyms({SEMANTIC_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with invalid string token") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "_", ")", ";"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with random extra token") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "random", "pattern", "a", "(", "\"count\"", ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with invalid integer") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "122s", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with invalid synonym name") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "1sd", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "122", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

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
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a"), Clause::create(Constants::PATTERN, Value::create("count"), Wildcard::create("s")));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: variable v on LHS and partial pattern s on RHS") {
    std::vector<std::string> queryTokens = {"variable", "v", ";", "assign", "a", ";", "Select", "a", "pattern", "a", "(", "v", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "v"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a"), Clause::create(Constants::PATTERN, Synonym::create(Constants::VARIABLE, "v"), Wildcard::create("s")));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: wildcard on LHS and partial pattern x on RHS") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "_\"x\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a1")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a1"), Clause::create(Constants::PATTERN, Wildcard::create(), Wildcard::create("x")));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: wildcard on LHS and partial pattern x + y on RHS") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "_\"x + y\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a1")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a1"), Clause::create(Constants::PATTERN, Wildcard::create(), Wildcard::create("x + y")));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: wildcard on LHS and nested equation pattern x + (y + z) on RHS") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "\"x + (y + z)\"", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a1")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a1"), Clause::create(Constants::PATTERN, Wildcard::create(), Value::create("x + (y + z)")));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: wildcard on LHS and exact equation pattern x + y on RHS") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "\"x + y\"", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a1")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a1"), Clause::create(Constants::PATTERN, Wildcard::create(), Value::create("x + y")));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: wildcard on LHS and exact pattern x on RHS") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "\"x\"", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a1")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a1"), Clause::create(Constants::PATTERN, Wildcard::create(), Value::create("x")));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: wildcard on LHS and partial number pattern 123 on RHS") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "_\"123\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a1")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a1"), Clause::create(Constants::PATTERN, Wildcard::create(), Wildcard::create("123")));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with pattern: wildcard on both sides") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "Select", "a1", "pattern", "a1", "(", "_", ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a1")});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a1"), Clause::create(Constants::PATTERN, Wildcard::create(), Wildcard::create()));
    expectedResObject.setPatternClauses({pair});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse pattern with undeclared variable count on LHS") {
    std::shared_ptr<Synonym> SEMANTIC_ERROR_SYNONYM = Synonym::create(Constants::SEMANTIC_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "count", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SEMANTIC_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse pattern with empty string on first param") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse pattern with empty string on second param") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"1\"", ",", "__", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with invalid assign syn on pattern") {
    std::shared_ptr<Synonym> SEMANTIC_ERROR_SYNONYM = Synonym::create(Constants::SEMANTIC_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "s", "(", "\"count\"", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SEMANTIC_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has unclosed brackets") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "_\"s\"_"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has random close bracket tokens") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", ")", "\"s\"_"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has no open bracket") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "\"count\"", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has no matching enclosing wildcard") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"count\"", ",", "\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern that has undeclared assign synonym") {
    std::shared_ptr<Synonym> SEMANTIC_ERROR_SYNONYM = Synonym::create(Constants::SEMANTIC_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "Select", "a", "pattern", "a", "(", "a", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SEMANTIC_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern with no pattern keyword") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "(", "a", ",", "_\"s\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with pattern with wrong pattern expression") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "Select", "a", "pattern", "a", "(", "a", ",", "_\"s + s (dd !)\"_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

/**
 * such that parsing with valid declarations
 * 
 */

TEST_CASE("Parse correct query with such that statement Modifies") {
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "that", "Modifies", "(", "1", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSuchThatClauses(
            {Clause::create(Constants::MODIFIES, Value::create("1"), Synonym::create(Constants::VARIABLE, "x"))});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with such that procedure Modifies") {
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "procedure", "p", ";", "Select", "a", "such", "that", "Modifies", "(", "p", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::ASSIGN, "a"), Synonym::create(Constants::PROCEDURE, "p")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSuchThatClauses(
            {Clause::create(Constants::MODIFIES, Synonym::create(Constants::PROCEDURE, "p"),
                            Synonym::create(Constants::VARIABLE, "x"))});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);
    
    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with such that procedure Uses") {
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "procedure", "p", ";", "Select", "a", "such", "that", "Uses", "(", "p", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::ASSIGN, "a"), Synonym::create(Constants::PROCEDURE, "p")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSuchThatClauses({Clause::create(Constants::USES, Synonym::create(Constants::PROCEDURE, "p"),
                                                         Synonym::create(Constants::VARIABLE, "x"))});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct query with such that Follows") {
    std::vector<std::string> queryTokens = {"assign", "a1", ";", "stmt", "s2", ";", "Select", "a1", "such", "that", "Follows", "(", "a1", ",", "s2", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::ASSIGN, "a1"), Synonym::create(Constants::STMT, "s2")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a1")});
    expectedResObject.setSuchThatClauses({Clause::create(Constants::FOLLOWS, Synonym::create(Constants::ASSIGN, "a1"),
                                                         Synonym::create(Constants::STMT, "s2"))});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse incorrect query with such that procedure Modifies and print syn") {
    std::shared_ptr<Synonym> SEMANTIC_ERROR_SYNONYM = Synonym::create(Constants::SEMANTIC_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "print", "p", ";", "Select", "a", "such", "that", "Modifies", "(", "p", ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SEMANTIC_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse incorrect query with such that procedure Uses and read syn") {
    std::shared_ptr<Synonym> SEMANTIC_ERROR_SYNONYM = Synonym::create(Constants::SEMANTIC_ERROR, "");
    std::vector<std::string> queryTokens = {"assign", "a", ";", "read", "r", ";", "Select", "a", "such", "that", "Uses", "(", "r", ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SEMANTIC_ERROR_SYNONYM});

    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with syntax and semantic error should return syntax error") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "d", "such", "that", "Modifies", "1", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with incomplete such that keyword") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "Modifies", "1", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with no such that keyword") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "Modifies", "(", "1", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with no such that clause") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "that"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with Follows and name instead of integer for arg1") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "that", "Follows", "(", "\"sxs\"" , ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with Parent and name instead of integer for arg1") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "that", "Parent", "(", "\"sxs\"" , ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with Calls and integer instead of name for arg1") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "that", "Calls", "(", "1" , ",", "_", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse query with Calls and integer instead of name for arg2") {
    std::shared_ptr<Synonym> SYNTAX_ERROR_SYNONYM = Synonym::create(Constants::SYNTAX_ERROR, "");
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "such", "that", "Calls", "(", "_" , ",", "1", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setSelectSynonyms({SYNTAX_ERROR_SYNONYM});
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
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSuchThatClauses(
            {Clause::create(Constants::MODIFIES, Value::create("1"), Synonym::create(Constants::VARIABLE, "x"))});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a"), Clause::create(Constants::PATTERN, Value::create("x"), Wildcard::create("count")));
    expectedResObject.setPatternClauses({pair});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct complex query with pattern -> such that") {
    std::vector<std::string> queryTokens = {"variable", "x", ";", "assign", "a", ";", "Select", "a", "pattern", "a", "(", "\"x\"", ",", "_\"count\"_", ")",
                                            "such", "that", "Modifies", "(", "1", ",", "x", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::ASSIGN, "a")});
    expectedResObject.setSuchThatClauses(
            {Clause::create(Constants::MODIFIES, Value::create("1"), Synonym::create(Constants::VARIABLE, "x"))});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "a"), Clause::create(Constants::PATTERN, Value::create("x"), Wildcard::create("count")));
    expectedResObject.setPatternClauses({pair});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}

TEST_CASE("Parse correct complex query with keywords as variables") {
    std::vector<std::string> queryTokens = {"variable", "Select", ";", "assign", "pattern", ";", "Select", "Select", "pattern", "pattern", "(", "\"x\"", ",", "_\"count\"_", ")",
                                            "such", "that", "Modifies", "(", "1", ",", "Select", ")"};
    ParserResponse expectedResObject;
    expectedResObject.setDeclarations({Synonym::create(Constants::VARIABLE, "Select"), Synonym::create(Constants::ASSIGN, "pattern")});
    expectedResObject.setSelectSynonyms({Synonym::create(Constants::VARIABLE, "Select")});
    expectedResObject.setSuchThatClauses(
            {Clause::create(Constants::MODIFIES, Value::create("1"), Synonym::create(Constants::VARIABLE, "Select"))});
    PatternClausePair pair = make_pair(Synonym::create(Constants::ASSIGN, "pattern"), Clause::create(Constants::PATTERN, Value::create("x"), Wildcard::create("count")));
    expectedResObject.setPatternClauses({pair});
    ParserResponse resObj = qp.parseQueryTokens(queryTokens);

    REQUIRE(expectedResObject.compare(resObj) == true);
}