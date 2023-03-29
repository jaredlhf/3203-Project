#include "QueryUtils.h"

template<typename T>
bool QueryUtils::isEmpty(std::unordered_set<T> set) {
	return set.size() <= 0;
}

template<typename T>
bool QueryUtils::isNotEmpty(std::unordered_set<T> set) {
	return !isEmpty(set);
}

template<typename T>
bool QueryUtils::contains(std::unordered_set<T> set, T item) {
	return set.count(item) > 0;
}

bool QueryUtils::isAssignStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet) {
	std::unordered_set<int> asgSet = pkbRet->getAllStmt(Constants::ASSIGN);
	return contains(asgSet, lineNum);
}

bool QueryUtils::isContainerStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet) {
	std::unordered_set<int> whileSet = pkbRet->getAllStmt(Constants::WHILE);
	std::unordered_set<int> ifSet = pkbRet->getAllStmt(Constants::IF);
	return contains(whileSet, lineNum) || contains(ifSet, lineNum);
}

std::unordered_set<std::string> QueryUtils::getModifiesInNonContainStmt(int lineNum, 
	std::shared_ptr<PkbRetriever> pkbRet) {
	// handle call stmts vs normal stmts
	std::unordered_set<int> callStmts = pkbRet->getAllStmt(Constants::CALL);
	std::unordered_set<std::string> lineMods =
		std::find(callStmts.begin(), callStmts.end(), lineNum) == callStmts.end()
		? pkbRet->getModVar(lineNum)
		: ModStrat::getAllVarModByProc(pkbRet->getCallAttr(lineNum), pkbRet);

	return lineMods;
}

bool QueryUtils::affects(int modLine, int usesLine, std::shared_ptr<PkbRetriever> pkbRet) {
	// Edge case: return false if neither is an assign stmt
	if (!isAssignStmt(modLine, pkbRet) || !isAssignStmt(usesLine, pkbRet)) {
		return false;
	}

	// Edge case: return false if modLine and usesLine are not in the same procedure
	if (pkbRet->getProc(modLine) != pkbRet->getProc(usesLine)) {
		return false;
	}

	// Get variable modified in modLine (Guaranteed to be 1 item in set since it is an assign stmt)
	std::unordered_set<std::string> modSet = pkbRet->getModVar(modLine);
	std::string modVar;
	for (std::string var : modSet) {
		modVar = var;
	}

	std::unordered_set<std::string> usesSet = pkbRet->getUsesVar(usesLine);
	// Return false if modVar is not in usesSet
	if (std::find(usesSet.begin(), usesSet.end(), modVar) == usesSet.end()) {
		return false;
	}

	std::string mainProc = pkbRet->getProc(modLine);
	std::shared_ptr<CFGNode> rootNode = getNodeOfLine(modLine, pkbRet->getCFGNode(mainProc));
	// Check if base cfg node has new modifies (base cfg node will not be a if or while node)
	std::vector<int> rootLines = rootNode->getLineNo();
	std::unordered_set<std::string> otherModInNode;
	for (int nextLine : rootLines) {
		if (nextLine > modLine && nextLine < usesLine) {
			std::unordered_set<std::string> lineMods = getModifiesInNonContainStmt(nextLine, pkbRet);
			otherModInNode.insert(lineMods.begin(), lineMods.end());
		}
	}

	// If modVar is found elsewhere in curr node, return false
	if (std::find(otherModInNode.begin(), otherModInNode.end(), modVar) != otherModInNode.end()) {
		return false;
	}

	// Use dfs to determine if its modified again in path
	std::unordered_set<std::shared_ptr<CFGNode>> baseSet;
	NodeVisitSet visitedSet = std::make_shared<std::unordered_set<std::shared_ptr<CFGNode>>>(baseSet);
	std::vector<std::shared_ptr<CFGNode>> nextNodes = rootNode->getAllNextNodes();
	std::shared_ptr<CFGNode> nextNode = nextNodes.size() > 0
		? nextNodes[0]
		: nullptr;
	return recursivelyNoModifies(modVar, nextNode, visitedSet, pkbRet, usesLine);
}

bool QueryUtils::recursivelyNoModifies(std::string modVar, std::shared_ptr<CFGNode> rootNode,
	NodeVisitSet visitedSet, std::shared_ptr<PkbRetriever> pkbRet, int usesLine) {
	if (!rootNode) {
		return true;
	}

	visitedSet->insert(rootNode);
	std::vector<int> nodeLines = rootNode->getLineNo();
	bool hasNoModifies = true;
	bool skipCurrNode = nodeLines.size() == 1 && isContainerStmt(nodeLines[0], pkbRet);
	if (!skipCurrNode) {
		std::unordered_set<std::string> modVars;
		// check for mods in curr node
		bool isUsesNode = std::find(nodeLines.begin(), nodeLines.end(), usesLine) != nodeLines.end();
		for (int line : nodeLines) {
			std::unordered_set<std::string> lineMods = getModifiesInNonContainStmt(line, pkbRet);
			modVars.insert(lineMods.begin(), lineMods.end());
		}

		if (std::find(modVars.begin(), modVars.end(), modVar) != modVars.end()) {
			return false;
		}
	}

	// Add next nodes to visit
	std::vector<std::shared_ptr<CFGNode>> nextNodes = rootNode->getAllNextNodes();
	for (std::shared_ptr<CFGNode> nextNode : nextNodes) {
		if (std::find(visitedSet->begin(), visitedSet->end(), nextNode) == visitedSet->end()) {
			hasNoModifies = hasNoModifies && 
				recursivelyNoModifies(modVar, nextNode, visitedSet, pkbRet, usesLine);
		}

		if (!hasNoModifies) {
			return hasNoModifies;
		}
	}

	visitedSet->erase(rootNode);
	return hasNoModifies;
}

std::shared_ptr<CFGNode> QueryUtils::getNodeOfLine(int lineNum, std::shared_ptr<CFGNode> rootNode) {
	std::queue<std::shared_ptr<CFGNode>> visitQueue;
	visitQueue.push(rootNode);
	while (visitQueue.size() > 0) {
		std::shared_ptr<CFGNode> curr = visitQueue.front();
		visitQueue.pop();
		if (!curr) {
			continue;
		}
		std::vector<int> nodeLines = curr->getLineNo();
		if (std::find(nodeLines.begin(), nodeLines.end(), lineNum) != nodeLines.end()) {
			return curr;
		}

		std::vector<std::shared_ptr<CFGNode>> nextNodes = curr->getAllNextNodes();
		for (std::shared_ptr<CFGNode> node : nextNodes) {
			visitQueue.push(node);
		}
	}
	
	return nullptr;
}