#include<stdio.h>
#include <iostream>

#include "FollowsStore.h"

FollowsStore::FollowsStore() : leftStmtStore{ }, rightStmtStore{ } {}
FollowsStore::FollowsStore(std::unordered_map<int, int> leftStmtStore, std::unordered_map<int, int> rightStmtStore) 
	: leftStmtStore{ leftStmtStore }, rightStmtStore{ rightStmtStore } {}

void FollowsStore::addFollows(int leftStmt, int rightStmt) {
	leftStmtStore[rightStmt] = leftStmt;
	rightStmtStore[leftStmt] = rightStmt;
}

int FollowsStore::getLeftStmt(int rightStmt) {
	if (hasRightStmt(rightStmt)) {
		return leftStmtStore[rightStmt];
	}
	else {
		return -1;
	}
}

int FollowsStore::getRightStmt(int leftStmt) {
	if (hasLeftStmt(leftStmt)) {
		return rightStmtStore[leftStmt];
	}
	else {
		return -1;
	}
}

bool FollowsStore::hasLeftStmt(int lineNum) {
	if (rightStmtStore.find(lineNum) != rightStmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool FollowsStore::hasRightStmt(int lineNum) {
	if (leftStmtStore.find(lineNum) != leftStmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> FollowsStore::getAllLeft() {
	std::unordered_set<int> leftStmtList;
	for (const auto& [key, value] : leftStmtStore) {
		leftStmtList.insert(value);
	}
	return leftStmtList;
}


std::unordered_set<int> FollowsStore::getAllRight() {
	std::unordered_set<int> rightStmtList;
	for (const auto& [key, value] : rightStmtStore) {
		rightStmtList.insert(value);
	}
	return rightStmtList;
}


void FollowsStore::clear() {
	rightStmtStore.clear();
	leftStmtStore.clear();
}