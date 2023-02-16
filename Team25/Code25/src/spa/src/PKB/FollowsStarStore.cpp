#include<stdio.h>
#include <iostream>

#include "FollowsStarStore.h"

FollowsStarStore::FollowsStarStore() {}


void FollowsStarStore::addFollowsStar(int followee, std::unordered_set<int> followerLst) {
	followerStar[followee] = followerLst;
	for (const auto& follower : followerLst) {
		followeeStar[follower].emplace(followee);
	}
}


std::unordered_set<int> FollowsStarStore::getFolloweeStar(int follower) {
	if (hasFollower(follower)) {
		return followeeStar[follower];
	}
	else {
		return {};
	}
}

std::unordered_set<int> FollowsStarStore::getFollowerStar(int followee) {
	if (hasFollowee(followee)) {
		return followerStar[followee];
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
