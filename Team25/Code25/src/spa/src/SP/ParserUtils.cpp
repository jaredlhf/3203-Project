#include "ParserUtils.h"

ParserUtils::ParserUtils(std::shared_ptr<Tokenizer> t) {
    this->tokenizer = t;
    currentStmtNo = 0;
}

std::string ParserUtils::expect(std::shared_ptr<Token> expectedToken) {
    std::string next = tokenizer->getNextToken();
    if (!expectedToken->isEqual(next)) {
        std::string error = "error: unexpected token, got: " + next;

        throw std::invalid_argument(error);
    }
    return next;
}

int ParserUtils::getCurrentStmtNo() {
    return currentStmtNo;
}

void ParserUtils::incrementStmtNo() {
    currentStmtNo += 1;
}

