#include <string>
#include <unordered_set>
#include "QPS/Constants/Synonym.h"
#include "QPS/Constants/Constants.h"
#include "catch.hpp"

using namespace std;

// TESTS FOR ENTITY OVERRIDEN FUNCTIONS
TEST_CASE("Synonym classes return the right values for Entity parent class virtual functions") {
	CallSynonym cl("cll");
	ProcedureSynonym pr("cll");
	StmtSynonym st("cll");
	REQUIRE(cl.isSynonym() == true);
	REQUIRE(pr.isConstant() == false);
	REQUIRE(st.isWildcard() == false);
	REQUIRE(Synonym::create(Constants::ASSIGN, "a")->isSynonym() == true);
	REQUIRE(Synonym::create(Constants::ASSIGN, "a")->isConstant() == false);
	REQUIRE(Synonym::create(Constants::ASSIGN, "a")->isWildcard() == false);
}

// TESTS FOR BASE SYNONYM CLASS FUNCTIONS
TEST_CASE("Synonym name matches given name works correctly") {
	CallSynonym cl("cll");
	REQUIRE(cl.matchesName("cll") == true);
}

TEST_CASE("Synonym name does not match different name") {
	ProcedureSynonym cl("cll");
	REQUIRE(cl.matchesName("clo") == false);
}

TEST_CASE("Adding non-duplicate results returns the correct set") {
	ProcedureSynonym cl("cll");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v1");

	REQUIRE(cl.getMatches() == unordered_set<string>({"v", "v1"}));
}

TEST_CASE("Adding duplicate results returns the correct set") {
	ProcedureSynonym cl("cll");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v1");
	cl.addMatchingResult("v");

	REQUIRE(cl.getMatches() == unordered_set<string>({ "v", "v1" }));
}

TEST_CASE("Adding results to set will NOT match with different set") {
	ProcedureSynonym cl("cll");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v1");
	cl.addMatchingResult("v");

	REQUIRE(cl.getMatches() != unordered_set<string>({ "c", "v1" }));
}

TEST_CASE("Compare function returns the right results for Synonyms of the same type and name") {
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->compare(Synonym::create(Constants::ASSIGN, "x")) == true);
	REQUIRE(Synonym::create(Constants::CALL, "x")->compare(Synonym::create(Constants::CALL, "x")) == true);
}

TEST_CASE("Compare function returns false for Synonyms of different type") {
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->compare(Synonym::create(Constants::ASSIGN, "x")) == false);
	REQUIRE(Synonym::create(Constants::CALL, "x")->compare(Synonym::create(Constants::PROCEDURE, "x")) == false);
}

TEST_CASE("Compare function returns false for Synonyms of different name") {
	REQUIRE(Synonym::create(Constants::ASSIGN, "y")->compare(Synonym::create(Constants::ASSIGN, "x")) == false);
	REQUIRE(Synonym::create(Constants::CALL, "x")->compare(Synonym::create(Constants::CALL, "y")) == false);
}



// TESTS FOR STATIC SYNONYM CLASS FUNCTIONS
TEST_CASE("create function creates the right classes based on the keywords passed in") {
	REQUIRE(Synonym::create(Constants::STMT, "x")->matchesKeyword(Constants::STMT));
	REQUIRE(Synonym::create(Constants::READ, "x")->matchesKeyword(Constants::READ));
	REQUIRE(Synonym::create(Constants::PRINT, "x")->matchesKeyword(Constants::PRINT));
	REQUIRE(Synonym::create(Constants::CALL, "x")->matchesKeyword(Constants::CALL));
	REQUIRE(Synonym::create(Constants::WHILE, "x")->matchesKeyword(Constants::WHILE));
	REQUIRE(Synonym::create(Constants::IF, "x")->matchesKeyword(Constants::IF));
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->matchesKeyword(Constants::ASSIGN));
	REQUIRE(Synonym::create(Constants::VARIABLE, "x")->matchesKeyword(Constants::VARIABLE));
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->matchesKeyword(Constants::CONSTANT));
	REQUIRE(Synonym::create(Constants::PROCEDURE, "x")->matchesKeyword(Constants::PROCEDURE));
}


