#pragma once

#include <stdio.h>
#include <unordered_set>
#include <string>

using namespace std;

#include "VariableStore.h"
#include "ConstantStore.h"
#include "FollowsStore.h"
#include "ProcedureStore.h"
#include "StatementStore.h"

class PkbRetriever{
private:
	shared_ptr<VariableStore> varStorage;
	shared_ptr<ConstantStore> constStorage;
	shared_ptr<FollowsStore> followsStorage;
	shared_ptr<ProcedureStore> procedureStorage;
	shared_ptr<StatementStore> statementStorage;

public:
	PkbRetriever(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore);
	std::unordered_set<std::string> getAllVar();
	std::unordered_set<int> getAllConst();
	int getFollowee(int rightLineNum);
	int getFollower(int leftLineNum);
	std::unordered_set<int> getAllFollowers();
	std::unordered_set<int> getAllFollowees();
	std::unordered_set<string> getAllProc();
	std::unordered_set<int> getAllStmt(string stmtType);
};