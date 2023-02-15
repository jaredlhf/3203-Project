#include "Parser.h"


Parser::Parser(std::shared_ptr<Tokenizer> t, std::shared_ptr<PkbPopulator> populator) {
    this->tokenizer = t;
    this->pkbPopulator = populator;
    this->utils = std::make_shared<ParserUtils>(t);
};


void Parser::parseProgram() {
    do {
        if (tokenizer->getTokens().empty()) {
            throw std::invalid_argument("error: no procedures found");
        } else {
            ProcedureNode proc = parseProcedure();
            StmtLstNode s = *(proc.getStmtLst());
            for (const auto & i : (s.getStatements())) {
                i->accept();
            }
        }
    } while (!tokenizer->getTokens().empty());
}


ProcedureNode Parser::parseProcedure() {
    utils->expect(std::make_shared<Procedure>());
    utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<LeftBrace>());
    StmtLstNode stmtLst = StmtParser::parseStmtLst(this->utils, this->tokenizer);
    ProcedureNode node = ProcedureNode(std::make_shared<StmtLstNode>(stmtLst));
    utils->expect(std::make_shared<RightBrace>());
    return node;
}





