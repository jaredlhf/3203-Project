#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "ProcedureStore.h"

// TODO: Delete file

ProcedureStore::ProcedureStore() {}

void ProcedureStore::addProc(string procName) {
	procStore.emplace(procName);
}

unordered_set<string> ProcedureStore::getAllProc() {
	return procStore;
}

bool ProcedureStore::has(string procName) {
	if (procStore.find(procName) != procStore.end()) {
		return true;
	}
	else {
		return false;
	}
}

int ProcedureStore::size() {
	return procStore.size();
}

void ProcedureStore::clear() {
	procStore.clear();
}
