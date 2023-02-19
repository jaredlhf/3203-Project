#include "Qps.h"

Qps::Qps(std::shared_ptr<PkbRetriever> retriever) {
	pkbRetriever = retriever;
}

void Qps::query(const std::string& queryStr, std::list<std::string>& uiList) {
    std::cout<< "here1" <<std::endl;
	std::vector<std::string> tokens = tokenizer.tokenize(queryStr);
    std::cout<< "here2" <<std::endl;
	ParserResponse response = parser.parseQueryTokens(tokens);
    std::cout<< "here3" <<std::endl;
	std::list<std::string> result = evaluator.evaluate(response, pkbRetriever);
    std::cout<< "here4" <<std::endl;
	uiList.insert(uiList.end(), result.begin(), result.end());
    std::cout<< "here5" <<std::endl;
}