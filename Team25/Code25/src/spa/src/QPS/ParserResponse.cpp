#include "ParserResponse.h"



void ParserResponse::setDeclarations(std::vector<std::shared_ptr<Synonym>> declarations) {
    ParserResponse::declarations = declarations;
    return;
}

void ParserResponse::setSynonym(std::shared_ptr<Synonym> synonym) {
    ParserResponse::synonym = synonym;
    return;
}

void ParserResponse::setPatternClause(std::shared_ptr<Clause> patternClause) {
    ParserResponse::patternClause = patternClause;
    return;
}

std::vector<std::shared_ptr<Synonym>> ParserResponse::getDeclarations() {
    return ParserResponse::declarations;
}

std::shared_ptr<Synonym> ParserResponse::getSynonym() {
    return ParserResponse::synonym;
}

std::shared_ptr<Clause> ParserResponse::getPatternClause() {
    return ParserResponse::patternClause;
}

// add a compare for patternClause
bool ParserResponse::compare(ParserResponse other) {
    std::vector<std::shared_ptr<Synonym>> otherDeclarations = other.getDeclarations();
    if (otherDeclarations.size() != this->declarations.size()) {
        return false;
    }

    for (int i = 0; i < otherDeclarations.size(); i++) {
        std::shared_ptr<Synonym> d = this->declarations[i];
        if (!otherDeclarations[i]->compare(d)) {
            return false;
        }
    }

    return other.getSynonym()->compare(this->synonym);
}