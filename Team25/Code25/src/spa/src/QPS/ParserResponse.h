#pragma once

#include <vector>
#include <string>
#include "constants/Synonym.h"


class ParserResponse {
    private:
        std::vector<std::shared_ptr<Synonym>> declarations;
        std::shared_ptr<Synonym> synonym;
        // std::vector<std::string> suchThatClause;
        // std::vector<std::string> patternClause;
        
    public:
        void setDeclarations(std::vector<std::shared_ptr<Synonym>> declarations);
        void setSynonym(std::shared_ptr<Synonym> synonym);
        // void setSuchThatClause(std::vector<std::string> clause);
        // void setPatternClause(std::vector<std::string> clause);
        std::shared_ptr<Synonym> getSynonym();
        std::vector<std::shared_ptr<Synonym>> getDeclarations();
        // std::vector<std::string> getSuchThatClause();
        // std::vector<std::string> getPatternClause();
        static bool compare(ParserResponse a, ParserResponse b);



};