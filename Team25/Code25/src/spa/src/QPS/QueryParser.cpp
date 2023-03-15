#include "QueryParser.h"
#include "../SP/ExpressionParser.h"

int MIN_DECLARATION_LENGTH = 2;
int SUCH_THAT_LENGTH = 6;
int WHILE_LENGTH = 6;
int IF_LENGTH = 8;
const std::string SELECT_MARKER = "Select";
const std::string PATTERN_MARKER = "pattern";
const std::string AND_MARKER = "and";
const std::string WITH_MARKER = "with";
const std::string DECLARATION_END_TOKEN = ";";
const std::string OPEN_SELECT_BRACKET = "<";
const std::string CLOSE_SELECT_BRACKET = ">";
const std::string EQUALS = "=";
std::vector<std::string> SUCHTHAT_MARKER = {"such", "that"};

bool QueryParser::isValidDeclaration(std::vector<std::string> s) {

    if (s.size() < MIN_DECLARATION_LENGTH) {
        return false;
    }

    // check if design entity is valid
    if (!ParserUtils::isDesignEntityToken(s[0])) {
        return false;
    }

    for (int i = 1; i < s.size(); i++) {

        // checking that variables are separated by commas
        if (i % 2 == 0 && s[i] != Constants::SEPARATOR) {
            return false;
        }

        // checking if variable names are in correct format
        if (i % 2 != 0) {
            if (!ParserUtils::isValidNaming(s[i])) {
                return false;
            }
        }

    }
    return true;
}

std::vector<std::string> QueryParser::validateSuchThatClause(std::vector<std::string> s) {
    if (s.size() != SUCH_THAT_LENGTH) {
        return {};
    }

    if (!ParserUtils::isRelRefToken(s[0])) {
        return {};
    }

    if (s[1] != Constants::OPEN_BRACKET || s[s.size() - 1] != Constants::CLOSE_BRACKET) {
        return {};
    }

    if (s[3] != Constants::SEPARATOR) {
        return {};
    }

    return { s[0], s[2], s[4] };
}

std::vector<std::shared_ptr<Synonym>> QueryParser::validateSelectSynonyms(std::vector<std::string> tokens, const std::vector<std::shared_ptr<Synonym>>& declarations) {

    int tokenLength = tokens.size();
    int synCount = 0;
    std::vector<std::shared_ptr<Synonym>> result = {};
    if (tokens[0] != OPEN_SELECT_BRACKET && tokens[tokenLength - 1] != Constants::CLOSE_BRACKET) {
        return result;
    }
    // delete the open and close brackets
    tokens.erase(tokens.begin());
    tokens.pop_back();

    for (int i = 0; i < tokens.size(); i++) {
        if (i % 2 != 0) {
            if (tokens[i] != Constants::SEPARATOR) {
                return {};
            }
            continue;
        }
        synCount++;
        std::shared_ptr<Synonym> syn;
        if (tokens[i].find(".") != std::string::npos) {
            syn = ParserUtils::getValidAttrRef(tokens[i], declarations);
        } else {
            syn = ParserUtils::getValidDeclaration(tokens[i], declarations);
        }
        
        if (ParserUtils::isSyntaxError(syn)) {
            return {};
        }
        if (!ParserUtils::isSemanticError(syn)) {
            result.push_back(syn);
        }
    }
    // mismatch in parsed synonyms vs approved synonyms
    if (synCount != result.size()) {
        return {Synonym::create(Constants::SEMANTIC_ERROR, "")};
    }

    return result;
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
        if (declared_synonyms.find(declaration[i]) != declared_synonyms.end()) {
            return {};
        }
        declared_synonyms.insert(declaration[i]);
        declarations.push_back(Synonym::create(keyword, declaration[i]));
    }
    return declarations;
}

ParserResponse QueryParser::generateSyntaxErrorResponse() {
    ParserResponse responseObject;
    std::shared_ptr<Synonym> synonym = Synonym::create(Constants::SYNTAX_ERROR, "");
    responseObject.setSelectSynonyms({synonym});
    return responseObject;
}

ParserResponse QueryParser::generateSemanticErrorResponse() {
    ParserResponse responseObject;
    std::shared_ptr<Synonym> synonym = Synonym::create(Constants::SEMANTIC_ERROR, "");
    responseObject.setSelectSynonyms({synonym});
    return responseObject;
}


