#include "QueryParser.h"

int MIN_DECLARATION_LENGTH = 2;
std::string SELECT_MARKER = "Select";
std::string PATTERN_MARKER = "pattern";
std::vector<std::string> SUCHTHAT_MARKER = {"such", "that"};

bool QueryParser::isValidDeclaration(std::vector<std::string> s,
    std::unordered_set<std::string>& declared_synonyms, 
    std::unordered_set<std::string>& assignment_synonyms) {

    if (s.size() < MIN_DECLARATION_LENGTH) {
        std::cout << "too short" << std::endl;
        return false;
    }

    // check if design entity is valid
    if (!ParserUtils::isDesignEntityToken(s[0])) {
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
            if (!ParserUtils::isValidNaming(s[i])) {
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
            if (!ParserUtils::isValidEntRef(s[ptr])) {
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

    if (!ParserUtils::isValidExpression(expression)) {
        return response;
    }

    if (expression.size() > 1) {
        response.setPattern(Value::create(expression[1]));
    } else {
        response.setPattern(Wildcard::create());    
    }

    return response;
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

    int tokenLength = tokens.size();
    std::unordered_set<std::string> declared_synonyms = {};
    std::unordered_set<std::string> assignment_synonyms = {};

    std::vector<std::shared_ptr<Synonym>> declarations = {};
    std::shared_ptr<Synonym> synonym = nullptr;
    // vector<string> suchThatClause = {};
    std::shared_ptr<Clause> patternClause = {};

    int ptr = 0;
    bool afterSynonym = false;

    // get all declarations
    while (ptr < tokenLength) {
        // check if declarations are over
        if (tokens[ptr] == SELECT_MARKER) {
            break;
        }
        std::vector<std::string> declaration = {};
        while (tokens[ptr] != ";" && ptr < tokenLength) {
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
    while (ptr < tokenLength) {

        if (afterSynonym) {
            if (tokens[ptr] != PATTERN_MARKER && tokens[ptr] != SUCHTHAT_MARKER[0]) {
                std::cout << "invalid select synonym" << std::endl;
                return generateSyntaxErrorResponse(); 
            }
            if (tokens[ptr] == PATTERN_MARKER || tokens[ptr] == SUCHTHAT_MARKER[0]) {
                break;
            }
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

    while (ptr < tokenLength) {
        if (tokens[ptr] == ";") {
            std::cout << "invalid semicolon token after declarations" << std::endl;
            return generateSyntaxErrorResponse();
        }
        // get pattern clause after declarations and select synonym
        if (tokens[ptr] == PATTERN_MARKER) {
            std::vector<std::string> patternTokens = {};
            while (ptr < tokenLength) {
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
        if (tokens[ptr] == SUCHTHAT_MARKER[1]) {
            while (ptr < tokenLength) {
                std::cout << tokens[ptr] << std::endl;
                ptr++;
            }
            
        }

        ptr++;    
    }

    responseObject.setDeclarations(declarations);
    responseObject.setSynonym(synonym);
    responseObject.setPatternClause(patternClause);

    return responseObject;
}