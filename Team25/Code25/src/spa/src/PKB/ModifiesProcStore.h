#pragma once

#include<stdio.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class ModifiesProcStore {
private: 
	unordered_map<string, unordered_set<string>> modProcStore;
	unordered_map<string, unordered_set<string>> modVarStore;

public:
	ModifiesProcStore();

	void addModifiesProc(string procName, string varName);
	unordered_set<string> getModVar(string procName);
	unordered_set<string> getModProc(string varName);
	bool hasModVar(string varName);
	bool hasModProc(string procName);
	/*unordered_set<string> getAllModVarProc();
	unordered_set<string> getAllModProc();*/

	void clear();
};
