#include<stdio.h>
#include <unordered_set>
#include <memory>
#include <string>


#include "PkbRetriever.h"

/*
 * Constructor class for PkbRetriever
 * param: VarStorage* varStore
 */

PkbRetriever::PkbRetriever(shared_ptr<VariableStore> varStore, shared_ptr<ConstantStore> constStore, shared_ptr<FollowsStore> followsStore, shared_ptr<ProcedureStore> procedureStore, 
	shared_ptr<StatementStore> statementStore, shared_ptr<PatternStore> patternStore, shared_ptr<FollowsStarStore> followsStarStore, shared_ptr<ModifiesProcStore> modifiesProcStore, 
	shared_ptr<ModifiesStore> modifiesStore, shared_ptr<ParentStarStore> parentStarStore, shared_ptr<ParentStore> parentStore, shared_ptr<UsesProcStore> usesProcStore, 
	shared_ptr<UsesStore> usesStore, shared_ptr<CallsStore> callsStore, shared_ptr<CallsStarStore> callsStarStore, shared_ptr<PrintAttribute> printAttrStore, 
	shared_ptr<ReadAttribute> readAttrStore, shared_ptr<CallAttribute> callAttrStore, shared_ptr<NextStore> nextStore, shared_ptr<CFGStore> cfgStore, shared_ptr<ContainCallsStore> conCallStore) {
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
	this->printAttrStorage = printAttrStore;
	this->readAttrStorage = readAttrStore;
	this->callAttrStorage = callAttrStore;
	this->nextStorage = nextStore;
	this->cfgStorage = cfgStore;
	this->conCallStorage = conCallStore;
};

/*Var Store*/
std::unordered_set<std::string> PkbRetriever::getAllVar() {
	return this->varStorage->getAllVar();
}

/*Const Store*/
std::unordered_set<int> PkbRetriever::getAllConst() {
	return this->constStorage->getAllConst();
}

/*Procedure Store*/
std::string PkbRetriever::getProc(int lineNum) {
	return this->procedureStorage->getProc(lineNum);
}

std::unordered_set<int> PkbRetriever::getStmt(std::string procName) {
	return this->procedureStorage->getStmt(procName);
}

std::unordered_set<std::string> PkbRetriever::getAllProc() {
	return this->procedureStorage->getAllProc();
}

/*Statement Store*/
std::unordered_set<int> PkbRetriever::getAllStmt(std::string stmtType) {
	return this->statementStorage->getAllStmt(stmtType);
}

/*Pattern Store*/
std::string PkbRetriever::getAssignRhs(int stmtNo) {
	return this->patternStorage->getAssignRhs(stmtNo);
}

std::unordered_set<int> PkbRetriever::getAssignLhs(std::string leftVar) {
	return this->patternStorage->getAssignLhs(leftVar);
}

std::unordered_set<std::string> PkbRetriever::getIfVars(int stmtNo) {
	return this->patternStorage->getIfVars(stmtNo);
}

std::unordered_set<int> PkbRetriever::getIfStatements(std::string varName) {
	return this->patternStorage->getIfStatements(varName);
}

std::unordered_set<std::string> PkbRetriever::getWhileVars(int stmtNo) {
	return this->patternStorage->getWhileVars(stmtNo);
}

std::unordered_set<int> PkbRetriever::getWhileStatements(std::string varName) {
	return this->patternStorage->getWhileStatements(varName);
}

/*FollowsStar Store*/
std::unordered_set<int> PkbRetriever::getFolloweeStar(int follower) {
	return this->followsStarStorage->getLeftStar(follower);
}

std::unordered_set<int> PkbRetriever::getFollowerStar(int followee) {
	return this->followsStarStorage->getRightStar(followee);
}

std::unordered_set<int> PkbRetriever::getAllFollowerStar() {
	return this->followsStarStorage->getAllRight();
}
std::unordered_set<int> PkbRetriever::getAllFolloweeStar() {
	return this->followsStarStorage->getAllLeft();
}

/*Follows Store*/
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

