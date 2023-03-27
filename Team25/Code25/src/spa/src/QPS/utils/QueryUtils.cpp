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

bool QueryUtils::affects(int modLine, int usedLine, std::shared_ptr<PkbRetriever> pkbRet) {
	return false;
}