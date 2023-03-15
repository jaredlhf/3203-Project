#include "SP/TNode.h"
#include "catch.hpp"

SCENARIO("Testing getChildren()") {
  GIVEN("A TNodes ") {
    AssignNode a1 = AssignNode(1, "x", "y+z", "test");
    AssignNode a2 = AssignNode(4, "a", "b+c", "test");
    PrintNode p1 = PrintNode(2, "w", "test");
    ReadNode r1 = ReadNode(10, "v", "test");

    std::vector<std::shared_ptr<StmtNode>> stmtLst;
    stmtLst.push_back(std::make_shared<AssignNode>(a2));
    StmtLstNode sln1 = StmtLstNode(stmtLst, "test");

    std::vector<std::shared_ptr<StmtNode>> stmtLst2;
    stmtLst2.push_back(std::make_shared<AssignNode>(a1));
    stmtLst2.push_back(std::make_shared<PrintNode>(p1));
    StmtLstNode sln2 = StmtLstNode(stmtLst2, "test");

    WhileNode w1 = WhileNode(
        5, "x>0", std::make_shared<StmtLstNode>(stmtLst, "test"), "test");

    IfNode if1 =
        IfNode(6, "y<4", std::make_shared<StmtLstNode>(stmtLst, "test"),
               std::make_shared<StmtLstNode>(stmtLst2, "test"), "test");

    WHEN("getChildren() on a StmtLstNode") {
      std::vector<std::shared_ptr<TNode>> children = sln2.getChildren();
      THEN("it should return correct children") {
        std::shared_ptr<AssignNode> c1 =
            std::dynamic_pointer_cast<AssignNode>(children[0]);
        REQUIRE(c1->getLine() == 1);
        REQUIRE(c1->getExpr() == "y+z");
        REQUIRE(c1->getVar() == "x");
        std::shared_ptr<PrintNode> c2 =
            std::dynamic_pointer_cast<PrintNode>(children[1]);
        REQUIRE(c2->getVar() == "w");
        REQUIRE(c2->getLine() == 2);
      }
    }

    WHEN("getChildren() on a AssignNode") {
      std::vector<std::shared_ptr<TNode>> children = a1.getChildren();
      THEN("it should return correct children") { REQUIRE(children.empty()); }
    }

    WHEN("getChildren() on a ReadNode") {
      std::vector<std::shared_ptr<TNode>> children = r1.getChildren();
      THEN("it should return empty children") { REQUIRE(children.empty()); }
    }

    WHEN("getChildren() on a PrintNode") {
      std::vector<std::shared_ptr<TNode>> children = p1.getChildren();
      THEN("it should return empty children") { REQUIRE(children.empty()); }
    }

    WHEN("getChildren() on a IfNode") {
      std::vector<std::shared_ptr<TNode>> children = if1.getChildren();
      THEN("it should return correct children") {
        std::shared_ptr<StmtLstNode> c1 =
            std::dynamic_pointer_cast<StmtLstNode>(children[0]);
        std::shared_ptr<AssignNode> a1 =
            std::dynamic_pointer_cast<AssignNode>(c1->getStatements()[0]);
        REQUIRE(a1->getLine() == 4);
        REQUIRE(a1->getVar() == "a");
        REQUIRE(a1->getExpr() == "b+c");
        std::shared_ptr<StmtLstNode> c2 =
            std::dynamic_pointer_cast<StmtLstNode>(children[1]);
        std::shared_ptr<AssignNode> a2 =
            std::dynamic_pointer_cast<AssignNode>(c2->getStatements()[0]);
        REQUIRE(a2->getLine() == 1);
        REQUIRE(a2->getExpr() == "y+z");
        REQUIRE(a2->getVar() == "x");
        std::shared_ptr<PrintNode> p1 =
            std::dynamic_pointer_cast<PrintNode>(c2->getStatements()[1]);
        REQUIRE(p1->getVar() == "w");
        REQUIRE(p1->getLine() == 2);
      }
    }

    WHEN("getChildren() on a WhileNode") {
      std::vector<std::shared_ptr<TNode>> children = w1.getChildren();
      THEN("it should return correct children") {
        std::shared_ptr<StmtLstNode> c1 =
            std::dynamic_pointer_cast<StmtLstNode>(children[0]);
        std::shared_ptr<AssignNode> a1 =
            std::dynamic_pointer_cast<AssignNode>(c1->getStatements()[0]);
        REQUIRE(a1->getLine() == 4);
        REQUIRE(a1->getVar() == "a");
        REQUIRE(a1->getExpr() == "b+c");
      }
    }
  }
}
