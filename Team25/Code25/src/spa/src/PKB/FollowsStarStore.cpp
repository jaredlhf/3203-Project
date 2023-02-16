#include<stdio.h>
#include <iostream>

#include "FollowsStarStore.h"

FollowsStarStore::FollowsStarStore() {}


void FollowsStarStore::addFollowsStar(int leftLineNum, std::unordered_set<int> lineNumLst) {
	followerStar[leftLineNum] = lineNumLst;
	for (const auto& rightLineNum : lineNumLst) {
		followeeStar[rightLineNum].emplace(leftLineNum);
	}
}


std::unordered_set<int> FollowsStarStore::getFolloweeStar(int rightLineNum) {
	if (hasFollower(rightLineNum)) {
		return followeeStar[rightLineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> FollowsStarStore::getFollowerStar(int leftLineNum) {
	if (hasFollowee(leftLineNum)) {
		return followerStar[leftLineNum];
	}
	else {
		return {};
	}
}
bool FollowsStarStore::hasFollowee(int lineNum) {
	if (followerStar.find(lineNum) != followerStar.end()) {
		return true;
	}
	else {
		return false;
	}
}
bool FollowsStarStore::hasFollower(int lineNum) {
	if (followeeStar.find(lineNum) != followeeStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> FollowsStarStore::getAllFollowers() {
	std::unordered_set<int> followerList;
	for (const auto& [key, value] : followerStar) {
		followerList.insert(value.begin(), value.end());
	}
	return followerList;
}

std::unordered_set<int> FollowsStarStore::getAllFollowees() {
	std::unordered_set<int> followeeList;
	for (const auto& [key, value] : followeeStar) {
		followeeList.insert(value.begin(), value.end());
	}
	return followeeList;
}


void FollowsStarStore::clear() {
	followeeStar.clear();
	followerStar.clear();
}
