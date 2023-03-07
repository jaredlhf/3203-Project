#include "SP/StmtParser.h"
#include "catch.hpp"


SCENARIO("Testing createStmtParser") {
    GIVEN("A few string types") {
        std::string readStr = "read";
        std::string readStr2 = "x";

        std::string printStr = "print";
        std::string printStr2 = "y";

        std::string callStr = "call";
        std::string callStr2 = "z";

        std::string whileStr = "while";
        std::string whileStr2 = "(";

        std::string ifStr = "if";
        std::string ifStr2 = "(";

        std::string assignStr = "name";
        std::string assignStr2 = "=";

        std::string assignStrOverlap = "read";
        std::string assignStrOverlap2 = "=";

        std::string assignStrOverlap3 = "while";
        std::string assignStrOverlap4 = "=";

        std::string invalidAssignVarStr = "0dsad";
        std::string invalidAssignVarStr2 = "=";

        std::string invalidAssignTokenStr = "x";
        std::string invalidAssignTokenStr2 = "y";

        WHEN("valid string") {
            THEN("it should create a StmtParser of the correct type") {
                REQUIRE(typeid(*StmtParser::createStmtParser(readStr, readStr2)) == typeid(*std::make_shared<ReadParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(printStr, printStr2)) == typeid(*std::make_shared<PrintParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(callStr, callStr2)) == typeid(*std::make_shared<CallParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(whileStr, whileStr2)) == typeid(*std::make_shared<WhileParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(ifStr, ifStr2)) == typeid(*std::make_shared<IfParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(assignStr, assignStr2)) == typeid(*std::make_shared<AssignParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(assignStrOverlap, assignStrOverlap2)) == typeid(*std::make_shared<AssignParser>()));
                REQUIRE(typeid(*StmtParser::createStmtParser(assignStrOverlap3, assignStrOverlap4)) == typeid(*std::make_shared<AssignParser>()));
            }
        }

        WHEN("invalid string") {
            THEN("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::createStmtParser(invalidAssignVarStr, invalidAssignVarStr2), std::invalid_argument);
                REQUIRE_THROWS_AS(StmtParser::createStmtParser(invalidAssignTokenStr, invalidAssignTokenStr2), std::invalid_argument);
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

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = ap->parse(util, t, "test");
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "y+1");
            }
        }

        WHEN("tokenizer has long valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(longValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = ap->parse(util, t, "test");
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "read");
                REQUIRE(node->getExpr() == "y-1*f/s%f+231+(z)-(w+y)");
            }
        }

        WHEN("tokenizer has multiple valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(manyValidStatements);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = ap->parse(util, t, "test");
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "(z)-(w+y)");
            }
        }

        WHEN("tokenizer has statement with irregular spaces") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(irregularSpacesValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = ap->parse(util, t, "test");
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "1+y");
            }
        }

        WHEN("tokenizer has invalid statement on the left hand side") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidLhs);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ap->parse(util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement on the right hand side") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidRhs);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ap->parse(util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has a statement with an invalid variable on the right hand side ") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidRhsVarName);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ap->parse(util, t, "test"), std::invalid_argument);
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

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = pp->parse(util, t, "test");
            std::shared_ptr<PrintNode> node = dynamic_pointer_cast<PrintNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "y");
            }
        }

        WHEN("tokenizer has invalid statement with missing variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidMissingVarStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(pp->parse(util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement with invalid variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidVarStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(pp->parse(util, t, "test"), std::invalid_argument);
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

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = rp->parse(util, t, "test");
            std::shared_ptr<ReadNode> node = dynamic_pointer_cast<ReadNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "y");
            }
        }

        WHEN("tokenizer has invalid statement with missing variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidMissingVarStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(rp->parse(util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement with invalid variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidVarStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(rp->parse(util, t, "test"), std::invalid_argument);
            }
        }
    }
}