/*ParentStar Store*/
std::unordered_set<int> PkbRetriever::getParentStar(int child) {
	return this->parentStarStorage->getLeftStar(child);
}
std::unordered_set<int> PkbRetriever::getChildrenStar(int parent) {
	return this->parentStarStorage->getRightStar(parent);
}

std::unordered_set<int> PkbRetriever::getAllParentStar() {
	return this->parentStarStorage->getAllLeft();
}

std::unordered_set<int> PkbRetriever::getAllChildrenStar() {
	return this->parentStarStorage->getAllRight();
}

/*Parent Store*/
int PkbRetriever::getParent(int child) {
	return this->parentStorage->getLeftStmt(child);
}

std::unordered_set<int> PkbRetriever::getChildren(int parent) {
	return this->parentStorage->getRightStmt(parent);
}

std::unordered_set<int> PkbRetriever::getAllParents() {
	return this->parentStorage->getAllLeft();
}

std::unordered_set<int> PkbRetriever::getAllChildren() {
	return this->parentStorage->getAllRight();
}

/*ModifiesProc Store*/
std::unordered_set<std::string> PkbRetriever::getModPVar(std::string procName) {
	return this->modifiesProcStorage->getVar(procName);
}

std::unordered_set<std::string> PkbRetriever::getModPProc(std::string varName) {
	return this->modifiesProcStorage->getProc(varName);
}

std::unordered_set<std::string> PkbRetriever::getAllModPVar() {
	return this->modifiesProcStorage->getAllVar();
}

std::unordered_set<std::string> PkbRetriever::getAllModPProc() {
	return this->modifiesProcStorage->getAllProc();
}

/*Modifies Store*/
std::unordered_set<std::string> PkbRetriever::getModVar(int lineNum) {
	return this->modifiesStorage->getVar(lineNum);
}

std::unordered_set<int> PkbRetriever::getModStmt(std::string varName) {
	return this->modifiesStorage->getStmt(varName);
}

std::unordered_set<std::string> PkbRetriever::getAllModVar() {
	return this->modifiesStorage->getAllVar();
}

std::unordered_set<int> PkbRetriever::getAllModStmt() {
	return this->modifiesStorage->getAllStmt();
}

/*UsesProc Store*/
std::unordered_set<std::string> PkbRetriever::getUsesPVar(std::string procName) {
	return this->usesProcStorage->getVar(procName);
}

std::unordered_set<std::string> PkbRetriever::getUsesPProc(std::string varName) {
	return this->usesProcStorage->getProc(varName);
}

std::unordered_set<std::string> PkbRetriever::getAllUsesPVar() {
	return this->usesProcStorage->getAllVar();
}

std::unordered_set<std::string> PkbRetriever::getAllUsesPProc() {
	return this->usesProcStorage->getAllProc();
}

/*Uses Store*/
std::unordered_set<std::string> PkbRetriever::getUsesVar(int lineNum) {
	return this->usesStorage->getVar(lineNum);
}

std::unordered_set<int> PkbRetriever::getUsesStmt(std::string varName) {
	return this->usesStorage->getStmt(varName);
}

std::unordered_set<std::string> PkbRetriever::getAllUsesVar() {
	return this->usesStorage->getAllVar();
}

std::unordered_set<int> PkbRetriever::getAllUsesStmt() {
	return this->usesStorage->getAllStmt();
}

/*Calls Store*/
std::unordered_set<std::string> PkbRetriever::getLeftCall(std::string rightProc) {
	return this->callsStorage->getLeftProc(rightProc);
}

std::unordered_set<std::string> PkbRetriever::getRightCall(std::string leftProc) {
	return this->callsStorage->getRightProc(leftProc);
}

std::unordered_set<std::string> PkbRetriever::getAllLeftCall() {
	return this->callsStorage->getAllLeft();
}

std::unordered_set<std::string> PkbRetriever::getAllRightCall() {
	return this->callsStorage->getAllRight();
}

/*CallsStar Store*/
std::unordered_set<std::string> PkbRetriever::getLeftCallStar(std::string rightProc) {
	return this->callsStarStorage->getLeftStar(rightProc);
}

std::unordered_set<std::string> PkbRetriever::getRightCallStar(std::string leftProc) {
	return this->callsStarStorage->getRightStar(leftProc);
}

