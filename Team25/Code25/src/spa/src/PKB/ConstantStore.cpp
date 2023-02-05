#include<stdio.h>
#include <iostream>
#include <vector>

using namespace std;

#include "ConstantStore.h"

ConstantStore::ConstantStore() {}

void ConstantStore::addConst(int constNum) {
	constStore.emplace(constNum);
}

unordered_set<int> ConstantStore::getAllConst() {
	return constStore;
}

bool ConstantStore::has(int constNum) {
	if (constStore.find(constNum) != constStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

int ConstantStore::size() {
	return constStore.size();
}

void ConstantStore::clear() {
	constStore.clear();
}
