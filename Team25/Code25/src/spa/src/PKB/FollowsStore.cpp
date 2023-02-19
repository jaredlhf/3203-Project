#include<stdio.h>
#include <iostream>

#include "FollowsStore.h"

FollowsStore::FollowsStore() {}

void FollowsStore::addFollows(int followee, int follower) {
	followeeStore[follower] = followee;
	followerStore[followee] = follower;
}

int FollowsStore::getFollowee(int follower) {
	if (hasFollower(follower)) {
		return followeeStore[follower];
	}
	else {
		return -1;
	}
}

int FollowsStore::getFollower(int followee) {
	if (hasFollowee(followee)) {
		return followerStore[followee];
	}
	else {
		return -1;
	}
}

bool FollowsStore::hasFollowee(int lineNum) {
	if (followerStore.find(lineNum) != followerStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool FollowsStore::hasFollower(int lineNum) {
	if (followeeStore.find(lineNum) != followeeStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> FollowsStore::getAllFollowers() {
	std::unordered_set<int> followerList;
	for (const auto& [key, value] : followerStore) {
		followerList.insert(value);
	}
	return followerList;
}

std::unordered_set<int> FollowsStore::getAllFollowees() {
	std::unordered_set<int> followeeList;
	for (const auto& [key, value] : followeeStore) {
		followeeList.insert(value);
	}
	return followeeList;
}

void FollowsStore::clear() {
	followerStore.clear();
	followeeStore.clear();
}