#include<stdio.h>
#include <iostream>


#include "UsesStore.h"

UsesStore::UsesStore() {}

UsesStore::UsesStore(std::unordered_map<int, std::unordered_set<std::string>> varStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore)
	: varStore{ varStore }, stmtStore{ stmtStore } {}

void UsesStore::addUses(int lineNum, std::string varName) {
	varStore[lineNum].emplace(varName);
	stmtStore[varName].emplace(lineNum);
}

std::unordered_set<std::string> UsesStore::getVar(int lineNum) {
	if (hasStmt(lineNum)) {
		return varStore[lineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> UsesStore::getStmt(std::string varName) {
	if (hasVar(varName)) {
		return stmtStore[varName];
	}
	else {
		return {};
	}
}

bool UsesStore::hasVar(std::string varName) {
	if (stmtStore.find(varName) != stmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool UsesStore::hasStmt(int lineNum) {
	if (varStore.find(lineNum) != varStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<std::string> UsesStore::getAllVar() {
	std::unordered_set<std::string> varList;

	for (const auto& [key, value] : varStore) {
		varList.insert(value.begin(), value.end());
	}
	return varList;
}

std::unordered_set<int> UsesStore::getAllStmt() {
	std::unordered_set<int> stmtList;

	for (const auto& [key, value] : stmtStore) {
		stmtList.insert(value.begin(), value.end());
	}
	return stmtList;
}


