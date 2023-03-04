#include "QueryEvaluator.h"


// Adds the data from the parser into the class attributes
void QueryEvaluator::handleParserResponse(ParserResponse& response) {
	this->declarations = response.getDeclarations();
	this->resultSynonym = response.getSynonym();
	this->patternSynonym = response.getAssignSynonym();
	this->patternClause = response.getPatternClause();
	this->suchThatClause = response.getSuchThatClause();
}


// Public functions
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> QueryEvaluator::resolveSelectSynonym(
	std::shared_ptr<Synonym> resultSynonym, std::shared_ptr<PkbRetriever> pkbRet) {
	return resultSynonym->resolveSelectResult(pkbRet);
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> QueryEvaluator::resolveClauses(
	std::vector<std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>> clauseResults) {

	// If there is a syn_err, sem_err or no match in the header, short-circuit and return
	std::vector<Constants::ClauseResult> clauseResList;
	for (std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clauseRes : clauseResults) {
		clauseResList.push_back(clauseRes.first);
	}
	Constants::ClauseResult limitingRes = Constants::getLowerBound(clauseResList);
	if (limitingRes != Constants::ClauseResult::OK) {
		return std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>(limitingRes, 
			QpsTable::create());
	}

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res;
	res.first = limitingRes;
	res.second = QpsTable::create();

	for (std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clauseRes : clauseResults) {
		res.second = res.second->join(clauseRes.second);
	}

	return res;
}

std::list<std::string> QueryEvaluator::evaluate(ParserResponse response, std::shared_ptr<PkbRetriever> pkbRetriever) {
	std::list<std::string> result;
	handleParserResponse(response);

	// Edge case: If resultSynonym is a syntax or semantic error, return immediately
	if (this->resultSynonym->matchesKeyword(Constants::SYNTAX_ERROR) || this->resultSynonym->matchesKeyword(Constants::SEMANTIC_ERROR)) {
		return std::list<std::string>({ this->resultSynonym->getKeyword() });
	}

	std::vector<std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>> clauseResults;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> selectRes =
		resolveSelectSynonym(this->resultSynonym, pkbRetriever);
	clauseResults.push_back(selectRes);

	if (this->suchThatClause) {
		// TODO write implementation for suchThat clause retrieval
		clauseResults.push_back(this->suchThatClause->resolve(pkbRetriever));
	}

	if (this->patternClause) {
		// TODO write implementation for pattern clause retrieval
		std::shared_ptr<PatternClause> ptnClause = std::static_pointer_cast<PatternClause>(this->patternClause);
		clauseResults.push_back(ptnClause->resolve(pkbRetriever, this->patternSynonym));
	}

	// TODO update implementation for join all logic
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> finalRes =
		resolveClauses(clauseResults);

	// Handle non valid ans cases
	Constants::ClauseResult finalClauseStatus = finalRes.first;
	std::shared_ptr<QpsTable> finalResTable = finalRes.second;
	if (finalClauseStatus == Constants::ClauseResult::SYN_ERR) {
		return std::list<std::string>({ Constants::SYNTAX_ERROR });
	}

	if (finalClauseStatus == Constants::ClauseResult::SEM_ERR) {
		return std::list<std::string>({ Constants::SEMANTIC_ERROR });
	}

	if (finalClauseStatus == Constants::ClauseResult::NO_MATCH) {
		return std::list<std::string>({});
	}

	// Retrieve answer of resultSyn col in table
	std::set<std::string> ansSet = finalResTable->getColResults(resultSynonym->getName());
	for (const std::string& answer : ansSet) {
		result.push_back(answer);
	}

	return result;
}