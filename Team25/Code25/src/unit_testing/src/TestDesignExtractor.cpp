#include "SP/DesignExtractor.h"
#include "SP/TNode.h"
#include "catch.hpp"
#include <regex>
#include "SP/SPConstants.h"

using namespace std;

//TEST_CASE("ModifiesAssignTest") {
//    ModifiesExtractor m;
//    AssignNode a = AssignNode(1,"v","x");
//    shared_ptr<AssignNode> sp = make_shared<AssignNode>(a);
//    m.visit(sp);
//}
//
//TEST_CASE("ModifiesReadTest") {
//    ModifiesExtractor m;
//    ReadNode r = ReadNode(1, "bumblebee");
//    shared_ptr<ReadNode> sp = make_shared<ReadNode>(r);
//    m.visit(sp);
//}

VariableStore vs;
ConstantStore cs;
FollowsStore fs;
ProcedureStore ps;
StatementStore ss;
PatternStore patts;
FollowsStarStore fstars;
ModifiesProcStore mprocs;
ModifiesStore ms;
ParentStarStore pStars;
ParentStore parents;
UsesStore uses;

std::shared_ptr vsPointer = std::make_shared<VariableStore>(vs);
std::shared_ptr csPointer = std::make_shared<ConstantStore>(cs);
std::shared_ptr fsPointer = std::make_shared<FollowsStore>(fs);
std::shared_ptr psPointer = std::make_shared<ProcedureStore>(ps);
std::shared_ptr ssPointer = std::make_shared<StatementStore>(ss);
std::shared_ptr pattsPointer = std::make_shared<PatternStore>(patts);
std::shared_ptr<FollowsStarStore> fstarsPointer = std::make_shared<FollowsStarStore>(fstars);
std::shared_ptr<ModifiesProcStore> mprocsPointer = std::make_shared<ModifiesProcStore>(mprocs);
std::shared_ptr<ModifiesStore> msPointer = std::make_shared<ModifiesStore>(ms);
std::shared_ptr<ParentStarStore> pStarsPointer = std::make_shared<ParentStarStore>(pStars);
std::shared_ptr<ParentStore> parentsPointer = std::make_shared<ParentStore>(parents);
std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);

PkbPopulator pkbPopulator(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, usesPointer);
std::shared_ptr<PkbPopulator> pkbPop = std::make_shared<PkbPopulator>(pkbPopulator);

