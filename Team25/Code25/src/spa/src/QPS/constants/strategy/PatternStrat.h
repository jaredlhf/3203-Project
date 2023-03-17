#pragma once

#include "ClauseStrat.h"

class ClauseStrat;

class PatternStrat : public ClauseStrat {
private:
	// Extra attributes for PatternStrat
	std::shared_ptr<Synonym> pairedSyn;
	std::vector<std::string> synMatches;
	std::string synName;
	std::string synKeyword;

	// Strategy functions used for assign
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> wildcardWildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> wildcardSoftwildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> wildcardConst();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> constWildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> constSoftwildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> constConst();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> synWildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> synSoftwildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> synConst();
	// Strategy functions used for if
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ifWildcardWildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ifConstWildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ifSynWildcard();
	// Strategy functions used for while
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> whileWildcardWildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> whileConstWildcard();
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> whileSynWildcard();

public:
	// Constructor function for Strat
	PatternStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
		std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet, std::shared_ptr<Synonym> pairedSyn);

	// Overriden functions for ClauseStrat
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolve() override;

	// Factory function for strategy used
	virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> createReturnStrategy() override;
};