// TESTS FOR POLYMORPHIC FUNCTIONS IN CONCRETE SYNONYM CLASSES
TEST_CASE("All concrete synonym classes match the correct keywords") {
	StmtSynonym st("cll");
	ReadSynonym re("cll");
	PrintSynonym pr("cll");
	CallSynonym cl("cll");
	WhileSynonym wh("cll");
	IfSynonym i("cll");
	AssignSynonym asg("cll");
	VariableSynonym var("cll");
	ConstantSynonym cnst("cll");
	ProcedureSynonym proc("cll");

	REQUIRE(st.matchesKeyword(Constants::STMT) == true);
	REQUIRE(re.matchesKeyword(Constants::READ) == true);
	REQUIRE(pr.matchesKeyword(Constants::PRINT) == true);
	REQUIRE(cl.matchesKeyword(Constants::CALL) == true);
	REQUIRE(wh.matchesKeyword(Constants::WHILE) == true);
	REQUIRE(i.matchesKeyword(Constants::IF) == true);
	REQUIRE(asg.matchesKeyword(Constants::ASSIGN) == true);
	REQUIRE(var.matchesKeyword(Constants::VARIABLE) == true);
	REQUIRE(cnst.matchesKeyword(Constants::CONSTANT) == true);
	REQUIRE(proc.matchesKeyword(Constants::PROCEDURE) == true);
}

TEST_CASE("All concrete synonym classes returns false for the wrong keywords") {
	StmtSynonym st("cll");
	ReadSynonym re("cll");
	PrintSynonym pr("cll");
	CallSynonym cl("cll");
	WhileSynonym wh("cll");
	IfSynonym i("cll");
	AssignSynonym asg("cll");
	VariableSynonym var("cll");
	ConstantSynonym cnst("cll");
	ProcedureSynonym proc("cll");

	REQUIRE(st.matchesKeyword(Constants::READ) == false);
	REQUIRE(re.matchesKeyword(Constants::PRINT) == false);
	REQUIRE(pr.matchesKeyword(Constants::CALL) == false);
	REQUIRE(cl.matchesKeyword(Constants::WHILE) == false);
	REQUIRE(wh.matchesKeyword(Constants::IF) == false);
	REQUIRE(i.matchesKeyword(Constants::ASSIGN) == false);
	REQUIRE(asg.matchesKeyword(Constants::VARIABLE) == false);
	REQUIRE(var.matchesKeyword(Constants::CONSTANT) == false);
	REQUIRE(cnst.matchesKeyword(Constants::PROCEDURE) == false);
	REQUIRE(proc.matchesKeyword(Constants::STMT) == false);
}

TEST_CASE("All concrete synonym classes returns the right results for isStmtRef function") {
	StmtSynonym st("cll");
	ReadSynonym re("cll");
	PrintSynonym pr("cll");
	CallSynonym cl("cll");
	WhileSynonym wh("cll");
	IfSynonym i("cll");
	AssignSynonym asg("cll");
	VariableSynonym var("cll");
	ConstantSynonym cnst("cll");
	ProcedureSynonym proc("cll");

	REQUIRE(Synonym::create(Constants::STMT, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::READ, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::PRINT, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::CALL, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::WHILE, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::IF, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::VARIABLE, "x")->isStmtRef() == false);
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->isStmtRef() == false);
	REQUIRE(Synonym::create(Constants::PROCEDURE, "x")->isStmtRef() == false);
}

TEST_CASE("All concrete synonym classes returns the right results for isVariableSyn function") {
	StmtSynonym st("cll");
	ReadSynonym re("cll");
	PrintSynonym pr("cll");
	CallSynonym cl("cll");
	WhileSynonym wh("cll");
	IfSynonym i("cll");
	AssignSynonym asg("cll");
	VariableSynonym var("cll");
	ConstantSynonym cnst("cll");
	ProcedureSynonym proc("cll");

	REQUIRE(Synonym::create(Constants::STMT, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::READ, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::PRINT, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::CALL, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::WHILE, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::IF, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::VARIABLE, "x")->isVariableSyn() == true);
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::PROCEDURE, "x")->isVariableSyn() == false);
}