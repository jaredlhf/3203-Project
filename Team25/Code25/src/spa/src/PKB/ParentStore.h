#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class ParentStore {
private:
	unordered_map<int, int> parentStore;
	unordered_map<int, std::unordered_set<int>> childrenStore;
public:
	ParentStore();
	void addParent(int parent, int child);
	int getParent(int child);
	std::unordered_set<int> getChildren(int parent);
	bool hasParent(int lineNum);
	bool hasChildren(int lineNum);
	unordered_set<int> getAllParents();
	unordered_set<int> getAllChildren();
	void clear();
};