TEST_CASE("ModifiesIfTest") {
    ModifiesExtractor m(pkbPop);
    //First If stmtLst
    vector<std::shared_ptr<StmtNode>> ifStmts;
    AssignNode a1 = AssignNode(3,"k","x + y + z + 1");
    shared_ptr<AssignNode> ifSp1 = make_shared<AssignNode>(a1);
    PrintNode p1 = PrintNode(4,"l");
    shared_ptr<PrintNode> ifSp2 = make_shared<PrintNode>(p1);
    ifStmts.push_back(ifSp1);
    ifStmts.push_back(ifSp2);
    StmtLstNode ifSl = StmtLstNode(ifStmts);
    shared_ptr<StmtLstNode> ifSp = make_shared<StmtLstNode>(ifSl);

    //First Else stmtLst
    vector<std::shared_ptr<StmtNode>> elseStmts;
    AssignNode a2 = AssignNode(15,"i","a + b + c + 1");
    shared_ptr<AssignNode> elseSp1 = make_shared<AssignNode>(a2);
    PrintNode p2 = PrintNode(16,"j");
    shared_ptr<PrintNode> elseSp2 = make_shared<PrintNode>(p2);
    elseStmts.push_back(elseSp1);
    elseStmts.push_back(elseSp2);

    //nested second if stmtlst
    vector<std::shared_ptr<StmtNode>> ifStmts1;
    AssignNode a11 = AssignNode(6,"g","x + y + z + 1");
    shared_ptr<AssignNode> ifSp11= make_shared<AssignNode>(a11);
    PrintNode p11 = PrintNode(7,"h");
    shared_ptr<PrintNode> ifSp21 = make_shared<PrintNode>(p11);
    ifStmts1.push_back(ifSp11);
    ifStmts1.push_back(ifSp21);

    // nested third if stmtlst
    vector<std::shared_ptr<StmtNode>> ifStmts2;
    AssignNode a12 = AssignNode(9,"e","x + y + z + 1");
    shared_ptr<AssignNode> ifSp12= make_shared<AssignNode>(a12);
    PrintNode p12 = PrintNode(10,"f");
    shared_ptr<PrintNode> ifSp22 = make_shared<PrintNode>(p12);
    ifStmts2.push_back(ifSp12);
    ifStmts2.push_back(ifSp22);
    StmtLstNode ifSl2 = StmtLstNode(ifStmts2);
    shared_ptr<StmtLstNode> ifSp32 = make_shared<StmtLstNode>(ifSl2);

    // nested third else stmtlst
    vector<std::shared_ptr<StmtNode>> elseStmts2;
    AssignNode a22 = AssignNode(11,"c","a + b + c + 1");
    shared_ptr<AssignNode> elseSp12 = make_shared<AssignNode>(a22);
    PrintNode p22 = PrintNode(12,"d");
    shared_ptr<PrintNode> elseSp22 = make_shared<PrintNode>(p22);
    elseStmts2.push_back(elseSp12);
    elseStmts2.push_back(elseSp22);
    StmtLstNode elseSl2 = StmtLstNode(elseStmts2);
    shared_ptr<StmtLstNode> elseSp32 = make_shared<StmtLstNode>(elseSl2);

    //third if cond expr
    shared_ptr<IfNode> i3 = make_shared<IfNode>(IfNode(8,"x>3",ifSp32,elseSp32));

    ifStmts1.push_back(i3);
    StmtLstNode ifSl1 = StmtLstNode(ifStmts1);
    shared_ptr<StmtLstNode> ifSp31 = make_shared<StmtLstNode>(ifSl1);

    //third else stmtLst
    vector<std::shared_ptr<StmtNode>> elseStmts1;
    AssignNode a21 = AssignNode(13,"a","a + b + c + 1");
    shared_ptr<AssignNode> elseSp11 = make_shared<AssignNode>(a21);
    ReadNode p21 = ReadNode(14,"b");
    shared_ptr<ReadNode> elseSp21 = make_shared<ReadNode>(p21);
    elseStmts1.push_back(elseSp11);
    elseStmts1.push_back(elseSp21);
    StmtLstNode elseSl1 = StmtLstNode(elseStmts1);
    shared_ptr<StmtLstNode> elseSp31 = make_shared<StmtLstNode>(elseSl1);

    shared_ptr<IfNode> i2 = make_shared<IfNode>(IfNode(5,"x>3",ifSp31,elseSp31));

    elseStmts.push_back(i2);
    StmtLstNode elseSl = StmtLstNode(elseStmts);
    shared_ptr<StmtLstNode> elseSp = make_shared<StmtLstNode>(elseSl);

    //First If cond expr
    shared_ptr<IfNode> i = make_shared<IfNode>(IfNode(2,"x>3",ifSp,elseSp));

    m.visit(i, SPConstants::INVALID_LINE_NO);
}
//
//TEST_CASE("UsesAssignTest") {
//    UsesExtractor u;
//    AssignNode a = AssignNode(1,"v","x + y + z + 1");
//    shared_ptr<AssignNode> sp = make_shared<AssignNode>(a);
//    u.visit(sp);
//}
//
//TEST_CASE("UsesPrintTest") {
//    UsesExtractor u;
//    PrintNode p = PrintNode(2,"m");
//    shared_ptr<PrintNode> sp = make_shared<PrintNode>(p);
//    u.visit(sp);
//}

