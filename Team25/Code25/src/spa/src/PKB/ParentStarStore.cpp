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
	if (leftStmtStar.find(rightStmt) != leftStmtStar.end()) {
		return leftStmtStar[rightStmt];
	}
	else {
		return {};
	}
}

std::unordered_set<int> ParentStarStore::getRightStar(int leftStmt) {
	if (rightStmtStar.find(leftStmt) != rightStmtStar.end()) {
		return rightStmtStar[leftStmt];
	}
	else {
		return {};
	}
}

