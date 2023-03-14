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

void PatternStore::addIfStatement(int stmtNo, std::string varName) {
	ifStatementStore[stmtNo].emplace(varName);
}

void PatternStore::addIfStatementVar(std::string varName, int stmtNo) {
	ifStatementVarStore[varName].emplace(stmtNo);
}

void PatternStore::addWhileStatement(int stmtNo, std::string varName) {
	whileStatementStore[stmtNo].emplace(varName);
}

void PatternStore::addWhileStatementVar(std::string varName, int stmtNo) {
	whileStatementVarStore[varName].emplace(stmtNo);
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

std::unordered_set<int> PatternStore::getIfStatements(std::string varName) {
	if (hasIfStatements(varName)) {
		return ifStatementVarStore[varName];
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

std::unordered_set<int> PatternStore::getWhileStatements(std::string varName) {
	if (hasWhileStatements(varName)) {
		return whileStatementVarStore[varName];
	}
	else {
		return unordered_set<int>{};
	}
}

std::unordered_set<std::string> PatternStore::getWhileVars(int stmtNo) {
	if (hasWhileVars(stmtNo)) {
		return whileStatementStore[stmtNo];
	}
	else {
		return std::unordered_set<std::string>{};
	}
}

bool PatternStore::hasAssignLhs(std::string leftVar) {
	return LhsAssignStore.find(leftVar) != LhsAssignStore.end();
}

bool PatternStore::hasAssignRhs(int stmtNo) {
	return RhsAssignStore.find(stmtNo) != RhsAssignStore.end();
}
bool PatternStore::hasIfStatements(std::string varName) {
	return ifStatementVarStore.find(varName) != ifStatementVarStore.end();
}
bool PatternStore::hasIfVars(int stmtNo) {
	return ifStatementStore.find(stmtNo) != ifStatementStore.end();
}

bool PatternStore::hasWhileStatements(std::string varName) {
	return whileStatementVarStore.find(varName) != whileStatementVarStore.end();
}

bool PatternStore::hasWhileVars(int stmtNo) {
	return whileStatementStore.find(stmtNo) != whileStatementStore.end();
}

int PatternStore::LhsAssignStoreSize() {
	return LhsAssignStore.size();
}
int PatternStore::RhsAssignStoreSize() {
	return RhsAssignStore.size();
}


