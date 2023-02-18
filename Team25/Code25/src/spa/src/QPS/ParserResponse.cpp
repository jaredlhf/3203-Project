#include "ParserResponse.h"



void ParserResponse::setDeclarations(std::vector<std::shared_ptr<Synonym>> declarations) {
    this->declarations = declarations;
    return;
}

void ParserResponse::setSynonym(std::shared_ptr<Synonym> synonym) {
    this->synonym = synonym;
    return;
}

void ParserResponse::setAssignSynonym(std::shared_ptr<Synonym> synonym) {
    this->assignSynonym = synonym;
    return;
}

void ParserResponse::setPatternClause(std::shared_ptr<Clause> patternClause) {
    this->patternClause = patternClause;
    return;
}

void ParserResponse::setSuchThatClause(std::shared_ptr<Clause> suchThatClause) {
    this->suchThatClause = suchThatClause;
    return;
}

std::vector<std::shared_ptr<Synonym>> ParserResponse::getDeclarations() {
    return this->declarations;
}

std::shared_ptr<Synonym> ParserResponse::getSynonym() {
    return this->synonym;
}

std::shared_ptr<Synonym> ParserResponse::getAssignSynonym() {
    return this->assignSynonym;
}

std::shared_ptr<Clause> ParserResponse::getPatternClause() {
    return this->patternClause;
}

std::shared_ptr<Clause> ParserResponse::getSuchThatClause() {
    return this->suchThatClause;
}

// add a compare for patternClause
bool ParserResponse::compare(ParserResponse other) {
    bool isSamePattern = true;
    bool isSameSuchThat = true;
    bool isSameAssignSyn = true;

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

    if (other.getSynonym() == nullptr || this->synonym == nullptr) {
        return false;
    }

    if (other.getAssignSynonym() != nullptr && this->assignSynonym != nullptr) {
        isSameAssignSyn = other.getAssignSynonym()->compare(this->assignSynonym) ;
    }

    if (other.getPatternClause() != nullptr && this->patternClause != nullptr) {
        isSamePattern = other.getPatternClause()->compare(this->patternClause);
    }

    if (other.getSuchThatClause() != nullptr && this->suchThatClause != nullptr) {
        isSameSuchThat = other.getSuchThatClause()->compare(this->suchThatClause);
    }
    
    return other.getSynonym()->compare(this->synonym) && isSameAssignSyn && isSamePattern && isSameSuchThat;
}