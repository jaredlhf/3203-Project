#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <stdio.h>
#include <map>
#include <iostream>
#include "ParserResponse.h"
#include "constants/Synonym.h"

class QueryParser {
    private:
        bool isValidIntegerString(const std::string& s);
        bool isValidNaming(const std::string& s);
        bool isValidDeclaration(std::vector<std::string> s,
            std::unordered_set<std::string>& declared_synonyms, 
            std::unordered_set<std::string>& assignment_synonyms);
        std::vector<std::shared_ptr<Synonym>> processDeclaration(std::vector<std::string> declaration);
        // static bool isValidSuchThatClause(vector<string> s);
        // static bool isValidPatternClause(vector<string> s);
        // static bool isEntRef(string s);
        // static bool isStmtRef(string s);

    public:
        ParserResponse parseQueryTokens(std::vector<std::string> tokens);
};