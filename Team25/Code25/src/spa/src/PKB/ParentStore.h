#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

/* Storage class for Parent relationship between two statements. 
In Parent(s1, s2), Parent is s1 and Child is s2.*/
class ParentStore {
private:
	std::unordered_map<int, int> parentStore;
	std::unordered_map<int, std::unordered_set<int>> childrenStore;
public:
	ParentStore();
	void addParent(int parent, int child);
	int getParent(int child);
	std::unordered_set<int> getChildren(int parent);
	bool hasParent(int lineNum);
	bool hasChildren(int lineNum);
	std::unordered_set<int> getAllParents();
	std::unordered_set<int> getAllChildren();
	void clear();
};