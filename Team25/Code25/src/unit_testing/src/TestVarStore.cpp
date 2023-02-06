#include "PKB/VariableStore.h"

#include "catch.hpp"
using namespace std;

VariableStore varStore;

TEST_CASE("Empty variable store") {
	unordered_set<string> output({  });

	REQUIRE(varStore.size() == 0);
	REQUIRE(varStore.getAllVar() == output);
}

TEST_CASE("Add one variable") {
	varStore.clear();
	varStore.addVar("one");

	unordered_set<string> output({ "one"});

	REQUIRE(varStore.size() == 1);
	REQUIRE(varStore.getAllVar() == output);
	REQUIRE(varStore.has("one"));
	REQUIRE(!varStore.has("two"));
}

TEST_CASE("Add two variable") {
	varStore.clear();
	varStore.addVar("one");
	varStore.addVar("two");

	unordered_set<string> output({ "one", "two"});

	REQUIRE(varStore.size() == 2);
	REQUIRE(varStore.getAllVar() == output);
	REQUIRE(varStore.has("one"));
	REQUIRE(varStore.has("two"));
}

TEST_CASE("Add duplicate variable") {
	varStore.clear();
	varStore.addVar("one");
	varStore.addVar("one");

	unordered_set<string> output({ "one" });

	REQUIRE(varStore.size() == 1);
	REQUIRE(varStore.getAllVar() == output);
	REQUIRE(varStore.has("one"));
}
