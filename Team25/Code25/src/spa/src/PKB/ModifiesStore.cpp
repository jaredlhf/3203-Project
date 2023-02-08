#include<stdio.h>
#include <iostream>

using namespace std;

#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() {}

void ModifiesStore::addModifies(int lineNum, string varName) {
	modVarStore[lineNum].emplace(varName);
	modStmtStore[varName].emplace(lineNum);
}

unordered_set<string> ModifiesStore::getModVar(int lineNum) {
	if (hasModStmt(lineNum)) {
		return modVarStore[lineNum];
	}
	else {
		return unordered_set<string>{};
	}
}

unordered_set<int> ModifiesStore::getModStmt(string varName) {
	if (hasModVar(varName)) {
		return modStmtStore[varName];
	}
	else {
		return unordered_set<int>{};
	}
}

bool ModifiesStore::hasModVar(string varName) {
	if (modStmtStore.find(varName) != modStmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ModifiesStore::hasModStmt(int lineNum) {
	if (modVarStore.find(lineNum) != modVarStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

unordered_set<string> ModifiesStore::getAllModVar() {
	unordered_set<string> modVarList;
	
	for (const auto& [key, value] : modVarStore) {
			modVarList.insert(value.begin(), value.end());
		}
	return modVarList;
}

unordered_set<int> ModifiesStore::getAllModStmt() {
	unordered_set<int> modStmtList;
	for (const auto& [key, value] : modStmtStore) {
		modStmtList.insert(value.begin(), value.end());
	}
	return modStmtList;
}

void ModifiesStore::clear() {
	modStmtStore.clear();
	modVarStore.clear();
}