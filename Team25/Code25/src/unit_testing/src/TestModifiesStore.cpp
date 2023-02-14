#include "PKB/ModifiesStore.h"

#include "catch.hpp"
using namespace std;

ModifiesStore modStore;

/*
TEST_CASE("Empty mod store") {
	unordered_set<int> outputStmt({ });
	unordered_set<string> outputVar({ });
	
	modStore.clear();

	REQUIRE(modStore.getAllStmt() == outputStmt);
	REQUIRE(modStore.getAllVar() == outputVar);
}*/
/*
TEST_CASE("Add one mod") {
	unordered_set<int> outputStmt({ 2 });
	string outputVarA = "x";
	unordered_set<string> outputVarB({ "x" });
	
	modStore.clear();
	modStore.add(2, "x");

	REQUIRE(modStore.getVar(2) == outputVarA);
	REQUIRE(modStore.getStmt("x") == outputStmt);
	REQUIRE(modStore.hasVar("x"));
	REQUIRE(modStore.hasStmt(2));
	REQUIRE(modStore.getAllStmt() == outputStmt);
	REQUIRE(modStore.getAllVar() == outputVarB);
}

TEST_CASE("Add two mod") {
	unordered_set<int> outputStmt({ 2 });
	string outputVarA({ "y" });
	unordered_set<string> outputVarB({ "x", "y"});

	modStore.clear();
	modStore.add(2, "x");
	modStore.add(2, "y");
	modStore.add(3, "y");

	REQUIRE(modStore.getVar(2) == outputVarA);
	REQUIRE(modStore.getStmt("x") == outputStmt);
	REQUIRE(modStore.getStmt("y") == outputStmt);
	REQUIRE(modStore.hasVar("x"));
	REQUIRE(modStore.hasVar("y"));
	REQUIRE(modStore.hasStmt(2));
	REQUIRE(modStore.getAllStmt() == outputStmt);
	REQUIRE(modStore.getAllVar() == outputVarB);
}

TEST_CASE("Add multiple modifies") {
	unordered_set<int> outputStmtA({ 2, 3 });
	unordered_set<int> outputStmtB({ 2 });
	unordered_set<int> outputStmtC({ 3 });
	string outputVarA = "y" ;
	unordered_set<string> outputVarB({ "x","v" });
	unordered_set<string> outputVarC({ "x","y","v" });

	modStore.clear();
	modStore.add(2, "x");
	modStore.add(2, "y");
	modStore.add(3, "v");
	modStore.add(3, "x");

	REQUIRE(modStore.getVar(2) == outputVarA);
	REQUIRE(modStore.getStmt("x") == outputStmtA);
	REQUIRE(modStore.getStmt("y") == outputStmtB);
	REQUIRE(modStore.hasVar("x"));
	REQUIRE(modStore.hasVar("y"));
	REQUIRE(modStore.hasVar("v"));
	REQUIRE(modStore.hasStmt(2));
	REQUIRE(modStore.hasStmt(3));
	REQUIRE(modStore.getAllStmt() == outputStmtA);
	REQUIRE(modStore.getAllVar() == outputVarC);
}*/
