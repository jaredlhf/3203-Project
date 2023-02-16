#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>


class FollowsStarStore {
private:
	std::unordered_map<int, std::unordered_set<int>> followeeStar;
	std::unordered_map<int, std::unordered_set<int>> followerStar;
public:
	FollowsStarStore();
	void addFollowsStar(int leftLineNum, std::unordered_set<int> lineNumLst);
	std::unordered_set<int> getFolloweeStar(int rightLineNum);
	std::unordered_set<int> getFollowerStar(int leftLineNum);
	bool hasFollowee(int lineNum);
	bool hasFollower(int lineNum);
	bool hasFollows(int leftLineNum, int rightLineNum);
	std::unordered_set<int> getAllFollowers();
	std::unordered_set<int> getAllFollowees();
	
	void clear();
};
