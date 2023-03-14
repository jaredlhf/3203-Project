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
	unordered_map<std::string, unordered_set<int>> whileStatementVarStore;
	unordered_map<int, unordered_set<std::string>> whileStatementStore;

public:
	PatternStore();

	void addAssignLhs(std::string leftVar, int stmtNo);
	void addAssignRhs(int stmtNo, std::string rightStmt);
	void addIfStatement(int stmtNo, std::string varName);
	void addIfStatementVar(std::string varName, int stmtNo);
	void addWhileStatement(int stmtNo, std::string varName);
	void addWhileStatementVar(std::string varName, int stmtNo);
	std::unordered_set<int> getAssignLhs(std::string leftVar);
	std::string getAssignRhs(int stmtNo);
	std::unordered_set<std::string> getIfVars(int stmtNo);
	std::unordered_set<int> getIfStatements(std::string varName);
	std::unordered_set<std::string> getWhileVars(int stmtNo);
	std::unordered_set<int> getWhileStatements(std::string varName);
	bool hasAssignLhs(std::string leftVar);
	bool hasAssignRhs(int stmtNo);
	bool hasIfVars(int stmtNo);
	bool hasIfStatements(std::string varName);
	bool hasWhileVars(int stmtNo);
	bool hasWhileStatements(std::string varName);
	int LhsAssignStoreSize();
	int RhsAssignStoreSize();
};