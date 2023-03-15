#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <stdio.h>
#include <iostream>
#include "ParserResponse.h"
#include "utils/ParserUtils.h"
#include "constants/Constants.h"
#include "constants/Relationship.h"
#include "constants/Synonym.h"
#include "constants/Clause.h"
#include "constants/Wildcard.h"
#include "constants/PatternValidator.h"

class QueryParser {
    private:
        static bool isValidDeclaration(std::vector<std::string> s);
        static ParserResponse generateSyntaxErrorResponse();
        static ParserResponse generateSemanticErrorResponse();
        static std::vector<std::shared_ptr<Synonym>> processDeclaration(std::vector<std::string> declaration, std::unordered_set<std::string> declared_synonyms);
        static std::vector<std::string> validateSuchThatClause(std::vector<std::string> s);
        static std::vector<std::shared_ptr<Synonym>> validateSelectSynonyms(std::vector<std::string> tokens, const std::vector<std::shared_ptr<Synonym>>& declarations);
    public:
        ParserResponse parseQueryTokens(std::vector<std::string> tokens);
};