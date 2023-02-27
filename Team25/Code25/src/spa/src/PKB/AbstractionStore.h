#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

class AbstractionStore {
public:
	virtual void clear() = 0;
};

class StmtVarStore : public AbstractionStore {
	virtual bool hasVar(std::string varName) = 0;
	virtual bool hasStmt(int lineNum) = 0;
	virtual std::unordered_set<std::string> getAllVar() = 0;
	virtual std::unordered_set<int> getAllStmt() = 0;
};

class ProcVarStore : public AbstractionStore {
	virtual bool hasVar(std::string varName) = 0;
	virtual bool hasProc(std::string procName) = 0;
	virtual std::unordered_set<std::string> getAllVar() = 0;
	virtual std::unordered_set<std::string> getAllProc() = 0;
};