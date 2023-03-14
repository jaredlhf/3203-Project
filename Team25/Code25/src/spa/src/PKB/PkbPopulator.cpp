#include<stdio.h>
#include <vector>
#include <string>

#include "PkbPopulator.h"

/*
 * Constructor class for PkbPopulator
 * param: VarStorage* varStore
 */
PkbPopulator::PkbPopulator(std::shared_ptr<VariableStore> varStore, std::shared_ptr<ConstantStore> constStore, std::shared_ptr<FollowsStore> followsStore, std::shared_ptr<ProcedureStore> procedureStore,
                           std::shared_ptr<StatementStore> statementStore, std::shared_ptr<PatternStore> patternStore, std::shared_ptr<FollowsStarStore> followsStarStore, std::shared_ptr<ModifiesProcStore> modifiesProcStore,
                           std::shared_ptr<ModifiesStore> modifiesStore, std::shared_ptr<ParentStarStore> parentStarStore, std::shared_ptr<ParentStore> parentStore, std::shared_ptr<UsesProcStore> usesProcStore,
                           std::shared_ptr<UsesStore> usesStore, std::shared_ptr<CallsStore> callsStore, std::shared_ptr<CallsStarStore> callsStarStore) {
	this->varStorage = varStore;
	this->constStorage = constStore;
	this->followsStorage = followsStore;
	this->procedureStorage = procedureStore;
	this->statementStorage = statementStore;
	this->patternStorage = patternStore;
	this->followsStarStorage = followsStarStore;
	this->modifiesProcStorage = modifiesProcStore;
	this->modifiesStorage = modifiesStore;
	this->parentStarStorage = parentStarStore;
	this->parentStorage = parentStore;
	this->usesProcStorage = usesProcStore;
	this->usesStorage = usesStore;
	this->callsStorage = callsStore;
	this->callsStarStorage = callsStarStore;
}


void PkbPopulator::addVar(std::string varName) {
	this->varStorage->addVar(varName);
}

void PkbPopulator::addConst(int constNum) {
	this->constStorage->addConst(constNum);
}

void PkbPopulator::addFollows(int leftLineNum, int rightLineNum) {
	this->followsStorage->addFollows(leftLineNum, rightLineNum);
}

void PkbPopulator::addProc(std::string procName) {
	this->procedureStorage->addProc(procName);
}

void PkbPopulator::addStmt(std::string stmtType, int lineNum) {
	this->statementStorage->addStmt(stmtType, lineNum);
}

void PkbPopulator::addAssignLhs(std::string leftVar, int stmtNo) {
	this->patternStorage->addAssignLhs(leftVar, stmtNo);
}

void PkbPopulator::addAssignRhs(int stmtNo, std::string rightStmt) {
	this->patternStorage->addAssignRhs(stmtNo, rightStmt);
}

void PkbPopulator::addFollowsStar(int followee, std::unordered_set<int> followerLst) {
	this->followsStarStorage->addFollowsStar(followee, followerLst);
}

void PkbPopulator::addModifiesProc(std::string procName, std::string varName) {
	this->modifiesProcStorage->addModifiesProc(procName, varName);
}

void PkbPopulator::addModifies(int lineNum, std::string varName) {
	this->modifiesStorage->addModifies(lineNum, varName);
}

void PkbPopulator::addParentStar(int parent, int child) {
	this->parentStarStorage->addParentStar(parent, child);
}

void PkbPopulator::addParent(int parent, int child) {
	this->parentStorage->addParent(parent, child);
}

void PkbPopulator::addUsesProc(std::string procName, std::string varName) {
	this->usesProcStorage->addUsesProc(procName, varName);
}

void PkbPopulator::addUses(int lineNum, std::string varName) {
	this->usesStorage->addUses(lineNum, varName);
}

void PkbPopulator::addCallsStar(std::string leftProc, std::string rightProc) {
	this->callsStarStorage->addCallsStar(leftProc, rightProc);
}

void PkbPopulator::addCalls(std::string leftProc, std::string rightProc) {
	this->callsStorage->addCalls(leftProc, rightProc);
}


 