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

		WHEN("The PkbRetriever references empty stores") {
			std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
			std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
			std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
			std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
			std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
			std:shared_ptr<PatternStore> pattsPointer = std::make_shared<PatternStore>(patts);

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer);
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
		}
		WHEN("The PkbRetriever references non-empty stores") {
			std::shared_ptr vsPointer = std::make_shared<VariableStore>(vs);
			std::shared_ptr csPointer = std::make_shared<ConstantStore>(cs);
			std::shared_ptr fsPointer = std::make_shared<FollowsStore>(fs);
			std::shared_ptr psPointer = std::make_shared<ProcedureStore>(ps);
			std::shared_ptr ssPointer = std::make_shared<StatementStore>(ss);
			std::shared_ptr pattsPointer = std::make_shared<PatternStore>(patts);

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer);
			vsPointer -> add("x");
			csPointer -> add(1);
			fsPointer -> addFollows(1, 2);
			psPointer -> add("testProc");
			ssPointer -> addStmt("assign", 1);
			pattsPointer->addAssignLhs("x", 1);
			pattsPointer->addAssignLhs("y", 2);
			pattsPointer->addAssignLhs("x", 3);
			pattsPointer->addAssignRhs(1, "y + 1");
			pattsPointer->addAssignRhs(2, "y + x");
			pattsPointer->addAssignRhs(3, "z + 2");
			THEN("Getting all variables hsould return a non empty set") {
				REQUIRE(pkbRet.getAllVar().size() == 1);
				REQUIRE(pkbRet.getAllVar().count("x") == 1);
			}
			THEN("Getting all constants should return a non empty set") {
				REQUIRE(pkbRet.getAllConst().size() == 1);
				REQUIRE(pkbRet.getAllConst().count(1) == 1);
			}
			THEN("Getting all follows should return a non empty set") {
				REQUIRE(pkbRet.getAllFollowees().size() == 1);
				REQUIRE(pkbRet.getAllFollowees().count(2) == 1);
				REQUIRE(pkbRet.getAllFollowers().size() == 1);
				REQUIRE(pkbRet.getAllFollowers().count(1) == 1);
			}
			THEN("Getting all procedures should return a non empty set") {
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
		}
	}
}