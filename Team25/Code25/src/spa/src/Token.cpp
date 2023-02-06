#include "Token.h"

bool Token::isValidName(std::string variable) {
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

bool Procedure::isEqual(std::string tokenString) {
    return tokenString == "procedure";
}

bool Name::isEqual(std::string tokenString) {
    std::cout << tokenString << std::endl;
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


