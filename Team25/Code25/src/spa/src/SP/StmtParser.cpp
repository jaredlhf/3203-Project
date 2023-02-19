#include "StmtParser.h"

std::regex value("(\\w+)");

std::shared_ptr<StmtParser> StmtParser::createStmtParser(std::string stmtType) {
//    std::cout << "creating: " << stmtType << std::endl;
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

std::shared_ptr<StmtNode> StmtParser::parseStmt(std::string stmtType, std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    shared_ptr<StmtParser> sp = createStmtParser(stmtType);
    utils->incrementStmtNo();
    std::shared_ptr<StmtNode> sn = sp->parse(utils, tokenizer);
    return sn;
}

StmtLstNode StmtParser::parseStmtLst(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    std::vector<std::shared_ptr<StmtNode>> StmtLsts;
    do {
        std::shared_ptr<StmtNode> sn = parseStmt(tokenizer->peek(), utils, tokenizer);
        StmtLsts.push_back(sn);
    } while(!RightBrace().isEqual(tokenizer->peek()));
    StmtLstNode node = StmtLstNode(StmtLsts);
    return node;
}

std::shared_ptr<StmtNode> AssignParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    std::string lhs = utils->expect(std::make_shared<Name>());

    utils->expect(std::make_shared<Equal>());
    std::string rhs = "";
    vector<string> rhsTokens;
    while(tokenizer->peek() != ";") {
        std::string next = tokenizer->getNextToken();
        rhs = rhs + next;
        rhsTokens.push_back(next);
    }
    if (!ExpressionParser::isExpr((rhs))) {
        throw std::invalid_argument("Invalid expression ");
    }
    std::cout<< rhs << " " << utils->getCurrentStmtNo()<<endl;
    AssignNode node = AssignNode(utils->getCurrentStmtNo(), lhs, rhs);
    utils->expect(std::make_shared<Semicolon>());

    return std::make_shared<AssignNode>(node);
}

std::shared_ptr<StmtNode> PrintParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    utils->expect(std::make_shared<Print>());
    std::string var = utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<Semicolon>());
    PrintNode node = PrintNode(utils->getCurrentStmtNo(), var);
    std::cout<< var << " " << utils->getCurrentStmtNo()<<endl;
    return std::make_shared<PrintNode>(node);
}

//TODO: implementation
std::shared_ptr<StmtNode> CallParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    PrintNode node = PrintNode(utils->getCurrentStmtNo(), "ds");
    return std::make_shared<PrintNode>(node);
}

std::shared_ptr<StmtNode> WhileParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    int lineNo = utils->getCurrentStmtNo();
    utils->expect(std::make_shared<While>());
    //parse conditional expr
    std::string rhs = "";
    vector<string> rhsTokens;
    while(tokenizer->peek() != "{") {
        std::string next = tokenizer->getNextToken();
        rhs = rhs + next;
        rhsTokens.push_back(next);
    }
    if (rhs[0] == '(' && rhs[rhs.size()-1] == ')') {
        rhs.pop_back();
        rhs.erase(rhs.begin());
    } else {
        throw std::invalid_argument("no parenthesis for cond_expr");
    }
    if(!ExpressionParser::isCondExpr(rhs)) {
        throw std::invalid_argument("Invalid expression ");
    }

    utils->expect(std::make_shared<LeftBrace>());
    StmtLstNode stmtLstNode = parseStmtLst(utils, tokenizer);
    utils->expect(std::make_shared<RightBrace>());

    std::cout<< rhs << " " << lineNo<<endl;
    WhileNode node = WhileNode(lineNo, rhs, std::make_shared<StmtLstNode>(stmtLstNode));
    return std::make_shared<WhileNode>(node);
}

std::shared_ptr<StmtNode> IfParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    int lineNo = utils->getCurrentStmtNo();
    utils->expect(std::make_shared<If>());
    //parse conditional expr
    std::string rhs = "";
    vector<string> rhsTokens;
    while(tokenizer->peek() != "then") {
        std::string next = tokenizer->getNextToken();
        rhs = rhs + next;
        rhsTokens.push_back(next);
    }
    if (rhs[0] == '(' && rhs[rhs.size()-1] == ')') {
        rhs.pop_back();
        rhs.erase(rhs.begin());
    }else {
        throw std::invalid_argument("no parenthesis for cond_expr");
    }
    if(!ExpressionParser::isCondExpr(rhs)) {
        throw std::invalid_argument("Invalid expression ");
    }


    utils->expect(std::make_shared<Then>());
    utils->expect(std::make_shared<LeftBrace>());
    StmtLstNode ifLstNode = parseStmtLst(utils, tokenizer);
    utils->expect(std::make_shared<RightBrace>());
    utils->expect(std::make_shared<Else>());
    utils->expect(std::make_shared<LeftBrace>());
    StmtLstNode elseLstNode = parseStmtLst(utils, tokenizer);
    utils->expect(std::make_shared<RightBrace>());

    IfNode node = IfNode(lineNo, rhs, std::make_shared<StmtLstNode>(ifLstNode), std::make_shared<StmtLstNode>(elseLstNode));
    std::cout<< rhs << " " << lineNo<<endl;
    return std::make_shared<IfNode>(node);;
}

std::shared_ptr<StmtNode> ReadParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer) {
    utils->expect(std::make_shared<Read>());
    std::string var = utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<Semicolon>());
    std::cout<< var << " " << utils->getCurrentStmtNo()<<endl;
    ReadNode node = ReadNode(utils->getCurrentStmtNo(), var);
    return std::make_shared<ReadNode>(node);;
}