#pragma once
#include <stdio.h>
#include <vector>
#include <string>

#include "FollowsStore.h"
#include "EntityStore.h"
#include "PatternStore.h"
#include "FollowsStarStore.h"
#include "ModifiesProcStore.h"
#include "ModifiesStore.h"
#include "ParentStarStore.h"
#include "ParentStore.h"
#include "UsesProcStore.h"
#include "UsesStore.h"

class PkbPopulator {

private:
	shared_ptr<VariableStore> varStorage;
	shared_ptr<ConstantStore> constStorage;
	shared_ptr<FollowsStore> followsStorage;
	shared_ptr<ProcedureStore> procedureStorage;
	shared_ptr<StatementStore> statementStorage;
	shared_ptr<PatternStore> patternStorage;
	shared_ptr<FollowsStarStore> followsStarStorage;
	shared_ptr<ModifiesProcStore> modifiesProcStorage;
	shared_ptr<ModifiesStore> modifiesStorage;
	shared_ptr<ParentStarStore> parentStarStorage;
	shared_ptr<ParentStore> parentStorage;
	shared_ptr<UsesProcStore> usesProcStorage;
	shared_ptr<UsesStore> usesStorage;

public:
	PkbPopulator(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore, shared_ptr<FollowsStarStore> followsStarStore, shared_ptr<ModifiesProcStore> modifiesProcStore, shared_ptr<ModifiesStore> modifiesStore, shared_ptr<ParentStarStore> parentStarStore, shared_ptr<ParentStore> parentStore, shared_ptr<UsesProcStore> usesProcStorage, shared_ptr<UsesStore> usesStore);
	void addVar(std::string varName);
	void addConst(int constNum);
	void addFollows(int leftLineNum, int rightLineNum);
	void addProc(std::string procName);
	void addStmt(std::string stmtType, int lineNum);
	void addAssignLhs(std::string leftVar, int stmtNo);
	void addAssignRhs(int stmtNo, std::string rightStmt);
	void addFollowsStar(int followee, std::unordered_set<int> followerLst);
	void addModifiesProc(std::string procName, std::string varName);
	void addModifies(int lineNum, std::string varName);
	void addParentStar(int parent, int child);
	void addParent(int parent, int child);
	void addUsesProc(std::string procName, std::string varName);
	void addUses(int lineNum, std::string varName);
};