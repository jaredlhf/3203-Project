#include <stdio.h>
#include <unordered_set>
#include "QueryParser.h"

using namespace std;

string SELECT_MARKER = "select";
string PATTERN_MARKER = "pattern";
vector<string> SUCHTHAT_MARKER = {"such", "that"};
vector<string> DESIGN_ENTITIES = {"stmt", "read", "print", "call", 
"while","if", "assign", "variable", "constant", "procedure"};
int MIN_DECLARATION_LENGTH = 2;

unordered_set<string> declared_synonyms = {};
unordered_set<string> assignment_synonyms = {};

bool QueryParser::isValidIntegerString(string s) {
    // checks if string exists
    if (s.empty()) {
        return false;
    }

    // checks if string is a valid integer
    try {
        int v = stoi(s);
    } 
    catch (exception &err) {
        return false;
    }

    // checks if integer string has leading zeroes
    if (s[0] == '0' && s.length() > 1) {
        return false;
    }

    return true;
}

bool QueryParser::isValidNaming(string s) {
    // checks if first character of synonym name or variable name starts with a letter
    for (int i = 0; i < s.length(); i++) {
        if (i == 0 && !isalpha(s[i])) {
            return false;
        }

        if (!isalpha(s[i]) || !isdigit(s[i])) {
            return false;
        }
    }

    return true;
}

bool QueryParser::isValidDeclaration(vector<string> s) {
    if (s.size() < MIN_DECLARATION_LENGTH) {
        return false;
    }

    // check if design entity is valid
    if (!any_of(DESIGN_ENTITIES.begin(), DESIGN_ENTITIES.end(), s[0])) {
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

bool QueryParser::isValidPatternClause(vector<string> s) {
    // check if syn-assign is declared
    if (assignment_synonyms.find(s[0]) == assignment_synonyms.end()) {
        return false;
    }

    // check if pattern is enclosed by brackets
    if (s[1] != "(" || s[s.size() - 1] != ")") {
        return false;
    }

    
}

vector<vector<string>> QueryParser::parseQueryTokens(vector<string> tokens) {
    vector<vector<string>> declarations = {};
    string synonym = "";
    vector<string> suchThatClause = {};
    vector<string> patternClause = {};
    

    int ptr = 0;
    bool isDeclaration = true;
    bool afterSynonym = false;
    while (ptr < tokens.size()) {
        // get declarations
        if (isDeclaration) {
            vector<string> declaration = {};
            while (tokens[ptr] != ";" && ptr < tokens.size()) {
                declaration.push_back(tokens[ptr]);
                ptr++;
            }
            if (isValidDeclaration(declaration)) {
                declarations.push_back(declaration);
            } else {
                return {};
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

        // find pattern/suchthat after declarations and select synonym
        if (afterSynonym && !isDeclaration) {
            // get pattern clause
            if (tokens[ptr] == "pattern") {

            } else if (ptr + 1 < tokens.size()) {
                // get such that clause
                if (tokens[ptr] == SUCHTHAT_MARKER[0] && tokens[ptr + 1] == SUCHTHAT_MARKER[1]) {

                }
            }
        }
        
        
        

    }
       

}