std::unordered_set<std::string> PkbRetriever::getAllLeftCallStar() {
	return this->callsStarStorage->getAllLeft();
}

std::unordered_set<std::string> PkbRetriever::getAllRightCallStar() {
	return this->callsStarStorage->getAllRight();
}

/*Print Attribute Store*/
std::string PkbRetriever::getPrintAttr(int lineNum) {
	return this->printAttrStorage->getAttr(lineNum);
}

std::unordered_set<int> PkbRetriever::getPrintStmt(std::string varName) {
	return this->printAttrStorage->getStmt(varName);
}

std::unordered_set<std::string> PkbRetriever::getAllPrintAttr() {
	return this->printAttrStorage->getAllAttr();
}

std::unordered_set<int> PkbRetriever::getAllPrintStmt() {
	return this->printAttrStorage->getAllStmt();
}

/*Read Attribute Store*/
std::string PkbRetriever::getReadAttr(int lineNum) {
	return this->readAttrStorage->getAttr(lineNum);
}

std::unordered_set<int> PkbRetriever::getReadStmt(std::string varName) {
	return this->readAttrStorage->getStmt(varName);
}

std::unordered_set<std::string> PkbRetriever::getAllReadAttr() {
	return this->readAttrStorage->getAllAttr();
}

std::unordered_set<int> PkbRetriever::getAllReadStmt() {
	return this->readAttrStorage->getAllStmt();
}

/*Call Attribute Store*/
std::string PkbRetriever::getCallAttr(int lineNum) {
	return this->callAttrStorage->getAttr(lineNum);
}

std::unordered_set<int> PkbRetriever::getCallStmt(std::string procName) {
	return this->callAttrStorage->getStmt(procName);
}

std::unordered_set<std::string> PkbRetriever::getAllCallAttr() {
	return this->callAttrStorage->getAllAttr();
}

std::unordered_set<int> PkbRetriever::getAllCallStmt() {
	return this->callAttrStorage->getAllStmt();
}

/*Next Store*/
std::unordered_set<int> PkbRetriever::getLeftNext(int rightStmt) {
	return this->nextStorage->getLeftStmt(rightStmt);
}

std::unordered_set<int> PkbRetriever::getRightNext(int leftStmt) {
	return this->nextStorage->getRightStmt(leftStmt);
}

std::unordered_set<int> PkbRetriever::getAllLeftNext() {
	return this->nextStorage->getAllLeft();
}

std::unordered_set<int> PkbRetriever::getAllRightNext() {
	return this->nextStorage->getAllRight();
}

std::unordered_set<int> PkbRetriever::getRightNextStar(int leftStmt) {
	return this->nextStorage->getRightStmtStar(leftStmt);
}

std::unordered_set<int> PkbRetriever::getLeftNextStar(int rightStmt) {
	return this->nextStorage->getLeftStmtStar(rightStmt);
}

/*CFG Store*/
std::shared_ptr<CFGNode> PkbRetriever::getCFGNode(std::string procName) {
	return this->cfgStorage->getCFGNode(procName);
}

std::vector<std::shared_ptr<CFGNode>> PkbRetriever::getAllCFGNodes() {
	return this->cfgStorage->getAllCFGNodes();
}

std::vector<std::shared_ptr<CFGNode>> PkbRetriever::getNextNodes(std::shared_ptr<CFGNode> currNode) {
	return this->cfgStorage->getNextNodes(currNode);
}

std::vector<int> PkbRetriever::getLineNo(std::shared_ptr<CFGNode> currNode) {
	return this->cfgStorage->getLineNo(currNode);
}

/*Container Calls Store*/
std::unordered_set<std::string> PkbRetriever::getConProc(int lineNum) {
	return this->conCallStorage->getProc(lineNum);
}

std::unordered_set<int> PkbRetriever::getConStmt(std::string procName) {
	return this->conCallStorage->getStmt(procName);
}

std::unordered_set<std::string> PkbRetriever::getAllConProc() {
	return this->conCallStorage->getAllProc();
}

std::unordered_set<int> PkbRetriever::getAllConStmt() {
	return this->conCallStorage->getAllStmt();
}