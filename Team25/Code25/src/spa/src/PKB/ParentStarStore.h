#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

/* Storage class for Parent* relationship between direct and indirect parents and children 
In Parent*(s1, s2), Parent star is s1 and Children star is s2.*/
class ParentStarStore {
private:
	std::unordered_map<int, std::unordered_set<int>> parentStar;
	std::unordered_map<int, std::unordered_set<int>> childrenStar;
public:
	ParentStarStore();
	void addParentStar(int parent, int child);
	std::unordered_set<int> getParentStar(int child);
	std::unordered_set<int> getChildrenStar(int parent);
	bool hasParent(int lineNum);
	bool hasChildren(int lineNum);
	std::unordered_set<int> getAllParents();
	std::unordered_set<int> getAllChildren();
	void clear();
};