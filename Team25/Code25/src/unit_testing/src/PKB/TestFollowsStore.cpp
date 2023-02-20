#include "PKB/FollowsStore.h"

#include "catch.hpp"



SCENARIO("Populating follows store") {
	GIVEN("New instance of follows store") {
		FollowsStore followsStore;

		THEN("It should start empty") {
			REQUIRE(followsStore.getAllFollowers().size() == 0);
			REQUIRE(followsStore.getAllFollowees().size() == 0);
		}

		WHEN("One follows is added") {
			followsStore.addFollows(1, 3);

			THEN("Followee should be mapped to follower") {
				REQUIRE(followsStore.getFollowee(3) == 1);
				REQUIRE(followsStore.getFollower(1) == 3);
			}

			WHEN("Duplicate follows is added") {
				followsStore.addFollows(1, 3);

				THEN("Follows relation should remain the same") {
					REQUIRE(followsStore.getFollowee(3) == 1);
					REQUIRE(followsStore.getFollower(1) == 3);
				}
			}
		}
		WHEN("Two follows are added") {
			followsStore.addFollows(1, 3);
			followsStore.addFollows(3, 4);

			THEN("Followees should be mapped to followers correctly") {
				REQUIRE(followsStore.getFollowee(3) == 1);
				REQUIRE(followsStore.getFollower(1) == 3);
				REQUIRE(followsStore.getFollowee(4) == 3);
				REQUIRE(followsStore.getFollower(3) == 4);
			}

			THEN("getAllFollowers method should return all followers") {
				REQUIRE(followsStore.getAllFollowers() == std::unordered_set<int>({ 3, 4 }));
			}

			THEN("getAllFollowees method should return all followees") {
				REQUIRE(followsStore.getAllFollowees() == std::unordered_set<int>({ 1, 3 }));
			}
		}
	}
}