#include "QueryParser.h"

int MIN_DECLARATION_LENGTH = 2;
int SUCH_THAT_LENGTH = 8;
const std::string SELECT_MARKER = "Select";
const std::string PATTERN_MARKER = "pattern";
const std::string OPEN_BRACKET = "(";
const std::string CLOSE_BRACKET = ")";
const std::string DECLARATION_END_TOKEN = ";";
const std::string SEPARATOR = ",";
std::vector<std::string> SUCHTHAT_MARKER = {"such", "that"};

bool QueryParser::isValidDeclaration(std::vector<std::string> s,
        std::unordered_set<std::string>& declared_synonyms, std::unordered_set<std::string>& assignment_synonyms) {

    if (s.size() < MIN_DECLARATION_LENGTH) {
        return false;
    }

    // check if design entity is valid
    if (!ParserUtils::isDesignEntityToken(s[0])) {
        return false;
    }

    for (int i = 1; i < s.size(); i++) {

        // checking that variables are separated by commas
        if (i % 2 == 0 && s[i] != SEPARATOR) {
            return false;
        }

        // checking if variable names are in correct format
        if (i % 2 != 0) {
            if (!ParserUtils::isValidNaming(s[i])) {
                return false;
            }

            if (s[0] == Constants::ASSIGN) {
                assignment_synonyms.insert(s[i]);
            }
        }

    }
    return true;
}

ValidatePatternResponse QueryParser::validatePatternClause(std::vector<std::string> s, 
        std::unordered_set<std::string> assignment_synonyms, std::vector<std::shared_ptr<Synonym>> declarations) {
    
    std::string keyword;
    std::string entRef;
    std::string expression;
    ValidatePatternResponse response;

    int ptr = 0;
    while (ptr < s.size()) {
        if (ptr == 0) {
            keyword = s[ptr];
        }

        // check if syn-assign is declared
        if (ptr == 1) {
            if (assignment_synonyms.find(s[ptr]) == assignment_synonyms.end()) {
                response.setAssignSyn(Synonym::create(Constants::SEMANTIC_ERROR, ""));
            } else {
                response.setAssignSyn(Synonym::create(Constants::ASSIGN, s[ptr]));
            }
        }
        
        // check if pattern is enclosed by brackets
        if (ptr == 2) {
            if (s[ptr] != OPEN_BRACKET || s[s.size() - 1] != CLOSE_BRACKET) {
                return response;
            }
        }

        // check if entRef is valid
        if (ptr == 3) {
            std::shared_ptr<Entity> entRef = ParserUtils::getValidEntRef(s[ptr], declarations);

            if (entRef->isSynonym()) {
                // TODO: extract this to a function
                if (std::static_pointer_cast<Synonym>(entRef)->getKeyword() == Constants::SYNTAX_ERROR) {
                    response.setAssignSyn(Synonym::create(Constants::SYNTAX_ERROR, ""));
                } else if (std::static_pointer_cast<Synonym>(entRef)->getKeyword() == Constants::SEMANTIC_ERROR) {
                    response.setAssignSyn(Synonym::create(Constants::SEMANTIC_ERROR, ""));
                }
            }
            response.setEntRef(entRef);
        }

        if (ptr == 4 && s[ptr] != SEPARATOR) {
            return response;
        }
        
        // retrieve pattern
        if (ptr == 5) {
            expression = s[ptr];
        }
        ptr++;
    }

    if (!ParserUtils::isValidExpression(expression)) {
        return response;
    }

    if (expression == Constants::WILDCARD) {
        response.setPattern(Wildcard::create());
    } else {
        // only for partial matching
        // TODO: adapt to other possible patterns in future milestones
        std::string cleanedString = expression.substr(2, expression.size() - 4);
        response.setPattern(Wildcard::create(cleanedString));
    }

    return response;
}

std::vector<std::string> QueryParser::validateSuchThatClause(std::vector<std::string> s) {
    if (s.size() != SUCH_THAT_LENGTH) {
        return {};
    }
    
    if (s[0] != SUCHTHAT_MARKER[0] || s[1] != SUCHTHAT_MARKER[1]) {
        return {};
    }
    for (int i = 0; i < 2; i++) {
        s.erase(s.begin());
    }

    if (!ParserUtils::isRelRefToken(s[0])) {
        return {};
    }

    if (s[1] != OPEN_BRACKET || s[s.size() - 1] != CLOSE_BRACKET) {
        return {};
    }

    if (s[3] != SEPARATOR) {
        return {};
    }

    return { s[0], s[2], s[4] };
}

