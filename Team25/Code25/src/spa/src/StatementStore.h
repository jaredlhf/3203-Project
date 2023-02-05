#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class StatementStore {
private:
	unordered_map<string, unordered_set<int>> stmtStore;
public:
	StatementStore();
	void addStmt(string stmtType, int lineNum);
	unordered_set<int> getAllStmt(string stmtType);
	bool checkStmt(string stmtType);
	int size();
	void clear();
};