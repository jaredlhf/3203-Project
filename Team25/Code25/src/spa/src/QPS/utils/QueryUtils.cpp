#include "QueryUtils.h"

std::map<std::pair<int, int>, bool> QueryUtils::cache = {};

template<typename T>
bool QueryUtils::isEmpty(std::unordered_set<T> set) {
	return set.size() <= 0;
}

template<typename T>
bool QueryUtils::isNotEmpty(std::unordered_set<T> set) {
	return !isEmpty(set);
}

template<typename T>
bool QueryUtils::isEmpty(std::set<T> set) {
	return set.size() <= 0;
}

template<typename T>
bool QueryUtils::isNotEmpty(std::set<T> set) {
	return !isEmpty(set);
}

template<typename T>
bool QueryUtils::isEmpty(std::vector<T> set) {
	return set.size() <= 0;
}

template<typename T>
bool QueryUtils::isNotEmpty(std::vector<T> set) {
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

std::unordered_set<std::string> QueryUtils::getAllVarModByProc(const std::string& proc, std::shared_ptr<PkbRetriever> pkbRet) {
	std::unordered_set<std::string> res;
	std::unordered_set<std::string> allProcs = pkbRet->getRightCallStar(proc);
	// Add proc to the full list of procs that we need to check
	allProcs.insert(proc);

	for (const std::string& currProc : allProcs) {
		std::unordered_set<std::string> currProcVars = pkbRet->getModPVar(currProc);
		for (const std::string& var : currProcVars) {
			res.insert(var);
		}
	}

	return res;
}

std::unordered_set<std::string> QueryUtils::getModifiesInNonContainStmt(int lineNum, 
	std::shared_ptr<PkbRetriever> pkbRet) {
	// handle call stmts vs normal stmts
	std::unordered_set<int> callStmts = pkbRet->getAllStmt(Constants::CALL);
	std::unordered_set<std::string> lineMods =
		std::find(callStmts.begin(), callStmts.end(), lineNum) == callStmts.end()
		? pkbRet->getModVar(lineNum)
		: getAllVarModByProc(pkbRet->getCallAttr(lineNum), pkbRet);

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
	// Special case: if mod and uses are in the same proc and mod comes before uses, return true
	// if it isnt modified again else false
	}
	else if (modLine < usesLine && std::find(rootLines.begin(), rootLines.end(), usesLine) != rootLines.end()) {
		return std::find(otherModInNode.begin(), otherModInNode.end(), modVar) == otherModInNode.end();
	}

	// Use dfs to determine if its modified again in path
	std::unordered_set<std::shared_ptr<CFGNode>> baseSet;
	NodeVisitSet visitedSet = std::make_shared<std::unordered_set<std::shared_ptr<CFGNode>>>(baseSet);
	std::vector<std::shared_ptr<CFGNode>> nextNodes;
	for (std::shared_ptr<CFGNode> node : rootNode->getAllNextNodes()) {
		if (node && QueryUtils::isNotEmpty(node->getLineNo())) {
			nextNodes.push_back(node);
		}
	}
	if (nextNodes.size() <= 0) {
		return false;
	}
	std::shared_ptr<CFGNode> nextNode = nextNodes[0];
	return !recursivelyModifies(modVar, nextNode, visitedSet, pkbRet, usesLine, modLine, false);
}