std::vector<std::shared_ptr<Synonym>> QueryParser::processDeclaration(std::vector<std::string> declaration, 
        std::unordered_set<std::string> declared_synonyms) {

    std::vector<std::shared_ptr<Synonym>> declarations = {};

    std::string keyword = declaration[0];
    for (int i = 1; i < declaration.size(); i++) {

        if (i % 2 == 0) {
            continue;
        }
        
        // creating the Synonym
        if (i % 2 != 0) {
            if (declared_synonyms.find(declaration[i]) != declared_synonyms.end()) {
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
    bool hasSemanticError = false;

    std::vector<std::shared_ptr<Synonym>> declarations = {};
    std::shared_ptr<Synonym> synonym;
    std::shared_ptr<Synonym> assignSynonym;
    std::shared_ptr<Clause> patternClause;
    std::shared_ptr<Clause> suchThatClause;

    int ptr = 0;

    // get all declarations
    while (ptr < tokenLength) {
        // check if declarations are over
        if (tokens[ptr] == SELECT_MARKER) {
            break;
        }
        // retrieve a declaration phrase
        std::vector<std::string> declaration = {};
        while (ptr < tokenLength && tokens[ptr] != DECLARATION_END_TOKEN) {
            declaration.push_back(tokens[ptr]);
            ptr++;
        }
        if (!isValidDeclaration(declaration, declared_synonyms, assignment_synonyms)) {
            return generateSyntaxErrorResponse();
        }
        std::vector<std::shared_ptr<Synonym>> temp = processDeclaration(declaration, declared_synonyms);
        if (temp.empty()) {
            hasSemanticError = true;
        } 
        declarations.insert(declarations.end(), temp.begin(), temp.end());

        ptr++;
    }

    // get synonym for select statement
    bool hasSeenSelectToken = false;
    bool afterSynonym = false;
    while (ptr < tokenLength) {
        // invalid semicolon token after declarations
        if (tokens[ptr] == DECLARATION_END_TOKEN) {
            return generateSyntaxErrorResponse();
        }
        if (hasSeenSelectToken && afterSynonym) {
            if (tokens[ptr] != PATTERN_MARKER && tokens[ptr] != SUCHTHAT_MARKER[0]) {
                return generateSyntaxErrorResponse();
            }
            if (tokens[ptr] == PATTERN_MARKER || tokens[ptr] == SUCHTHAT_MARKER[0]) {
                break;
            }
        }
        if (tokens[ptr] == SELECT_MARKER && !hasSeenSelectToken) {
            ptr++;
            hasSeenSelectToken = true;
            continue;
        }
        if (hasSeenSelectToken) {
            for (auto& element: declarations) {
                if (element->matchesName(tokens[ptr])) {
                    synonym = element;
                    afterSynonym = true;
                    break;
                }
            }
            if (!afterSynonym) {
                hasSemanticError = true;
                break;
            }
        }

        ptr++;
    }
    while (ptr < tokenLength) {
        // invalid semicolon token after declarations
        if (tokens[ptr] == DECLARATION_END_TOKEN) {
            return generateSyntaxErrorResponse();
        }
        // get pattern clause after declarations and select synonym
        if (tokens[ptr] == PATTERN_MARKER) {
            std::vector<std::string> patternTokens = {};
            while (ptr < tokenLength) {
                if (tokens[ptr] == CLOSE_BRACKET) {
                    patternTokens.push_back(tokens[ptr]);
                    break;
                }
                patternTokens.push_back(tokens[ptr]);
                ptr++;
            }

            ValidatePatternResponse response = validatePatternClause(patternTokens, assignment_synonyms, declarations);

            if (response.getAssignSyn()->getKeyword() == Constants::SEMANTIC_ERROR) {
                hasSemanticError = true;
            }

            if (response.isIncomplete() || response.getAssignSyn()->getKeyword() == Constants::SYNTAX_ERROR) {
                return generateSyntaxErrorResponse();
            }
            patternClause = Clause::create(Constants::PATTERN, response.getEntRef(), response.getPattern());
            assignSynonym = response.getAssignSyn();
        }

        if (tokens[ptr] == SUCHTHAT_MARKER[0]) {
            std::vector<std::string> suchThatTokens;
            while (ptr < tokenLength) {
                if (tokens[ptr] == CLOSE_BRACKET) {
                    suchThatTokens.push_back(tokens[ptr]);
                    break;
                }
                suchThatTokens.push_back(tokens[ptr]);
                ptr++;
            }

            std::vector<std::string> suchThatArgs = validateSuchThatClause(suchThatTokens);
            if (suchThatArgs.empty()) {
                return generateSyntaxErrorResponse();
            }

            std::shared_ptr<Relationship> relationshipValidator = Relationship::create(suchThatArgs[0], suchThatArgs[1], suchThatArgs[2]);
            std::vector<std::shared_ptr<Entity>> refs = relationshipValidator->verifyRelationship(declarations); 
            std::string refKeyword;
            if (refs[0]->isSynonym()) {
                refKeyword = std::static_pointer_cast<Synonym>(refs[0])->getKeyword();
                if (refKeyword == Constants::SYNTAX_ERROR) {
                    return generateSyntaxErrorResponse();
                } else if (refKeyword == Constants::SEMANTIC_ERROR) {
                    hasSemanticError = true;
                }
            }

            if (refs[1]->isSynonym()) {
                refKeyword = std::static_pointer_cast<Synonym>(refs[1])->getKeyword();
                if (refKeyword == Constants::SYNTAX_ERROR) {
                    return generateSyntaxErrorResponse();
                } else if (refKeyword == Constants::SEMANTIC_ERROR) {
                    hasSemanticError = true;
                }
            }

            suchThatClause = Clause::create(relationshipValidator->getKeyword(), refs[0], refs[1]);
        }

        ptr++;    
    }
    if (hasSemanticError) {
        return generateSemanticErrorResponse();
    }
    responseObject.setDeclarations(declarations);
    responseObject.setSynonym(synonym);
    responseObject.setAssignSynonym(assignSynonym);
    responseObject.setPatternClause(patternClause);
    responseObject.setSuchThatClause(suchThatClause);
    


    return responseObject;
}