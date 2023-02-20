#include "PKB/ParentStarStore.h"

#include "catch.hpp"

SCENARIO("Populating parent star store") {
	GIVEN("New instance of parent star store") {
		ParentStarStore parentStar;

		THEN("It should start empty") {
			REQUIRE(parentStar.getAllParents().size() == 0);
			REQUIRE(parentStar.getAllChildren().size() == 0);
		}

		WHEN("One parent star is added") {
			parentStar.addParentStar(1, 2);
			parentStar.addParentStar(1, 3);
			parentStar.addParentStar(1, 4);

			THEN("Parents should be mapped to Children") {
				REQUIRE(parentStar.getChildrenStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
				REQUIRE(parentStar.getParentStar(2) == std::unordered_set<int>({ 1 }));
				REQUIRE(parentStar.getParentStar(3) == std::unordered_set<int>({ 1 }));
				REQUIRE(parentStar.getParentStar(4) == std::unordered_set<int>({ 1 }));
			}

			WHEN("Duplicate parent star is added") {
				parentStar.addParentStar(1, 2);
				parentStar.addParentStar(1, 3);
				parentStar.addParentStar(1, 4);

				THEN("Parent star store should remain the same") {
					REQUIRE(parentStar.getChildrenStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
					REQUIRE(parentStar.getParentStar(2) == std::unordered_set<int>({ 1 }));
					REQUIRE(parentStar.getParentStar(3) == std::unordered_set<int>({ 1 }));
					REQUIRE(parentStar.getParentStar(4) == std::unordered_set<int>({ 1 }));
				}
			}
		}

		WHEN("Threee parent star is added") {
			parentStar.addParentStar(1, 2);
			parentStar.addParentStar(1, 3);
			parentStar.addParentStar(1, 4);
			parentStar.addParentStar(2, 3);
			parentStar.addParentStar(2, 4);
			parentStar.addParentStar(3, 4);

			THEN("There should be 3 Parents and 3 Children") {
				REQUIRE(parentStar.getAllParents() == std::unordered_set<int>({ 1, 2, 3 }));
				REQUIRE(parentStar.getAllChildren() == std::unordered_set<int>({ 2, 3, 4 }));
			}

			THEN("Parents and Children should be mapped correctly") {
				REQUIRE(parentStar.getChildrenStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
				REQUIRE(parentStar.getChildrenStar(2) == std::unordered_set<int>({ 3, 4 }));
				REQUIRE(parentStar.getChildrenStar(3) == std::unordered_set<int>({ 4 }));

				REQUIRE(parentStar.getParentStar(2) == std::unordered_set<int>({ 1 }));
				REQUIRE(parentStar.getParentStar(3) == std::unordered_set<int>({ 1, 2 }));
				REQUIRE(parentStar.getParentStar(4) == std::unordered_set<int>({ 1, 2, 3 }));
			}
		}
	}
}

