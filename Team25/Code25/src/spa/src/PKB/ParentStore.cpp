#include<stdio.h>
#include <iostream>

#include "ParentStore.h"

ParentStore::ParentStore() {}

void ParentStore::addParent(int parent, int child) {
	parentStore[child] = parent;
	childrenStore[parent].emplace(child);
}

int ParentStore::getParent(int child) {
	if (hasChildren(child)) {
		return parentStore[child];
	}
	else {
		return -1;
	}
}

std::unordered_set<int> ParentStore::getChildren(int parent) {
	if (hasParent(parent)) {
		return childrenStore[parent];
	}
	else {
		return {};
	}
}

bool ParentStore::hasParent(int lineNum) {
	if (childrenStore.find(lineNum) != childrenStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ParentStore::hasChildren(int lineNum) {
	if (parentStore.find(lineNum) != parentStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> ParentStore::getAllParents() {
	std::unordered_set<int> parentList;
	for (const auto& [key, value] : parentStore) {
		parentList.insert(value);
	}
	return parentList;
}

std::unordered_set<int> ParentStore::getAllChildren() {
	std::unordered_set<int> childrenList;
	for (const auto& [key, value] : childrenStore) {
		childrenList.insert(value.begin(), value.end());
	}
	return childrenList;
}

void ParentStore::clear() {
	parentStore.clear();
	childrenStore.clear();
}