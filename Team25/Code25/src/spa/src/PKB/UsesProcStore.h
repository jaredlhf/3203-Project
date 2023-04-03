#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "AbstractionStore.h"

class UsesProcStore : public ProcVarStore {
private:
	std::unordered_map<std::string, std::unordered_set<std::string>> varStore;

public:
	UsesProcStore();
	UsesProcStore(std::unordered_map<std::string, std::unordered_set<std::string>> varStore);

	void addUsesProc(std::string procName, std::string varName);
	std::unordered_set<std::string> getVar(std::string procName) override;
};
