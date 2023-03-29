#include <iostream>
#include <algorithm>
#include "EntityStore.h"

/* Constant Store*/
/*---------------------------------------------------------------------------------------------*/
ConstantStore::ConstantStore() : store{} {}

ConstantStore::ConstantStore(std::unordered_set<int> store) : store{ store } {}

void ConstantStore::addConst(int constNum) {
	this->store.emplace(constNum);
}

std::unordered_set<int> ConstantStore::getAllConst() {
	return this->store;
}



/* Variable Store*/
/*---------------------------------------------------------------------------------------------*/
VariableStore::VariableStore() : store{} {}

VariableStore::VariableStore(std::unordered_set<std::string> store) : store{ store } {}

void VariableStore::addVar(std::string varName) {
	this->store.emplace(varName);
}

std::unordered_set<std::string> VariableStore::getAllVar() {
	return this->store;
}



/* Procedure Store*/
/*---------------------------------------------------------------------------------------------*/
ProcedureStore::ProcedureStore() : procStore{}, stmtStore{} {}

ProcedureStore::ProcedureStore(std::unordered_map<int, std::string> procStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore) 
	: procStore{ procStore }, stmtStore{ stmtStore } {}

void ProcedureStore::addProc(std::string procName, int lineNum) {
	procStore[lineNum] = procName;
	stmtStore[procName].emplace(lineNum);
}

std::string ProcedureStore::getProc(int lineNum) {
	if (procStore.find(lineNum) != procStore.end()) {
		return procStore[lineNum];
	}
	else {
		return {};
	}
}

std::unordered_set<int> ProcedureStore::getStmt(std::string procName) {
	if (stmtStore.find(procName) != stmtStore.end()) {
		return stmtStore[procName];
	}
	else {
		return {};
	}
}

std::unordered_set<std::string> ProcedureStore::getAllProc() {
	std::unordered_set<std::string> procList;
	for (const auto& [key, value] : stmtStore) {
		procList.insert(key);
	}
	return procList;
}


/* Statement Store*/
/*---------------------------------------------------------------------------------------------*/
StatementStore::StatementStore() : store{} {}

StatementStore::StatementStore(std::unordered_map<std::string, std::unordered_set<int>> store) : store{ store } {}

void StatementStore::addStmt(std::string stmtType, int lineNum) {
	store[stmtType].emplace(lineNum);
}

std::unordered_set<int> StatementStore::getAllStmt(std::string stmtType) {
	if (store.find(stmtType) != store.end()) {
		return store[stmtType];
	}
	else {
		return {};
	}
}
