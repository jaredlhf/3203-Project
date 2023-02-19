#include "SP/Parser.h"
#include "catch.hpp"

//SCENARIO("Testing ParseProgram") {
//    GIVEN("A few assign statements") {
//        std::string shortValidStatement = "x = y + 1;";
//        std::string longValidStatement = "read = y - 1 * f / s % f + 231 + (z) - (w + y);";
//        std::string manyValidStatements = "x = (z) - (w+y);y = a +b;";
//        std::string irregularSpacesValidStatement = "x =    \n"
//                                                    "   1      +\n"
//                                                    "y\n"
//                                                    "   ;";
//
//        std::string invalidLhs = "x+y = y;";
//        std::string invalidRhs = "x= y ++ t;";
//        std::string invalidRhsVarName = "x= y + 0t;";
//
//        std::shared_ptr<AssignParser> ap = std::make_shared<AssignParser>();
//
//
//        WHEN("tokenizer has short valid statement") {
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>();
//            t->tokenize(shortValidStatement);
//
//            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
//            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
//            THEN ("it should generate correct AST") {
//                REQUIRE(node->getVar() == "x");
//                REQUIRE(node->getExpr() == "y+1");
//            }
//        }
//    }
//}
