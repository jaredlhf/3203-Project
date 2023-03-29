#pragma once

#include <queue>
#include "PKB/PkbRetriever.h"
#include "QPS/constants/Constants.h"
#include "QPS/constants/strategy/ModStrat.h"


class QueryUtils {
public:
	typedef std::shared_ptr<std::unordered_set<std::shared_ptr<CFGNode>>> NodeVisitSet;

	template<typename T>
	static bool isEmpty(std::unordered_set<T> set);

	template<typename T>
	static bool isNotEmpty(std::unordered_set<T> set);

	template<typename T>
	static bool contains(std::unordered_set<T> set, T item);

	static bool isAssignStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet);

	static bool isContainerStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet);

	static std::unordered_set<std::string> getModifiesInNonContainStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet);

	static bool affects(int modLine, int usedLine, std::shared_ptr<PkbRetriever> pkbRet);

	static bool recursivelyNoModifies(std::string modVar, std::shared_ptr<CFGNode> rootNode,
		NodeVisitSet visitedSet, std::shared_ptr<PkbRetriever> pkbRet, int lineNum);

	static std::shared_ptr<CFGNode> getNodeOfLine(int lineNum, std::shared_ptr<CFGNode> rootNode);
};