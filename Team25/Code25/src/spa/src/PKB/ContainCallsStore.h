#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "AbstractionStore.h"

class ContainCallsStore : public ProcStmtStore {
private:
	std::unordered_map<int, std::unordered_set<std::string>> procStore;
	std::unordered_map<std::string, std::unordered_set<int>> stmtStore;

public:
	ContainCallsStore();
	ContainCallsStore(std::unordered_map<int, std::unordered_set<std::string>> procStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore);

	void addContainCall(int lineNum, std::string procName);
	std::unordered_set<std::string> getProc(int lineNum) override;
	std::unordered_set<int> getStmt(std::string procName) override;
	std::unordered_set<std::string> getAllProc() override;
	std::unordered_set<int> getAllStmt() override;
};