#include<stdio.h>
#include <iostream>

using namespace std;

#include "ModifiesProcStore.h"

ModifiesProcStore::ModifiesProcStore() {}

void ModifiesProcStore::addModifiesProc(string procName, string varName) {
	modProcStore[varName].emplace(procName);
	modVarStore[procName].emplace(varName);
}

unordered_set<string> ModifiesProcStore::getModVar(string procName) {
	if (hasModProc(procName)) {
		return modVarStore[procName];
	}
	else {
		return unordered_set<string>{};
	}
}

unordered_set<string> ModifiesProcStore::getModProc(string varName) {
	if (hasModVar(varName)) {
		return modProcStore[varName];
	}
	else {
		return unordered_set<string>{};
	}
}

bool ModifiesProcStore::hasModVar(string varName) {
	if (modVarStore.find(varName) != modVarStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ModifiesProcStore::hasModProc(string procName) {
	if (modProcStore.find(procName) != modProcStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

void ModifiesProcStore::clear() {
	modProcStore.clear();
	modVarStore.clear();
}