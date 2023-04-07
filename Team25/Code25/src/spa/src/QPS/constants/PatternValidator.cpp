#include "PatternValidator.h"

PatternValidator::PatternValidator(std::shared_ptr<Synonym> synonym, const std::vector<std::string>& tokens) {
    patternTokens = tokens;
    patternSynonym = synonym;
}

std::shared_ptr<PatternValidator> PatternValidator::create(std::shared_ptr<Synonym> synonym, const std::vector<std::string>& tokens) {
    if (ParserUtils::isExpectedSynonym(synonym, Constants::ASSIGN)) return std::make_shared<AssignPatternValidator>(AssignPatternValidator(synonym, tokens));
    if (ParserUtils::isExpectedSynonym(synonym, Constants::IF)) return std::make_shared<IfPatternValidator>(IfPatternValidator(synonym, tokens));
    if (ParserUtils::isExpectedSynonym(synonym, Constants::WHILE)) return std::make_shared<WhilePatternValidator>(WhilePatternValidator(synonym, tokens));
    return std::make_shared<PatternValidator>(PatternValidator(synonym, tokens));
}

PatternClausePair PatternValidator::verifyPattern(const std::vector<std::shared_ptr<Synonym>>& declarations) {
    return make_pair(Synonym::create(Constants::SEMANTIC_ERROR, ""), patternClause);
}

AssignPatternValidator::AssignPatternValidator(std::shared_ptr<Synonym> synonym, const std::vector<std::string>& tokens) : PatternValidator(synonym, tokens) {
    patternTokens = tokens;
    patternSynonym = synonym;
}

PatternClausePair AssignPatternValidator::verifyPattern(const std::vector<std::shared_ptr<Synonym>>& declarations) {
    int ptr = 0;
    int ASSIGN_LENGTH = 5;
    bool hasSemanticError = false;

    std::string expression;
    std::shared_ptr<Entity> entRef;

    if (patternTokens.size() != ASSIGN_LENGTH) {
        return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
    }
    while (ptr < patternTokens.size()) {

        // check if pattern is enclosed by brackets
        if (ptr == 0) {
            if (patternTokens[ptr] != Constants::OPEN_BRACKET || patternTokens[patternTokens.size() - 1] != Constants::CLOSE_BRACKET) {
                return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
            }
        }

        // check if entRef is valid
        if (ptr == 1) {
            entRef = ParserUtils::getValidEntRef(patternTokens[ptr], declarations);
            if (ParserUtils::isSyntaxError(entRef)) {
                return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
            }
            if (ParserUtils::isSemanticError(entRef)) {
                hasSemanticError = true;
            }
        }

        if (ptr == 2 && patternTokens[ptr] != Constants::SEPARATOR) {
            return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
        }

        if (ptr == 3) {
            expression = patternTokens[ptr];
            break;
        }
        ptr++;
    }

    if (!ParserUtils::isValidExpression(expression)) {
        return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
    }
    if (hasSemanticError) {
        return make_pair(Synonym::create(Constants::SEMANTIC_ERROR, ""), nullptr);
    }

    std::string cleanedString;
    if (expression == Constants::WILDCARD) {
        patternClause = Clause::create(Constants::PATTERN, entRef, Wildcard::create());
    } else if (expression[0] == '_') {
        cleanedString = expression.substr(2, expression.size() - 4);
        patternClause = Clause::create(Constants::PATTERN, entRef, Wildcard::create(cleanedString));
    } else {
        cleanedString = expression.substr(1, expression.size() - 2);
        patternClause = Clause::create(Constants::PATTERN, entRef, Value::create(cleanedString));
    }

    return make_pair(patternSynonym, patternClause);
}

IfPatternValidator::IfPatternValidator(std::shared_ptr<Synonym> synonym, const std::vector<std::string> &tokens) : PatternValidator(synonym, tokens) {
    patternTokens = tokens;
    patternSynonym = synonym;
}

PatternClausePair IfPatternValidator::verifyPattern(const std::vector<std::shared_ptr<Synonym>> &declarations) {
    int ptr = 0;
    int IF_LENGTH = 7;
    bool hasSemanticError = false;

    std::string expression;
    std::shared_ptr<Entity> entRef;

    if (patternTokens.size() != IF_LENGTH) {
        return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
    }
    while (ptr < patternTokens.size()) {

        // check if pattern is enclosed by brackets
        if (ptr == 0) {
            if (patternTokens[ptr] != Constants::OPEN_BRACKET || patternTokens[patternTokens.size() - 1] != Constants::CLOSE_BRACKET) {
                return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
            }
        }

        // check if entRef is valid
        if (ptr == 1) {
            entRef = ParserUtils::getValidEntRef(patternTokens[ptr], declarations);
            if (ParserUtils::isSyntaxError(entRef)) {
                return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
            }
            if (ParserUtils::isSemanticError(entRef)) {
                hasSemanticError = true;
            }
        }

        if (ptr == 2 && patternTokens[ptr] != Constants::SEPARATOR) {
            return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
        }

        if (ptr == 3 && patternTokens[ptr] != Constants::WILDCARD) {
            hasSemanticError = true;
        }

        if (ptr == 4 && patternTokens[ptr] != Constants::SEPARATOR) {
            return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
        }

        if (ptr == 5 && patternTokens[ptr] != Constants::WILDCARD) {
            hasSemanticError = true;
        }

        ptr++;
    }
    if (hasSemanticError) {
        return make_pair(Synonym::create(Constants::SEMANTIC_ERROR, ""), nullptr);
    }
    return make_pair(patternSynonym, Clause::create(Constants::PATTERN, entRef, Wildcard::create()));
}

WhilePatternValidator::WhilePatternValidator(std::shared_ptr<Synonym> synonym, const std::vector<std::string> &tokens) : PatternValidator(synonym, tokens) {
    patternTokens = tokens;
    patternSynonym = synonym;
}

PatternClausePair WhilePatternValidator::verifyPattern(const std::vector<std::shared_ptr<Synonym>> &declarations) {
    int ptr = 0;
    int WHILE_LENGTH = 5;
    bool hasSemanticError = false;

    std::string expression;
    std::shared_ptr<Entity> entRef;

    if (patternTokens.size() != WHILE_LENGTH) {
        return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
    }
    while (ptr < patternTokens.size()) {

        // check if pattern is enclosed by brackets
        if (ptr == 0) {
            if (patternTokens[ptr] != Constants::OPEN_BRACKET || patternTokens[patternTokens.size() - 1] != Constants::CLOSE_BRACKET) {
                return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
            }
        }

        // check if entRef is valid
        if (ptr == 1) {
            entRef = ParserUtils::getValidEntRef(patternTokens[ptr], declarations);
            if (ParserUtils::isSyntaxError(entRef)) {
                return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
            }
            if (ParserUtils::isSemanticError(entRef)) {
                hasSemanticError = true;
            }
        }

        if (ptr == 2 && patternTokens[ptr] != Constants::SEPARATOR) {
            return make_pair(Synonym::create(Constants::SYNTAX_ERROR, ""), nullptr);
        }

        if (ptr == 3 && patternTokens[ptr] != Constants::WILDCARD) {
            hasSemanticError = true;
        }
        ptr++;
    }
    if (hasSemanticError) {
        return make_pair(Synonym::create(Constants::SEMANTIC_ERROR, ""), nullptr);
    }
    return make_pair(patternSynonym, Clause::create(Constants::PATTERN, entRef, Wildcard::create()));
}