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
#include "AttributeStore.h"
#include "NextStore.h"
#include "CFGStore.h"
#include "ContainCallsStore.h"

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
	shared_ptr<CallsStore> callsStorage;
	shared_ptr<CallsStarStore> callsStarStorage;
	shared_ptr<PrintAttribute> printAttrStorage;
	shared_ptr<ReadAttribute> readAttrStorage;
	shared_ptr<CallAttribute> callAttrStorage;
	shared_ptr<NextStore> nextStorage;
	shared_ptr<CFGStore> cfgStorage;
	shared_ptr<ContainCallsStore> conCallStorage;

public:
	PkbPopulator(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, 
		shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore, shared_ptr<FollowsStarStore> followsStarStore, shared_ptr<ModifiesProcStore> modifiesProcStore, 
		shared_ptr<ModifiesStore> modifiesStore, shared_ptr<ParentStarStore> parentStarStore, shared_ptr<ParentStore> parentStore, shared_ptr<UsesProcStore> usesProcStorage, 
		shared_ptr<UsesStore> usesStore, shared_ptr<CallsStore> callsStore, shared_ptr<CallsStarStore> callsStarStore, shared_ptr<PrintAttribute> printAttrStore, 
		shared_ptr<ReadAttribute> readAttrStore, shared_ptr<CallAttribute> callAttrStore, shared_ptr<NextStore> nextStore, shared_ptr<CFGStore> cfgStore, shared_ptr<ContainCallsStore> conCallStore);
	void addVar(std::string varName);
	void addConst(int constNum);
	void addFollows(int leftLineNum, int rightLineNum);
	void addProc(std::string procName, int lineNum);
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
	void addIfStatement(int stmtNo, std::string varName);
	void addIfStatementVar(std::string varName, int stmtNo);
	void addWhileStatement(int stmtNo, std::string varName);
	void addWhileStatementVar(std::string varName, int stmtNo);
	void addPrintAttr(std::string varName, int lineNum);
	void addReadAttr(std::string varName, int lineNum);
	void addCallAttr(std::string procName, int lineNum);
	void addNext(int leftLineNum, int rightLineNum);
	void addCFGNode(std::string procName, shared_ptr<CFGNode> node);
	void addContainCalls(int lineNum, std::string procName);
};