#include "PKB/FollowsStarStore.h"

#include "catch.hpp"
using namespace std;

FollowsStarStore followsStar;

TEST_CASE("Empty follows star store") {
	unordered_set<int> output({ });
	followsStar.clear();
	REQUIRE(followsStar.getAllFollowers().size() == 0);
	REQUIRE(followsStar.getAllFollowees().size() == 0);
	REQUIRE(followsStar.getAllFollowers() == output);
	REQUIRE(followsStar.getAllFollowees() == output);

}

TEST_CASE("Add one follows star") {
	
	followsStar.clear();
	std::unordered_set<int> followeeLst({ 1 });
	std::unordered_set<int> followerLst({ 2, 3, 4 });
	followsStar.addFollowsStar(1, followerLst);

	REQUIRE(followsStar.getFolloweeStar(2) == followeeLst);
	REQUIRE(followsStar.getFollowerStar(1) == followerLst);
	REQUIRE(followsStar.hasFollowee(1));
	REQUIRE(followsStar.hasFollower(3));
	REQUIRE(!followsStar.hasFollowee(3));
	REQUIRE(!followsStar.hasFollower(1));
	REQUIRE(followsStar.getAllFollowers() == followerLst);
}

TEST_CASE("Add two follows star") {
	followsStar.clear();
	std::unordered_set<int> followeeLstA({ 1 });
	std::unordered_set<int> followerLstA({ 2, 3, 4 });
	std::unordered_set<int> followeeLstB({ 1, 2 });
	std::unordered_set<int> followerLstB({ 3, 4 });
	followsStar.addFollowsStar(1, followerLstA);
	followsStar.addFollowsStar(2, followerLstB);

	REQUIRE(followsStar.getFolloweeStar(3) == followeeLstB);
	REQUIRE(followsStar.getFollowerStar(2) == followerLstB);
	REQUIRE(followsStar.hasFollowee(2));
	REQUIRE(followsStar.hasFollower(3));
	REQUIRE(followsStar.hasFollower(4));
	REQUIRE(!followsStar.hasFollowee(4));
}