SCENARIO("Testing IfParser") {
    GIVEN("A few if statements") {
        std::string shortValidStatement = "if (x>0) then { x = x + 1; } else { y = y + 1; }";
        std::string longValidStatement =  "if ((x >0)&& (y < 5)) then { \n"
                                          "x = x + 1; \n"
                                          "} else { \n"
                                          "y = y + 1;\n"
                                          "if (x < 5) then { x = x * 10; } else { y = y *2; } \n"
                                          "}";

        //std::string missingThen = "if (x>0) { x = x + 1; } else { y = y + 1; }";
        std::string missingElse = "if (x>0) then { x = x + 1; } {y = y + 1;}";
        std::string missingIfLst = "if (x>0) then {} else { y = y + 1; }";
        std::string missingElseLst = "if (x>0) then {y = y + 1;} else {  }";
        std::string missingCondExpr = "if () then {y = y + 1;} else { y = y + 1; }";


        std::shared_ptr<IfParser> ip = std::make_shared<IfParser>();

        WHEN("tokenizer has short valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(shortValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = ip->parse(util, t, "test");
            std::shared_ptr<IfNode> node = dynamic_pointer_cast<IfNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getCondExpr() == "x>0");
                std::shared_ptr<AssignNode> a =dynamic_pointer_cast<AssignNode>(node->getIfLst()->getStatements()[0]);
                REQUIRE(a->getVar() == "x");
                REQUIRE(a->getExpr() == "x+1");
                std::shared_ptr<AssignNode> a2 =dynamic_pointer_cast<AssignNode>(node->getElseLst()->getStatements()[0]);
                REQUIRE(a2->getVar() == "y");
                REQUIRE(a2->getExpr() == "y+1");
            }
        }

        WHEN("tokenizer has long valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(longValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = ip->parse(util, t, "test");
            std::shared_ptr<IfNode> node = dynamic_pointer_cast<IfNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getCondExpr() == "(x>0)&&(y<5)");
                std::shared_ptr<AssignNode> a =dynamic_pointer_cast<AssignNode>(node->getIfLst()->getStatements()[0]);
                REQUIRE(a->getVar() == "x");
                REQUIRE(a->getExpr() == "x+1");
                std::shared_ptr<AssignNode> a2 =dynamic_pointer_cast<AssignNode>(node->getElseLst()->getStatements()[0]);
                REQUIRE(a2->getVar() == "y");
                REQUIRE(a2->getExpr() == "y+1");
                std::shared_ptr<IfNode> ifs = dynamic_pointer_cast<IfNode>(node->getElseLst()->getStatements()[1]);
                REQUIRE(ifs->getCondExpr() == "x<5");
                std::shared_ptr<AssignNode> a3 =dynamic_pointer_cast<AssignNode>(ifs->getIfLst()->getStatements()[0]);
                REQUIRE(a3->getVar() == "x");
                REQUIRE(a3->getExpr() == "x*10");
                std::shared_ptr<AssignNode> a4 =dynamic_pointer_cast<AssignNode>(ifs->getElseLst()->getStatements()[0]);
                REQUIRE(a4->getVar() == "y");
                REQUIRE(a4->getExpr() == "y*2");
            }
        }

        WHEN("tokenizer has invalid if statement with missing else") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingElse);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ip->parse(util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid if statement with missing ifLst") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingIfLst);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ip->parse(util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid if statement with missing elseLst") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingElseLst);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ip->parse(util, t, "test"), std::out_of_range);
            }
        }

        WHEN("tokenizer has invalid if statement with missing condExpr") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingCondExpr);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ip->parse(util, t, "test"), std::invalid_argument);
            }
        }


    }
}

