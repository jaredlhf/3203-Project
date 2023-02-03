#include "VariableStore.h"

#include "catch.hpp"
using namespace std;

VariableStore varStore;

TEST_CASE("Empty store") {
	REQUIRE(varStore.size() == 0);
}

TEST_CASE("Add one variable") {
	varStore.addVar("one");

	unordered_set<string> output({ "one" });

	REQUIRE(varStore.size() == 1);
	REQUIRE(varStore.getAllVar() == output);
	REQUIRE(varStore.checkVar("one"));
	REQUIRE(!varStore.checkVar("two"));
}

TEST_CASE("Add two variable") {
	varStore.addVar("one");
	varStore.addVar("two");

	unordered_set<string> output({ "one", "two"});

	REQUIRE(varStore.size() == 2);
	REQUIRE(varStore.getAllVar() == output);
	REQUIRE(varStore.checkVar("one"));
	REQUIRE(varStore.checkVar("two"));
}

