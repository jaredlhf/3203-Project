#pragma once

#include <string>
#include <list>
#include <vector>
#include "QueryTokenizer.h"
#include "QueryParser.h"
#include "ParserResponse.h"
#include "QueryEvaluator.h"
#include "PKB/PkbRetriever.h"

class Qps {
private:
	PkbRetriever* pkbRetriever;
	QueryTokenizer tokenizer;
	QueryParser parser;
	QueryEvaluator evaluator;

public:
	Qps(PkbRetriever* pkbRetriever);
	void query(string queryStr, list<string> &uiList);
};