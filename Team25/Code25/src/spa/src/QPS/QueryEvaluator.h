#pragma once
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include "ParserResponse.h"
#include "constants/Constants.h"
#include "constants/Synonym.h"

using namespace std;

class QueryEvaluator {
private:
	unordered_map<string, Synonym> declarations;
	Synonym resultSynonym;
	void handleParserResponse(ParserResponse &response);

public:
	list<string> evaluate(ParserResponse response);
};