TEST_CASE("FollowsTest") {
    FollowsExtractor f(pkbPop);
    vector<std::shared_ptr<StmtNode>> stmts;
    AssignNode a = AssignNode(1,"v","x + y + z + 1");
    shared_ptr<AssignNode> sp1 = make_shared<AssignNode>(a);
    PrintNode p = PrintNode(2,"m");
    shared_ptr<PrintNode> sp2 = make_shared<PrintNode>(p);
    stmts.push_back(sp1);
    stmts.push_back(sp2);
    StmtLstNode sl = StmtLstNode(stmts);
    shared_ptr<StmtLstNode> sp = make_shared<StmtLstNode>(sl);
    f.visit(sp, SPConstants::INVALID_LINE_NO);
}

TEST_CASE("FollowsWithWhileTest") {
    FollowsExtractor f(pkbPop);
    vector<std::shared_ptr<StmtNode>> stmts;

    AssignNode a = AssignNode(1,"v","x + y + z + 1");
    shared_ptr<AssignNode> sp1 = make_shared<AssignNode>(a);
    PrintNode p = PrintNode(2,"m");
    shared_ptr<PrintNode> sp2 = make_shared<PrintNode>(p);

    vector<std::shared_ptr<StmtNode>> ifStmts;
    AssignNode a1 = AssignNode(3,"v","x + y + z + 1");
    shared_ptr<AssignNode> ifSp1 = make_shared<AssignNode>(a1);
    PrintNode p1 = PrintNode(4,"m");
    shared_ptr<PrintNode> ifSp2 = make_shared<PrintNode>(p1);
    ifStmts.push_back(ifSp1);
    ifStmts.push_back(ifSp2);
    StmtLstNode ifSl = StmtLstNode(ifStmts);
    shared_ptr<StmtLstNode> ifSp = make_shared<StmtLstNode>(ifSl);

    vector<std::shared_ptr<StmtNode>> elseStmts;
    AssignNode a2 = AssignNode(5,"v","x + y + z + 1");
    shared_ptr<AssignNode> elseSp1 = make_shared<AssignNode>(a2);
    PrintNode p2 = PrintNode(6,"m");
    shared_ptr<PrintNode> elseSp2 = make_shared<PrintNode>(p2);
    elseStmts.push_back(elseSp1);
    elseStmts.push_back(elseSp2);
    StmtLstNode elseSl = StmtLstNode(elseStmts);
    shared_ptr<StmtLstNode> elseSp = make_shared<StmtLstNode>(elseSl);
    shared_ptr<IfNode> i = make_shared<IfNode>(IfNode(3,"x>3",ifSp,elseSp));

    AssignNode a3 = AssignNode(7,"v","x + y + z + 1");
    shared_ptr<AssignNode> sp3 = make_shared<AssignNode>(a3);
    PrintNode p3 = PrintNode(8,"m");
    shared_ptr<PrintNode> sp4 = make_shared<PrintNode>(p3);

    stmts.push_back(sp1);
    stmts.push_back(sp2);
    stmts.push_back(i);
    stmts.push_back(sp3);
    stmts.push_back(sp4);
    StmtLstNode sl = StmtLstNode(stmts);
    shared_ptr<StmtLstNode> sp = make_shared<StmtLstNode>(sl);

    f.visit(sp, SPConstants::INVALID_LINE_NO);
}

