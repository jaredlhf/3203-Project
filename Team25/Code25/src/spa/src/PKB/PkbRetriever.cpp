#include<stdio.h>
#include <unordered_set>
#include <string>

using namespace std;

#include "PkbRetriever.h"

/*
 * Constructor class for PkbRetriever
 * param: VarStorage* varStore
 */

PkbRetriever::PkbRetriever(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore) {
	this->varStorage = varStore;
	this->constStorage = constStore;
	this->followsStorage = followsStore;
	this->procedureStorage = procedureStore;
	this->statementStorage = statementStore;
	this->patternStorage = patternStore;
};

std::unordered_set<std::string> PkbRetriever::getAllVar() {
	return this->varStorage->getAll();
}

std::unordered_set<int> PkbRetriever::getAllConst() {
	return this->constStorage->getAll();
}

int PkbRetriever::getFollowee(int rightLineNum) {
	return this->followsStorage->getFollowee(rightLineNum);
}

int PkbRetriever::getFollower(int leftLineNum) {
	return this->followsStorage->getFollower(leftLineNum);
}

std::unordered_set<int> PkbRetriever::getAllFollowers() {
	return this->followsStorage->getAllFollowers();
}

std::unordered_set<int> PkbRetriever::getAllFollowees() {
	return this->followsStorage->getAllFollowees();
}

std::unordered_set<std::string> PkbRetriever::getAllProc() {
	return this->procedureStorage->getAll();
}

std::unordered_set<int> PkbRetriever::getAllStmt(std::string stmtType) {
	return this->statementStorage->getAllStmt(stmtType);
}

std::unordered_set<int> PkbRetriever::getAssignLhs(std::string leftVar) {
	return this->patternStorage->getAssignLhs(leftVar);
}
	
std::string PkbRetriever::getAssignRhs(int stmtNo) {
	return this->patternStorage->getAssignRhs(stmtNo);
}