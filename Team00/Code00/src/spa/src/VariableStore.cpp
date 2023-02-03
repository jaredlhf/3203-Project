#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "VariableStore.h"

VariableStore::VariableStore() {}

void VariableStore::addVar(string varName) {
	varStore.emplace(varName);
}

unordered_set<string> VariableStore::getAllVar() {
	return varStore;
}

bool VariableStore::checkVar(string varName) {
	if (varStore.find(varName) != varStore.end()) {
		return true;
	} else {
		return false;
	}
}

int VariableStore::size() {
	return varStore.size();
}
