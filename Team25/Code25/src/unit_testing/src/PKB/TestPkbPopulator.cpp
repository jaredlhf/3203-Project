#include "PKB/PkbPopulator.h"
#include <iostream>
#include "catch.hpp"

using namespace std;

SCENARIO("Working version of PkbPopulator") {
	GIVEN("Valid instances of empty stores") {
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

	

		WHEN("The PkbPopulator references empty stores") {
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
		

			PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cStarsPointer);
			THEN("Adding one variable should increase the variable store size by 1") {
				REQUIRE(vsPointer->size() == 0);
				pkbPop.addVar("x");
				REQUIRE(vsPointer->size() == 1);
			}
			THEN("Adding one constant should increase the constant store size by 1") {
				REQUIRE(csPointer->size() == 0);
				pkbPop.addConst(10000);
				REQUIRE(csPointer->size() == 1);
			}
			THEN("Adding one procedure should increase the procedure store size by 1") {
				REQUIRE(psPointer->size() == 0);
				pkbPop.addProc("sampleProc");
				REQUIRE(psPointer->size() == 1);
			}
			THEN("Adding one statement should increase the statement store size by 1") {
				REQUIRE(ssPointer->size() == 0);
				pkbPop.addStmt("assign", 2);
				REQUIRE(ssPointer->size() == 1);
			}
			THEN("Adding one follows relationship should increase the follows store size by 1") {
				REQUIRE(fsPointer->getAllRight().size() == 0);
				REQUIRE(fsPointer->getAllLeft().size() == 0);
				pkbPop.addFollows(1, 2);
				REQUIRE(fsPointer->getAllRight().size() == 1);
				REQUIRE(fsPointer->getAllLeft().size() == 1);
			}
			THEN("Adding one pattern should increase the LHS pattern store size by 1") {
				REQUIRE(pattsPointer->LhsAssignStoreSize() == 0);
				pkbPop.addAssignLhs("x", 1);
				REQUIRE(pattsPointer->LhsAssignStoreSize() == 1);
			}
			THEN("Adding one pattern should increase the RHS pattern store size by 1") {
				REQUIRE(pattsPointer->RhsAssignStoreSize() == 0);
				pkbPop.addAssignRhs(1, "x + y");
				REQUIRE(pattsPointer->RhsAssignStoreSize() == 1);
			}
			THEN("Adding one follows star should increase the follows star store size by 1") {
				REQUIRE(fstarsPointer->getAllRight().size() == 0);
				REQUIRE(fstarsPointer->getAllLeft().size() == 0);
				pkbPop.addFollowsStar(1, std::unordered_set<int>({1, 2, 3}));
				REQUIRE(fstarsPointer->getAllRight().size() == 3);
				REQUIRE(fstarsPointer->getAllLeft().size() == 1);
			}
			THEN("Adding one modifes procedure should increase the modifiesProc store size by 1") {
				REQUIRE(mprocsPointer->getAllProc().size() == 0);
				REQUIRE(mprocsPointer->getAllVar().size() == 0);
				pkbPop.addModifiesProc("sampleProc", "x");
				REQUIRE(mprocsPointer->getAllProc().size() == 1);
				REQUIRE(mprocsPointer->getAllVar().size() == 1);
			}
			THEN("Adding one modifes should increase the modifies store size by 1") {
				REQUIRE(msPointer->getAllStmt().size() == 0);
				REQUIRE(msPointer->getAllVar().size() == 0);
				pkbPop.addModifies(1, "x");
				REQUIRE(msPointer->getAllStmt().size() == 1);
				REQUIRE(msPointer->getAllVar().size() == 1);
			}
			THEN("Adding one parentsStar should increase the parentsStar store size by 1") {
				REQUIRE(pStarsPointer->getAllLeft().size() == 0);
				REQUIRE(pStarsPointer->getAllRight().size() == 0);
				pkbPop.addParentStar(1, 1);
				REQUIRE(pStarsPointer->getAllLeft().size() == 1);
				REQUIRE(pStarsPointer->getAllRight().size() == 1);
			}
			THEN("Adding one parent should increase the parent store size by 1") {
				REQUIRE(parentsPointer->getAllLeft().size() == 0);
				REQUIRE(parentsPointer->getAllRight().size() == 0);
				pkbPop.addParent(1, 1);
				REQUIRE(parentsPointer->getAllLeft().size() == 1);
				REQUIRE(parentsPointer->getAllRight().size() == 1);
			}
			THEN("Adding one uses procedure should increase the usesProc store size by 1") {
				REQUIRE(uprocsPointer->getAllProc().size() == 0);
				REQUIRE(uprocsPointer->getAllVar().size() == 0);
				pkbPop.addUsesProc("sampleProc", "y");
				REQUIRE(uprocsPointer->getAllProc().size() == 1);
				REQUIRE(uprocsPointer->getAllVar().size() == 1);
			}
			THEN("Adding one uses should increase the uses store size by 1") {
				REQUIRE(usesPointer->getAllStmt().size() == 0);
				REQUIRE(usesPointer->getAllVar().size() == 0);
				pkbPop.addUses(1, "y");
				REQUIRE(usesPointer->getAllStmt().size() == 1);
				REQUIRE(usesPointer->getAllVar().size() == 1);
			}
		}
	}
}

