#include "SP/Parser.h"
#include "catch.hpp"

SCENARIO("Testing ParseProgram") {
    GIVEN("A simple program") {
        std::string program = "procedure computeCentroid {\n"
                                          "      while ((x != 0) && (y != 6)) {\n"
                                          "          count1 = count2 + 8;\n"
                                          "          if (count3 == 0) then {\n"
                                          "               flag = 1;\n"
                                          "          } else {\n"
                                          "               cenX = cenX1 / count;\n"
                                          "               if (x > 2) then { "
                                          "                   w = e + 3; "
                                          "               } else { "
                                          "                   r = t *5; "
                                          "               } \n"
                                          "          }\n"
                                          "      }\n"
                                          "      normSq = cenX * cenX + cenY * cenY;\n"
                                          "}";




        WHEN("tokenizer has simple program") {
            std::shared_ptr<Tokenizer> t = std::make_shared<Tokenizer>();
            t->tokenize(program);
            std::shared_ptr<Parser> p = std::make_shared<Parser>(t);

            THEN ("it should generate correct AST") {
                std::shared_ptr<ProcedureNode> pn = dynamic_pointer_cast<ProcedureNode>(p->parseProgram()->getNode());
                std::shared_ptr<WhileNode> wn = dynamic_pointer_cast<WhileNode>(pn->getStmtLst()->getStatements()[0]);
                REQUIRE(wn->getCondExpr() == "(x!=0)&&(y!=6)");
                REQUIRE(wn->getLine() == 1);
                std::shared_ptr<AssignNode> a = dynamic_pointer_cast<AssignNode>(wn->getStmtLst()->getStatements()[0]);
                REQUIRE(a->getVar() == "count1");
                REQUIRE(a->getExpr() == "count2+8");
                REQUIRE(a->getLine() == 2);
                std::shared_ptr<IfNode> ifs = dynamic_pointer_cast<IfNode>(wn->getStmtLst()->getStatements()[1]);
                REQUIRE(ifs->getCondExpr() == "count3==0");
                REQUIRE(ifs->getLine() == 3);
                std::shared_ptr<AssignNode> a2 = dynamic_pointer_cast<AssignNode>(ifs->getIfLst()->getStatements()[0]);
                REQUIRE(a2->getVar() == "flag");
                REQUIRE(a2->getExpr() == "1");
                REQUIRE(a2->getLine() == 4);
                std::shared_ptr<AssignNode> a3 = dynamic_pointer_cast<AssignNode>(ifs->getElseLst()->getStatements()[0]);
                REQUIRE(a3->getVar() == "cenX");
                REQUIRE(a3->getExpr() == "cenX1/count");
                REQUIRE(a3->getLine() == 5);
                std::shared_ptr<IfNode> ifs2 = dynamic_pointer_cast<IfNode>(ifs->getElseLst()->getStatements()[1]);
                REQUIRE(ifs2->getCondExpr() == "x>2");
                REQUIRE(ifs2->getLine() == 6);
                std::shared_ptr<AssignNode> a4 = dynamic_pointer_cast<AssignNode>(ifs2->getIfLst()->getStatements()[0]);
                REQUIRE(a4->getVar() == "w");
                REQUIRE(a4->getExpr() == "e+3");
                REQUIRE(a4->getLine() == 7);
                std::shared_ptr<AssignNode> a5 = dynamic_pointer_cast<AssignNode>(ifs2->getElseLst()->getStatements()[0]);
                REQUIRE(a5->getVar() == "r");
                REQUIRE(a5->getExpr() == "t*5");
                REQUIRE(a5->getLine() == 8);
                std::shared_ptr<AssignNode> a6 = dynamic_pointer_cast<AssignNode>(pn->getStmtLst()->getStatements()[1]);
                REQUIRE(a6->getVar() == "normSq");
                REQUIRE(a6->getExpr() == "cenX*cenX+cenY*cenY");
                REQUIRE(a6->getLine() == 9);
            }
        }
    }
}
