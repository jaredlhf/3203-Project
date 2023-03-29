#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "ContainCallsStore.h"

ContainCallsStore::ContainCallsStore() : procStore{}, stmtStore{} {}
ContainCallsStore::ContainCallsStore(std::unordered_map<int, std::unordered_set<std::string>> procStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore)
	: procStore{ procStore }, stmtStore{ stmtStore } {}

void ContainCallsStore::addContainCall(int lineNum, std::string procName) {
	procStore[lineNum].emplace(procName);
	stmtStore[procName].emplace(lineNum);
}

std::unordered_set<std::string> ContainCallsStore::getProc(int lineNum) {
	if (procStore.find(lineNum) != procStore.end()) {
		return procStore[lineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> ContainCallsStore::getStmt(std::string procName) {
	if (stmtStore.find(procName) != stmtStore.end()) {
		return stmtStore[procName];
	}
	else {
		return {};
	}
}


std::unordered_set<std::string> ContainCallsStore::getAllProc() {
	std::unordered_set<std::string> procList;

	for (const auto& [key, value] : procStore) {
		procList.insert(value.begin(), value.end());
	}
	return procList;
}

std::unordered_set<int> ContainCallsStore::getAllStmt() {
	std::unordered_set<int> stmtList;

	for (const auto& [key, value] : stmtStore) {
		stmtList.insert(value.begin(), value.end());
	}
	return stmtList;
}

