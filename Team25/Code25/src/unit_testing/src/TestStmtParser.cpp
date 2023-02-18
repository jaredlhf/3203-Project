#include "SP/StmtParser.h"
#include "catch.hpp"


SCENARIO("Testing createStmtParser") {
    GIVEN("A few string types") {
        std::string readStr = "read";
        std::string printStr = "print";
        std::string callStr = "call";
        std::string whileStr = "while";
        std::string ifStr = "if";
        std::string assignStr = "name";

        std::string invalidStr = "0dsad";
        std::string invalidStr2 = "32";

        WHEN("valid string") {
            THEN("it should create a StmtParser of the correct type") {
                REQUIRE(typeid(*StmtParser::createStmtParser(readStr)) == typeid(*std::make_shared<ReadParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(printStr)) == typeid(*std::make_shared<PrintParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(callStr)) == typeid(*std::make_shared<CallParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(whileStr)) == typeid(*std::make_shared<WhileParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(ifStr)) == typeid(*std::make_shared<IfParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(assignStr)) == typeid(*std::make_shared<AssignParser>()));
            }
        }

        WHEN("invalid string") {
            THEN("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::createStmtParser(invalidStr), std::invalid_argument);
                REQUIRE_THROWS_AS(StmtParser::createStmtParser(invalidStr2), std::invalid_argument);
            }
        }
    }
}

SCENARIO("Testing AssignParser") {
    GIVEN("A few assign statements") {
        std::string shortValidStatement = "x = y + 1;";
        std::string longValidStatement =  "read = y - 1 * f / s % f + 231 + (z) - (w + y);";
        std::string manyValidStatements =  "x = (z) - (w+y);y = a +b;";
        std::string irregularSpacesValidStatement = "x =    \n"
                                                    "   1      +\n"
                                                    "y\n"
                                                    "   ;";

        std::string invalidLhs = "x+y = y;";
        std::string invalidRhs = "x= y ++ t;";
        std::string invalidRhsVarName = "x= y + 0t;";

        std::shared_ptr<AssignParser> ap = std::make_shared<AssignParser>();


        WHEN("tokenizer has short valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(shortValidStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "y+1");
            }
        }

        WHEN("tokenizer has long valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(longValidStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "read");
                REQUIRE(node->getExpr() == "y-1*f/s%f+231+(z)-(w+y)");
            }
        }

        WHEN("tokenizer has multiple valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(manyValidStatements);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "(z)-(w+y)");
            }
        }

        WHEN("tokenizer has statement with irregular spaces") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(irregularSpacesValidStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "1+y");
            }
        }

        WHEN("tokenizer has invalid statement on the left hand side") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidLhs);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ap->parse(util, t), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement on the right hand side") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidRhs);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ap->parse(util, t), std::invalid_argument);
            }
        }

        WHEN("tokenizer has a statement with an invalid variable on the right hand side ") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidRhsVarName);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ap->parse(util, t), std::invalid_argument);
            }
        }
    }
}

SCENARIO("Testing PrintParser") {
    GIVEN("A few print statements") {
        std::string validStatement = "print y;";

        std::string invalidMissingVarStatement = "print;";
        std::string invalidVarStatement = "print 0re;";

        std::shared_ptr<PrintParser> pp = std::make_shared<PrintParser>();

        WHEN("tokenizer has valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(validStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<PrintNode> node = dynamic_pointer_cast<PrintNode>(pp->parse(util, t));
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "y");
            }
        }

        WHEN("tokenizer has invalid statement with missing variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidMissingVarStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(pp->parse(util, t), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement with invalid variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidVarStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(pp->parse(util, t), std::invalid_argument);
            }
        }
    }
}

SCENARIO("Testing ReadParser") {
    GIVEN("A few read statements") {
        std::string validStatement = "read y;";

        std::string invalidMissingVarStatement = "read;";
        std::string invalidVarStatement = "read 0re;";

        std::shared_ptr<ReadParser> rp = std::make_shared<ReadParser>();

        WHEN("tokenizer has valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(validStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<ReadNode> node = dynamic_pointer_cast<ReadNode>(rp->parse(util, t));
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "y");
            }
        }

        WHEN("tokenizer has invalid statement with missing variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidMissingVarStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(rp->parse(util, t), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement with invalid variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidVarStatement);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(rp->parse(util, t), std::invalid_argument);
            }
        }
    }
}

//SCENARIO("Testing IfParser") {
//    GIVEN("A few if statements") {
//        std::string shortValidStatement = "x = y + 1;";
//        std::string longValidStatement =  "read = y - 1 * f / s % f + 231 + (z) - (w + y);";
//        std::string manyValidStatements =  "x = (z) - (w+y);y = a +b;";
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
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
//            t->tokenize(shortValidStatement);
//
//            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
//            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
//            THEN ("it should generate correct AST") {
//                REQUIRE(node->getVar() == "x");
//                REQUIRE(node->getExpr() == "y+1");
//            }
//        }
//
//        WHEN("tokenizer has long valid statement") {
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
//            t->tokenize(longValidStatement);
//
//            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
//            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
//            THEN ("it should generate correct AST") {
//                REQUIRE(node->getVar() == "read");
//                REQUIRE(node->getExpr() == "y-1*f/s%f+231+(z)-(w+y)");
//            }
//        }
//
//        WHEN("tokenizer has multiple valid statement") {
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
//            t->tokenize(manyValidStatements);
//
//            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
//            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
//            THEN ("it should generate correct AST") {
//                REQUIRE(node->getVar() == "x");
//                REQUIRE(node->getExpr() == "(z)-(w+y)");
//            }
//        }
//
//        WHEN("tokenizer has statement with irregular spaces") {
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
//            t->tokenize(irregularSpacesValidStatement);
//
//            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
//            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(ap->parse(util, t));
//            THEN ("it should generate correct AST") {
//                REQUIRE(node->getVar() == "x");
//                REQUIRE(node->getExpr() == "1+y");
//            }
//        }
//
//        WHEN("tokenizer has invalid statement on the left hand side") {
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
//            t->tokenize(invalidLhs);
//
//            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
//            THEN ("it should throw an error") {
//                REQUIRE_THROWS_AS(ap->parse(util, t), std::invalid_argument);
//            }
//        }
//
//        WHEN("tokenizer has invalid statement on the right hand side") {
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
//            t->tokenize(invalidRhs);
//
//            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
//            THEN ("it should throw an error") {
//                REQUIRE_THROWS_AS(ap->parse(util, t), std::invalid_argument);
//            }
//        }
//
//        WHEN("tokenizer has a statement with an invalid variable on the right hand side ") {
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
//            t->tokenize(invalidRhsVarName);
//
//            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
//            THEN ("it should throw an error") {
//                REQUIRE_THROWS_AS(ap->parse(util, t), std::invalid_argument);
//            }
//        }
//    }
//}
