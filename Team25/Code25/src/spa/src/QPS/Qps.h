#pragma once

#include <string>
#include <list>
#include <vector>
#include <memory>
#include "QueryTokenizer.h"
#include "QueryParser.h"
#include "ParserResponse.h"
#include "QueryEvaluator.h"
#include "PKB/PkbRetriever.h"

class Qps {
private:
	std::shared_ptr<PkbRetriever> pkbRetriever;
	QueryTokenizer tokenizer;
	QueryParser parser;
	QueryEvaluator evaluator;

public:
	Qps(std::shared_ptr<PkbRetriever> pkbRetriever);
	void query(const std::string& queryStr, std::list<std::string>& uiList);
};