SCENARIO("Testing WhileParser") {
    GIVEN("A few while statements") {
        std::string shortValidStatement = "while (x>0) { y = y + 1; }";
        std::string longValidStatement =  "while ((x >0)&& (y < 5)) { if ((x >0)&& (y < 5)) then { \n"
                                          "x = x + 1; \n"
                                          "} else { \n"
                                          "y = y + 1;\n"
                                          "if (x < 5) then { x = x * 10; } else { y = y *2; } \n"
                                          "}}";

        std::string missingStmtLst = "while (x>0) {  }";
        std::string missingCondExpr = "while () { y = y + 1; }";


        std::shared_ptr<WhileParser> wp = std::make_shared<WhileParser>();

        WHEN("tokenizer has short valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(shortValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = wp->parse(util, t, "test");
            std::shared_ptr<WhileNode> node = dynamic_pointer_cast<WhileNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getCondExpr() == "x>0");
                std::shared_ptr<AssignNode> a2 =dynamic_pointer_cast<AssignNode>(node->getStmtLst()->getStatements()[0]);
                REQUIRE(a2->getVar() == "y");
                REQUIRE(a2->getExpr() == "y+1");
            }
        }

        WHEN("tokenizer has long valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(longValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = wp->parse(util, t, "test");
            std::shared_ptr<WhileNode> node = dynamic_pointer_cast<WhileNode>(resultDTO->getNode());

            THEN ("it should generate correct AST") {
                std::shared_ptr<IfNode> ifs = dynamic_pointer_cast<IfNode>(node->getStmtLst()->getStatements()[0]);
                REQUIRE(node->getCondExpr() == "(x>0)&&(y<5)");
                REQUIRE(ifs->getCondExpr() == "(x>0)&&(y<5)");
                std::shared_ptr<AssignNode> a =dynamic_pointer_cast<AssignNode>(ifs->getIfLst()->getStatements()[0]);
                REQUIRE(a->getVar() == "x");
                REQUIRE(a->getExpr() == "x+1");
                std::shared_ptr<AssignNode> a2 =dynamic_pointer_cast<AssignNode>(ifs->getElseLst()->getStatements()[0]);
                REQUIRE(a2->getVar() == "y");
                REQUIRE(a2->getExpr() == "y+1");
                std::shared_ptr<IfNode> ifs2 = dynamic_pointer_cast<IfNode>(ifs->getElseLst()->getStatements()[1]);
                REQUIRE(ifs2->getCondExpr() == "x<5");
                std::shared_ptr<AssignNode> a3 =dynamic_pointer_cast<AssignNode>(ifs2->getIfLst()->getStatements()[0]);
                REQUIRE(a3->getVar() == "x");
                REQUIRE(a3->getExpr() == "x*10");
                std::shared_ptr<AssignNode> a4 =dynamic_pointer_cast<AssignNode>(ifs2->getElseLst()->getStatements()[0]);
                REQUIRE(a4->getVar() == "y");
                REQUIRE(a4->getExpr() == "y*2");
            }
        }

        WHEN("tokenizer has invalid if statement with missing stmtLst") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingStmtLst);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(wp->parse(util, t, "test"), std::out_of_range);
            }
        }


        WHEN("tokenizer has invalid if statement with missing condExpr") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingCondExpr);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(wp->parse(util, t, "test"), std::invalid_argument);
            }
        }
    }
}

