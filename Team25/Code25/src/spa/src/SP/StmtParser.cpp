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
    } else if (stmtType == "assign") {
        return std::make_shared<AssignParser>();
    } else {
        throw std::invalid_argument("Not a statement keyword or valid name");
    }
}

TNode StmtParser::parseStmt(std::string stmtType, std::shared_ptr<Parser> parser) {
    shared_ptr<StmtParser> sp = createStmtParser(stmtType);
    sp->parse(parser);
}

TNode AssignParser::parse(std::shared_ptr<Parser> parser) {
    std::string lhs = parser->expect(std::make_shared<Name>());
    //pkb populate lhs
    parser->pkbPopulator->addVar(lhs);
    parser->expect(std::make_shared<Equal>());
    std::string rhs = "";
    vector<string> rhsTokens;
    while(parser->tokenizer->peek() != ";") {
        std::string next = parser->tokenizer->getNextToken();
        rhs = rhs + next;
        rhsTokens.push_back(next);
    }
    if(parser->expressionParser.verifyExpr((rhs))) {
        std::smatch result;
        std::vector<std::string> variableVector;
        for (std::string token: rhsTokens) {
            std::regex_search(token, result, value);
            variableVector.push_back(result[0]);
        }
        for (string entity: variableVector)
            if (Token::isValidName((entity))) {
                parser->pkbPopulator->addVar(entity);
            } else if (Token::isNumber(entity)) {
                parser->pkbPopulator->addConst(std::stoi(entity));
            }
    } else {
        throw std::invalid_argument("Invalid expression ");
    }

    parser->expect(std::make_shared<Semicolon>());
}