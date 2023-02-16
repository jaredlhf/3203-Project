#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>


class FollowsStore {
private:
	std::unordered_map<int, int> followeeStore;
	std::unordered_map<int, int> followerStore;
public:
	FollowsStore();
	void addFollows(int leftLineNum, int rightLineNum);
	int getFollowee(int rightLineNum);
	int getFollower(int leftLineNum);
	bool hasFollowee(int lineNum);
	bool hasFollower(int lineNum);
	std::unordered_set<int> getAllFollowers();
	std::unordered_set<int> getAllFollowees();
	void clear();
};