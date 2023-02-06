#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

class Token {
public:
    static bool isValidName(std::string variable);
    virtual bool isEqual(std::string tokenString) = 0;
};

class Procedure: public Token {
public:
    bool isEqual(std::string tokenString) override;
};

class Name: public Token {
public:
    bool isEqual(std::string tokenString) override;
};

class LeftBrace: public Token {
public:
    bool isEqual(std::string tokenString) override;
};

class RightBrace: public Token {
public:
    bool isEqual(std::string tokenString) override;
};

class Statement: public Token {
public:
    bool isEqual(std::string tokenString) override;
};

class Equal: public Token {
public:
    bool isEqual(std::string tokenString) override;
};

class Semicolon: public Token {
public:
    bool isEqual(std::string tokenString) override;
};

#endif