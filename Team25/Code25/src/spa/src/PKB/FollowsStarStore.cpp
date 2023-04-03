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
	if (leftStmtStar.find(rightStmt) != leftStmtStar.end()) {
		return leftStmtStar[rightStmt];
	}
	else {
		return {};
	}
}

std::unordered_set<int> FollowsStarStore::getRightStar(int leftStmt) {
	if (rightStmtStar.find(leftStmt) != rightStmtStar.end()) {
		return rightStmtStar[leftStmt];
	}
	else {
		return {};
	}
}



