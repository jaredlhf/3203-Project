#include<stdio.h>
#include <algorithm>
#include <iostream>

#include "CallsStarStore.h"

CallsStarStore::CallsStarStore() : leftProcStar{}, rightProcStar{} {}

CallsStarStore::CallsStarStore(std::unordered_map<std::string, std::unordered_set<std::string>> leftProcStar, std::unordered_map<std::string, std::unordered_set<std::string>> rightProcStar) : leftProcStar{ leftProcStar }, rightProcStar{ rightProcStar } {}

void CallsStarStore::addCallsStar(std::string leftProc, std::string rightProc) {
	rightProcStar[leftProc].emplace(rightProc);
	leftProcStar[rightProc].emplace(leftProc);
}

std::unordered_set<std::string> CallsStarStore::getLeftStar(std::string rightProc) {
	if (leftProcStar.find(rightProc) != leftProcStar.end()) {
		return leftProcStar[rightProc];
	}
	else {
		return {};
	}
}

std::unordered_set<std::string> CallsStarStore::getRightStar(std::string leftProc) {
	if (rightProcStar.find(leftProc) != rightProcStar.end()) {
		return rightProcStar[leftProc];
	}
	else {
		return {};
	}
}

std::unordered_set<std::string> CallsStarStore::getAllLeft() {
	std::unordered_set<std::string> leftProcList;
	for (const auto& [key, value] : leftProcStar) {
		leftProcList.insert(value.begin(), value.end());
	}
	return leftProcList;
}

std::unordered_set<std::string> CallsStarStore::getAllRight() {
	std::unordered_set<std::string> rightProcList;
	for (const auto& [key, value] : rightProcStar) {
		rightProcList.insert(value.begin(), value.end());
	}
	return rightProcList;
}