ParserResponse QueryParser::parseQueryTokens(std::vector<std::string> tokens) {

    ParserResponse responseObject;

    int tokenLength = tokens.size();
    std::unordered_set<std::string> declared_synonyms = {};
    bool hasSemanticError = false;

    std::vector<std::shared_ptr<Synonym>> declarations = {};
    std::vector<std::shared_ptr<Synonym>> selectSynonyms = {};
    std::vector<PatternClausePair> patternClauses;
    std::vector<std::shared_ptr<Clause>> suchThatClauses;
    std::vector<std::shared_ptr<Clause>> withClauses;

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
        if (!isValidDeclaration(declaration)) {
            return generateSyntaxErrorResponse();
        }
        std::vector<std::shared_ptr<Synonym>> temp = processDeclaration(declaration, declared_synonyms);
        if (temp.empty()) {
            hasSemanticError = true;
        } 
        declarations.insert(declarations.end(), temp.begin(), temp.end());

        ptr++;
    }

    // get synonyms for select statement
    bool hasSeenSelectToken = false;
    bool afterSynonym = false;
    std::unordered_set<std::string> afterSynTokens = {"such", "pattern", "with"};
    while (ptr < tokenLength) {
        // invalid semicolon token after declarations
        if (tokens[ptr] == DECLARATION_END_TOKEN) {
            return generateSyntaxErrorResponse();
        }
        if (hasSeenSelectToken && afterSynonym) {
            if (afterSynTokens.find(tokens[ptr]) == afterSynTokens.end()) {
                return generateSyntaxErrorResponse();
            }
            break;
        }
        if (tokens[ptr] == SELECT_MARKER && !hasSeenSelectToken) {
            ptr++;
            hasSeenSelectToken = true;
            continue;
        }
        if (hasSeenSelectToken) {
            std::shared_ptr<Synonym> syn;
            if (tokens[ptr].find(".") != std::string::npos) {
                syn = ParserUtils::getValidAttrRef(tokens[ptr], declarations);
            } else {
                syn = ParserUtils::getValidDeclaration(tokens[ptr], declarations);
            }
             
            bool isSemError = ParserUtils::isSemanticError(syn);
            bool isSynError = ParserUtils::isSyntaxError(syn);

            if (isSynError) {
                if (tokens[ptr] != OPEN_SELECT_BRACKET) {
                    return generateSyntaxErrorResponse();
                }
            }


            // if no synonym found, check if is BOOLEAN query
            if (isSemError && tokens[ptr] == Constants::BOOLEAN) {
                syn = Synonym::create(Constants::BOOLEAN, "");
                isSemError = false;
            }
            
            // confirms its a semantic error, not a boolean query and not an open bracket token
            if (isSemError && tokens[ptr] != OPEN_SELECT_BRACKET) {
                hasSemanticError = true;
                afterSynonym = true;
                ptr++;
                continue;
            }

            // if theres a match, means there is a valid select synonym or boolean query
            if (!isSemError && !isSynError) {
                selectSynonyms.push_back(syn);
                afterSynonym = true;
                ptr++;
                continue;
            }

            // if not semantic error and synonym is empty, means its some other token
            if (tokens[ptr] != OPEN_SELECT_BRACKET) {
                return generateSyntaxErrorResponse();
            }
            // get items within bracket if any
            std::vector<std::string> selectTokens = {};
            while (ptr < tokenLength) {
                if (tokens[ptr] == CLOSE_SELECT_BRACKET) {
                    selectTokens.push_back(tokens[ptr]);
                    break;
                }
                selectTokens.push_back(tokens[ptr]);
                ptr++;
            }
            std::vector<std::shared_ptr<Synonym>> synonyms = validateSelectSynonyms(selectTokens, declarations);
            if (synonyms.empty()) {
                return generateSyntaxErrorResponse();
            }
            if (ParserUtils::isSemanticError(synonyms[0])) {
                hasSemanticError = true;
            }
            selectSynonyms = synonyms;
            afterSynonym = true;
        }

        ptr++;
    }

    bool hasSuch = false;
    bool isSuchThat = false;
    bool isPattern = false;
    bool isWith = false;

    while (ptr < tokenLength) {
        // invalid semicolon token after declarations
        if (tokens[ptr] == DECLARATION_END_TOKEN) {
            return generateSyntaxErrorResponse();
        }
        
        if (hasSuch && tokens[ptr] != SUCHTHAT_MARKER[1]) {
            return generateSyntaxErrorResponse();
        }

        if (tokens[ptr] == AND_MARKER) {
            ptr++;
            continue;
        }

        if (tokens[ptr] == WITH_MARKER && !isWith) {
            ptr++;
            isWith = true;
            continue;
        }

        if (tokens[ptr] == PATTERN_MARKER && !isPattern) {
            isPattern = true;
            ptr++;
            continue;
        }

        if (tokens[ptr] == SUCHTHAT_MARKER[0] && !hasSuch && !isSuchThat) {
            hasSuch = true;
            ptr++;
            continue;
        }

        if (hasSuch && tokens[ptr] == SUCHTHAT_MARKER[1] && !isSuchThat) {
            isSuchThat = true;
            ptr++;
            hasSuch = false;
            continue;
        }

        if (isPattern && !isSuchThat && !isWith) {
            std::vector<std::string> patternTokens = {};
            while (ptr < tokenLength) {
                if (tokens[ptr] == Constants::CLOSE_BRACKET) {
                    patternTokens.push_back(tokens[ptr]);
                    break;
                }
                patternTokens.push_back(tokens[ptr]);
                ptr++;
            }

            if (ptr + 1 >= tokenLength || tokens[ptr + 1] != AND_MARKER) {
                isPattern = false;
            }

            int tokenSize = patternTokens.size();
            if (tokenSize != WHILE_LENGTH && tokenSize != IF_LENGTH) {
                return generateSyntaxErrorResponse();
            }
            std::shared_ptr<Synonym> patternSynonym = ParserUtils::getValidDeclaration(patternTokens[0], declarations);
            if (ParserUtils::isSyntaxError(patternSynonym)) {
                return generateSyntaxErrorResponse();
            }
            std::vector<std::string> patternCond = {patternTokens.begin() + 1, patternTokens.end()};
            std::shared_ptr<PatternValidator> patternValidator = PatternValidator::create(patternSynonym, patternCond);
            PatternClausePair patternPair = patternValidator->verifyPattern(declarations);
            if (ParserUtils::isSyntaxError(patternPair.first)) {
                return generateSyntaxErrorResponse();
            }

            if (ParserUtils::isSemanticError(patternPair.first)) {
                hasSemanticError = true;
            }
            patternClauses.push_back(patternPair);
        }

        if (isSuchThat && !isPattern && !isWith) {
            std::vector<std::string> suchThatTokens;
            while (ptr < tokenLength) {
                if (tokens[ptr] == Constants::CLOSE_BRACKET) {
                    suchThatTokens.push_back(tokens[ptr]);
                    break;
                }
                suchThatTokens.push_back(tokens[ptr]);
                ptr++;
            }

            if (ptr + 1 >= tokenLength || tokens[ptr + 1] != AND_MARKER) {
                isSuchThat = false;
            }

            std::vector<std::string> suchThatArgs = validateSuchThatClause(suchThatTokens);
            if (suchThatArgs.empty()) {
                return generateSyntaxErrorResponse();
            }

            std::shared_ptr<Relationship> relationshipValidator = Relationship::create(suchThatArgs[0], suchThatArgs[1], suchThatArgs[2]);
            std::vector<std::shared_ptr<Entity>> refs = relationshipValidator->verifyRelationship(declarations); 

            std::shared_ptr<Entity> firstRef = refs[0];
            std::shared_ptr<Entity> secondRef = refs[1];

            if (ParserUtils::isSyntaxError(firstRef)) {
                return generateSyntaxErrorResponse();
            }
            if (ParserUtils::isSemanticError(firstRef)) {
                hasSemanticError = true;
            }

            if (ParserUtils::isSyntaxError(secondRef)) {
                return generateSyntaxErrorResponse();
            }
            if (ParserUtils::isSemanticError(secondRef)) {
                hasSemanticError = true;
            }

            suchThatClauses.push_back(Clause::create(relationshipValidator->getKeyword(), firstRef, secondRef));
        }

        if (isWith && !isPattern && !isSuchThat) {
            std::vector<std::string> withTokens = {};

            while (ptr < tokenLength) {
                withTokens.push_back(tokens[ptr]);
                if (withTokens.size() == 3) {
                    break;
                }
                ptr++;
            }

            if (withTokens.size() != 3) {
                return generateSyntaxErrorResponse();
            }

            if (ptr + 1 >= tokenLength || tokens[ptr + 1] != AND_MARKER) {
                isWith = false;
            }

            if (withTokens[1] != EQUALS) {
                return generateSyntaxErrorResponse();
            }

            std::shared_ptr<Entity> firstRef = ParserUtils::getValidWithRef(withTokens[0], declarations);
            std::shared_ptr<Entity> secondRef = ParserUtils::getValidWithRef(withTokens[2], declarations);

            if (ParserUtils::isSyntaxError(firstRef) || ParserUtils::isSyntaxError(secondRef)) {
                return generateSyntaxErrorResponse();
            }
            if (ParserUtils::isSemanticError(firstRef) || ParserUtils::isSemanticError(secondRef)) {
                hasSemanticError = true;
            }
            withClauses.push_back(Clause::create(Constants::WITH, firstRef, secondRef));
        }

        ptr++;    
    }
    if (hasSemanticError) {
        return generateSemanticErrorResponse();
    }

    if (isSuchThat || isPattern) {
        return generateSyntaxErrorResponse();
    }
    
    responseObject.setDeclarations(declarations);
    responseObject.setSelectSynonyms(selectSynonyms);
    responseObject.setPatternClauses(patternClauses);
    responseObject.setSuchThatClauses(suchThatClauses);
    responseObject.setWithClauses(withClauses);

    return responseObject;
}