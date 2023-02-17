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

public:
	PatternStore();

	void addAssignLhs(std::string leftVar, int stmtNo);
	void addAssignRhs(int stmtNo, std::string rightStmt);
	unordered_set<int> getAssignLhs(std::string leftVar);
	std::string getAssignRhs(int stmtNo);
	bool hasAssignLhs(std::string leftVar);
	bool hasAssignRhs(int stmtNo);

	void clear();
	
};