#include "Token.h"


bool Procedure::isValidToken(string tokenString) const {
    return tokenString == "procedure";
}

bool Name::isValidToken(string tokenString) const {
    return Parser::isValidName(tokenString);
}

bool LeftBrace::isValidToken(string tokenString) const {
    return tokenString == "{";
}

bool RightBrace::isValidToken(string tokenString) const {
    return tokenString == "}";
}

bool Statement::isValidToken(string tokenString) const {
    // TODO: implementation
    return true;
}


