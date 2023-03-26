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
ProcedureStore::ProcedureStore() : store{} {}

ProcedureStore::ProcedureStore(std::unordered_set<std::string> store) : store{ store } {}

void ProcedureStore::addProc(std::string procName) {
	this->store.emplace(procName);
}

std::unordered_set<std::string> ProcedureStore::getAllProc() {
	return this->store;
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
		return std::unordered_set<int>{};
	}
}
