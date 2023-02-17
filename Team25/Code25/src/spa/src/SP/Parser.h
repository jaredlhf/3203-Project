#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <vector>

#include "Token.h"
#include "Tokenizer.h"
#include "TNode.h"
#include "ParserUtils.h"
#include "StmtParser.h"
#include "ExpressionParser.h"
#include "PKB/PkbPopulator.h"


class Parser {
public:
    Parser(std::shared_ptr<Tokenizer> t, std::shared_ptr<PkbPopulator> populator);
    ProcedureNode parseProgram();
private:
    std::shared_ptr<PkbPopulator> pkbPopulator;
    std::shared_ptr<Tokenizer> tokenizer;
    std::shared_ptr<ParserUtils> utils;

    ProcedureNode parseProcedure();
};

#endif

