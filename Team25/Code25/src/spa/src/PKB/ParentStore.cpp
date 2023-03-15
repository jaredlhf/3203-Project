#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "ParentStore.h"

ParentStore::ParentStore() : leftStmtStore{ }, rightStmtStore{ } {}

ParentStore::ParentStore(std::unordered_map<int, int> leftStmtStore, std::unordered_map<int, std::unordered_set<int>> rightStmtStore)
	: leftStmtStore{ leftStmtStore }, rightStmtStore{ rightStmtStore } {}

void ParentStore::addParent(int leftStmt, int rightStmt) {
	leftStmtStore[rightStmt] = leftStmt;
	rightStmtStore[leftStmt].emplace(rightStmt);
}

int ParentStore::getLeftStmt(int rightStmt) {
	if (hasRightStmt(rightStmt)) {
		return leftStmtStore[rightStmt];
	}
	else {
		return -1;
	}
}

std::unordered_set<int> ParentStore::getRightStmt(int parent) {
	if (hasLeftStmt(parent)) {
		return rightStmtStore[parent];
	}
	else {
		return {};
	}
}

bool ParentStore::hasLeftStmt(int lineNum) {
	if (rightStmtStore.find(lineNum) != rightStmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ParentStore::hasRightStmt(int lineNum) {
	if (leftStmtStore.find(lineNum) != leftStmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> ParentStore::getAllLeft() {
	std::unordered_set<int> leftStmtList;
	for (const auto& [key, value] : leftStmtStore) {
		leftStmtList.insert(value);
	}
	return leftStmtList;
}

std::unordered_set<int> ParentStore::getAllRight() {
	std::unordered_set<int> rightStmtList;
	for (const auto& [key, value] : rightStmtStore) {
		rightStmtList.insert(value.begin(), value.end());
	}
	return rightStmtList;
}

