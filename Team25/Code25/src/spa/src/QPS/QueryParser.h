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

class ValidatePatternResponse {
    private:
        std::shared_ptr<Synonym> synonym;
        std::shared_ptr<Entity> entRef;
        std::shared_ptr<Entity> pattern;
    public: 
        void setSynonym(std::shared_ptr<Synonym> s) {
            this->synonym = s;
        }
        void setEntRef(std::shared_ptr<Entity> e) {
            this->entRef = e;
        }
        void setPattern(std::shared_ptr<Entity> p) {
            this->pattern = p;
        }
        std::shared_ptr<Synonym> getSynonym() {
            return this->synonym;
        }
        std::shared_ptr<Entity> getEntRef() {
            return this->entRef;
        }
        std::shared_ptr<Entity> getPattern() {
            return this->pattern;
        }
        bool isIncomplete() {
            return this->synonym == nullptr || this->entRef == nullptr || this->pattern == nullptr; 
        }
};

class QueryParser {
    private:
        static bool isValidDeclaration(std::vector<std::string> s,
            std::unordered_set<std::string>& declared_synonyms, 
            std::unordered_set<std::string>& assignment_synonyms);
        static std::vector<std::shared_ptr<Synonym>> processDeclaration(std::vector<std::string> declaration, std::unordered_set<std::string> declared_synonyms);
        static ValidatePatternResponse validatePatternClause(std::vector<std::string> s, std::unordered_set<std::string> assignment_synonyms, std::vector<std::shared_ptr<Synonym>> declarations);
        static std::vector<std::string> validateSuchThatClause(std::vector<std::string> s);
        static ParserResponse generateSyntaxErrorResponse();
        static ParserResponse generateSemanticErrorResponse();
        static std::vector<std::shared_ptr<Synonym>> validateSelectSynonyms(std::vector<std::string> tokens, const std::vector<std::shared_ptr<Synonym>>& declarations);
    public:
        ParserResponse parseQueryTokens(std::vector<std::string> tokens);
};