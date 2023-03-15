#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "ExpressionParser.h"
#include "PKB/PkbPopulator.h"
#include "ParserDTO.h"
#include "SPParserUtils.h"
#include "StmtParser.h"
#include "TNode.h"
#include "Token.h"
#include "Tokenizer.h"

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
