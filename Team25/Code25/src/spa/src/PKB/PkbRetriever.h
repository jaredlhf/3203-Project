#pragma once

#include <stdio.h>
#include <unordered_set>
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

class PkbRetriever{
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
	PkbRetriever(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore, shared_ptr<FollowsStarStore> followsStarStore, shared_ptr<ModifiesProcStore> modifiesProcStore, shared_ptr<ModifiesStore> modifiesStore, shared_ptr<ParentStarStore> parentStarStore, shared_ptr<ParentStore> parentStore, shared_ptr<UsesProcStore> usesProcStorage, shared_ptr<UsesStore> usesStore);
	/*Var Store*/
	std::unordered_set<std::string> getAllVar(); 
	/*Const Store*/
	std::unordered_set<int> getAllConst(); 
	/*Procedure Store*/
	std::unordered_set<string> getAllProc(); 
	/*Statement Store*/
	std::unordered_set<int> getAllStmt(string stmtType); 
	/*Pattern Store*/
	std::unordered_set<int> getAssignLhs(std::string leftVar); 
	std::string getAssignRhs(int stmtNo);
	/*FollowsStar Store*/
	std::unordered_set<int> getFolloweeStar(int rightLineNum);
	std::unordered_set<int> getFollowerStar(int leftLineNum);
	std::unordered_set<int> getAllFollowerStar();
	std::unordered_set<int> getAllFolloweeStar();
	/*Follows Store*/
	int getFollowee(int rightLineNum);
	int getFollower(int leftLineNum);
	std::unordered_set<int> getAllFollowers();
	std::unordered_set<int> getAllFollowees();
	/*ParentStar Store*/
	std::unordered_set<int> getParentStar(int child);
	std::unordered_set<int> getChildrenStar(int parent);
	std::unordered_set<int> getAllParentStar();
	std::unordered_set<int> getAllChildrenStar();
	/*Parent Store*/
	int getParent(int child);
	std::unordered_set<int> getChildren(int parent);
	std::unordered_set<int> getAllParents();
	std::unordered_set<int> getAllChildren();
	/*ModifiesProc Store*/
	std::unordered_set<std::string> getModPVar(std::string procName);
	std::unordered_set<std::string> getModPProc(std::string varName);
	std::unordered_set<std::string> getAllModPVar();
	std::unordered_set<std::string> getAllModPProc();
	/*Modifies Store*/
	std::unordered_set<std::string> getModVar(int lineNum); 
	std::unordered_set<int> getModStmt(std::string varName);
	std::unordered_set<std::string> getAllModVar();
	std::unordered_set<int> getAllModStmt();
	/*UsesProc Store*/
	std::unordered_set<std::string> getUsesPVar(std::string procName);
	std::unordered_set<std::string> getUsesPProc(std::string varName);
	std::unordered_set<std::string> getAllUsesPVar();
	std::unordered_set<std::string> getAllUsesPProc();
	/*Uses Store*/
	std::unordered_set<std::string> getUsesVar(int lineNum);
	std::unordered_set<int> getUsesStmt(std::string varName);
	std::unordered_set<std::string> getAllUsesVar();
	std::unordered_set<int> getAllUsesStmt();
};