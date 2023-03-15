#ifndef SPA_SPPARSERUTILS_H
#define SPA_SPPARSERUTILS_H

#include "Token.h"
#include "Tokenizer.h"
#include <string>

class SPParserUtils {
public:
  SPParserUtils(std::shared_ptr<Tokenizer> t);
  std::string expect(std::shared_ptr<Token> expectedToken);
  int getCurrentStmtNo();
  void incrementStmtNo();

private:
  std::shared_ptr<Tokenizer> tokenizer;
  int currentStmtNo;
};

#endif // SPA_SPPARSERUTILS_H
