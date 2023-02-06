#include "PKB/FollowsStore.h"

#include "catch.hpp"
using namespace std;

FollowsStore followsStore;

TEST_CASE("Empty follows store") {
	unordered_set<int> output({ });

	REQUIRE(followsStore.getAllFollowers().size() == 0);
	REQUIRE(followsStore.getAllFollowees().size() == 0);
	REQUIRE(followsStore.getAllFollowers() == output);
	REQUIRE(followsStore.getAllFollowees() == output);

}

TEST_CASE("Add one follows") {
	followsStore.clear();
	followsStore.addFollows(1, 3);

	REQUIRE(followsStore.getFollowee(3) == 1);
	REQUIRE(followsStore.getFollower(1) == 3);
	REQUIRE(followsStore.hasFollowee(1));
	REQUIRE(followsStore.hasFollower(3));
	REQUIRE(!followsStore.hasFollowee(3));
	REQUIRE(!followsStore.hasFollower(1));
}

TEST_CASE("Add two follows") {
	followsStore.clear();
	followsStore.addFollows(1, 3);
	followsStore.addFollows(3, 4);

	REQUIRE(followsStore.getFollowee(4) == 3);
	REQUIRE(followsStore.getFollower(3) == 4);
	REQUIRE(followsStore.hasFollowee(3));
	REQUIRE(followsStore.hasFollower(3));
	REQUIRE(followsStore.hasFollower(4));
	REQUIRE(!followsStore.hasFollowee(4));
}