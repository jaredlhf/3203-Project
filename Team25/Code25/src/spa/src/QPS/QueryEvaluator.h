#pragma once

#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "ParserResponse.h"
#include "constants/Constants.h"
#include "constants/Synonym.h"
#include "PKB/PkbRetriever.h"


class QueryEvaluator {
private:
	std::unordered_map<std::string, std::shared_ptr<Synonym>> declarations;
	std::shared_ptr<Synonym> resultSynonym;
	void handleParserResponse(ParserResponse& response);

public:
	std::list<std::string> evaluate(ParserResponse response, PkbRetriever* pkbRetriever);
};