#pragma once
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "ParserResponse.h"
#include "constants/Constants.h"
#include "constants/Synonym.h"
#include "PKB/PkbRetriever.h"


class QueryEvaluator {
private:
	std::unordered_map<std::string, Synonym> declarations;
	Synonym resultSynonym;
	void handleParserResponse(ParserResponse& response);

public:
	std::list<std::string> evaluate(ParserResponse response, PkbRetriever* pkbRetriever);
};