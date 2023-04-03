#include "PKB/FollowsStarStore.h"

#include "catch.hpp"

SCENARIO("Populating follows star store") {
	GIVEN("New instance of follows star store") {
		FollowsStarStore followsStar;

		WHEN("No follows star is added") {
			THEN("Get method should return empty") {
				REQUIRE(followsStar.getRightStar(1) == std::unordered_set<int>());
				REQUIRE(followsStar.getLeftStar(2) == std::unordered_set<int>());
			}
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
