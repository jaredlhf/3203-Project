#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// TODO: Delete file

class VariableStore {
private :
	unordered_set<string> varStore;
public :
	VariableStore(); 
	void addVar(string varName);
	unordered_set<string> getAllVar();
	bool has(string varName);
	int size();
	void clear();
};