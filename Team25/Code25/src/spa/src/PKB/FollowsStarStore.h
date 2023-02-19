#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

/* Storage class for Follows* relationship between direct and indirect statements.
In Follows*(s1, s2), Followee star is s1 and Follower star is s2 */
class FollowsStarStore {
private:
	std::unordered_map<int, std::unordered_set<int>> followeeStar;
	std::unordered_map<int, std::unordered_set<int>> followerStar;
public:
	FollowsStarStore();
	void addFollowsStar(int followee, std::unordered_set<int> followerLst);
	std::unordered_set<int> getFolloweeStar(int follower);
	std::unordered_set<int> getFollowerStar(int followee);
	bool hasFollowee(int lineNum);
	bool hasFollower(int lineNum);
	std::unordered_set<int> getAllFollowers();
	std::unordered_set<int> getAllFollowees();
	
	void clear();
};
