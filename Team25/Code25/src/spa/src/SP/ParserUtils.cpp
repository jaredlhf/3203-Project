#include "ParserUtils.h"

ParserUtils::ParserUtils(std::shared_ptr<Tokenizer> t) {
    this->tokenizer = t;
}

std::string ParserUtils::expect(std::shared_ptr<Token> expectedToken) {
    std::string next = tokenizer->getNextToken();
    if (!expectedToken->isEqual(next)) {
        std::cout << "error: unexpected token, got: " << next << std::endl;

        throw 1;
    }
    return next;
}