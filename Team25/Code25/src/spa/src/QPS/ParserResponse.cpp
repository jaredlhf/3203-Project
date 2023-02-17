#include "ParserResponse.h";


void ParserResponse::setDeclarations(std::vector<std::vector<std::string>> declarations) {
    ParserResponse::declarations = declarations;
    return;
}

std::vector<std::vector<std::string>> ParserResponse::getDeclarations() {
    return ParserResponse::declarations;
}

void ParserResponse::setSynonym(std::string synonym) {
    ParserResponse::synonym = synonym;
    return;
}

std::string ParserResponse::getSynonym() {
    return ParserResponse::synonym;
}

bool ParserResponse::compare(ParserResponse a, ParserResponse b) {
    return a.getSynonym() == b.getSynonym() && a.getDeclarations() == b.getDeclarations();
}