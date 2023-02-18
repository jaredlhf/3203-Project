#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "PkbPopulator.h"

/*
 * Constructor class for PkbPopulator
 * param: VarStorage* varStore
 */
PkbPopulator::PkbPopulator(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore) {
	this->varStorage = varStore;
	this->constStorage = constStore;
	this->followsStorage = followsStore;
	this->procedureStorage = procedureStore;
	this->statementStorage = statementStore;
	this->patternStorage = patternStore;
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




 