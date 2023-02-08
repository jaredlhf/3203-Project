#pragma once
#include <vector>
#include <string>

using namespace std;

class ParserResponse {
    private:
        vector<vector<string>> declarations;
        string synonym;
        // vector<string> suchThatClause;
        // vector<string> patternClause;
        
    public:
        void setDeclarations(vector<vector<string>> declarations);
        void setSynonym(string synonym);
        // void setSuchThatClause(vector<string> clause);
        // void setPatternClause(vector<string> clause);
        string getSynonym();
        vector<vector<string>> getDeclarations();
        // vector<string> getSuchThatClause();
        // vector<string> getPatternClause();
        static bool compare(ParserResponse a, ParserResponse b);



};