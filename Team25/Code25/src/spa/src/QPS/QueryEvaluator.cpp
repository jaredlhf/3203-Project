#include "QueryEvaluator.h"


// Adds the data from the parser into the class attributes
void QueryEvaluator::handleParserResponse(ParserResponse& response) {
	this->declarations = response.getDeclarations();
	this->resultSynonym = response.getSynonym();

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