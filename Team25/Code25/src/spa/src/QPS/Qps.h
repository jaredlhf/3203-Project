#pragma once

#include <string>
#include <list>
#include <vector>
#include "QueryTokenizer.h"
#include "QueryParser.h"
#include "ParserResponse.h"
#include "QueryEvaluator.h"

class Qps {
private:
	QueryTokenizer tokenizer;
	QueryParser parser;
	QueryEvaluator evaluator;

public:
	void query(string queryStr, list<string> &uiList);
};