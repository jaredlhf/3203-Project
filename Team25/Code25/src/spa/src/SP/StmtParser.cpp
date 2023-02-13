#include "StmtParser.h"

std::regex value("(\\w+)");

std::shared_ptr<StmtParser> StmtParser::createStmtParser(std::string stmtType) {
    if (stmtType == "read") {
        return std::make_shared<ReadParser>();
    } else if (stmtType == "print") {
        return std::make_shared<PrintParser>();
    } else if (stmtType == "call") {
        return std::make_shared<CallParser>();
    } else if (stmtType == "while") {
        return std::make_shared<WhileParser>();
    } else if (stmtType == "if") {
        return std::make_shared<IfParser>();
    } else if (Token::isValidName(stmtType)) {
        return std::make_shared<AssignParser>();
    } else {
        throw std::invalid_argument("Not a statement keyword or valid name");
    }
}

TNode StmtParser::parseStmt(std::string stmtType, std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    shared_ptr<StmtParser> sp = createStmtParser(stmtType);
    TNode tn = sp->parse(utils, tokenizer);
    return tn;
}

TNode AssignParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    std::string lhs = utils->expect(std::make_shared<Name>());
    //pkb populate lhs
    //parser->pkbPopulator->addVar(lhs);
    std::cout << "populating:" << lhs << std::endl;
    utils->expect(std::make_shared<Equal>());
    std::string rhs = "";
    vector<string> rhsTokens;
    while(tokenizer->peek() != ";") {
        std::string next = tokenizer->getNextToken();
        rhs = rhs + next;
        rhsTokens.push_back(next);
    }
    if(ExpressionParser::verifyExpr((rhs))) {
        std::smatch result;
        std::vector<std::string> variableVector;
        for (std::string token: rhsTokens) {
            std::regex_search(token, result, value);
            variableVector.push_back(result[0]);
        }
        for (string entity: variableVector)
            if (Token::isValidName((entity))) {
                std::cout << "populating:" << entity << std::endl;
                //parser->pkbPopulator->addVar(entity);
            } else if (Token::isNumber(entity)) {
                //parser->pkbPopulator->addConst(std::stoi(entity));
                std::cout << "populating:" << entity << std::endl;
            }
    } else {
        throw std::invalid_argument("Invalid expression ");
    }

    utils->expect(std::make_shared<Semicolon>());
    return TNode();
}

TNode PrintParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    return TNode();
}

TNode CallParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    return TNode();
}

TNode WhileParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    return TNode();
}

TNode IfParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    return TNode();
}

TNode ReadParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    return TNode();
}