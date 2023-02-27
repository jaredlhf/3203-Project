#include <iostream>

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

bool ConstantStore::has(int constNum) {
	if (this->store.find(constNum) != this->store.end()) {
		return true;
	}
	else {
		return false;
	}
}

int ConstantStore::size() {
	return this->store.size();
}

void ConstantStore::clear() {
	return this->store.clear();
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

bool VariableStore::has(std::string varName) {
	if (this->store.find(varName) != this->store.end()) {
		return true;
	}
	else {
		return false;
	}
}

int VariableStore::size() {
	return this->store.size();
}

void VariableStore::clear() {
	return this->store.clear();
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

bool ProcedureStore::has(std::string procName) {
	if (this->store.find(procName) != this->store.end()) {
		return true;
	}
	else {
		return false;
	}
}

int ProcedureStore::size() {
	return this->store.size();
}

void ProcedureStore::clear() {
	return this->store.clear();
}


/* Statement Store*/
/*---------------------------------------------------------------------------------------------*/
StatementStore::StatementStore() : store{} {}

StatementStore::StatementStore(std::unordered_map<std::string, std::unordered_set<int>> store) : store{ store } {}

void StatementStore::addStmt(std::string stmtType, int lineNum) {
	store[stmtType].emplace(lineNum);
}

std::unordered_set<int> StatementStore::getAllStmt(std::string stmtType) {
	if (has(stmtType)) {
		return store[stmtType];
	}
	else {
		return std::unordered_set<int>{};
	}
}

bool StatementStore::has(std::string stmtType) {
	if (store.find(stmtType) != store.end()) {
		return true;
	}
	else {
		return false;
	}
}

int StatementStore::size() {
	return store.size();
}

void StatementStore::clear() {
	store.clear();
}