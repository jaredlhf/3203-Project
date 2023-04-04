#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "ModifiesProcStore.h"

ModifiesProcStore::ModifiesProcStore() : varStore{} {}

ModifiesProcStore::ModifiesProcStore(std::unordered_map<std::string, std::unordered_set<std::string>> varStore)
	: varStore{ varStore } {}

void ModifiesProcStore::addModifiesProc(std::string procName, std::string varName) {
	varStore[procName].emplace(varName);
}

std::unordered_set<std::string> ModifiesProcStore::getVar(std::string procName) {
	if (varStore.find(procName) != varStore.end()) {
		return varStore[procName];
	}
	else {
		return {};
	}
}
