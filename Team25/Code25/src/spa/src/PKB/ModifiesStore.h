#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

class ModifiesStore {
private:
	unordered_map<int, unordered_set<string>> modVarStore;
	unordered_map<string, unordered_set<int>> modStmtStore;

	
public:
	ModifiesStore();

	void addModifies(int lineNum, string varName);
	unordered_set<string> getModVar(int lineNum);
	unordered_set<int> getModStmt(string varName);
	bool hasModVar(string varName);
	bool hasModStmt(int lineNum);
	unordered_set<string> getAllModVar();
	unordered_set<int> getAllModStmt();
	
	void clear();
};