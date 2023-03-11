#include "PKB/PkbRetriever.h"
#include <iostream>
#include "catch.hpp"

#include "QPS/constants/Constants.h"


/*Test for individual gets for modify*/

SCENARIO("Working version of PkbRetriever") {
	GIVEN("Valid instance of empty stores") {
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

		WHEN("The PkbRetriever references empty stores") {
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

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cStarsPointer, printAPointer, readAPointer, callAPointer);
			THEN("Getting all variables should return an empty set") {
				REQUIRE(pkbRet.getAllVar().size() == 0);
			}
			THEN("Getting all constants should return an empty set") {
				REQUIRE(pkbRet.getAllConst().size() == 0);
			}
			THEN("Getting all follows should return an empty set") {
				REQUIRE(pkbRet.getAllFollowees().size() == 0);
				REQUIRE(pkbRet.getAllFollowers().size() == 0);
			}
			THEN("Getting all constants should return an empty set") {
				REQUIRE(pkbRet.getAllConst().size() == 0);
			}
			THEN("Getting all procedures should return an empty set") {
				REQUIRE(pkbRet.getAllProc().size() == 0);
			}
			THEN("Getting all statements should return an empty set") {
				REQUIRE(pkbRet.getAllStmt(Constants::ASSIGN).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::READ).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::PRINT).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::CALL).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::WHILE).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::IF).size() == 0);
			}
			THEN("Getting all Lhs patterns should return an empty set") {
				REQUIRE(pkbRet.getAssignLhs("x").size() == 0);
				REQUIRE(pkbRet.getAssignLhs("y").size() == 0);
				REQUIRE(pkbRet.getAssignLhs("z").size() == 0);
			}
			THEN("Getting all Rhs patterns should return an empty string") {
				REQUIRE(pkbRet.getAssignRhs(1) == "");
				REQUIRE(pkbRet.getAssignRhs(2) == "");
				REQUIRE(pkbRet.getAssignRhs(3) == "");
			}
			THEN("Getting all follower star should return an empty set") {
				REQUIRE(pkbRet.getAllFollowerStar().size() == 0);
			}
			THEN("Getting all followee star should return an empty set") {
				REQUIRE(pkbRet.getAllFolloweeStar().size() == 0);
			}
			THEN("Getting all modifies statement should return an empty set") {
				REQUIRE(pkbRet.getAllModStmt().size() == 0);
			}
			THEN("Getting all modifies variable should return an empty set") {
				REQUIRE(pkbRet.getAllModVar().size() == 0);
			}
			THEN("Getting all modifiesProc procedure should return an empty set") {
				REQUIRE(pkbRet.getAllModPProc().size() == 0);
			}
			THEN("Getting all modifiesProc variable should return an empty set") {
				REQUIRE(pkbRet.getAllModPVar().size() == 0);
			}
			THEN("Getting all parents star parents should return an empty set") {
				REQUIRE(pkbRet.getAllParentStar().size() == 0);
			}
			THEN("Getting all parents star children should return an empty set") {
				REQUIRE(pkbRet.getAllChildrenStar().size() == 0);
			}
			THEN("Getting all parent should return an empty set") {
				REQUIRE(pkbRet.getAllParents().size() == 0);
			}
			THEN("Getting all uses statment should return an empty set") {
				REQUIRE(pkbRet.getAllUsesStmt().size() == 0);
			}
			THEN("Getting all uses variable should return an empty set") {
				REQUIRE(pkbRet.getAllUsesVar().size() == 0);
			}
			THEN("Getting all usesProc variable should return an empty set") {
				REQUIRE(pkbRet.getAllUsesPVar().size() == 0);
			}
			THEN("Getting all usesProc procedure should return an empty set") {
				REQUIRE(pkbRet.getAllUsesPProc().size() == 0);
			}
			THEN("Getting all left calls should return an empty set") {
				REQUIRE(pkbRet.getAllLeftCall().size() == 0);
			}
			THEN("Getting all right calls should return an empty set") {
				REQUIRE(pkbRet.getAllRightCall().size() == 0);
			}
			THEN("Getting all left calls star should return an empty set") {
				REQUIRE(pkbRet.getAllLeftCallStar().size() == 0);
			}
			THEN("Getting all right calls star should return an empty set") {
				REQUIRE(pkbRet.getAllRightCallStar().size() == 0);
			}
			THEN("Getting all print attributes and print statements should return an empty set") {
				REQUIRE(pkbRet.getAllPrintAttr().size() == 0);
				REQUIRE(pkbRet.getAllPrintStmt().size() == 0);
			}
			THEN("Getting all read attributes and read statements should return an empty set") {
				REQUIRE(pkbRet.getAllReadAttr().size() == 0);
				REQUIRE(pkbRet.getAllReadStmt().size() == 0);
			}
			THEN("Getting all call attributes and call statements should return an empty set") {
				REQUIRE(pkbRet.getAllCallAttr().size() == 0);
				REQUIRE(pkbRet.getAllCallStmt().size() == 0);
			}

		}
		WHEN("The PkbRetriever references non-empty stores") {
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

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cStarsPointer, printAPointer, readAPointer, callAPointer);
			vsPointer -> addVar("x");
			csPointer -> addConst(1);
			fsPointer -> addFollows(1, 2);
			psPointer -> addProc("testProc");
			ssPointer -> addStmt(Constants::ASSIGN, 1);
			pattsPointer->addAssignLhs("x", 1);
			pattsPointer->addAssignLhs("y", 2);
			pattsPointer->addAssignLhs("x", 3);
			pattsPointer->addAssignRhs(1, "y + 1");
			pattsPointer->addAssignRhs(2, "y + x");
			pattsPointer->addAssignRhs(3, "z + 2");
			fstarsPointer->addFollowsStar(1, std::unordered_set({ 2, 3 }));
			fstarsPointer->addFollowsStar(2, std::unordered_set({ 3 }));
			msPointer->addModifies(1, "x");
			mprocsPointer->addModifiesProc("sampleProc", "x");
			pStarsPointer->addParentStar(1, 2);
			pStarsPointer->addParentStar(1, 3);
			parentsPointer->addParent(1, 2);
			usesPointer->addUses(1, "x");
			uprocsPointer->addUsesProc("sampleProc", "x");
			callsPointer->addCalls("proc1", "proc2");
			cStarsPointer->addCallsStar("proc1", "proc2");
			cStarsPointer->addCallsStar("proc2", "proc3");
			cStarsPointer->addCallsStar("proc1", "proc3");
			printAPointer->addAttr("x", 1);
			readAPointer->addAttr("y", 2);
			callAPointer->addAttr("sampleProc", 3);

			THEN("Getting a variables hsould return a non empty set") {
				REQUIRE(pkbRet.getAllVar().size() == 1);
				REQUIRE(pkbRet.getAllVar().count("x") == 1);
			}
			THEN("Getting a constants should return a non empty set") {
				REQUIRE(pkbRet.getAllConst().size() == 1);
				REQUIRE(pkbRet.getAllConst().count(1) == 1);
			}
			THEN("Getting a follows should return a non empty set") {
				REQUIRE(pkbRet.getAllFollowees().size() == 1);
				REQUIRE(pkbRet.getAllFollowees().count(1) == 1);
				REQUIRE(pkbRet.getAllFollowers().size() == 1);
				REQUIRE(pkbRet.getAllFollowers().count(2) == 1);
			}
			THEN("Getting a procedures should return a non empty set") {
				REQUIRE(pkbRet.getAllProc().size() == 1);
				REQUIRE(pkbRet.getAllProc().count("testProc") == 1);
			}
			THEN("Getting all statements should return a non empty set") {
				REQUIRE(pkbRet.getAllStmt(Constants::ASSIGN).size() == 1);
				REQUIRE(pkbRet.getAllStmt(Constants::ASSIGN).count(1) == 1);
				REQUIRE(pkbRet.getAllStmt(Constants::READ).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::PRINT).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::CALL).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::WHILE).size() == 0);
				REQUIRE(pkbRet.getAllStmt(Constants::IF).size() == 0);
			}
			THEN("Getting a LHS assign should return a non empty set") {
				REQUIRE(pkbRet.getAssignLhs("x").size() == 2);
				REQUIRE(pkbRet.getAssignLhs("y").size() == 1);
				REQUIRE(pkbRet.getAssignLhs("x").count(1) == 1);
				REQUIRE(pkbRet.getAssignLhs("x").count(3) == 1);
				REQUIRE(pkbRet.getAssignLhs("y").count(2) == 1);
			}
			THEN("Getting a RHS assign should return an exact non empty string") {
				REQUIRE(pkbRet.getAssignRhs(1) == "y + 1");
				REQUIRE(pkbRet.getAssignRhs(1) != "y+1");
				REQUIRE(pkbRet.getAssignRhs(2) == "y + x");
				REQUIRE(pkbRet.getAssignRhs(2) != "y+x");
				REQUIRE(pkbRet.getAssignRhs(3) == "z + 2");
				REQUIRE(pkbRet.getAssignRhs(3) != "z+2");
			}
			THEN("Getting a follower star should return a non empty set") {
				REQUIRE(pkbRet.getFollowerStar(1).size() == 2);
				REQUIRE(pkbRet.getFollowerStar(2).size() == 1);
				REQUIRE(pkbRet.getFollowerStar(3).size() == 0);
				REQUIRE(pkbRet.getAllFollowerStar().size() == 2);
			}
			THEN("Getting a followee star should return a non empty set") {
				REQUIRE(pkbRet.getFolloweeStar(1).size() == 0);
				REQUIRE(pkbRet.getFolloweeStar(2).size() == 1);
				REQUIRE(pkbRet.getFolloweeStar(3).size() == 2);
				REQUIRE(pkbRet.getAllFolloweeStar().size() == 2);
			}
			THEN("Getting a modifies statement should return a non empty set") {
				REQUIRE(pkbRet.getModStmt("x").size() == 1);
				REQUIRE(pkbRet.getAllModStmt().size() == 1);
			}
			THEN("Getting a modifies variable should return a non empty set") {
				REQUIRE(pkbRet.getModVar(1).size() == 1);
				REQUIRE(pkbRet.getAllModVar().size() == 1);
			}
			THEN("Getting a modifiesProc procedure should return a non empty set") {
				REQUIRE(pkbRet.getModPProc("x").size() == 1);
				REQUIRE(pkbRet.getAllModPProc().size() == 1);
			}
			THEN("Getting a modifiesProc variable should return a non empty set") {
				REQUIRE(pkbRet.getModPVar("sampleProc").size() == 1);
				REQUIRE(pkbRet.getAllModPVar().size() == 1);
			}
			THEN("Getting parents star parent should return a non empty set") {
				REQUIRE(pkbRet.getParentStar(1).size() == 0);
				REQUIRE(pkbRet.getParentStar(2).size() == 1);
				REQUIRE(pkbRet.getParentStar(3).size() == 1);
				REQUIRE(pkbRet.getAllParentStar().size() == 1);
			}
			THEN("Getting parents star parent should return a non empty set") {
				REQUIRE(pkbRet.getChildrenStar(1).size() == 2);
				REQUIRE(pkbRet.getChildrenStar(2).size() == 0);
				REQUIRE(pkbRet.getChildrenStar(3).size() == 0);
				REQUIRE(pkbRet.getAllChildrenStar().size() == 2);
			}
			THEN("Getting parent should return a child") {
				REQUIRE(pkbRet.getParent(1) == -1);
				REQUIRE(pkbRet.getParent(2) == 1);
				REQUIRE(pkbRet.getParent(3) == -1);
				REQUIRE(pkbRet.getAllParents().size() == 1);
			}
			THEN("Getting a uses statment should return an empty set") {
				REQUIRE(pkbRet.getUsesStmt("x").size() == 1);
				REQUIRE(pkbRet.getAllUsesStmt().size() == 1);
			}
			THEN("Getting a uses variable should return an empty set") {
				REQUIRE(pkbRet.getUsesVar(1).size() == 1);
				REQUIRE(pkbRet.getAllUsesVar().size() == 1);
			}
			THEN("Getting a usesProc procedure should return a non empty set") {
				REQUIRE(pkbRet.getUsesPProc("x").size() == 1);
				REQUIRE(pkbRet.getAllUsesPProc().size() == 1);
			}
			THEN("Getting a usesProc variable should return a non empty set") {
				REQUIRE(pkbRet.getUsesPVar("sampleProc").size() == 1);
				REQUIRE(pkbRet.getAllUsesPVar().size() == 1);
			}
			THEN("Getting a call should return a non empty set") {
				REQUIRE(pkbRet.getLeftCall("proc2").size() == 1);
				REQUIRE(pkbRet.getRightCall("proc1").size() == 1);
				REQUIRE(pkbRet.getAllLeftCall().size() == 1);
				REQUIRE(pkbRet.getAllRightCall().size() == 1);
			}
			THEN("Getting a call star should return a non empty set") {
				REQUIRE(pkbRet.getLeftCallStar("proc2").size() == 1);
				REQUIRE(pkbRet.getRightCallStar("proc2").size() == 1);
				REQUIRE(pkbRet.getLeftCallStar("proc3").size() == 2);
				REQUIRE(pkbRet.getRightCallStar("proc1").size() == 2);
				REQUIRE(pkbRet.getAllLeftCallStar().size() == 2);
				REQUIRE(pkbRet.getAllRightCallStar().size() == 2);
			}
			THEN("Getting print attribute should return a non empty set") {
				REQUIRE(pkbRet.getPrintAttr(1).size() == 1);
				REQUIRE(pkbRet.getPrintStmt("x").size() == 1);
				REQUIRE(pkbRet.getAllPrintAttr().size() == 1);
				REQUIRE(pkbRet.getAllPrintStmt().size() == 1);
			}
			THEN("Getting read attribute should return a non empty set") {
				REQUIRE(pkbRet.getReadAttr(2).size() == 1);
				REQUIRE(pkbRet.getReadStmt("y").size() == 1);
				REQUIRE(pkbRet.getAllReadAttr().size() == 1);
				REQUIRE(pkbRet.getAllReadStmt().size() == 1);
			}
			THEN("Getting call attribute should return a non empty set") {
				REQUIRE(pkbRet.getCallAttr(3).size() == 1);
				REQUIRE(pkbRet.getCallStmt("sampleProc").size() == 1);
				REQUIRE(pkbRet.getAllCallAttr().size() == 1);
				REQUIRE(pkbRet.getAllCallStmt().size() == 1);
			}
		}
	}
}