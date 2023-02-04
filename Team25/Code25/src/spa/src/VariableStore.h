#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class VariableStore {
private :
	unordered_set<string> varStore;
public :
	VariableStore(); 
	void addVar(string varName);
	unordered_set<string> getAllVar();
	bool checkVar(string varName);
	int size();
	void clear();
};