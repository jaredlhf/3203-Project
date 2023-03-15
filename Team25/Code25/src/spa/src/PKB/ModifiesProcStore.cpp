#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "ModifiesProcStore.h"

ModifiesProcStore::ModifiesProcStore() : procStore{}, varStore{} {}

ModifiesProcStore::ModifiesProcStore(std::unordered_map<std::string, std::unordered_set<std::string>> procStore, 
	std::unordered_map<std::string, std::unordered_set<std::string>> varStore)
	: procStore{ procStore }, varStore{ varStore } {}

void ModifiesProcStore::addModifiesProc(std::string procName, std::string varName) {
	procStore[varName].emplace(procName);
	varStore[procName].emplace(varName);
}

std::unordered_set<std::string> ModifiesProcStore::getVar(std::string procName) {
	if (hasProc(procName)) {
		return varStore[procName];
	}
	else {
		return {};
	}
}

std::unordered_set<std::string> ModifiesProcStore::getProc(std::string varName) {
	if (hasVar(varName)) {
		return procStore[varName];
	}
	else {
		return {};
	}
}

bool ModifiesProcStore::hasVar(std::string varName) {
	if (procStore.find(varName) != procStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ModifiesProcStore::hasProc(std::string procName) {
	if (varStore.find(procName) != varStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<std::string> ModifiesProcStore::getAllVar()
{
	std::unordered_set<std::string> varList;

	for (const auto& [key, value] : varStore) {
		varList.insert(value.begin(), value.end());
	}
	return varList;
}

std::unordered_set<std::string> ModifiesProcStore::getAllProc()
{
	std::unordered_set<std::string> procList;

	for (const auto& [key, value] : procStore) {
		procList.insert(value.begin(), value.end());
	}
	return procList;
}

