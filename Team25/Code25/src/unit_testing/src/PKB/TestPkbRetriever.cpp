#include "PKB/PkbRetriever.h"
#include <iostream>
#include "catch.hpp"

using namespace std;

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

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer);
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
				REQUIRE(pkbRet.getAllStmt("assign").size() == 0);
				REQUIRE(pkbRet.getAllStmt("read").size() == 0);
				REQUIRE(pkbRet.getAllStmt("print").size() == 0);
				REQUIRE(pkbRet.getAllStmt("call").size() == 0);
				REQUIRE(pkbRet.getAllStmt("while").size() == 0);
				REQUIRE(pkbRet.getAllStmt("if").size() == 0);
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
				REQUIRE(pkbRet.getFollowerStar(1).size() == 0);
				REQUIRE(pkbRet.getFollowerStar(2).size() == 0);
				REQUIRE(pkbRet.getFollowerStar(3).size() == 0);
			}
			THEN("Getting all followee star should return an empty set") {
				REQUIRE(pkbRet.getFolloweeStar(1).size() == 0);
				REQUIRE(pkbRet.getFolloweeStar(2).size() == 0);
				REQUIRE(pkbRet.getFolloweeStar(3).size() == 0);
			}
			THEN("Getting all modifies statement should return an empty set") {
				REQUIRE(pkbRet.getModStmt("x").size() == 0);
				REQUIRE(pkbRet.getModStmt("y").size() == 0);
				REQUIRE(pkbRet.getModStmt("z").size() == 0);
			}
			THEN("Getting all modifies variable should return an empty set") {
				REQUIRE(pkbRet.getModVar(1).size() == 0);
				REQUIRE(pkbRet.getModVar(2).size() == 0);
				REQUIRE(pkbRet.getModVar(3).size() == 0);
			}
			THEN("Getting all parents star parents should return an empty set") {
				REQUIRE(pkbRet.getParentStar(1).size() == 0);
				REQUIRE(pkbRet.getParentStar(2).size() == 0);
				REQUIRE(pkbRet.getParentStar(3).size() == 0);
			}
			THEN("Getting all parents star children should return an empty set") {
				REQUIRE(pkbRet.getChildrenStar(1).size() == 0);
				REQUIRE(pkbRet.getChildrenStar(2).size() == 0);
				REQUIRE(pkbRet.getChildrenStar(3).size() == 0);
			}
			THEN("Getting all parent should return -1") {
				REQUIRE(pkbRet.getParent(1) == -1);
				REQUIRE(pkbRet.getParent(2) == -1);
				REQUIRE(pkbRet.getParent(3) == -1);
			}
			THEN("Getting all uses statment should return an empty set") {
				REQUIRE(pkbRet.getUsesStmt("x").size() == 0);
				REQUIRE(pkbRet.getUsesStmt("y").size() == 0);
				REQUIRE(pkbRet.getUsesStmt("z").size() == 0);
			}
			THEN("Getting all uses variable should return an empty set") {
				REQUIRE(pkbRet.getUsesVar(1).size() == 0);
				REQUIRE(pkbRet.getUsesVar(2).size() == 0);
				REQUIRE(pkbRet.getUsesVar(3).size() == 0);
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

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer);
			vsPointer -> addVar("x");
			csPointer -> addConst(1);
			fsPointer -> addFollows(1, 2);
			psPointer -> addProc("testProc");
			ssPointer -> addStmt("assign", 1);
			pattsPointer->addAssignLhs("x", 1);
			pattsPointer->addAssignLhs("y", 2);
			pattsPointer->addAssignLhs("x", 3);
			pattsPointer->addAssignRhs(1, "y + 1");
			pattsPointer->addAssignRhs(2, "y + x");
			pattsPointer->addAssignRhs(3, "z + 2");
			fstarsPointer->addFollowsStar(1, std::unordered_set({ 1, 2, 3 }));
			msPointer->addModifies(1, "x");
			pStarsPointer->addParentStar(1, 2);
			parentsPointer->addParent(1, 2);
			usesPointer->addUses(1, "x");
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
				REQUIRE(pkbRet.getAllStmt("assign").size() == 1);
				REQUIRE(pkbRet.getAllStmt("assign").count(1) == 1);
				REQUIRE(pkbRet.getAllStmt("read").size() == 0);
				REQUIRE(pkbRet.getAllStmt("print").size() == 0);
				REQUIRE(pkbRet.getAllStmt("call").size() == 0);
				REQUIRE(pkbRet.getAllStmt("while").size() == 0);
				REQUIRE(pkbRet.getAllStmt("if").size() == 0);
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
				REQUIRE(pkbRet.getFollowerStar(1).size() == 3);
				REQUIRE(pkbRet.getFollowerStar(2).size() == 0);
				REQUIRE(pkbRet.getFollowerStar(3).size() == 0);
			}
			THEN("Getting a followee star should return a non empty set") {
				REQUIRE(pkbRet.getFolloweeStar(1).size() == 1);
				REQUIRE(pkbRet.getFolloweeStar(2).size() == 1);
				REQUIRE(pkbRet.getFolloweeStar(3).size() == 1);
			}
			THEN("Getting a modifies statement should return a non empty set") {
				REQUIRE(pkbRet.getModStmt("x").size() == 1);
				REQUIRE(pkbRet.getModStmt("y").size() == 0);
				REQUIRE(pkbRet.getModStmt("z").size() == 0);
			}
			THEN("Getting a modifies variable should return a non empty set") {
				REQUIRE(pkbRet.getModVar(1).size() == 1);
				REQUIRE(pkbRet.getModVar(2).size() == 0);
				REQUIRE(pkbRet.getModVar(3).size() == 0);
			}
			THEN("Getting parents star parent should return a non empty set") {
				REQUIRE(pkbRet.getParentStar(1).size() == 0);
				REQUIRE(pkbRet.getParentStar(2).size() == 1);
				REQUIRE(pkbRet.getParentStar(3).size() == 0);
			}
			THEN("Getting parents star parent should return a non empty set") {
				REQUIRE(pkbRet.getChildrenStar(1).size() == 1);
				REQUIRE(pkbRet.getChildrenStar(2).size() == 0);
				REQUIRE(pkbRet.getChildrenStar(3).size() == 0);
			}
			THEN("Getting parent should return non -1") {
				REQUIRE(pkbRet.getParent(1) == -1);
				REQUIRE(pkbRet.getParent(2) == 1);
				REQUIRE(pkbRet.getParent(3) == -1);
			}
			THEN("Getting a uses statment should return an empty set") {
				REQUIRE(pkbRet.getUsesStmt("x").size() == 1);
				REQUIRE(pkbRet.getUsesStmt("y").size() == 0);
				REQUIRE(pkbRet.getUsesStmt("z").size() == 0);
			}
			THEN("Getting a uses variable should return an empty set") {
				REQUIRE(pkbRet.getUsesVar(1).size() == 1);
				REQUIRE(pkbRet.getUsesVar(2).size() == 0);
				REQUIRE(pkbRet.getUsesVar(3).size() == 0);
			}
		}
	}
}