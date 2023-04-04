#include<stdio.h>
#include <iostream>

#include "NextStore.h"

NextStore::NextStore() : leftStmtStore{ }, rightStmtStore{ } {}
NextStore::NextStore(std::unordered_map<int, std::unordered_set<int>> leftStmtStore, std::unordered_map<int, std::unordered_set<int>> rightStmtStore)
	: leftStmtStore{ leftStmtStore }, rightStmtStore{ rightStmtStore } {}

void NextStore::addNext(int leftStmt, int rightStmt) {
	leftStmtStore[rightStmt].emplace(leftStmt);
	rightStmtStore[leftStmt].emplace(rightStmt);
}

std::unordered_set<int> NextStore::getLeftStmt(int rightStmt) {
	if (leftStmtStore.find(rightStmt) != leftStmtStore.end()) {
		return leftStmtStore[rightStmt];
	}
	else {
		return {};
	}
}

std::unordered_set<int> NextStore::getRightStmt(int leftStmt) {
	if (rightStmtStore.find(leftStmt) != rightStmtStore.end()) {
		return rightStmtStore[leftStmt];
	}
	else {
		return {};
	}
}


std::unordered_set<int> NextStore::getAllLeft() {
	std::unordered_set<int> leftStmtList;
	for (const auto& [key, value] : leftStmtStore) {
		leftStmtList.insert(value.begin(), value.end());
	}
	return leftStmtList;
}


std::unordered_set<int> NextStore::getAllRight() {
	std::unordered_set<int> rightStmtList;
	for (const auto& [key, value] : rightStmtStore) {
		rightStmtList.insert(value.begin(), value.end());
	}
	return rightStmtList;
}

std::unordered_set<int> NextStore::getRightStmtStar(int leftStmt) {
	std::unordered_set<int> rightStmtList;
	std::shared_ptr<std::unordered_set<int>> visited = std::make_shared<std::unordered_set<int>>();
	std::unordered_set<int> initialValues = getRightStmt(leftStmt);
	std::vector<int> visitList;
	visitList.insert(visitList.end(), initialValues.begin(), initialValues.end());
	rightStmtList.insert(initialValues.begin(), initialValues.end());

	while (visitList.size() > 0) {
		int curr = visitList[0];
		visitList.erase(visitList.begin());
		rightStmtList.insert(curr);
		if (std::find(visited->begin(), visited->end(), curr) == visited->end()) {
			std::unordered_set<int> results = getRightStmt(curr);
			for (int res : results) {
				if (std::find(visited->begin(), visited->end(), curr) == visited->end()) {
					visitList.push_back(res);
				}
			}

			rightStmtList.insert(results.begin(), results.end());
		}
		visited->insert(curr);
	}
	return rightStmtList;
}

std::unordered_set<int> NextStore::getLeftStmtStar(int rightStmt) {
	std::unordered_set<int> leftStmtList;
	std::shared_ptr<std::unordered_set<int>> visited = std::make_shared<std::unordered_set<int>>();
	std::unordered_set<int> initialValues = getLeftStmt(rightStmt);
	std::vector<int> visitList;
	visitList.insert(visitList.end(), initialValues.begin(), initialValues.end());
	leftStmtList.insert(initialValues.begin(), initialValues.end());

	while (visitList.size() > 0) {
		int curr = visitList[0];
		visitList.erase(visitList.begin());
		leftStmtList.insert(curr);
		if (std::find(visited->begin(), visited->end(), curr) == visited->end()) {
			std::unordered_set<int> results = getLeftStmt(curr);
			for (int res : results) {
				if (std::find(visited->begin(), visited->end(), curr) == visited->end()) {
					visitList.push_back(res);
				}
			}

			leftStmtList.insert(results.begin(), results.end());
		}
		visited->insert(curr);
	}
	return leftStmtList;
}