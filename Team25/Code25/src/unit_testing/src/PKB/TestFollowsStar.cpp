#include "PKB/FollowsStarStore.h"

#include "catch.hpp"

SCENARIO("Populating follows star store") {
	GIVEN("New instance of follows star store") {
		FollowsStarStore followsStar;

		THEN("It should start empty") {
			REQUIRE(followsStar.getAllLeft().size() == 0);
			REQUIRE(followsStar.getAllRight().size() == 0);
		}

		WHEN("One follows star is added") {
			followsStar.addFollowsStar(1, std::unordered_set<int>({ 2, 3, 4 }));

			THEN("Followee should be mapped to Followers") {
				REQUIRE(followsStar.getRightStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
				REQUIRE(followsStar.getLeftStar(2) == std::unordered_set<int>({ 1 }));
				REQUIRE(followsStar.getLeftStar(3) == std::unordered_set<int>({ 1 }));
				REQUIRE(followsStar.getLeftStar(4) == std::unordered_set<int>({ 1 }));
			}

			WHEN("Duplicate follows star is added") {
				followsStar.addFollowsStar(1, std::unordered_set<int>({ 2, 3, 4 }));

				THEN("Follows star store should remain the same") {
					REQUIRE(followsStar.getRightStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
					REQUIRE(followsStar.getLeftStar(2) == std::unordered_set<int>({ 1 }));
					REQUIRE(followsStar.getLeftStar(3) == std::unordered_set<int>({ 1 }));
					REQUIRE(followsStar.getLeftStar(4) == std::unordered_set<int>({ 1 }));
				}
			}
		}

		WHEN("Two follows star is added") {
			followsStar.addFollowsStar(1, std::unordered_set<int>({ 2, 3, 4 }));
			followsStar.addFollowsStar(2, std::unordered_set<int>({ 3, 4 }));

			THEN("There should be 2 Followees and 3 Followers") {
				REQUIRE(followsStar.getAllLeft() == std::unordered_set<int>({ 1, 2 }));
				REQUIRE(followsStar.getAllRight() == std::unordered_set<int>({ 2, 3, 4 }));
			}

			THEN("Followers and followees should be mapped correctly") {
				REQUIRE(followsStar.getRightStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
				REQUIRE(followsStar.getRightStar(2) == std::unordered_set<int>({ 3, 4 }));
				
				REQUIRE(followsStar.getLeftStar(2) == std::unordered_set<int>({ 1 }));
				REQUIRE(followsStar.getLeftStar(3) == std::unordered_set<int>({ 1, 2 }));
				REQUIRE(followsStar.getLeftStar(4) == std::unordered_set<int>({ 1, 2 }));
			}
		}
	}
}
