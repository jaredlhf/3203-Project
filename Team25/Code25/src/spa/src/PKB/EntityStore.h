#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>


class ConstantStore {
private:
	std::unordered_set<int> store;
public:
	ConstantStore();
	ConstantStore(std::unordered_set<int> store);
	void addConst(int constNum);
	std::unordered_set<int> getAllConst();
};

class VariableStore {
private:
	std::unordered_set<std::string> store;
public:
	VariableStore();
	VariableStore(std::unordered_set<std::string> store);
	void addVar(std::string varName);
	std::unordered_set<std::string> getAllVar();
};

class ProcedureStore {
private:
	std::unordered_set<std::string> store;
public:
	ProcedureStore();
	ProcedureStore(std::unordered_set<std::string> store);
	void addProc(std::string procName);
	std::unordered_set<std::string> getAllProc();
};

class StatementStore {
private:
	std::unordered_map<std::string, std::unordered_set<int>> store;
public:
	StatementStore();
	StatementStore(std::unordered_map<std::string, std::unordered_set<int>> store);
	void addStmt(std::string stmtType, int lineNum);
	std::unordered_set<int> getAllStmt(std::string stmtType);
};