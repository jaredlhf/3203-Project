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
	// return false if neither is an assign stmt
	if (!isAssignStmt(modLine, pkbRet) || !isAssignStmt(usedLine, pkbRet)) {
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


	return false;
}