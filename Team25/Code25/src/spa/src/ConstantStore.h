#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class ConstantStore {
private:
	unordered_set<int> constStore;
public:
	ConstantStore();
	void addConst(int constNum);
	unordered_set<int> getAllConst();
	bool checkConst(int constNum);
	int size();
	void clear();
};