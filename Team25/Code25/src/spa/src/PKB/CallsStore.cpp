#include<stdio.h>
#include <iostream>

#include "CallsStore.h"

CallsStore::CallsStore() : leftProcStore{}, rightProcStore{} {}
CallsStore::CallsStore(std::unordered_map<std::string, std::string> leftProcStore, std::unordered_map<std::string, std::string> rightProcStore) 
	: leftProcStore{ leftProcStore }, rightProcStore{ rightProcStore } {}

void CallsStore::addCalls(std::string leftProc, std::string rightProc) {
	leftProcStore[rightProc] = leftProc;
	rightProcStore[leftProc] = rightProc;
}

std::string CallsStore::getLeftProc(std::string rightProc) {
	if (hasRightProc(rightProc)) {
		return leftProcStore[rightProc];
	}
	else {
		return {};
	}
}

std::string CallsStore::getRightProc(std::string leftProc) {
	if (hasLeftProc(leftProc)) {
		return rightProcStore[leftProc];
	}
	else {
		return {};
	}
}

bool CallsStore::hasLeftProc(std::string procName) {
	if (rightProcStore.find(procName) != rightProcStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool CallsStore::hasRightProc(std::string procName) {
	if (leftProcStore.find(procName) != leftProcStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<std::string> CallsStore::getAllLeft() {
	std::unordered_set<std::string> leftProcList;
	for (const auto& [key, value] : leftProcStore) {
		leftProcList.insert(value);
	}
	return leftProcList;
}

std::unordered_set<std::string> CallsStore::getAllRight() {
	std::unordered_set<std::string> rightProcList;
	for (const auto& [key, value] : rightProcStore) {
		rightProcList.insert(value);
	}
	return rightProcList;
}