#include<stdio.h>
#include <iostream>


#include "UsesStore.h"

UsesStore::UsesStore() {}

UsesStore::UsesStore(std::unordered_map<int, std::unordered_set<std::string>> varStore)
	: varStore{ varStore } {}

void UsesStore::addUses(int lineNum, std::string varName) {
	varStore[lineNum].emplace(varName);
}

std::unordered_set<std::string> UsesStore::getVar(int lineNum) {
	if (varStore.find(lineNum) != varStore.end()) {
		return varStore[lineNum];
	}
	else {
		return {};
	}
}
