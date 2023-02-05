#pragma once
#include <vector>
#include <string>
#include "ParserResponse.h"
#include <unordered_set>

using namespace std;

class QueryParser {
    private:
        static bool isValidIntegerString(string s);
        static bool isValidNaming(string s);
        static bool isValidDeclaration(vector<string> s,
         unordered_set<string>& declared_synonyms, unordered_set<string>& assignment_synonyms);
        // static bool isValidSuchThatClause(vector<string> s);
        // static bool isValidPatternClause(vector<string> s);
        // static bool isEntRef(string s);
        // static bool isStmtRef(string s);

    public:
        static ParserResponse parseQueryTokens(vector<string> tokens);
};