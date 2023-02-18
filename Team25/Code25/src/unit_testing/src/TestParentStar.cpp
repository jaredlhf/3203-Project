#include "PKB/ParentStarStore.h"

#include "catch.hpp"
using namespace std;

ParentStarStore parentStar;

TEST_CASE("Empty parent star store") {
	unordered_set<int> output({ });
	parentStar.clear();
	REQUIRE(parentStar.getAllChildren().size() == 0);
	REQUIRE(parentStar.getAllParents().size() == 0);
	REQUIRE(parentStar.getAllChildren() == output);
	REQUIRE(parentStar.getAllParents() == output);

}

TEST_CASE("Add one parent star") {

	parentStar.clear();
	std::unordered_set<int> parentLst({ 1 });
	std::unordered_set<int> childrenLst({ 2, 3, 4 });
	parentStar.addParentStar(1, childrenLst);
	

	REQUIRE(parentStar.getParentStar(2) == parentLst);
	REQUIRE(parentStar.getChildrenStar(1) == childrenLst);
	REQUIRE(parentStar.hasParent(1));
	REQUIRE(parentStar.hasChildren(3));
	REQUIRE(!parentStar.hasParent(3));
	REQUIRE(!parentStar.hasChildren(1));
	REQUIRE(parentStar.getAllChildren() == childrenLst);
}

TEST_CASE("Add two parent star") {
	parentStar.clear();
	std::unordered_set<int> parentLstA({ 1 });
	std::unordered_set<int> childrenLstA({ 2, 3, 4 });
	std::unordered_set<int> parentLstB({ 1, 2 });
	std::unordered_set<int> childrenLstB({ 3, 4 });
	parentStar.addParentStar(1, childrenLstA);
	parentStar.addParentStar(2, childrenLstB);

	REQUIRE(parentStar.getParentStar(3) == parentLstB);
	REQUIRE(parentStar.getChildrenStar(2) == childrenLstB);
	REQUIRE(parentStar.hasParent(2));
	REQUIRE(parentStar.hasChildren(3));
	REQUIRE(parentStar.hasChildren(4));
	REQUIRE(!parentStar.hasParent(4));
}
