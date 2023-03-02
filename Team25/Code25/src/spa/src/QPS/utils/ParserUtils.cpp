#include "ParserUtils.h"

// BUG: does not work with unordered_set.find()
//std::unordered_set<std::string> DESIGN_ENTITIES = {Constants::STMT, Constants::READ, Constants::PRINT, Constants::CALL,
//             Constants::WHILE, Constants::IF, Constants::ASSIGN, Constants::VARIABLE, Constants::CONSTANT, Constants::PROCEDURE};
std::unordered_set<std::string> DESIGN_ENTITIES = {"stmt", "read", "print", "call", "while", "if", "assign", "variable", "constant", "procedure"};
std::unordered_set<std::string> RELREF = {"Follows", "Follows*", "Parent", "Parent*", "Uses", "Modifies", "Calls", "Calls*", "Next", "Next*"};

bool ParserUtils::isValidIntegerString(const std::string& s) {
    // checks if string exists
    if (s.empty()) {
        return false;
    }

    // checks if the string contains any non-numerical characters
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    if (s.empty() || it != s.end()) {
        return false;
    }
    
    // checks if integer string has leading zeroes
    if (s[0] == '0' && s.length() > 1) {
        return false;
    }

    return true;
}

bool ParserUtils::isValidNaming(const std::string& s) {
    if (s.length() == 0) {
        return false;
    }

    // checks if first character of synonym name or variable name starts with a letter
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if (i == 0 && !isalpha(c)) {
            return false;
        }

        if (!isalpha(c) && !isdigit(c)) {
            return false;
        }
    }

    return true;
}

std::shared_ptr<Entity> ParserUtils::getValidEntRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations) {
    if (s == Constants::WILDCARD) {
        return Wildcard::create();
    }

    if (s.find('"') != std::string::npos) {
        std::string cleanString = removeQuotations(s);
        if (isValidNaming(cleanString)) {
            return Value::create(cleanString);
        }
    }

    if (isValidNaming(s)) {
        for (auto& d : declarations) {
            if (d->getName() == s) {
                return d;
            }
        }
        return Synonym::create(Constants::SEMANTIC_ERROR, "");
    }
    return Synonym::create(Constants::SYNTAX_ERROR, "");
}

std::shared_ptr<Entity> ParserUtils::getValidProcEntRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations) {
    std::unordered_set<std::string> PROC_DESIGN_ENTITIES = {"assign", "call", "if", "while", "read", "print", "stmt", "procedure"};
    
    if (s == Constants::WILDCARD) {
        return Wildcard::create();
    }

    if (s.find('"') != std::string::npos) {
        std::string cleanString = removeQuotations(s);
        if (isValidNaming(cleanString)) {
            return Value::create(cleanString);
        }
    }

    if (isValidNaming(s)) {
        for (auto& d : declarations) {
            if (d->getName() == s && PROC_DESIGN_ENTITIES.find(d->getKeyword()) != PROC_DESIGN_ENTITIES.end()) {
                return d;
            }
        }
        return Synonym::create(Constants::SEMANTIC_ERROR, "");
    }
    return Synonym::create(Constants::SYNTAX_ERROR, "");
}

std::shared_ptr<Entity> ParserUtils::getValidStmtRef(const std::string& s, const std::vector<std::shared_ptr<Synonym>>& declarations) {
    if (s == Constants::WILDCARD) {
        return Wildcard::create();
    }

    if (isValidIntegerString(s)) {
        return Value::create(s);
    }

    if (isValidNaming(s)) {
        for (auto& d : declarations) {
            if (d->getName() == s) {
                return d;
            }
        }
        return Synonym::create(Constants::SEMANTIC_ERROR, "");
    }
    return Synonym::create(Constants::SYNTAX_ERROR, "");
}

// check for valid expression pattern for milestone 1
// TODO: modify for pattern extensions with operators
bool ParserUtils::isValidExpression(const std::string& s) {
    int length = s.size();
    if (length == 1) {
        return s == Constants::WILDCARD;
    }
    if (s[0] != s[length - 1]) {
        return false;
    }
    if (s[0] != '_') {
        return false;
    }

    if (s[1] != s[length - 2]) {
        return false;
    }

    if (s[1] != '\"') {
        return false;
    }

    std::string cleanedString = s.substr(2, length - 4);
    return isValidNaming(cleanedString) || isValidIntegerString((cleanedString));
}

bool ParserUtils::isDesignEntityToken(const std::string& s) {
    if (DESIGN_ENTITIES.find(s) == DESIGN_ENTITIES.end()) {
        return false;
    }
    return true;
}

bool ParserUtils::isRelRefToken(const std::string& s) {
    if (RELREF.find(s) == RELREF.end()) {
        return false;
    }
    return true;
}

std::string ParserUtils::removeQuotations(const std::string& s) {
    std::string newStr = s;

    if (s[0] == '\"') {
        newStr = s.substr(1, s.size() - 1);
    }
    if (newStr[newStr.size() - 1] == '\"') {
        newStr = newStr.substr(0, newStr.size() - 1);
    }
    return newStr;
}

bool ParserUtils::isSyntaxError(std::shared_ptr<Entity> e) {
    
    if (e->isSynonym()) {
        std::string refKeyword = std::static_pointer_cast<Synonym>(e)->getKeyword();
        return refKeyword == Constants::SYNTAX_ERROR;
    }

    return false;
}

bool ParserUtils::isSemanticError(std::shared_ptr<Entity> e) {
    
    if (e->isSynonym()) {
        std::string refKeyword = std::static_pointer_cast<Synonym>(e)->getKeyword();
        return refKeyword == Constants::SEMANTIC_ERROR;
    }

    return false;
}

bool ParserUtils::isExpectedSynonym(std::shared_ptr<Entity> e, const std::string& s) {
    if (!e->isSynonym()) {
        false;
    }

    return std::static_pointer_cast<Synonym>(e)->getKeyword() == s;
}