TEST_CASE("FollowsStarTest") {
    FollowsStarExtractor f(pkbPop);
    vector<std::shared_ptr<StmtNode>> stmts;

    AssignNode a = AssignNode(1,"v","x + y + z + 1");
    shared_ptr<AssignNode> sp1 = make_shared<AssignNode>(a);
    PrintNode p = PrintNode(2,"m");
    shared_ptr<PrintNode> sp2 = make_shared<PrintNode>(p);

    vector<std::shared_ptr<StmtNode>> ifStmts;
    AssignNode a1 = AssignNode(3,"v","x + y + z + 1");
    shared_ptr<AssignNode> ifSp1 = make_shared<AssignNode>(a1);
    PrintNode p1 = PrintNode(4,"m");
    shared_ptr<PrintNode> ifSp2 = make_shared<PrintNode>(p1);
    ifStmts.push_back(ifSp1);
    ifStmts.push_back(ifSp2);
    StmtLstNode ifSl = StmtLstNode(ifStmts);
    shared_ptr<StmtLstNode> ifSp = make_shared<StmtLstNode>(ifSl);

    vector<std::shared_ptr<StmtNode>> elseStmts;
    AssignNode a2 = AssignNode(5,"v","x + y + z + 1");
    shared_ptr<AssignNode> elseSp1 = make_shared<AssignNode>(a2);
    PrintNode p2 = PrintNode(6,"m");
    shared_ptr<PrintNode> elseSp2 = make_shared<PrintNode>(p2);
    elseStmts.push_back(elseSp1);
    elseStmts.push_back(elseSp2);
    StmtLstNode elseSl = StmtLstNode(elseStmts);
    shared_ptr<StmtLstNode> elseSp = make_shared<StmtLstNode>(elseSl);
    shared_ptr<IfNode> i = make_shared<IfNode>(IfNode(3,"x>3",ifSp,elseSp));

    AssignNode a3 = AssignNode(7,"v","x + y + z + 1");
    shared_ptr<AssignNode> sp3 = make_shared<AssignNode>(a3);
    PrintNode p3 = PrintNode(8,"m");
    shared_ptr<PrintNode> sp4 = make_shared<PrintNode>(p3);

    stmts.push_back(sp1);
    stmts.push_back(sp2);
    stmts.push_back(i);
    stmts.push_back(sp3);
    stmts.push_back(sp4);
    StmtLstNode sl = StmtLstNode(stmts);
    shared_ptr<StmtLstNode> sp = make_shared<StmtLstNode>(sl);

    f.visit(sp, SPConstants::INVALID_LINE_NO);
}

TEST_CASE("ParentsTest") {
    ParentsExtractor p(pkbPop);

    vector<std::shared_ptr<StmtNode>> ifStmts;
    AssignNode a1 = AssignNode(3,"v","x + y + z + 1");
    shared_ptr<AssignNode> ifSp1 = make_shared<AssignNode>(a1);
    PrintNode p1 = PrintNode(4,"m");
    shared_ptr<PrintNode> ifSp2 = make_shared<PrintNode>(p1);
    ifStmts.push_back(ifSp1);
    ifStmts.push_back(ifSp2);
    StmtLstNode ifSl = StmtLstNode(ifStmts);
    shared_ptr<StmtLstNode> ifSp = make_shared<StmtLstNode>(ifSl);

    vector<std::shared_ptr<StmtNode>> elseStmts;
    AssignNode a2 = AssignNode(5,"v","a + b + c + 1");
    shared_ptr<AssignNode> elseSp1 = make_shared<AssignNode>(a2);
    PrintNode p2 = PrintNode(6,"n");
    shared_ptr<PrintNode> elseSp2 = make_shared<PrintNode>(p2);
    elseStmts.push_back(elseSp1);
    elseStmts.push_back(elseSp2);
    StmtLstNode elseSl = StmtLstNode(elseStmts);
    shared_ptr<StmtLstNode> elseSp = make_shared<StmtLstNode>(elseSl);

    shared_ptr<IfNode> i = make_shared<IfNode>(IfNode(2,"x>3",ifSp,elseSp));

    p.visit(i, SPConstants::INVALID_LINE_NO);
}

