#pragma once

#include "QPS/constants/Clause.h"

class UsesStrat;
class ModStrat;
class ParentStrat;
class FollowsStrat;
class ParentStStrat;
class FollowsStStrat;
class PatternStrat;

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
	static std::shared_ptr<ClauseStrat> create(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
		std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet, std::shared_ptr<Synonym> pairedSyn);

	// Overridable functions for ClauseStrat
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve();

	// Factory function for strategy used
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> createReturnStrategy();
};