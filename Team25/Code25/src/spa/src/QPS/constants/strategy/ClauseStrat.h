#pragma once

#include "QPS/constants/Clause.h"

class UsesStrat;
class ModStrat;

class ClauseStrat {
protected:
	std::string clauseKeyword;
	std::shared_ptr<Entity> arg1;
	std::shared_ptr<Entity> arg2;
	std::shared_ptr<PkbRetriever> pkbRet;

public:
	// Constructor function for ClauseStrat
	ClauseStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
		std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet);

	// Factory function for ClauseStrat
	static std::shared_ptr<ClauseStrat> create(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
		std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet);

	// Overridable functions for ClauseStrat
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve();

	// Factory function for strategy used
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> createReturnStrategy() = 0;
};