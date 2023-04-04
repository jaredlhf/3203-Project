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

public:
	UsesStore();
	UsesStore(std::unordered_map<int, std::unordered_set<std::string>> varStore);
	
	void addUses(int lineNum, std::string varName);
	std::unordered_set<std::string> getVar(int lineNum) override;
};