SCENARIO("Testing StmtParser") {
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


        WHEN("tokenizer has short valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(shortValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "y+1");
            }
            THEN ("it should return the correct line number") {
                REQUIRE(resultDTO->getLine() == 1);
            }
        }

        WHEN("tokenizer has long valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(longValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "read");
                REQUIRE(node->getExpr() == "y-1*f/s%f+231+(z)-(w+y)");
            }
            THEN ("it should return the correct line number") {
                REQUIRE(resultDTO->getLine() == 1);
            }
        }

        WHEN("tokenizer has multiple valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(manyValidStatements);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "(z)-(w+y)");
            }
            THEN ("it should return the correct line number") {
                REQUIRE(resultDTO->getLine() == 1);
            }
        }

        WHEN("tokenizer has statement with irregular spaces") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(irregularSpacesValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<AssignNode> node = dynamic_pointer_cast<AssignNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "x");
                REQUIRE(node->getExpr() == "1+y");
            }
            THEN ("it should return the correct line number") {
                REQUIRE(resultDTO->getLine() == 1);
            }
        }

        WHEN("tokenizer has invalid statement on the left hand side") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidLhs);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement on the right hand side") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidRhs);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has a statement with an invalid variable on the right hand side ") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidRhsVarName);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }
    }

    GIVEN("A few print statements") {
        std::string validStatement = "print y;";

        std::string invalidMissingVarStatement = "print;";
        std::string invalidVarStatement = "print 0re;";

        WHEN("tokenizer has valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>();
            t->tokenize(validStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<PrintNode> node = dynamic_pointer_cast<PrintNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "y");
            }
            THEN ("it should return the correct line number") {
                REQUIRE(resultDTO->getLine() == 1);
            }
        }

        WHEN("tokenizer has invalid statement with missing variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>();
            t->tokenize(invalidMissingVarStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement with invalid variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>();
            t->tokenize(invalidVarStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }
    }

    GIVEN("A few read statements") {
        std::string validStatement = "read y;";

        std::string invalidMissingVarStatement = "read;";
        std::string invalidVarStatement = "read 0re;";

        WHEN("tokenizer has valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(validStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<ReadNode> node = dynamic_pointer_cast<ReadNode>(resultDTO->getNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getVar() == "y");
            }
            THEN ("it should return the correct line number") {
                REQUIRE(resultDTO->getLine() == 1);
            }
        }

        WHEN("tokenizer has invalid statement with missing variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidMissingVarStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid statement with invalid variable") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(invalidVarStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }
    }

    GIVEN("A few if statements") {
        std::string shortValidStatement = "if (x>0) then { x = x + 1; } else { y = y + 1; }";
        std::string longValidStatement =  "if ((x >0)&& (y < 5)) then { \n"
                                          "x = x + 1; \n"
                                          "} else { \n"
                                          "y = y + 1;\n"
                                          "if (x < 5) then { x = x * 10; } else { y = y *2; } \n"
                                          "}";

        std::string missingElse = "if (x>0) then { x = x + 1; } {y = y + 1;}";
        std::string missingIfLst = "if (x>0) then {} else { y = y + 1; }";
        std::string missingElseLst = "if (x>0) then {y = y + 1;} else {  }";
        std::string missingCondExpr = "if () then {y = y + 1;} else { y = y + 1; }";


        WHEN("tokenizer has short valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(shortValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<IfNode> node = dynamic_pointer_cast<IfNode>(resultDTO->getNode());
            std::shared_ptr<CFGIfNode> cfgNode = dynamic_pointer_cast<CFGIfNode>(resultDTO->getCFGNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getCondExpr() == "x>0");
                std::shared_ptr<AssignNode> a =dynamic_pointer_cast<AssignNode>(node->getIfLst()->getStatements()[0]);
                REQUIRE(a->getVar() == "x");
                REQUIRE(a->getExpr() == "x+1");
                std::shared_ptr<AssignNode> a2 =dynamic_pointer_cast<AssignNode>(node->getElseLst()->getStatements()[0]);
                REQUIRE(a2->getVar() == "y");
                REQUIRE(a2->getExpr() == "y+1");
            }
            THEN ("it should generate correct CFG") {
                REQUIRE(cfgNode->getLineNo().size() == 1);
                REQUIRE(cfgNode->getLineNo()[0] == 1);
                std::shared_ptr<CFGNode> thenCfgNode = cfgNode->getAllNextNodes()[0];
                std::shared_ptr<CFGNode> elseCfgNode = cfgNode->getAllNextNodes()[1];
                REQUIRE(thenCfgNode->getLineNo().size() == 1);
                REQUIRE(thenCfgNode->getLineNo()[0] == 2);
                REQUIRE(elseCfgNode->getLineNo().size() == 1);
                REQUIRE(elseCfgNode->getLineNo()[0] == 3);
            }
        }

        WHEN("tokenizer has long valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(longValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<IfNode> node = dynamic_pointer_cast<IfNode>(resultDTO->getNode());
            std::shared_ptr<CFGIfNode> cfgNode = dynamic_pointer_cast<CFGIfNode>(resultDTO->getCFGNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getCondExpr() == "(x>0)&&(y<5)");
                std::shared_ptr<AssignNode> a =dynamic_pointer_cast<AssignNode>(node->getIfLst()->getStatements()[0]);
                REQUIRE(a->getVar() == "x");
                REQUIRE(a->getExpr() == "x+1");
                std::shared_ptr<AssignNode> a2 =dynamic_pointer_cast<AssignNode>(node->getElseLst()->getStatements()[0]);
                REQUIRE(a2->getVar() == "y");
                REQUIRE(a2->getExpr() == "y+1");
                std::shared_ptr<IfNode> ifs = dynamic_pointer_cast<IfNode>(node->getElseLst()->getStatements()[1]);
                REQUIRE(ifs->getCondExpr() == "x<5");
                std::shared_ptr<AssignNode> a3 =dynamic_pointer_cast<AssignNode>(ifs->getIfLst()->getStatements()[0]);
                REQUIRE(a3->getVar() == "x");
                REQUIRE(a3->getExpr() == "x*10");
                std::shared_ptr<AssignNode> a4 =dynamic_pointer_cast<AssignNode>(ifs->getElseLst()->getStatements()[0]);
                REQUIRE(a4->getVar() == "y");
                REQUIRE(a4->getExpr() == "y*2");
            }

            THEN ("it should generate correct CFG") {
                REQUIRE(cfgNode->getLineNo().size() == 1);
                REQUIRE(cfgNode->getLineNo()[0] == 1);
                REQUIRE(cfgNode->getAllNextNodes().size() == 2);
                std::shared_ptr<CFGNode> thenCfgNode = cfgNode->getAllNextNodes()[0];
                std::shared_ptr<CFGNode> elseCfgNode = cfgNode->getAllNextNodes()[1];
                REQUIRE(thenCfgNode->getLineNo().size() == 1);
                REQUIRE(thenCfgNode->getLineNo()[0] == 2);
                REQUIRE(elseCfgNode->getLineNo().size() == 1);
                REQUIRE(elseCfgNode->getLineNo()[0] == 3);

                REQUIRE(elseCfgNode->getAllNextNodes().size() == 1);
                std::shared_ptr<CFGNode> if2CfgNode = elseCfgNode->getAllNextNodes()[0];
                REQUIRE(if2CfgNode->getLineNo().size() == 1);
                REQUIRE(if2CfgNode->getLineNo()[0] == 4);
                REQUIRE(if2CfgNode->getAllNextNodes().size() == 2);

                std::shared_ptr<CFGNode> then2CfgNode = if2CfgNode->getAllNextNodes()[0];
                std::shared_ptr<CFGNode> else2CfgNode = if2CfgNode->getAllNextNodes()[1];
                REQUIRE(then2CfgNode->getLineNo().size() == 1);
                REQUIRE(then2CfgNode->getLineNo()[0] == 5);
                REQUIRE(else2CfgNode->getLineNo().size() == 1);
                REQUIRE(else2CfgNode->getLineNo()[0] == 6);
            }
        }

        WHEN("tokenizer has invalid if statement with missing else") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingElse);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid if statement with missing ifLst") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingIfLst);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid if statement with missing elseLst") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingElseLst);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::out_of_range);
            }
        }

        WHEN("tokenizer has invalid if statement with missing condExpr") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingCondExpr);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }
    }

    GIVEN("A few while statements") {
        std::string shortValidStatement = "while (x>0) { y = y + 1; }";
        std::string longValidStatement =  "while ((x >0)&& (y < 5)) { if ((x >0)&& (y < 5)) then { \n"
                                          "x = x + 1; \n"
                                          "} else { \n"
                                          "y = y + 1;\n"
                                          "if (x < 5) then { x = x * 10; } else { y = y *2; } \n"
                                          "}}";

        std::string missingStmtLst = "while (x>0) {  }";
        std::string missingCondExpr = "while () { y = y + 1; }";


        WHEN("tokenizer has short valid statement") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(shortValidStatement);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
            std::shared_ptr<WhileNode> node = dynamic_pointer_cast<WhileNode>(resultDTO->getNode());
            std::shared_ptr<CFGWhileNode> cfgNode = dynamic_pointer_cast<CFGWhileNode>(resultDTO->getCFGNode());
            THEN ("it should generate correct AST") {
                REQUIRE(node->getCondExpr() == "x>0");
                std::shared_ptr<AssignNode> a2 =dynamic_pointer_cast<AssignNode>(node->getStmtLst()->getStatements()[0]);
                REQUIRE(a2->getVar() == "y");
                REQUIRE(a2->getExpr() == "y+1");
            }
            THEN ("it should generate correct CFG") {
                REQUIRE(cfgNode->getLineNo().size() == 1);
                REQUIRE(cfgNode->getLineNo()[0] == 1);
                std::shared_ptr<CFGNode> loopCfgNode = cfgNode->getAllNextNodes()[1];
                REQUIRE(loopCfgNode->getLineNo().size() == 1);
                REQUIRE(loopCfgNode->getLineNo()[0] == 2);
            }
        }

