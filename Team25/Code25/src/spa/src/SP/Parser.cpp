#include <memory>
#include "Parser.h"


Parser::Parser(std::shared_ptr<Tokenizer> t, std::shared_ptr<SPUtils> spUtil) {
    this->tokenizer = t;
    this->utils = std::make_shared<SPParserUtils>(t);
    this->spUtils = spUtil;
};

std::vector<std::shared_ptr<ParserDTO>> Parser::parseProgram() {
    std::vector<std::shared_ptr<ParserDTO>> procDTOs;
    do {
        if (tokenizer->getTokens().empty()) {
            throw std::invalid_argument("error: no procedures found");
        } else {
            std::shared_ptr<ParserDTO> procedureDTO = parseProcedure();
            procDTOs.push_back(procedureDTO);
        }
    } while (!tokenizer->getTokens().empty());
    return procDTOs;
}


std::shared_ptr<ParserDTO> Parser::parseProcedure() {
    utils->expect(SPConstants::PROCEDURE_TOKEN);
    std::string proc = utils->expect(SPConstants::NAME_TOKEN);
    utils->expect(SPConstants::LEFTBRACE_TOKEN);

    std::shared_ptr<ParserDTO> stmtLstDTO = StmtParser::parseStmtLst(this->utils, this->tokenizer, proc);
    shared_ptr<StmtLstNode> stmtLstNode = std::dynamic_pointer_cast<StmtLstNode>(stmtLstDTO->getNode());
    ProcedureNode node = ProcedureNode(stmtLstNode, proc);

    utils->expect(SPConstants::RIGHTBRACE_TOKEN);

    spUtils->addProc(proc);

    std::shared_ptr<CFGNode> cfgNode = stmtLstDTO->getCFGNode();
    std::shared_ptr<ParserDTO> resultDTO = std::make_shared<ParserDTO>(std::make_shared<ProcedureNode>(node), cfgNode, proc);
    return resultDTO;
}





