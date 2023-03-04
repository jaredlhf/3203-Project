#include "SP/DesignExtractor.h"
#include "SP/TNode.h"
#include "catch.hpp"
#include <regex>

using namespace std;
// sample test for testing purposes, actual design extractor is tested in the integration tests
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

    PkbPopulator pkbPopulator(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer,
                              mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer);
    std::shared_ptr<PkbPopulator> pkbPop = std::make_shared<PkbPopulator>(pkbPopulator);
    GIVEN("ModifiesExtractor") {
        ModifiesExtractor m(pkbPop);
        WHEN("a assign node is visited parsed") {
            AssignNode a = AssignNode(1, "v", "x");
            shared_ptr<AssignNode> sp = make_shared<AssignNode>(a);
            m.visit(sp, a.getLine());
            THEN("v should populate") {
                REQUIRE(msPointer->getVar(a.getLine()) == std::unordered_set<std::string>({ "v" }));
            }
        }WHEN("a read node is visited parsed") {
            ReadNode r = ReadNode(2, "x");
            shared_ptr<ReadNode> sp = make_shared<ReadNode>(r);
            m.visit(sp, r.getLine());
            THEN("v should populate") {
                REQUIRE(msPointer->getVar(r.getLine()) == std::unordered_set < std::string>({ "x" }));
            }
        }
    }
}

