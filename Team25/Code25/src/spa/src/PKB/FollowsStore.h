#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class FollowsStore {
private:
	unordered_map<int, int> followeeStore;
	unordered_map<int, int> followerStore;
public:
	FollowsStore();
	void addFollows(int leftLineNum, int rightLineNum);
	int getFollowee(int rightLineNum);
	int getFollower(int leftLineNum);
	bool hasFollowee(int lineNum);
	bool hasFollower(int lineNum);
	bool hasFollows(int leftLineNum, int rightLineNum);
	unordered_set<int> getAllFollowers();
	unordered_set<int> getAllFollowees();
	void clear();
};