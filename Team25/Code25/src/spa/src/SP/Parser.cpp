#include "Parser.h"


Parser::Parser(std::shared_ptr<Tokenizer> t) {
    this->tokenizer = t;
    this->utils = std::make_shared<SPParserUtils>(t);
};


std::shared_ptr<ParserDTO> Parser::parseProgram() {
    do {
        if (tokenizer->getTokens().empty()) {
            throw std::invalid_argument("error: no procedures found");
        } else {
            std::shared_ptr<ParserDTO> procedureDTO = parseProcedure();
            return procedureDTO;
        }
    } while (!tokenizer->getTokens().empty());
}


std::shared_ptr<ParserDTO> Parser::parseProcedure() {
    utils->expect(std::make_shared<Procedure>());
    utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<LeftBrace>());
    std::shared_ptr<ParserDTO> stmtLstDTO = StmtParser::parseStmtLst(this->utils, this->tokenizer);
    shared_ptr<StmtLstNode> stmtLstNode = std::dynamic_pointer_cast<StmtLstNode>(stmtLstDTO->getNode());
    ProcedureNode node = ProcedureNode(stmtLstNode);
    utils->expect(std::make_shared<RightBrace>());

    std::shared_ptr<CFGNode> cfgNode = stmtLstDTO->getCFGNode();
    std::shared_ptr<ParserDTO> resultDTO = std::make_shared<ParserDTO>(std::make_shared<ProcedureNode>(node), cfgNode);
    return resultDTO;
}





