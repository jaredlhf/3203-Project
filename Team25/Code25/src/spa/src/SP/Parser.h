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


class Parser {
public:
    Parser(std::shared_ptr<Tokenizer> t);
    std::vector<ProcedureNode> parseProgram();
private:
    std::shared_ptr<Tokenizer> tokenizer;
    std::shared_ptr<SPParserUtils> utils;

    ProcedureNode parseProcedure();
};

#endif

