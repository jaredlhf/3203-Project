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
#include "CallsStore.h"
#include "CallsStarStore.h"

class PkbRetriever{
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
	PkbRetriever(std::shared_ptr<VariableStore> varStore, std::shared_ptr<ConstantStore> constStore, std::shared_ptr<FollowsStore> followsStore, std::shared_ptr<ProcedureStore> procedureStore, 
		std::shared_ptr<StatementStore> statementStore, std::shared_ptr<PatternStore> patternStore, std::shared_ptr<FollowsStarStore> followsStarStore, std::shared_ptr<ModifiesProcStore> modifiesProcStore, 
		std::shared_ptr<ModifiesStore> modifiesStore, std::shared_ptr<ParentStarStore> parentStarStore, std::shared_ptr<ParentStore> parentStore, std::shared_ptr<UsesProcStore> usesProcStorage, 
		std::shared_ptr<UsesStore> usesStore, std::shared_ptr<CallsStore> callsStore, std::shared_ptr<CallsStarStore> callsStarStore);
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
	/*Calls Store*/
	std::unordered_set<std::string> getLeftCall(std::string rightProc);
	std::unordered_set<std::string> getRightCall(std::string leftProc);
	std::unordered_set<std::string> getAllLeftCall();
	std::unordered_set<std::string> getAllRightCall();
	/*CallsStar Store*/
	std::unordered_set<std::string> getLeftCallStar(std::string rightProc);
	std::unordered_set<std::string> getRightCallStar(std::string leftProc);
	std::unordered_set<std::string> getAllLeftCallStar();
	std::unordered_set<std::string> getAllRightCallStar();
};