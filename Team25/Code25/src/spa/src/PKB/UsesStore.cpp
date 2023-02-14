#include<stdio.h>
#include <iostream>


#include "UsesStore.h"

UsesStore::UsesStore() {}

void UsesStore::add(int lineNum, std::string varName) {
	varStore[lineNum] = varName;
	stmtStore[varName].emplace(lineNum);
}

std::string UsesStore::getVar(int lineNum) {
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
		return std::unordered_set<int>{};
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
	std::unordered_set<string> varList;
	
	for (const auto& [key, value] : varStore) {
			varList.insert(value);
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


void UsesStore::clear() {
	stmtStore.clear();
	varStore.clear();
}