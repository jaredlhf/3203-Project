#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

#include "AbstractionStore.h"

class ModifiesProcStore : public ProcVarStore {
private: 
	std::unordered_map<std::string, std::unordered_set<std::string>> procStore;
	std::unordered_map<std::string, std::unordered_set<std::string>> varStore;

public:
	ModifiesProcStore();
	ModifiesProcStore(std::unordered_map<std::string, std::unordered_set<std::string>> procStore, std::unordered_map<std::string, std::unordered_set<std::string>> varStore);
	
	void addModifiesProc(std::string procName, std::string varName);
	std::unordered_set<std::string> getVar(std::string procName) override;
	std::unordered_set<std::string> getProc(std::string varName) override;
	std::unordered_set<std::string> getAllVar() override;
	std::unordered_set<std::string> getAllProc() override;
};
