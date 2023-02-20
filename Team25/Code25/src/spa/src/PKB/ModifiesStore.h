#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

/* Storage class for Modifies relationship between a statement and variable. 
In Modifies(a, v), statement line number is a and variable name is v.*/
class ModifiesStore {
private:
	std::unordered_map<int, std::string> varStore;
	std::unordered_map<std::string, std::unordered_set<int>> stmtStore;

	
public:
	ModifiesStore();

	void add(int lineNum, std::string varName);
	std::string getVar(int lineNum);
	std::unordered_set<int> getStmt(std::string varName);
	bool hasVar(std::string varName);
	bool hasStmt(int lineNum);
	std::unordered_set<std::string> getAllVar();
	std::unordered_set<int> getAllStmt();
	
	void clear();
};