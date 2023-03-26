#include<stdio.h>
#include <algorithm>
#include <iostream>


#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() : varStore{}, stmtStore {} {}

ModifiesStore::ModifiesStore(std::unordered_map<int, std::unordered_set<std::string>> varStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore)
	: varStore{varStore}, stmtStore{stmtStore} {}

void ModifiesStore::addModifies(int lineNum, std::string varName) {
	varStore[lineNum].emplace(varName);
	stmtStore[varName].emplace(lineNum);
}

std::unordered_set<std::string> ModifiesStore::getVar(int lineNum) {
	if (varStore.find(lineNum) != varStore.end()) {
		return varStore[lineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> ModifiesStore::getStmt(std::string varName) {
	if (stmtStore.find(varName) != stmtStore.end()) {
		return stmtStore[varName];
	}
	else {
		return std::unordered_set<int>{};
	}
}

std::unordered_set<std::string> ModifiesStore::getAllVar() {
	std::unordered_set<std::string> varList;
	
	for (const auto& [key, value] : varStore) {
			varList.insert(value.begin(), value.end());
		}
	return varList;
}

std::unordered_set<int> ModifiesStore::getAllStmt() {
	std::unordered_set<int> stmtList;
	for (const auto& [key, value] : stmtStore) {
		stmtList.insert(value.begin(), value.end());
	}
	return stmtList;
}

