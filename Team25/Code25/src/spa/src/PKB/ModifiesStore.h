#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "AbstractionStore.h"

/* Storage class for Modifies relationship between a statement and variable. 
In Modifies(a, v), statement line number is a and variable name is v.*/
class ModifiesStore : public StmtVarStore {
private:
	std::unordered_map<int, std::unordered_set<std::string>> varStore;
	std::unordered_map<std::string, std::unordered_set<int>> stmtStore;

public:
	ModifiesStore();
	ModifiesStore(std::unordered_map<int, std::unordered_set<std::string>> varStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore);

	void addModifies(int lineNum, std::string varName);
	std::unordered_set<std::string> getVar(int lineNum) override;
	std::unordered_set<int> getStmt(std::string varName) override;
	bool hasVar(std::string varName) override;
	bool hasStmt(int lineNum) override;
	std::unordered_set<std::string> getAllVar() override;
	std::unordered_set<int> getAllStmt() override;
};