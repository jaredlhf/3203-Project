#include<stdio.h>
#include <iostream>

using namespace std;

#include "PatternStore.h"

PatternStore::PatternStore() {}

unordered_map<std::string, unordered_set<int>> LhsAssignStore;
unordered_map<int, std::string> RhsAssignStore;
unordered_map<std::string, unordered_set<int>> ifStatementVarStore;
unordered_map<int, unordered_set<std::string>> ifStatementStore;

void PatternStore::addAssignLhs(std::string leftVar, int stmtNo) {
	LhsAssignStore[leftVar].emplace(stmtNo);
}

void PatternStore::addAssignRhs(int stmtNo, std::string rightStmt) {
	RhsAssignStore.insert({ stmtNo, rightStmt });
}

void PatternStore::addIfStatement(std::string var, int stmtNo) {
	ifStatementVarStore[var].emplace(stmtNo);
}

void PatternStore::addIfStatementVar(int stmtNo, std::string varName) {
	ifStatementStore[stmtNo].emplace(varName);
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

std::unordered_set<int> PatternStore::getIfStatements(std::string var) {
	if (hasIfStatements(var)) {
		return ifStatementVarStore[var];
	}
	else {
		return unordered_set<int>{};
	}
}

std::unordered_set<std::string> PatternStore::getIfVars(int stmtNo) {
	if (hasIfVars(stmtNo)) {
		return ifStatementStore[stmtNo];
	}
	else {
		return unordered_set<std::string>{};
	}
}


bool PatternStore::hasAssignLhs(std::string leftVar) {
	return LhsAssignStore.find(leftVar) != LhsAssignStore.end();
}

bool PatternStore::hasAssignRhs(int stmtNo) {
	return RhsAssignStore.find(stmtNo) != RhsAssignStore.end();
}
bool PatternStore::hasIfStatements(std::string var) {
	return ifStatementVarStore.find(var) != ifStatementVarStore.end();
}
bool PatternStore::hasIfVars(int stmtNo) {
	return ifStatementStore.find(stmtNo) != ifStatementStore.end();
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


