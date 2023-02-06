#include "PKB/ConstantStore.h"

#include "catch.hpp"
using namespace std;

ConstantStore constStore;

TEST_CASE("Empty constant store") {
	unordered_set<int> output({ });

	REQUIRE(constStore.size() == 0);
	REQUIRE(constStore.getAllConst() == output);
}

TEST_CASE("Add one constant") {
	constStore.clear();
	constStore.addConst(1);

	unordered_set<int> output({ 1 });

	REQUIRE(constStore.size() == 1);
	REQUIRE(constStore.getAllConst() == output);
	REQUIRE(constStore.has(1));
	REQUIRE(!constStore.has(2));
}

TEST_CASE("Add two constants") {
	constStore.clear();
	constStore.addConst(1);
	constStore.addConst(2);

	unordered_set<int> output({ 1, 2 });

	REQUIRE(constStore.size() == 2);
	REQUIRE(constStore.getAllConst() == output);
	REQUIRE(constStore.has(1));
	REQUIRE(constStore.has(2));
}

TEST_CASE("Add duplicate constant") {
	constStore.clear();
	constStore.addConst(1);
	constStore.addConst(1);

	unordered_set<int> output({ 1 });

	REQUIRE(constStore.size() == 1);
	REQUIRE(constStore.getAllConst() == output);
	REQUIRE(constStore.has(1));
}
