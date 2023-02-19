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


TEST_CASE("Add parent star") {
	parentStar.clear();
	std::unordered_set<int> parentLstA({ 1 });
	std::unordered_set<int> childrenLstA({ 2, 3, 4 });
	std::unordered_set<int> parentLstB({ 1, 2 });
	std::unordered_set<int> childrenLstB({ 3, 4 });
	parentStar.addParentStar(1, 2);
	parentStar.addParentStar(1, 3);
	parentStar.addParentStar(1, 4);
	parentStar.addParentStar(2, 3);
	parentStar.addParentStar(2, 4);
	parentStar.addParentStar(3, 4);

	REQUIRE(parentStar.getParentStar(2) == parentLstA);
	REQUIRE(parentStar.getChildrenStar(1) == childrenLstA);
	REQUIRE(parentStar.getParentStar(3) == parentLstB);
	REQUIRE(parentStar.getChildrenStar(2) == childrenLstB);
	REQUIRE(parentStar.hasParent(2));
	REQUIRE(parentStar.hasChildren(3));
	REQUIRE(parentStar.hasChildren(4));
	REQUIRE(!parentStar.hasParent(4));
}
