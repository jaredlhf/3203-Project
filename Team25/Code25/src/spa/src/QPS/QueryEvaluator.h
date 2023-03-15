#pragma once

#include "PKB/PkbRetriever.h"
#include "ParserResponse.h"
#include "QpsTable.h"
#include "ResultFormatter.h"
#include "constants/Clause.h"
#include "constants/Constants.h"
#include "constants/Synonym.h"
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class QueryEvaluator {
private:
  std::vector<std::shared_ptr<Synonym>> declarations;
  std::vector<std::shared_ptr<Synonym>> resultSynonyms;
  std::vector<PatternClausePair> patternClauses;
  std::vector<std::shared_ptr<Clause>> suchThatClauses;
  void handleParserResponse(ParserResponse &response);
  std::vector<std::string> getResultNames();

public:
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>
  resolveSelectSynonyms(std::vector<std::shared_ptr<Synonym>> resultSynonyms,
                        std::shared_ptr<PkbRetriever> pkbRetriever);
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveClauses(
      std::vector<std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>>
          clauseResults);
  std::list<std::string> evaluate(ParserResponse response,
                                  std::shared_ptr<PkbRetriever> pkbRetriever);
};