#pragma once

#include "PKB/PkbRetriever.h"
#include "ParserResponse.h"
#include "QueryEvaluator.h"
#include "QueryParser.h"
#include "QueryTokenizer.h"
#include <list>
#include <memory>
#include <string>
#include <vector>

class Qps {
private:
  std::shared_ptr<PkbRetriever> pkbRetriever;
  QueryTokenizer tokenizer;
  QueryParser parser;
  QueryEvaluator evaluator;

public:
  Qps(std::shared_ptr<PkbRetriever> pkbRetriever);
  void query(const std::string &queryStr, std::list<std::string> &uiList);
};