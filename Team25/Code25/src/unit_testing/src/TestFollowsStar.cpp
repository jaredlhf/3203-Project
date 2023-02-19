#include "PKB/FollowsStarStore.h"

#include "catch.hpp"

SCENARIO("Populating follows star store") {
	GIVEN("New instance of follows star store") {
		FollowsStarStore followsStar;

		THEN("It should start empty") {
			REQUIRE(followsStar.getAllFollowees().size() == 0);
			REQUIRE(followsStar.getAllFollowers().size() == 0);
		}

		WHEN("One follows star is added") {
			followsStar.addFollowsStar(1, std::unordered_set<int>({ 2, 3, 4 }));

			THEN("Followee should be mapped to Followers") {
				REQUIRE(followsStar.getFollowerStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
				REQUIRE(followsStar.getFolloweeStar(2) == std::unordered_set<int>({ 1 }));
				REQUIRE(followsStar.getFolloweeStar(3) == std::unordered_set<int>({ 1 }));
				REQUIRE(followsStar.getFolloweeStar(4) == std::unordered_set<int>({ 1 }));
			}

			WHEN("Duplicate follows star is added") {
				followsStar.addFollowsStar(1, std::unordered_set<int>({ 2, 3, 4 }));

				THEN("Follows star store should remain the same") {
					REQUIRE(followsStar.getFollowerStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
					REQUIRE(followsStar.getFolloweeStar(2) == std::unordered_set<int>({ 1 }));
					REQUIRE(followsStar.getFolloweeStar(3) == std::unordered_set<int>({ 1 }));
					REQUIRE(followsStar.getFolloweeStar(4) == std::unordered_set<int>({ 1 }));
				}
			}
		}

		WHEN("Two follows star is added") {
			followsStar.addFollowsStar(1, std::unordered_set<int>({ 2, 3, 4 }));
			followsStar.addFollowsStar(2, std::unordered_set<int>({ 3, 4 }));

			THEN("There should be 2 Followees and 3 Followers") {
				REQUIRE(followsStar.getAllFollowees() == std::unordered_set<int>({ 1, 2 }));
				REQUIRE(followsStar.getAllFollowers() == std::unordered_set<int>({ 2, 3, 4 }));
			}

			THEN("Followers and followees should be mapped correctly") {
				REQUIRE(followsStar.getFollowerStar(1) == std::unordered_set<int>({ 2, 3, 4 }));
				REQUIRE(followsStar.getFollowerStar(2) == std::unordered_set<int>({ 3, 4 }));
				
				REQUIRE(followsStar.getFolloweeStar(2) == std::unordered_set<int>({ 1 }));
				REQUIRE(followsStar.getFolloweeStar(3) == std::unordered_set<int>({ 1, 2 }));
				REQUIRE(followsStar.getFolloweeStar(4) == std::unordered_set<int>({ 1, 2 }));
			}
		}
	}
}
