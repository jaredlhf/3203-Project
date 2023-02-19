#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

/* Storage class for statements and their line numbers.*/
class StatementStore {
private:
	std::unordered_map<std::string, std::unordered_set<int>> stmtStore;
public:
	StatementStore();
	void addStmt(std::string stmtType, int lineNum);
	std::unordered_set<int> getAllStmt(std::string stmtType);
	bool has(std::string stmtType);
	int size();
	void clear();
};