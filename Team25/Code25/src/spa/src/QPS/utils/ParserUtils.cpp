#include "ParserUtils.h"


// BUG: does not work with unordered_set.find()
// std::unordered_set<std::string> DESIGN_ENTITIES = {Constants::STMT, Constants::READ, Constants::PRINT, Constants::CALL,
//             Constants::WHILE, Constants::IF, Constants::ASSIGN, Constants::VARIABLE, Constants::CONSTANT, Constants::PROCEDURE};
std::unordered_set<std::string> DESIGN_ENTITIES = {"stmt", "read", "print", "call", "while", "if", "assign", "variable", "constant", "procedure"};
std::unordered_set<std::string> RELREF = {"Follows", "Follows*", "Parent", "Parent*", "Uses", "Modifies"};

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

bool ParserUtils::isValidEntRef(const std::string& s) {
    
    if (s == Constants::WILDCARD) {
        return true;
    }
    if (s[0] == '\"' && s[s.size() - 1] == '\"') {
        return isValidNaming(s.substr(1, s.size() - 2));
    }

    return isValidNaming(s);
}

// check for valid expression pattern for milestone 1
// TODO: modify for pattern extensions with operators
bool ParserUtils::isValidExpression(std::vector<std::string> s) {
    if (s.size() == 1) {
        std::string token = removeQuotations(s[0]);
        return token == Constants::WILDCARD;
    }
    if (s.size() == 3) {
        if (s[0] == s[2] && s[0] == Constants::WILDCARD) {
            std::string token = removeQuotations(s[1]);
            return isValidNaming(token) || isValidIntegerString(token);
        }
    }
    return false;
}

bool ParserUtils::isDesignEntityToken(const std::string& s) {
    if (DESIGN_ENTITIES.find(s) == DESIGN_ENTITIES.end()) {
        std::cout << "invalid design entity" << std::endl;
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
