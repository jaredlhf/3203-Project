#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <memory>

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
#include "CallsStore.h"
#include "CallsStarStore.h"

class PkbPopulator {

private:
	std::shared_ptr<VariableStore> varStorage;
	std::shared_ptr<ConstantStore> constStorage;
	std::shared_ptr<FollowsStore> followsStorage;
	std::shared_ptr<ProcedureStore> procedureStorage;
	std::shared_ptr<StatementStore> statementStorage;
	std::shared_ptr<PatternStore> patternStorage;
	std::shared_ptr<FollowsStarStore> followsStarStorage;
	std::shared_ptr<ModifiesProcStore> modifiesProcStorage;
	std::shared_ptr<ModifiesStore> modifiesStorage;
	std::shared_ptr<ParentStarStore> parentStarStorage;
	std::shared_ptr<ParentStore> parentStorage;
	std::shared_ptr<UsesProcStore> usesProcStorage;
	std::shared_ptr<UsesStore> usesStorage;
	std::shared_ptr<CallsStore> callsStorage;
	std::shared_ptr<CallsStarStore> callsStarStorage;

public:
	PkbPopulator(std::shared_ptr<VariableStore> varStore, std::shared_ptr<ConstantStore> constStore, std::shared_ptr<FollowsStore> followsStore, std::shared_ptr<ProcedureStore> procedureStore, 
		std::shared_ptr<StatementStore> statementStore, std::shared_ptr<PatternStore> patternStore, std::shared_ptr<FollowsStarStore> followsStarStore, std::shared_ptr<ModifiesProcStore> modifiesProcStore, 
		std::shared_ptr<ModifiesStore> modifiesStore, std::shared_ptr<ParentStarStore> parentStarStore, std::shared_ptr<ParentStore> parentStore, std::shared_ptr<UsesProcStore> usesProcStorage, 
		std::shared_ptr<UsesStore> usesStore, std::shared_ptr<CallsStore> callsStore, std::shared_ptr<CallsStarStore> callsStarStore);
	void addVar(std::string varName);
	void addConst(int constNum);
	void addFollows(int leftLineNum, int rightLineNum);
	void addProc(std::string procName);
	void addStmt(std::string stmtType, int lineNum);
	void addAssignLhs(std::string leftVar, int stmtNo);
	void addAssignRhs(int stmtNo, std::string rightStmt);
	void addFollowsStar(int leftLineNum, std::unordered_set<int> rightLineNumLst);
	void addModifiesProc(std::string procName, std::string varName);
	void addModifies(int lineNum, std::string varName);
	void addParentStar(int parent, int child);
	void addParent(int parent, int child);
	void addUsesProc(std::string procName, std::string varName);
	void addUses(int lineNum, std::string varName);
	void addCallsStar(std::string leftProc, std::string rightProc);
	void addCalls(std::string leftProc, std::string rightProc);
	
};