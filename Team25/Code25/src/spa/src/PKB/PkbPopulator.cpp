#include<stdio.h>
#include <vector>
#include <string>

using namespace std;

#include "PkbPopulator.h"
#include "FollowsStore.h"
#include "StatementStore.h"
#include "EntityStore.h"

/*
 * Constructor class for PkbPopulator
 * param: VarStorage* varStore
 */
PkbPopulator::PkbPopulator(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore) {
	this->varStorage = varStore;
	this->constStorage = constStore;
	this->followsStorage = followsStore;
	this->procedureStorage = procedureStore;
	this->statementStorage = statementStore;
};


void PkbPopulator::addVar(std::string varName) {
	this->varStorage->add(varName);
};

void PkbPopulator::addConst(int constNum) {
	this->constStorage->add(constNum);
};

void PkbPopulator::addFollows(int leftLineNum, int rightLineNum) {
	this->followsStorage->addFollows(leftLineNum, rightLineNum);
};

void PkbPopulator::addProc(std::string procName) {
	this->procedureStorage->add(procName);
};

void PkbPopulator::addStmt(std::string stmtType, int lineNum) {
	this->statementStorage->addStmt(stmtType, lineNum);
};




 