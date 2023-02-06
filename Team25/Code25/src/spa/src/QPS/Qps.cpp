#include "Qps.h"

Qps::Qps(PkbRetriever* retriever) {
	pkbRetriever = retriever;
}

void Qps::query(string queryStr, list<string> &uiList) {
	vector<string> tokens = tokenizer.tokenize(queryStr);
	ParserResponse response = parser.parseQueryTokens(tokens);
	list<string> result = evaluator.evaluate(response, pkbRetriever);

	uiList.insert(uiList.end(), result.begin(), result.end());
}