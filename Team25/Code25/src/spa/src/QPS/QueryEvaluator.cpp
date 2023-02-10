#include "QueryEvaluator.h"


// Adds the data from the parser into the class attributes
void QueryEvaluator::handleParserResponse(ParserResponse& response) {
	std::vector<std::vector<std::string>> rawDeclarations = response.getDeclarations();
	for (std::vector<std::string>& row : rawDeclarations) {
		std::string decType = row[0];
		for (int i = 1; i < row.size(); i++) {
			if (row[i] == ",") {
				continue;
			}
			std::string varName = row[i];
			declarations.insert({varName, Synonym::create(decType, varName)});
		}
	}

	std::string resultName = response.getSynonym();
	resultSynonym = declarations[resultName];
}

Constants::ClauseResult QueryEvaluator::resolveClause(std::vector<std::shared_ptr<Clause>> clauses) {
	return Constants::ClauseResult::NO_MATCH;
}

std::list<std::string> QueryEvaluator::evaluate(ParserResponse response, PkbRetriever* pkbRetriever) {
	std::list<std::string> result;
	handleParserResponse(response);

	std::unordered_set<std::string> resSet = (*pkbRetriever).getAllVar();
	for (const std::string& variable : resSet) {
		resultSynonym->addMatchingResult(variable);
	}

	for (const std::string& answer : resultSynonym->getMatches()) {
		result.push_back(answer);
	}

	return result;
}