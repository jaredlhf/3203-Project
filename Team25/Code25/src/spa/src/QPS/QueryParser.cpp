#include "QueryParser.h"
#include "ParserResponse.h"
#include "constants/Constants.h"
#include "constants/Synonym.h"
#include "constants/Clause.h"
#include "constants/Wildcard.h"

std::string SELECT_MARKER = "Select";
std::string PATTERN_MARKER = "pattern";
std::vector<std::string> SUCHTHAT_MARKER = {"such", "that"};

// BUG: does not work with unordered_set.find()
// std::unordered_set<std::string> DESIGN_ENTITIES = {Constants::STMT, Constants::READ, Constants::PRINT, Constants::CALL,
// Constants::WHILE, Constants::IF, Constants::ASSIGN, Constants::VARIABLE, Constants::CONSTANT, Constants::PROCEDURE};

std::unordered_set<std::string> DESIGN_ENTITIES = {"stmt", "read", "print", "call", "while", "if", "assign", "variable", "constant", "procedure"};
int MIN_DECLARATION_LENGTH = 2;

bool QueryParser::isValidIntegerString(const std::string& s) {
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

bool QueryParser::isValidNaming(const std::string& s) {

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

bool QueryParser::isValidDeclaration(std::vector<std::string> s,
    std::unordered_set<std::string>& declared_synonyms, 
    std::unordered_set<std::string>& assignment_synonyms) {

    if (s.size() < MIN_DECLARATION_LENGTH) {
        std::cout << "too short" << std::endl;
        return false;
    }

    // check if design entity is valid
    if (DESIGN_ENTITIES.find(s[0]) == DESIGN_ENTITIES.end()) {
        std::cout << "invalid design entity" << std::endl;
        return false;
    }

    for (int i = 1; i < s.size(); i++) {

        // checking that variables are separated by commas
        if (i % 2 == 0 && s[i] != ",") {
            std::cout << "not csv" << std::endl;
            return false;
        }

        // checking if variable names are in correct format
        if (i % 2 != 0) {
            if (!isValidNaming(s[i])) {
                std::cout << "invalid name" << std::endl;
                return false;
            }

            if (s[0] == "assign") {
                assignment_synonyms.insert(s[i]);
            }
        }

    }

    return true;
}

bool QueryParser::isValidEntRef(const std::string& s) {
    
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
bool QueryParser::isValidExpression(std::vector<std::string> s) {
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

ValidatePatternResponse QueryParser::validatePatternClause(std::vector<std::string> s, std::unordered_set<std::string> assignment_synonyms, std::vector<std::shared_ptr<Synonym>> declarations) {
    std::string keyword;
    std::string entRef;
    std::vector<std::string> expression;
    ValidatePatternResponse response;

    int ptr = 0;
    while (ptr < s.size()) {
        if (ptr == 0) {
            keyword = s[ptr];
        }

        // check if syn-assign is declared
        if (ptr == 1) {
            if (assignment_synonyms.find(s[ptr]) == assignment_synonyms.end()) {
                std::cout << "invalid assign syn" << std::endl;
                response.setAssignSyn(Synonym::create(Constants::SEMANTIC_ERROR, ""));
            } else {
                response.setAssignSyn(Synonym::create(Constants::ASSIGN, s[ptr]));
            }
            
        }
        
        // check if pattern is enclosed by brackets
        if (ptr == 2) {
            if (s[ptr] != "(" || s[s.size() - 1] != ")") {
                std::cout << "no brackets" << std::endl;
                return response;
            }
        }

        // check if entRef is valid
        if (ptr == 3) {
            if (!isValidEntRef(s[ptr])) {
                std::cout << "invalid entref" << std::endl;
                return response;
            }
            // if is wildcard
            if (s[ptr] == "_") {
                response.setEntRef(Wildcard::create());
            // if is variable synonym, check if already declared
            } else if (s[ptr].find('"') == std::string::npos) {
                bool isDeclared = false;

                for (auto& d : declarations) {
                    if (d->getKeyword() == Constants::VARIABLE && d->getName() == s[ptr]) {
                        response.setEntRef(Synonym::create(Constants::VARIABLE, s[ptr]));
                        isDeclared = true;
                        break;
                    }
                }

                if (!isDeclared) {
                    response.setAssignSyn(Synonym::create(Constants::SEMANTIC_ERROR, ""));
                }
            } 
            // if is constant value
            else {
                response.setEntRef(Value::create(s[ptr]));
            }
        }

        if (ptr == 4 && s[ptr] != ",") {
            std::cout << "not a comma" << std::endl;
            return response;
        }
        
        // retrieve pattern
        while (ptr > 4 && ptr < s.size() - 1) {
            expression.push_back(s[ptr]);
            ptr++;
        }
        ptr++;
    }

    if (!isValidExpression(expression)) {
        return response;
    }

    if (expression.size() > 1) {
        response.setPattern(Value::create(expression[1]));
    } else {
        response.setPattern(Wildcard::create());    
    }

    return response;
}

std::string QueryParser::removeQuotations(const std::string& s) {
    std::string newStr = s;

    if (s[0] == '\"') {
        newStr = s.substr(1, s.size() - 1);
    }
    if (newStr[newStr.size() - 1] == '\"') {
        newStr = newStr.substr(0, newStr.size() - 1);
    }
    return newStr;
}

std::vector<std::shared_ptr<Synonym>> QueryParser::processDeclaration(std::vector<std::string> declaration, std::unordered_set<std::string> declared_synonyms) {
    std::vector<std::shared_ptr<Synonym>> declarations = {};

    std::string keyword = declaration[0];
    for (int i = 1; i < declaration.size(); i++) {

        if (i % 2 == 0) {
            continue;
        }
        
        // creating the Synonym
        if (i % 2 != 0) {
            if (declared_synonyms.find(declaration[i]) != declared_synonyms.end()) {
                std::cout << "repeated name" << std::endl;
                return {};
            }
            declared_synonyms.insert(declaration[i]);
            declarations.push_back(Synonym::create(keyword, declaration[i]));
        }
    }
    return declarations;
}

ParserResponse QueryParser::generateSyntaxErrorResponse() {
    ParserResponse responseObject;
    std::shared_ptr<Synonym> synonym = Synonym::create(Constants::SYNTAX_ERROR, "");
    responseObject.setSynonym(synonym);
    return responseObject;
}

ParserResponse QueryParser::generateSemanticErrorResponse() {
    ParserResponse responseObject;
    std::shared_ptr<Synonym> synonym = Synonym::create(Constants::SEMANTIC_ERROR, "");
    responseObject.setSynonym(synonym);
    return responseObject;
}


ParserResponse QueryParser::parseQueryTokens(std::vector<std::string> tokens) {

    ParserResponse responseObject;

    std::vector<std::shared_ptr<Synonym>> declarations = {};
    std::shared_ptr<Synonym> synonym = nullptr;
    // vector<string> suchThatClause = {};
    std::shared_ptr<Clause> patternClause = {};

    std::unordered_set<std::string> declared_synonyms = {};
    std::unordered_set<std::string> assignment_synonyms = {};

    int ptr = 0;
    bool afterSynonym = false;

    // get all declarations
    while (ptr < tokens.size()) {
        // check if declarations are over
        if (tokens[ptr] == SELECT_MARKER) {
            break;
        }
        std::vector<std::string> declaration = {};
        while (tokens[ptr] != ";" && ptr < tokens.size()) {
            declaration.push_back(tokens[ptr]);
            ptr++;
        }
        if (!isValidDeclaration(declaration, declared_synonyms, assignment_synonyms)) {
            return generateSyntaxErrorResponse();
        }
        std::vector<std::shared_ptr<Synonym>> temp = processDeclaration(declaration, declared_synonyms);
        if (temp.size() == 0) {
            return generateSemanticErrorResponse();
        }
        declarations.insert(declarations.end(), temp.begin(), temp.end());

        ptr++;
    }

    // get synonym for select statement
    while (ptr < tokens.size()) {
        if (afterSynonym && tokens[ptr] != PATTERN_MARKER) {
            std::cout << "invalid select synonym" << std::endl;
            return generateSemanticErrorResponse();
        } else if (afterSynonym && tokens[ptr] == PATTERN_MARKER){
            break;
        }

        if (tokens[ptr] != SELECT_MARKER) {
            // check if synonym used in select statement exists in declaration
            for (auto& element: declarations) {
                if (element->matchesName(tokens[ptr])) {
                    synonym = element;
                    afterSynonym = true;
                    break;
                }
            }
            
        }
        ptr++;
    }

    while (ptr < tokens.size()) {
        if (tokens[ptr] == ";") {
            std::cout << "invalid semicolon token after declarations" << std::endl;
            return generateSyntaxErrorResponse();
        }
        // get pattern clause after declarations and select synonym
        if (tokens[ptr] == PATTERN_MARKER) {
            std::vector<std::string> patternTokens = {};
            while (ptr < tokens.size()) {
                if (tokens[ptr] == ")") {
                    patternTokens.push_back(tokens[ptr]);
                    break;
                }
                patternTokens.push_back(tokens[ptr]);
                ptr++;
            }

            ValidatePatternResponse response = validatePatternClause(patternTokens, assignment_synonyms, declarations);

            if (response.getAssignSyn()->getKeyword() == Constants::SEMANTIC_ERROR) {
                std::cout << "semantic error on pattern" << std::endl;
                return generateSemanticErrorResponse();
            }

            if (response.isIncomplete()) {
                std::cout << "invalid patternClause" << std::endl;
                return generateSyntaxErrorResponse();
            }
            patternClause = Clause::create(Constants::PATTERN, response.getEntRef(), response.getPattern());
        }
        if (ptr + 1 < tokens.size()) {
            // get such that clause
            if (tokens[ptr] == SUCHTHAT_MARKER[0] && tokens[ptr + 1] == SUCHTHAT_MARKER[1]) {

            }
        }

        ptr++;    
    }

    responseObject.setDeclarations(declarations);
    responseObject.setSynonym(synonym);
    responseObject.setPatternClause(patternClause);

    return responseObject;
}