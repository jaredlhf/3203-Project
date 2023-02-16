#include "SP/DesignExtractor.h"
#include "SP/TNode.h"
#include "catch.hpp"
#include <regex>

using namespace std;

TEST_CASE("ModifiesAssignTest") {
    ModifiesExtractor m;
    AssignNode a = AssignNode(1,"v","x");
    shared_ptr<AssignNode> sp = make_shared<AssignNode>(a);
    m.visit(sp);
}

TEST_CASE("ModifiesReadTest") {
    ModifiesExtractor m;
    ReadNode r = ReadNode(1, "bumblebee");
    shared_ptr<ReadNode> sp = make_shared<ReadNode>(r);
    m.visit(sp);
}

TEST_CASE("UsesAssignTest") {
    UsesExtractor u;
    AssignNode a = AssignNode(1,"v","x + y + z + 1");
    shared_ptr<AssignNode> sp = make_shared<AssignNode>(a);
    u.visit(sp);
}

TEST_CASE("UsesPrintTest") {
    UsesExtractor u;
    PrintNode p = PrintNode(2,"m");
    shared_ptr<PrintNode> sp = make_shared<PrintNode>(p);
    u.visit(sp);
}

TEST_CASE("FollowsTest") {
    FollowsExtractor f;
    vector<std::shared_ptr<StmtNode>> stmts;
    AssignNode a = AssignNode(1,"v","x + y + z + 1");
    shared_ptr<AssignNode> sp1 = make_shared<AssignNode>(a);
    PrintNode p = PrintNode(2,"m");
    shared_ptr<PrintNode> sp2 = make_shared<PrintNode>(p);
    stmts.push_back(sp1);
    stmts.push_back(sp2);
    StmtLstNode sl = StmtLstNode(stmts);
    shared_ptr<StmtLstNode> sp = make_shared<StmtLstNode>(sl);
    f.visit(sp);
}



