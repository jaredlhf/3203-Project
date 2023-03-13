#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

class PatternStore {
private:
	unordered_map<std::string, unordered_set<int>> LhsAssignStore;
	unordered_map<int, std::string> RhsAssignStore;
	unordered_map<std::string, unordered_set<int>> ifStatementVarStore;
	unordered_map<int, unordered_set<std::string>> ifStatementStore;

public:
	PatternStore();

	void addAssignLhs(std::string leftVar, int stmtNo);
	void addAssignRhs(int stmtNo, std::string rightStmt);
	void addIfStatement(std::string var, int stmtNo);
	void addIfStatementVar(int stmtNo, std::string varName);
	std::unordered_set<int> getAssignLhs(std::string leftVar);
	std::string getAssignRhs(int stmtNo);
	std::unordered_set<std::string> getIfVars(int stmtNo);
	std::unordered_set<int> getIfStatements(std::string var);
	bool hasAssignLhs(std::string leftVar);
	bool hasAssignRhs(int stmtNo);
	bool hasIfVars(int stmtNo);
	bool hasIfStatements(std::string var);
	int LhsAssignStoreSize();
	int RhsAssignStoreSize();
};