#include "PKB/UsesStore.h"

#include "catch.hpp"
using namespace std;

UsesStore usesStore;

TEST_CASE("Empty uses store") {
	unordered_set<int> outputStmt({ });
	unordered_set<string> outputVar({ });

	usesStore.clear();

	REQUIRE(usesStore.getAllStmt() == outputStmt);
	REQUIRE(usesStore.getAllVar() == outputVar);
}

TEST_CASE("Add one uses") {
	unordered_set<int> outputStmt({ 2 });
	unordered_set<string> outputVar({ "x" });

	usesStore.clear();
	usesStore.add(2, "x");

	REQUIRE(usesStore.getVar(2) == outputVar);
	REQUIRE(usesStore.getStmt("x") == outputStmt);
	REQUIRE(usesStore.hasVar("x"));
	REQUIRE(usesStore.hasStmt(2));
	REQUIRE(usesStore.getAllStmt() == outputStmt);
	REQUIRE(usesStore.getAllVar() == outputVar);
}

TEST_CASE("Add multiple uses") {
	unordered_set<int> outputStmtA({ 2, 3 });
	unordered_set<int> outputStmtB({ 2 });
	unordered_set<int> outputStmtC({ 3 });
	unordered_set<string> outputVarA({ "x","y" });
	unordered_set<string> outputVarB({ "x","v" });
	unordered_set<string> outputVarC({ "x","y","v"});

	usesStore.clear();
	usesStore.add(2, "x");
	usesStore.add(2, "y");
	usesStore.add(3, "v");
	usesStore.add(3, "x");

	REQUIRE(usesStore.getVar(2) == outputVarA);
	REQUIRE(usesStore.getStmt("x") == outputStmtA);
	REQUIRE(usesStore.getStmt("y") == outputStmtB);
	REQUIRE(usesStore.getStmt("v") == outputStmtC);
	REQUIRE(usesStore.hasVar("x"));
	REQUIRE(usesStore.hasVar("y"));
	REQUIRE(usesStore.hasVar("v"));
	REQUIRE(usesStore.hasStmt(2));
	REQUIRE(usesStore.hasStmt(3));
	REQUIRE(usesStore.getAllStmt() == outputStmtA);
	REQUIRE(usesStore.getAllVar() == outputVarC);
}