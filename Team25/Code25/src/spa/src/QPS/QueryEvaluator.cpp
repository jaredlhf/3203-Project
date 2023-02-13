#include "QueryEvaluator.h"


// Adds the data from the parser into the class attributes
void QueryEvaluator::handleParserResponse(ParserResponse& response) {
	this->declarations = response.getDeclarations();
	this->resultSynonym = response.getSynonym();

}

// Fills the result synonym with the initial results
void QueryEvaluator::initializeResultSynonym(std::shared_ptr<PkbRetriever> pkbRetriever) {
	std::string resKeyword = this->resultSynonym->getKeyword();
	/*
		Handle the result synonym, for:
		- statement type synonym
		- variable type synonym
		- constant type synonym
	*/
	if (this->resultSynonym->isStmtRef()) {
		std::unordered_set<int> rawRes = pkbRetriever->getAllStmt(resKeyword);
		for (int i : rawRes) {
			this->resultSynonym->addMatchingResult(std::to_string(i));
		}
	}
	else if (this->resultSynonym->matchesKeyword(Constants::VARIABLE)) {
		for (const std::string& s : pkbRetriever->getAllVar()) {
			this->resultSynonym->addMatchingResult(s);
		}
	}
	else if (this->resultSynonym->matchesKeyword(Constants::CONSTANT)) {
		for (int i : pkbRetriever->getAllConst()) {
			this->resultSynonym->addMatchingResult(std::to_string(i));
		}
	}
}

Constants::ClauseResult QueryEvaluator::resolveClause(std::vector<std::shared_ptr<Clause>> clauses) {
	return Constants::ClauseResult::NO_MATCH;
}

std::list<std::string> QueryEvaluator::evaluate(ParserResponse response, std::shared_ptr<PkbRetriever> pkbRetriever) {
	std::list<std::string> result;
	handleParserResponse(response);

	// Edge case: If resultSynonym is a syntax or semantic error, return immediately
	if (this->resultSynonym->matchesKeyword(Constants::SYNTAX_ERROR) || this->resultSynonym->matchesKeyword(Constants::SEMANTIC_ERROR)) {
		return std::list<std::string>({ this->resultSynonym->getKeyword() });
	}

	initializeResultSynonym(pkbRetriever);

	for (const std::string& answer : resultSynonym->getMatches()) {
		result.push_back(answer);
	}

	return result;
}