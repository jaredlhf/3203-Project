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

bool QueryUtils::affects(int modLine, int usesLine, std::shared_ptr<PkbRetriever> pkbRet) {
	// return false if neither is an assign stmt
	if (!isAssignStmt(modLine, pkbRet) || !isAssignStmt(usesLine, pkbRet)) {
		return false;
	}

	std::unordered_set<std::string> modSet = pkbRet->getModVar(modLine);
	std::string modVar;
	// Guaranteed to be 1 item in set since it is an assign stmt
	for (std::string var : modSet) {
		modVar = var;
	}

	std::unordered_set<std::string> usesSet = pkbRet->getUsesVar(modLine);
	// Return false if modVar is not in usedSet
	if (std::find(usesSet.begin(), usesSet.end(), modVar) == usesSet.end()) {
		return false;
	}

	std::shared_ptr<CFGNode> rootNode = getNodeOfLine(modLine, pkbRet->getCFGNode("TO BE CHANGED"));
	// Check if base cfg node has new modifies (base cfg node will not be a if or while node)
	std::vector<int> rootLines = rootNode->getLineNo();
	std::unordered_set<std::string> otherModInNode;
	for (int nextLine : rootLines) {
		if (nextLine > modLine && nextLine < usesLine) {
			// handle call stmts vs normal stmts
			std::unordered_set<std::string> lineMods = pkbRet->getModVar(nextLine);
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
	return recursivelyCheckModifies(modVar, rootNode, visitedSet, pkbRet);
}

bool QueryUtils::recursivelyCheckModifies(std::string modVar, std::shared_ptr<CFGNode> rootNode,
	NodeVisitSet visitedSet, std::shared_ptr<PkbRetriever> pkbRet) {
	return false;
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