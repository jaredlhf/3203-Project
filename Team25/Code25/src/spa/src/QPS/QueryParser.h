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
        std::shared_ptr<Synonym> assignSynonym;
        std::shared_ptr<Entity> entRef;
        std::shared_ptr<Entity> pattern;
    public: 
        void setAssignSyn(std::shared_ptr<Synonym> a) {
            this->assignSynonym = a;
        }
        void setEntRef(std::shared_ptr<Entity> e) {
            this->entRef = e;
        }
        void setPattern(std::shared_ptr<Entity> p) {
            this->pattern = p;
        }
        std::shared_ptr<Synonym> getAssignSyn() {
            return this->assignSynonym;
        }
        std::shared_ptr<Entity> getEntRef() {
            return this->entRef;
        }
        std::shared_ptr<Entity> getPattern() {
            return this->pattern;
        }
        bool isIncomplete() {
            return this->assignSynonym == nullptr || this->entRef == nullptr || this->pattern == nullptr; 
        }
};

class ValidateSuchThatResponse {
    private:
        std::string keyword = "";
        std::shared_ptr<Entity> firstRef;
        std::shared_ptr<Entity> secondRef;
    public: 
        void setKeyword(std::string s) {
            this->keyword = s;
        }
        void setFirstRef(std::shared_ptr<Entity> e) {
            this->firstRef = e;
        }
        void setSecondRef(std::shared_ptr<Entity> e) {
            this->secondRef = e;
        }
        std::string getKeyword() {
            return this->keyword;
        }
        std::shared_ptr<Entity> getFirstRef() {
            return this->firstRef;
        }
        std::shared_ptr<Entity> getSecondRef() {
            return this->secondRef;
        }
        bool isIncomplete() {
            return this->keyword == "" || this->secondRef == nullptr || this->firstRef == nullptr; 
        }
};

class QueryParser {
    private:
        bool isValidDeclaration(std::vector<std::string> s,
            std::unordered_set<std::string>& declared_synonyms, 
            std::unordered_set<std::string>& assignment_synonyms);
        std::vector<std::shared_ptr<Synonym>> processDeclaration(std::vector<std::string> declaration, std::unordered_set<std::string> declared_synonyms);
        ValidatePatternResponse validatePatternClause(std::vector<std::string> s, std::unordered_set<std::string> assignment_synonyms, std::vector<std::shared_ptr<Synonym>> declarations);
        std::vector<std::string> validateSuchThatClause(std::vector<std::string> s);
        ParserResponse generateSyntaxErrorResponse();
        ParserResponse generateSemanticErrorResponse();

    public:
        ParserResponse parseQueryTokens(std::vector<std::string> tokens);
};