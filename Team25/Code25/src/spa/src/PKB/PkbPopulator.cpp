#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "PkbPopulator.h"

/*
 * Constructor class for PkbPopulator
 * param: VarStorage* varStore
 */
PkbPopulator::PkbPopulator(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore, shared_ptr<FollowsStarStore> followsStarStore, shared_ptr<ModifiesProcStore> modifiesProcStore, shared_ptr<ModifiesStore> modifiesStore, shared_ptr<ParentStarStore> parentStarStore, shared_ptr<ParentStore> parentStore, shared_ptr<UsesStore> usesStore) {
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
	this->usesStorage = usesStore;
}


void PkbPopulator::addVar(std::string varName) {
	this->varStorage->add(varName);
}

void PkbPopulator::addConst(int constNum) {
	this->constStorage->add(constNum);
}

void PkbPopulator::addFollows(int leftLineNum, int rightLineNum) {
	this->followsStorage->addFollows(leftLineNum, rightLineNum);
}

void PkbPopulator::addProc(std::string procName) {
	this->procedureStorage->add(procName);
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
	this->modifiesStorage->add(lineNum, varName);
}

void PkbPopulator::addParentStar(int parent, int child) {
	this->parentStarStorage->addParentStar(parent, child);
}

void PkbPopulator::addParent(int parent, int child) {
	this->parentStorage->addParent(parent, child);
}

void PkbPopulator::addUses(int lineNum, std::string varName) {
	this->usesStorage->add(lineNum, varName);
}



 