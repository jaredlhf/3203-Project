#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "ContainCallsStore.h"

ContainCallsStore::ContainCallsStore() : procStore{} {}
ContainCallsStore::ContainCallsStore(std::unordered_map<int, std::unordered_set<std::string>> procStore)
	: procStore{ procStore } {}

void ContainCallsStore::addContainCall(int lineNum, std::string procName) {
	procStore[lineNum].emplace(procName);
}

std::unordered_set<std::string> ContainCallsStore::getProc(int lineNum) {
	if (procStore.find(lineNum) != procStore.end()) {
		return procStore[lineNum];
	}
	else {
		return {};
	}
}