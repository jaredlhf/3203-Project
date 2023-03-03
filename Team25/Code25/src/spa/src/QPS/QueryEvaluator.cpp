#include "QueryEvaluator.h"


// Adds the data from the parser into the class attributes
void QueryEvaluator::handleParserResponse(ParserResponse& response) {
	this->declarations = response.getDeclarations();
	this->resultSynonyms = response.getSelectSynonyms();
	this->patternClauses = response.getPatternClauses();
	this->suchThatClauses = response.getSuchThatClauses();
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
	for (std::shared_ptr<Synonym> resSyn : this->resultSynonyms) {
		if (resSyn->matchesKeyword(Constants::SYNTAX_ERROR) || resSyn->matchesKeyword(Constants::SEMANTIC_ERROR)) {
			return std::list<std::string>({ resSyn->getKeyword() });
		}
	}
	

	std::vector<std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>> clauseResults;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> selectRes =
		resolveSelectSynonym(this->resultSynonyms[0], pkbRetriever); /*TODO CHANGE TO RESOLVE ALL SELECTS*/
	clauseResults.push_back(selectRes);

	for (std::shared_ptr<Clause> stClause : this->suchThatClauses) {
		clauseResults.push_back(stClause->resolve(pkbRetriever));
	}

	for (PatternClausePair ptClausePair : this->patternClauses) {
		std::shared_ptr<PatternClause> ptnClause = std::static_pointer_cast<PatternClause>(ptClausePair.second);
		clauseResults.push_back(ptnClause->resolve(pkbRetriever, ptClausePair.first));
	}

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
	/*TODO RESOLVE ANSWER FOR ALL SELECT SYNONYMS*/
	std::set<std::string> ansSet = finalResTable->getColResults(this->resultSynonyms[0]->getName());
	for (const std::string& answer : ansSet) {
		result.push_back(answer);
	}

	return result;
}