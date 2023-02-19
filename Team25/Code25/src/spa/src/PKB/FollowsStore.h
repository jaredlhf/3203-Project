#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

/* Storage class for Follows relationship between two statements. 
In Follows(s1, s2), Followees are s1 and Followers are s2.*/
class FollowsStore {
private:
	std::unordered_map<int, int> followeeStore;
	std::unordered_map<int, int> followerStore;
public:
	FollowsStore();
	void addFollows(int followee, int follower);
	int getFollowee(int follower);
	int getFollower(int followee);
	bool hasFollowee(int lineNum);
	bool hasFollower(int lineNum);
	std::unordered_set<int> getAllFollowers();
	std::unordered_set<int> getAllFollowees();
	void clear();
};