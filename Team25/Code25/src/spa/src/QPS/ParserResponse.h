#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "constants/Synonym.h"
#include "constants/Clause.h"

typedef std::pair<std::shared_ptr<Synonym>, std::shared_ptr<Clause>> PatternClausePair;

class ParserResponse {
    private:
        std::vector<std::shared_ptr<Synonym>> declarations;
        std::vector<std::shared_ptr<Synonym>> selectSynonyms;
        std::vector<std::shared_ptr<Clause>> suchThatClauses;
        std::vector<std::shared_ptr<Clause>> withClauses;
        std::vector<PatternClausePair> patternClauses;

        
    public:
        void setDeclarations(std::vector<std::shared_ptr<Synonym>> declarations);
        void setSelectSynonyms(std::vector<std::shared_ptr<Synonym>> synonyms);
        void setPatternClauses(std::vector<PatternClausePair >  patternClauses);
        void setSuchThatClauses(std::vector<std::shared_ptr<Clause>> suchThatClauses);
        void setWithClauses(std::vector<std::shared_ptr<Clause>> withClauses);
        std::vector<std::shared_ptr<Synonym>> getSelectSynonyms();
        std::vector<std::shared_ptr<Synonym>> getDeclarations();
        std::vector<std::shared_ptr<Clause>> getSuchThatClauses();
        std::vector<std::shared_ptr<Clause>> getWithClauses();
        std::vector<PatternClausePair> getPatternClauses();
        bool compare(ParserResponse other);
};