//        WHEN("tokenizer has long valid statement") {
//            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
//            t->tokenize(longValidStatement);
//
//            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
//            std::shared_ptr<ParserDTO> resultDTO = StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test");
//            std::shared_ptr<WhileNode> node = dynamic_pointer_cast<WhileNode>(resultDTO->getNode());
//            std::shared_ptr<CFGWhileNode> cfgNode = dynamic_pointer_cast<CFGWhileNode>(resultDTO->getCFGNode());
//
//            THEN ("it should generate correct AST") {
//                std::shared_ptr<IfNode> ifs = dynamic_pointer_cast<IfNode>(node->getStmtLst()->getStatements()[0]);
//                REQUIRE(node->getCondExpr() == "(x>0)&&(y<5)");
//                REQUIRE(ifs->getCondExpr() == "(x>0)&&(y<5)");
//                std::shared_ptr<AssignNode> a =dynamic_pointer_cast<AssignNode>(ifs->getIfLst()->getStatements()[0]);
//                REQUIRE(a->getVar() == "x");
//                REQUIRE(a->getExpr() == "x+1");
//                std::shared_ptr<AssignNode> a2 =dynamic_pointer_cast<AssignNode>(ifs->getElseLst()->getStatements()[0]);
//                REQUIRE(a2->getVar() == "y");
//                REQUIRE(a2->getExpr() == "y+1");
//                std::shared_ptr<IfNode> ifs2 = dynamic_pointer_cast<IfNode>(ifs->getElseLst()->getStatements()[1]);
//                REQUIRE(ifs2->getCondExpr() == "x<5");
//                std::shared_ptr<AssignNode> a3 =dynamic_pointer_cast<AssignNode>(ifs2->getIfLst()->getStatements()[0]);
//                REQUIRE(a3->getVar() == "x");
//                REQUIRE(a3->getExpr() == "x*10");
//                std::shared_ptr<AssignNode> a4 =dynamic_pointer_cast<AssignNode>(ifs2->getElseLst()->getStatements()[0]);
//                REQUIRE(a4->getVar() == "y");
//                REQUIRE(a4->getExpr() == "y*2");
//            }
//            THEN ("it should generate correct CFG") {
//                REQUIRE(cfgNode->getLineNo().size() == 1);
//                REQUIRE(cfgNode->getLineNo()[0] == 1);
//                std::shared_ptr<CFGNode> nextCfgNode = cfgNode->getAllNextNodes()[0];
//                REQUIRE(nextCfgNode->getLineNo().size() == 0);

