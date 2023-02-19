#include "Qps.h"

Qps::Qps(std::shared_ptr<PkbRetriever> retriever) {
	pkbRetriever = retriever;
}

void Qps::query(const std::string& queryStr, std::list<std::string>& uiList) {
	std::vector<std::string> tokens = tokenizer.tokenize(queryStr);
	ParserResponse response = parser.parseQueryTokens(tokens);
	std::list<std::string> result = evaluator.evaluate(response, pkbRetriever);
	uiList.insert(uiList.end(), result.begin(), result.end());
}