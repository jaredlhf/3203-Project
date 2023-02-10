#include "StmtParser.h"

TNode AssignParser::parse() {
//    std::string lhs = expect(std::make_shared<Name>());
//    //pkb populate lhs
//    pkbPopulator->addVar(lhs);
//    expect(std::make_shared<Equal>());
//    std::string rhs = "";
//    vector<string> rhsTokens;
//    while(tokens.front() != ";") {
//        rhs = rhs + tokens.front();
//        rhsTokens.push_back((tokens.front()));
//        tokens.erase(tokens.begin());
//    }
//    if(Parser::expressionParser.verifyExpr((rhs))) {
//        std::smatch result;
//        std::vector<std::string> variableVector;
//        for (string token: rhsTokens) {
//            std::regex_search(token, result, value);
//            variableVector.push_back(result[0]);
//        }
//        for (string entity: variableVector)
//            if (isValidVariableName((entity))) {
//                pkbPopulator->addVar(entity);
//            } else if (isNumber(entity)) {
//                pkbPopulator->addConst(std::stoi(entity));
//            }
//    } else {
//        throw std::invalid_argument("Invalid expression ");
//    }
//
//    expect(std::make_shared<Semicolon>());
}