//                std::shared_ptr<CFGNode> loopCfgNode = cfgNode->getAllNextNodes()[1];
//                REQUIRE(loopCfgNode->getLineNo().size() == 1);
//                REQUIRE(loopCfgNode->getLineNo()[0] == 2);
//                REQUIRE(loopCfgNode->getAllNextNodes().size() == 2);
//                std::shared_ptr<CFGNode> thenCfgNode = loopCfgNode->getAllNextNodes()[0];
//                std::shared_ptr<CFGNode> elseCfgNode = loopCfgNode->getAllNextNodes()[1];
//                REQUIRE(thenCfgNode->getLineNo().size() == 1);
//                REQUIRE(thenCfgNode->getLineNo()[0] == 3);
//                REQUIRE(thenCfgNode->getAllNextNodes().size() == 1);
//                std::shared_ptr<CFGNode> thenNextCfgNode = thenCfgNode->getAllNextNodes()[0];
//                REQUIRE(thenNextCfgNode->getLineNo().size() == 1);
//                REQUIRE(thenNextCfgNode->getLineNo()[0] == 1);
//                REQUIRE(elseCfgNode->getLineNo().size() == 1);
//                REQUIRE(elseCfgNode->getLineNo()[0] == 4);
//
//                std::shared_ptr<CFGNode> if2CfgNode = elseCfgNode->getAllNextNodes()[0];
//                REQUIRE(if2CfgNode->getLineNo().size() == 1);
//                REQUIRE(if2CfgNode->getLineNo()[0] == 5);
//                REQUIRE(if2CfgNode->getAllNextNodes().size() == 2);
//                std::shared_ptr<CFGNode> then2CfgNode = if2CfgNode->getAllNextNodes()[0];
//                std::shared_ptr<CFGNode> else2CfgNode = if2CfgNode->getAllNextNodes()[1];
//                REQUIRE(then2CfgNode->getLineNo().size() == 1);
//                REQUIRE(then2CfgNode->getLineNo()[0] == 6);
//                std::shared_ptr<CFGNode> thenNext2CfgNode = then2CfgNode->getAllNextNodes()[0];
//                REQUIRE(thenNext2CfgNode->getLineNo().size() == 1);
//                REQUIRE(thenNext2CfgNode->getLineNo()[0] == 1);
//                REQUIRE(else2CfgNode->getLineNo().size() == 1);
//                REQUIRE(else2CfgNode->getLineNo()[0] == 7);
//                std::shared_ptr<CFGNode> elseNext2CfgNode = else2CfgNode->getAllNextNodes()[0];
//                REQUIRE(elseNext2CfgNode->getLineNo().size() == 1);
//                REQUIRE(elseNext2CfgNode->getLineNo()[0] == 1);
//            }
//        }

        WHEN("tokenizer has invalid if statement with missing stmtLst") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingStmtLst);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::out_of_range);
            }
        }


        WHEN("tokenizer has invalid if statement with missing condExpr") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingCondExpr);

            std::shared_ptr<SPParserUtils> util = std::make_shared<SPParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(StmtParser::parseStmt(t->peek(), t->peekTwice(), util, t, "test"), std::invalid_argument);
            }
        }
    }

}


