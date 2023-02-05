#include "StatementStore.h"

#include "catch.hpp"
using namespace std;

StatementStore stmtStore;

TEST_CASE("Empty statement store") {
	unordered_set<int> output({  });

	REQUIRE(stmtStore.size() == 0);
	REQUIRE(stmtStore.getAllStmt("") == output);
}

TEST_CASE("Add one statement") {
	stmtStore.clear();
	stmtStore.addStmt("assign", 3);

	unordered_set<int> output({ 3 });

	REQUIRE(stmtStore.size() == 1);
	REQUIRE(stmtStore.getAllStmt("assign") == output);
	REQUIRE(stmtStore.checkStmt("assign"));
}

TEST_CASE("Add two same statements") {
	stmtStore.clear();
	stmtStore.addStmt("assign", 3);
	stmtStore.addStmt("assign", 5);

	unordered_set<int> output({ 3, 5 });

	REQUIRE(stmtStore.size() == 1);
	REQUIRE(stmtStore.getAllStmt("assign") == output);
	REQUIRE(stmtStore.checkStmt("assign"));
}

TEST_CASE("Add two different statements") {
	stmtStore.clear();
	stmtStore.addStmt("assign", 3);
	stmtStore.addStmt("if", 5);

	unordered_set<int> outputA({ 3 });
	unordered_set<int> outputB({ 5 });

	REQUIRE(stmtStore.size() == 2);
	REQUIRE(stmtStore.getAllStmt("assign") == outputA);
	REQUIRE(stmtStore.getAllStmt("if") == outputB);
	REQUIRE(stmtStore.checkStmt("assign"));
	REQUIRE(stmtStore.checkStmt("if"));
}

TEST_CASE("Add duplicate statement") {
	stmtStore.clear();
	stmtStore.addStmt("assign", 3);
	stmtStore.addStmt("assign", 3);

	unordered_set<int> output({ 3 });

	REQUIRE(stmtStore.size() == 1);
	REQUIRE(stmtStore.getAllStmt("assign") == output);
	REQUIRE(stmtStore.checkStmt("assign"));
}