bool QueryUtils::affectsStar(int modLine, int usesLine, std::shared_ptr<PkbRetriever> pkbRet) {
	// Edge case: return false if neither is an assign stmt
	if (!isAssignStmt(modLine, pkbRet) || !isAssignStmt(usesLine, pkbRet)) {
		return false;
	}

	// Edge case: return false if modLine and usesLine are not in the same procedure
	if (pkbRet->getProc(modLine) != pkbRet->getProc(usesLine)) {
		return false;
	}

	if (cache.find({ modLine, usesLine }) == cache.end()) {
		cache.insert({ { modLine, usesLine }, affects(modLine, usesLine, pkbRet) });
	}

	// trivial case: if s1 affects s2 directly, return true
	if (cache.at({ modLine, usesLine })) {
		return true;
	}

	std::string proc = pkbRet->getProc(modLine);
	std::unordered_set<int> procStmts = pkbRet->getStmt(proc);
	for (int middleStmt : procStmts) {
		if (cache.find({ modLine, middleStmt }) == cache.end()) {
			cache.insert({ { modLine, middleStmt }, affects(modLine, middleStmt, pkbRet) });
		}

		if (cache.find({ middleStmt, usesLine }) == cache.end()) {
			cache.insert({ { middleStmt, usesLine }, affects(middleStmt, usesLine, pkbRet) });
		}
		if (cache.at({ modLine, middleStmt }) && cache.at({ middleStmt, usesLine })) {
			return true;
		}
	}

	return false;
}

bool QueryUtils::recursivelyModifies(std::string modVar, std::shared_ptr<CFGNode> rootNode,
	NodeVisitSet visitedSet, std::shared_ptr<PkbRetriever> pkbRet, int usesLine, int modLine, bool seenUses) {
	// If ptr is null, just skip
	if (!rootNode) {
		return false;
	}

	std::vector<int> nodeLines = rootNode->getLineNo();

	// Skip checking for node if it is a if or while cfg node
	bool skipCurrNode = nodeLines.size() == 1 && isContainerStmt(nodeLines[0], pkbRet);
	bool isUsesNode = std::find(nodeLines.begin(), nodeLines.end(), usesLine) != nodeLines.end();
	seenUses = isUsesNode;
	bool hasModifies = skipCurrNode || !seenUses;
	bool isModInSameNode = isUsesNode && std::find(nodeLines.begin(), nodeLines.end(), modLine) != nodeLines.end();
	
	// Special case: if modifies line is in same node as uses line, check if there is any other modifies before uses line
	if (isModInSameNode) {
		std::unordered_set<std::string> modVars;
		for (int line : nodeLines) {
			if (line >= usesLine && line <= modLine) {
				continue;
			}
			std::unordered_set<std::string> lineMods = getModifiesInNonContainStmt(line, pkbRet);
			modVars.insert(lineMods.begin(), lineMods.end());
		}

		return std::find(modVars.begin(), modVars.end(), modVar) != modVars.end();
	}

	if (!skipCurrNode) {
		visitedSet->insert(rootNode);
		std::unordered_set<std::string> modVars;

		// check for mods in curr node
		for (int line : nodeLines) {
			if (isUsesNode && line >= usesLine) {
				continue;
			}
			std::unordered_set<std::string> lineMods = getModifiesInNonContainStmt(line, pkbRet);
			modVars.insert(lineMods.begin(), lineMods.end());
		}

		// if modVar is changed again in curr node, return false directly
		if (std::find(modVars.begin(), modVars.end(), modVar) != modVars.end()) {
			visitedSet->erase(rootNode);
			return true;
		}
	}

	if (isUsesNode) {
		visitedSet->erase(rootNode);
		return hasModifies;
	}

	// Add next nodes to visit
	std::vector<std::shared_ptr<CFGNode>> nextNodes = rootNode->getAllNextNodes();
	for (std::shared_ptr<CFGNode> nextNode : nextNodes) {
		if (!nextNode || isEmpty(nextNode->getLineNo())) {
			continue;
		}
		if (std::find(visitedSet->begin(), visitedSet->end(), nextNode) == visitedSet->end()) {
			bool pathHasModifies = recursivelyModifies(modVar, nextNode, visitedSet, pkbRet, usesLine, modLine, seenUses);
			hasModifies = hasModifies && pathHasModifies;
				
		}
	}

	visitedSet->erase(rootNode);
	return hasModifies;
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

void QueryUtils::clearCache() {
	cache.clear();
}