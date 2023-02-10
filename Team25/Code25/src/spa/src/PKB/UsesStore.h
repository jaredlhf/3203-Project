#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

class UsesStore {
private:
	unordered_map<int, unordered_set<string>> usesVarStore;
	unordered_map<string, unordered_set<int>> usesStmtStore;


public:
	UsesStore();

	void addUses(int lineNum, string varName);
	unordered_set<string> getUsesVar(int lineNum);
	unordered_set<int> getUsesStmt(string varName);
	bool hasUsesVar(string varName);
	bool hasUsesStmt(int lineNum);
	unordered_set<string> getAllUsesVar();
	unordered_set<int> getAllUsesStmt();

	void clear();
};