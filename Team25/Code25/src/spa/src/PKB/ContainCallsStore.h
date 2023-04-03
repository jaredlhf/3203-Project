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

public:
	ContainCallsStore();
	ContainCallsStore(std::unordered_map<int, std::unordered_set<std::string>> procStore);

	void addContainCall(int lineNum, std::string procName);
	std::unordered_set<std::string> getProc(int lineNum) override;
};