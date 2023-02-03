#pragma once
#include <vector>
#include <string>

using namespace std;

class QueryParser {
    private:
        static bool isValidIntegerString(string s);
        static bool isValidNaming(string s);
        static bool isValidDeclaration(vector<string> s);
        static bool isValidSuchThatClause(vector<string> s);
        static bool isValidPatternClause(vector<string> s);
        static bool isEntRef(string s);
        static bool isStmtRef(string s);
        
    public:
        static vector<vector<string>> parseQueryTokens(vector<string> tokens);
};