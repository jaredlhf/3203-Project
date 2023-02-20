	#include<stdio.h>
#include <iostream>

#include "ParentStarStore.h"

ParentStarStore::ParentStarStore() {}


void ParentStarStore::addParentStar(int parent, int child) {
	childrenStar[parent].emplace(child);
	parentStar[child].emplace(parent);
}

std::unordered_set<int> ParentStarStore::getParentStar(int child) {
	if (hasChildren(child)) {
		return parentStar[child];
	}
	else {
		return {};
	}
}

std::unordered_set<int> ParentStarStore::getChildrenStar(int parent) {
	if (hasParent(parent)) {
		return childrenStar[parent];
	}
	else {
		return {};
	}
}

bool ParentStarStore::hasParent(int lineNum) {
	if (childrenStar.find(lineNum) != childrenStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

bool ParentStarStore::hasChildren(int lineNum) {
	if (parentStar.find(lineNum) != parentStar.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::unordered_set<int> ParentStarStore::getAllParents() {
	std::unordered_set<int> parentList;
	for (const auto& [key, value] : parentStar) {
		parentList.insert(value.begin(), value.end());
	}
	return parentList;
}

std::unordered_set<int> ParentStarStore::getAllChildren() {
	std::unordered_set<int> childrenList;
	for (const auto& [key, value] : childrenStar) {
		childrenList.insert(value.begin(), value.end());
	}
	return childrenList;
}

void ParentStarStore::clear() {
	parentStar.clear();
	childrenStar.clear();
}