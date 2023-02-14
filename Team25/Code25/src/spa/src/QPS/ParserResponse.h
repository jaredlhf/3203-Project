#pragma once

#include <vector>
#include <string>

class ParserResponse {
    private:
        std::vector<std::vector<std::string>> declarations;
        std::string synonym;
        // std::vector<std::string> suchThatClause;
        // std::vector<std::string> patternClause;
        
    public:
        void setDeclarations(std::vector<std::vector<std::string>> declarations);
        void setSynonym(std::string synonym);
        // void setSuchThatClause(std::vector<std::string> clause);
        // void setPatternClause(std::vector<std::string> clause);
        std::string getSynonym();
        std::vector<std::vector<std::string>> getDeclarations();
        // std::vector<std::string> getSuchThatClause();
        // std::vector<std::string> getPatternClause();
        static bool compare(ParserResponse a, ParserResponse b);



};