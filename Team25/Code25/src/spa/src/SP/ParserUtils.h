#ifndef SPA_PARSERUTILS_H
#define SPA_PARSERUTILS_H

#include <string>
#include "Token.h"
#include "Tokenizer.h"

class ParserUtils {
public:
    ParserUtils(std::shared_ptr<Tokenizer> t);
    std::string expect(std::shared_ptr<Token> expectedToken);
    int getCurrentStmtNo();
    void incrementStmtNo();

private:
    std::shared_ptr<Tokenizer> tokenizer;
    int currentStmtNo;
};

#endif //SPA_PARSERUTILS_H
