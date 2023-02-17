#include "PKB/ParentStore.h"

#include "catch.hpp"
using namespace std;

ParentStore parentStore;

TEST_CASE("Empty parent store") {
	unordered_set<int> output({ });
	parentStore.clear();
	REQUIRE(parentStore.getAllChildren().size() == 0);
	REQUIRE(parentStore.getAllParents().size() == 0);
	REQUIRE(parentStore.getAllChildren() == output);
	REQUIRE(parentStore.getAllParents() == output);

}

TEST_CASE("Add one parent") {
	parentStore.clear();
	parentStore.addParent(1, 3);
	unordered_set<int> outputA({ 3 });
	unordered_set<int> outputB({ 1 });

	REQUIRE(parentStore.getParent(3) == 1);
	REQUIRE(parentStore.getChildren(1) == outputA);
	REQUIRE(parentStore.hasParent(1));
	REQUIRE(parentStore.hasChildren(3));
	REQUIRE(!parentStore.hasParent(3));
	REQUIRE(!parentStore.hasChildren(1));
	REQUIRE(parentStore.getAllChildren() == outputA);
	REQUIRE(parentStore.getAllParents() == outputB);
}

TEST_CASE("Add two parents") {
	parentStore.clear();
	parentStore.addParent(1, 3);
	parentStore.addParent(3, 4);
	unordered_set<int> outputA({ 3 });
	unordered_set<int> outputB({ 4 });
	unordered_set<int> outputC({ 3,4 });
	unordered_set<int> outputD({ 1,3 });

	REQUIRE(parentStore.getParent(4) == 3);
	REQUIRE(parentStore.getChildren(3) == outputB);
	REQUIRE(parentStore.hasParent(3));
	REQUIRE(parentStore.hasChildren(3));
	REQUIRE(parentStore.hasChildren(4));
	REQUIRE(!parentStore.hasParent(4));
	REQUIRE(parentStore.getAllChildren() == outputC);
	REQUIRE(parentStore.getAllParents() == outputD);
}

TEST_CASE("Add duplicate parents") {
	parentStore.clear();
	parentStore.addParent(1, 3);
	parentStore.addParent(1, 3);
	unordered_set<int> outputA({ 3 });
	unordered_set<int> outputB({ 1 });

	REQUIRE(parentStore.getParent(3) == 1);
	REQUIRE(parentStore.getChildren(1) == outputA);
	REQUIRE(parentStore.hasParent(1));
	REQUIRE(parentStore.hasChildren(3));
	REQUIRE(!parentStore.hasParent(3));
	REQUIRE(!parentStore.hasChildren(1));
	REQUIRE(parentStore.getAllChildren() == outputA);
	REQUIRE(parentStore.getAllParents() == outputB);
}