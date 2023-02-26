#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
//TODO Delete if unused

/* Storage class for statements and their line numbers.*/
/*
class StatementStore {
private:
	std::unordered_map<std::string, std::unordered_set<int>> store;
public:
	StatementStore();
	StatementStore(std::unordered_map<std::string, std::unordered_set<int>> store);
	void addStmt(std::string stmtType, int lineNum);
	std::unordered_set<int> getAllStmt(std::string stmtType);
	bool has(std::string stmtType);
	int size();
	void clear();
};*/