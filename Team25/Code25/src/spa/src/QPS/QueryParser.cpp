#include "QueryParser.h"
#include "ParserResponse.h"
#include "constants/Constants.h"
#include "constants/Synonym.h"

std::string SELECT_MARKER = "Select";
std::string PATTERN_MARKER = "pattern";
std::vector<std::string> SUCHTHAT_MARKER = {"such", "that"};

std::vector<std::string> DESIGN_ENTITIES = {Constants::STMT, Constants::READ, Constants::PRINT, Constants::CALL,
Constants::WHILE, Constants::IF, Constants::ASSIGN, Constants::VARIABLE, Constants::CONSTANT, Constants::PROCEDURE};

int MIN_DECLARATION_LENGTH = 2;

bool QueryParser::isValidIntegerString(const std::string& s) {
    // checks if string exists
    if (s.empty()) {
        return false;
    }

    // checks if string is a valid integer
    try {
        int v = stoi(s);
    } 
    catch (std::exception &err) {
        return false;
    }

    // checks if integer string has leading zeroes
    if (s[0] == '0' && s.length() > 1) {
        return false;
    }

    return true;
}

bool QueryParser::isValidNaming(const std::string& s) {
    // checks if first character of synonym name or variable name starts with a letter
    for (int i = 0; i < s.length(); i++) {
        if (i == 0 && !isalpha(s[i])) {
            return false;
        }

        if (!isalpha(s[i]) && !isdigit(s[i])) {
            return false;
        }
    }

    return true;
}

bool QueryParser::isValidDeclaration(std::vector<std::string> s,
    std::unordered_set<std::string>& declared_synonyms, 
    std::unordered_set<std::string>& assignment_synonyms) {
    
    if (s.size() < MIN_DECLARATION_LENGTH) {
        return false;
    }

    // check if design entity is valid
    if (find(DESIGN_ENTITIES.begin(), DESIGN_ENTITIES.end(), s[0]) == DESIGN_ENTITIES.end()) {
        return false;
    }

    for (int i = 1; i < s.size(); i++) {

        // checking that variables are separated by commas
        if (i % 2 == 0 && s[i] != ",") {
            return false;
        }

        // checking if variable names are in correct format and not repeated
        if (i % 2 != 0) {
            if (!isValidNaming(s[i])) {
                return false;
            }

            
            if (declared_synonyms.find(s[i]) != declared_synonyms.end()) {
                return false;
            }
            if (s[0] == "assign") {
                assignment_synonyms.insert(s[i]);
            }
            declared_synonyms.insert(s[i]);

        }

    }

    return true;
}

std::vector<std::shared_ptr<Synonym>> QueryParser::processDeclaration(std::vector<std::string> declaration) {

}
// bool QueryParser::isValidPatternClause(vector<string> s) {
//     // check if syn-assign is declared
//     if (assignment_synonyms.find(s[0]) == assignment_synonyms.end()) {
//         return false;
//     }

//     // check if pattern is enclosed by brackets
//     if (s[1] != "(" || s[s.size() - 1] != ")") {
//         return false;
//     }    
// }

ParserResponse QueryParser::parseQueryTokens(std::vector<std::string> tokens) {

    ParserResponse responseObject;

    std::vector<std::vector<std::string>> declarations = {};
    std::string synonym = "";
    // vector<string> suchThatClause = {};
    // vector<string> patternClause = {};
    
    std::unordered_set<std::string> declared_synonyms = {};
    std::unordered_set<std::string> assignment_synonyms = {};

    int ptr = 0;
    bool isDeclaration = true;
    bool afterSynonym = false;
    while (ptr < tokens.size()) {

        // get declarations
        if (isDeclaration) {
            std::vector<std::string> declaration = {};
            while (tokens[ptr] != ";" && ptr < tokens.size()) {

                declaration.push_back(tokens[ptr]);
                ptr++;
            }
            ptr++;
            if (isValidDeclaration(declaration, declared_synonyms, assignment_synonyms)) {
                declarations.push_back(declaration);
            } else {
                declarations.push_back({"SyntaxError"});
            }
        }

        // get synonym
        if (tokens[ptr] == SELECT_MARKER) {
            isDeclaration = false;
            afterSynonym = true;
            ptr++;
            if (ptr < tokens.size()) {
                synonym = tokens[ptr];
            }
            ptr++;
        }

        if (ptr >= tokens.size()) {
            break;
        }

        // // find pattern/suchthat after declarations and select synonym
        // if (afterSynonym && !isDeclaration) {
        //     // get pattern clause
        //     if (tokens[ptr] == "pattern") {

        //     } else if (ptr + 1 < tokens.size()) {
        //         // get such that clause
        //         if (tokens[ptr] == SUCHTHAT_MARKER[0] && tokens[ptr + 1] == SUCHTHAT_MARKER[1]) {

        //         }
        //     }
        // }
    }
    ptr++;

    responseObject.setDeclarations(declarations);
    responseObject.setSynonym(synonym);

    return responseObject;
    

}