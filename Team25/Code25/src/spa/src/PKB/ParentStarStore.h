#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class ParentStarStore {
private:
	std::unordered_map<int, std::unordered_set<int>> parentStar;
	std::unordered_map<int, std::unordered_set<int>> childrenStar;
public:
	ParentStarStore();
	void addParentStar(int parent, std::unordered_set<int> childrenLst);
	std::unordered_set<int> getParentStar(int children);
	std::unordered_set<int> getChildrenStar(int parent);
	bool hasParent(int lineNum);
	bool hasChildren(int lineNum);
	std::unordered_set<int> getAllParents();
	std::unordered_set<int> getAllChildren();
	void clear();
};