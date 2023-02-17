#include<stdio.h>
#include <iostream>

using namespace std;

#include "PatternStore.h"

PatternStore::PatternStore() {}

void PatternStore::addAssignLhs(std::string leftVar, int stmtNo) {
	LhsAssignStore[leftVar].emplace(stmtNo);
}

void PatternStore::addAssignRhs(int stmtNo, std::string rightStmt) {
	RhsAssignStore.insert({ stmtNo, rightStmt });
}

std::unordered_set<int> PatternStore::getAssignLhs(std::string leftVar) {
	if (hasAssignLhs(leftVar)) {
		return LhsAssignStore[leftVar];
	}
	else {
		return unordered_set<int>{};
	}
}

std::string PatternStore::getAssignRhs(int stmtNo) {
	if (hasAssignRhs(stmtNo)) {
		return RhsAssignStore[stmtNo];
	}
	else {
		return {};
	}
}


bool PatternStore::hasAssignLhs(std::string leftVar) {
	return LhsAssignStore.find(leftVar) != LhsAssignStore.end();
}

bool PatternStore::hasAssignRhs(int stmtNo) {
	return RhsAssignStore.find(stmtNo) != RhsAssignStore.end();
}
int PatternStore::LhsAssignStoreSize() {
	return LhsAssignStore.size();
}
int PatternStore::RhsAssignStoreSize() {
	return RhsAssignStore.size();
}

void PatternStore::clear() {
	LhsAssignStore.clear();
	RhsAssignStore.clear();
}


