#include "PKB/ModifiesStore.h"

#include "catch.hpp"
using namespace std;

ModifiesStore modifiesStore;

TEST_CASE("Empty modifies store") {
	unordered_set<int> outputStmt({ });
	unordered_set<string> outputVar({ });
	
	modifiesStore.clear();

	REQUIRE(modifiesStore.getAllModStmt() == outputStmt);
	REQUIRE(modifiesStore.getAllModVar() == outputVar);
}

TEST_CASE("Add one modifies") {
	unordered_set<int> outputStmt({ 2 });
	unordered_set<string> outputVar({ "x" });
	
	modifiesStore.clear();
	modifiesStore.addModifies(2, "x");

	REQUIRE(modifiesStore.getModVar(2) == outputVar);
	REQUIRE(modifiesStore.getModStmt("x") == outputStmt);
	REQUIRE(modifiesStore.hasModVar("x"));
	REQUIRE(modifiesStore.hasModStmt(2));
	REQUIRE(modifiesStore.getAllModStmt() == outputStmt);
	REQUIRE(modifiesStore.getAllModVar() == outputVar);
}

TEST_CASE("Add two modifies") {
	unordered_set<int> outputStmt({ 2 });
	unordered_set<string> outputVar({ "x","y" });

	modifiesStore.clear();
	modifiesStore.addModifies(2, "x");
	modifiesStore.addModifies(2, "y");

	REQUIRE(modifiesStore.getModVar(2) == outputVar);
	REQUIRE(modifiesStore.getModStmt("x") == outputStmt);
	REQUIRE(modifiesStore.getModStmt("y") == outputStmt);
	REQUIRE(modifiesStore.hasModVar("x"));
	REQUIRE(modifiesStore.hasModVar("y"));
	REQUIRE(modifiesStore.hasModStmt(2));
	REQUIRE(modifiesStore.getAllModStmt() == outputStmt);
	REQUIRE(modifiesStore.getAllModVar() == outputVar);
}

TEST_CASE("Add multiple modifies") {
	unordered_set<int> outputStmtA({ 2, 3 });
	unordered_set<int> outputStmtB({ 2 });
	unordered_set<int> outputStmtC({ 3 });
	unordered_set<string> outputVarA({ "x","y"});
	unordered_set<string> outputVarB({ "x","v" });
	unordered_set<string> outputVarC({ "x","y","v" });

	modifiesStore.clear();
	modifiesStore.addModifies(2, "x");
	modifiesStore.addModifies(2, "y");
	modifiesStore.addModifies(3, "v");
	modifiesStore.addModifies(3, "x");

	REQUIRE(modifiesStore.getModVar(2) == outputVarA);
	REQUIRE(modifiesStore.getModStmt("x") == outputStmtA);
	REQUIRE(modifiesStore.getModStmt("y") == outputStmtB);
	REQUIRE(modifiesStore.hasModVar("x"));
	REQUIRE(modifiesStore.hasModVar("y"));
	REQUIRE(modifiesStore.hasModVar("v"));
	REQUIRE(modifiesStore.hasModStmt(2));
	REQUIRE(modifiesStore.hasModStmt(3));
	REQUIRE(modifiesStore.getAllModStmt() == outputStmtA);
	REQUIRE(modifiesStore.getAllModVar() == outputVarC);
}