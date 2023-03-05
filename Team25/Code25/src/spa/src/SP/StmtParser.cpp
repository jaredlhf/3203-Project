#include "StmtParser.h"

std::regex value("(\\w+)");

std::shared_ptr<StmtParser> StmtParser::createStmtParser(std::string firstToken, std::string secondToken) {
    if (Token::isValidName(firstToken) && secondToken == "=") {
        return std::make_shared<AssignParser>();
    } else if (firstToken == "read") {
        return std::make_shared<ReadParser>();
    } else if (firstToken == "print") {
        return std::make_shared<PrintParser>();
    } else if (firstToken == "call") {
        return std::make_shared<CallParser>();
    } else if (firstToken == "while") {
        return std::make_shared<WhileParser>();
    } else if (firstToken == "if") {
        return std::make_shared<IfParser>();
    } else {
        throw std::invalid_argument("Not a statement keyword or valid name");
    }
}

std::shared_ptr<ParserDTO> StmtParser::parseStmt(std::string firstToken, std::string secondToken, std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) {
    shared_ptr<StmtParser> sp = createStmtParser(firstToken, secondToken);
    utils->incrementStmtNo();
    std::shared_ptr<ParserDTO> resultDTO = sp->parse(utils, tokenizer, proc);
    return resultDTO;
}

std::shared_ptr<ParserDTO> StmtParser::parseStmtLst(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) {
    std::vector<std::shared_ptr<StmtNode>> StmtLsts;
    std::shared_ptr<CFGNode> head = std::make_shared<CFGNode>();
    std::shared_ptr<CFGNode> cfgNode = head;

    do {
        std::shared_ptr<ParserDTO> stmtDTO = parseStmt(tokenizer->peek(), tokenizer->peekTwice(), utils, tokenizer, proc);
        StmtLsts.push_back(std::dynamic_pointer_cast<StmtNode>(stmtDTO->getNode()));

        if (stmtDTO->getCFGNode() != nullptr) {
            std::shared_ptr<CFGNode> nextCfgNode = stmtDTO->getCFGNode();
            cfgNode->setNextNode(nextCfgNode);
            std::shared_ptr<CFGNode> newCfgNode = std::make_shared<CFGNode>();
            nextCfgNode->setNextNode(newCfgNode);
            cfgNode = newCfgNode;
        } else {
            int nextLineNo = stmtDTO->getLine();
            cfgNode->addLineNo(nextLineNo);
        }
    } while(!RightBrace().isEqual(tokenizer->peek()));
    StmtLstNode node = StmtLstNode(StmtLsts, proc);

    std::shared_ptr<ParserDTO> resultDTO = std::make_shared<ParserDTO>(std::make_shared<StmtLstNode>(node), head);
    return resultDTO;
}

std::shared_ptr<ParserDTO> AssignParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) {
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
    AssignNode node = AssignNode(utils->getCurrentStmtNo(), lhs, rhs, proc);
    utils->expect(std::make_shared<Semicolon>());

    ParserDTO resultDTO = ParserDTO(std::make_shared<AssignNode>(node), utils->getCurrentStmtNo());
    return std::make_shared<ParserDTO>(resultDTO);
}


std::shared_ptr<ParserDTO> PrintParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) {
    utils->expect(std::make_shared<Print>());
    std::string var = utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<Semicolon>());
    PrintNode node = PrintNode(utils->getCurrentStmtNo(), var, proc);

    ParserDTO resultDTO = ParserDTO(std::make_shared<PrintNode>(node), utils->getCurrentStmtNo());
    return std::make_shared<ParserDTO>(resultDTO);
}

std::shared_ptr<ParserDTO> WhileParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) {
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
    shared_ptr<ParserDTO> stmtLstDTO = parseStmtLst(utils, tokenizer, proc);
    shared_ptr<StmtLstNode> stmtLstNode = std::dynamic_pointer_cast<StmtLstNode>(stmtLstDTO->getNode());
    utils->expect(std::make_shared<RightBrace>());

    WhileNode node = WhileNode(lineNo, rhs, stmtLstNode, proc);

    std::shared_ptr<CFGWhileNode> cfgNode = std::make_shared<CFGWhileNode>(std::vector<int>(lineNo));
    std::shared_ptr<CFGNode> loopCfgNode = stmtLstDTO->getCFGNode();
    cfgNode->setLoopNode(loopCfgNode);
    loopCfgNode->setNextNode(cfgNode);

    ParserDTO resultDTO = ParserDTO(std::make_shared<WhileNode>(node), cfgNode);
    return std::make_shared<ParserDTO>(resultDTO);
}

std::shared_ptr<ParserDTO> IfParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) {
    int lineNo = utils->getCurrentStmtNo();
    utils->expect(std::make_shared<If>());

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
    shared_ptr<ParserDTO> ifLstDTO = parseStmtLst(utils, tokenizer, proc);
    shared_ptr<StmtLstNode> ifLstNode = std::dynamic_pointer_cast<StmtLstNode>(ifLstDTO->getNode());
    utils->expect(std::make_shared<RightBrace>());
    utils->expect(std::make_shared<Else>());
    utils->expect(std::make_shared<LeftBrace>());
    shared_ptr<ParserDTO> elseLstDTO = parseStmtLst(utils, tokenizer, proc);
    shared_ptr<StmtLstNode> elseLstNode = std::dynamic_pointer_cast<StmtLstNode>(elseLstDTO->getNode());
    utils->expect(std::make_shared<RightBrace>());

    IfNode node = IfNode(lineNo, rhs, ifLstNode, elseLstNode, proc);

    std::shared_ptr<CFGIfNode> cfgNode = std::make_shared<CFGIfNode>(std::vector<int>(lineNo));
    std::shared_ptr<CFGNode> thenCfgNode = ifLstDTO->getCFGNode();
    std::shared_ptr<CFGNode> elseCfgNode = elseLstDTO->getCFGNode();
    cfgNode->setThenNode(thenCfgNode);
    cfgNode->setElseNode(elseCfgNode);

    ParserDTO resultDTO = ParserDTO(std::make_shared<IfNode>(node), cfgNode);
    return std::make_shared<ParserDTO>(resultDTO);
}

std::shared_ptr<ParserDTO> ReadParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) {
    utils->expect(std::make_shared<Read>());
    std::string var = utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<Semicolon>());
    ReadNode node = ReadNode(utils->getCurrentStmtNo(), var, proc);

    ParserDTO resultDTO = ParserDTO(std::make_shared<ReadNode>(node), utils->getCurrentStmtNo());
    return std::make_shared<ParserDTO>(resultDTO);
}

std::shared_ptr<ParserDTO> CallParser::parse(std::shared_ptr<SPParserUtils> utils, std::shared_ptr<Tokenizer> tokenizer, const std::string& proc) {
    utils->expect(std::make_shared<Call>());
    std::string var = utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<Semicolon>());
    CallNode node = CallNode(utils->getCurrentStmtNo(), var, proc);

    ParserDTO resultDTO = ParserDTO(std::make_shared<CallNode>(node), utils->getCurrentStmtNo());
    return std::make_shared<ParserDTO>(resultDTO);
}