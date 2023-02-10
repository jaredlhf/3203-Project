#include "constants/Synonym.h"
#include "ParserResponse.h"

void ParserResponse::setDeclarations(std::vector<std::shared_ptr<Synonym>> declarations) {
    ParserResponse::declarations = declarations;
    return;
}

std::vector<std::shared_ptr<Synonym>> ParserResponse::getDeclarations() {
    return ParserResponse::declarations;
}

void ParserResponse::setSynonym(std::shared_ptr<Synonym> synonym) {
    ParserResponse::synonym = synonym;
    return;
}

std::shared_ptr<Synonym> ParserResponse::getSynonym() {
    return ParserResponse::synonym;
}

bool ParserResponse::compare(ParserResponse a, ParserResponse b) {
    return a.getSynonym() == b.getSynonym() && a.getDeclarations() == b.getDeclarations();
}