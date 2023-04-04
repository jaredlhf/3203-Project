#include<stdio.h>
#include <iostream>

#include "UsesProcStore.h"

UsesProcStore::UsesProcStore() : varStore{} {}

UsesProcStore::UsesProcStore(
	std::unordered_map<std::string, std::unordered_set<std::string>> varStore)
	: varStore{ varStore } {}

void UsesProcStore::addUsesProc(std::string procName, std::string varName) {
	varStore[procName].emplace(varName);
}

std::unordered_set<std::string> UsesProcStore::getVar(std::string procName) {
	if (varStore.find(procName) != varStore.end()) {
		return varStore[procName];
	}
	else {
		return {};
	}
}

