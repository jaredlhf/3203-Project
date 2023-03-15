#include<stdio.h>
#include <iostream>
#include <algorithm>
#include "FollowsStarStore.h"

FollowsStarStore::FollowsStarStore() : leftStmtStar{}, rightStmtStar{} {}

FollowsStarStore::FollowsStarStore(std::unordered_map<int, std::unordered_set<int>> leftStmtStar, std::unordered_map<int, std::unordered_set<int>> rightStmtStar) : leftStmtStar{ leftStmtStar }, rightStmtStar{ rightStmtStar } {}


void FollowsStarStore::addFollowsStar(int leftStmt, std::unordered_set<int> rightStmtLst) {
	rightStmtStar[leftStmt] = rightStmtLst;
	for (const auto& rightStmt : rightStmtLst) {
		leftStmtStar[rightStmt].emplace(leftStmt);
	}
}


std::unordered_set<int> FollowsStarStore::getLeftStar(int rightStmt) {
	if (hasRightStmt(rightStmt)) {
		return leftStmtStar[rightStmt];
	}
	else {
		return {};
	}
}

std::unordered_set<int> FollowsStarStore::getRightStar(int leftStmt) {
	if (hasLeftStmt(leftStmt)) {
		return rightStmtStar[leftStmt];
	}
	else {
		return {};
	}
}

bool FollowsStarStore::hasLeftStmt(int lineNum) {
	if (rightStmtStar.find(lineNum) != rightStmtStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool FollowsStarStore::hasRightStmt(int lineNum) {
	if (leftStmtStar.find(lineNum) != leftStmtStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> FollowsStarStore::getAllRight() {
	std::unordered_set<int> rightStmtList;
	for (const auto& [key, value] : rightStmtStar) {
		rightStmtList.insert(value.begin(), value.end());
	}
	return rightStmtList;
}

std::unordered_set<int> FollowsStarStore::getAllLeft() {
	std::unordered_set<int> leftStmtList;
	for (const auto& [key, value] : leftStmtStar) {
		leftStmtList.insert(value.begin(), value.end());
	}
	return leftStmtList;
}


