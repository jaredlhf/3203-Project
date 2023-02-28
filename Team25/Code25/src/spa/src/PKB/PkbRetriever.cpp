#include<stdio.h>
#include <unordered_set>
#include <string>

using namespace std;

#include "PkbRetriever.h"

/*
 * Constructor class for PkbRetriever
 * param: VarStorage* varStore
 */

PkbRetriever::PkbRetriever(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore, shared_ptr<FollowsStarStore> followsStarStore, shared_ptr<ModifiesProcStore> modifiesProcStore, shared_ptr<ModifiesStore> modifiesStore, shared_ptr<ParentStarStore> parentStarStore, shared_ptr<ParentStore> parentStore, shared_ptr<UsesStore> usesStore) {
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
};

std::unordered_set<std::string> PkbRetriever::getAllVar() {
	return this->varStorage->getAllVar();
}

std::unordered_set<int> PkbRetriever::getAllConst() {
	return this->constStorage->getAllConst();
}

int PkbRetriever::getFollowee(int rightLineNum) {
	return this->followsStorage->getLeftStmt(rightLineNum);
}

int PkbRetriever::getFollower(int leftLineNum) {
	return this->followsStorage->getRightStmt(leftLineNum);
}

std::unordered_set<int> PkbRetriever::getAllFollowers() {
	return this->followsStorage->getAllRight();
}

std::unordered_set<int> PkbRetriever::getAllFollowees() {
	return this->followsStorage->getAllLeft();
}

std::unordered_set<std::string> PkbRetriever::getAllProc() {
	return this->procedureStorage->getAllProc();
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

std::unordered_set<int> PkbRetriever::getFolloweeStar(int follower) {
	return this->followsStarStorage->getFolloweeStar(follower);
}

std::unordered_set<int> PkbRetriever::getFollowerStar(int followee) {
	return this->followsStarStorage->getFollowerStar(followee);
}

std::unordered_set<std::string> PkbRetriever::getModVar(int lineNum) {
	return this->modifiesStorage->getVar(lineNum);
}

std::unordered_set<int> PkbRetriever::getModStmt(std::string varName) {
	return this->modifiesStorage->getStmt(varName);
}

std::unordered_set<int> PkbRetriever::getParentStar(int child) {
	return this->parentStarStorage->getParentStar(child);
}
std::unordered_set<int> PkbRetriever::getChildrenStar(int parent) {
	return this->parentStarStorage->getChildrenStar(parent);
}

int PkbRetriever::getParent(int child) {
	return this->parentStorage->getLeftStmt(child);
}

std::unordered_set<int> PkbRetriever::getChildren(int parent) {
	return this->parentStorage->getRightStmt(parent);
}

std::unordered_set<std::string> PkbRetriever::getUsesVar(int lineNum) {
	return this->usesStorage->getVar(lineNum);
}
std::unordered_set<int> PkbRetriever::getUsesStmt(std::string varName) {
	return this->usesStorage->getStmt(varName);
}