#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "ParentStarStore.h"

ParentStarStore::ParentStarStore() : leftStmtStar{}, rightStmtStar{} {}

ParentStarStore::ParentStarStore(std::unordered_map<int, std::unordered_set<int>> leftStmtStar, std::unordered_map<int, std::unordered_set<int>> rightStmtStar) : leftStmtStar{ leftStmtStar }, rightStmtStar{ rightStmtStar } {}

void ParentStarStore::addParentStar(int leftStmt, int rightStmt) {
	rightStmtStar[leftStmt].emplace(rightStmt);
	leftStmtStar[rightStmt].emplace(leftStmt);
}

std::unordered_set<int> ParentStarStore::getLeftStar(int rightStmt) {
	if (hasRightStmt(rightStmt)) {
		return leftStmtStar[rightStmt];
	}
	else {
		return {};
	}
}

std::unordered_set<int> ParentStarStore::getRightStar(int leftStmt) {
	if (hasLeftStmt(leftStmt)) {
		return rightStmtStar[leftStmt];
	}
	else {
		return {};
	}
}

bool ParentStarStore::hasLeftStmt(int lineNum) {
	if (rightStmtStar.find(lineNum) != rightStmtStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ParentStarStore::hasRightStmt(int lineNum) {
	if (leftStmtStar.find(lineNum) != leftStmtStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> ParentStarStore::getAllRight() {
	std::unordered_set<int> rightStmtList;
	for (const auto& [key, value] : rightStmtStar) {
		rightStmtList.insert(value.begin(), value.end());
	}
	return rightStmtList;
}

std::unordered_set<int> ParentStarStore::getAllLeft() {
	std::unordered_set<int> leftStmtList;
	for (const auto& [key, value] : leftStmtStar) {
		leftStmtList.insert(value.begin(), value.end());
	}
	return leftStmtList;
}
