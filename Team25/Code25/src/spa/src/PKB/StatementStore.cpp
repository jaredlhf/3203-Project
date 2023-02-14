#include<stdio.h>
#include <iostream>
#include <string>

#include "StatementStore.h"

StatementStore::StatementStore() {}

void StatementStore::addStmt(std::string stmtType, int lineNum) {
	stmtStore[stmtType].emplace(lineNum);
}

unordered_set<int> StatementStore::getAllStmt(std::string stmtType) {
	if (has(stmtType)) {
		return stmtStore[stmtType];
	}
	else {
		return unordered_set<int>{};
	}
}

bool StatementStore::has(std::string stmtType) {
	if (stmtStore.find(stmtType) != stmtStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

int StatementStore::size() {
	return stmtStore.size();
}

void StatementStore::clear() {
	stmtStore.clear();
}