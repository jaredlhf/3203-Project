#include "SP/TNode.h"
#include "catch.hpp"


TEST_CASE("accept()") {
    TNode n = TNode();
    n.accept();
}

TEST_CASE("Create AssignNode") {
    string var = "x";
    string expr = "y + z";
    int lineNo = 1;
    AssignNode a = AssignNode(lineNo, var, expr);

}
