#pragma once

#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "ParserResponse.h"
#include "constants/Clause.h"
#include "constants/Constants.h"
#include "constants/Synonym.h"
#include "PKB/PkbRetriever.h"


class QueryEvaluator {
private:
	std::vector<std::shared_ptr<Synonym>> declarations;
	std::shared_ptr<Synonym> resultSynonym;
	std::shared_ptr<Synonym> patternSynonym;
	std::shared_ptr<Clause> patternClause;
	std::shared_ptr<Clause> suchThatClause;
	void handleParserResponse(ParserResponse& response);
	void initializeResultSynonym(std::shared_ptr<PkbRetriever> pkbRetriever);
	Constants::ClauseResult resolveClause(std::vector<std::shared_ptr<Clause>> clauses);

public:
	std::list<std::string> evaluate(ParserResponse response, std::shared_ptr<PkbRetriever> pkbRetriever);
};