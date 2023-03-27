#pragma once

#include "PKB/PkbRetriever.h"
#include "QPS/constants/Constants.h"


class QueryUtils {
public:
	template<typename T>
	static bool isEmpty(std::unordered_set<T> set);

	template<typename T>
	static bool isNotEmpty(std::unordered_set<T> set);

	template<typename T>
	static bool contains(std::unordered_set<T> set, T item);

	static bool isAssignStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet);

	static bool affects(int modLine, int usedLine, std::shared_ptr<PkbRetriever> pkbRet);
};