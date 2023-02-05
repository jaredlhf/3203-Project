#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class FollowsStore {
private:
	unordered_map<int, int> followsStore;
public:
	FollowsStore();
	void addFollows(int leftLineNum, int rightLineNum);
	int getFollows(int leftLineNum);
	bool has(int constNum);
	int size();
	void clear();
};