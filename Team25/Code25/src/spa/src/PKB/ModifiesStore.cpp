#include<stdio.h>
#include <algorithm>
#include <iostream>


#include "ModifiesStore.h"

ModifiesStore::ModifiesStore() : varStore{} {}

ModifiesStore::ModifiesStore(std::unordered_map<int, std::unordered_set<std::string>> varStore)
	: varStore{varStore} {}

void ModifiesStore::addModifies(int lineNum, std::string varName) {
	varStore[lineNum].emplace(varName);

}

std::unordered_set<std::string> ModifiesStore::getVar(int lineNum) {
	if (varStore.find(lineNum) != varStore.end()) {
		return varStore[lineNum];
	}
	else {
		return {};
	}
}