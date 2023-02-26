#include<stdio.h>
#include <iostream>
#include <string>

#include "StatementStore.h"
//TODO Delete if unused

/*
StatementStore::StatementStore() : store{} {}

StatementStore::StatementStore(std::unordered_map<std::string, std::unordered_set<int>> store) : store{ store } {}

void StatementStore::addStmt(std::string stmtType, int lineNum) {
	store[stmtType].emplace(lineNum);
}

std::unordered_set<int> StatementStore::getAllStmt(std::string stmtType) {
	if (has(stmtType)) {
		return store[stmtType];
	}
	else {
		return std::unordered_set<int>{};
	}
}

bool StatementStore::has(std::string stmtType) {
	if (store.find(stmtType) != store.end()) {
		return true;
	}
	else {
		return false;
	}
}

int StatementStore::size() {
	return store.size();
}

void StatementStore::clear() {
	store.clear();
}
*/