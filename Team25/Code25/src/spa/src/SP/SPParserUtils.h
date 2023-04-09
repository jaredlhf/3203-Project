#ifndef SPA_SPPARSERUTILS_H
#define SPA_SPPARSERUTILS_H

#include <string>
#include "Token.h"
#include "Tokenizer.h"
#include "SPConstants.h"

class SPParserUtils {
public:
    SPParserUtils(std::shared_ptr<Tokenizer> t);
    std::string expect(const std::string expectedToken);
    int getCurrentStmtNo();
    void incrementStmtNo();

private:
    std::shared_ptr<Tokenizer> tokenizer;
    int currentStmtNo;
};

#endif //SPA_SPPARSERUTILS_H
