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
	unordered_map<int, int> childStore;
public:
	ParentStore();
	void addParent(int leftLineNum, int rightLineNum);
	int getParent(int rightLineNum);
	int getChild(int leftLineNum);
	bool hasParent(int lineNum);
	bool hasChild(int lineNum);
	/*bool hasFollows(int leftLineNum, int rightLineNum);*/
	unordered_set<int> getAllParents();
	unordered_set<int> getAllChildren();
	void clear();
};