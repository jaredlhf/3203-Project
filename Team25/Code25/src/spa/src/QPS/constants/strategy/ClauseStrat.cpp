#include "ClauseStrat.h"
#include "UsesStrat.h"
#include "ModStrat.h"

// Constructor function for ClauseStrat

ClauseStrat::ClauseStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
	std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet) {
	this->clauseKeyword = clauseKeyword;
	this->arg1 = arg1;
	this->arg2 = arg2;
	this->pkbRet = pkbRet;
}

// Factory function for ClauseStrat
std::shared_ptr<ClauseStrat> ClauseStrat::create(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
	std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet) {
	if (clauseKeyword == Constants::USES) {
		return std::make_shared<UsesStrat>(UsesStrat(clauseKeyword, arg1, arg2, pkbRet));
	}

	if (clauseKeyword == Constants::MODIFIES) {
		return std::make_shared<ModStrat>(ModStrat(clauseKeyword, arg1, arg2, pkbRet));
	}
}

// Overridable functions for ClauseStrat
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ClauseStrat::resolve() {
	return QpsTable::getDefaultSynErr();
}