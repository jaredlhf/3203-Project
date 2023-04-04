#pragma once

#include <queue>
#include <map>
#include <set>
#include "PKB/PkbRetriever.h"
#include "QPS/constants/Constants.h"


class QueryUtils {
private:
	static std::map<std::pair<int, int>, bool> cache;
public:
	typedef std::shared_ptr<std::unordered_set<std::shared_ptr<CFGNode>>> NodeVisitSet;

	template<typename T>
	static bool isEmpty(std::unordered_set<T> set);

	template<typename T>
	static bool isNotEmpty(std::unordered_set<T> set);

	template<typename T>
	static bool isEmpty(std::set<T> set);

	template<typename T>
	static bool isNotEmpty(std::set<T> set);

	template<typename T>
	static bool isEmpty(std::vector<T> set);

	template<typename T>
	static bool isNotEmpty(std::vector<T> set);

	template<typename T>
	static bool contains(std::unordered_set<T> set, T item);

	static bool isAssignStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet);

	static bool isContainerStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet);

	static std::unordered_set<std::string> getAllVarModByProc(const std::string& proc, std::shared_ptr<PkbRetriever> pkbRet);

	static std::unordered_set<std::string> getModifiesInNonContainStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet);

	static bool affects(int modLine, int usedLine, std::shared_ptr<PkbRetriever> pkbRet);

	static bool affectsStar(int modLine, int usedLine, std::shared_ptr<PkbRetriever> pkbRet);

	static bool recursivelyModifies(std::string modVar, std::shared_ptr<CFGNode> rootNode,
		NodeVisitSet visitedSet, std::shared_ptr<PkbRetriever> pkbRet, int usesLine, int modLine, bool seenUses);

	static std::shared_ptr<CFGNode> getNodeOfLine(int lineNum, std::shared_ptr<CFGNode> rootNode);

	static void clearCache();
};