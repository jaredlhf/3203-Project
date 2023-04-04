#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "CallsStore.h"

CallsStore::CallsStore() : leftProcStore{}, rightProcStore{} {}
CallsStore::CallsStore(std::unordered_map<std::string, std::unordered_set<std::string>> leftProcStore, std::unordered_map<std::string, std::unordered_set<std::string>> rightProcStore)
	: leftProcStore{ leftProcStore }, rightProcStore{ rightProcStore } {}

void CallsStore::addCalls(std::string leftProc, std::string rightProc) {
	leftProcStore[rightProc].emplace(leftProc);
	rightProcStore[leftProc].emplace(rightProc);
}

std::unordered_set<std::string> CallsStore::getLeftProc(std::string rightProc) {
	if (leftProcStore.find(rightProc) != leftProcStore.end()) {
		return leftProcStore[rightProc];
	}
	else {
		return {};
	}
}

std::unordered_set<std::string> CallsStore::getRightProc(std::string leftProc) {
	if (rightProcStore.find(leftProc) != rightProcStore.end()) {
		return rightProcStore[leftProc];
	}
	else {
		return {};
	}
}


std::unordered_set<std::string> CallsStore::getAllLeft() {
	std::unordered_set<std::string> leftProcList;
	for (const auto& [key, value] : leftProcStore) {
		leftProcList.insert(value.begin(), value.end());
	}
	return leftProcList;
}

std::unordered_set<std::string> CallsStore::getAllRight() {
	std::unordered_set<std::string> rightProcList;
	for (const auto& [key, value] : rightProcStore) {
		rightProcList.insert(value.begin(), value.end());
	}
	return rightProcList;
}