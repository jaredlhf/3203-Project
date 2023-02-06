#include<stdio.h>
#include <iostream>
#include <string>

using namespace std;

#include "StatementStore.h"

StatementStore::StatementStore() {}

void StatementStore::addStmt(string stmtType, int lineNum) {
	stmtStore[stmtType].emplace(lineNum);
}

unordered_set<int> StatementStore::getAllStmt(string stmtType) {
	if (has(stmtType)) {
		return stmtStore[stmtType];
	}
	else {
		return unordered_set<int>{};
	}
}

bool StatementStore::has(string stmtType) {
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