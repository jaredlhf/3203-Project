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
        std::shared_ptr<Synonym> assignSynonym;
        std::shared_ptr<Clause> patternClause;
        std::shared_ptr<Clause> suchThatClause;
        
        
    public:
        void setDeclarations(std::vector<std::shared_ptr<Synonym>> declarations);
        void setSynonym(std::shared_ptr<Synonym> synonym);
        void setAssignSynonym(std::shared_ptr<Synonym> synonym);
        void setPatternClause(std::shared_ptr<Clause> patternClause);
        void setSuchThatClause(std::shared_ptr<Clause> suchThatClause);
        std::shared_ptr<Synonym> getSynonym();
        std::shared_ptr<Synonym> getAssignSynonym();
        std::vector<std::shared_ptr<Synonym>> getDeclarations();
        std::shared_ptr<Clause> getPatternClause();
        std::shared_ptr<Clause> getSuchThatClause();
        bool compare(ParserResponse other);



};