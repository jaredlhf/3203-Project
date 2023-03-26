#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "AbstractionStore.h"

/* Storage class for Uses relationship between statements and variables.
In Uses(a, v), statement line number is a and variable name is v.*/
class UsesStore : public StmtVarStore {
private:
	std::unordered_map<int, std::unordered_set<std::string>> varStore;
	std::unordered_map<std::string, std::unordered_set<int>> stmtStore;

public:
	UsesStore();
	UsesStore(std::unordered_map<int, std::unordered_set<std::string>> varStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore);
	
	void addUses(int lineNum, std::string varName);
	std::unordered_set<std::string> getVar(int lineNum) override;
	std::unordered_set<int> getStmt(std::string varName) override;
	std::unordered_set<std::string> getAllVar() override;
	std::unordered_set<int> getAllStmt() override;
};