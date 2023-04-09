#include<memory>
#include "SPParserUtils.h"

SPParserUtils::SPParserUtils(std::shared_ptr<Tokenizer> t) {
    this->tokenizer = t;
    currentStmtNo = 0;
}

std::string SPParserUtils::expect(const std::string expectedToken) {
    std::string next = tokenizer->getNextToken();
    if ((expectedToken == SPConstants::NAME_TOKEN && Token::isValidName(next)) || (expectedToken == next)) {
        return next;
    }
    std::string error = "Error: unexpected token, got: " + next;
    throw std::invalid_argument(error);


}

int SPParserUtils::getCurrentStmtNo() {
    return currentStmtNo;
}

void SPParserUtils::incrementStmtNo() {
    currentStmtNo += 1;
}

