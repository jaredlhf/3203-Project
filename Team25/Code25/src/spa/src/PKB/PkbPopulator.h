#pragma once
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "VariableStore.h"
#include "ConstantStore.h"
#include "FollowsStore.h"
#include "ProcedureStore.h"
#include "StatementStore.h"

class PkbPopulator {

private:
	VariableStore* varStorage;
	ConstantStore* constStorage;
	FollowsStore* followsStorage;
	ProcedureStore* procedureStorage;
	StatementStore* statementStorage;

public:
	PkbPopulator(VariableStore* varStore, ConstantStore* constStore, FollowsStore* followsStore, ProcedureStore* procedureStore, StatementStore* statementStore);
	void addVar(std::string varName);
	void addConst(int constNum);
	void addFollows(int leftLineNum, int rightLineNum);
	void addProc(std::string procName);
	void addStmt(std::string stmtType, int lineNum);
};