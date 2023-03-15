#include<memory>
#include "SPParserUtils.h"

SPParserUtils::SPParserUtils(std::shared_ptr<Tokenizer> t) {
    this->tokenizer = t;
    currentStmtNo = 0;
}

std::string SPParserUtils::expect(std::shared_ptr<Token> expectedToken) {
    std::string next = tokenizer->getNextToken();
    if (!expectedToken->isEqual(next)) {
        std::string error = "Error: unexpected token, got: " + next;

        throw std::invalid_argument(error);
    }
    return next;
}

int SPParserUtils::getCurrentStmtNo() {
    return currentStmtNo;
}

void SPParserUtils::incrementStmtNo() {
    currentStmtNo += 1;
}

