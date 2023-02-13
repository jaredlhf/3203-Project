#include "Token.h"

bool Token::isValidName(const std::string& variable) {
    if (!((variable[0] >= 'a' && variable[0] <= 'z')
          || (variable[0] >= 'A' && variable[0] <= 'Z')
          || variable[0] == '_'))
        return false;
    for (int i = 1; i < variable.length(); i++) {
        if (!((variable[i] >= 'a' && variable[i] <= 'z')
              || (variable[i] >= 'A' && variable[i] <= 'Z')
              || (variable[i] >= '0' && variable[i] <= '9')
              || variable[i] == '_'))
            return false;
    }
    return true;
}

bool Token::isNumber(const std::string& str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) {
        ++it;
    }
    return !str.empty() && it == str.end();
}

bool Procedure::isEqual(std::string tokenString) {
    return tokenString == "procedure";
}

bool Name::isEqual(std::string tokenString) {
    return isValidName(tokenString);
}

bool LeftBrace::isEqual(std::string tokenString) {
    return tokenString == "{";
}

bool RightBrace::isEqual(std::string tokenString) {
    return tokenString == "}";
}

bool Statement::isEqual(std::string tokenString) {
    // TODO: implementation
    return true;
}

bool Equal::isEqual(std::string tokenString) {
    return tokenString == "=";
}

bool Semicolon::isEqual(std::string tokenString) {
    return tokenString == ";";
}

bool Read::isEqual(std::string tokenString) {
    return tokenString == "read";
}

bool Print::isEqual(std::string tokenString) {
    return tokenString == "print";
}

bool While::isEqual(std::string tokenString) {
    return tokenString == "while";
}

bool If::isEqual(std::string tokenString) {
    return tokenString == "if";
}

bool Then::isEqual(std::string tokenString) {
    return tokenString == "then";
}

bool Else::isEqual(std::string tokenString) {
    return tokenString == "else";
}