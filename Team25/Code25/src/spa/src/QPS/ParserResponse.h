#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "constants/Synonym.h"
#include "constants/Clause.h"

class ParserResponse {
    private:
        std::vector<std::shared_ptr<Synonym>> declarations;
        std::shared_ptr<Synonym> synonym;
        std::shared_ptr<Clause> patternClause;
        // std::vector<std::string> suchThatClause;
        // std::vector<std::string> patternClause;
        
    public:
        void setDeclarations(std::vector<std::shared_ptr<Synonym>> declarations);
        void setSynonym(std::shared_ptr<Synonym> synonym);
        void setPatternClause(std::shared_ptr<Clause> patternClause);
        // void setSuchThatClause(std::vector<std::string> clause);
        // void setPatternClause(std::vector<std::string> clause);
        std::shared_ptr<Synonym> getSynonym();
        std::vector<std::shared_ptr<Synonym>> getDeclarations();
        std::shared_ptr<Clause> getPatternClause();
        // std::vector<std::string> getSuchThatClause();
        // std::vector<std::string> getPatternClause();
        bool compare(ParserResponse other);



};