#include "PKB/PkbPopulator.h"
#include <iostream>
#include "catch.hpp"

#include "QPS/constants/Constants.h"

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
		PrintAttribute printA;
		ReadAttribute readA;
		CallAttribute callA;
		NextStore next;
	

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
			std::shared_ptr<PrintAttribute> printAPointer = std::make_shared<PrintAttribute>(printA);
			std::shared_ptr<ReadAttribute> readAPointer = std::make_shared<ReadAttribute>(readA);
			std::shared_ptr<CallAttribute> callAPointer = std::make_shared<CallAttribute>(callA);
			std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);

			PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, 
				fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, 
				usesPointer, callsPointer, cStarsPointer, printAPointer, readAPointer, callAPointer, nextPointer);
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
				pkbPop.addStmt(Constants::ASSIGN, 2);
				REQUIRE(ssPointer->size() == 1);
			}
			THEN("Adding one follows relationship should increase the follows store size by 1") {
				REQUIRE(fsPointer->getAllRight().size() == 0);
				REQUIRE(fsPointer->getAllLeft().size() == 0);
				pkbPop.addFollows(1, 2);
				REQUIRE(fsPointer->getAllRight().size() == 1);
				REQUIRE(fsPointer->getAllLeft().size() == 1);
			}
			THEN("Adding one assign pattern should increase the LHS assign pattern store size by 1") {
				REQUIRE(pattsPointer->LhsAssignStoreSize() == 0);
				pkbPop.addAssignLhs("x", 1);
				REQUIRE(pattsPointer->LhsAssignStoreSize() == 1);
			}
			THEN("Adding one assign pattern should increase the RHS assign pattern store size by 1") {
				REQUIRE(pattsPointer->RhsAssignStoreSize() == 0);
				pkbPop.addAssignRhs(1, "x + y");
				REQUIRE(pattsPointer->RhsAssignStoreSize() == 1);
			}
			THEN("Adding one if pattern should increase the ifStatementStore size by 1") {
				REQUIRE(pattsPointer->ifStatementStoreSize() == 0);
				pkbPop.addIfStatement(1, "x");
				REQUIRE(pattsPointer->ifStatementStoreSize() == 1);
			}
			THEN("Adding one if pattern variable should increase the ifStatementVarStore size by 1") {
				REQUIRE(pattsPointer->ifStatementVarStoreSize() == 0);
				pkbPop.addIfStatementVar("x", 1);
				REQUIRE(pattsPointer->ifStatementVarStoreSize() == 1);
			}
			THEN("Adding one while pattern should increase the whileStatementStore size by 1") {
				REQUIRE(pattsPointer->whileStatementStoreSize() == 0);
				pkbPop.addWhileStatement(2, "y");
				REQUIRE(pattsPointer->whileStatementStoreSize() == 1);
			}
			THEN("Adding one while pattern variable should increase the whileStatementVarStore size by 1") {
				REQUIRE(pattsPointer->whileStatementVarStoreSize() == 0);
				pkbPop.addWhileStatementVar("y", 2);
				REQUIRE(pattsPointer->whileStatementVarStoreSize() == 1);
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
			THEN("Adding one call should increase the calls store size by 1") {
				REQUIRE(callsPointer->getAllLeft().size() == 0);
				REQUIRE(callsPointer->getAllRight().size() == 0);
				pkbPop.addCalls("sampleProc1", "sampleProc2");
				REQUIRE(callsPointer->getAllLeft().size() == 1);
				REQUIRE(callsPointer->getAllRight().size() == 1);
			}
			THEN("Adding one call star should increase the callsStar store size by 1") {
				REQUIRE(cStarsPointer->getAllLeft().size() == 0);
				REQUIRE(cStarsPointer->getAllRight().size() == 0);
				pkbPop.addCallsStar("sampleProc1", "sampleProc2");
				REQUIRE(cStarsPointer->getAllLeft().size() == 1);
				REQUIRE(cStarsPointer->getAllRight().size() == 1);
			}
			THEN("Adding one print attribute should increase print attribute store size by 1") {
				REQUIRE(printAPointer->getAllAttr().size() == 0);
				REQUIRE(printAPointer->getAllStmt().size() == 0);
				pkbPop.addPrintAttr("x", 1);
				REQUIRE(printAPointer->getAllAttr().size() == 1);
				REQUIRE(printAPointer->getAllStmt().size() == 1);
			}
			THEN("Adding one read attribute should increase print attribute store size by 1") {
				REQUIRE(readAPointer->getAllAttr().size() == 0);
				REQUIRE(readAPointer->getAllStmt().size() == 0);
				pkbPop.addReadAttr("y", 2);
				REQUIRE(readAPointer->getAllAttr().size() == 1);
				REQUIRE(readAPointer->getAllStmt().size() == 1);
			}
			THEN("Adding one print attribute should increase print attribute store size by 1") {
				REQUIRE(callAPointer->getAllAttr().size() == 0);
				REQUIRE(callAPointer->getAllStmt().size() == 0);
				pkbPop.addCallAttr("sampleProc", 3);
				REQUIRE(callAPointer->getAllAttr().size() == 1);
				REQUIRE(callAPointer->getAllStmt().size() == 1);
			}
			THEN("Adding one next statement should increase next store size by 1") {
				REQUIRE(nextPointer->getAllLeft().size() == 0);
				REQUIRE(nextPointer->getAllRight().size() == 0);
				pkbPop.addNext(1, 2);
				REQUIRE(nextPointer->getAllLeft().size() == 1);
				REQUIRE(nextPointer->getAllRight().size() == 1);
			}
		}
	}
}

