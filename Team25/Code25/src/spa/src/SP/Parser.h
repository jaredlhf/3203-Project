#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <vector>

#include "Token.h"
#include "Tokenizer.h"
#include "TNode.h"
#include "SPParserUtils.h"
#include "StmtParser.h"
#include "ExpressionParser.h"
#include "PKB/PkbPopulator.h"
#include "ParserDTO.h"


class Parser {
public:
    Parser(std::shared_ptr<Tokenizer> t);
    std::vector<std::shared_ptr<ParserDTO>> parseProgram();
private:
    std::shared_ptr<Tokenizer> tokenizer;
    std::shared_ptr<SPParserUtils> utils;

    std::shared_ptr<ParserDTO> parseProcedure();
};

#endif

