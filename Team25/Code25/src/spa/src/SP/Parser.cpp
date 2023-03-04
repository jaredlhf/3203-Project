#include "Parser.h"


Parser::Parser(std::shared_ptr<Tokenizer> t) {
    this->tokenizer = t;
    this->utils = std::make_shared<SPParserUtils>(t);
};

// Returns just a ProcedureNode for milestone 1
std::vector<ProcedureNode> Parser::parseProgram() {
    std::vector<ProcedureNode> procs;
    do {
        if (tokenizer->getTokens().empty()) {
            throw std::invalid_argument("error: no procedures found");
        } else {
            ProcedureNode proc = parseProcedure();
            procs.push_back(proc);
        }
    } while (!tokenizer->getTokens().empty());
    return procs;
}


ProcedureNode Parser::parseProcedure() {
    utils->expect(std::make_shared<Procedure>());
    std::string proc = utils->expect(std::make_shared<Name>());
    utils->expect(std::make_shared<LeftBrace>());
    StmtLstNode stmtLst = StmtParser::parseStmtLst(this->utils, this->tokenizer, proc);
    ProcedureNode node = ProcedureNode(std::make_shared<StmtLstNode>(stmtLst), proc);
    std::cout<< "parser procedure name: " << node.getProc()<<endl;
    utils->expect(std::make_shared<RightBrace>());
    return node;
}