TEST_CASE("ParentsStarTest") {
    ParentsStarExtractor p(pkbPop);

    //First If stmtLst
    vector<std::shared_ptr<StmtNode>> ifStmts;
    AssignNode a1 = AssignNode(3,"v","x + y + z + 1");
    shared_ptr<AssignNode> ifSp1 = make_shared<AssignNode>(a1);
    PrintNode p1 = PrintNode(4,"m");
    shared_ptr<PrintNode> ifSp2 = make_shared<PrintNode>(p1);
    ifStmts.push_back(ifSp1);
    ifStmts.push_back(ifSp2);
    StmtLstNode ifSl = StmtLstNode(ifStmts);
    shared_ptr<StmtLstNode> ifSp = make_shared<StmtLstNode>(ifSl);

    //First Else stmtLst
    vector<std::shared_ptr<StmtNode>> elseStmts;
    AssignNode a2 = AssignNode(15,"v","a + b + c + 1");
    shared_ptr<AssignNode> elseSp1 = make_shared<AssignNode>(a2);
    PrintNode p2 = PrintNode(16,"n");
    shared_ptr<PrintNode> elseSp2 = make_shared<PrintNode>(p2);
    elseStmts.push_back(elseSp1);
    elseStmts.push_back(elseSp2);

    //nested second if stmtlst
    vector<std::shared_ptr<StmtNode>> ifStmts1;
    AssignNode a11 = AssignNode(6,"v","x + y + z + 1");
    shared_ptr<AssignNode> ifSp11= make_shared<AssignNode>(a11);
    PrintNode p11 = PrintNode(7,"m");
    shared_ptr<PrintNode> ifSp21 = make_shared<PrintNode>(p11);
    ifStmts1.push_back(ifSp11);
    ifStmts1.push_back(ifSp21);

    // nested third if stmtlst
    vector<std::shared_ptr<StmtNode>> ifStmts2;
    AssignNode a12 = AssignNode(9,"v","x + y + z + 1");
    shared_ptr<AssignNode> ifSp12= make_shared<AssignNode>(a12);
    PrintNode p12 = PrintNode(10,"m");
    shared_ptr<PrintNode> ifSp22 = make_shared<PrintNode>(p12);
    ifStmts2.push_back(ifSp12);
    ifStmts2.push_back(ifSp22);
    StmtLstNode ifSl2 = StmtLstNode(ifStmts2);
    shared_ptr<StmtLstNode> ifSp32 = make_shared<StmtLstNode>(ifSl2);

    // nested third else stmtlst
    vector<std::shared_ptr<StmtNode>> elseStmts2;
    AssignNode a22 = AssignNode(11,"v","a + b + c + 1");
    shared_ptr<AssignNode> elseSp12 = make_shared<AssignNode>(a22);
    PrintNode p22 = PrintNode(12,"n");
    shared_ptr<PrintNode> elseSp22 = make_shared<PrintNode>(p22);
    elseStmts2.push_back(elseSp12);
    elseStmts2.push_back(elseSp22);
    StmtLstNode elseSl2 = StmtLstNode(elseStmts2);
    shared_ptr<StmtLstNode> elseSp32 = make_shared<StmtLstNode>(elseSl2);

    //third if cond expr
    shared_ptr<IfNode> i3 = make_shared<IfNode>(IfNode(8,"x>3",ifSp32,elseSp32));

    ifStmts1.push_back(i3);
    StmtLstNode ifSl1 = StmtLstNode(ifStmts1);
    shared_ptr<StmtLstNode> ifSp31 = make_shared<StmtLstNode>(ifSl1);

    //third else stmtLst
    vector<std::shared_ptr<StmtNode>> elseStmts1;
    AssignNode a21 = AssignNode(13,"v","a + b + c + 1");
    shared_ptr<AssignNode> elseSp11 = make_shared<AssignNode>(a21);
    PrintNode p21 = PrintNode(14,"n");
    shared_ptr<PrintNode> elseSp21 = make_shared<PrintNode>(p21);
    elseStmts1.push_back(elseSp11);
    elseStmts1.push_back(elseSp21);
    StmtLstNode elseSl1 = StmtLstNode(elseStmts1);
    shared_ptr<StmtLstNode> elseSp31 = make_shared<StmtLstNode>(elseSl1);

    shared_ptr<IfNode> i2 = make_shared<IfNode>(IfNode(5,"x>3",ifSp31,elseSp31));

    elseStmts.push_back(i2);
    StmtLstNode elseSl = StmtLstNode(elseStmts);
    shared_ptr<StmtLstNode> elseSp = make_shared<StmtLstNode>(elseSl);

    //First If cond expr
    shared_ptr<IfNode> i = make_shared<IfNode>(IfNode(2,"x>3",ifSp,elseSp));

    p.visit(i, SPConstants::INVALID_LINE_NO);
}



















