#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <stdio.h>
#include <map>
#include <iostream>
#include "ParserResponse.h"

class QueryParser {
    private:
        static bool isValidIntegerString(const std::string& s);
        static bool isValidNaming(const std::string& s);
        static bool isValidDeclaration(std::vector<std::string> s,
            std::unordered_set<std::string>& declared_synonyms, 
            std::unordered_set<std::string>& assignment_synonyms);
        // static bool isValidSuchThatClause(vector<string> s);
        // static bool isValidPatternClause(vector<string> s);
        // static bool isEntRef(string s);
        // static bool isStmtRef(string s);

    public:
        static ParserResponse parseQueryTokens(std::vector<std::string> tokens);
};