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

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<IfNode> node = dynamic_pointer_cast<IfNode>(ip->parse(util, t));
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

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<IfNode> node = dynamic_pointer_cast<IfNode>(ip->parse(util, t));
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

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ip->parse(util, t), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid if statement with missing ifLst") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingIfLst);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ip->parse(util, t), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid if statement with missing elseLst") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingElseLst);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ip->parse(util, t), std::invalid_argument);
            }
        }

        WHEN("tokenizer has invalid if statement with missing condExpr") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingCondExpr);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(ip->parse(util, t), std::invalid_argument);
            }
        }


    }
}

SCENARIO("Testing WhileParser") {
    GIVEN("A few if statements") {
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

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<WhileNode> node = dynamic_pointer_cast<WhileNode>(wp->parse(util, t));
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

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            std::shared_ptr<WhileNode> node = dynamic_pointer_cast<WhileNode>(wp->parse(util, t));

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

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(wp->parse(util, t), std::invalid_argument);
            }
        }


        WHEN("tokenizer has invalid if statement with missing condExpr") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>() ;
            t->tokenize(missingCondExpr);

            std::shared_ptr<ParserUtils> util = std::make_shared<ParserUtils>(t);
            THEN ("it should throw an error") {
                REQUIRE_THROWS_AS(wp->parse(util, t), std::invalid_argument);
            }
        }
    }
}
