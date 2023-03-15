#pragma once

#include <string>
#include "Clause.h"
#include "Constants.h"
#include "../ParserResponse.h"
#include "../utils/ParserUtils.h"


class PatternValidator {
    protected:
        std::shared_ptr<Clause> patternClause;
        std::shared_ptr<Synonym> patternSynonym;
        std::vector<std::string> patternTokens;
        std::string patternKeyword;
    public:
        // constructor
        PatternValidator(std::shared_ptr<Synonym> synonym, const std::vector<std::string>& tokens);

        // static class function
        static std::shared_ptr<PatternValidator> create(std::shared_ptr<Synonym> synonym, const std::vector<std::string>& tokens);

        // function to override
        virtual PatternClausePair verifyPattern(const std::vector<std::shared_ptr<Synonym>>& declarations);
};

class AssignPatternValidator : public PatternValidator {
    public:
        AssignPatternValidator(std::shared_ptr<Synonym> synonym, const std::vector<std::string>& tokens);
        virtual PatternClausePair verifyPattern(const std::vector<std::shared_ptr<Synonym>>& declarations) override;
};

class IfPatternValidator : public PatternValidator {
    public:
        IfPatternValidator(std::shared_ptr<Synonym> synonym, const std::vector<std::string>& tokens);
        virtual PatternClausePair verifyPattern(const std::vector<std::shared_ptr<Synonym>>& declarations) override;
};

class WhilePatternValidator : public PatternValidator {
    public:
        WhilePatternValidator(std::shared_ptr<Synonym> synonym, const std::vector<std::string>& tokens);
        virtual PatternClausePair verifyPattern(const std::vector<std::shared_ptr<Synonym>>& declarations) override;
};