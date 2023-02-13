#include "StmtParser.h"

std::regex value("(\\w+)");

std::shared_ptr<StmtParser> StmtParser::createStmtParser(std::string stmtType) {
    std::cout << "creating: " << stmtType << std::endl;
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

StmtNode StmtParser::parseStmt(std::string stmtType, std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    shared_ptr<StmtParser> sp = createStmtParser(stmtType);
    StmtNode sn = sp->parse(utils, tokenizer);
    return sn;
}

StmtLstNode StmtParser::parseStmtLst(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    std::vector<StmtNode> StmtLsts;
    do {
        StmtNode sn = parseStmt(tokenizer->peek(), utils, tokenizer);
        StmtLsts.push_back(sn);
    } while(!RightBrace().isEqual(tokenizer->peek()));
    StmtLstNode node = StmtLstNode(StmtLsts);
    return node;
}

StmtNode AssignParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
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
    return StmtNode();
}

StmtNode PrintParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    utils->expect(std::make_shared<Read>());
    utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<Semicolon>());
    return StmtNode();
}

StmtNode CallParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    return StmtNode();
}

StmtNode WhileParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    utils->expect(std::make_shared<While>());
    //parse conditional expr
    utils->expect(std::make_shared<LeftBrace>());
    parseStmtLst(utils, tokenizer);
    utils->expect(std::make_shared<RightBrace>());
    return StmtNode();
}

StmtNode IfParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    utils->expect(std::make_shared<If>());
    //parse conditional expr
    utils->expect(std::make_shared<Then>());
    utils->expect(std::make_shared<LeftBrace>());
    parseStmtLst(utils, tokenizer);
    utils->expect(std::make_shared<RightBrace>());
    utils->expect(std::make_shared<Else>());
    utils->expect(std::make_shared<LeftBrace>());
    parseStmtLst(utils, tokenizer);
    utils->expect(std::make_shared<RightBrace>());
    return StmtNode();
}

StmtNode ReadParser::parse(std::shared_ptr<ParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    utils->expect(std::make_shared<Read>());
    utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<Semicolon>());
    return StmtNode();
}