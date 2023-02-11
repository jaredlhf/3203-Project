#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// TODO: Delete file

class ProcedureStore {
private:
	unordered_set<string> procStore;
public:
	ProcedureStore();
	void addProc(string procName);
	unordered_set<string> getAllProc();
	bool has(string procName);
	int size();
	void clear();
};