#include "SP/DesignExtractor.h"
#include "SP/TNode.h"
#include "catch.hpp"
#include <regex>

using namespace std;
SCENARIO("ExtractingNode") {
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
    UsesProcStore uprocs;
    UsesStore uses;
    CallsStore calls;
    CallsStarStore cStars;
    PrintAttribute printA;
    ReadAttribute readA;
    CallAttribute callA;
    NextStore next;
    CFGStore cfg;
    ContainCallsStore concall;

    std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
    std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
    std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
    std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
    std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
    std::shared_ptr<PatternStore> pattsPointer = std::make_shared<PatternStore>(patts);
    std::shared_ptr<FollowsStarStore> fstarsPointer = std::make_shared<FollowsStarStore>(fstars);
    std::shared_ptr<ModifiesProcStore> mprocsPointer = std::make_shared<ModifiesProcStore>(mprocs);
    std::shared_ptr<ModifiesStore> msPointer = std::make_shared<ModifiesStore>(ms);
    std::shared_ptr<ParentStarStore> pStarsPointer = std::make_shared<ParentStarStore>(pStars);
    std::shared_ptr<ParentStore> parentsPointer = std::make_shared<ParentStore>(parents);
    std::shared_ptr<UsesProcStore> uprocsPointer = std::make_shared<UsesProcStore>(uprocs);
    std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);
    std::shared_ptr<CallsStore> callsPointer = std::make_shared<CallsStore>(calls);
    std::shared_ptr<CallsStarStore> cStarsPointer = std::make_shared<CallsStarStore>(cStars);
    std::shared_ptr<PrintAttribute> printAPointer = std::make_shared<PrintAttribute>(printA);
    std::shared_ptr<ReadAttribute> readAPointer = std::make_shared<ReadAttribute>(readA);
    std::shared_ptr<CallAttribute> callAPointer = std::make_shared<CallAttribute>(callA);
    std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);
    std::shared_ptr<CFGStore> cfgPointer = std::make_shared<CFGStore>(cfg);
    std::shared_ptr<ContainCallsStore> concallPointer = std::make_shared<ContainCallsStore>(concall);

    PkbPopulator pkbPopulator(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, 
        fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, 
        usesPointer, callsPointer, cStarsPointer, printAPointer, readAPointer, callAPointer, nextPointer, 
        cfgPointer, concallPointer);
    std::shared_ptr<PkbPopulator> pkbPop = std::make_shared<PkbPopulator>(pkbPopulator);
    GIVEN("ModifiesExtractor") {
        ModifiesExtractor m(pkbPop);
        WHEN("a assign node is visited") {
            AssignNode a = AssignNode(1, "v", "x", "test");
            shared_ptr<AssignNode> sp = make_shared<AssignNode>(a);
            m.visit(sp, a.getLine());
            THEN("v should populate") {
                REQUIRE(msPointer->getVar(a.getLine()) == std::unordered_set<std::string>({ "v" }));
            }
        }WHEN("a read node is visited parsed") {
            ReadNode r = ReadNode(2, "x", "test");
            shared_ptr<ReadNode> sp = make_shared<ReadNode>(r);
            m.visit(sp, r.getLine());
            THEN("v should populate") {
                REQUIRE(msPointer->getVar(r.getLine()) == std::unordered_set < std::string>({ "x" }));
            }
        }
    }
    GIVEN("UsesExtractor") {
        UsesExtractor u(pkbPop);
        WHEN("a assign node is visited parsed") {
            AssignNode a = AssignNode(1, "v", "x", "test");
            shared_ptr<AssignNode> sp = make_shared<AssignNode>(a);
            u.visit(sp, a.getLine());
            THEN("x should populate") {
                REQUIRE(usesPointer->getVar(a.getLine()) == std::unordered_set<std::string>({ "x" }));
            }
        }WHEN("a print node is visited parsed") {
            PrintNode p = PrintNode(2, "x", "test");
            shared_ptr<PrintNode> sp = make_shared<PrintNode>(p);
            u.visit(sp, p.getLine());
            THEN("x should populate") {
                REQUIRE(usesPointer->getVar(p.getLine()) == std::unordered_set < std::string>({ "x" }));
            }
        }
    }
    GIVEN("FollowsExtractor") {
        FollowsExtractor f(pkbPop);
        WHEN("a stmtlst node is visited") {
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a = AssignNode(1, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a);
            stmts.push_back(assign1);
            AssignNode a1 = AssignNode(2, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> s = make_shared<StmtLstNode>(sl);
            f.visit(s, 1);
            THEN("getRightStmt of 1 should return 2") {
                REQUIRE(fsPointer->getRightStmt(1) == 2);
            }
            THEN("getLeftStmt of 2 should return 1") {
                REQUIRE(fsPointer->getLeftStmt(2) == 1);
            }
        }
    }
    GIVEN("FollowsStarExtractor") {
        FollowsStarExtractor f(pkbPop);
        WHEN("a stmtlst node is visited") {
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a = AssignNode(1, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a);
            stmts.push_back(assign1);
            AssignNode a1 = AssignNode(2, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            AssignNode a2 = AssignNode(3, "v", "x", "test");
            shared_ptr<AssignNode> assign3 = make_shared<AssignNode>(a2);
            stmts.push_back(assign3);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> s = make_shared<StmtLstNode>(sl);
            f.visit(s, -1);
            THEN("getRightStar of 1 should return 2,3") {
                REQUIRE(fstarsPointer->getRightStar(1) == std::unordered_set<int>({ 2,3 }));
            }
            THEN("getLeftStar of 3 should return 1,2") {
                REQUIRE(fstarsPointer->getLeftStar(3) == std::unordered_set<int>({ 1,2 }));
            }
        }
    }
    GIVEN("ParentsExtractor") {
        ParentsExtractor p(pkbPop);
        WHEN("a if node is visited") {
            //ifNode
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a = AssignNode(2, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a);
            stmts.push_back(assign1);
            AssignNode a1 = AssignNode(3, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> ifStmtLst = make_shared<StmtLstNode>(sl);
            //elseNode
            std::vector<std::shared_ptr<StmtNode>> stmts1;
            AssignNode e = AssignNode(4, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign = make_shared<AssignNode>(e);
            stmts1.push_back(elseAssign);
            AssignNode e1 = AssignNode(5, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign2 = make_shared<AssignNode>(e1);
            stmts1.push_back(elseAssign2);
            StmtLstNode sl2 = StmtLstNode(stmts1, "test");
            shared_ptr<StmtLstNode> elseStmtLst = make_shared<StmtLstNode>(sl2);
            IfNode ifs = IfNode(1,"x>1",ifStmtLst,elseStmtLst,"test");
            shared_ptr<IfNode> ifNode = make_shared<IfNode>(ifs);
            p.visit(ifNode, 1);
            THEN("getRightStmt of 1 should return 2,3") {
                REQUIRE(parentsPointer->getRightStmt(1) == std::unordered_set<int>({ 2,3,4,5}));
            }
            THEN("getLeftStmt of 2 should return 1") {
                REQUIRE(parentsPointer->getLeftStmt(2) == 1);
            }
        }
    }
    GIVEN("ParentsStarExtractor") {
        ParentsStarExtractor p(pkbPop);
        WHEN("a if and nested while node is visited") {
            //ifNode
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a = AssignNode(2, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a);
            stmts.push_back(assign1);
            AssignNode a1 = AssignNode(3, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> ifStmtLst = make_shared<StmtLstNode>(sl);
            //elseNode
            std::vector<std::shared_ptr<StmtNode>> stmts1;
            AssignNode e = AssignNode(4, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign = make_shared<AssignNode>(e);
            stmts1.push_back(elseAssign);
            AssignNode e1 = AssignNode(5, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign2 = make_shared<AssignNode>(e1);
            stmts1.push_back(elseAssign2);
            //stmtLstNode for while
            std::vector<std::shared_ptr<StmtNode>> stmts9;
            AssignNode a8 = AssignNode(7, "v", "x", "test");
            shared_ptr<AssignNode> assign8 = make_shared<AssignNode>(a8);
            stmts9.push_back(assign8);
            AssignNode a9 = AssignNode(8, "v", "x", "test");
            shared_ptr<AssignNode> assign9 = make_shared<AssignNode>(a9);
            stmts9.push_back(assign9);
            StmtLstNode sl9 = StmtLstNode(stmts9, "test");
            shared_ptr<StmtLstNode> whStmtLst = make_shared<StmtLstNode>(sl9);
            WhileNode whs = WhileNode(6,"abc > cde",whStmtLst,"test");
            shared_ptr<WhileNode> whNode = make_shared<WhileNode>(whs);
            stmts1.push_back(whNode);
            StmtLstNode sl2 = StmtLstNode(stmts1, "test");
            shared_ptr<StmtLstNode> elseStmtLst = make_shared<StmtLstNode>(sl2);
            IfNode ifs = IfNode(1,"x>1",ifStmtLst,elseStmtLst,"test");
            shared_ptr<IfNode> ifNode = make_shared<IfNode>(ifs);
            p.visit(ifNode, 1);
            p.visit(whNode,6);
            THEN("getRightStar of 1 should return 2,3,4,5,6,7,8") {
                REQUIRE(pStarsPointer->getRightStar(1)== std::unordered_set<int>({ 2,3,4,5,6,7,8}));
            }
            THEN("getLeftStar of 7 should return 1,6") {
                REQUIRE(pStarsPointer->getLeftStar(7) == std::unordered_set<int>({1,6}));
            }
        }
    }
    GIVEN("CallsExtractor") {
        std::shared_ptr<SPUtils> spUtils = std::make_shared<SPUtils>();
        CallsExtractor c(pkbPop, spUtils);
        WHEN("a call node is visited") {
            spUtils->addProc("compute");
            CallNode c1 = CallNode(1, "compute", "test");
            shared_ptr<CallNode> call = make_shared<CallNode>(c1);
            c.visit(call,1);
            THEN("getRightProc of test should return compute") {
                REQUIRE(callsPointer->getRightProc("test") == std::unordered_set<std::string>({"compute"}));
            }
            THEN("getLeftProc of compute should return test") {
                REQUIRE(callsPointer->getLeftProc("compute") == std::unordered_set<std::string>({"test"}));
            }
        }
        WHEN("a call node that calls an non-existent procedure is visited") {
            CallNode c1 = CallNode(1, "compute", "test");
            shared_ptr<CallNode> call = make_shared<CallNode>(c1);

            THEN("should throw an error") {
                REQUIRE_THROWS_AS(c.visit(call,1), std::invalid_argument);
            }

        }
    }
    GIVEN("CallsStarExtractor") {
        CallsStarExtractor c(pkbPop);

        WHEN("a call node is visited") {
            CallNode c1 = CallNode(1, "compute", "test");
            shared_ptr<CallNode> call1 = make_shared<CallNode>(c1);
            CallNode c2 = CallNode(2, "centroid", "compute");
            shared_ptr<CallNode> call2 = make_shared<CallNode>(c2);
            c.visit(call1,1);
            c.visit(call2,1);
            THEN("getRightStar of test should return compute,centroid") {
                REQUIRE(cStarsPointer->getRightStar("test") == std::unordered_set<std::string>({"compute", "centroid"}));
            }
            THEN("getLeftStar of centroid should return test,compute") {
                REQUIRE(cStarsPointer->getLeftStar("centroid") == std::unordered_set<std::string>({"test", "compute"}));
            }
        }
    }
    GIVEN("PatternExtractor") {
        PatternExtractor p(pkbPop);
        WHEN("a assign node is visited") {
            AssignNode a = AssignNode(1, "v", "x - y + 2", "test");
            shared_ptr<AssignNode> assign = make_shared<AssignNode>(a);
            p.visit(assign,1);
            THEN("getAssignRhs of 1 should return correct expr") {
                REQUIRE(pattsPointer->getAssignRhs(1) == "x - y + 2");
            }
            THEN("getAssignLhs of v should return 1") {
                REQUIRE(pattsPointer->getAssignLhs("v") == std::unordered_set<int>({1}));
            }
        }
        WHEN("a if node is visited") {
            //ifNode
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a = AssignNode(2, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a);
            stmts.push_back(assign1);
            AssignNode a1 = AssignNode(3, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> ifStmtLst = make_shared<StmtLstNode>(sl);
            //elseNode
            std::vector<std::shared_ptr<StmtNode>> stmts1;
            AssignNode e = AssignNode(4, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign = make_shared<AssignNode>(e);
            stmts1.push_back(elseAssign);
            AssignNode e1 = AssignNode(5, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign2 = make_shared<AssignNode>(e1);
            stmts1.push_back(elseAssign2);
            StmtLstNode sl2 = StmtLstNode(stmts1, "test");
            shared_ptr<StmtLstNode> elseStmtLst = make_shared<StmtLstNode>(sl2);
            IfNode ifs = IfNode(1,"x + y > z",ifStmtLst,elseStmtLst,"test");
            shared_ptr<IfNode> ifNode = make_shared<IfNode>(ifs);
            p.visit(ifNode, 1);
            THEN("getIfVars of 1 should return correct expr") {
                REQUIRE(pattsPointer->getIfVars(1) == std::unordered_set<std::string>({"x", "y", "z"}));
            }
            THEN("getIfStatements of x should return 1") {
                REQUIRE(pattsPointer->getIfStatements("x") == std::unordered_set<int>({1}));
            }
        }
        WHEN("a while node is visited") {
            //stmtLstNode
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a = AssignNode(8, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a);
            stmts.push_back(assign1);
            AssignNode a1 = AssignNode(9, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> whStmtLst = make_shared<StmtLstNode>(sl);
            WhileNode whs = WhileNode(7,"abc > cde",whStmtLst,"test");
            shared_ptr<WhileNode> whNode = make_shared<WhileNode>(whs);
            p.visit(whNode, 7);
            THEN("getWhileVars of 1 should return abc,cde") {
                REQUIRE(pattsPointer->getWhileVars(7) == std::unordered_set<std::string>({"abc", "cde"}));
            }
            THEN("getWhileStatements of abc should return 1") {
                REQUIRE(pattsPointer->getWhileStatements("abc") == std::unordered_set<int>({7}));
            }
        }
    }
    GIVEN("AttributeExtractor") {
        AttributeExtractor a(pkbPop);
        WHEN("a assign node is visited") {
            AssignNode a1 = AssignNode(1, "v", "x + y + 2", "test");
            shared_ptr<AssignNode> assign = make_shared<AssignNode>(a1);
            a.visit(assign,1);
            THEN("getAllVar should return v,x,y") {
                REQUIRE(vsPointer->getAllVar() == std::unordered_set<std::string>({"v","x","y"}));
            }
            THEN("getAllConst should return 2") {
                REQUIRE(csPointer->getAllConst() == std::unordered_set<int>({2}));
            }
        }
        WHEN("a call node is visited") {
            CallNode c1 = CallNode(2, "compute", "test");
            shared_ptr<CallNode> call1 = make_shared<CallNode>(c1);
            a.visit(call1,2);
            THEN("getAttr() should return compute") {
                REQUIRE(callAPointer->getAttr(2) == "compute");
            }
        }
        WHEN("a read node is visited") {
            ReadNode r = ReadNode(3, "book", "test");
            shared_ptr<ReadNode> read = make_shared<ReadNode>(r);
            a.visit(read,3);
            THEN("getAttr() should return compute") {
                REQUIRE(readAPointer->getAttr(3) == "book");
            }
        }
        WHEN("a print node is visited") {
            PrintNode p = PrintNode(3, "ans", "test");
            shared_ptr<PrintNode> print = make_shared<PrintNode>(p);
            a.visit(print,4);
            THEN("getAttr() should return compute") {
                REQUIRE(printAPointer->getAttr(4) =="ans");
            }
        }
        WHEN("a if node is visited") {
            //ifNode
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a3 = AssignNode(2, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a3);
            stmts.push_back(assign1);
            AssignNode a1 = AssignNode(3, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> ifStmtLst = make_shared<StmtLstNode>(sl);
            //elseNode
            std::vector<std::shared_ptr<StmtNode>> stmts1;
            AssignNode e = AssignNode(4, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign = make_shared<AssignNode>(e);
            stmts1.push_back(elseAssign);
            AssignNode e1 = AssignNode(5, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign2 = make_shared<AssignNode>(e1);
            stmts1.push_back(elseAssign2);
            StmtLstNode sl2 = StmtLstNode(stmts1, "test");
            shared_ptr<StmtLstNode> elseStmtLst = make_shared<StmtLstNode>(sl2);
            IfNode ifs = IfNode(1,"x + y > z",ifStmtLst,elseStmtLst,"test");
            shared_ptr<IfNode> ifNode = make_shared<IfNode>(ifs);
            a.visit(ifNode, 1);
            THEN("getAllVar should return x,y,z") {
                REQUIRE(vsPointer->getAllVar() == std::unordered_set<std::string>({"x", "y", "z"}));
            }
        }
        WHEN("a while node is visited") {
            //stmtLstNode
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a3 = AssignNode(8, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a3);
            stmts.push_back(assign1);
            AssignNode a1 = AssignNode(9, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> whStmtLst = make_shared<StmtLstNode>(sl);
            WhileNode whs = WhileNode(7,"abc > cde",whStmtLst,"test");
            shared_ptr<WhileNode> whNode = make_shared<WhileNode>(whs);
            a.visit(whNode, 7);
            THEN("getAllVar should return abc,cde") {
                REQUIRE(vsPointer->getAllVar() == std::unordered_set<std::string>({"abc", "cde"}));
            }
        }
    }
    GIVEN("StatementExtractor") {
        StatementExtractor s(pkbPop);
        WHEN("a few nodes are visited") {
            CallNode c1 = CallNode(1, "compute", "test");
            shared_ptr<CallNode> call1 = make_shared<CallNode>(c1);
            AssignNode a3 = AssignNode(2, "v", "x", "test");
            shared_ptr<AssignNode> assign1 = make_shared<AssignNode>(a3);
            PrintNode p = PrintNode(3, "v", "test");
            shared_ptr<PrintNode> print = make_shared<PrintNode>(p);
            ReadNode r = ReadNode(4, "x", "test");
            shared_ptr<ReadNode> sp = make_shared<ReadNode>(r);
            //ifNode
            std::vector<std::shared_ptr<StmtNode>> stmts;
            AssignNode a4 = AssignNode(6, "v", "x", "test");
            shared_ptr<AssignNode> assign3 = make_shared<AssignNode>(a4);
            stmts.push_back(assign3);
            AssignNode a1 = AssignNode(7, "v", "x", "test");
            shared_ptr<AssignNode> assign2 = make_shared<AssignNode>(a1);
            stmts.push_back(assign2);
            StmtLstNode sl = StmtLstNode(stmts, "test");
            shared_ptr<StmtLstNode> ifStmtLst = make_shared<StmtLstNode>(sl);
            //elseNode
            std::vector<std::shared_ptr<StmtNode>> stmts1;
            AssignNode e = AssignNode(8, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign = make_shared<AssignNode>(e);
            stmts1.push_back(elseAssign);
            AssignNode e1 = AssignNode(9, "v", "x", "test");
            shared_ptr<AssignNode> elseAssign2 = make_shared<AssignNode>(e1);
            stmts1.push_back(elseAssign2);
            StmtLstNode sl2 = StmtLstNode(stmts1, "test");
            shared_ptr<StmtLstNode> elseStmtLst = make_shared<StmtLstNode>(sl2);
            IfNode ifs = IfNode(5,"x + y > z",ifStmtLst,elseStmtLst,"test");
            shared_ptr<IfNode> ifNode = make_shared<IfNode>(ifs);
            //stmtLstNode for while
            std::vector<std::shared_ptr<StmtNode>> stmts5;
            AssignNode a5 = AssignNode(11, "v", "x", "test");
            shared_ptr<AssignNode> assign6 = make_shared<AssignNode>(a5);
            stmts5.push_back(assign6);
            AssignNode a7 = AssignNode(12, "v", "x", "test");
            shared_ptr<AssignNode> assign8 = make_shared<AssignNode>(a7);
            stmts5.push_back(assign8);
            StmtLstNode sl4 = StmtLstNode(stmts5, "test");
            shared_ptr<StmtLstNode> whStmtLst = make_shared<StmtLstNode>(sl4);
            WhileNode whs = WhileNode(10,"abc > cde",whStmtLst,"test");
            shared_ptr<WhileNode> whNode = make_shared<WhileNode>(whs);
            s.visit(call1,1);
            s.visit(assign1,2);
            s.visit(print,3);
            s.visit(sp,4);
            s.visit(ifNode,5);
            s.visit(whNode,10);
            THEN("getAllStmt for call should return 1") {
                REQUIRE(ssPointer->getAllStmt("call") == std::unordered_set<int>({1}));
            }
            THEN("getAllStmt for assign should return 2") {
                REQUIRE(ssPointer->getAllStmt("assign") == std::unordered_set<int>({2}));
            }
            THEN("getAllStmt for print should return 3") {
                REQUIRE(ssPointer->getAllStmt("print") == std::unordered_set<int>({3}));
            }
            THEN("getAllStmt for print should return 4") {
                REQUIRE(ssPointer->getAllStmt("read") == std::unordered_set<int>({4}));
            }
            THEN("getAllStmt for if should return 5") {
                REQUIRE(ssPointer->getAllStmt("if") == std::unordered_set<int>({5}));
            }
            THEN("getAllStmt for while should return 10") {
                REQUIRE(ssPointer->getAllStmt("while") == std::unordered_set<int>({10}));
            }
        }
    }
}

